// Mgr_Layers.cpp: implementation of the Mgr_Layers class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Layers.h"
#include "Database.h"
#include "Mgr_Dxfs.h"
#include "Mgr_Database.h"
#include "Global.h"
#include "Mgr_Detail.h"
#include "DB_View.h"
#include "Mgr_Lua.h"
#include "Mgr_File.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Layer_Info::Layer_Info()
{
	cur_part_ = true;
	cur_sheet_ = true;
	cur_cut_ = true;
	cur_view_ = true;
	
	cur_mark_ = false;
	cur_dim_ = false;

	ser_part_ = false;
	ser_sheet_ = false;
	ser_cut_ = false;
	ser_view_ = false;
	ser_mark_ = true;
	ser_dim_ = true;
	ser_ap_dim_ = true;

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Layers::Mgr_Layers()
{

}

Mgr_Layers::~Mgr_Layers()
{

}
static void get_layers_cur(const Layer_Info &info,strings &layers)
{
	if(info.cur_part_)
		layers.push_back(LAYER_PART);
	if(info.cur_sheet_)
		layers.push_back(LAYER_SHEET);
	if(info.cur_cut_)
		layers.push_back(LAYER_CUT);
	if(info.cur_view_)
		layers.push_back(LAYER_VIEW);
	if(info.cur_mark_)
		layers.push_back(LAYER_MARK);
	if(info.cur_dim_)
		layers.push_back(LAYER_DIM);

}
static void get_layers_ser(const Layer_Info &info,strings &layers)
{
	if(info.ser_part_)
		layers.push_back(LAYER_PART);
	if(info.ser_sheet_)
		layers.push_back(LAYER_SHEET);
	if(info.ser_cut_)
		layers.push_back(LAYER_CUT);
	if(info.ser_view_)
		layers.push_back(LAYER_VIEW);
	if(info.ser_mark_)
		layers.push_back(LAYER_MARK);
	if(info.ser_dim_)
		layers.push_back(LAYER_DIM);
	if(info.ser_ap_dim_)
		layers.push_back(LAYER_AP_DIM);

}

void hidden_layers(const Layer_Info &info,dlhml::Database *db)
{
	strings layers;
	get_layers_cur(info,layers);
	for(int i=0;i<layers.size();i++){
		show_ents_by_layer(db,layers[i],false);
	}	
}
void download_layers(const Layer_Info &info,dlhml::Database *db)
{
	strings layers;
	get_layers_ser(info,layers);
	std::string key_detail;
	for(int i=0;i<layers.size();i++){
		key_detail = Global::instance()->get_detail_key(Global::instance()->get_cur_detail_name(),layers[i]);
		detail::download(key_detail);
	}	
}
void download_layers(DB_Layer &db_layer,dlhml::Database *db)
{
	db_layer.download_layers(db);
}

void download_layer(std::string layer_name,dlhml::Database *db)
{
	std::string key_detail = Global::instance()->get_detail_key(Global::instance()->get_cur_detail_name(),layer_name);
	detail::download(key_detail);

}

void upload_layers(dlhml::Database *db)
{
	strings layer_names;
	std::string lua_file,need_upload;
	Global::instance()->db_detail().get_layers_name(Global::instance()->get_cur_detail_name(),layer_names);
	for(int i=0;i<layer_names.size();i++){
		lua_file = Global::instance()->get_layer_lua_name(layer_names[i]);
		Entitys ents;
		get_layer_ent(DB_View::instance()->database(),layer_names[i],ents);
		need_upload = Global::instance()->get_need_upload_path_name(lua_file);
		save_lua(need_upload,ents);
		
	}
	
	upload_files(Global::instance()->project_info().server_ip_,Global::instance()->get_need_upload_files_path());

	

/*
	std::string lua_file = Global::instance()->project_info().dir_path;
	std::string temp,name = Global::instance()->project_info().company_+"-"+Global::instance()->project_info().name_+"-"+dxf_file;
	std::string lua_name;
	for(int i=0;i<layer_hashs.size();i++){
		lua_name = name +"-"+layer_hashs[i].layer_name_+".lua";
		temp = lua_file+lua_name;
		save_lua(temp,layer_hashs[i].ents_);
		layer_hashs[i].lua_path_name_ = temp;
		layer_hashs[i].lua_file_name_ = lua_name;
		lua_files.push_back(lua_name);
	}
*/

}