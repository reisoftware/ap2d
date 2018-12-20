// DB_Company.cpp: implementation of the DB_Company class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Ap2D.h"
#include "DB_Company.h"

#include "encode.h"
#include "ap2d_objs.h"
#include "Global.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define TEXT_LEN 3000

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void Project::set_from_str(char *in)
{
	rei_init(in);
	name_ = rei_get("name_");

	dir_path_ = rei_get("dir_path_");
	rei_quit();
	
}
void Project::get_str(char *out)
{
	rei_quit();

	rei_add_str(NULL,"name_",name_.c_str());

	rei_add_str(NULL,"dir_path_",dir_path_.c_str());
	
	rei_get_encode(out);

}
void Project::set_from_str_sub(char *name)
{
	char s[TEXT_LEN] = {0};
	sprintf(s,"%s.name_",name);	
	name_ = rei_get(s);

	sprintf(s,"%s.dir_path_",name);	
	dir_path_ = rei_get(s);

	sprintf(s,"%s.groups_num",name);	
	int count  = atoi(rei_get(s));
	std::string str;
	for (int i = 0; i < count; i++){
		char field_name[MAX_REDIS_STR]={0};
		sprintf(field_name,"item%d",i);
		str = rei_get(field_name);
		groups_.push_back(str);
	}
	
}
void Project::get_str_sub(char *name)
{
	char s[TEXT_LEN] = {0};
	sprintf(s,"%s.name_",name);	
	rei_add_str(NULL,s,name_.c_str());

	sprintf(s,"%s.dir_path_",name);	
	rei_add_str(NULL,s,dir_path_.c_str());

	int count = groups_.size();
	sprintf(s,"%s.groups_num",name);	
	rei_add_int(NULL,s,count);
	char field_name[MAX_REDIS_STR]={0};
	for (int i = 0; i < count; i++){
		sprintf(field_name,"item%d",i);
		rei_add_str(NULL,field_name,groups_[i].c_str());
	}
	
	

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void Company::set_from_str(char *in)
{
	rei_init(in);
	name_ = rei_get("name_");

	int count  = atoi(rei_get("items_num"));
	char field_name[MAX_REDIS_STR]={0};
	Project pro;
	for (int i = 0; i < count; i++){
		sprintf(field_name,"item%d",i);
		pro.set_from_str_sub(field_name);
		pros_.push_back(pro);
	}
	rei_quit();
	
}
void Company::get_str(char *out)
{
	rei_quit();

	rei_add_str(NULL,"name_",name_.c_str());
	int count = pros_.size();
	rei_add_int(NULL,"items_num",count);
	char field_name[MAX_REDIS_STR]={0};
	for (int i = 0; i < count; i++){
			sprintf(field_name,"item%d",i);
			pros_[i].get_str_sub(field_name);
	}
	
	rei_get_encode(out);

}//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Company::DB_Company()
{

}

DB_Company::~DB_Company()
{

}
void DB_Company::show_companys(ListCtrl_Sort	&list_ctrl)
{
	list_ctrl.DeleteAllItems();
	for(int i=0;i<items_.size();i++){
		list_ctrl.add_item(items_[i].name_.c_str());
	}
}
void DB_Company::show_projects(std::string company_name,ListCtrl_Sort	&list_ctrl)
{
	Companys::iterator iter = find(company_name);
	if(iter == items_.end())
		return;
	list_ctrl.DeleteAllItems();
	for(int i=0;i<(iter)->pros_.size();i++){
		std::string ss = (iter)->pros_[i].name_.c_str();
		list_ctrl.add_item((iter)->pros_[i].name_.c_str());
	}
}
void DB_Company::upload(std::string key)
{
	del_all(const_cast<char*>(key.c_str()),Global::instance()->ap2d());

	for(int i=0;i<items_.size();i++){
		if(strcmp(items_[i].name_.c_str(),"") == 0)
			continue;
		char val[MAX_REDIS]={0};
		items_[i].get_str(val);		
		int id = new_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d());
  	update_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d(),id,val);
		
	}
}
void DB_Company::create_item(char *in)
{
	Company item;
	item.set_from_str(in);
	if(strcmp(item.name_.c_str(),"") == 0)
		return;
	items_.push_back(item);

}

void DB_Company::download(std::string key)
{
	items_.clear();

	if(redis_hgetall(Global::instance()->ap2d()->redis,const_cast<char*>(key.c_str()))){ 
		char str[MAX_REDIS] = {0}; 
		char *rs = NULL; 
		rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
		std::string val = rs;
		rs = strchr(str,'*'); 
		if(!rs) 
			return ; 	
		int num = atoi(rs + 1); 	
		
		for(int i = 0; i < num / 2 ; ++i){ 
			str[0] = 0;
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			if(!rs) 
				return;
			std::string val = rs;
			create_item(const_cast<char*>(val.c_str()));
		}	
	}

}


void DB_Company::set_project_path(std::string company_name,std::string project_name,std::string dir_path)
{
	Companys::iterator iter = find(company_name);
	if(iter == items_.end()){
		return ;
	}
	for(int i=0;i<iter->pros_.size();i++){
		if(strcmp(iter->pros_[i].name_.c_str(),project_name.c_str()) == 0){
			iter->pros_[i].dir_path_ = dir_path;
			break;
		}
	}


}
std::string DB_Company::get_project_path(std::string company_name,std::string project_name)
{
	Companys::iterator iter = find(company_name);
	if(iter == items_.end()){
		return "E:\\1_project\\";
	}
	for(int i=0;i<iter->pros_.size();i++){
		if(strcmp(iter->pros_[i].name_.c_str(),project_name.c_str()) == 0){
			return iter->pros_[i].dir_path_;
		}
	}
	return "E:\\1_project\\";
}
void DB_Company::push_project(std::string company_name,Project &pro)
{
	Companys::iterator iter = find(company_name);
	if(iter == items_.end()){
		return ;
	}
	iter->pros_.push_back(pro);

}
void DB_Company::edit_project_name(std::string company_name,std::string project_name,std::string project_path)
{
	Companys::iterator iter = find(company_name);
	if(iter == items_.end()){
		return ;
	}
	for(int i=0;i<iter->pros_.size();i++){
		if(strcmp(iter->pros_[i].name_.c_str(),project_name.c_str()) == 0){
			iter->pros_[i].name_ = project_name;
			iter->pros_[i].dir_path_ = project_path;
		}
	}
}
void DB_Company::del_project_name(std::string company_name,std::string project_name)
{
	Companys::iterator iter = find(company_name);
	if(iter == items_.end()){
		return ;
	}
	//UGLY 没有删除成功
//	for(int i=0;i<iter->pros_.size();i++){
//		if(strcmp(iter->pros_[i].name_.c_str(),project_name.c_str()) == 0){
//			iter->pros_[i].name_ = project_name;
//		}
//	}

}
