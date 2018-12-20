#ifndef _ENCODE_H
#define _ENCODE_H
#include "net.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _rei_type
{
  char *name;
  char *value;
} rei_type;

NET_API void rei_init(char* input);
NET_API void rei_quit(void);
NET_API char *rei_get(const char *field_name);
NET_API char* prefix_get(const char* prefix,const char* field_name);
NET_API int rei_add(const char *field_name,const char* value);
NET_API int rei_add_int(const char* prefix,const char* field_name,int value);
NET_API int rei_add_str(const char* prefix,const char* field_name,const char* value);
NET_API int rei_add_float(const char* prefix,const char* field_name,double value);
NET_API int rei_add_bool(const char* prefix,const char* field_name,bool value);
NET_API int rei_get_num(void);
NET_API int rei_get_encode(char* out);
#ifdef __cplusplus
}
#endif
#endif
