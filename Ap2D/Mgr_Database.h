// Mgr_Database.h: interface for the Mgr_Database class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_DATABASE_H__69CBDF57_87B4_47C7_8281_84079591C73E__INCLUDED_)
#define AFX_MGR_DATABASE_H__69CBDF57_87B4_47C7_8281_84079591C73E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Mgr_Dxfs.h"
#include "ApLayer_Ent.h"
#include "DB_Detail.h"
#include "Dimension_Style.h"
#include "Mgr_Convert.h"


class Prop_Ent  
{
public:
	Prop_Ent(){;}
	virtual ~Prop_Ent(){;}

	struct PageArrow{
		PageArrow()
		{
			arrow_pos_ = "no";
			arrow_num_ = "0";
			arrow_style_ = "common";
			arrow_level_ = 10;
			arrow_hight_ = 10;
		//	arrow_num_ = 1;

		}
		std::string arrow_pos_;
		std::string arrow_style_;
		double arrow_level_;
		double arrow_hight_;
		std::string arrow_num_;
		
		BOOL check_arrow_pos_;
		BOOL check_arrow_level_;
		BOOL check_arrow_kind_;
		BOOL check_arrow_hight_;
		BOOL check_arrow_num_;
	
	};
	struct PageCommon{
		PageCommon()
		{
			line_type_ = "Continuous";
			color_ = 7;

		}
		std::string line_type_;
		int color_;

		BOOL check_l_type_;
		BOOL check_l_color_;
	};
	struct PageDim{
		PageDim()
		{
			dim_kind_ = "Continue Line Dim";

			start_offset_ = 20;
			end_offset_ = 20;
			start_dim_len_ = 20;
			end_dim_len_ = 20;

		}
		std::string	dim_kind_;

		double	start_offset_;
		double	end_offset_;
		double	start_dim_len_;
		double	end_dim_len_;

		BOOL	check_dim_kind_;

		BOOL	check_start_offset_;
		BOOL	check_end_offset_;
		BOOL	check_start_dim_len_;	
		BOOL	check_end_dim_len_;	
		
	};
	struct PageRadius{
		PageRadius()
		{
			radius_ = 0;

		}
		double	radius_;

		BOOL	check_l_radius_;	
	};
	struct PageText{
		PageText()
		{
			content_ = "A";
			color_ = 3;
			angle_ = 0;
			hight_ = 80;
			dim_kind_ = "";
			frame_out_ = g_dimKindNoFrame;
			frame_color_ = 3;
			precision_ = 0.1;
			text_pos_ = "Center";
		}
		std::string	content_;
		double	hight_;
		int	color_;
		double	angle_;
		CString	dim_kind_;
		std::string	text_pos_;

		std::string	frame_kind_;
		std::string	frame_out_;
		int	frame_color_;

		double	precision_;

		std::string	font_style_;
		double	width_factor_;

		BOOL	check_content_;
		BOOL	check_hight_;
		BOOL	check_color_;
		BOOL	check_angle_;

		BOOL	check_frame_out_;
		BOOL	check_frame_color_;
		BOOL	check_frame_kind_;
		BOOL	check_precision_;
		BOOL	check_font_style_;
		BOOL	check_width_factor_;
	};


	struct PageTextCommon{
		PageTextCommon()
		{
			content_ = "A";
			color_ = 3;
			angle_ = 0;
			hight_ = 80;
			precision_ = 0.1;
			text_pos_ = "Center";
			font_style_ = "Standard";
			width_factor_ = 1;
		}
		std::string	content_;
		double	hight_;
		int	color_;
		double	angle_;
		CString	dim_kind_;
		std::string	text_pos_;

		double	precision_;
		std::string	font_style_;
		double	width_factor_;

		BOOL	check_content_;
		BOOL	check_hight_;
		BOOL	check_color_;
		BOOL	check_angle_;

		BOOL	check_precision_;
		BOOL	check_font_style_;
		BOOL	check_width_factor_;
	};


	struct Common{
			Common()
			{
				line_type_ = "Continuous";
				color_ = "7";

			}
			std::string line_type_;
			std::string color_;

			BOOL check_l_type_;
			BOOL check_l_color_;
		};

		struct Line{
		Line()
		{
			line_type_ = "Continuous";
			color_ = 7;

		}
		std::string line_type_;
		int color_;
		std::string arrow_pos_;
		std::string arrow_style_;
		double arrow_level_;
		double arrow_hight_;
		
		BOOL check_l_type_;
		BOOL check_l_color_;
		BOOL check_arrow_pos_;
		BOOL check_arrow_level_;
		BOOL check_arrow_kind_;
		BOOL check_arrow_hight_;

	};
	struct Arc{
		Arc()
		{
			line_type_ = "Continuous";
			color_ = 7;
			radius_ = 20;

		}
		std::string	line_type_;
		int	color_;
		std::string	arrow_pos_;
		std::string	arrow_style_;
		double	arrow_hight_;
		double	arrow_level_;
		double	radius_;

		BOOL	check_l_type_;
		BOOL	check_l_radius_;
		BOOL	check_l_color_;
		BOOL	check_arrow_pos_;
		BOOL	check_arrow_level_;
		BOOL	check_arrow_kind_;
		BOOL	check_arrow_hight_;
	};
	struct Circle{
		Circle()
		{
			line_type_ = "Continuous";
			color_ = "7";
			radius_ = 20;
		}
		std::string	line_type_;
		std::string	color_;
		double	radius_;

		BOOL	check_l_type_;
		BOOL	check_radius_;
		BOOL	check_l_color_;
	};
	struct Spline{
		Spline()
		{
			line_type_ = "Continuous";
			color_ = "7";
		}
		std::string	line_type_;
		std::string	color_;

		BOOL	check_l_type_;
		BOOL	check_l_color_;
	};
	struct Text{
		Text()
		{
			content_ = "A";
			color_ = "3";
			angle_ = 0;
			hight_ = 80;
			precision_ = 0.1;
		}
		std::string	content_;
		double	hight_;
		std::string	color_;
		double	angle_;
		CString	dim_kind_;
		double	precision_;

		std::string	frame_out_;
		std::string	frame_kind_;
		std::string	frame_color_;
		std::string	arrow_style_;
		double	arrow_hight_;
		double	arrow_level_;

		BOOL	check_content_;
		BOOL	check_hight_;
		BOOL	check_color_;
		BOOL	check_angle_;

		BOOL	check_frame_out_;
		BOOL	check_frame_kind_;
		BOOL	check_frame_color_;
		BOOL	check_arrow_style_;
		BOOL	check_arrow_level_;
		BOOL	check_arrow_hight_;
	
		BOOL	check_precision_;
	};
	struct Dim{
		Dim()
		{
			unit_ = "mm";
			precision_ = 0.1;
			line_color_ = "1";
		}
		std::string	unit_;
		double	precision_;
		std::string	line_color_;
		std::string	dim_kind_;
		double	start_offset_;
		double	reach_len_;


		BOOL	check_unit_;
		BOOL	check_precision_;
		BOOL	check_line_color_;
		BOOL	check_dim_kind_;
		BOOL	check_start_offset_;
		BOOL	check_reach_len_;

		std::string	text_pos_;
		std::string	text_frame_;
		std::string	text_color_;
		double	text_hight_;
		std::string	text_format_;

		std::string	arrow_style_;
		std::string	arrow_color_;		
		double	arrow_hight_;
		double	arrow_level_;


		BOOL	check_text_pos_;
		BOOL	check_text_frame_;
		BOOL	check_text_color_;
		BOOL	check_text_hight_;
		BOOL	check_text_format_;

		BOOL	check_arrow_style_;
		BOOL	check_arrow_color_;
		BOOL	check_arrow_hight_;
		BOOL	check_arrow_level_;
		
		

	};


};


class Prop_Dlg 
{
public:
	Prop_Dlg(){;}
	virtual ~Prop_Dlg(){;}

	struct Select_Color_Prop
	{
		Select_Color_Prop()
		{
			cur_file_num_ = 0;
			cur_color_one_ = 1;
			cur_color_two_ = 1;
			cur_color_error_ = 1;
			is_rember_color_ = FALSE;

			dbl_color_file0_ = 8;
			dbl_color_file1_ = 2;
		}
		int cur_file_num_ ;
		BOOL is_rember_color_ ;
		int cur_color_one_ ;
		int cur_color_two_ ;
		int cur_color_error_ ;

		std::string one_prefix_;
		std::string one_postfix_;
	
		std::string two_prefix_;
		std::string two_postfix_;
		
		BOOL include_cur_txt_;
		std::string cur_txt_group_;
		
		std::string cur_txt_val_;


		int dbl_color_file0_;
		int dbl_color_file1_;

	
	};
	Entitys ents_one_;
	Entitys ents_two_;

};


namespace dlhml
{
	class Database;
}

class Mgr_Database  
{
public:
	Mgr_Database();
	virtual ~Mgr_Database();

};
void get_ents(dlhml::Database *db,Entitys &ents);

void get_str_by_ents(Entitys &ents,char *out);
void get_layer_ent(dlhml::Database *db,std::string layer_name,Entitys &ents);

void show_ents_by_layer(dlhml::Database *db,std::string layer_name,bool show);
void show_ents();
bool get_select_ents(dlhml::Database *db,Entitys &sel_ents);

void show_ents_part(Entitys &ents,bool show);
void show_text(dlhml::Database *db,std::string txt);


void clear_select(dlhml::Database *db);

bool is_lines(Entitys &ents);
bool is_circles(Entitys &ents);
bool is_arcs(Entitys &ents);
bool is_texts(Entitys &ents);
bool is_dims(Entitys &ents);
bool is_dims_no_angle(Entitys &ents);
bool is_dims_blk(Entitys &ents);

void get_layers(dlhml::Database *db,strings &layers);

void get_texts(dlhml::Database *db,const Entitys &ents,Entitys &texts);
void get_lines(dlhml::Database *db,const Entitys &ents,Entitys &lns);
void get_lines(dlhml::Database *db,Entitys &lns);
void get_line_arrows(dlhml::Database *db,const Entitys &ents,Entitys &lns);
void get_line_arrows(dlhml::Database *db,Entitys &lns);



void part_ents(dlhml::Database *db,ApLayer_Ents &layer_ents);
void part_ents(dlhml::Database *db,Ap_Layers &layer_hashs);

void change_color(dlhml::Database *db,int color_index);
void change_color(Entitys &ents,int color_index);
void change_color(Entitys &ents,int color_no1,int color_no2);

void show_ents(dlhml::Database *db,std::string txt_val,Entitys &equ_txt_texts);

void check_equ_text(dlhml::Database *db,Entitys &sel_ents);

void change_group_name(Entitys &ents,std::string group);

//得到集合中字符串等于参数str的文本实体集合
void get_texts_equal_str(CString str,const Entitys &sel_texts,Entitys &texts);
//得到集合中实体的内所有子实体是文字实体的集合
void get_sons_in_ents(dlhml::Database *db,const Entitys &ents,Entitys &sons);
//得到所有标注块
void get_lead_dim_infos(dlhml::Database *db,const Entitys &ents,Entitys &dim_blks);
//得到所有标注块
void get_text_dim_infos(dlhml::Database *db,const Entitys &ents,Entitys &dim_blks);
//处理包含该字符串的集合
void get_texts_include_str(CString str,const Entitys &sel_texts,Entitys &texts);

std::string get_select_txt(dlhml::Database *db);

class Group_Txt
{
public:
	Group_Txt(){count_ =0;}
	~Group_Txt(){}

	bool operator==(const Group_Txt& rhs)
	{
		if(strcmp(txt_.c_str(),rhs.txt_.c_str()) == 0 )
			return true;
		return false;
	}	
	
	std::string group_name_;
	int count_;
	int count_0_;
	int count_1_;

	std::string txt_;
};
typedef std::vector<Group_Txt>  Group_Txts;

void print_info(Entitys &equ_txts);

void show_equ_txts(dlhml::Database *db,Entitys &sel_texts);

void get_ents_by_group(dlhml::Database *db,std::string group,Entitys &groups);

void create_report(dlhml::Database *db);

void select_ents_by_layer(dlhml::Database *db,bool sel);
void reserve_select(dlhml::Database *db);

void create_dim_style(dlhml::Dimension_Style & dim_style);
void find_tool_text_sel(std::vector<dlhml::Entity*>,std::vector<dlhml::Entity*>&,CString);
void find_tool_line_type_sel(std::vector<dlhml::Entity*> data,std::vector<dlhml::Entity*>&  show_data,CString text);
void find_tool_type_sel(std::vector<dlhml::Entity*> data,std::vector<dlhml::Entity*>&  show_data,CString text);
void find_tool_color_sel(std::vector<dlhml::Entity*> ,int);

void mgr_db_init_dlg_sel_tab_text_data(std::vector<dlhml::Entity*>,std::vector<dlhml::Entity*>,CListCtrl &);
void show_sel_tab_txt(CString,std::vector<dlhml::Entity*>);
void show_tab_txt_dlg_all_ents(std::vector<dlhml::Entity*>);

#endif // !defined(AFX_MGR_DATABASE_H__69CBDF57_87B4_47C7_8281_84079591C73E__INCLUDED_)
