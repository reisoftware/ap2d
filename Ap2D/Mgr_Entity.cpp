// Mgr_Entity.cpp: implementation of the Mgr_Entity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Entity.h"
#include "global.h"
#include "Mgr_Convert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Entity::Mgr_Entity()
{

}

Mgr_Entity::~Mgr_Entity()
{

}
void init_line_arrow(dlhml::Line_Arrow &seed)
{
	seed.line_style(Global::instance()->cur_val().page_common_.line_type_);
	seed.color_index(Global::instance()->cur_val().page_common_.color_);

}
void init_circle(dlhml::Circle &seed)
{
	seed.line_style(Global::instance()->cur_val().page_common_.line_type_);
	seed.color_index(Global::instance()->cur_val().page_common_.color_);
	seed.radius(Global::instance()->cur_val().page_radius_.radius_);

}
void init_arc_arrow(dlhml::Arc_Arrow &seed)
{
	seed.line_style(Global::instance()->cur_val().page_common_.line_type_);
	seed.color_index(Global::instance()->cur_val().page_common_.color_);
	seed.radius(Global::instance()->cur_val().page_radius_.radius_);

}
void init_cloud_line(dlhml::Cloud_Line &seed)
{
	seed.line_style(Global::instance()->cur_val().page_common_.line_type_);
	seed.color_index(Global::instance()->cur_val().page_common_.color_);

}

template<class T> void init_dim(T &seed)
{
	seed.line_style(Global::instance()->cur_val().page_common_.line_type_);
	seed.color_index(Global::instance()->cur_val().page_common_.color_);

	dlhml::Dimension_Style dim_style;

	seed.dim_text(Global::instance()->cur_val().page_text_.content_.c_str());
	dim_style = seed.dim_style_val();

	dim_style.text_height(Global::instance()->cur_val().page_text_.hight_);
	dim_style.text_color(Global::instance()->cur_val().page_text_.color_);
	dim_style.line_color(Global::instance()->cur_val().page_text_.frame_color_);


	dim_style.txt_frame(get_txt_frame(Global::instance()->cur_val().page_text_.frame_kind_.c_str()));
	dim_style.text_frame_color(Global::instance()->cur_val().page_text_.frame_color_);

	dim_style.arrow_style(get_arrow_style_by_name(Global::instance()->cur_val().page_arrow_.arrow_style_.c_str()));
	dim_style.arrow_size(Global::instance()->cur_val().page_arrow_.arrow_level_);

	double s = Global::instance()->cur_val().page_text_.precision_;
	dim_style.text_precision(Global::instance()->cur_val().page_text_.precision_);

	seed.dim_style_val(dim_style);

}
void init_dim_lead(dlhml::Lead_Dimension &seed)
{
	init_dim<dlhml::Lead_Dimension>(seed);
	


}
void init_dim_text(dlhml::Text_Dimension &seed)
{
	init_dim<dlhml::Text_Dimension>(seed);
	


}

void init_dim_lead_info(dlhml::Lead_Dimension_Info &seed)
{
	init_dim<dlhml::Lead_Dimension_Info>(seed);
}
void init_dim_text_info(dlhml::Text_Dimension_Info &seed)
{
	init_dim<dlhml::Text_Dimension_Info>(seed);
}


void init_ln_dim(dlhml::Ln_Dim &seed)
{
	init_dim<dlhml::Ln_Dim>(seed);
}

void init_angle_dim(dlhml::Angle_Dimension &seed)
{
	init_dim<dlhml::Angle_Dimension>(seed);
	
}
void init_radius_dim(dlhml::Radius_Dimension &seed)
{
	init_dim<dlhml::Radius_Dimension>(seed);


}



void set_brush_prop(Entitys &ents,Brush_Prop &brush_prop)
{
	for(int i=0;i<ents.size();i++){
//		if(ents[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
//
//		}//else if(ents[])
	}
}