//==========================================================================
/**
 * @file        : redis_free_reply.h
 *
 * @description : redis����ص�reply��������reply����delete��й©
 *
 * $tag         :
 *
 * @author      : 
 */
//==========================================================================

#ifndef __REDIS_FREE_REPLY_H__
#define __REDIS_FREE_REPLY_H__

extern "C"
{
#include "hiredis.h"
}
#include "redis_connect.h"

class RedisConnPool;

class RedisFreeReply
{
public:
    RedisFreeReply(redisReply* areply);
    RedisFreeReply& operator = (redisReply* reply) = delete;
    RedisFreeReply& operator = (RedisFreeReply& free_reply) = delete;
    void operator()(const RedisFreeReply&) = delete;
    ~RedisFreeReply();

public:
    redisReply* reply_;
};

#endif /*__REDIS_FREE_REPLY_H__*/