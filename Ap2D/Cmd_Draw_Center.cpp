// Cmd_Draw_Center.cpp: implementation of the Cmd_Draw_Center class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Cmd_Draw_Center.h"
#include "Global.h"
#include "DB_View.h"
#include "Line_Arrow.h"
#include "Line.h"

#include "cbk.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace dlhml;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Cmd_Draw_Center::Cmd_Draw_Center(dlhml::Scene& scene):Create_Entity(scene)
{
  command_line_output("Please select first point.");

}

Cmd_Draw_Center::~Cmd_Draw_Center()
{

}

void Cmd_Draw_Center::clear_temp_lines()
{
	for(int i=0;i<temp_ids_.size();i++){
	  DB_View::instance()->database()->erase_entity(temp_ids_[i]);

	}

}
void Cmd_Draw_Center::draw_center_point()
{
	Point p1 = pts_[0];
	Point p2 = pts_[1];
	Point p3 = pts_[2];

	double u1=((p2.x*p2.x)-(p1.x*p1.x)+(p2.y*p2.y)- (p1.y*p1.y))/2.0f;
	double u2=((p3.x*p3.x)-(p1.x*p1.x)+(p3.y*p3.y)- (p1.y*p1.y))/2.0f;

	double d11= p2.x-p1.x;
	double d12= p2.y-p1.y;
	double d21= p3.x-p1.x;
	double d22= p3.y-p1.y;

	double x0 = ((u1*d22)-(u2*d12))/((d11*d22)-(d21*d12));
	double y0 = ((u2*d11)-(u1*d21))/((d11*d22)-(d21*d12));


	Point mid(x0,y0);
	
	double len = 3.0;
	Point pt1(mid.x-len,mid.y+len),pt2(mid.x+len,mid.y-len),pt3(mid.x-len,mid.y-len),pt4(mid.x+len,mid.y+len);

	dlhml::Line *ln = dlhml::Line::create_me();
	ln->setdata(pt1,pt2);
	ln->color_index(3);
	Entity_ID id;
	ln->post2db(*DB_View::instance()->database(),id);

	dlhml::Line *ln2 = dlhml::Line::create_me();
	ln2->setdata(pt3,pt4);
	ln2->color_index(3);
	ln2->post2db(*DB_View::instance()->database(),id);



	pts_.clear();
	clear_temp_lines();

	DB_View::instance()->cur_view()->scene()->invalidate();

}
void Cmd_Draw_Center::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
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
		//获取框内选中的点
		select_point();

	
		if(pts_.size()==3){
			draw_center_point();
			command_line_output("Create middle OK.Please select the first point:");
			step_ = 0;
		}else{
			command_line_output("Please select the second point:");
			step_ = 0;
		}
		break;
	default:
		break;
	}
	

}

void Cmd_Draw_Center::right_button_down_p(UINT nFlags, const dlhml::Point& pt)
{

}
//***选中辅助功能代码***************************************************************

void Cmd_Draw_Center::mouse_move_p(UINT nFlags, const dlhml::Point& pt)
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

void Cmd_Draw_Center::get_select_ents(Entitys &ents) 
{
	ents.clear();
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
void Cmd_Draw_Center::xor_select_rect()
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
void Cmd_Draw_Center::draw_corss(const dlhml::Point &pt)
{	
	double len = 3.0;
	Point pt1(pt.x-len,pt.y+len),pt2(pt.x+len,pt.y-len),pt3(pt.x-len,pt.y-len),pt4(pt.x+len,pt.y+len);

	dlhml::Line *ln = dlhml::Line::create_me();
	ln->setdata(pt1,pt2);
	ln->color_index(1);
	Entity_ID id;
	ln->post2db(*DB_View::instance()->database(),id);
	temp_ids_.push_back(id);
	
	dlhml::Line *ln2 = dlhml::Line::create_me();
	ln2->setdata(pt3,pt4);
	ln2->color_index(1);
	ln2->post2db(*DB_View::instance()->database(),id);
	temp_ids_.push_back(id);


}
void Cmd_Draw_Center::add_pt(const dlhml::Point &pt)
{
	for(int i=0;i<pts_.size();i++){
		if(pts_[i] == pt)
			return ;
	}
	pts_.push_back(pt);

	draw_corss(pt);

}

void Cmd_Draw_Center::deal_lines_pt(Entitys &lines)
{
	//判断选中的线，那些点再选择框中。
	Rect rect;
	rect.setdata(begin_,end_);
	for(int i=0;i<lines.size();i++){
		Line *ln = (Line *)lines[i];		
		Point st = ln->start();
		Point ed = ln->end();
		if(st.envelop(rect)){
			add_pt(st);
		}else if(ed.envelop(rect)){
			add_pt(ed);
		}
	}
}
void Cmd_Draw_Center::deal_arrow_lines_pt(Entitys &arrow_lines)
{
	//判断选中的线，那些点再选择框中。
	Rect rect;
	rect.setdata(begin_,end_);
	for(int i=0;i<arrow_lines.size();i++){
		Line_Arrow *ln = (Line_Arrow *)arrow_lines[i];		
		Point st = ln->start();
		Point ed = ln->end();
		if(st.envelop(rect)){
			add_pt(st);
		}else if(ed.envelop(rect)){
			add_pt(ed);
		}
	}
}
void Cmd_Draw_Center::select_point()
{
	get_select_ents(sel_ents_);	
	Entitys lines,ln_arrows;
	get_lines(scene_.database(),sel_ents_,lines);
	get_line_arrows(scene_.database(),sel_ents_,ln_arrows);

	deal_lines_pt(lines);
	deal_arrow_lines_pt(ln_arrows);
	
	

	DB_View::instance()->cur_view()->scene()->invalidate();
	
}
//***选中辅助功能代码***************************************************************






