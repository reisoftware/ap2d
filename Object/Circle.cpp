// Circle.cpp: implementation of the Circle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Circle.h"
#include "Global.h"
#include "Database.h"
#include "File.h"
#include "DrawEntity.h"
#include "Matrix_d.h"
#include "Entity_Snap_Implement.h"
#include "Entity_Calculate.h"
#include "Line.h"
#include "Normal.h"
#include "Edit_Entity.h"
#include "Visitor.h"
#include "Cloud_Line.h"
#include "intersect.h"

#include "fstream"
#include "getrace.h"
#include "encode.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Circle,Entity)
Circle::Circle()
:radius_(0)
MCT_INIT2("Circle")
{

}
Circle::Circle(const Circle& rhs)
:Entity(rhs)
,radius_(rhs.radius_)
,center_(rhs.center_)
MCT_INIT2("Circle")
{
}
Circle& Circle::operator=(const Circle& rhs)
{
	Entity::operator=(rhs);
	if(this == &rhs)
		return *this;
	radius_ = rhs.radius_;
	center_ = rhs.center_;
	return *this;
}
Circle::Circle(const Point& c,Float r)
:radius_(r)
,center_(c)
MCT_INIT2("Circle")
{

}
Circle::~Circle()
{

}

bool Circle::operator==(const Circle& r)const
{
  if(
    center_ == r.center_ &&
    radius_ == r.radius_
    )
  {
    return true;
  }
  return false;
}


bool Circle::visit(Visitor& v)
{
  box_change(true);
	return v.Visit_Circle(*this);
}
void Circle::loadme(File& in)
{
	in >> radius_;
	center_.load(in);
}
void Circle::saveme(const File& out) const
{
	out << radius_;
	center_.save(out);
}
void Circle::save_luame(std::ofstream &out,int tab_num)
{
	lua::double_save(out,"radius_",radius_,tab_num);
	center_.save_lua(out,"center_",tab_num);
}


void Circle::open_luame(lua_State *l) 
{
	TRACE_OUT("Circle::open_luame()\n");
	get_value(number,l,radius_,"radius_");
	center_.open_lua(l,"center_");

}
void Circle::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","CIRCLE");
	get_str_ent();
	//////////////////////////
	rei_add_float(NULL,"center_.x",center_.x);
	rei_add_float(NULL,"center_.y",center_.y);
	rei_add_float(NULL,"center_.z",center_.z);

	rei_add_float(NULL,"radius_",radius_);
	rei_get_encode(out);
}

void Circle::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	////////////////////////////////////////////////////////////	
	center_.x = atof(rei_get("center_.x"));
	center_.y = atof(rei_get("center_.y"));
	center_.z = atof(rei_get("center_.z"));

	radius_ = atof(rei_get("radius_"));
	rei_quit();


}

void Circle::edit_propertyme(const Edit_Entity& edit)
{
  std::ofstream f("D:/circle_edit_propertyme",std::ios_base::app|std::ios_base::out);
  f<<"1\n";
	edit.edit_circle(*this);
}
void Circle::drawme(Draw_Entity& out) const
{
	out.draw_circle(*this);
}
void Circle::xor_drawme(Draw_Entity& out) const
{
	out.xor_draw_circle(*this);
}

errorinfo Circle::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}

void Circle::transformbyme(const Matrix& mat)
{
//	REITRACE;
  dlhml::transformby2d_distance(mat, radius_);
  //radius_ *= mat.value(0,0);
	center_.transformby(mat);
}
//void Circle::transformbyme(const Matrix& mat)
//{
//		REITRACE;
//	//半径比例随x比例
////  if(mat.mat_type()==SCALE_MAT){
////	  radius_ *= mat.value(0,0);
////  }
//  radius_ *= mat.value(0,0);
//	center_.transformby(mat);
//}
void Circle::drag_startme(const Matrix& mat)
{
}
void Circle::drag_endme(const Matrix& mat)
{
	Point p = center_.polarTo(radius_,Normal(1,0,0));
	p.transformby(mat);
	radius_ = p.distanceto(center_);
}

Entity* Circle::cloneme() const
{
	return new Circle(*this);
}

void Circle::closeme()
{
	delete this;
}

bool Circle::intersectme(const Rect& rect) const
{
  Point st,ed,pt1,pt2;
  Line line;
  //Entity_Calculate calc;

  st.setdata(rect.xmin(),rect.ymax(),0.0);
  ed.setdata(rect.xmax(),rect.ymax(),0.0);
  line.setdata(st,ed);
  //if(calc.line_insect_circle(pt1,pt2,line,*this)){
  if(intersect2d_c_s(*this,line,pt1,pt2)){
    return true;
  }
  st.setdata(rect.xmax(),rect.ymax(),0.0);
  ed.setdata(rect.xmax(),rect.ymin(),0.0);
  line.setdata(st,ed);
//if(calc.line_insect_circle(pt1,pt2,line,*this)){
  if(intersect2d_c_s(*this,line,pt1,pt2)){
    return true;
  }
  st.setdata(rect.xmax(),rect.ymin(),0.0);
  ed.setdata(rect.xmin(),rect.ymin(),0.0);
  line.setdata(st,ed);
//if(calc.line_insect_circle(pt1,pt2,line,*this)){
  if(intersect2d_c_s(*this,line,pt1,pt2)){
    return true;
  }  
  st.setdata(rect.xmin(),rect.ymin(),0.0);
  ed.setdata(rect.xmin(),rect.ymax(),0.0);
  line.setdata(st,ed);
//if(calc.line_insect_circle(pt1,pt2,line,*this)){
  if(intersect2d_c_s(*this,line,pt1,pt2)){
    return true;
  }

  //center
  if(center_.envelop(rect)){
    return true;
  }

  return false;
}

bool Circle::envelopme(const Rect& rect) const
{
  bool b1,b2,b3,b4;
  Point pt;
  
  pt.setdata(center_.x-radius_,center_.y,0.0);
  b1 = pt.envelop(rect);
  pt.setdata(center_.x+radius_,center_.y,0.0);
  b2 = pt.envelop(rect);
  pt.setdata(center_.x,center_.y-radius_,0.0);
  b3 = pt.envelop(rect);
  pt.setdata(center_.x,center_.y+radius_,0.0);
  b4 = pt.envelop(rect);
  
  return b1 && b2 && b3 && b4;
}

Rect Circle::calc_box2d() const
{
  Rect box2d_;
  box2d_.xmax(center_.x + radius_);
  box2d_.xmin(center_.x - radius_);
  box2d_.ymax(center_.y + radius_);
  box2d_.ymin(center_.y - radius_);
  return box2d_;
}
bool Circle::snap_center_pointme(Point& pt,const Rect& rect) const
{
  if(center_.envelop(rect)){
    pt = center_;
    return true;
  }
  return false;
}
bool Circle::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
  Point o;
  o.x = (rect.xmax()+rect.xmin())/2.0;
  o.y = (rect.ymax()+rect.ymin())/2.0;
  Float dis = o.distanceto(center_);
  if(fabs(dis-radius_)<(rect.ymax()-rect.ymin())/2.0){
    Normal nor;
    nor.set_data(Point(center_.x,center_.y),o);
    pt = center_.polarTo(radius_,nor);
    return true;
  }
  return false;
}
//bool Circle::snap_intersect_pointme(Point& pt,
//                                    const Entity& ent,
//                                    const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////  Entity_Snap_Implement<Circle> imp(*this);
////  return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Circle::snap_intersect_pointme(Point& pt,
                                    const Entity_Snap& snap,
                                    const Rect& rect) const
{
  return snap.intersect(pt,rect,*this);
}

void Circle::radius(const Point& pt)
{
  box_change(true);
  radius_ = center_.distanceto(pt);
}

Float Circle::length()const
{
  return radius_ * pi2;
}

void Circle::intersectme(const Entity& e , std::vector<Point>& pts)const
{
  if(&e == this){
    return;
  }
  e.intersect(*this, pts);
}
void Circle::intersectme(const Line & ln, std::vector<Point>& pts)const
{
  //Entity_Calculate calc;
  Point pt1, pt2;
  //bool myre = calc.line_insect_circle(pt1, pt2, ln, *this);
//   if(myre){
//     pts.push_back(pt1);
//     pts.push_back(pt2);
//   }
  int xpt_count = intersect2d_c_l(*this, ln, pt1, pt2);
  dlhml::push_xpt(xpt_count, pt1, pt2, pts);
}
void Circle::intersectme(const RArc & ac, std::vector<Point>& pts)const
{
  Entity_Calculate calc;
  Point pt1, pt2;
  bool myre = calc.circle_insect_arc(pt1, pt2, *this, ac);
  if(myre){
    pts.push_back(pt1);
    pts.push_back(pt2);
  }
  //return myre;
}
void Circle::intersectme(const Circle & cr, std::vector<Point>& pts)const
{
  if(&cr == this){
    return;
  }
  Entity_Calculate calc;
  Point pt1, pt2;
  bool myre = calc.circle_insect_circle(pt1, pt2, cr, *this);
  if(myre){
    pts.push_back(pt1);
    pts.push_back(pt2);
  }
  //return myre;
}
//bool Circle::intersectme(const Cloud_Line& cl, std::vector<Point>& pts)const
//{
//  Entity_Calculate calc;
//  Point pt;
//  bool myre=false;
//  std::vector<Entity*> lns;
//  cl.get_lines(lns);
//  int i=0;
//  for(i=0; i<lns.size(); i++){
//    if(lns[i]->intersect(*this, pts)){
//      myre=true;
//    }
//  }
//  destory(lns);
//  return myre;
//}

void Circle::setctrl(const std::vector<Point>& pts)
{
  box_change(true);
  if(pts.size()<2){
    return;
  }
  center_=pts[0];
  radius_=pts[0].distanceto2d(pts[1]);
}
void Circle::getctrl(std::vector<Point>& pts)const
{
  pts.push_back(center_);
  Point pt=center_.polarTo(radius_, Normal(1,0,0));
  pts.push_back(pt);
}
int Circle::pt_count()const
{
  return 2;
}
void Circle::setdrag(const std::vector<Point>& pts, int index)
{
  box_change(true);
  if(pts.size()<2){
    return;
  }
  switch(index)
  {
  case 0:
    center_=pts[0];
    break;
  case 1:
  case 2:
  case 3:
  case 4:
    radius_=pts[0].distanceto2d(pts[index]);
    break;
  }
}
void Circle::getdrag(std::vector<Point>& pts)const
{
  pts.push_back(center_);
  pts.push_back(center_.polarTo(radius_, Normal(1,0,0)));
  pts.push_back(center_.polarTo(radius_, Normal(0,1,0)));
  pts.push_back(center_.polarTo(radius_, Normal(-1,0,0)));
  pts.push_back(center_.polarTo(radius_, Normal(0,-1,0)));
}

 
//namespace
}
