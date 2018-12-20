// Global.cpp: implementation of the Global class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Global.h"

#include "net.h"
#include "net_ap.h"
#include "Mgr_File.h"
#include "dir.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void Project_Info::upload(std::string key)
{
}
void Project_Info::download(std::string key)
{
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Setting::Setting()
{
	reduce_scale_ = 1;
	reduce_scale_export_ = 1;

	std::string ini_file = afc::dir::exe_path()+"setting.ini";
	std::string val = read(ini_file.c_str(), "show_right_menu","show_right_menu");
	show_right_menu_ = atoi(val.c_str());
	reduce_scale_ = atof(read(ini_file.c_str(), "reduce_scale","reduce_scale").c_str());
	reduce_scale_export_ = atof(read(ini_file.c_str(), "reduce_scale_export","reduce_scale_export").c_str());
	if(val == ""){
		show_right_menu_ = TRUE;

	}
	if(reduce_scale_<=0)
		reduce_scale_ = 1;
	if(reduce_scale_export_<=0)
		reduce_scale_export_ = 1;
	
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Global::Global()
{
	scale_ = 1.0;
//	init_ap2d();
	project_info_.company_ = "dahe";
	project_info_.name_ = "project";
	right_but_exit_ = 1;

	is_eidt_ = false;

	
}

Global::~Global()
{
	close_ap2d(ap_);
	close_net();
	free(ap_);
}
static int un_lock_int(int s) 
{
	long t = s;
	t = t/2+50;
	return t;
}
std::string server = "52109835592035951514";
long g_port = 12658;

void Global::init_ap2d()
{
return;

	int res = init_net();
	if(!res)
		return ;
	ap_ = (AP2D*)malloc(sizeof(AP2D));
	//std::string ser = un_lock_str(server);
	//std::string ser = "www.qqft.com";
//	std::string ser = SERVER_IP;
	std::string ser = afc::net::get_server();
	strcpy(ap_->server,ser.c_str());
	ap_->port = un_lock_int(g_port);
	ap_->index = 1;
	strcpy(ap_->sign,"ap2d");
	int ss = init_ap2d_server(ap_);

}

Global* Global::instance()
{	
	static Global g;
	return &g;
}

void Global::close()
{
	delete this;
}

std::string Global::get_detail_db_key()
{
	std::string str;
	str = project_info_.company_+":"+project_info_.name_+":db_detail";
	return str;
	
}
std::string Global::get_detail_key(std::string name,std::string layer_name)
{
	std::string str;
	str = project_info_.company_+":"+project_info_.name_+":"+name+":"+layer_name;
	return str;

}
std::string Global::get_company_key()
{
	return "ap2d:companys";

}
std::string Global::get_tree_key(std::string pro_name,std::string company_name)
{
	std::string str;
	str = company_name+":"+pro_name+":"+"trees";
	return str;

}
std::string Global::get_tree_key()
{
	std::string str;
	str = project_info_.company_+":"+project_info_.name_+":"+"trees";
	return str;

}
std::string Global::get_detail_layers_key(std::string name)
{
	std::string str;
	str = project_info_.company_+":"+project_info_.name_+":"+name+":"+"layers";
	return str;
}
std::string Global::get_detail_name_lua(std::string layer_name_lua)
{
	std::string str;
	str = project_info_.dir_path+layer_name_lua;
	return str;

}
std::string Global::get_need_upload_files_path()
{
	cur_need_upload_ = project_info_.dir_path+"server\\";
	return cur_need_upload_;
}
std::string Global::get_local_file_name(std::string name,std::string &local)
{
	std::string str;
	str = project_info_.dir_path+"local\\"+name;
	local = str;
	return str;

}
std::string Global::get_apdim_name(std::string detail_name)
{
	std::string str;
	str = project_info_.company_+":"+project_info_.name_+":"+detail_name+":"+LAYER_AP_DIM;
	return str;
}
std::string Global::get_apdim_lua_name(std::string detail_name)
{
	std::string str;
	str = project_info_.company_+"-"+project_info_.name_+"-"+detail_name+"-"+LAYER_AP_DIM+".lua";
	return str;
}
std::string Global::get_layer_lua_name(std::string layer_name)
{
	std::string str;
	str = project_info_.company_+"-"+project_info_.name_+"-"+cur_detail_name_+"-"+layer_name+".lua";
	return str;

}
std::string Global::get_need_upload_path_name(std::string lua_name)
{
	std::string str;
	str = project_info_.dir_path+"server\\"+lua_name;
	return str;
}
std::string Global::get_hotkey_profile()
{ 
	
	std::string path = exe_path() + "hotkey.ini";
	return path;
}
