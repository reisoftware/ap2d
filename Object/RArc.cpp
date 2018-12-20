// RArc.cpp: implementation of the RArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RArc.h"
#include "Global.h"

#include "File.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Matrix_d.h"
#include "Entity_Snap_Implement.h"
#include "Normal.h"
#include "Transform_Func.h"
#include "Line.h"
#include "Entity_Calculate.h"
#include "Edit_Entity.h"
#include "Visitor.h"
#include "Line.h"
#include "Cloud_Line.h"
#include "geo_obj.h"
#include "intersect.h"

#include <cassert>
#include "../include/getrace.h"
#include "../geometry/box.h"
#include "../geometry/intersect.h"
#include "encode.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(RArc,Entity)
RArc::RArc()
MCT_INIT1("RArc")
{
  box_change(true);
}
RArc::~RArc() 
{ 
}

///////////////////////////// <<write>> ///////////////////////////////
//set
void RArc::set(const geo::Arc& o)
{
  box_change(true);
  arc_ = o;
}

void RArc::set(const Point& pt1, const Point& pt2, const Point& pt3)
{
  box_change(true);
  geo::Point gpt1 = convert(pt1);
  geo::Point gpt2 = convert(pt2);
  geo::Point gpt3 = convert(pt3);
  arc_.set(gpt1, gpt2, gpt3);
}

void RArc::set(const Point& c, const Point& s, const Point& e, const Point& p)
{
  box_change(true);
  geo::Point gc = convert(c);
  geo::Point gs = convert(s);
  geo::Point ge = convert(e);
  geo::Point gp = convert(p);
  arc_.set(gc, gs, ge, gp);
}

void RArc::center(const Point& pt)
{
  box_change(true);
  arc_.center(convert(pt));
}

void RArc::set_radian2d(const Point& c, Float r, Float srad, Float erad)
{
  box_change(true);
  geo::Point gc = convert(c);
  arc_.set_radian2d(gc, r, srad, erad);
}

void RArc::set_degree2d(const Point& c, Float r, Float sdeg, Float edeg)
{
  box_change(true);
  geo::Point gc = convert(c);
  arc_.set_degree2d(gc, r, sdeg, edeg);
}

void RArc::radius(Float r)
{
  box_change(true);
  arc_.radius(r);
}
void RArc::start(const Point& pt)
{
  box_change(true);
  arc_.start = convert(pt);
}
void RArc::path(const Point& pt)
{
  box_change(true);
  arc_.path = convert(pt);
}
void RArc::end(const Point& pt)
{
  box_change(true);
  arc_.end = convert(pt);
}



///////////////////////////// <<read>> ///////////////////////////////
geo::Arc RArc::get()const
{
  return arc_;
}

Point RArc::center()const
{
  geo::Point gc = arc_.center();
  Point oc = convert(gc);
  return oc;
}

Float RArc::radius()const
{
  return arc_.radius();
}

Float RArc::radian()const
{
  return arc_.radian();
}

Float RArc::degree()const
{
  return arc_.degree();
}


Float RArc::start_radian2d()const
{
  return arc_.start_radian2d();
}

Float RArc::start_degree2d()const
{
  return arc_.start_degree2d();
}


Float RArc::end_radian2d()const
{
  return arc_.end_radian2d();
}

Float RArc::end_degree2d()const
{
  return arc_.end_degree2d();
}

Float RArc::middle_radian2d()const
{
  return arc_.middle_radian2d();
}

Float RArc::middle_degree2d()const
{
  return arc_.middle_degree2d();
}

/////////////////
Point RArc::middle()const
{
  geo::Point gm = arc_.middle();
  Point om = convert(gm);
  return om;
}

Point RArc::start()const
{
  Point pt = convert(arc_.start);
  return pt;
}

Point RArc::path()const
{
  Point pt = convert(arc_.path);
  return pt;
}

Point RArc::end()const
{
  Point pt = convert(arc_.end);
  return pt;
}

Point RArc::middle2d()const
{
  return convert(arc_.middle2d());
}

Point RArc::start2d()const
{
  return convert(arc_.start2d());
}

Point RArc::path2d()const
{
  return convert(arc_.path2d());
}

Point RArc::end2d()const
{
  return convert(arc_.end2d());
}



////
bool RArc::visit(Visitor& v)
{
  box_change(true);
	return v.Visit_RArc(*this);
}

// void RArc::get_end_point(Point& st,Point& ed) const
// {
// 	Float angle1 = pi*start_degree_/180;
// 	Float angle2 = pi*end_degree_/180;
// 	st.setdata(center_.x+cos(angle1)*radius_,
// 		center_.y+sin(angle1)*radius_);
// 	ed.setdata(center_.x+cos(angle2)*radius_,
// 		center_.y+sin(angle2)*radius_);
// }

// void RArc::set_3_pt(const Point& pt1,const Point& pt2,const Point& pt3)
// {
//   box_change(true);
//   pt1_ = pt1;
//   pt2_ = pt2;
//   pt3_ = pt3;
// }
 
// void RArc::set_start_pt(const Point& pt)
// {
//   box_change(true);
//   pt1_=pt;
//   init_other();
// //  Point pt1, pt2, pt3;
// //  get_3_pt(pt1,pt2,pt3);
// //  pt1 = pt;
// //  setdata(pt1, pt2, pt3); 
// }
 
// void RArc::set_path_pt(const Point& pt)
// {
//   box_change(true);
//   pt2_=pt;
//   init_other();
// //  Point pt1, pt2, pt3;
// //  get_3_pt(pt1,pt2,pt3);
// //  pt2 = pt;
// //  setdata(pt1, pt2, pt3); 
// }

// void RArc::set_end_pt(const Point& pt)
// {
//   box_change(true);
//   pt3_=pt;
//   init_other();
// //  Point pt1, pt2, pt3;
// //  get_3_pt(pt1,pt2,pt3);
// //  pt3 = pt;
// //  setdata(pt1, pt2, pt3); 
// }
 
// void RArc::getdata(Point& pt1,Point& pt2,Point& pt3)const
// {
//   pt1 = pt1_;
//   pt2 = pt2_;
//   pt3 = pt3_;
// }
 
// Point RArc::get_start_pt()const
// {
//   return pt1_;
// }

// Point RArc::get_path_pt()const
// {
//   return pt2_;
// }

// Point RArc::get_end_pt()const
// {
//   return pt3_;
// }

// Point RArc::get_middle_pt()const
// {
//   if(pt2_ == pt3_){
//     return Line(pt1_,pt2_).middle();
//   }
// 
//   double start_angle = start_degree_;
//   double end_angle   = end_degree_  ;
//   std_degree(start_angle);
//   std_degree(end_angle);
//   double mid_angle = (start_angle+end_angle)/2;
//   if(!is_sort(start_angle, mid_angle, end_angle)){
//     mid_angle += 180;
//     std_degree(mid_angle);
//   }
//   Normal mid_nor;
//   degree_2_normal2d(mid_angle, mid_nor);
//   mid_nor.set_unit();
//   Point pt = center_.polarTo(radius_, mid_nor);
//   return pt;
// }



//c
// void RArc::center(const Point& c)
// {
//   box_change(true);
//   center_ = c;
//   init_pt();
// }
// Point RArc::center() const								
// {
//   return center_;
// }
// 
// //r
// void RArc::radius(Float r)
// {
//   box_change(true);
//   radius_ = r;
//   init_pt();
// }
// Float RArc::radius() const								
// {
//   return radius_;
// }
// 
// //start
// void RArc::start_degree(Float a)
// {
//   box_change(true);
//   std_degree(a);
//   start_degree_ = a;
//   init_pt();
// }
// Float RArc::start_degree() const					
// {
//   return start_degree_;
// }
// 
// 
// void RArc::end_degree(Float a)
// {
//   box_change(true);
//   std_degree(a);
//   end_degree_ = a;
//   init_pt();
// }
// void RArc::start_radian(Float a)
// {
//   box_change(true);
//   start_degree_ = radian_2_degree(a);
//   std_degree(start_degree_);
//   init_pt();
// }
// void RArc::end_radian(Float a)
// {
//   box_change(true);
//   end_degree_ = radian_2_degree(a);
//   std_degree(end_degree_);
//   init_pt();
// }
// 
// void RArc::setdata(const Point& c,Float r,Float stang,Float edang)
// {
//   box_change(true);
//   std_degree(stang);
//   std_degree(edang);
// 	center_ = c;
// 	start_degree_= stang;
// 	end_degree_  = edang;
// 	radius_ = r;
//   init_pt();
// }
// void RArc::setdata(const Point& c,const Point& st,const Point& ed,const Point& path)
// {
//   box_change(true);
//   double r = c.distanceto(path);
//   Normal st_nor, ed_nor, path_nor;
//   st_nor.set_data(c,st);
//   ed_nor.set_data(c,ed);
//   path_nor.set_data(c,path);
// 
//   Float st_deg=0, ed_deg=0, path_deg=0;
//   normal2d_2_degree(st_nor,st_deg);
//   normal2d_2_degree(ed_nor,ed_deg);
//   normal2d_2_degree(path_nor,path_deg);
// 
//   if(is_sort(st_deg,path_deg,ed_deg)){
//     setdata(c,r,st_deg,ed_deg);
//   }else{
//     setdata(c,r,ed_deg,st_deg);
//   }
// 
//   //Point st_arc = c.polarTo(r,st_nor);
//   //Point ed_arc = c.polarTo(r,ed_nor);
//   //set_3_pt(st_arc, path, ed_arc);
//   //  if(start == end){
//   //    return false;
//   //  }
//   //  Line ln(start, end);
//   //  if(ln.is_in_line(path)){
//   //    return false;
//   //  }
//   //init_other();
// }

// 获得穿过三点的正圆的圆心和半径
// 如果三点成直线返回值：FALSE
// bool RArc::setdata(const Point& start,const Point& path,const Point& end)
// {
//   box_change(true);
//   set_3_pt(start, path, end);
//   //  if(start == end){
//   //    return false;
//   //  }
//   //  Line ln(start, end);
//   //  if(ln.is_in_line(path)){
//   //    return false;
//   //  }
//   init_other();
//   return true; 
// }

// void RArc::init_pt()
// {
//   box_change(true);
//   double start_angle = start_degree_;
//   double end_angle   = end_degree_  ;
//   std_degree(start_angle);
//   std_degree(end_angle);
//   double mid_angle = (start_angle+end_angle)/2;
//   if(!is_sort(start_angle, mid_angle, end_angle)){
//     mid_angle += 180;
//     std_degree(mid_angle);
//   }
// 
//   Normal start_nor, mid_nor, end_nor;
//   degree_2_normal2d(start_angle, start_nor);
//   degree_2_normal2d(mid_angle  , mid_nor  );
//   degree_2_normal2d(end_angle  , end_nor  );
//   start_nor.set_unit();
//   mid_nor  .set_unit();
//   end_nor  .set_unit();
// 
//   pt1_ = center_.polarTo(radius_, start_nor);
//   pt2_ = center_.polarTo(radius_, mid_nor  );
//   pt3_ = center_.polarTo(radius_, end_nor  );
// }

// void RArc::init_other()
// {
//   box_change(true);
//   if(pt1_== pt2_|| pt2_==pt3_ || pt1_==pt3_){
//     center_=pt1_;
//     radius_=0;
//     start_degree_=0;
//     end_degree_  =0;
//     return;
//   }
//   Line ln;
// //  ln.setdata(pt1_,pt2_);
// //  if(pt2_==pt3){
// //    center_=ln.middle();;
// //    radius_=ln.length()/2;
// //    start_degree_=0;
// //    end_degree_  =0;
// //    return;
// //  }
//   ln.setdata(pt1_, pt3_);
//   if(ln.is_in_line(pt2_)){
//     return;
//   }
//   init_other(pt1_,pt2_,pt3_);
//   return;
// 
//   Point start=pt1_;
//   Point path =pt2_;
//   Point end  =pt3_;
// 
//   Normal n1;
//   n1.set_data(path.x-start.x,path.y-start.y,0);
//   Float a1 = n1.angle_x_axis_two_pi();
//   Matrix mat;
//   mat.set_z_rotation_radian(-a1);
//   Point temp(end);
//   Point temp1(path);
//   temp.transformby(mat);
//   temp1.transformby(mat);
//   if(temp.y<temp1.y){
//     init_other(end, path, start);
//   }
//   else{
//     init_other(start, path, end);
//   }
// }

// void RArc::init_other(const Point& pt1,const Point& pt2,const Point& pt3)
// {
//   box_change(true);
//   Entity_Calculate calc; 
//   Line l1,l2; 
//   calc.middle_perpendicular_line(l1,pt1,pt2); 
//   calc.middle_perpendicular_line(l2,pt2,pt3); 
//   calc.line_insect_line(center_,l1,l2); 
//   radius_ = center_.distanceto(pt2); 
// //  Normal nor; 
// //  nor.set_data(pt1.x-center_.x,pt1.y-center_.y,0); 
// //  start_degree_= nor.angle_x_axis_two_pi()*180/pi; 
// //  nor.set_data(pt3.x-center_.x,pt3.y-center_.y,0); 
// //  end_degree_  = nor.angle_x_axis_two_pi()*180/pi; 
// //  nor.set_data(pt2.x-center_.x,pt2.y-center_.y,0); 
// //  Float path_degree  = nor.angle_x_axis_two_pi()*180/pi; 
// //
// //  std_degree(start_degree_);
// //  std_degree(end_degree_  );
// //  std_degree(path_degree  );
// 
//   Normal nor;
//   Float path_degree;
//   nor.set_data(center_,pt1);
//   normal2d_2_degree(nor,start_degree_);
//   nor.set_data(center_,pt2);
//   normal2d_2_degree(nor,path_degree);
//   nor.set_data(center_,pt3);
//   normal2d_2_degree(nor,end_degree_);
// 
// 
//   if(!is_sort(start_degree_,path_degree,end_degree_)){
//     std::swap(start_degree_,end_degree_);
//   }
// }

// bool RArc::is_sort(double asin1, double asin2, double asin3)const
// {
//   if(LessEqu(asin1,asin3)){
//     return (LessEqu(asin1,asin2)&&LessEqu(asin2,asin3));
//   }
//   else{
//     return !(MoreThen(asin1,asin2)&&MoreThen(asin2,asin3));
//   }
// 
// //	if(asin1<asin3)
// //	{
// //		return (asin1<asin2 && asin2<asin3);
// //	}
// //	else
// //	{
// //		return !(asin1>asin2 && asin2>asin3);
// //	}
// }

void RArc::loadme(File& in)
{
// 	in >> radius_	>> start_degree_ >> end_degree_;
// 	center_.load(in);
//   pt1_.load(in);
//   pt2_.load(in);
//   pt3_.load(in);

  box_change(true);
  Point s, p, e;
  s.load(in);
  p.load(in);
  e.load(in);
  set(s, p, e);
//   geo::Point gs, gp, ge;
//   gs = convert(s);
//   gp = convert(p);
//   ge = convert(e);
//   arc_.set(gs, gp, ge);
}
void RArc::saveme(const File& out) const
{
// 	out << radius_	<< start_degree_ << end_degree_ ;
// 	center_.save(out);
//   pt1_.save(out);
//   pt2_.save(out);
//   pt3_.save(out);
//   Point s, p, e;
//   s = convert(arc_.start);
//   p = convert(arc_.middle());
//   e = convert(arc_.end);
  start().save(out);
  path().save(out);
  end().save(out);
}
void RArc::save_luame(std::ofstream &out,int tab_num)
{
// 	lua::float_save(out,"radius_",radius_,tab_num);
// 	lua::float_save(out,"start_degree_",start_degree_,tab_num);
// 	lua::float_save(out,"end_degree_",end_degree_,tab_num);
// 
// 	center_.save_lua(out,"center_",tab_num);
// 	pt1_.save_lua(out,"pt1_",tab_num);
// 	pt2_.save_lua(out,"pt2_",tab_num);
// 	pt3_.save_lua(out,"pt3_",tab_num);
//   Point s, p, e;
//   s = convert(arc_.start);
//   p = convert(arc_.path);
//   e = convert(arc_.end);
  start().save_lua(out,"start_pt",tab_num);
  path().save_lua(out,"path_pt",tab_num);
  end().save_lua(out,"end_pt",tab_num);
}

void RArc::open_luame(lua_State *l)  
{
	TRACE_OUT("RArc open in open_luame()\n");
// 	get_value(number,l,radius_,"radius_");
// 	get_value(number,l,start_degree_,"start_degree_");
// 	get_value(number,l,end_degree_,"end_degree_");
// 	center_.open_lua(l,"center_");
// 	pt1_.open_lua(l,"pt1_");
// 	pt2_.open_lua(l,"pt2_");
// 	pt3_.open_lua(l,"pt3_");

  box_change(true);
  Point s, p, e;
  s.open_lua(l, "start_pt");
  p.open_lua(l, "path_pt");
  e.open_lua(l, "end_pt");
  set(s, p, e);
//   geo::Point gs, gp, ge;
//   gs = convert(s);
//   gp = convert(p);
//   ge = convert(e);
//   arc_.set(gs, gp, ge);
}
void RArc::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","ARC");

	get_str_ent();
	////////////////////////////////////////////////////////////

	rei_add_float(NULL,"arc_.start.x",arc_.start.x);
	rei_add_float(NULL,"arc_.start.y",arc_.start.y);
	rei_add_float(NULL,"arc_.start.z",arc_.start.z);

	rei_add_float(NULL,"arc_.path.x",arc_.path.x);
	rei_add_float(NULL,"arc_.path.y",arc_.path.y);
	rei_add_float(NULL,"arc_.path.z",arc_.path.z);

	rei_add_float(NULL,"arc_.end.x",arc_.end.x);
	rei_add_float(NULL,"arc_.end.y",arc_.end.y);
	rei_add_float(NULL,"arc_.end.z",arc_.end.z);
	rei_get_encode(out);
}

void RArc::set_from_strme(char *in)
{
	rei_init(in);

	seled_ = atoi(rei_get("seled_"));
	visibility_ = atoi(rei_get("visibility_"));
	linewidth_ = atoi(rei_get("linewidth_"));
	real_color_ = atoi(rei_get("real_color_"));
	

	linestyle_ = rei_get("linestyle_");
	layername_ = rei_get("layername_");
	group_ = rei_get("group_");
	////////////////////////////////////////////////////////////
	
	arc_.start.x = atof(rei_get("arc_.start.x"));
	arc_.start.y = atof(rei_get("arc_.start.y"));
	arc_.start.z = atof(rei_get("arc_.start.z"));

	arc_.path.x = atof(rei_get("arc_.path.x"));
	arc_.path.y = atof(rei_get("arc_.path.y"));
	arc_.path.z = atof(rei_get("arc_.path.z"));

	arc_.end.x = atof(rei_get("arc_.end.x"));
	arc_.end.y = atof(rei_get("arc_.end.y"));
	arc_.end.z = atof(rei_get("arc_.end.z"));

	rei_quit();
}
void RArc::get_str_sub()
{
	get_str_ent();
	////////////////////////////////////////////////////////////

	rei_add_float(NULL,"arc_.start.x",arc_.start.x);
	rei_add_float(NULL,"arc_.start.y",arc_.start.y);
	rei_add_float(NULL,"arc_.start.z",arc_.start.z);

	rei_add_float(NULL,"arc_.path.x",arc_.path.x);
	rei_add_float(NULL,"arc_.path.y",arc_.path.y);
	rei_add_float(NULL,"arc_.path.z",arc_.path.z);

	rei_add_float(NULL,"arc_.end.x",arc_.end.x);
	rei_add_float(NULL,"arc_.end.y",arc_.end.y);
	rei_add_float(NULL,"arc_.end.z",arc_.end.z);

}
void RArc::set_from_str_sub()
{
	seled_ = atoi(rei_get("seled_"));
	visibility_ = atoi(rei_get("visibility_"));
	linewidth_ = atoi(rei_get("linewidth_"));
	real_color_ = atoi(rei_get("real_color_"));
	

	linestyle_ = rei_get("linestyle_");
	layername_ = rei_get("layername_");
	group_ = rei_get("group_");
	////////////////////////////////////////////////////////////
	
	arc_.start.x = atof(rei_get("arc_.start.x"));
	arc_.start.y = atof(rei_get("arc_.start.y"));
	arc_.start.z = atof(rei_get("arc_.start.z"));

	arc_.path.x = atof(rei_get("arc_.path.x"));
	arc_.path.y = atof(rei_get("arc_.path.y"));
	arc_.path.z = atof(rei_get("arc_.path.z"));

	arc_.end.x = atof(rei_get("arc_.end.x"));
	arc_.end.y = atof(rei_get("arc_.end.y"));
	arc_.end.z = atof(rei_get("arc_.end.z"));

}

// void RArc::lua_load(iLua_File &fin)
// {
// 
// 
// }
// 
// void RArc::lua_save(oLua_File &fout)const
// {
// 	Entity::lua_save(fout);
// 	fout.save_value("radius_", radius_);
// 	fout.save_value("start_degree_", start_degree_);
// 	fout.save_value("end_degree_", end_degree_);
// 	fout.save_value("center_", &center_);
// 	fout.save_value("pt1_", &pt1_);
// 	fout.save_value("pt2_", &pt2_);
// 	fout.save_value("pt3_", &pt3_);
// }

void RArc::edit_propertyme(const Edit_Entity& edit)
{
	edit.edit_arc(*this);
}

void RArc::drawme(Draw_Entity& out) const
{
	out.draw_arc(*this);
}
void RArc::xor_drawme(Draw_Entity& out) const
{
	out.xor_draw_arc(*this);
}

errorinfo RArc::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}

void RArc::transformbyme(const Matrix& mat)
{
//	//半径比例随x比例
//	REITRACE;
//   dlhml::transformby2d_distance(mat, radius_);
//   //radius_ *= mat.value(0,0);
// 	center_.transformby(mat);
// 
//   pt1_.transformby(mat);
//   pt2_.transformby(mat);
//   pt3_.transformby(mat);
//   init_other();
  box_change(true);
  Point s, p, e;
  s = start();
  p = path();
  e = end();
  s.transformby(mat);
  p.transformby(mat);
  e.transformby(mat);
  set(s, p, e);
//   geo::Point gs, gp, ge;
//   gs = convert(s);
//   gp = convert(p);
//   ge = convert(e);
//   arc_.set(gs, gp, ge);
}

//void RArc::transformbyme(const Matrix& mat)
//{
////	//半径比例随x比例
////  if(mat.mat_type()==SCALE_MAT){
////  	radius_ *= mat.value(0,0);
////  }
//	REITRACE;
//  radius_ *= mat.value(0,0);
//	center_.transformby(mat);
//
//  pt1_.transformby(mat);
//  pt2_.transformby(mat);
//  pt3_.transformby(mat);
//  init_other();
//}
void RArc::drag_startme(const Matrix& mat)
{
}
void RArc::drag_endme(const Matrix& mat)
{
}

Entity* RArc::cloneme() const
{
	return new RArc(*this);
}

void RArc::closeme()
{
	delete this;
}

bool RArc::intersectme(const Rect& rect) const 
{ 
// 	TRACE_OUT("the pt1 point is		: (%f, %f)\n", this->pt1_.x, this->pt1_.y);
// 	TRACE_OUT("the pt2 point is		: (%f, %f)\n", this->pt2_.x, this->pt2_.y);
// 	TRACE_OUT("the pt3 point is		: (%f, %f)\n", this->pt3_.x, this->pt3_.y);
// 	TRACE_OUT("the rect.xmin() = %f\n", rect.xmin());
// 	TRACE_OUT("the rect.ymin() = %f\n", rect.ymin());
// 	TRACE_OUT("the rect.xmax() = %f\n", rect.xmax());
// 	TRACE_OUT("the rect.ymax() = %f\n", rect.ymax());
  Point st, ed, p1, p2;
  Line line; 
  st.setdata(rect.xmax(), rect.ymax(), 0.0);
  ed.setdata(rect.xmin(), rect.ymax(), 0.0);
  line.setdata(st,ed);
	if (intersect2d_a_s(*this, line, p1, p2) != 0){
// 		TRACE_OUT("the	up	side is the intersect side\n");
// 		TRACE_OUT("the intersect point num is %d\n", intersect2d_a_s(*this, line, p1, p2));
// 		TRACE_OUT("@@@@the p1 point is		: (%f, %f)\n", p1.x, p1.y);
// 		TRACE_OUT("@@@@the p2 point is		: (%f, %f)\n", p2.x, p2.y);
		return true;
	}

  st.setdata(rect.xmax(), rect.ymin(), 0.0);
  ed.setdata(rect.xmin(), rect.ymin(), 0.0);
  line.setdata(st,ed);
	if (intersect2d_a_s(*this, line, p1, p2) != 0){
// 		TRACE_OUT("the	down	side is the intersect side\n");
// 		TRACE_OUT("the intersect point num is %d\n", intersect2d_a_s(*this, line, p1, p2));
// 		TRACE_OUT("@@@@the p1 point is		: (%f, %f)\n", p1.x, p1.y);
// 		TRACE_OUT("@@@@the p2 point is		: (%f, %f)\n", p2.x, p2.y);
		return true;
	}

  st.setdata(rect.xmin(), rect.ymin(), 0.0);
  ed.setdata(rect.xmin(), rect.ymax(), 0.0);
  line.setdata(st,ed);
	if (intersect2d_a_s(*this, line, p1, p2) != 0){
// 		TRACE_OUT("the	left	side is the intersect side\n");
// 		TRACE_OUT("the intersect point num is %d\n", intersect2d_a_s(*this, line, p1, p2));
// 		TRACE_OUT("@@@@the p1 point is		: (%f, %f)\n", p1.x, p1.y);
// 		TRACE_OUT("@@@@the p2 point is		: (%f, %f)\n", p2.x, p2.y);
		return true;
	}

  st.setdata(rect.xmax(), rect.ymin(), 0.0);
  ed.setdata(rect.xmax(), rect.ymax(), 0.0);
  line.setdata(st,ed);
	if (intersect2d_a_s(*this, line, p1, p2) != 0){
// 		TRACE_OUT("the	right	side is the intersect side\n");
// 		TRACE_OUT("the intersect point num is %d\n", intersect2d_a_s(*this, line, p1, p2));
// 		TRACE_OUT("@@@@the p1 point is		: (%f, %f)\n", p1.x, p1.y);
// 		TRACE_OUT("@@@@the p2 point is		: (%f, %f)\n", p2.x, p2.y);
		return true;
	}
	

	

	
  return false;
} 

// bool RArc::intersectme(const Rect& rect) const 
// { 
//   Point st,ed,p1,p2;
//   Line line;
//   Entity_Calculate calc;
// 
//   st.setdata(rect.xmin(),rect.ymax(),0.0);
//   ed.setdata(rect.xmax(),rect.ymax(),0.0);
//   line.setdata(st,ed);
//   if(calc.line_insect_arc(p1,p2,line,*this)){
//     return true;
//   }
//   st.setdata(rect.xmax(),rect.ymax(),0.0);
//   ed.setdata(rect.xmax(),rect.ymin(),0.0);
//   line.setdata(st,ed);
//   if(calc.line_insect_arc(p1,p2,line,*this)){
//     return true;
//   }
//   st.setdata(rect.xmax(),rect.ymin(),0.0);
//   ed.setdata(rect.xmin(),rect.ymin(),0.0);
//   line.setdata(st,ed);
//   if(calc.line_insect_arc(p1,p2,line,*this)){
//     return true;
//   }
//   st.setdata(rect.xmin(),rect.ymin(),0.0);
//   ed.setdata(rect.xmin(),rect.ymax(),0.0);
//   line.setdata(st,ed);
//   if(calc.line_insect_arc(p1,p2,line,*this)){
//     return true;
//   }
// 
// //center
// //  if(center_.envelop(rect)){
// //    return true;
// //  }
// 
//   return false;
// } 

bool RArc::envelopme(const Rect& rect) const
{
	return box2d().envelop(rect);
}

// zhaoxinghua
// bool RArc::is_in(Float degree)const
// {
// 	Float stdst = start_degree_;
// 	dlhml::std_degree(stdst);
// 	Float stded = end_degree_;
// 	dlhml::std_degree(stded);
// 	Float stddeg = degree;
// 	dlhml::std_degree(stddeg);
// 
// 	if(dlhml::MoreEqu(stded,stdst))
// 		return dlhml::MoreEqu(stddeg,stdst) && dlhml::MoreEqu(stded,stddeg);
// 	else
// 		return (dlhml::MoreEqu(stddeg,stdst) && dlhml::MoreEqu(360,stddeg)) || dlhml::MoreEqu(stded,stddeg);
// }

//bool RArc::is_in(Float degree)const
//{
//  if(MoreEqu(degree,start_degree_) && LessEqu(degree,end_degree_)){
//    return true;
//  }
//  return false;
//}

Rect RArc::calc_box2d() const
{
  geo::Box gb;
  gb = arc_.box();

//   gb.min_.x = center().x - radius();
//   gb.min_.y = center().y - radius();
//   gb.max_.x = center().x + radius();
//   gb.max_.y = center().y + radius();

	Rect box_rc;
	box_rc.xmin(gb.min_.x);
	box_rc.ymin(gb.min_.y);
	box_rc.xmax(gb.max_.x);
	box_rc.ymax(gb.max_.y);
  box_rc.update();
	return box_rc;
}
// Rect RArc::calc_box2d() const
// {
// 	Rect box2d_;
// ////	Point st,ed;
// ////	get_end_point(st,ed);
// ////	Float minX = min(st.x, ed.x);
// ////	Float minY = min(st.y, ed.y);
// ////	Float maxX = max(st.x, ed.x);
// ////	Float maxY = max(st.y, ed.y);
// 
// //BET
// //  Float r=radius_*1.01;
// //  Float minX = center_.x - r; 
// //  Float minY = center_.y - r; 
// //  Float maxX = center_.x + r; 
// //  Float maxY = center_.y + r; 
// //
// //	Float M_PI = pi;
// //	Float M_PI_2 = pi/2;
// //
// //	Float a1 = start_degree_*pi/180;
// //	Float a2 = end_degree_  *pi/180;
// //
// //	// check for left limit:
// //	if ((a1<M_PI && a2>M_PI) ||	
// //		(a1>a2-1.0e-12 && a2>M_PI) ||	(a1>a2-1.0e-12 && a1<M_PI) ) {
// //		minX = min(center_.x - radius_, minX);
// //	}
// //	// check for right limit:
// //	if (a1 > a2-1.0e-12) {
// //		maxX = max(center_.x + radius_, maxX);
// //	}
// //// check for bottom limit:
// //	if ((a1<(M_PI_2*3) && a2>(M_PI_2*3)) || 
// //		(a1>a2-1.0e-12 && a2>(M_PI_2*3)) || (a1>a2-1.0e-12    && a1<(M_PI_2*3)) ) {
// //		minY = min(center_.y - radius_, minY);
// //	}
// //	// check for top limit:
// //	if ((a1<M_PI_2 && a2>M_PI_2) ||
// //		(a1>a2-1.0e-12   && a2>M_PI_2) ||	(a1>a2-1.0e-12   && a1<M_PI_2) ) {
// //		maxY = max(center_.y + radius_, maxY);
// //	}
// //TER
// 
//   Point st,ed;
//   st = start();
//   ed = end();
//   //get_end_point(st,ed);
//   Float r=radius()*1.01;
//   Float maxX = center().x + r; 
//   if(!is_in(0)){
//     maxX = max(st.x, ed.x);
//   }
//   Float maxY = center_.y + r; 
//   if(!is_in(90)){
//     maxY = max(st.y, ed.y);
//   }
//   Float minX = center_.x - r; 
//   if(!is_in(180)){
//     minX = min(st.x, ed.x);
//   }
//   Float minY = center_.y - r; 
//   if(!is_in(270)){
//     minY = min(st.y, ed.y);
//   }
// 
// 
// 	box2d_.xmin(minX);
// 	box2d_.ymin(minY);
// 	box2d_.xmax(maxX);
// 	box2d_.ymax(maxY);
// 	return box2d_;
// }
bool RArc::snap_endpointme(Point& pt,const Rect& rect) const
{
	Point st,ed;
  st=convert(arc_.start);
  ed=convert(arc_.end);
	//get_end_point(st,ed);
	if(st.envelop(rect)){
		pt = st;
		return true;
	}
	if(ed.envelop(rect)){
		pt = ed;
		return true;
	}
	return false;
}
bool RArc::snap_center_pointme(Point& pt,const Rect& rect) const
{
  Point c = convert(arc_.center());
	if(c.envelop(rect)){
		pt = c;
		return true;
	}
	return false;
}
//bool RArc::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////	Entity_Snap_Implement<RArc> imp(*this);
////	//Entity_Snap_Implement<Line> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool RArc::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}

//bet
bool RArc::snap_nearest_pointme(Point& pt,const Rect& rect)const
{
	Point o;
	o.x = (rect.xmax()+rect.xmin())/2.0;
	o.y = (rect.ymax()+rect.ymin())/2.0;

  Normal nor;
  nor.set_data(convert(arc_.center()), o);
  nor.set_unit();
  Point arcpt = convert(arc_.center()).polarTo(arc_.radius(), nor);
  if(arcpt.envelop(rect)){
    pt = arcpt;
    return true;
  }
  return false;
}
bool RArc::snap_middle_pointme(Point& pt,const Rect& rect)const
{
  Point midpt = middle();
  if(midpt.envelop(rect)){
    pt = midpt;
    return true;
  }
  return false;
}
 
void RArc::setctrl(const std::vector<Point>& pts)
{
  box_change(true);
  assert(pts.size()>=3);
  set(pts[0],pts[1],pts[2]);
}
void RArc::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(start());
  pts.push_back(path());
  pts.push_back(end());
}
int RArc::pt_count()const
{
  return 3;
} 
void RArc::setdrag(const std::vector<Point>& pts, int index)
{
  box_change(true);
  if(pts.size()<4){
    return;
  }
  //Point nor = pts[0]-center_;
  switch(index)
  {
  case 0:
    center(pts[0]);
    break;
  case 1:
    arc_.start = convert(pts[1]);
    break;
  case 2:
    arc_.path = convert(pts[2]);
    break;
  case 3:
    arc_.end = convert(pts[3]);
    break;
  }
}
void RArc::getdrag(std::vector<Point>& pts)const
{
  pts.push_back(convert(arc_.center()));
  pts.push_back(convert(arc_.start));
  pts.push_back(convert(arc_.path));
  pts.push_back(convert(arc_.end));
//  pts.push_back(middle());
//  pts.push_back(start ());
//  pts.push_back(end   ());
}

Float RArc::length_p()const
{
	Float sa = start_degree2d();
	Float ea = end_degree2d();
	std_degree(sa);
	std_degree(ea);
	Float degree = ea - sa;
	std_degree(degree);
	Float radian = degree_2_radian(degree);
	double len = radius() * radian;
	return len;
}

Float RArc::length_p(const Normal& nor)const
{
  Normal arc_nor(start(),end());
  arc_nor.set_unit();
  Float arc_len = length();
  Point nor_ed = start().polarTo(arc_len, arc_nor);

  Line ln(start(),nor_ed);
  return ln.length(nor);
}

Point RArc::polarTo_p(Float len, bool orderway)const
{
  Float rad = len/radius();
  Float deg = radian_2_degree(rad);
  std_radian(rad);
  if(orderway){
    deg = start_degree2d() + deg;
  }else{
    deg = end_degree2d()   - deg;
  }
  std_degree(deg);
  Normal nor;
  degree_2_normal2d(deg,nor);
  //Point pt = center_.polarTo(radius_,nor);
  return center().polarTo(radius(),nor);
}

void RArc::intersectme(const Entity& e , std::vector<Point>& pts)const
{
  if(&e == this){
    return;
  }
  e.intersect(*this, pts);
}
void RArc::intersectme(const Line & ln, std::vector<Point>& pts)const
{
//   Entity_Calculate calc;
//   Point pt1, pt2;
//   bool myre = calc.line_insect_arc(pt1, pt2, ln, *this);
//   if(myre){
//     pts.push_back(pt1);
//     pts.push_back(pt2);
//   }

	Point p1, p2;
	int xpt_count = intersect2d_a_s(*this, ln, p1, p2);
  dlhml::push_xpt(xpt_count, p1, p2, pts);
// 	if (intersection != 0){
// //		TRACE_OUT("the p1 point is		: (%f, %f)\n", p1.x, p1.y);
// //		TRACE_OUT("the p2 point is		: (%f, %f)\n", p2.x, p2.y);
//     pts.push_back(p1);
//     pts.push_back(p2);
// 	}
}
void RArc::intersectme(const RArc & ac, std::vector<Point>& pts)const
{
  if(&ac == this){
    return;
  }
  Entity_Calculate calc;
  Point pt1, pt2;
  bool myre = calc.arc_insect_arc(pt1, pt2, ac, *this);
  if(myre){
    pts.push_back(pt1);
    pts.push_back(pt2);
  }
  //return myre;
}
void RArc::intersectme(const Circle & cr, std::vector<Point>& pts)const
{
  Entity_Calculate calc;
  Point pt1, pt2;
  bool myre = calc.circle_insect_arc(pt1, pt2, cr, *this);
  if(myre){
    pts.push_back(pt1);
    pts.push_back(pt2);
  }
  //return myre;
}


//namespace
}
