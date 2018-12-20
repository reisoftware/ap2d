// Vis_Ent_Dblclk.cpp: implementation of the Vis_Ent_Dblclk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Vis_Ent_Dblclk.h"

#include "DB_View.h"
#include "Mgr_Database.h"
#include "Global.h"
#include "Mgr_Convert.h"
#include "Line_Arrow.h"
#include "Line.h"
#include "Circle.h"
#include "RArc.h"
#include "Text.h"
#include "Cloud_Line.h"
#include "Angle_Dimension.h"
#include "Ln_Dim.h"
#include "Three_Pt_Dimension.h"
#include "Ln_Dim_Block.h"
#include "Three_Pt_Dimension_Block.h"
#include "Radius_Dimension.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Text_Dimension.h"

#include "Arc_Arrow.h"
#include "Tab_Entity.h"
#include "Dlg_Dim_Name_Set.h"
#include "Lead_Dimension_Info.h"

#include "Text_Dimension_Info.h"
#include "Ln_Dim_PlateSide.h"
#include "Ln_Dim_Direct.h"

#include "Dim_Angle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Tab_Entity *g_tab_edit= NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Vis_Ent_Dblclk::Vis_Ent_Dblclk()
{

}

Vis_Ent_Dblclk::~Vis_Ent_Dblclk()
{

}
void Vis_Ent_Dblclk::show_dlg()
{
	Entitys sel_ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);

	if(::IsWindow(g_tab_edit->GetSafeHwnd())){
		g_tab_edit->CloseWindow();
		delete g_tab_edit;
		//g_tab_edit->reload();
		//g_tab_edit->SetFocus();
		//return;
	}	
	g_tab_edit = new Tab_Entity;
	g_tab_edit->Create(IDD_TAB_ENTITY);
	g_tab_edit->ShowWindow(SW_SHOW);


}

static void get_page_common(Prop_Ent::PageCommon &page_common,std::string line_type,int color_index)
{
	page_common.line_type_ = line_type;
	page_common.color_ = color_index;

}
static void get_page_dim(Prop_Ent::PageDim &page_dim,std::string line_type,dlhml::Dimension_Style &ds)
{
	page_dim.start_dim_len_= ds.start_dim_length();
	page_dim.end_dim_len_ = ds.end_dim_length();
	page_dim.start_offset_ = ds.extend_start_off();
	page_dim.end_offset_ = ds.extend_end_off();

}
static void get_page_text(Prop_Ent::PageText &page_text,double angle,std::string dim_text,CString dim_kind,dlhml::Dimension_Style &ds)
{
	page_text.angle_= angle;
	page_text.color_= ds.text_color();
	page_text.content_= dim_text;
	page_text.dim_kind_= dim_kind;
	page_text.frame_kind_= get_txt_frame(ds.txt_frame());
	page_text.frame_color_= ds.text_frame_color();
	page_text.frame_out_= get_txt_frame(ds.txt_frame());
	page_text.hight_= ds.text_height();
	page_text.text_pos_= get_txt_pos(ds.text_pos());

	page_text.precision_ = ds.text_precision();


}
static void get_page_arrow(Prop_Ent::PageArrow &page_arrow,dlhml::Dimension_Style &ds)
{
	page_arrow.arrow_style_= get_arrow_style(ds.arrow_style());
	page_arrow.arrow_hight_= ds.arrow_size();
	page_arrow.arrow_level_= ds.arrow_size();	
	page_arrow.arrow_pos_ = get_arrow_pos(ds.arrow_num());

}
static void get_page_radius(Prop_Ent::PageRadius &page_radius,double radius)
{
	page_radius.radius_= radius;
}

bool Vis_Ent_Dblclk::visit_line(dlhml::Line& line)
{
	get_page_common(Global::instance()->cur_val().page_common_,line.line_style(),line.color_index());

	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::visit_line_arrow(dlhml::Line_Arrow& la)
{
	get_page_common(Global::instance()->cur_val().page_common_,la.line_style(),la.color_index());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,la.dim_style_val());
	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::Visit_Circle(dlhml::Circle& circle)
{
	get_page_common(Global::instance()->cur_val().page_common_,circle.line_style(),circle.color_index());
	get_page_radius(Global::instance()->cur_val().page_radius_,circle.radius());
	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::Visit_RArc(dlhml::RArc& arc)
{
	get_page_common(Global::instance()->cur_val().page_common_,arc.line_style(),arc.color_index());
	get_page_radius(Global::instance()->cur_val().page_radius_,arc.radius());

	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::Visit_Arc_Arrow(dlhml::Arc_Arrow& aa)
{
	dlhml::Dimension_Style ds = aa.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,aa.line_style(),ds.line_color());
	get_page_radius(Global::instance()->cur_val().page_radius_,aa.radius());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,aa.line_style(),ds);	
	show_dlg();
  return true;
}

bool Vis_Ent_Dblclk::Visit_Cloud_Line(dlhml::Cloud_Line& cloud)
{
	get_page_common(Global::instance()->cur_val().page_common_,cloud.line_style(),cloud.color_index());
	show_dlg();
	return true;
}  


bool Vis_Ent_Dblclk::Visit_Text(dlhml::Text& text)
{
	Global::instance()->cur_val().page_text_common_.content_= text.text();
	Global::instance()->cur_val().page_text_common_.angle_= text.rotation();
	Global::instance()->cur_val().page_text_common_.color_= text.color_index();
	Global::instance()->cur_val().page_text_common_.hight_= text.dxf_height();
	Global::instance()->cur_val().page_text_common_.width_factor_= text.width_factor();
	Global::instance()->cur_val().page_text_common_.font_style_= text.font();

	show_dlg();
	return true;
}


bool Vis_Ent_Dblclk::Visit_Lead_Dimension(dlhml::Lead_Dimension& lead_dim)
{
	dlhml::Dimension_Style ds = lead_dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,lead_dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,lead_dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,lead_dim.text_rotation(),lead_dim.dim_text(),Dim_Kind_Lead_dim,ds);

	show_dlg();
	return true;
}

bool Vis_Ent_Dblclk::Visit_Text_Dimension(dlhml::Text_Dimension& text_dim) 
{
	dlhml::Dimension_Style ds = text_dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,text_dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,text_dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,text_dim.text_rotation(),text_dim.dim_text(),Dim_Kind_Lead_dim,ds);
	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::Visit_Angle_Dimension(dlhml::Angle_Dimension& dim)
{
	dlhml::Dimension_Style ds = dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,dim.text_rotation(),dim.dim_text(),Dim_Kind_Lead_dim,ds);
	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::Visit_Ln_Dim(dlhml::Ln_Dim& dim) 
{
	dlhml::Dimension_Style ds = dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,dim.text_rotation(),dim.dim_text(),Dim_Kind_Lead_dim,ds);
	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::Visit_Ln_Dim_Block(dlhml::Ln_Dim_Block& dim)
{
	if(dim.mode() == dlhml::PILEUP_DIM)
		Global::instance()->cur_val().page_dim_.dim_kind_ = "Continue Line Dim";
	else if(dim.mode() == dlhml::CLOSED_DIM)
		Global::instance()->cur_val().page_dim_.dim_kind_ = "Base Line Dim";
	dlhml::Dimension_Style ds;
	dim.get_dim_style(ds);
	get_page_common(Global::instance()->cur_val().page_common_,dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,0,"0",Dim_Kind_Lead_dim,ds);
	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::Visit_Radius_Dimension(dlhml::Radius_Dimension& dim)
{
	dlhml::Dimension_Style ds = dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,dim.text_rotation(),dim.dim_text(),Dim_Kind_Lead_dim,ds);
	show_dlg();
	return true;
}
bool Vis_Ent_Dblclk::Visit_Lead_Dimension_Block(dlhml::Lead_Dimension_Block& lead_dim_block)
{
/*
	dlhml::Dimension_Style ds = lead_dim_block.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,lead_dim_block.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,lead_dim_block.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,lead_dim_block.text_rotation(),lead_dim_block.dim_text(),Dim_Kind_Lead_dim,ds);
*/
	show_dlg();
	return true;
}

bool Vis_Ent_Dblclk::visit_Lead_Dimension_Info(dlhml::Lead_Dimension_Info& lead_dim_info)
{
	//Dlg_Dim_Name_Set dlg;
	//dlg.DoModal();

	dlhml::Dimension_Style ds = lead_dim_info.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,lead_dim_info.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,lead_dim_info.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,lead_dim_info.text_rotation(),lead_dim_info.dim_text(),Dim_Kind_Lead_dim,ds);
	show_dlg();

	return true;
}


bool Vis_Ent_Dblclk::Visit_Text_Dimension_Info(dlhml::Text_Dimension_Info& dim) 
{
	dlhml::Dimension_Style ds = dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,dim.text_rotation(),dim.dim_text(),Dim_Kind_Lead_dim,ds);
	show_dlg();

	return true;
}
bool Vis_Ent_Dblclk::Visit_Ln_Dim_PlateSide(dlhml::Ln_Dim_PlateSide& dim) 
{
	dlhml::Dimension_Style ds = dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,dim.text_rotation(),dim.dim_text(),Dim_Kind_Lead_dim,ds);
	show_dlg();

	return true;
}
bool Vis_Ent_Dblclk::Visit_Ln_Dim_Direct(dlhml::Ln_Dim_Direct& dim)
{
	dlhml::Dimension_Style ds = dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,dim.line_style(),ds.line_color());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,dim.line_style(),ds);	
	get_page_text(Global::instance()->cur_val().page_text_,dim.text_rotation(),dim.dim_text(),Dim_Kind_Lead_dim,ds);
	show_dlg();

	return true;
}

bool Vis_Ent_Dblclk::Visit_Dim_Angle(dlhml::Dim_Angle& dim)
{
	dlhml::Dimension_Style ds = dim.dim_style_val();
	get_page_common(Global::instance()->cur_val().page_common_,dim.line_style(),ds.line_color());
//	get_page_radius(Global::instance()->cur_val().page_radius_,dim.radius());
	get_page_arrow(Global::instance()->cur_val().page_arrow_,ds);
	get_page_dim(Global::instance()->cur_val().page_dim_,dim.line_style(),ds);	


	show_dlg();


	return true;

}

