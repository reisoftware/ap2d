// Create_Dim_Axis_Dimension.cpp: implementation of the Create_Dim_Axis_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Create_Dim_Axis_Dimension.h"

#include "Scene_d.h"
#include "Line.h"
#include "Paint_Entity.h"
#include "Painter_Windows.h"

#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Block.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Create_Dim_Axis_Dimension::Create_Dim_Axis_Dimension(Scene& scene)
:Create_Entity(scene)
MCT_INIT2("Create_Dim_Axis_Dimension")
{
  create_text_=true;
	group_ents_ = NULL;;
}

Create_Dim_Axis_Dimension::~Create_Dim_Axis_Dimension()
{

}
void Create_Dim_Axis_Dimension::mouse_move_p(UINT nFlags, const Point& pt)
{
	switch(step_)
	{
	case 0:
		begin_ = pt;
		get_snap_point(begin_);
		break;
	case 1:
		xor_draw();
		end_ = pt;
		get_ortho_point(begin_,end_);
		get_snap_point(end_);
		xor_draw();
		break;
	default:
		break;
	}
}
void Create_Dim_Axis_Dimension::left_button_down_p(UINT nFlags, const Point& pt)
{
	++step_;
	switch(step_)
	{
	case 1:
		begin_ = pt;
		get_snap_point(begin_);
		//判断是否在块内
		scene_.database()->select_group(group_ents_,begin_);
		end_ = begin_;
		break;
	case 2:
		end_ = pt;
		get_ortho_point(begin_,end_);
		get_snap_point(end_);
		
		add_dim();
		scene_.invalidate();
		step_ = 0;
		break;
	default:
		break;
	}
}
void Create_Dim_Axis_Dimension::right_button_up_p(UINT nFlags, const Point& pt)
{
	switch(step_)
	{
	case 1:
		step_ = 0;
		xor_draw();
		scene_.idle_command();
		//scene_.idle_command(this);
		break;
	default:
		break;
	}
}
void Create_Dim_Axis_Dimension::xor_draw_p(Draw_Entity& paint)
{
	Lead_Dimension dim;
	dim.start(begin_);
	dim.text_position(end_);
	dim.dim_text("C");
	dim.text_position(end_);
//	dim.is_axis(true);
	dim.color(scene_.entity_color());
	dim.xor_draw(paint);
}
void Create_Dim_Axis_Dimension::add_dim()
{
	Lead_Dimension*	pDim = Lead_Dimension::create_me();
	pDim->start(begin_);
	pDim->text_position(end_);
	pDim->dim_text("C");
	pDim->text_position(end_);
  pDim->align_point(Text::center_center);
  pDim->dim_style_val().text_pos(Dimension_Style::CENTER);
	pDim->color(scene_.entity_color());
	Entity_ID id;
	pDim->post2db(*scene_.database(),id);
	//添加到块
  //
	if(group_ents_)
		group_ents_->push_back(pDim);
}

}
