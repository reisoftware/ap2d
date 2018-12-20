// Mgr_Dxfs.h: interface for the Mgr_Dxfs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXFS_MGR_H__E9F79AC7_0B31_4FD9_B5F5_38408FA0EE99__INCLUDED_)
#define AFX_DXFS_MGR_H__E9F79AC7_0B31_4FD9_B5F5_38408FA0EE99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include "Entity.h"
#include "Entity.h"
#include "Ap2D.h"

static const char *LAYER_PART = "PART1";
static const char *LAYER_SHEET = "SHEET";
static const char *LAYER_CUT = "CUT";
static const char *LAYER_VIEW = "VIEW";
static const char *LAYER_MARK = "MARK";
static const char *LAYER_DIM = "DIMENSION";
static const char *LAYER_AP_DIM = "APDIM";


#define OBJ_LINE	0
#define OBJ_ARC 1
#define OBJ_CIRCLE 2
#define OBJ_TEXT 3
#define OBJ_RECTENTITY 4
#define OBJ_ANGLE_DIM 5
#define OBJ_CLOUD_LINE 6
#define OBJ_CUT_SECTION 7
#define OBJ_RADIUS_DIM 8
#define OBJ_LEAD_DIM 9
#define OBJ_LEAD_DIM_BLOCK 10
#define OBJ_LN_DIM 11
#define OBJ_LN_DIM_BLK 12


typedef std::vector<dlhml::Entity*> Entitys;
class Detail;

class Mgr_Dxfs  
{
public:
	Mgr_Dxfs();
	virtual ~Mgr_Dxfs();

	void get_hash_val(std::string path,std::string file,Detail &detail);

	//2012-3-7新的思路，分开计算哈希值和上传图纸，需要打开图纸获取图层两次，时间加倍，但节省上传时间。
	void get_hash_val_new(std::string path,std::string file,Detail &detail);
	void upload_dxf_by_layers(std::string path,std::string file);
	void download_dxf_by_layers(std::string file);
 
};
void upload_new_dxfs(std::string dir_path,strings &files);
void load_dxf(std::string name,dlhml::Database *db);

int get_dxf_status(std::string name);
int get_dxf_status_lua(std::string name);

std::string get_hash_value(char *str);

//计算hash值，分层存lua，计算每层的hash值，把分层的文件加到上传库中。
void deal_dxf(std::string file_name);
void deal_new_dxfs(std::string dir_path,strings &files);

//按文件上传的方法
int get_dxf_status_by_file(std::string file_name);
void create_detail(std::string file_name,Detail &detail);

#endif // !defined(AFX_DXFS_MGR_H__E9F79AC7_0B31_4FD9_B5F5_38408FA0EE99__INCLUDED_)
