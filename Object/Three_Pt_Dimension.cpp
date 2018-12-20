// Three_Pt_Dimension.cpp: implementation of the Three_Pt_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Three_Pt_Dimension.h"
#include "File.h"
#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Entity_Snap_Implement.h"
#include "Normal.h"
#include "Matrix_d.h"
#include "Entity_Calculate.h"
#include "Line.h"
#include "Dimension_Style.h"
#include "Database.h"
#include "Text.h"
#include "Circle.h"
#include <cassert>
#include "Visitor.h"

#include <algorithm>
#include <functional>
//#include "..\DrawDll\reitrace.h"

#include "Global.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Three_Pt_Dimension,Dimension) 
Three_Pt_Dimension::Three_Pt_Dimension() 
:extend_angle_(0)
MCT_INIT2("Three_Pt_Dimension")
{ 
//	extend_angle_ = 0.0;
} 
Three_Pt_Dimension::Three_Pt_Dimension(const Three_Pt_Dimension& rhs)
:Dimension(rhs)
MCT_INIT2("Three_Pt_Dimension")
{
	extend_angle_ = rhs.extend_angle_;
	start_ = rhs.start_;
	end_ = rhs.end_;
	dimpt_ = rhs.dimpt_;
}
Three_Pt_Dimension& Three_Pt_Dimension::operator=(const Three_Pt_Dimension& rhs)
{
	Dimension::operator =(rhs);
	if(this == &rhs)
		return *this;
	extend_angle_ = rhs.extend_angle_;
	start_ = rhs.start_;
	end_ = rhs.end_;
	dimpt_ = rhs.dimpt_;
	return *this;
}
Three_Pt_Dimension::~Three_Pt_Dimension()
{

}
void Three_Pt_Dimension::setdata(const Point& st,
                                 const Point& ed,
                                 const Point& dim)
{
	start_.set2d(st);
	end_  .set2d(ed);
	dimpt_.set2d(dim);
//	start_  = st;
//	end_    = ed;
//	dimpt_  = dim;
}

void Three_Pt_Dimension::extend_radian(Float angle)					
{
  extend_angle_=angle;
}
Float Three_Pt_Dimension::extend_radian() const							
{
  return extend_angle_;
}
	
void Three_Pt_Dimension::dimline_radian(Float angle)					
{
  extend_angle_ = angle + pi/2;
  std_radian(extend_angle_);
}
Float Three_Pt_Dimension::dimline_radian() const							
{
  Float dimline_angle = extend_angle_ - pi/2;
  std_radian(dimline_angle);
  return dimline_angle;
}	
void Three_Pt_Dimension::dimline_degree(Float a)
{
  dimline_radian(degree_2_radian(a));
}
Float Three_Pt_Dimension::dimline_degree() const							
{
  //Float dimline_angle = extend_angle_ - pi/2;
  //std_radian(dimline_angle);
  return radian_2_degree(dimline_radian());
}	
void Three_Pt_Dimension::start_dim_to(const Point& st)			
{
  start_.set2d(st);
//  start_=st;
}
Point Three_Pt_Dimension::start_dim_to() const			        
{
  return start_;
}
void Three_Pt_Dimension::end_dim_to(const Point& ed)				
{
  end_.set2d(ed);
//  end_=ed;
}
Point Three_Pt_Dimension::end_dim_to() const				        
{
  return end_;
}
void Three_Pt_Dimension::dimension_pt(const Point& dimpt)		
{
  dimpt_.set2d(dimpt);
//  dimpt_ = dimpt;
}
Point Three_Pt_Dimension::dimension_pt() const			        
{
  return dimpt_;
}



bool Three_Pt_Dimension::visit(Visitor& v)
{
	return v.Visit_Three_Pt_Dimension(*this);
}
void Three_Pt_Dimension::loadme(File& in)
{
	load_me(in);
	in >> extend_angle_;
	start_.load(in);
	end_.load(in);
	dimpt_.load(in);
}

void Three_Pt_Dimension::saveme(const File& out) const
{
	save_me(out);
	out << extend_angle_;
	start_.save(out);
	end_.save(out);
	dimpt_.save(out);
}
void Three_Pt_Dimension::edit_propertyme(const Edit_Entity& edit)
{
//	edit.edit_three_pt_dim(*this);
}
//void Three_Pt_Dimension::drawme(Draw_Entity& out) const
//{
//	out.draw_three_pt_dim(*this);
//}
//
//void Three_Pt_Dimension::xor_drawme(Draw_Entity& out) const
//{
//	out.xor_draw_three_pt_dim(*this);
//}
errorinfo Three_Pt_Dimension::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}

void Three_Pt_Dimension::transformbyme(const Matrix& mat)
{
//	REITRACE;
	text_position_.transformby(mat);
	start_.transformby(mat);
	end_.transformby(mat);
	dimpt_.transformby(mat);
}
void Three_Pt_Dimension::drag_startme(const Matrix& mat)
{
	dimpt_.transformby(mat);
}
void Three_Pt_Dimension::drag_endme(const Matrix& mat)
{
	dimpt_.transformby(mat);
}
Entity* Three_Pt_Dimension::cloneme() const
{
	return new Three_Pt_Dimension(*this);
}
void Three_Pt_Dimension::closeme()
{
	delete this;
}
bool Three_Pt_Dimension::get_dim_lines_show(std::vector<Line*>& lines) const
{
	get_lines(*lines[0],*lines[1],*lines[2]);
	for(int i=0;i<3;++i){
		lines[i]->line_style(line_style());
		lines[i]->color(color());
	}
	return true;
}
int Three_Pt_Dimension::get_arrow_line_show(const Line& dim,std::vector<Line*>& lines) const
{
//	assert(static_current_db_);
//	assert(dim_style_);
//	Dimension_Style* ds=0;
//	static_current_db_->get_dimensionstyle(ds,dim_style_);
//	assert(ds);
//	Normal nor;
//	nor.set_data(cos(extend_angle_+pi/2),sin(extend_angle_+pi/2),0);
//	int num1 = ds->get_arrow_line(dim.start(),nor,lines);
//	nor.set_data(cos(extend_angle_-pi/2),sin(extend_angle_-pi/2),0);
//	std::vector<Line*> end;
//	std::copy(lines.begin()+num1,lines.end(),std::back_inserter(end));
//	int num2 = ds->get_arrow_line(dim.end(),nor,end);
//	int num = num1+num2;
//	for(int i=0;i<num;++i){
//		lines[i]->line_style(line_style());
//		lines[i]->color(color());
//	}
//	return num;
  return 0;
}
/*
int Three_Pt_Dimension::get_start_arrow_line_show(std::vector<Line*>& lines) const
{
	Line start,end,dim;
	get_lines(start,end,dim);
	assert(static_current_db_);
	assert(dim_style_);
	Dimension_Style* ds=0;
	static_current_db_->get_dimensionstyle(ds,dim_style_);
	assert(ds);
	Normal nor;
	nor.set_data(cos(extend_angle_+pi/2),sin(extend_angle_+pi/2),0);
	int num = ds->get_arrow_line(dim.start(),nor,lines);
	for(int i=0;i<num;++i){
		lines[i]->line_style(line_style());
		lines[i]->color(color());
	}
	return num;
}
int Three_Pt_Dimension::get_end_arrow_line_show(std::vector<Line*>& lines) const
{
	Line start,end,dim;
	get_lines(start,end,dim);
	assert(static_current_db_);
	assert(dim_style_);
	Dimension_Style* ds=0;
	static_current_db_->get_dimensionstyle(ds,dim_style_);
	assert(ds);
	Normal nor;
	nor.set_data(cos(extend_angle_-pi/2),sin(extend_angle_-pi/2),0);
	int num = ds->get_arrow_line(dim.end(),nor,lines);
	for(int i=0;i<num;++i){
		lines[i]->line_style(line_style());
		lines[i]->color(color());
	}
	return num;
}
*/
int Three_Pt_Dimension::get_arrow_circle_show(const Line& dim,std::vector<Circle*>& circles) const
{
//	assert(static_current_db_);
//	assert(dim_style_);
//	Dimension_Style* ds=0;
//	static_current_db_->get_dimensionstyle(ds,dim_style_);
//	assert(ds);
//	int num1 = ds->get_arrow_circle(dim.start(),circles);
//	std::vector<Circle*> end;
//	std::copy(circles.begin()+num1,circles.end(),std::back_inserter(end));
//	int num2 = ds->get_arrow_circle(dim.end(),end);
//	int num = num1+num2;
//	for(int i=0;i<num;++i){
//		circles[i]->line_style(line_style());
//		circles[i]->color(color());
//	}
//	return num;
  return 0;
}
/*
int Three_Pt_Dimension::get_start_arrow_circle_show(std::vector<Circle*>& circles) const
{
	Line start,end,dim;
	get_lines(start,end,dim);
	assert(static_current_db_);
	assert(dim_style_);
	Dimension_Style* ds=0;
	static_current_db_->get_dimensionstyle(ds,dim_style_);
	assert(ds);
	int num = ds->get_arrow_circle(dim.start(),circles);
	for(int i=0;i<num;++i){
		circles[i]->line_style(line_style());
		circles[i]->color(color());
	}
	return num;
}
int Three_Pt_Dimension::get_end_arrow_circle_show(std::vector<Circle*>& circles) const
{
	Line start,end,dim;
	get_lines(start,end,dim);
	assert(static_current_db_);
	assert(dim_style_);
	Dimension_Style* ds=0;
	static_current_db_->get_dimensionstyle(ds,dim_style_);
	assert(ds);
	int num = ds->get_arrow_circle(dim.end(),circles);
	for(int i=0;i<num;++i){
		circles[i]->line_style(line_style());
		circles[i]->color(color());
	}
	return num;
}
*/
bool Three_Pt_Dimension::get_lines(Line& start_extendline,
                                   Line& end_extendline,
                                   Line& dimline) const
{
	assert(static_current_db_);
	Dimension_Style* ds=0;
	static_current_db_->get_dimensionstyle(ds,dim_style_name_);
	assert(ds);
	Normal n;
	n.set_x_axis_angle(extend_angle_);
	Point pt = start_.polarTo(start_.distanceto(end_),n);
	Entity_Calculate calc;
	Point pp1;
	Line line(start_,pt);
	calc.line_perpendicular(pp1,line,dimpt_);
	pt = end_.polarTo(start_.distanceto(end_),n);
	Point pp2;
	line.setdata(end_,pt);
	calc.line_perpendicular(pp2,line,dimpt_);
	dimline.setdata(pp1,pp2);

	Point off1,off2;
	off1 = ds->get_extend_base(start_,pp1);
	off2 = ds->get_extend_end(start_,pp1);
	start_extendline.setdata(off1,off2);
	off1 = ds->get_extend_base(end_,pp2);
	off2 = ds->get_extend_end(end_,pp2);
	end_extendline.setdata(off1,off2);
	return true;
}
bool Three_Pt_Dimension::intersectme(const Rect& rect) const
{
	Line start,end,dim;
	get_lines(start,end,dim);
	Entity_Calculate calc;
	if(calc.linesegment_insect_rect(start,rect))
		return true;
	if(calc.linesegment_insect_rect(end,rect))
		return true;
	if(calc.linesegment_insect_rect(dim,rect))
		return true;
	Text text;
	get_text_show(text);
	if(text.intersect(rect))
		return true;
	return false;
}
bool Three_Pt_Dimension::envelopme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
	return start_.envelop(rect) && end_.envelop(rect) 
		&& dimpt_.envelop(rect) && text_position_.envelop(rect)
		&& text.envelop(rect);
}
Rect Three_Pt_Dimension::calc_box2d() const
{
	Rect box2d_;
	std::vector<Entity*> ents;
	Line start,end,dim;
	get_lines(start,end,dim);
	ents.push_back(&start);
	ents.push_back(&end);
	ents.push_back(&dim);
	Text text;
	get_text_show(text);
	ents.push_back(&text);

	dlhml::box2d(box2d_, ents);
//	Entity_Calculate calc;
//	calc.get_ents_rect(box2d_,ents);
	return box2d_;
}
bool Three_Pt_Dimension::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
//NOOK SNAP 2009.07.02
////Entity 统一实现
  return false;
//	Entity_Snap_Implement<Three_Pt_Dimension> imp(*this);
//	return ent.snap_intersect_point_imp(pt,imp,rect);
}
bool Three_Pt_Dimension::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}


}
