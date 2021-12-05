#include "sysInclude.h"
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>

//系统提供的接口函数
//丢弃报文
extern void tcp_DiscardPkt(char *pBuffer, int type);
//IP 报文发送
extern void tcp_sendIpPkt(unsigned char *pData, UINT16 len, unsigned int  srcAddr, unsigned int dstAddr, UINT8	ttl);
//IP 数据报文主动接收
extern int waitIpPacket(char *pBuffer, int timeout);
//客户端获得本机 IPv4 地址
extern unsigned int getIpv4Address();
//客户端获得服务器 IPv4 地址
extern unsigned int getServerIpv4Address();

//全局变量
int gSrcPort = 2005;
int gDstPort = 2006;
int gSeqNum = 0;
int gAckNum = 0;
int SockNum = 5;

//传输控制块
typedef struct TCB              
{
    unsigned int srcAddr;//源地址
    unsigned int dstAddr;//目的地址
    unsigned short srcPort;//源端口
    unsigned short dstPort;//目的端口
    unsigned int seq;//序号
    unsigned int ack;//确认序号
    int sockfd;
    BYTE state; 
    unsigned char* data;
};
//TCP头部结构
typedef struct tcp_head
{           
    UINT16 SrcPort;
    UINT16 DstPort;
    UINT32 SeqNo;
    UINT32 AckNo;
    UINT8  HeadLen;
    UINT8  Flag;  
    UINT16 WindowSize;
    UINT16 CheckSum;
    UINT16 UrgentPointer;
    char data[100];  
};

typedef struct TCB_node
{
    struct TCB* current;
    struct TCB_node* next;
    
};


struct TCB *current_TCB;
struct TCB_node *TCB_table;

//状态state
enum state_
{
    CLOSED,
    SYN_SENT,
    ESTABLISHED,
    FIN_WAIT1,
    FIN_WAIT2,
    TIME_WAIT
};

//TCP分组接收
int stud_tcp_input(char *pBuffer, unsigned short len, unsigned int srcAddr, unsigned int dstAddr)
{
    struct tcp_head* head = (struct tcp_head*)pBuffer;
    head->SeqNo = ntohl(head->SeqNo);
    head->AckNo = ntohl(head->AckNo);
    //计算校验和
    unsigned int local_checksum = 0;
    unsigned int local_srcAddr = ntohl(srcAddr);
    unsigned int local_dstAddr = ntohl(dstAddr);
    local_checksum += (local_srcAddr >> 16) + local_srcAddr&0xffff;
    local_checksum += (local_dstAddr >> 16) + local_dstAddr&0xffff;
    local_checksum += IPPROTO_TCP;
    local_checksum += 0x14;
    local_checksum += ntohs(head->SrcPort) + ntohs(head->DstPort);
    local_checksum += ntohs(head->WindowSize);
    local_checksum += ntohs(head->UrgentPointer);
    local_checksum += ((head->SeqNo)>>16)+(head->SeqNo)&0xffff;
    local_checksum += ((head->AckNo)>>16)+(head->AckNo)&0xffff;
    local_checksum += ((head->HeadLen)<<8)+(head->Flag);
    local_checksum = (local_checksum>>16)+local_checksum&0xffff;
    local_checksum = (local_checksum>>16)+local_checksum&0xffff;
    local_checksum = (~local_checksum)&0xffff;

    if (local_checksum != ntohs(head->CheckSum))
    {
        return -1;
    }

    //检查序列号
    int seqAdd = 1;
    if (current_TCB->state == FIN_WAIT2)
    {
        seqAdd = 0;
    }
    else if(len >20)
    {
        seqAdd = len - 20;
    }
    if(head->AckNo != (current_TCB->seq + seqAdd))
    {
        tcp_DiscardPkt(pBuffer,STUD_TCP_TEST_SEQNO_ERROR);
        return -1;
    }
    
    //状态转换
    switch(current_TCB->state)
    {
        case SYN_SENT:
            if(head->Flag == PACKET_TYPE_SYN_ACK)
            {
                current_tcb->state = ESTABLISHED;
                current_tcb->ack=  head->SeqNo+1;                          
                current_tcb->seq = head->AckNo;
                stud_tcp_output(NULL, 0, PACKET_TYPE_ACK, current_TCB->srcPort, current_TCB->dstPort, ntohl(srcAddr), ntohl(dstAddr));
                break;
            }
            else
                return -1;
        case ESTABLISHED:
            if(head->Flag == PACKET_TYPE_ACK)
            {
                if(len > 20)
                {
                    current_TCB->ack = head->SeqNo + len -20;
                    current_TCB->seq = head->AckNo; 
                    break;
                }
                else if(len == 20)
                {
                    current_TCB->ack = head->SeqNo + 1;
                    current_TCB->seq = head->AckNo; 
                    break;
                }
                else
                    return -1;
            }
            else
                return -1;
        case FIN_WAIT1: 
          if(head->Flag == PACKET_TYPE_ACK)
          {
            current_TCB->ack=  head->SeqNo+1;                          
            current_TCB->seq = head->AckNo;
            current_TCB->state = FIN_WAIT2; 
            break;
          }
          else 
            return -1;
        case FIN_WAIT2:
            if(head->Flag == PACKET_TYPE_FIN_ACK)
            {
                current_TCB->state = TIME_WAIT;
                stud_tcp_output(NULL, 0, PACKET_TYPE_ACK, current_TCB->srcPort, current_TCB->dstPort, ntohl(srcAddr), ntohl(dstAddr));
                break;
            }
            else
                return -1;

        default: 
            return -1;
    }

    return 0;
}

//TCP分组发送
void stud_tcp_output(char *pData, unsigned short len, unsigned char flag, unsigned short srcPort, unsigned short dstPort, unsigned int srcAddr, unsigned int dstAddr)
{
    if(current_TCB==NULL){    
        current_TCB = (TCB*)malloc(sizeof(TCB));
        current_TCB->seq = gSeqNum;
        current_TCB->ack = gAckNum;
        current_TCB->srcPort = srcPort;
        current_TCB->dstPort = dstPort;
        current_TCB->srcAddr = srcAddr;
        current_TCB->dstAddr = dstAddr;
        current_TCB->state = CLOSED;
    }
    tcp_head* head = (tcp_head*)malloc(sizeof(tcp_head));
    int i = 0 ;
    for(i = 0;i < len;i++)
    {
        head->data[i] = pData[i];
    }
    head->SrcPort = srcPort;
    head->DstPort = dstPort;
    head->SeqNo = current_TCB->seq;
    head->AckNo = current_TCB->ack;
    head->Headlen = 0x50;
    head->Flag = flag;
    head->WindowSize = 1;
    head->UrgentPointer = 0;

    switch(current_TCB->state)
    {
        case CLOSED:
            if(flag == PACKET_TYPE_SYN)
            {
                current_TCB->state = SYN_SENT;
            }
            else 
                return;
            break;

        case ESTABLISHED:
            if(flag == PACKET_TYPE_FIN_ACK)
            {
                current_TCB->state = FIN_WAIT1;
                break;
            }
            else if(flag == PACKET_TYPE_DATA || flag == PACKET_TYPE_ACK)
            {
                break;
            }
            else
                return;
            break;

        defalut:  
        return;
    }

    //计算校验和
    unsigned int local_checksum = 0;
    unsigned int local_srcAddr = ntohl(srcAddr);
    unsigned int local_dstAddr = ntohl(dstAddr);
    local_checksum += (local_srcAddr >> 16) + local_srcAddr&0xffff;
    local_checksum += (local_dstAddr >> 16) + local_dstAddr&0xffff;
    local_checksum += IPPROTO_TCP;
    local_checksum += 0x14;
    local_checksum += head->srcPort + head->dstPort;
    local_checksum += thead->WindowSize;
    local_checksum += head->UrgentPointer;
    local_checksum += ((head->SeqNo)>>16)+(head->SeqNo)&0xffff;
    local_checksum += ((head->AckNo)>>16)+(head->AckNo)&0xffff;
    local_checksum += ((head->HeadLen)<<8)+(head->Flag);
    if(head->flag == PACKET_TYPE_DATA)
    {
        local_checksum += len;
        int temp = len;
        char*p = pData;
        while(temp > 0)
        {
            local_checksum += (*p)<<8;
            p++;
            local_checksum += (*p);
            p++;
            temp = temp - 2;
        }
    }
    local_checksum = (local_checksum>>16)+local_checksum&0xffff;
    local_checksum = (local_checksum>>16)+local_checksum&0xffff;
    local_checksum = (~local_checksum)&0xffff;

    //发送
    head->CheckSum = nthos(local_checksum);
    head->SrcPort = ntohs(head->SrcPort);
    head->DstPort = ntohs(head->DstPort);
    head->SeqNo = ntohl(head->SeqNo);
    head->AckNo = ntohl(head->AckNo);
    head->WindowSize = nthos(head->WindowSize);
    head->UrgentPointer = nthos(head->UrgentPointer);
    tcp_sendIpPkt((unsigned char*)thead, 20+len, current_TCB->srcAddr, current_TCB->dstAddr, 60);
}

//Socket接口函数

//获得 socket描述符
int stud_tcp_socket(int domain, int type, int protocol)
{
    if(domain != AF_INET || type != SOCK_STREAM || protocol != IPPROTO_TCP)
        return -1;
    
    current_TCB = (TCB*)malloc(sizeof(TCB));
    if(TCB_table == NULL)
    {
        TCB_table = (TCB_node*)malloc(sizeof(TCB_node));
        TCB_table->current = current_TCB;
        TCB_table->next = NULL;
    }
    else
    {
        TCB_node *current = TCB_table;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = (TCB_node*)malloc(sizeof(TCB_node));
        current->next->current = current_TCB;
        current->next->next = NULL;
    }

    current_TCB->sockfd = SockNum++;
    current_TCB->srcPort = gSrcPort++;
    current_TCB->seq = gSeqNum++;
    current_TCB->ack = gAckNum;
    current_TCB->state = CLOSED;

    return current_TCB->sockfd;
    
}

//TCP 建立连接函数
int stud_tcp_connect(int sockfd, struct sockaddr_in* addr, int addrlen)
{   
    UINT32 srcAddr = getIpv4Address();
    UINT32 dstAddr = htonl(addr->sin_addr.s_addr);
    current_TCB->srcAddr = srcAddr;
    current_TCB->dstAddr = dstAddr;
    current_TCB->dstPort = ntohs(addr->sin_port);
    current_TCB->state = SYN_SENT;
    stud_tcp_output(NULL, 0, PACKET_TYPE_SYN, current_TCB->srcPort, current_TCB->dstPort, srcAddr, dstAddr);
    
    tcp_head* receive = (tcp_head*)malloc(sizeof(tcp_head));
    int i = -1;
    while(i == -1)
        i = waitIpPacket((char*)receive, 5000);
    
    stud_tcp_input((char *)receive, 20, ntohl(current_TCB->srcAddr), ntohl(current_TCB->dstAddr));
    return 0;
}

//TCP 报文发送函数
int stud_tcp_send(int sockfd, const unsigned char* pData, unsigned short datalen, int flags)
{
    if(current_TCB->state != ESTABLISHED)
        return -1;

    UINT32 srcAddr = getIpv4Address();
    UINT32 dstAddr = current_TCB->dstAddr;
    current_TCB->data = (char*)malloc(sizeof(char) * datalen);
    strcpy((char*)current_TCB->data,(char*)pData); 
    stud_tcp_output((char *)current_TCB->data, datalen, PACKET_TYPE_DATA, current_TCB->srcPort, current_TCB->dstPort, srcAddr, dstAddr);
    
    tcp_head* receive = (tcp_head*)malloc(sizeof(tcp_head));
    int i = -1;
    while(i == -1)
        i = waitIpPacket((char*)receive, 5000);

    stud_tcp_input((char *)receive, datalen+20, ntohl(current_TCB->srcAddr), ntohl(current_TCB->dstAddr));
    return 0;
}

//TCP 报文接收函数
int stud_tcp_recv(int sockfd, const unsigned char* pData, unsigned short datalen, int flags)
{
    if(current_TCB->state != ESTABLISHED)
        return -1;
    UINT32 srcAddr = getIpv4Address();
    UINT32 dstAddr = current_TCB->dstAddr;

    tcp_head* receive = (tcp_head*)malloc(sizeof(tcp_head));
    int i = -1;
    while(i == -1)
        i = waitIpPacket((char*)receive, 5000);

    strcpy((char*)pData,(char*)receive->data);
    datalen=sizeof(pData);
    stud_tcp_input((char *)receive, datalen+20, ntohl(current_TCB->srcAddr), ntohl(current_TCB->dstAddr));
    return 0;
}

//TCP 关闭连接函数
int stud_tcp_close( int sockfd )
{
    TCB_node *current_p = TCB_table;
    TCB_node *pre_current = current_p;

    while(current_p != NULL && current_p->current != NULL)
    {
        if(current_p->current->sockfd == sockfd)
        {
            current_TCB = current_p->current;
            break;
        }
        pre_current = current_p;
        current_p = current_p->next;
    }
    if(current_p == NULL)
        return -1;

    UINT32 srcAddr = getIpv4Address();
    UINT32 dstAddr = current_TCB->dstAddr;
    if(current_tcb->state != ESTABLISHED)
    {
        if(current_p!=pre_current)        
        {
             pre_current->next=current_p->next;
             free(current_p);
        }
        else
             free(current_TCB);

        current_TCB=NULL;
        return -1;
    }

    stud_tcp_output(NULL, 0, PACKET_TYPE_FIN, current_TCB->srcPort, current_TCB->dstPort, srcAddr, dstAddr);
    current_TCB->state = FIN_WAIT1;

    tcp_head* receive = (tcp_head*)malloc(sizeof(tcp_head));
    int i = -1;
    while(i == -1)
        i = waitIpPacket((char*)receive, 5000);
    //ACK
    stud_tcp_input((char *)receive, 20,ntohl(current_TCB->srcAddr), ntohl(current_TCB->dstAddr));

    int i = -1;
    while(i == -1)
        i = waitIpPacket((char*)receive, 5000);
    //FIN/ACK
    stud_tcp_input((char *)receive, 20, ntohl(current_TCB->srcAddr), ntohl(current_TCB->dstAddr));
    return 0;
}