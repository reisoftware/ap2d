#ifndef _AP_H_
#define _AP_H_
#include "net.h"
#ifdef __cplusplus
extern "C"{
#endif
typedef struct _AP_{
	char server[64];
	int port;
	int index;
	REDIS redis;
}AP;

NET_API int init_ap_server(AP* ap);
NET_API int close_ap(AP* ap);
NET_API int new_ap_model(AP* ap);

NET_API int new_plane(AP* ap);
NET_API int new_axis(AP* ap);
NET_API int new_node(AP* ap);
NET_API int new_jnt(AP* ap);
NET_API int new_mem(AP* ap);
NET_API int new_group(AP* ap);
NET_API int new_drawing(AP* ap);

NET_API int get_plane_count(AP* ap);
NET_API int get_axis_count(AP* ap);
NET_API int get_node_count(AP* ap);
NET_API int get_jnt_count(AP* ap);
NET_API int get_mem_count(AP* ap);
NET_API int get_group_count(AP* ap);
NET_API int get_drawing_count(AP* ap);

NET_API int get_plane(AP* ap,int index,char* out);
NET_API int get_axis(AP* ap,int index,char* out);
NET_API int get_node(AP* ap,int index,char* out);
NET_API int get_jnt(AP* ap,int index,char* out);
NET_API int get_mem(AP* ap,int index,char* out);
NET_API int get_group(AP* ap,int index,char* out);
NET_API int get_drawing(AP* ap,int index,char* out);

NET_API int del_plane(AP* ap,int index);
NET_API int del_axis(AP* ap,int index);
NET_API int del_node(AP* ap,int index);
NET_API int del_jnt(AP* ap,int index);
NET_API int del_mem(AP* ap,int index);
NET_API int del_group(AP* ap,int index);
NET_API int del_drawing(AP* ap,int index);

NET_API int update_plane(AP* ap,int index,char* str);
NET_API int update_axis(AP* ap,int index,char* str);
NET_API int update_node(AP* ap,int index,char* str);
NET_API int update_jnt(AP* ap,int index,char* str);
NET_API int update_mem(AP* ap,int index,char* str);
NET_API int update_group(AP* ap,int index,char* str);
NET_API int update_drawing(AP* ap,int index,char* str);
#ifdef __cplusplus
}
#endif
#endif