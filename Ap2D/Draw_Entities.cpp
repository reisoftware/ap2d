// Draw_Entities.cpp: implementation of the Draw_Entities class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Draw_Entities.h"
#include "Circle.h"

#include "DB_View.h"
#include "Rectentity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Draw_Entities::Draw_Entities()
{

}

Draw_Entities::~Draw_Entities()
{

}
void Draw_Entities::draw_circle(const dlhml::Point &center,int color,float r)
{
	dlhml::Circle *cir = dlhml::Circle::create_me();

	cir->color_index(color);
	cir->setdata(center,r);

	dlhml::Entity_ID id;
	cir->post2db(*DB_View::instance()->database(),id);

	DB_View::instance()->cur_view()->scene()->invalidate();	
}
void Draw_Entities::draw_rect(const dlhml::Point &center,int color,float r)
{
	dlhml::Rectentity *rc = dlhml::Rectentity::create_me();

	dlhml::Point left_top(center.x-r,center.y+r/2.0);
	dlhml::Point right_bottom(center.x+r,center.y-r/2.0);
	dlhml::Rect rc_temp;
	rc_temp.setdata(left_top,right_bottom);
	rc->color_index(color);
	rc->rect(rc_temp);


	
	dlhml::Entity_ID id;
	rc->post2db(*DB_View::instance()->database(),id);

	DB_View::instance()->cur_view()->scene()->invalidate();	
}

void Draw_Entities::draw_rect(const dlhml::Rect &rect,int color)
{
	dlhml::Rectentity *rc = dlhml::Rectentity::create_me();
	rc->color_index(color);
	rc->rect(rect);
	
	dlhml::Entity_ID id;
	rc->post2db(*DB_View::instance()->database(),id);

	DB_View::instance()->cur_view()->scene()->invalidate();	

}
