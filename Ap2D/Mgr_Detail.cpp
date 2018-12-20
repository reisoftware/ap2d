// Mgr_Detail.cpp: implementation of the Mgr_Detail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Detail.h"

#include "Database.h"
#include "Mgr_Dxfs.h"
#include "DB_View.h"
#include "Global.h"
#include "getrace.h"

#include "Line.h"
#include "RArc.h"
#include "Circle.h"
#include "Text.h"
#include "Rectentity.h"
#include "Angle_Dimension.h"
#include "Cloud_Line.h"
#include "Cut_Section.h"
#include "Radius_Dimension.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Lead_Dimension_Block.h"
#include "Ln_Dim.h"
#include "Ln_Dim_Block.h"

#include "encode.h"
#include "Mgr_Database.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Detail::Mgr_Detail()
{

}

Mgr_Detail::~Mgr_Detail()
{

}

static void divide_vals(char *rs,strings &vals)
{
	CString left,s = rs;
	char *key = "kind=";
	int pos = s.Find(key);
	std::string v;
	int len = s.GetLength();
	int i=0;
	while(s != ""){
			left = s.Left(s.Find(key));
			if(left != "" ){
				v = key+left;
				vals.push_back(v);
			}else{
/*
				if((left == "" )&& (s.GetLength()>10)){
					v = key+left;
					vals.push_back(v);
				}
*/
			}
			if(s.GetLength()>5){
				s.Delete(0,left.GetLength()+5);	
				left = s.Left(s.Find(key));
				if(left == ""){
					v = key+s;
					vals.push_back(v);
					s = "";
				}

			}else 
				s = "";
	}
	int count = vals.size();


/*
	char *key = "kind=";
	char v[500];
	char *pos = strstr(rs,key);
	while (pos != NULL){
		pos = strstr(rs,key);
		int size = pos-rs;
		strncpy(v,rs,size);
		pos = strstr(rs,key);
	}
*/
}

static int get_kind(std::string val)
{
	rei_init(const_cast<char *>(val.c_str()));
	std::string kind = rei_get("kind");
	int id = -1;
	rei_quit();

	if(strcmp(kind.c_str(),"LINE")==0)
		return OBJ_LINE;
	else if(strcmp(kind.c_str(),"ARC")==0)
		return OBJ_ARC;
	else if(strcmp(kind.c_str(),"CIRCLE")==0)
		return OBJ_CIRCLE;
	else if(strcmp(kind.c_str(),"TEXT")==0)
		return OBJ_TEXT;
	else if(strcmp(kind.c_str(),"ANGLE_DIM")==0)
		return OBJ_ANGLE_DIM;
	else if(strcmp(kind.c_str(),"CLOUD_LINE")==0)
		return OBJ_CLOUD_LINE;
	else if(strcmp(kind.c_str(),"CUT_SECTION")==0)
		return OBJ_CUT_SECTION;
	else if(strcmp(kind.c_str(),"RADIUS_DIM")==0)
		return OBJ_RADIUS_DIM;
	else if(strcmp(kind.c_str(),"LEAD_DIM")==0)
		return OBJ_LEAD_DIM;
	else if(strcmp(kind.c_str(),"LEAD_DIM_BLOCK")==0)
		return OBJ_LEAD_DIM_BLOCK;
	else if(strcmp(kind.c_str(),"LN_DIM")==0)
		return OBJ_LN_DIM;
	else if(strcmp(kind.c_str(),"LN_DIM_BLK")==0)
		return OBJ_LN_DIM_BLK;
	else if(strcmp(kind.c_str(),"RECTENTITY")==0)
		return OBJ_RECTENTITY;
	return id;
}
template<class T> 
void create_ent(std::string val)
{
	T *l = T::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);

}

static void create_line(std::string val)
{
	dlhml::Line *l = dlhml::Line::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);

}
static void create_circle(std::string val)
{
	dlhml::Circle *l = dlhml::Circle::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_arc(std::string val)
{
	dlhml::RArc *l = dlhml::RArc::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_text(std::string val)
{
	dlhml::Text *l = dlhml::Text::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_angle_dim(std::string val)
{
	dlhml::Angle_Dimension *l = dlhml::Angle_Dimension::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_cloud_line(std::string val)
{
	dlhml::Cloud_Line *l = dlhml::Cloud_Line::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}

static void create_cut_section(std::string val)
{
//	TRACE_OUT("the cut str = %s\n" ,val.c_str());
	
	dlhml::Cut_Section *l = dlhml::Cut_Section::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_radius_dim(std::string val)
{
	dlhml::Radius_Dimension *l = dlhml::Radius_Dimension::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_lead_dim(std::string val)
{
	dlhml::Lead_Dimension *l = dlhml::Lead_Dimension::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_lead_dim_blk(std::string val)
{
	dlhml::Lead_Dimension_Block *l = dlhml::Lead_Dimension_Block::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_ln_dim(std::string val)
{
	dlhml::Ln_Dim *l = dlhml::Ln_Dim::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_ln_dim_blk(std::string val)
{
	dlhml::Ln_Dim_Block *l = dlhml::Ln_Dim_Block::create_me();
	int size = val.size();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}
static void create_rect(std::string val)
{
	dlhml::Rectentity *l = dlhml::Rectentity::create_me();
	l->set_from_str(const_cast<char*>(val.c_str()));
	dlhml::Entity_ID id;
	l->post2db(*DB_View::instance()->cur_view()->scene()->database(),id);
}


void create_detail(std::string val)
{
	double len = strlen(val.c_str());
//	TRACE_OUT("the str len = %d\n", val.size());
	char temp[50000];
	strcpy(temp,val.c_str());
	CString s = val.c_str();
	int size = s.GetLength();
	if(size<1)
		return ;

	int kind = get_kind(val);
	if(kind == OBJ_LINE)
		create_line(temp);
	else if(kind == OBJ_CIRCLE)
		create_circle(temp);
	else if(kind == OBJ_ARC)
		create_arc(temp);
	else if(kind == OBJ_TEXT)
		create_text(temp);
	else if(kind == OBJ_ANGLE_DIM)
		create_angle_dim(temp);
	else if(kind == OBJ_CLOUD_LINE)
		create_cloud_line(temp);
	else if(kind == OBJ_CUT_SECTION)
		create_cut_section(temp);
	else if(kind == OBJ_RADIUS_DIM)
		create_radius_dim(temp);
	else if(kind == OBJ_LEAD_DIM)
		create_lead_dim(temp);
	else if(kind == OBJ_LEAD_DIM_BLOCK)
		create_lead_dim_blk(temp);
	else if(kind == OBJ_LN_DIM)
		create_ln_dim(temp);
	else if(kind == OBJ_LN_DIM_BLK)
		create_ln_dim_blk(temp);
	else if(kind == OBJ_RECTENTITY)
		create_rect(temp);


	


}


static void create_ents(strings &vals)
{
	for(int i=0;i<vals.size();i++){
		std::string val = vals[i];
		if(val.find("kind") != 0)
			continue;
		int count = val.size();
		create_detail(val);
	
	}
}
namespace detail
{


void download(std::string key)
{
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
			strings vals;
			divide_vals(rs,vals);

			create_ents(vals);

						
		}	
	}

//	show_ents();

}
void merge_detail(std::string name)
{
	load_dxf(name,DB_View::instance()->cur_view()->scene()->database());
	hidden_layers(Global::instance()->layer_info(),DB_View::instance()->cur_view()->scene()->database());
	download_layers(Global::instance()->layer_info(),DB_View::instance()->cur_view()->scene()->database());
}

void delete_detail(std::string detail_name)
{
	strings layer_file_names;
	Global::instance()->db_detail().get_layers(detail_name,layer_file_names);	
	Global::instance()->db_file().delete_ser(detail_name,layer_file_names);
}






}