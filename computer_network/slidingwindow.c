#include “sysinclude.h”
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>


#define WINDOW_SIZE_STOP_WAIT 1
#define WINDOW_SIZE_BACK_N_FRAME 4
#define MAX_WAITLIST_NUM 1000

typedef enum{data,ack,nak} frame_kind; //帧类型：数据，肯定应答，否定应答

typedef struct frame_head//帧头
{
    frame_kind kind;//帧类型
    unsigned int seq;//序列号
    unsigned int ack;//确认号
    unsigned char data[100]; //数据
};
typedef struct frame//帧内容
{
    struct frame_head head;//帧头
    unsigned int size;//数据大小
};

//发送帧函数
extern void SendFRAMEPacket(unsigned char* pData, unsigned int len);


//停等协议测试函数
int stud_slide_window_stop_and_wait(char *pBuffer, int bufferSize, UINT8 messageType)
{
    static struct frame *winlist[WINDOW_SIZE_STOP_WAIT] = {0};//定义发送窗口序列winlist，停等协议中只有一个窗口
    static struct frame *waitlist[MAX_WAITLIST_NUM] = {0};//定义等待序列waitlist，最大为1000
    static int wait_begin = 0, wait_end = 0;//等待序列的首尾序号
    static int win_sum = 0, wait_sum = 0;//定义窗口序列、等待序列的总长度

    //发送，添加到发送队列，若无需停等则发送启动定时
    if(messageType==MSG_TYPE_SEND)
    {
        waitlist[wait_end] = (struct frame *)malloc(sizeof (struct frame));
        memcpy(waitlist[wait_end], (struct frame *)pBuffer, sizeof (struct frame));//将帧添加进waitlist
        waitlist[wait_end]->size = (unsigned int)bufferSize;

        if (wait_end < MAX_WAITLIST_NUM-2)//改变结尾序号
        {wait_end++;}
        else
        {wait_end=wait_end - MAX_WAITLIST_NUM + 1;}

        wait_sum++;

        if (win_sum < 1)//如果窗口序列为空
        {
            //将等待序列的第一个帧添加进窗口序列
            struct frame *temp = waitlist[wait_begin];
            //等待序列改变开头序号
            if (wait_begin < MAX_WAITLIST_NUM-2)
            {wait_begin++;}
            else
            {wait_begin=wait_end - MAX_WAITLIST_NUM + 1;}

            wait_sum—;

            winlist[0] = temp;
            win_sum = 1;

            //发送
            SendFRAMEPacket((unsigned char *)htonl(temp), temp->size);
        }
        else//窗口序列不为空，直接发送
        {
            struct frame *temp = winlist[0];
            SendFRAMEPacket((unsigned char *)htonl(temp), temp->size);
            win_sum = 0;
        }
    }

    //接收，确认队首已收到，结束定时器
    else if(messageType==MSG_TYPE_RECEIVE)
    {
        struct frame *temp = (struct frame *)pBuffer;
        frame_kind kind = (frame_kind)ntohl((unsigned long)temp->head.kind);//转为主机序且提取数据类型

        if (kind == nak) //当收到否定应答时，重新发送这一帧
        {
            struct frame *temp_1 = winlist[0];\
            SendFRAMEPacket((unsigned char *)htonl(temp_1), temp_1->size);
        }
        else if (kind == ack) //当收到肯定应答时，等待发送的帧进入发送窗口并发送
        {
            unsigned int ack = ntohl(temp->head.ack);
            while (ntohl(winlist[0]->head.seq) == ack)
            {
                //将ack对应的窗口关闭
                free(winlist[0]);
                win_sum = 0;

                //发送下一帧
                if (wait_sum > 0)
                {
                    winlist[0] = waitlist[wait_begin];
                    SendFRAMEPacket((unsigned char *)htonl(winlist[0]),winlist[0]->size);

                    if (wait_begin < MAX_WAITLIST_NUM-2)
                    {wait_begin++;}
                    else
                    {wait_begin=wait_end - MAX_WAITLIST_NUM + 1;}

                    wait_sum—;
                    win_sum = 1;
                }
            }
        }
    }
    //超时重发
    else if(messageType==MSG_TYPE_TIMEOUT)
    {
        struct frame *temp = winlist[0];
        SendFRAMEPacket((unsigned char *)htonl(temp), temp->size);
    }
    else return -1;
    return 0;
}




//回退 N 帧协议测试函数
int stud_slide_window_back_n_frame(char *pBuffer, int bufferSize, UINT8 messageType)
{
    static struct frame *winlist[WINDOW_SIZE_STOP_WAIT] = {0};//定义发送窗口序列winlist，停等协议中只有一个窗口
    static struct frame *waitlist[MAX_WAITLIST_NUM] = {0};//定义等待序列waitlist，最大为1000
    static int win_begin = 0, win_end = 0;//窗口序列的首尾序号
    static int wait_begin = 0, wait_end = 0;//等待序列的首尾序号
    static int win_sum = 0, wait_sum = 0;//定义窗口序列、等待序列的总长度

    //发送
    if (messageType == MSG_TYPE_SEND) {
        waitlist[wait_end] = (struct frame *)malloc(sizeof (struct frame));
        memcpy(waitlist[wait_end], (struct frame *)pBuffer, sizeof (struct frame));//将帧添加进等待序列
        waitlist[wait_end]->size = (unsigned int)bufferSize;

        if (wait_end < MAX_WAITLIST_NUM-2)//改变结尾序号
        {wait_end++;}
        else
        {wait_end=wait_end - MAX_WAITLIST_NUM + 1;}

        wait_sum++;

        // 当发送窗口未满时，从等待序列中添加
        while (win_sum < WINDOW_SIZE_BACK_N_FRAME)
        {
            struct frame *temp = waitlist[wait_begin];
            //等待序列改变开头序号
            if (wait_begin < MAX_WAITLIST_NUM-2)
            {wait_begin++;}
            else
            {wait_begin=wait_end - MAX_WAITLIST_NUM + 1;}

            wait_sum—;

            winlist[win_end] = temp;

            //等待窗口序列结尾序号
            if (win_end < WINDOW_SIZE_BACK_N_FRAME-2)
            {win_end++;}
            else
            {win_end=win_end - WINDOW_SIZE_BACK_N_FRAME + 1;}

            win_sum++;

        }
        //发送窗口满后，发送
        int win_num = win_begin;
        while (win_sum > 0)
        {
            struct frame *temp = winlist[win_num];
            SendFRAMEPacket((unsigned char *)htonl(temp), temp->size);
            win_sum—;
            win_num++;
        }
    }
        //确认收到
    else if (messageType == MSG_TYPE_RECEIVE) {
        struct frame *temp = (struct frame *)pBuffer;
        frame_kind kind = (frame_kind)ntohl((unsigned long)temp->head.kind);

        if (kind == nak) //如果收到否定应答，检查哪一帧出错，重发之后的帧
        {
            int find = win_begin;
            unsigned int seq = ntohl(temp->head.ack);
            while (seq != ntohl(winlist[find]->head.seq))//寻找出错帧
            {
                if (find < WINDOW_SIZE_BACK_N_FRAME-2)
                {find++;}
                else
                {find=find - WINDOW_SIZE_BACK_N_FRAME + 1;}
            }
            while(find <= win_end)
            {
                SendFRAMEPacket((unsigned char *)htonl(winlist[find]),winlist[find]->size);
                find++;
            }
        }
        else if (kind == ack) //如果是肯定应答，因为时累计确认，关闭多个窗口，从等待序列中添加并发送
        {
            unsigned int ack = ntohl(temp->head.ack);
            while (ntohl(winlist[win_begin]->head.seq) < ack)
            {
                free(winlist[win_begin]);//关闭窗口
                win_sum—;

                if (win_begin < WINDOW_SIZE_BACK_N_FRAME-2)
                {win_begin++;}
                else
                {win_begin=win_begin - WINDOW_SIZE_BACK_N_FRAME + 1;}

                win_sum—;
                // 当等待序列非空，添加一个到窗口序列并发送，否则，不发送
                if (wait_sum > 0)
                {
                    //确定添加位置
                    if (win_end < WINDOW_SIZE_BACK_N_FRAME-2)
                    {win_end++;}
                    else
                    {win_end=win_end - WINDOW_SIZE_BACK_N_FRAME + 1;}
                    //添加
                    winlist[win_end] = waitlist[wait_begin];
                    //发送
                    SendFRAMEPacket((unsigned char *)htonl(winlist[win_end]),winlist[win_end]->size);

                    wait_sum—;
                    win_sum++;
                }
            }
        }
    }
        // 超时重发
        /*
        回退N滑动窗口协议在超时情况下， 本应发与超时帧seq值相同的帧及其后续帧；然而实验中需要将滑动窗口中的所有帧重发
        */
    else if (messageType == MSG_TYPE_TIMEOUT) {
        UINT8 temp = ntohl(*((UINT8 *)pBuffer));
        int find = win_begin;
        while(find <= win_end)
        {
            SendFRAMEPacket((unsigned char *)htonl(winlist[find]),winlist[find]->size);
            find++;
        }
    }
    else return -1;
    return 0;
}


//选择性重传协议测试函数
//与回退N协议相似，差别在发现错误或超时后重发一帧还是多帧
int stud_slide_window_choice_frame_resend(char *pBuffer, int bufferSize, UINT8 messageType)
{
    static struct frame *winlist[WINDOW_SIZE_STOP_WAIT] = {0};//定义发送窗口序列winlist，停等协议中只有一个窗口
    static struct frame *waitlist[MAX_WAITLIST_NUM] = {0};//定义等待序列waitlist，最大为1000
    static int win_begin = 0, win_end = 0;//窗口序列的首尾序号
    static int wait_begin = 0, wait_end = 0;//等待序列的首尾序号
    static int win_sum = 0, wait_sum = 0;//定义窗口序列、等待序列的总长度

    //发送
    if (messageType == MSG_TYPE_SEND) {
        waitlist[wait_end] = (struct frame *)malloc(sizeof (struct frame));
        memcpy(waitlist[wait_end], (struct frame *)pBuffer, sizeof (struct frame));//将帧添加进等待序列
        waitlist[wait_end]->size = (unsigned int)bufferSize;

        if (wait_end < MAX_WAITLIST_NUM-2)//改变结尾序号
        {wait_end++;}
        else
        {wait_end=wait_end - MAX_WAITLIST_NUM + 1;}

        wait_sum++;

        // 当发送窗口未满时，从等待序列中添加
        while (win_sum < WINDOW_SIZE_BACK_N_FRAME)
        {
            struct frame *temp = waitlist[wait_begin];
            //等待序列改变开头序号
            if (wait_begin < MAX_WAITLIST_NUM-2)
            {wait_begin++;}
            else
            {wait_begin=wait_end - MAX_WAITLIST_NUM + 1;}

            wait_sum—;

            winlist[win_end] = temp;

            //等待窗口序列结尾序号
            if (win_end < WINDOW_SIZE_BACK_N_FRAME-2)
            {win_end++;}
            else
            {win_end=win_end - WINDOW_SIZE_BACK_N_FRAME + 1;}

            win_sum++;

        }
        //发送窗口满后，发送
        int win_num = win_begin;
        while (win_sum > 0)
        {
            struct frame *temp = winlist[win_num];
            SendFRAMEPacket((unsigned char *)htonl(temp), temp->size);
            win_sum—;
            win_num++;
        }
    }
        //确认收到
    else if (messageType == MSG_TYPE_RECEIVE) {
        struct frame *temp = (struct frame *)pBuffer;
        frame_kind kind = (frame_kind)ntohl((unsigned long)temp->head.kind);

        if (kind == nak) //如果收到否定应答，检查哪一帧出错，重发该帧
        {
            int find = win_begin;
            unsigned int seq = ntohl(temp->head.ack);
            while (seq != ntohl(winlist[find]->head.seq))//寻找出错帧
            {
                if (find < WINDOW_SIZE_BACK_N_FRAME-2)
                {find++;}
                else
                {find=find - WINDOW_SIZE_BACK_N_FRAME + 1;}
            }
            //重发
            SendFRAMEPacket((unsigned char *)htonl(winlist[find]),winlist[find]->size);
        }
        else if (kind == ack) //如果是肯定应答，因为时累计确认，关闭多个窗口，从等待序列中添加并发送
        {
            unsigned int ack = ntohl(temp->head.ack);
            while (ntohl(winlist[win_begin]->head.seq) <= ack)
            {
                free(winlist[win_begin]);//关闭窗口
                win_sum—;

                if (win_begin < WINDOW_SIZE_BACK_N_FRAME-2)
                {win_begin++;}
                else
                {win_begin=win_begin - WINDOW_SIZE_BACK_N_FRAME + 1;}

                win_sum—;
                // 当等待序列非空，添加一个到窗口序列并发送，否则，不发送
                if (wait_sum > 0)
                {
                    //确定添加位置
                    if (win_end < WINDOW_SIZE_BACK_N_FRAME-2)
                    {win_end++;}
                    else
                    {win_end=win_end - WINDOW_SIZE_BACK_N_FRAME + 1;}
                    //添加
                    winlist[win_end] = waitlist[wait_begin];
                    //发送
                    SendFRAMEPacket((unsigned char *)htonl(winlist[win_end]),winlist[win_end]->size);

                    wait_sum—;
                    win_sum++;
                }
            }
        }
    }
        // 超时重发
    else if (messageType == MSG_TYPE_TIMEOUT) {
        UINT8 temp = ntohl(*((UINT8 *)pBuffer));
        int find = win_begin;
        unsigned int seq = ntohl(temp->head.ack);
        while (seq != ntohl(winlist[find]->head.seq))//寻找超时
        {
            if (find < WINDOW_SIZE_BACK_N_FRAME-2)
            {find++;}
            else
            {find=find - WINDOW_SIZE_BACK_N_FRAME + 1;}
        }
        //重发
        SendFRAMEPacket((unsigned char *)htonl(winlist[find]),winlist[find]->size);
    }
    else return -1;
    return 0;
}
