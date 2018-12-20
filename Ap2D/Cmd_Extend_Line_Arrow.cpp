
#include "stdafx.h"
#include "ap2d.h"
#include "Cmd_Extend_Line_Arrow.h"

#include "Global.h"
#include "DB_View.h"
#include "Circle.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
using namespace dlhml;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Cmd_Extend_Line_Arrow::Cmd_Extend_Line_Arrow(dlhml::Scene& scene):Create_Entity(scene)
{
}

Cmd_Extend_Line_Arrow::~Cmd_Extend_Line_Arrow()
{
}

void Cmd_Extend_Line_Arrow::xor_select_rect()
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

void Cmd_Extend_Line_Arrow::get_select_ents(Entitys &ents) 
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
void Cmd_Extend_Line_Arrow::mouse_move_p(UINT nFlags, const dlhml::Point& pt)
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
void Cmd_Extend_Line_Arrow::intersect_lines(dlhml::Line_Arrow *ln,std::vector<Point> &pts)
{
	Entitys lines;
	get_line_arrows(DB_View::instance()->database(),lines);
	for(int i=0;i<lines.size();i++){
		dlhml::Line_Arrow *new_ln = (dlhml::Line_Arrow *)lines[i];
		if(ln != new_ln){
			Point pt;
			Line lll;
			new_ln->getdata(lll);
			ln->intersect(lll,pts);
		}
	
	}
}

void Cmd_Extend_Line_Arrow::draw_pts(const std::vector<dlhml::Point> &pts)
{
	for(int i=0;i<pts.size();i++){
		dlhml::Circle *cir = dlhml::Circle::create_me();
		cir->center(pts[i]);
		cir->radius(3);
		cir->color_index(5);
		Entity_ID id;
		cir->post2db(*DB_View::instance()->database(),id);
		ids_.push_back(id);
		DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(cir);

	}
}
void Cmd_Extend_Line_Arrow::create_extend_lines()
{
	Entitys lines;
	get_line_arrows(DB_View::instance()->database(),sel_ents_,lines);
	double dis = 3;
	for(int i=0;i<lines.size();i++){
		dlhml::Line_Arrow * ln_ = (Line_Arrow *)lines[i]->clone();
		ln_->color_index(5);
		Entity_ID id;
		ln_->post2db(*DB_View::instance()->database(),id);
		ids_.push_back(id);
		Rect box;
		DB_View::instance()->database()->all_entity_rect(box);
		Line l1,l2,l3,l4;
		l1.start(Point(box.xmin()-dis,box.ymax(),0));
		l1.end(Point(box.xmin()-dis,box.ymin(),0));
		ln_->extend(l1);
		l2.start(Point(box.xmin(),box.ymax()+dis,0));
		l2.end(Point(box.xmax(),box.ymax()+dis,0));
		ln_->extend(l2);
		l3.start(Point(box.xmax()+dis,box.ymax(),0));
		l3.end(Point(box.xmax()+dis,box.ymin(),0));
		ln_->extend(l3);
		l4.start(Point(box.xmin(),box.ymin()-dis,0));
		l4.end(Point(box.xmax(),box.ymin()-dis,0));
		ln_->extend(l4);

		DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(ln_);
		std::vector<Point> pts;
		intersect_lines(ln_,pts);
		draw_pts(pts);

	}

}

void Cmd_Extend_Line_Arrow::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
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
		get_select_ents(sel_ents_);
		
		create_extend_lines();
		

		
		
		step_=0;
		break;
	default:
		break;
	}
	

}
void Cmd_Extend_Line_Arrow::right_button_down_p(UINT nFlags, const dlhml::Point& pt)
{
	DB_View::instance()->cur_view()->scene()->get_idle()->clear_selected();
	for(int i=0;i<ids_.size();i++){
		DB_View::instance()->database()->erase_entity(ids_[i]);
	}
	ids_.clear();

}

