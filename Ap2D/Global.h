// Global.h: interface for the Global class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBAL_H__1BFB9E10_840B_4149_B1DE_C7B6F2F0F663__INCLUDED_)
#define AFX_GLOBAL_H__1BFB9E10_840B_4149_B1DE_C7B6F2F0F663__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Mgr_Toolbar.h"
#include "DB_Detail.h"
#include "ap2d_objs.h"

#include "Mgr_Layers.h"
#include "DB_Company.h"
#include "DB_Tree.h"
#include "Mgr_Database.h"
#include "DB_Layer.h"
#include "DB_File.h"

#include "DB_File_Date.h"
#include "net_ap.h"

#define USER_ADD_ENTS  "user_add_ents"
//static char *SERVER_IP = "192.168.2.229";
#define SERVER_IP "192.168.1.10"
//static char *SERVER_IP = "www.qqft.com";
struct Brush_Prop
{
	Prop_Ent::PageCommon page_common_;
	Prop_Ent::PageArrow page_arrow_;
	Prop_Ent::PageDim page_dim_;
	Prop_Ent::PageRadius page_radius_;
	Prop_Ent::PageText page_text_;

};
struct Current_Val
{
	Current_Val()
	{
		cur_select_text_ = false;
	}
	Prop_Ent::Common common_prop_;
	Prop_Ent::Line line_prop_;
	Prop_Ent::Circle circle_prop_;
	Prop_Ent::Arc arc_prop_;
	Prop_Ent::Spline spline_prop_;
	Prop_Ent::Text txt_prop_;
	Prop_Ent::Text lead_dim_prop_;
	Prop_Ent::Text txt_dim_prop_;
	Prop_Ent::Dim dim_prop_;

	Prop_Ent::PageCommon page_common_;
	Prop_Ent::PageArrow page_arrow_;
	Prop_Ent::PageDim page_dim_;
	Prop_Ent::PageRadius page_radius_;
	Prop_Ent::PageText page_text_;
	Prop_Ent::PageTextCommon page_text_common_;


	Prop_Dlg::Select_Color_Prop sel_color_prop_;

	Brush_Prop brush_prop_;

	bool cur_select_text_;

	CString user_;
	CString password_;

};

class Project_Info
{
public:
	Project_Info(){server_ip_ = afc::net::get_server();/*server_ip_ = "www.qqft.com";*/}
	virtual ~Project_Info(){;}

	void upload(std::string key);
	void download(std::string key);


	std::string name_;
	std::string company_;
	std::string server_key_;

	std::string dir_path;

	std::string server_ip_;
};

class Setting
{
public:
	Setting();
	virtual ~Setting(){;}

	BOOL show_right_menu_;
	double reduce_scale_;
	double reduce_scale_export_;
};
class Global  
{
public:
	Global();
	virtual ~Global();
	static Global* instance();
	void close(); 
	
	Mgr_Toolbar &mgr_toolbar(){return mgr_toolbar_;}
	double& scale(){return scale_;}
	Project_Info &project_info(){return project_info_;}
	DB_Detail &db_detail(){return db_detail_;}
	AP2D *ap2d(){return ap_;}

	//服务器上路径
	std::string get_detail_db_key();
	std::string get_detail_key(std::string name,std::string layer_name);
	std::string get_company_key();
	std::string get_tree_key(std::string pro_name,std::string company_name);
	std::string get_tree_key();
	std::string get_detail_layers_key(std::string name);

	std::string get_detail_name_lua(std::string layer_name_lua);

	std::string& get_cur_detail_name(){return cur_detail_name_;}
	std::string get_need_upload_files_path();

	Layer_Info& layer_info(){return layer_info_;}
	DB_Company& db_company(){return db_company_;}
	DB_Tree& db_tree(){return db_tree_;}

	Current_Val& cur_val(){return cur_val_;}
	DB_Layer& db_layer(){return db_layer_;}
	DB_File& db_file(){return db_file_;}

	int &rignt_but_exit(){return right_but_exit_;	}

	std::string get_local_file_name(std::string name,std::string &local);

	std::string get_apdim_name(std::string detail_name);
	std::string get_apdim_lua_name(std::string detail_name);

	std::string get_layer_lua_name(std::string layer_name);

	std::string get_need_upload_path_name(std::string lua_name);

	Entitys &get_old_ents(){return ents_old_;}

	DB_File_Date &db_file_date(){return db_file_date_;}

	Setting &setting(){return setting_;}

	std::string get_hotkey_profile();

	CString &dxf_name(){return dxf_name_;}

	bool is_eidt_;

private:
	Mgr_Toolbar mgr_toolbar_;
	double scale_;
	Project_Info project_info_;
	DB_Detail db_detail_;
	AP2D *ap_;
	
	std::string cur_detail_name_;
	Layer_Info layer_info_;
	DB_Company db_company_;
	DB_Tree db_tree_;

	Current_Val cur_val_;
	DB_Layer db_layer_;

	int right_but_exit_;

	DB_File db_file_;
	std::string cur_need_upload_;

	Entitys ents_old_;

	DB_File_Date db_file_date_;

	Setting setting_;

	void init_ap2d();

	CString dxf_name_;

	
};

#endif // !defined(AFX_GLOBAL_H__1BFB9E10_840B_4149_B1DE_C7B6F2F0F663__INCLUDED_)
