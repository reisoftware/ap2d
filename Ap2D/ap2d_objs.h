// ap2d_objs.h: interface for the ap2d_objs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AP2D_OBJS_H__0027DCCF_508F_4D0A_9ACE_F95CCD870687__INCLUDED_)
#define AFX_AP2D_OBJS_H__0027DCCF_508F_4D0A_9ACE_F95CCD870687__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "net.h"

typedef struct _AP2d_{
	char server[64];
	int port;
	int index;
	char sign[10];//ÉèÖÃap2dÇ°×º
	REDIS redis;
}AP2D;


/////////////////////////////////////////////////////
int init_ap2d_server(AP2D* ap);
int close_ap2d(AP2D* ap);
/////////////////////////////////////////////////////
int add_hkey(AP2D* ap,const char *key);
int del_under_key(AP2D* ap,char *key);
int del_key(AP2D* ap,char *key,int start_id,int end_id);

//company///////////////////////////////////////////////////
int new_company(AP2D* ap);
int get_company_count(AP2D* ap);
int get_company(AP2D* ap,int index,char* out);
int del_company(AP2D* ap,int index);
int update_company(AP2D* ap,int index,char* str);

///project//////////////////////////////////////////////////
int new_project(char *company,AP2D* ap);
int get_project_count(char *company,AP2D* ap);
int get_project(char *company,AP2D* ap,int index,char* out);
int del_project(char *company,AP2D* ap,int index);
int update_project(char *company,AP2D* ap,int index,char* str);
///key//////////////////////////////////////////////////
int new_key(char *v,AP2D* ap);
int get_key_count(char *v,AP2D* ap);
int get_key(char *v,AP2D* ap,int index,char* out);
int del_key(char *v,AP2D* ap,int index);
int update_key(char *v,AP2D* ap,int index,char* str);

void del(char *v,AP2D* ap);
void del_key_one(char *v,AP2D* ap);
void del_all(char *v,AP2D* ap);

int new_key(char *key,char *v,AP2D* ap);
int get_key_count(char *key,char *v,AP2D* ap);
int get_key(char *key,char *v,AP2D* ap,int index,char* out);
int del_key(char *key,char *v,AP2D* ap,int index);
int update_key(char *key,char *v,AP2D* ap,int index,char* str);



#endif // !defined(AFX_AP2D_OBJS_H__0027DCCF_508F_4D0A_9ACE_F95CCD870687__INCLUDED_)
