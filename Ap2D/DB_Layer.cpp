// DB_Layer.cpp: implementation of the DB_Layer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "DB_Layer.h"

#include "DB_View.h"
#include "Database.h"
#include "layer.h"
#include "Mgr_Database.h"

#include "ap2d_objs.h"
#include "Global.h"

#include "encode.h"
#include "Mgr_Detail.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void ApLayer::set_from_str(char *in)
{
	rei_init(in);

	CString s = rei_get("name_");
	int len = s.GetLength();
	s.Delete(len-2,2);
	//UGLY  此处对应日文版肯定会有问题，严格测试
	CString ss = "||";

	name_ = s.GetBuffer(0);
//	show_ = atoi(rei_get("show_"));
//	lock_ = atoi(rei_get("lock_"));

	rei_quit();

}
void ApLayer::get_str(char *out)
{
	rei_quit();
	rei_add_str(NULL,"name_",name_.c_str());

	rei_get_encode(out);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Layer::DB_Layer()
{

}

DB_Layer::~DB_Layer()
{

}
void DB_Layer::show(CComboBox & combo)
{
/*
	items_.clear();
	combo.Clear();
	strings layers;
	get_layers(DB_View::instance()->cur_view()->scene()->database(),layers);
	ApLayer ap_layer;
	for(int i=0;i<layers.size();i++){
		combo.InsertString(0,layers[i].c_str());	
		ap_layer.name_ =  layers[i];
		items_.push_back(ap_layer);
	}
*/
	combo.Clear();
	for(int i=0;i<items_.size();i++){
		combo.InsertString(0,items_[i].name_.c_str());	
	}
}

BOOL DB_Layer::get_show(std::string name)
{
	ApLayers::iterator iter = find(name);
	 
	if(iter == items_.end())
		return FALSE;

	return iter->show_;
}
BOOL DB_Layer::get_lock(std::string name)
{
	ApLayers::iterator iter = find(name);
	 
	if(iter == items_.end())
		return FALSE;
	return iter->lock_;
}

void DB_Layer::create(dlhml::Database *db)
{
	items_.clear();
	strings layers;
	get_layers(db,layers);
	ApLayer ap_layer;
	for(int i=0;i<layers.size();i++){
		ap_layer.name_ =  layers[i];
		items_.push_back(ap_layer);
	}

}
void DB_Layer::upload(std::string key)
{
	create(DB_View::instance()->database());
	
	del_all(const_cast<char*>(key.c_str()),Global::instance()->ap2d());

	for(int i=0;i<items_.size();i++){
		char val[MAX_REDIS]={0};
		items_[i].get_str(val);		
		int id = new_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d());
  	update_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d(),id,val);
		
	}

}
void DB_Layer::create_item(char *in)
{
	ApLayer item;
	item.set_from_str(in);
	if(strcmp(item.name_.c_str(),"")!=0 )
		items_.push_back(item);

}

void DB_Layer::download(std::string key)
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
void DB_Layer::download_layers(dlhml::Database *db)
{
	std::string key_detail;
	for(int i=0;i<items_.size();i++){
		key_detail = Global::instance()->get_detail_key(Global::instance()->get_cur_detail_name(),items_[i].name_);
		detail::download(key_detail);

	}
}