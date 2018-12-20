// Cmd_Select_Joint.cpp: implementation of the Cmd_Select_Joint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Cmd_Select_Joint.h"


#include "Global.h"
#include "DB_View.h"
#include "Circle.h"
#include "Dlg_Joint_DB.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace dlhml;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Cmd_Select_Joint::Cmd_Select_Joint(dlhml::Scene& scene):Create_Entity(scene)
{
	dlg = NULL;
}

Cmd_Select_Joint::~Cmd_Select_Joint()
{
	dlg = NULL;
}

void Cmd_Select_Joint::xor_select_rect()
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

void Cmd_Select_Joint::get_select_ents(Entitys &ents) 
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
void Cmd_Select_Joint::mouse_move_p(UINT nFlags, const dlhml::Point& pt)
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

void Cmd_Select_Joint::show_joint_info(Entitys &texts) 
{
	if(texts.size()==0)
		return;
	//DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(texts);
	std::string name = ((Text*)texts[0])->text();
//	AfxMessageBox(name.c_str());
	
		
	if (dlg){
		if (!dlg->dlg_is_have())
		{
			dlg = new Dlg_Joint_DB();
			dlg->set_sel_name(name.c_str());
			dlg->Create(IDD_DLG_JOINT_DB);
			dlg->ShowWindow(SW_SHOW);
			dlg->init_sel();
		}
	
	}
	else
		{
			dlg = new Dlg_Joint_DB();
			dlg->set_sel_name(name.c_str());
			dlg->Create(IDD_DLG_JOINT_DB);
			dlg->ShowWindow(SW_SHOW);
			dlg->init_sel();
		}

}
void Cmd_Select_Joint::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
{
	++step_;
	Entitys texts;
	switch(step_)
	{
	case 1:
		begin_ = end_ = pt;
		break;
	case 2:
		end_ = pt;
		xor_select_rect();
		get_select_ents(sel_ents_);		
		get_texts(DB_View::instance()->database(),sel_ents_,texts);
		show_joint_info(texts);		
		step_=0;
		break;
	default:
		break;
	}
	

}

BOOL Cmd_Select_Joint::get_message()
{
	if (dlg)
		return dlg->dlg_is_have();
	else
		return false;
	 
}
