// Mgr_Lua.cpp: implementation of the Mgr_Lua class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Lua.h"

#include "DB_View.h"
#include "Global.h"
#include "Dxf_Read.h"
#include "ApLayer_Ent.h"
#include "Mgr_File.h"
#include "getrace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Lua::Mgr_Lua()
{

}

Mgr_Lua::~Mgr_Lua()
{

}
static void full_layers(const strings &layers,ApLayer_Ents &layer_ents)
{
	ApLayer_Ent item;
	for(int i=0;i<layers.size();i++){
		item.layer_name_ = layers[i];
		layer_ents.push_back(item);		
	}
	//增加特殊层，如果没有层名的实体加到此层中
	item.layer_name_ = ELSE_LAYER;
	layer_ents.push_back(item);		

}
static void full_layers(const strings &layers,Ap_Layers &layer_hashs)
{
	Ap_Layer item;
	for(int i=0;i<layers.size();i++){
		item.layer_name_ = layers[i];
		layer_hashs.push_back(item);		
	}
	//增加特殊层，如果没有层名的实体加到此层中
	item.layer_name_ = ELSE_LAYER;
	layer_hashs.push_back(item);		

}
void save_luas(std::string dxf_file,ApLayer_Ents &aplayer_ents,strings &lua_files)
{
	std::string lua_file = Global::instance()->project_info().dir_path;
	std::string temp,name = Global::instance()->project_info().company_+"-"+Global::instance()->project_info().name_+"-"+dxf_file;
	for(int i=0;i<aplayer_ents.size();i++){
		temp = lua_file+name +"-"+aplayer_ents[i].layer_name_+".lua";
		save_lua(temp,aplayer_ents[i].ents_);
		lua_files.push_back(temp);
	}
}
void save_luas(std::string dxf_file,Ap_Layers &layer_hashs,strings &lua_files)
{
	std::string lua_file = Global::instance()->project_info().dir_path;
	std::string temp,name = Global::instance()->project_info().company_+"-"+Global::instance()->project_info().name_+"-"+dxf_file;
	std::string lua_name;
	for(int i=0;i<layer_hashs.size();i++){
		lua_name = name +"-"+layer_hashs[i].layer_name_+".lua";
		temp = lua_file+lua_name;
		int size = layer_hashs[i].ents_.size();
		save_lua(temp,layer_hashs[i].ents_);
		layer_hashs[i].lua_path_name_ = temp;
		layer_hashs[i].lua_file_name_ = lua_name;
		lua_files.push_back(lua_name);
	}
}
void save_lua(std::string lua_file,Entitys &ents)
{
	DB_View::instance()->cur_view()->scene()->database()->save_lua(ents,lua_file);
}
static void cal_hashs(Ap_Layers &layer_hashs)
{
	for(int i=0;i<layer_hashs.size();i++){
		std::string hash_val;
		get_file_hash(layer_hashs[i].lua_path_name_,layer_hashs[i].hash_val_);
	}	
}
void create_luas(std::string dxf_file,strings &lua_files,Detail &detail)
{
	DB_View::instance()->cur_view()->scene()->database()->clear_entity();
	std::string file_name = Global::instance()->project_info().dir_path.c_str()+dxf_file;
	Dxf_Read dxf_read;
	TRACE_OUT("\t\t Dxf_Read::read start .\n");
	DWORD start_time = GetTickCount();
	dxf_read.read(file_name,DB_View::instance()->cur_view()->scene());
	DWORD end_time = GetTickCount();

	TRACE_OUT("\t\t times =  %d ms.\n",(end_time-start_time));
	TRACE_OUT("\t\t Dxf_Read::read end .\n");
	
	strings layers;
	TRACE_OUT("\t\t get_layers start .\n");
	get_layers(DB_View::instance()->cur_view()->scene()->database(),layers);
	TRACE_OUT("\t\t get_layers end .\n");

	TRACE_OUT("\t\t full_layers start .\n");
	full_layers(layers,detail.ap_layers_);
	TRACE_OUT("\t\t full_layers end .\n");

	TRACE_OUT("\t\t part_ents start .\n");
	part_ents(DB_View::instance()->cur_view()->scene()->database(),detail.ap_layers_);
	TRACE_OUT("\t\t part_ents end .\n");

	TRACE_OUT("\t\t save_luas start .\n");
	start_time = GetTickCount();
	save_luas(dxf_file,detail.ap_layers_,lua_files);
	end_time = GetTickCount();

	TRACE_OUT("\t\t times =  %d ms.\n",(end_time-start_time));
	
	TRACE_OUT("\t\t save_luas end .\n");

	TRACE_OUT("\t\t cal_hashs start .\n");
	cal_hashs(detail.ap_layers_);
	TRACE_OUT("\t\t cal_hashs end .\n");

}


void download_luas(std::string detail_name)
{
	strings layer_file_names;
	Global::instance()->db_detail().get_layers(detail_name,layer_file_names);
	Global::instance()->db_file().download_ser(detail_name,layer_file_names);


	
}
void open_lua(std::string lua_file,dlhml::Database *db)
{
	db->open_lua(const_cast<char*>(lua_file.c_str()),db);
}

