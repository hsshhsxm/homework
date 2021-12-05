#include "sysInclude.h"
#include <netinet/in.h>

//系统提供的接口函数
extern void fwd_LocalRcv(char *pBuffer, int length);//接收流程的上层接口函数，调用本函数将正确分组提交上层
extern void fwd_SendtoLower(char *pBuffer, int length, unsigned int nexthop);//发送流程的下层接口函数
extern void fwd_DiscardPkt(char *pBuffer, int type);//丢弃错误分组的函数
extern unsigned int getIpv4Address();//获取本机IPv4地址

//路由表结构
typedef struct stud_route_msg
{
	unsigned int dest;//目的地址IP
	unsigned int masklen;//掩码长度
	unsigned int nexthop;//下一跳地址
}stud_route_msg;
//建立路由表
static stud_route_msg route_table[100];
static int table_size = 0;
//路由表初始化
void stud_Route_Init(){}
//路由的增加
void stud_route_add(stud_route_msg *proute) 
{
	table_size++;
	route_table[table_size].dest = ntohl(proute ->dest);
	route_table[table_size].masklen = ntohl(proute ->masklen);
	route_table[table_size].nexthop = ntohl(proute ->nexthop);
}
//查找路由表,确定下一步处理流程(丢弃/处理/转发)
int stud_fwd_deal(char *pBuffer, int length)
{
	//获取目的地址，ttl,校验和
	unsigned int dest_address = ntohl(((unsigned int *)pBuffer)[4]);
	unsigned int ttl = pBuffer[8];
	//检验TTL，如果为0则丢弃
	if(ttl == 0)
	{
		fwd_DiscardPkt(pBuffer,STUD_FORWARD_TEST_TTLERROR);
		return 1;
	}
	//如果目的地址是本机，接收
	if(dest_address == getIpv4Address())
	{
		fwd_LocalRcv(pBuffer,length);
		return 0;
	}
	//如果目的地址不是本机
	unsigned int max_masklen = 0;//掩码长度最大值
	unsigned int nexthop;//下一跳
	//按照最长匹配查找路由表获取下一跳
	for(int i = 0;i < table_size;i++)
	{
		unsigned int masklen = ntohl(route_table[i].masklen);
		if (ntohl(route_table[i].dest) == dest_address && masklen > max_masklen)
		{
			max_masklen = masklen; 
			nexthop = route_table[i].nexthop;
		}
	}
	//查找失败
	if(max_masklen == 0)
	{
		fwd_DiscardPkt(pBuffer,STUD_FORWARD_TEST_NOROUTE);
		return 1;
	}
	//查找成功，设置ttl
	pBuffer[8] = ttl - 1;
	//计算校验和
	((unsigned short *)pBuffer)[5] = 0;
	unsigned int sum = 0;
	for (int i = 0; i < 10; i++)
	{
        sum += ntohs(pBuffer[i]); 
        sum = (sum >> 16) + (sum & 0xffff);
    }
	((unsigned short *)pBuffer)[5] = htons((~(unsigned short)sum));
	//发送
	fwd_SendtoLower(pBuffer,length,nexthop);
	return 0;
}