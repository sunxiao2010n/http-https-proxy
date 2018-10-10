//==========================================================================
/**
 * @file        : redis_conn_pool.h
 *
 * @description : ֻ�ܵ��߳�ʹ�ã����߳�ʹ�÷��̰߳�ȫ
 *
 * $tag         :
 *
 * @author      : 
 */
 //==========================================================================

#ifndef __REDIS_CONN_POOL_H__
#define __REDIS_CONN_POOL_H__

#include <deque>
#include <stack>
#include "coroutine.h"
#include "redis_connect.h"
#include "redis_free_reply.h"
#include "redis_recy_conn.h"
#include "TRTypeDefine.h"

class RedisConnPool
{
public:
	RedisConnPool();
	virtual ~RedisConnPool();

	int           init(string& host_ip, __uint16 port, string& passwd
		, int timeout = 1, int pool_size = 10);

	//ֱ�ӵ���ִ��һ��redis��������ֶ�get_connection��push_back_connection
	redisReply*    exec_command(const char* format, ...);
	int            exec_command_int(long long& result, const char* format, ...);
	int            exec_command_string(string& result, const char* format, ...);
	int            exec_command_vec_string(vector<string>& result, const char* format, ...);
	int            exec_command_pipeline(vector<string>& result, int cmd_count, const char* format, ...);

	//�����ӳ�getһ�����ӣ�ʹ����ɺ�����ֶ�����push_back_connection�����Żس���
	RedisConnect*  get_connection();
	void           get_connection(RedisRecycConn& recyc_conn);
	void           push_back_connection(RedisConnect* rds_conn);
	size_t			get_chan_size();
	
	static RedisConnPool& Instance()
	{
		static RedisConnPool inst_;
		return inst_;
	}
protected:
	int            init_redis_pool();
	void			co_wait();
	void			co_ready();
protected:
	string                host_ip_;
	__uint16              port_;
	string                passwd_;
	int                   timeout_;         // �����������ӳ�ʱʱ������λ:��
	int                   pool_size_;       // ���ӳس�ʼʱ��������
	std::stack<RedisConnect*> redis_conn_stack_;
	co_chan<int>*		  ready_chan_;
};

#endif /*__REDIS_CONN_POOL_H__*/
