// ap2d_objs.cpp: implementation of the ap2d_objs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "ap2d_objs.h"

#define TEXT_LEN_SUPER 500
#define TEXT_LEN 3000
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
int init_ap2d_server(AP2D* ap)
{
	ap->redis = get_redis(ap->server,ap->port);
	return 1;
}
int close_ap2d(AP2D* ap)
{
	free_redis(ap->redis);
	ap->redis = 0;
	return 1;
}




//base/////////////////////////////////////////////////////////////
int add_hkey(AP2D* ap,const char *key)
{
	return redis_hset(ap->redis,key,"company:id","0");

}
int del_under_key(AP2D* ap,char *key)
{
	char num[10] = {0};
	redis_hget(ap->redis,ap->sign,key,num);
	for(int i=0;i<atoi(num);i++){
		del_key(key,ap,i);
	}
	return 0;
}
int del_key(AP2D* ap,char *key,int start_id,int end_id)
{
	char obj_name[MAX_REDIS] = {0};
	for(int i=start_id;i<end_id;i++){
		sprintf(obj_name,"%s:%d",key,i);
		redis_hdel(ap->redis,ap->sign,obj_name);

	}
	return 1;
}
//实现公司////////////////////////////////////////////////////////////////

static int new_obj_company(AP2D* ap,const char* name)
{
	int result = -1;
	char val[3000] = {0};
	sprintf(val,"%s:id",name);
	result = redis_hincr(ap->redis,ap->sign,val,NULL);
	return result;
}
char ap2d_company[10] = "company";
int new_company(AP2D* ap)
{
	return new_obj_company(ap,ap2d_company);
}
static int get_obj_count_company(AP2D* ap,const char* name)
{
	int result = -1;

	char obj_name[TEXT_LEN] = {0};
	char count[TEXT_LEN] = {0};
	count[0] = '\0';
	sprintf(obj_name,"%s:id",name);
	redis_hget(ap->redis,ap->sign,obj_name,count);
	result = atoi(count);

	return result;
}

int get_company_count(AP2D* ap)
{
	return get_obj_count_company(ap,ap2d_company);
}
static get_obj_company(AP2D* ap,const char* name,int index,char* out)
{
	int result = -1;
	char obj_name[TEXT_LEN] = {0};
	sprintf(obj_name,"%s:%d",name,index);
	result = redis_hget(ap->redis,ap->sign,obj_name,out);
	return result;
}

int get_company(AP2D* ap,int index,char* out)
{
	return get_obj_company(ap,ap2d_company,index,out);
}
static int del_obj_company(AP2D* ap,int index,const char* name)
{
	int result = -1;
	char obj_name[TEXT_LEN] = {0};
	sprintf(obj_name,"%s:%d",name,index);
	result = redis_hdel(ap->redis,ap->sign,obj_name);
	return result;
}

int del_company(AP2D* ap,int index)
{
	return del_obj_company(ap,index,ap2d_company);
}
static int update_obj_company(AP2D* ap,int index,char* str,const char* name)
{
	int result = -1;
	int num = strlen(str);
	char val[TEXT_LEN] = {0};
	sprintf(val,"%s:%d",name,index);
	result = redis_hset(ap->redis,ap->sign,val,str);
	return result;
}
int update_company(AP2D* ap,int index,char* str)
{
	return update_obj_company(ap,index,str,ap2d_company);
}
//project//////////////////////////////////////////////////////////////////////////////////////
int new_project(char *company,AP2D* ap)
{
	return new_obj_company(ap,company);
}
int get_project_count(char *company,AP2D* ap)
{
	return get_obj_count_company(ap,company);
}
int get_project(char *company,AP2D* ap,int index,char* out)
{
	return get_obj_company(ap,company,index,out);
}
int del_project(char *company,AP2D* ap,int index)
{
	return del_obj_company(ap,index,company);
}
int update_project(char *company,AP2D* ap,int index,char* str)
{
	return update_obj_company(ap,index,str,company);
}
//key//////////////////////////////////////////////////////////////////////////////////////
int new_key(char *v,AP2D* ap)
{
	return new_obj_company(ap,v);
}
int get_key_count(char *v,AP2D* ap)
{
	return get_obj_count_company(ap,v);
}
int get_key(char *v,AP2D* ap,int index,char* out)
{
	return get_obj_company(ap,v,index,out);
}
int del_key(char *v,AP2D* ap,int index)
{
	return del_obj_company(ap,index,v);
}
int update_key(char *v,AP2D* ap,int index,char* str)
{
	return update_obj_company(ap,index,str,v);
}
void del(char *v,AP2D* ap)
{
	int num_old = get_key_count(v,ap);
	for(int i=0;i<num_old+1;i++)
		del_key(v,ap,i);

	std::string s = v;
  s +=":id";
	redis_hset(ap->redis,"ap2d",s.c_str(),"0");
	
}
void del_key_one(char *v,AP2D* ap)
{
	redis_hdel(ap->redis,"ap2d",v);
}
void del_all(char *v,AP2D* ap)
{
	redis_del(ap->redis,v);
}


int new_key(char *key,char *v,AP2D* ap)
{
	int result = -1;
	char val[TEXT_LEN] = {0};
	sprintf(val,"%s:id",v);
	result = redis_hincr(ap->redis,key,val,NULL);
	return result;
}
int get_key_count(char *key,char *v,AP2D* ap)
{
	int result = -1;
	char obj_name[TEXT_LEN] = {0};
	char count[TEXT_LEN] = {0};
	count[0] = '\0';
	sprintf(obj_name,"%s:id",v);
	redis_hget(ap->redis,key,obj_name,count);
	result = atoi(count);
	return result;
}
int get_key(char *key,char *v,AP2D* ap,int index,char* out)
{
	int result = -1;
	char obj_name[TEXT_LEN] = {0};
	sprintf(obj_name,"%s:%d",v,index);
	result = redis_hget(ap->redis,key,obj_name,out);
	return result;
}
int del_key(char *key,char *v,AP2D* ap,int index)
{
	int result = -1;
	char obj_name[TEXT_LEN] = {0};
	sprintf(obj_name,"%s:%d",v,index);
	result = redis_hdel(ap->redis,key,obj_name);
	return result;
}
int update_key(char *key,char *v,AP2D* ap,int index,char* str)
{
	int result = -1;
	int num = strlen(str);
	char val[TEXT_LEN] = {0};
	sprintf(val,"%s:%d",v,index);
	result = redis_hset(ap->redis,key,val,str);
	return result;
}

