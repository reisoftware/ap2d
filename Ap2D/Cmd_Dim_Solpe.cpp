// Cmd_Dim_Solpe.cpp: implementation of the Cmd_Dim_Solpe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Cmd_Dim_Solpe.h"

#include "Global.h"
#include "DB_View.h"
#include "Line_Arrow.h"
#include "Line.h"

#include "cbk.h"
#include "Normal.h"
#include "format.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace dlhml;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Cmd_Dim_Solpe::Cmd_Dim_Solpe(dlhml::Scene& scene):Create_Entity(scene)
{
  command_line_output("Please select first point.");

}

Cmd_Dim_Solpe::~Cmd_Dim_Solpe()
{

}


void Cmd_Dim_Solpe::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
{
	++step_;

	switch(step_)
	{
	case 1:
		begin_ = end_ = pt;
		break;
	case 2:
		end_ = cur_pt_ = pt;
	
		xor_90_side();
		break;
	case 3:
		create_dim(pt);
		DB_View::instance()->cur_view()->scene()->invalidate();
		
	default:
		break;
	}
	

}

void Cmd_Dim_Solpe::right_button_down_p(UINT nFlags, const dlhml::Point& pt)
{

}

void Cmd_Dim_Solpe::mouse_move_p(UINT nFlags, const dlhml::Point& pt)
{
	switch(step_)
	{
	case 2:
		xor_90_side();
		cur_pt_ = pt;
		xor_90_side();
		break;
	case 3:
		xor_lean_side_move();
		cur_pt_ = pt;
		xor_lean_side_move();
		break;
	default:
		break;
	}
}
void Cmd_Dim_Solpe::xor_lean_side_move()
{

}

std::string Cmd_Dim_Solpe::get_lean_value(double base,double len_one,double len_two)
{
	std::string str;
	double len = (base *len_two)/len_one;
	str = afc::format(len,0,0,false);

	return str;
}

void Cmd_Dim_Solpe::xor_90_side()
{
	dlhml::Painter* painter = scene_.get_painter();
	dlhml::Paint_Entity paint(scene_,*painter);


	dlhml::Line line;
	line.setdata(begin_,end_);
	dlhml::Point perp_pt = line.perpendicular(cur_pt_);

	dlhml::Line line_perp;
	line_perp.setdata(cur_pt_,perp_pt);
	line_perp.xor_draw(paint);



	//第一条边的文字	
	dlhml::Text t_first;
	dlhml::Point mid_first = line_perp.middle();
	t_first.position(mid_first);
	
	
	double angle=0.0;
    dlhml::Normal nor;    
	nor.set_data(cur_pt_,perp_pt);
	normal2d_2_radian(nor,angle);
	t_first.rotation(angle);
	t_first.text("100");

	float k = (cur_pt_.y - perp_pt.y) / (cur_pt_.x - perp_pt.x);
	float b = perp_pt.y - k * perp_pt.x;
	if(cur_pt_.y > (k*cur_pt_.x + b) )
		t_first.align_point(dlhml::Text::center_bottom);
	else
		t_first.align_point(dlhml::Text::center_top);
	t_first.xor_draw(paint);



	//第二条边	
	dlhml::Line line_first;
	line_first.setdata(begin_,perp_pt);
	line_first.xor_draw(paint);


	//第二条边的文字	
	dlhml::Text t_second;
	dlhml::Point mid_second = line_first.middle();
	t_second.position(mid_second);


	nor.set_data(perp_pt,begin_);
	normal2d_2_radian(nor,angle);
	t_second.rotation(angle);

	std::string val = get_lean_value(100,line_perp.length(),line_first.length());
	t_second.text(val);

	t_second.align_point(dlhml::Text::center_bottom);

	t_second.xor_draw(paint);


	//斜边
	dlhml::Line line_lean;
	line_lean.setdata(cur_pt_,begin_);
	line_lean.xor_draw(paint);

}

//	Float k = (ln.pt2.y - ln.pt1.y) / (ln.pt2.x - ln.pt1.x);
//	Float b = ln.pt1.y - k * ln.pt1.x;

void Cmd_Dim_Solpe::create_dim(const dlhml::Point &lean_point)
{
	dlhml::Line line ;
	line.setdata(begin_,end_);
	dlhml::Point perp_pt = line.perpendicular(lean_point);

	//第一条直角边
	dlhml::Line *line_perp = dlhml::Line::create_me();
	line_perp->setdata(lean_point,perp_pt);
	Entity_ID id;
	line_perp->post2db(*DB_View::instance()->database(),id);



	//第一条边的文字	
	dlhml::Text *t_first = dlhml::Text::create_me();
	dlhml::Point mid_first = line_perp->middle();
	t_first->position(mid_first);	
	double angle=0.0;
    dlhml::Normal nor;    
	nor.set_data(lean_point,perp_pt);

/*
   if(lean_point.x > perp_pt.x)
	   nor.set_data(lean_point,perp_pt);
	else
	   nor.set_data(perp_pt,lean_point);
*/    
	normal2d_2_radian(nor,angle);
	t_first->rotation(angle);
	
	t_first->text("100");


	float k = (lean_point.y - perp_pt.y) / (lean_point.x - perp_pt.x);
	float b = perp_pt.y - k * perp_pt.x;
	if(lean_point.y > (k*lean_point.x + b) )
		t_first->align_point(dlhml::Text::center_bottom);
	else
		t_first->align_point(dlhml::Text::center_top);


	t_first->post2db(*DB_View::instance()->database(),id);
	

	//第二条边	
	dlhml::Line *line_first = dlhml::Line::create_me();
	line_first->setdata(begin_,perp_pt);
	line_first->post2db(*DB_View::instance()->database(),id);


	//第二条边的文字	
	dlhml::Text *t_second = dlhml::Text::create_me();
	dlhml::Point mid_second = line_first->middle();
	t_second->position(mid_second);
   
	
	nor.set_data(perp_pt,begin_);
	normal2d_2_radian(nor,angle);
	t_second->rotation(angle);


	std::string val = get_lean_value(100,line_perp->length(),line_first->length());
	t_second->text(val);
	
	t_second->align_point(dlhml::Text::center_bottom);
	t_second->post2db(*DB_View::instance()->database(),id);



	//斜边
	dlhml::Line *line_lean = dlhml::Line::create_me();
	line_lean->setdata(lean_point,begin_);
	line_lean->post2db(*DB_View::instance()->database(),id);

}








