// DB_Detail.cpp: implementation of the DB_Detail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "DB_Detail.h"
#include "Global.h"

#include "ap2d_objs.h"
#include "encode.h"
#include "getrace.h"
#include <set>



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void Ap_Layer::set_from_str_sub(char *name)
{
	char s[TEXT_LEN] = {0};
	sprintf(s,"%s.layer_name_",name);	
	layer_name_ = rei_get(s);

	sprintf(s,"%s.lua_path_name_",name);	
	lua_path_name_ = rei_get(s);

	sprintf(s,"%s.lua_file_name_",name);	
	lua_file_name_ = rei_get(s);


	sprintf(s,"%s.hash_val_",name);	
	hash_val_ = rei_get(s);
	CString ss = hash_val_.c_str();
	int len = ss.GetLength();
	if(len != 32)
		hash_val_ = ss.Left(32);

}
void Ap_Layer::get_str_sub(char *name)
{
	char s[TEXT_LEN] = {0};
	sprintf(s,"%s.layer_name_",name);	
	rei_add_str(NULL,s,layer_name_.c_str());

	sprintf(s,"%s.lua_path_name_",name);	
	rei_add_str(NULL,s,lua_path_name_.c_str());

	sprintf(s,"%s.lua_file_name_",name);	
	rei_add_str(NULL,s,lua_file_name_.c_str());
	
	sprintf(s,"%s.hash_val_",name);	
	rei_add_str(NULL,s,hash_val_.c_str());

}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void Detail::get_str(char *out)
{
	rei_quit();
	rei_add_str(NULL,"name_",name_.c_str());
	rei_add_str(NULL,"hash_val_",hash_val_.c_str());


	int count = ap_layers_.size();
	rei_add_int(NULL,"hashs_num",count);
	char field_name[MAX_REDIS_STR]={0};
	for (int i = 0; i < count; i++){
			sprintf(field_name,"hashs%d",i);
			ap_layers_[i].get_str_sub(field_name);
	}
	rei_get_encode(out);
}

void Detail::set_from_str(char *in)
{
	rei_init(in);

	name_ = rei_get("name_");
	hash_val_ = rei_get("hash_val_");

	int count  = atoi(rei_get("hashs_num"));
	char field_name[MAX_REDIS_STR]={0};
	Ap_Layer hash;
	for (int i = 0; i < count; i++){
		sprintf(field_name,"hashs%d",i);
		hash.set_from_str_sub(field_name);
		ap_layers_.push_back(hash);
	}
	rei_quit();

	
	
}
bool Detail::get_ap_layer(std::string layer_name,Ap_Layer &ap_layer)
{
	for(int i=0;i<ap_layers_.size();i++){
		if(strcmp(ap_layers_[i].layer_name_.c_str(),layer_name.c_str()) == 0){
			ap_layer = ap_layers_[i];
			return true;
		}
	}
	return false;
}
void Detail::edit_show(std::string layer_name,BOOL show)
{
	for(int i=0;i<ap_layers_.size();i++){
		if(strcmp(ap_layers_[i].layer_name_.c_str(),layer_name.c_str()) == 0){
			ap_layers_[i].show_ = show;
			return;
		}
	}
}
void Detail::edit_lock(std::string layer_name,BOOL lock)
{
	for(int i=0;i<ap_layers_.size();i++){
		if(strcmp(ap_layers_[i].layer_name_.c_str(),layer_name.c_str()) == 0){
			ap_layers_[i].lock_ = lock;
			return ;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Detail::DB_Detail()
{
	apdim_show_ = FALSE;
	apdim_lock_ = FALSE;
}

DB_Detail::~DB_Detail()
{

}
static std::string get_hash_val(Detail &detail,std::string layer_name)
{
	for(int i=0;i<detail.ap_layers_.size();i++){
		if(strcmp(detail.ap_layers_[i].layer_name_.c_str(), layer_name.c_str())==0)
			return detail.ap_layers_[i].hash_val_;
	}
	return "";
}
bool DB_Detail::is_change(Detail &detail)
{
	Details::iterator iter = find(detail.name_);
	if(iter == items_.end())
		return false;
	for(int i=0;i<detail.ap_layers_.size();i++){
		std::string layer_name = detail.ap_layers_[i].layer_name_;
		std::string old_hash_val = get_hash_val(*iter,layer_name);
		if(strcmp(detail.ap_layers_[i].hash_val_.c_str() ,old_hash_val.c_str()) == 0)
			continue;
		else{
			iter->change_layer_.push_back(layer_name);
			//return false;
		}
	}
	if(iter->change_layer_.size()>0)
		return false;
	else
		return true;
}

void DB_Detail::upload(std::string key)
{
	del_all(const_cast<char*>(key.c_str()),Global::instance()->ap2d());

	for(int i=0;i<items_.size();i++){
		char val[MAX_REDIS]={0};
		items_[i].get_str(val);		
		int id = new_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d());
  	update_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d(),id,val);
		
	}
}
void DB_Detail::create_item(char *in)
{
	Detail item;
	item.set_from_str(in);
	if(strcmp(item.name_.c_str(),"")!=0 )
		items_.push_back(item);

}

void DB_Detail::download(std::string key)
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
		}	//
	}

}
bool DB_Detail::is_have(std::string key)
{
	if(get_key_count(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d())<1)
		return false;
	return true;
}
std::string DB_Detail::change_info(std::string name)
{
	
	std::string str,info;
	Detail item;
	get(name,item);
	char val[MAX_REDIS]={0};
	CString s;
	std::set<std::string> ns;
	for(int i=0;i<item.change_layer_.size();i++){
		s = item.change_layer_[i].c_str() ;
		s = s.Left(s.Find("_"));
		ns.insert(s.GetBuffer(0));

	}
	int j = ns.size();
	std::set<std::string>::const_iterator it;
	for(it = ns.begin(); it != ns.end(); it++){
		str = *it+",";
		strcat(val,str.c_str());
	}
	strcat(val , " are changed!");
	return val;
}
static void get_hashs_prefex(std::string layer_name,Ap_Layers &hashs,Ap_Layers &hs)
{
	for(int i=0;i<hashs.size();i++){
		CString s = hashs[i].layer_name_.c_str();
		if(s.Find(layer_name.c_str()) != -1)
			hs.push_back(hashs[i]);
	}
}
static std::string get_hash_val(const Ap_Layers &new_hs,std::string layer_name)
{
	int size = new_hs.size();
	for(int i=0;i<new_hs.size();i++){
		std::string new_val = new_hs[i].layer_name_.c_str();
		if(strcmp(new_hs[i].layer_name_.c_str(),layer_name.c_str()) == 0)
			return new_hs[i].hash_val_;
	}
	return "";
}
static bool equ_val(const Ap_Layers &hashs,const Ap_Layers &new_hs)
{
	for(int i=0;i<hashs.size();i++){
		std::string new_val = get_hash_val(new_hs,hashs[i].layer_name_);
		std::string val = hashs[i].hash_val_.c_str();
		if(strcmp(val.c_str(),new_val.c_str()) == 0)
			continue;
		else
			return false;
	}
	return true;
}
bool DB_Detail::judge_hash(std::string detail_name,std::string layer_name,Ap_Layers &hashs)
{
	Details::iterator iter = find(detail_name);
	if(iter == items_.end())
		return false;
	Ap_Layers new_hs;
	get_hashs_prefex(layer_name,hashs,new_hs);

	if(equ_val(iter->ap_layers_,new_hs))
		return true;
/*
	for(int i=0;i<iter->ap_layers_.size();i++){
		std::string	s= iter->ap_layers_[i].layer_name_;
		if(strcmp(layer_name.c_str(),iter->ap_layers_[i].layer_name_.c_str()) != 0)
			continue;
		if(strcmp(iter->ap_layers_[i].hash_val_.c_str(),hash.hash_val_.c_str()) != 0)
			return true;
		else
			return false;
	}
*/
	return false;
}

std::string DB_Detail::get_layer_hash_val(std::string detail_name,std::string layer_name)
{
	Details::iterator iter = find(detail_name);
	if(iter == items_.end()){
		TRACE_OUT("the %s hash val is't created.",detail_name.c_str());
		return "";
	}

	for(int i=0;i<iter->ap_layers_.size();i++){
		if(strcmp(iter->ap_layers_[i].layer_name_.c_str(),layer_name.c_str()) == 0){
			return iter->ap_layers_[i].hash_val_;
		}
	}
	return "";
}

void DB_Detail::get_layers(std::string detail_name,strings &layer_file_names)
{
	Details::iterator iter = find(detail_name);
	if(iter == items_.end())
		return ;
	for(int i=0;i<iter->ap_layers_.size();i++){
		layer_file_names.push_back(iter->ap_layers_[i].lua_file_name_);
	}

	//加入用户标注层
	layer_file_names.push_back(Global::instance()->get_apdim_lua_name(detail_name));


}
void DB_Detail::get_layers_name(std::string detail_name,strings &layer_file_names)
{
	Details::iterator iter = find(detail_name);
	if(iter == items_.end())
		return ;
	for(int i=0;i<iter->ap_layers_.size();i++){
		layer_file_names.push_back(iter->ap_layers_[i].layer_name_);
	}

	//加入用户标注层
	layer_file_names.push_back(LAYER_AP_DIM);


}

void DB_Detail::show(std::string detail_name,CComboBox & combo)
{
	Details::iterator iter = find(detail_name);
	if(iter == items_.end())
		return ;
	for(int i=0;i<iter->ap_layers_.size();i++){
		combo.AddString(iter->ap_layers_[i].layer_name_.c_str());
	}
	combo.AddString(LAYER_AP_DIM);

}

BOOL DB_Detail::get_show(std::string detail_name,std::string layer_name)
{
	if(strcmp(layer_name.c_str(),LAYER_AP_DIM) == 0){
		return apdim_show_;
	}
	Details::iterator iter = find(detail_name);	 
	if(iter == items_.end())
		return FALSE;

	Ap_Layer ap_layer;
	bool have = iter->get_ap_layer(layer_name,ap_layer);
	if(have)
		return ap_layer.show_;
	else
		return FALSE;
}
BOOL DB_Detail::get_lock(std::string detail_name,std::string layer_name)
{
	if(strcmp(layer_name.c_str(),LAYER_AP_DIM) == 0){
		return apdim_lock_;
	}
	Details::iterator iter = find(detail_name);	 
	if(iter == items_.end())
		return FALSE;
	Ap_Layer ap_layer;
	bool have = iter->get_ap_layer(layer_name,ap_layer);
	if(have)
		return ap_layer.lock_;
	else
		return FALSE;
}
void DB_Detail::edit_show(std::string detail_name,std::string layer_name,BOOL show)
{
	if(strcmp(layer_name.c_str(),LAYER_AP_DIM) == 0){
		apdim_show_ = show;
	}
	Details::iterator iter = find(detail_name);	 
	if(iter == items_.end())
		return ;
	iter->edit_show(layer_name,show);
}
void DB_Detail::edit_lock(std::string detail_name,std::string layer_name,BOOL lock)
{
	if(strcmp(layer_name.c_str(),LAYER_AP_DIM) == 0){
		apdim_lock_ = lock;
	}
	Details::iterator iter = find(detail_name);	 
	if(iter == items_.end())
		return ;
	iter->edit_lock(layer_name,lock);

}
