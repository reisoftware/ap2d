// Cmd_Select_Text.cpp: implementation of the Cmd_Select_Text class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Cmd_Select_Text.h"
#include "Global.h"
#include "DB_View.h"
#include "Dlg_Select_Color.h"
#include "cbk.h"
#include "Dlg_Tip_Infoes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


using namespace dlhml;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cmd_Select_Text::Cmd_Select_Text(dlhml::Scene& scene):Create_Entity(scene)
{
	Global::instance()->rignt_but_exit() = 0;
}

Cmd_Select_Text::~Cmd_Select_Text()
{
	Global::instance()->rignt_but_exit() = 1;
}

void Cmd_Select_Text::mouse_move_p(UINT nFlags, const dlhml::Point& pt)
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

void Cmd_Select_Text::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
{
	++step_;
	switch(step_)
	{
	case 1:
		begin_ = end_ = pt;
		//xor_select_rect();
		select_entity();
		step_=0;
		break;
	case 2:
		break;
	default:
		break;
	}
	

}
void Cmd_Select_Text::right_button_down_p(UINT nFlags, const dlhml::Point& pt)
{

}
void Cmd_Select_Text::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}
void Cmd_Select_Text::middle_button_down_p(UINT nFlags, const dlhml::Point& pt)
{
		begin_ = end_ = pt;
	change_error();
	//Dlg_Tip_Infoes dlg;
	//if(dlg.DoModal()== IDOK){
	//	CString str = dlg.get_str();
	//}
	step_=0;	

	

}
void Cmd_Select_Text::left_button_dblclk_p(UINT nFlags, const dlhml::Point& pt)
{
}
void Cmd_Select_Text::xor_select_rect()
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
void Cmd_Select_Text::get_select_ents(Entitys &ents) 
{
	sel_ents_.clear();
	Rect rect;

	Point left_top,right_down;
	double dis = 2;
	left_top.x = begin_.x - dis;
	left_top.y = begin_.y + dis;
	left_top.z = begin_.z;
	right_down.x = begin_.x + dis;
	right_down.y = begin_.y - dis;
	right_down.z = begin_.z;

	//rect.setdata(begin_,end_);
	rect.setdata(left_top,right_down);
	EntityIDArray ids;
	entity_iterator iter = scene_.database()->entity_begin();
	for(; iter!=scene_.database()->entity_end();++iter){
			if((*iter)->intersect(rect) || (*iter)->envelop(rect))
				ents.push_back(*iter);
/*
		if(left_top.x > right_down.x){
			if((*iter)->intersect(rect) || (*iter)->envelop(rect))
				ents.push_back(*iter);
		}else{
			if((*iter)->envelop(rect))
				ents.push_back(*iter);
		}

	*/
	}	

}


void Cmd_Select_Text::change_error()
{
	get_select_ents(sel_ents_);	
	Entitys texts,equ_txt_texts;
	get_texts(scene_.database(),sel_ents_,texts);

	int color = 1,color_error = 1,color_no2 = 1;
	if(texts.size() >0){
		dlhml::Text *txt = (dlhml::Text *)texts[0];
		Global::instance()->cur_val().sel_color_prop_.cur_txt_group_ = txt->group();
		Global::instance()->cur_val().sel_color_prop_.cur_txt_val_ = txt->text();


		//是否弹出颜色设置

		if(afc::with_ctrl() || !Global::instance()->cur_val().sel_color_prop_.is_rember_color_){
			Dlg_Select_Color dlg;
			if(dlg.DoModal() == IDOK){
				color = dlg.get_color();
				color_error = dlg.get_error_color();
				color_no2 = dlg.get_color_no2();
			}
		}else{
			color = Global::instance()->cur_val().sel_color_prop_.cur_color_one_;
			color_error = Global::instance()->cur_val().sel_color_prop_.cur_color_error_;
			color_no2 = Global::instance()->cur_val().sel_color_prop_.cur_color_two_;
		}
		
		if(Global::instance()->cur_val().cur_select_text_ == true){
			//show_ents(scene_.database(),txt->text(),equ_txt_texts);
			change_color(sel_ents_,color_error,color_no2);
			print_info(sel_ents_);			
			scene_.get_idle()->set_xor(sel_ents_);

		}else{
			show_ents(scene_.database(),txt->text(),equ_txt_texts);
			change_color(equ_txt_texts,color_error,color_no2);
			print_info(equ_txt_texts);
			
			scene_.get_idle()->set_xor(equ_txt_texts);

		}
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
	
}


void Cmd_Select_Text::select_entity()
{
	get_select_ents(sel_ents_);	
	Entitys texts,equ_txt_texts;
	get_texts(scene_.database(),sel_ents_,texts);
	int color = 1,color_no2 = 1;
	if(texts.size() >0){
		dlhml::Text *txt = (dlhml::Text *)texts[0];
		Global::instance()->cur_val().sel_color_prop_.cur_txt_group_ = txt->group();
		Global::instance()->cur_val().sel_color_prop_.cur_txt_val_ = txt->text();


		//是否弹出颜色设置

		if(afc::with_ctrl() || !Global::instance()->cur_val().sel_color_prop_.is_rember_color_){
			Dlg_Select_Color dlg;
			if(dlg.DoModal() == IDOK){
				color = dlg.get_color();
				color_no2 = dlg.get_color_no2();
			}
		}else{
			color = Global::instance()->cur_val().sel_color_prop_.cur_color_one_;
			color_no2 = Global::instance()->cur_val().sel_color_prop_.cur_color_two_;
		}
		
		if(Global::instance()->cur_val().cur_select_text_ == true){
			//show_ents(scene_.database(),txt->text(),equ_txt_texts);
			change_color(sel_ents_,color,color_no2);
			print_info(sel_ents_);			
			scene_.get_idle()->set_xor(sel_ents_);

		}else{
			show_ents(scene_.database(),txt->text(),equ_txt_texts);
			change_color(equ_txt_texts,color,color_no2);
			print_info(equ_txt_texts);
			
			scene_.get_idle()->set_xor(equ_txt_texts);

		}
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
	
}
