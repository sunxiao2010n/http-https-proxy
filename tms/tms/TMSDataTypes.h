#pragma once

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned U32;
typedef unsigned long long U64;
#include <stdio.h>
#include <stdarg.h>

#define RETRY_TIMES 5
#define _Pr(fmt, args...) printf(fmt"\n",  ##args)
#define _Info(fmt, args...) printf(fmt"\n",  ##args)


#ifdef __cplusplus
struct UserId
{
	U64 mobile;
	U64 app;
	UserId(U64 m, U64 a)
		: mobile(m)
		, app(a)
	{}
	bool operator<(const UserId u) const
	{
		return mobile < u.mobile
			? true
			: mobile == u.mobile && app < u.app
				? true
				: false;
	}
};

constexpr int Tcp_Ack_Len()
{
	return 32 + 20;
}

//�˹��㷽��
//���������
constexpr int TrafficEst(int x) {
#ifdef ACCURATE_TRAFFIC
	//	return x + Tcp_Ack_Len() * 2  /*���� + ack*/
	//		 + (x / 1400) * Tcp_Ack_Len()  /* �����Ƭ + �����Ƭ��ack(��Ϊ�����Ƭʹ��sack) */
		return x + Tcp_Ack_Len() * 2 
			 + (x / 1394) * Tcp_Ack_Len()
		;
	
#else
	return x;
#endif
}

//�˹��㷽��
//���������
//tcp handshakes' traffic
constexpr int Traffic_TCP_hss()
{
#ifdef ACCURATE_TRAFFIC
	return 5 * Tcp_Ack_Len() + 2 * 60 /*tcp option max add*/;
#else
	return 0;
#endif
}

//��ȷ���㷽��
static inline int TelecomTrafficPredict(int tcplen) {
	if (tcplen <= 0)
		return tcplen + Tcp_Ack_Len();
	else
		return tcplen + Tcp_Ack_Len() + (tcplen-1)/1388 * Tcp_Ack_Len() ;
}

#endif // __cplusplus