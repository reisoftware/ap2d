// Mgr_Dxfs.cpp: implementation of the Mgr_Dxfs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Dxfs.h"

#include "Dxf_Read.h"
#include "DB_View.h"

#include "md5.h"
#include "Detail_Mgr.h"
#include "Mgr_Database.h"
#include "ap2d_objs.h"
#include "DB_Detail.h"
#include "Global.h"
#include "getrace.h"
#include "Left_Mgr.h"
#include "mgr_file.h"
#include "Mgr_Lua.h"


#define ENTITY_SIZE 300

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Dxfs::Mgr_Dxfs()
{

}

Mgr_Dxfs::~Mgr_Dxfs()
{

}
std::string get_hash_value(char *str)
{
	STRING md = append_padding_bits(str);
	UINT8 r[16] = {0};
	TCHAR buf[10] = {0};
	std::string hash;
	cal_hash_val(md,r);
	for (int i = 0; i < 16; i++ ){
		sprintf(buf, "%02x", r[i] );
		hash += buf;
	}	

	return hash;
}

static void part_ents(Entitys &all,std::vector<Entitys> &parts,int ent_num)
{
	int id=0;
	Entitys ents;

	for(int i=0;i<all.size();i++){
		if(id == ent_num){
			id = 0;
			parts.push_back(ents);
			ents.clear();
		}
		ents.push_back(all[i]);
		id++;
  }
	if(id != 0)
		parts.push_back(ents);
}
static void cal_hashs(std::string layer_name,std::vector<Entitys> &entss,Ap_Layers &hashs)
{
	CString s;
	Ap_Layer hash;
	for(int i=0;i<entss.size();i++){
		char out[MAX_REDIS] = {0};
		get_str_by_ents(entss[i],out);	

		//计算hash值
		s.Format("_%i",i);
		hash.layer_name_ = layer_name.c_str()+s;
		//计算键值，此处应该通过判断决定那些层是不用上传的，只要是键值相等的是不用传的，对于不等的，需要考虑那些需要覆盖
		hash.hash_val_ = get_hash_value(out);
		hashs.push_back(hash);

	}

}

static void upload_layer(std::string layer_name,std::string detail_name,std::vector<Entitys> &entss,Ap_Layers &hashs)
{
	//判读是否存在相同的hans值

	if(Global::instance()->db_detail().judge_hash(detail_name,layer_name,hashs))
		return;


	//同时上传该层图纸信息
	std::string detail_key = Global::instance()->get_detail_key(detail_name,layer_name);
	//删除已有的键值内容
	del_all(const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d());

	CString s;
	for(int i=0;i<entss.size();i++){
		char out[MAX_REDIS] = {0};
		get_str_by_ents(entss[i],out);	
		int id = new_key(const_cast<char*>(detail_key.c_str()),const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d());
  	update_key(const_cast<char*>(detail_key.c_str()),const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d(),id,out);
	}

}

static void get_hash_group(std::string layer_name,Ap_Layers &hashs,std::string detail_name)
{
	Entitys ents;
	get_layer_ent(DB_View::instance()->cur_view()->scene()->database(),layer_name,ents);
	int size = ents.size();


	std::vector<Entitys> entss;
	part_ents(ents,entss,ENTITY_SIZE);

	//此处应该分两步走，第一步计算hash值，第二步上传图纸。上传前判断hash是否相等，决定是否需要上传覆盖
//	cal_hashs(layer_name,entss,hashs);
//	upload_layer(layer_name,detail_name,entss,hashs);



	
	
		//同时上传该层图纸信息
		std::string detail_key = Global::instance()->get_detail_key(detail_name,layer_name);
		//删除已有的键值内容
		del_all(const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d());
		CString s;
		Ap_Layer hash;
		for(int i=0;i<entss.size();i++){
			char out[MAX_REDIS] = {0};
			get_str_by_ents(entss[i],out);	
	
			//计算hash值
			s.Format("_%i",i);
			hash.layer_name_ = layer_name.c_str()+s;
			//计算键值，此处应该通过判断决定那些层是不用上传的，只要是键值相等的是不用传的，对于不等的，需要考虑那些需要覆盖
			hash.hash_val_ = get_hash_value(out);
			hashs.push_back(hash);
			//保存图纸信息
			int id = new_key(const_cast<char*>(detail_key.c_str()),const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d());
	  	update_key(const_cast<char*>(detail_key.c_str()),const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d(),id,out);
	
		}	


}
static void get_hash(std::string layer_name,Ap_Layer &hash)
{
	Entitys ents;
	get_layer_ent(DB_View::instance()->cur_view()->scene()->database(),layer_name,ents);
	int size = ents.size();


//保存一个字符串，太多时会越界
	char out[MAX_REDIS] = {0};
	get_str_by_ents(ents,out);	
	hash.layer_name_ = layer_name;
	hash.hash_val_ = get_hash_value(out);
	CString s = out;

//	TRACE_OUT("layer_name = %s; ent_size = %d; ent_str_len = %d;\n",layer_name.c_str(),size,s.GetLength());
//	TRACE_OUT("hash_val = %s;\n",hash.hash_val_.c_str());




}
void Mgr_Dxfs::get_hash_val(std::string path,std::string file,Detail &detail)
{
	DB_View::instance()->cur_view()->scene()->database()->clear_entity();
	std::string file_name = path+file;
	Dxf_Read dxf_read;
	dxf_read.read(file_name,DB_View::instance()->cur_view()->scene());

	detail.name_ = file;

	//
	get_hash_group(LAYER_PART,detail.ap_layers_,file);
	get_hash_group(LAYER_SHEET,detail.ap_layers_,file);
	get_hash_group(LAYER_CUT,detail.ap_layers_,file);
	get_hash_group(LAYER_VIEW,detail.ap_layers_,file);
	get_hash_group(LAYER_MARK,detail.ap_layers_,file);
	get_hash_group(LAYER_DIM,detail.ap_layers_,file);
/*
	Ap_Layer hash;
	get_hash(LAYER_PART,hash);
	detail.hashs_.push_back(hash);
	get_hash(LAYER_SHEET,hash);
	detail.hashs_.push_back(hash);
	get_hash(LAYER_CUT,hash);
	detail.hashs_.push_back(hash);
	get_hash(LAYER_VIEW,hash);
	detail.hashs_.push_back(hash);
	get_hash(LAYER_MARK,hash);
	detail.hashs_.push_back(hash);
	get_hash(LAYER_DIM,hash);
	detail.hashs_.push_back(hash);
*/

}


static void get_hash_group_new(std::string layer_name,Ap_Layers &hashs,std::string detail_name)
{
	Entitys ents;
	get_layer_ent(DB_View::instance()->cur_view()->scene()->database(),layer_name,ents);
	int size = ents.size();

	std::vector<Entitys> entss;
	part_ents(ents,entss,ENTITY_SIZE);

	CString s;
	Ap_Layer hash;
	for(int i=0;i<entss.size();i++){
		char out[MAX_REDIS] = {0};
		get_str_by_ents(entss[i],out);	

		//计算hash值
		s.Format("_%i",i);
		hash.layer_name_ = layer_name.c_str()+s;
		//计算键值，此处应该通过判断决定那些层是不用上传的，只要是键值相等的是不用传的，对于不等的，需要考虑那些需要覆盖
		hash.hash_val_ = get_hash_value(out);
		hashs.push_back(hash);

	}	


}
void Mgr_Dxfs::get_hash_val_new(std::string path,std::string file,Detail &detail)
{
	DB_View::instance()->cur_view()->scene()->database()->clear_entity();
	std::string file_name = path+file;
	Dxf_Read dxf_read;
	dxf_read.read(file_name,DB_View::instance()->cur_view()->scene());

	detail.name_ = file;

	strings layers;
	get_layers(DB_View::instance()->cur_view()->scene()->database(),layers);
	for(int i=0;i<layers.size();i++){
		get_hash_group_new(layers[i],detail.ap_layers_,file);
	}

}
static void upload_dxf(std::string layer_name,std::string detail_name)
{
	Entitys ents;
	get_layer_ent(DB_View::instance()->cur_view()->scene()->database(),layer_name,ents);
	int size = ents.size();

	std::vector<Entitys> entss;
	part_ents(ents,entss,ENTITY_SIZE);

	std::string detail_key = Global::instance()->get_detail_key(detail_name,layer_name);
	//删除已有的键值内容
	del_all(const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d());
	CString s;
	for(int i=0;i<entss.size();i++){
		char out[MAX_REDIS] = {0};
		get_str_by_ents(entss[i],out);	

		int id = new_key(const_cast<char*>(detail_key.c_str()),const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d());
	  update_key(const_cast<char*>(detail_key.c_str()),const_cast<char*>(detail_key.c_str()),Global::instance()->ap2d(),id,out);

	}	


}
void Mgr_Dxfs::upload_dxf_by_layers(std::string path,std::string file)
{
	strings layers;
	get_layers(DB_View::instance()->cur_view()->scene()->database(),layers);
	for(int i=0;i<layers.size();i++){
		upload_dxf(layers[i],file);
	}
	//上传完图纸后，需要把对应的图层也一起上传，但需要考虑没有图层的实体的处理方法。
	//删除已有的键值内容
	std::string key = Global::instance()->get_detail_layers_key(file);
	del_all(const_cast<char*>(key.c_str()),Global::instance()->ap2d());
	Global::instance()->db_layer().upload(key);

}
void Mgr_Dxfs::download_dxf_by_layers(std::string file)
{
	Global::instance()->db_layer().download(Global::instance()->get_detail_layers_key(Global::instance()->get_cur_detail_name()));
	download_layers(Global::instance()->db_layer(),DB_View::instance()->cur_view()->scene()->database());

	download_layer(LAYER_AP_DIM,DB_View::instance()->cur_view()->scene()->database());
	
}
void load_dxf(std::string name,dlhml::Database *db)
{
	DB_View::instance()->cur_view()->scene()->database()->clear_entity();
	std::string file_name = Global::instance()->project_info().dir_path.c_str()+name;
	Dxf_Read dxf_read;
	dxf_read.read(file_name,DB_View::instance()->cur_view()->scene());

}



int get_dxf_status(std::string name)
{
	//先看看有没有时间记录，没有的话说明是新的，不用在进行hash值计算了
	if(!Global::instance()->db_file_date().find(name)){
		return STATUS_EDIT;

	}
	Mgr_Dxfs mgr_dxfs;
	Detail detail;
	//这是所有的存在的都是上传的，等下一步也做成变更的才上传
	mgr_dxfs.get_hash_val(Global::instance()->project_info().dir_path,name,detail);
	if(!Global::instance()->db_detail().is_have(Global::instance()->get_detail_db_key()))
		Global::instance()->db_detail().push(detail);
	if(Global::instance()->db_detail().is_change(detail)){
		
		return STATUS_EDIT;
	}else{
		return STATUS_CHANGE;
	}
	return STATUS_EDIT;
}

int get_dxf_status_lua(std::string name)
{
	Mgr_Dxfs mgr_dxfs;
	Detail detail;
	//这是所有的存在的都是上传的，等下一步也做成变更的才上传
	mgr_dxfs.get_hash_val(Global::instance()->project_info().dir_path,name,detail);
	if(!Global::instance()->db_detail().is_have(Global::instance()->get_detail_db_key()))
		Global::instance()->db_detail().push(detail);
	if(Global::instance()->db_detail().is_change(detail)){
		
		return STATUS_EDIT;
	}else{
		return STATUS_CHANGE;
	}
	return STATUS_EDIT;
}


void upload_new_dxfs(std::string dir_path,strings &files)
{
	TRACE_OUT("upload_new_dxfs start .\n");
	Global::instance()->db_detail().clear();
	Mgr_Dxfs mgr_dxfs;
	for(int i=0;i<files.size();i++){
		Detail detail;
		TRACE_OUT("\t Mgr_Dxfs::get_hash_val_new start .\n");
		mgr_dxfs.get_hash_val_new(dir_path,files[i],detail);
		TRACE_OUT("\t Mgr_Dxfs::get_hash_val_new end .\n");
		Global::instance()->db_detail().push(detail);
		TRACE_OUT("\t Mgr_Dxfs::upload_dxf_by_layers start .\n");
		mgr_dxfs.upload_dxf_by_layers(dir_path,files[i]);
		TRACE_OUT("\t Mgr_Dxfs::upload_dxf_by_layers end .\n");
	}
	TRACE_OUT("upload_new_dxfs end .\n");
	Global::instance()->db_detail().upload(Global::instance()->get_detail_db_key());
}

static void add_need_upload(strings &lua_files)
{
	ApFile file;
	for(int i=0;i<lua_files.size();i++){
		file.name_ = lua_files[i];
		Global::instance()->db_file().push(file);
	}

}
static void add_need_upload(std::string &lua_file)
{
	ApFile file;
	file.name_ = lua_file;
	Global::instance()->db_file().push(file);
}
void deal_dxf(std::string file_name)
{
	TRACE_OUT("deal_dxf start .\n");
	Detail detail;
	detail.name_ = file_name;
	std::string str = Global::instance()->project_info().dir_path+file_name;
	TRACE_OUT("\t get_file_hash start .\n");
	bool res = get_file_hash(str,detail.hash_val_);
	TRACE_OUT("\t get_file_hash end .\n");
	if(!res){
		TRACE_OUT("the %s can't cal the hase val .the file is error opening.\n",file_name.c_str());
		return ;
	}
	
	strings lua_files;
	TRACE_OUT("\t create_luas start .\n");
	create_luas(file_name,lua_files,detail);
	TRACE_OUT("\t create_luas end .\n");
	add_need_upload(lua_files);
	
	Global::instance()->db_detail().push(detail);
	TRACE_OUT("deal_dxf end .\n");

}

void deal_new_dxfs(std::string dir_path,strings &files)
{
	TRACE_OUT("upload_new_dxfs start .\n");
	Global::instance()->db_detail().clear();
	for(int i=0;i<files.size();i++){
		TRACE_OUT("ID = %d,%s is dealing.\n",i,files[i].c_str());

		deal_dxf(files[i]);
	}
	TRACE_OUT("upload_new_dxfs end .\n");
	Global::instance()->db_detail().upload(Global::instance()->get_detail_db_key());
	Global::instance()->db_file().upload_ser();
}

void create_detail(std::string file_name,Detail &detail)
{
	detail.name_ = file_name;
	std::string str = Global::instance()->project_info().dir_path+file_name;

	bool res = get_file_hash(str,detail.hash_val_);
	if(!res){
		TRACE_OUT("the %s can't cal the hase val .the file is error opening.\n",file_name.c_str());
		return ;
	}
	
	strings lua_files;
	create_luas(file_name,lua_files,detail);
	//此时不能上传，需要判断完后看看那些需要上传
//	add_need_upload(lua_files);

}
static bool check_layer_change(DB_Detail &db_detail,std::string detail_name,Ap_Layer &new_layer_hash)
{
	std::string hash_val = Global::instance()->db_detail().get_layer_hash_val(detail_name,new_layer_hash.layer_name_);
	std::string new_hash_val = new_layer_hash.hash_val_;
	if(strcmp(hash_val.c_str(),new_layer_hash.hash_val_.c_str()) == 0){
		return false;
	}else
		return true;
}


int get_dxf_status_by_file(std::string file_name)
{
	int status =STATUS_EDIT;
	Detail detail;
	create_detail(file_name,detail);

	for(int i=0;i<detail.ap_layers_.size();i++){
		if(check_layer_change(Global::instance()->db_detail(),detail.name_,detail.ap_layers_[i])){
			status = STATUS_CHANGE;
			add_need_upload(detail.ap_layers_[i].lua_path_name_);
		}
	}
	return status;
}



