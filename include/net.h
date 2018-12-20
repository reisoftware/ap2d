#ifndef _NET_H_
#define _NET_H_
#include <winsock2.h>
#ifdef NET_EXPORTS
#define NET_API __declspec(dllexport)
#else
#define NET_API 
#endif
#ifdef __cplusplus
extern "C" {
#endif
#define MAX_REDIS 409600
#define MAX_REDIS_STR 255
typedef struct _redis_type_* REDIS;
NET_API REDIS get_redis(const char* server,int portno);
NET_API void free_redis(REDIS redis);
NET_API int redis_ping(REDIS redis);
NET_API int redis_info(REDIS redis,char* buf);
NET_API int redis_set(REDIS redis,const char* key,const char* value);
NET_API int redis_get(REDIS redis,const char* key,char* value);
NET_API int redis_incr(REDIS redis,const char* key,char* error);
NET_API int redis_del(REDIS redis,const char* key);
NET_API int redis_hdel(REDIS redis,const char* key,const char* field);
NET_API int redis_hset(REDIS redis,const char* key,const char* field,const char* value);
NET_API int redis_hget(REDIS redis,const char* key,const char* field,char* value);
NET_API int redis_hkeys(REDIS redis,char* key);
NET_API int redis_hincr(REDIS redis,const char* key,const char* field,char* error);
NET_API int redis_subscribe(REDIS redis);
NET_API char* redis_getline(REDIS redis,char* out,int size);
NET_API int redis_keep_alive(REDIS redis);
NET_API int redis_hgetall(REDIS redis,const char* key);
NET_API int init_net();
NET_API void close_net();
#ifdef __cplusplus
}
#endif
#endif
