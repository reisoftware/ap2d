// Edit_Rectentity.cpp: implementation of the Edit_Rectentity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Edit_Rectentity.h"
/*
#include "Scene_d.h"
#include "Painter.h"
#include "myalgorithm.h"
#include "Paint_Entity.h"
#include "Rectentity.h"
#include <cassert>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Edit_Rectentity::Edit_Rectentity(Scene& scene,Rectentity& rectEnt)
:Create_Entity(scene),rectEnt_(rectEnt)
{
//	b_drag_lb_ = false;
//	b_drag_lt_ = false;
//	b_drag_rt_ = false;
//	b_drag_rb_ = false;	init_flag();
	paint_selected();
}

Edit_Rectentity::~Edit_Rectentity()
{

}
void Edit_Rectentity::paint_selected()
{
	Painter* painter = scene_.get_painter();
	Paint_Entity paint(scene_,*painter);
	xor_draw_rect_four_pts(rectEnt_,paint);
}
void Edit_Rectentity::get_rect(const Point& pt,Rect& rc)
{
	Float len = pick_rect_edge_length() * scene_.screen_to_world().value(0,0);
	rc.xmin(pt.x-len);
	rc.xmax(pt.x+len);
	rc.ymin(pt.y-len);
	rc.ymax(pt.y+len);
}
void Edit_Rectentity::mouse_move_p(UINT nFlags, const Point& pt)
{
	switch(step_)
	{
	case 1:
		xor_draw();
		cur_ = pt;
		xor_draw();
		break;
	default:
		break;
	}
}
void Edit_Rectentity::left_button_down_p(UINT nFlags, const Point& pt)
{
	Rect lb_Rect,lt_Rect,rt_Rect,rb_Rect;
	Point leftBottom,leftTop,RightTop,RightBottom;	
	switch(++step_)
	{
	case 1:
		get_rect_four_pts(rectEnt_.rect(),leftBottom,leftTop,RightTop,RightBottom);	
		cur_ = pt;
		begin_ = leftTop;
		get_rect(leftBottom,lb_Rect);
		get_rect(leftTop,lt_Rect);
		get_rect(RightTop,rt_Rect);
		get_rect(RightBottom,rb_Rect);
		if(pt.envelop(lb_Rect)){
			b_drag_lb_ = true;
		}else if(pt.envelop(lt_Rect)){
			b_drag_lt_ = true;
		}else if(pt.envelop(rt_Rect)){
			b_drag_rt_ = true;
		}else if(pt.envelop(rb_Rect)){
			b_drag_rb_ = true;
		}else{ 
			step_ = 0;
		}
		break;
	case 2:
		moved_rect_ = rectEnt_.rect();
		moved_pt_ = end_ = cur_ = pt;
		xor_draw();
		drag_rect();
		scene_.invalidate();
		scene_.idle_command();
		break;
	default:
		break;
	}
}
void Edit_Rectentity::drag_rect()
{
	Painter* painter = scene_.get_painter();
	Paint_Entity paint(scene_,*painter);
	paint.xor_draw_rectentity(rectEnt_);
	Rect renew;
	renew = get_new_rect(rectEnt_.rect(),end_);
	rectEnt_.rect(renew);
	paint.draw_rectentity(rectEnt_);
}
void Edit_Rectentity::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(step_)
	{
	case 0:
		if(vk_.esc()){
			xor_draw();
			scene_.info_to_command_line("exit edit rectangle",true);
			scene_.idle_command();
		}
		if(vk_.enter()){
			scene_.info_to_command_line("",true);
			scene_.info_to_command_line("no datum mark",true);
		}
		break;
	case 1:
		if(vk_.esc()){
			xor_draw();
			scene_.info_to_command_line("exit edit line",true);
			scene_.idle_command();
		}
		if(vk_.enter()){
			if(get_command_line_point(end_)){
				moved_rect_ = rectEnt_.rect();
				moved_pt_ = end_;
				xor_draw();
				drag_rect();
				scene_.idle_command();
			}	
			scene_.info_to_command_line("",true);
		}
		break; 
	default:
		break;
	}
}
void Edit_Rectentity::right_button_up_p(UINT nFlags, const Point& pt)
{
	scene_.idle_command();
}
void Edit_Rectentity::left_button_dblclk_p(UINT nFlags, const Point& pt)
{
	Edit_Entity* edit = scene_.get_edit_entity_dlg();
	assert(edit);
	edit->edit_rectentity(rectEnt_);
	scene_.invalidate();
}
void Edit_Rectentity::xor_draw_p(Draw_Entity& paint)
{	
//	xor_draw_rect_four_pts(rectEnt_,paint);
//	paint.xor_draw_rectentity(rectEnt_);
//	Rect rectNew = get_new_rect(rectEnt_,cur_);
//	rectEnt_

	Rectentity recttemp = rectEnt_;
	Rect reNew,rectOld = recttemp.rect();
	xor_draw_rect_four_pts(recttemp,paint);
	paint.xor_draw_rectentity(recttemp);
	reNew = get_new_rect(rectOld,cur_);
	recttemp.rect(reNew);
	paint.xor_draw_rectentity(recttemp);

	xor_draw_rect_four_pts(recttemp,paint);
}
Rect Edit_Rectentity::get_new_rect(const Rect& rectOld,const Point& ptMove)
{
	Rect reNew;
	Float xmax,xmin,ymax,ymin;
	if (b_drag_lb_) {
		xmin = rectOld.xmax() < ptMove.x ? rectOld.xmax() : ptMove.x;
		xmax = rectOld.xmax() > ptMove.x ? rectOld.xmax() : ptMove.x;
		ymin = rectOld.ymax() < ptMove.y ? rectOld.ymax() : ptMove.y;
		ymax = rectOld.ymax() > ptMove.y ? rectOld.ymax() : ptMove.y;
	}
	else if (b_drag_lt_) {
		xmin = rectOld.xmax() < ptMove.x ? rectOld.xmax() : ptMove.x;
		xmax = rectOld.xmax() > ptMove.x ? rectOld.xmax() : ptMove.x;
		ymin = rectOld.ymin() < ptMove.y ? rectOld.ymin() : ptMove.y;
		ymax = rectOld.ymin() > ptMove.y ? rectOld.ymin() : ptMove.y;
	}
	else if (b_drag_rb_) {
		xmin = rectOld.xmin() < ptMove.x ? rectOld.xmin() : ptMove.x;
		xmax = rectOld.xmin() > ptMove.x ? rectOld.xmin() : ptMove.x;
		ymin = rectOld.ymax() < ptMove.y ? rectOld.ymax() : ptMove.y;
		ymax = rectOld.ymax() > ptMove.y ? rectOld.ymax() : ptMove.y;
	}
	else if (b_drag_rt_) {
		xmin = rectOld.xmin() < ptMove.x ? rectOld.xmin() : ptMove.x;
		xmax = rectOld.xmin() > ptMove.x ? rectOld.xmin() : ptMove.x;
		ymin = rectOld.ymin() < ptMove.y ? rectOld.ymin() : ptMove.y;
		ymax = rectOld.ymin() > ptMove.y ? rectOld.ymin() : ptMove.y;
	}
	reNew.xmax(xmax);
	reNew.xmin(xmin);
	reNew.ymax(ymax);
	reNew.ymin(ymin);
//	
//	Rect reNew;
//	if(b_drag_lb_){
//		reNew.xmax(rectOld.xmax());
//		reNew.ymax(rectOld.ymax());
//		reNew.xmin(ptMove.x);
//		reNew.ymin(ptMove.y);
//	}else if(b_drag_lt_){
//		reNew.xmax(rectOld.xmax());
//		reNew.ymin(rectOld.ymin());
//		reNew.xmin(ptMove.x);
//		reNew.ymax(ptMove.y);
//	}else if(b_drag_rt_){
//		reNew.xmin(rectOld.xmin());
//		reNew.ymin(rectOld.ymin());
//		reNew.xmax(ptMove.x);
//		reNew.ymax(ptMove.y);		
//	}else if(b_drag_rb_){
//		reNew.xmin(rectOld.xmin());
//		reNew.ymax(rectOld.ymax());
//		reNew.xmax(ptMove.x);
//		reNew.ymin(ptMove.y);		
//	}
	return reNew;
}
void Edit_Rectentity::xor_draw_rect_four_pts(const Rectentity& rectEnt,Draw_Entity& paint)
{
	Point leftBottom,leftTop,RightTop,RightBottom;
	Rect rc;
	get_rect_four_pts(rectEnt.rect(),leftBottom,leftTop,RightTop,RightBottom);
	get_rect(leftBottom,rc);
	paint.xor_draw_rect(rc);
	get_rect(leftTop,rc);
	paint.xor_draw_rect(rc);
	get_rect(RightTop,rc);
	paint.xor_draw_rect(rc);
	get_rect(RightBottom,rc);
	paint.xor_draw_rect(rc);
}
bool Edit_Rectentity::execute_p()
{
	Point lt_pt,lb_pt,rt_pt,rb_pt;
	Point temp_pt;
	get_rect_four_pts(moved_rect_,lb_pt,lt_pt,rt_pt,rb_pt);
	if (b_drag_lb_) {
		temp_pt = end_ = lb_pt;
	}
	else if (b_drag_lt_) {
		temp_pt = end_ = lt_pt;
	}
	else if (b_drag_rb_) {
		temp_pt = end_ = rb_pt;
	}
	else if (b_drag_rt_) {
		temp_pt = end_ = rt_pt;
	}	
	init_flag();
	get_rect_four_pts(rectEnt_.rect(),lb_pt,lt_pt,rt_pt,rb_pt);
	if (moved_pt_ == lb_pt)
		b_drag_lb_ = true;
	else if (moved_pt_ == lt_pt) 
		b_drag_lt_ = true;
	else if (moved_pt_ == rb_pt)
		b_drag_rb_ = true;
	else 
		b_drag_rt_ = true;
	moved_pt_ = temp_pt;
	
	moved_rect_ = rectEnt_.rect();
	drag_rect();
	scene_.idle_command();
	return true;
}
bool Edit_Rectentity::unexecute_p()
{
	Point lt_pt,lb_pt,rt_pt,rb_pt;
	Point temp_pt;
	get_rect_four_pts(moved_rect_,lb_pt,lt_pt,rt_pt,rb_pt);
	if (b_drag_lb_) {
		temp_pt = end_ = lb_pt;
	}
	else if (b_drag_lt_) {
		temp_pt = end_ = lt_pt;
	}
	else if (b_drag_rb_) {
		temp_pt = end_ = rb_pt;
	}
	else if (b_drag_rt_) {
		temp_pt = end_ = rt_pt;
	}	
	init_flag();
	get_rect_four_pts(rectEnt_.rect(),lb_pt,lt_pt,rt_pt,rb_pt);
	if (moved_pt_ == lb_pt)
		b_drag_lb_ = true;
	else if (moved_pt_ == lt_pt) 
		b_drag_lt_ = true;
	else if (moved_pt_ == rb_pt)
		b_drag_rb_ = true;
	else 
		b_drag_rt_ = true;
	moved_pt_ = temp_pt;
	
	moved_rect_ = rectEnt_.rect();
	drag_rect();
	scene_.idle_command();
	return true;
}
void Edit_Rectentity::get_rect_four_pts(const Rect& rect,Point& lb_pt,Point& lt_pt,Point& rt_pt,Point& rb_pt)
{
	lb_pt.setdata(rect.xmin(),rect.ymin());
	lt_pt.setdata(rect.xmin(),rect.ymax());
	rt_pt.setdata(rect.xmax(),rect.ymax());
	rb_pt.setdata(rect.xmax(),rect.ymin());
}
}
*/
