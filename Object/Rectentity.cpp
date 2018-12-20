// Rectentity.cpp: implementation of the Rectentity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rectentity.h"
#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Point.h"
#include "Entity_Calculate.h"
#include "Line.h"
#include "Entity_Snap_Implement.h"
#include <algorithm>
#include "visitor.h"
//#include "..\DrawDll\reitrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Rectentity,Entity)
Rectentity::Rectentity()
MCT_INIT1("Rectentity")
{

}
Rectentity::Rectentity(const Rectentity& rhs)
:Entity(rhs)
MCT_INIT2("Rectentity")
{
	rect_ = rhs.rect_;
}
Rectentity& Rectentity::operator=(const Rectentity& rhs)
{
	Entity::operator =(rhs);
	if(this == &rhs)
		return *this;
	rect_ = rhs.rect_;
	return *this;
}
Rectentity::~Rectentity()
{

}
bool Rectentity::visit(Visitor& v)
{
	return v.Visit_Rectentity(*this);
}
void Rectentity::loadme(File& in)
{
	rect_.load(in);
}
void Rectentity::saveme(const File& out) const
{
	rect_.save(out);
}
void Rectentity::edit_propertyme(const Edit_Entity& edit)
{
	edit.edit_rectentity(*this);
}
void Rectentity::drawme(Draw_Entity& out) const
{
	out.draw_rectentity(*this);
}
void Rectentity::xor_drawme(Draw_Entity& out) const
{
	out.xor_draw_rectentity(*this);
}
errorinfo Rectentity::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}
void Rectentity::transformbyme(const Matrix& mat)
{
//	REITRACE;
	rect_.transformby(mat);
}
void Rectentity::drag_startme(const Matrix& mat)
{
}
void Rectentity::drag_endme(const Matrix& mat)
{
}
Entity* Rectentity::cloneme() const
{
	return new Rectentity(*this);
}
void Rectentity::closeme()
{
	delete this;
}
bool Rectentity::intersectme(const Rect& rect) const
{
	Line line[4];
	get_line(line);
	for(int i=0;i<4;++i){
		if(line[i].intersect(rect))
			return true;
	}
	return false;
//	return rect_.intersect(rect);
}
bool Rectentity::envelopme(const Rect& rect) const
{
	return rect_.envelop(rect);
}
Rect Rectentity::calc_box2d() const
{
	return rect_;
}
void Rectentity::get_point(Point (&pt)[4]) const
{
	pt[0].setdata(rect_.xmin(),rect_.ymin());
	pt[1].setdata(rect_.xmin(),rect_.ymax());
	pt[2].setdata(rect_.xmax(),rect_.ymax());
	pt[3].setdata(rect_.xmax(),rect_.ymin());
}
void Rectentity::get_line(Line (&line)[4]) const
{
	Point pts[4];
	get_point(pts);
	for(int i=0;i<4;++i){
		int i1=i;
		int i2=i+1==4?0:i+1;
		Point st=pts[i1];
		Point ed=pts[i2];
		line[i].setdata(st,ed);
	}
}
bool Rectentity::snap_endpointme(Point& pt,const Rect& rect) const
{/*
	Point pts[4];
	get_point(pts);
	for(int i=0;i<4;++i){
		if(pts[i].envelop(rect)){
			pt = pts[i];
			return true;
		}
	}*/
	return false;
}
bool Rectentity::snap_middle_pointme(Point& pt,const Rect& rect) const
{/*
	Point pts[4];
	get_point(pts);
	for(int i=0;i<4;++i){
		int i1=i;
		int i2=i+1==4?0:i+1;
		Point st=pts[i1];
		Point ed=pts[i2];
		Point middle = st + ed;
		middle /= 2.0;
		if(middle.envelop(rect)){
			pt = middle;
			return true;
		}
	}*/
	return false;
}
bool Rectentity::snap_nearest_pointme(Point& pt,const Rect& rect) const
{/*
	std::vector<Float> dis;
	Line line[4];
	get_line(line);
	for(int i=0;i<4;++i){
		Entity_Calculate calc;
		Point o,temp;
		o.x = (rect.xmax()+rect.xmin())/2.0;
		o.y = (rect.ymax()+rect.ymin())/2.0;
		calc.line_perpendicular(temp,line[i],o);
		dis.push_back(o.distanceto(temp));
	}
	std::vector<Float>::iterator it = std::min_element(dis.begin(),dis.end());
	return line[it-dis.begin()].snap_nearest_point(pt,rect);*/
	return false;
	return true;
}
bool Rectentity::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{/*
	Line line[4];
	get_line(line);
	for(int i=0;i<4;++i){
		Entity_Snap_Implement<Line> imp(line[i]);
		if(ent.snap_intersect_point_imp(pt,imp,rect))
			return true;
	}*/
	return false;
}
bool Rectentity::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{/*
	Line line[4];
	get_line(line);
	for(int i=0;i<4;++i){
	if(snap.intersect(pt,rect,line[i]))
		return true;
	}*/
	return false;
}
}
