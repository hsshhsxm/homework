#include "sysinclude.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>

//系统提供的接口函数
extern void ip_DiscardPkt(char *pBuffer, int type);//丢弃分组
extern void ip_SendtoLower(char *pBuffer, int length);//发送分组
extern void ip_SendtoUp(char *pBuffer, int length);//上层接收
extern unsigned int getIpv4Address();//获取本机的IPv4地址

//自己实现的接口
int stud_ip_recv(char *pBuffer, unsigned short length)//接收接口
{
    //获取ip首部信息并检查
    //检验版本号
    unsigned int version = pBuffer[0] >> 4;
    if(version != 4)
    {
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_VERSION_ERROR);
        return 1;
    }
    //检验头部长度
    unsigned int ip_head_length = pBuffer[0] & 0x0f;
    if(ip_head_length < 5)
    {
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_HEADLEN_ERROR);
        return 1;
    }
    //检验生存时间
    unsigned int time_to_live = pBuffer[8];
    if(time_to_live == 0)
    {
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_TTL_ERROR);
        return 1;
    }
    //检验首部校验和
    unsigned int sum = 0;
    for (int i =0;i < ip_head_length;i++)
    {
        sum += ntohs(pBuffer[i]);
    }
    unsigned int check = (sum >> 16) + (sum & 0xffff);
    if ((~check) != 0) 
    {
		ip_DiscardPkt(pBuffer, STUD_IP_TEST_CHECKSUM_ERROR);
		return 1;
    }
    //检验目的地址
    unsigned int dst_address = ntohl(((unsigned int *)pBuffer)[4]);
    if (dst_address != getIpv4Address() && (dst_address &0xff) != 255)
    {
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_DESTINATION_ERROR);
		return 1;
    }

    //如果所有检测正常，提取得到上层协议类型，
    //调用 ip_SendtoUp( )接口函数，交给系统进行后续接收处理
    ip_SendtoUp(pBuffer, length);
	return 0;
}


int stud_ip_Upsend(char *pBuffer, unsigned short len, unsigned int srcAddr,
	unsigned int dstAddr, byte protocol, byte ttl) //发送接口
{
    //根据所传参数（如数据大小），来确定分配的存储空间的大小并申请分组的存储空间
    unsigned short total_length = len + 20; 
    char *send_buffer = (char*)malloc(sizeof(char)*(total_length));
    //按照IPv4协议标准填写IPv4分组头部各字段
    //版本号和头部长度,服务类型
    send_buffer[0] = 0x45;
    send_buffer[1] = 0x0;
    //总长度
    unsigned short n_length = htons(total_length);
    memcpy(send_buffer + 2, &n_length, sizeof(unsigned short));
    //生存时间,协议
    send_buffer[8] = ttl;
    send_buffer[9] = protocol;
    //源地址，目的地址
    unsigned int src_address = htonl(srcAddr);
    unsigned int dst_address = htonl(dstAddr);
    memcpy(send_buffer + 12, &src_address, sizeof(unsigned int));
    memcpy(send_buffer + 16, &dst_address, sizeof(unsigned int));
    //校验和
	unsigned int sum = 0;
	for (int i = 0; i < 10; ++i)
	{
        sum += ntohs(send_buffer[i]); 
        sum = (sum >> 16) + (sum & 0xffff);
    }
    unsigned short n_checksum = htons(~(unsigned short)sum);
	memcpy(send_buffer + 10, &n_checksum, sizeof(unsigned short int)); 
    //数据
	memcpy(send_buffer + 20, pBuffer, len); 
    //发送
    ip_SendtoLower(send_buffer,total_length);

    return 0;
}