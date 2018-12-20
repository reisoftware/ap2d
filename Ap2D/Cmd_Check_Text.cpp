// Cmd_Check_Text.cpp: implementation of the Cmd_Check_Text class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Cmd_Check_Text.h"
#include "Global.h"
#include "DB_View.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace dlhml;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cmd_Check_Text::Cmd_Check_Text(dlhml::Scene& scene):Create_Entity(scene)
{
	Global::instance()->rignt_but_exit() = 0;
}

Cmd_Check_Text::~Cmd_Check_Text()
{
	Global::instance()->rignt_but_exit() = 1;
}

void Cmd_Check_Text::mouse_move_p(UINT nFlags, const dlhml::Point& pt)
{
	switch(step_)
	{
	case 1:
		xor_select_rect();
		end_ = pt;
		xor_select_rect();
		break;
	default:
		break;
	}
}

void Cmd_Check_Text::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
{
	++step_;
	switch(step_)
	{
	case 1:
		begin_ = end_ = pt;
		break;
	case 2:
		end_ = pt;
		xor_select_rect();
		select_entity();
		step_=0;
		break;
	default:
		break;
	}
	

}
void Cmd_Check_Text::right_button_down_p(UINT nFlags, const dlhml::Point& pt)
{

}
void Cmd_Check_Text::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}
void Cmd_Check_Text::middle_button_down_p(UINT nFlags, const dlhml::Point& pt)
{

	

}
void Cmd_Check_Text::left_button_dblclk_p(UINT nFlags, const dlhml::Point& pt)
{
	
}
void Cmd_Check_Text::xor_select_rect()
{
	dlhml::Painter* painter = scene_.get_painter();
	dlhml::Paint_Entity paint(scene_,*painter);

	dlhml::Line line;
	if(begin_.x > end_.x)
		line.line_style("dot");
	line.setdata(dlhml::Point(begin_.x,begin_.y),dlhml::Point(end_.x,begin_.y));
	line.xor_draw(paint);
	line.setdata(dlhml::Point(end_.x,begin_.y),dlhml::Point(end_.x,end_.y));
	line.xor_draw(paint);
	line.setdata(dlhml::Point(end_.x,end_.y),dlhml::Point(begin_.x,end_.y));
	line.xor_draw(paint);
	line.setdata(dlhml::Point(begin_.x,end_.y),dlhml::Point(begin_.x,begin_.y));
	line.xor_draw(paint);
}
void Cmd_Check_Text::get_select_ents(Entitys &ents) 
{
	sel_ents_.clear();
	Rect rect;
	rect.setdata(begin_,end_);
	EntityIDArray ids;
	entity_iterator iter = scene_.database()->entity_begin();
	for(; iter!=scene_.database()->entity_end();++iter){
		if(begin_.x > end_.x){
			if((*iter)->intersect(rect) || (*iter)->envelop(rect))
				ents.push_back(*iter);
		}else{
			if((*iter)->envelop(rect))
				ents.push_back(*iter);
		}
	}	

}



void Cmd_Check_Text::select_entity()
{
	DB_View::instance()->cur_view()->scene()->invalidate();
	
}

