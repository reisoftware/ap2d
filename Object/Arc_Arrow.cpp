
#include "stdafx.h"
#include "Arc_Arrow.h"
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
#include <cassert>

#include "Line.h"
#include "Cloud_Line.h"
#include "lua_tab.h"

//#include "angle_radian.h"
#include "fstream"
//#include "..\DrawDll\reitrace.h"
#include "getrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Arc_Arrow,Entity)
Arc_Arrow::Arc_Arrow()
MCT_INIT1("Arc_Arrow")
{
  show_change(true);
  //dim_style_val_.arrow_num(ARROW_DOUBLE);
//  myclass_ = "Arc_Arrow";
}

Arc_Arrow::Arc_Arrow(const RArc& ac)
MCT_INIT1("Arc_Arrow")
{
  show_change(true);
  arc_ = ac;
}

Arc_Arrow::~Arc_Arrow() 
{ 
} 


///////////////////////////// <<write>> ///////////////////////////////
void Arc_Arrow::set(const Point& pt1, const Point& pt2, const Point& pt3)
{
  show_change(true);
  arc_.set(pt1, pt2, pt3);
}
void Arc_Arrow::set(const Point& c, const Point& s, const Point& e, const Point& p)
{
  show_change(true);
  arc_.set(c, s, e, p);
}
void Arc_Arrow::set_radian2d(const Point& c, Float r, Float srad, Float erad)
{
  show_change(true);
  arc_.set_radian2d(c, r, srad, erad);
}
void Arc_Arrow::set_degree2d(const Point& c, Float r, Float sdeg, Float edeg)
{
  show_change(true);
  arc_.set_degree2d(c, r, sdeg, edeg);
}
  
void Arc_Arrow::center(const Point& pt)
{
  show_change(true);
  arc_.center(pt);
}
void Arc_Arrow::radius(Float r)
{
  show_change(true);
  arc_.radius(r);
}
void Arc_Arrow::start(const Point& pt)
{
  show_change(true);
  arc_.start(pt);
}
void Arc_Arrow::path(const Point& pt)
{
  show_change(true);
  arc_.path(pt);
}
void Arc_Arrow::end(const Point& pt)
{
  show_change(true);
  arc_.end(pt);
}

  
///////////////////////////// <<read>> ///////////////////////////////
RArc Arc_Arrow::get()const
{
  return arc_;
}

Point Arc_Arrow::center()const
{
  return arc_.center();
}

Float Arc_Arrow::radius()const
{
  return arc_.radius();
}
  
Float Arc_Arrow::radian()const
{
  return arc_.radian();
}

Float Arc_Arrow::degree()const
{
  return arc_.degree();
}
  
Float Arc_Arrow::start_radian2d()const
{
  return arc_.start_radian2d();
}

Float Arc_Arrow::start_degree2d()const
{
  return arc_.start_degree2d();
}
  
Float Arc_Arrow::end_radian2d()const
{
  return arc_.end_radian2d();
}

Float Arc_Arrow::end_degree2d()const
{
  return arc_.end_degree2d();
}
 
Float Arc_Arrow::middle_radian2d()const
{
  return arc_.middle_radian2d();
}

Float Arc_Arrow::middle_degree2d()const
{
  return arc_.middle_degree2d();
}

//3d point
Point Arc_Arrow::middle()const
{
  return arc_.middle();
}

Point Arc_Arrow::start()const
{
  return arc_.start();
}

Point Arc_Arrow::end()const
{
  return arc_.end();
}

Point Arc_Arrow::path()const
{
  return arc_.path();
}

//2d point
Point Arc_Arrow::middle2d()const
{
  return arc_.middle2d();
}

Point Arc_Arrow::start2d()const
{
  return arc_.start2d();
}

Point Arc_Arrow::path2d()const
{
  return arc_.path2d();
}

Point Arc_Arrow::end2d()const
{
  return arc_.end2d();
}




///////////////////////////// <<virtual>> ///////////////////////////////

bool Arc_Arrow::visit(Visitor& v)
{
  show_change(true);
  std::ofstream f("D:/Arc_Arrow-visit",std::ios_base::app|std::ios_base::out);
  f<<"1\n";
	return v.Visit_Arc_Arrow(*this);
}
// void Arc_Arrow::get_end_point(Point& st,Point& ed) const
// {
//   st = arc_.start();
//   ed = arc_.end();
//   //arc_.get_end_point(st,ed);
// }
// 
//  
// void Arc_Arrow::set_start_pt(const Point& pt)
// {
//   show_change(true);
//   arc_.set_start_pt(pt);
// }
//  
// void Arc_Arrow::set_path_pt(const Point& pt)
// {
//   show_change(true);
//   arc_.set_path_pt(pt);
// }
// 
// void Arc_Arrow::set_end_pt(const Point& pt)
// {
//   show_change(true);
//   arc_.set_end_pt(pt);
// }
//  
// void Arc_Arrow::getdata(Point& pt1,Point& pt2,Point& pt3)const
// {
//   arc_.getdata(pt1,pt2,pt3);
// }
//  
// Point Arc_Arrow::get_start_pt()const
// {
//   return arc_.get_start_pt();
// }
// 
// Point Arc_Arrow::get_path_pt()const
// {
//   return arc_.get_path_pt();
// }
// 
// Point Arc_Arrow::get_end_pt()const
// {
//   return arc_.get_end_pt();
// }
// 
// Point Arc_Arrow::get_middle_pt()const
// {
//   return arc_.get_middle_pt();
// }
// 
// 
// 
// 
// void Arc_Arrow::center(const Point& c)
// {
//   show_change(true);
//   arc_.center(c);
// }
// void Arc_Arrow::radius(Float r)
// {
//   show_change(true);
//   arc_.radius(r);
// }
// void Arc_Arrow::start_degree(Float a)
// {
//   show_change(true);
//   arc_.start_degree(a);
// }
// void Arc_Arrow::end_degree(Float a)
// {
//   show_change(true);
//   arc_.end_degree(a);
// }
// void Arc_Arrow::start_radian(Float a)
// {
//   show_change(true);
//   arc_.start_radian(a);
// }
// void Arc_Arrow::end_radian(Float a)
// {
//   show_change(true);
//   arc_.end_radian(a);
// }
// 
// void Arc_Arrow::getdata(RArc& ac)const
// {
//   ac = arc_;
// }
// void Arc_Arrow::setdata(const Point& c,Float r,Float stang,Float edang)
// {
//   show_change(true);
//   arc_.setdata(c,r,stang,edang);
// }
// void Arc_Arrow::setdata(const Point& c,const Point& st,const Point& ed,const Point& path)
// {
//   show_change(true);
//   arc_.setdata(c,st,ed,path);
// }
// 
// //获得穿过三点的正圆的圆心和半径
// //如果三点成直线返回值：FALSE
// bool Arc_Arrow::setdata(const Point& start,const Point& path,const Point& end)
// {
//   show_change(true);
//   return arc_.setdata(start,path,end);
// }


void Arc_Arrow::loadme(File& in)
{
  arc_.load(in);
}
void Arc_Arrow::saveme(const File& out) const
{
  arc_.save(out);
}
void Arc_Arrow::open_luame(lua_State *l)
{
	TRACE_OUT("Arc_Arrow open in open_luame()\n");
	arc_.open_lua(l,"arc_");
	txt_change(true);

}
void Arc_Arrow::save_luame(std::ofstream &out,int tab_num)
{
	arc_.save_lua(out,"arc_",tab_num);
}
void Arc_Arrow::get_strme(char *out)
{
	arc_.get_str(out);
}
void Arc_Arrow::set_from_strme(char *in)
{
	arc_.set_from_str(in);
}

void Arc_Arrow::edit_propertyme(const Edit_Entity& edit)
{
	//edit.edit_arc_arrow(*this);
}

// void Arc_Arrow::drawme(Draw_Entity& out) const
// {
// 	out.draw_arc(*this);
// }
// void Arc_Arrow::xor_drawme(Draw_Entity& out) const
// {
// 	out.xor_draw_arc(*this);
// }

errorinfo Arc_Arrow::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Arc_Arrow::transformbyme(const Matrix& mat)
{
	//REITRACE;
  show_change(true);
  arc_.transformby(mat);
}
void Arc_Arrow::drag_startme(const Matrix& mat)
{
  show_change(true);
}
void Arc_Arrow::drag_endme(const Matrix& mat)
{
  show_change(true);
}

Entity* Arc_Arrow::cloneme() const
{
	return new Arc_Arrow(*this);
}

void Arc_Arrow::closeme()
{
	delete this;
}

bool Arc_Arrow::intersectme(const Rect& rect) const 
{
  return arc_.intersect(rect);
} 
bool Arc_Arrow::envelopme(const Rect& rect) const
{
	return box2d().envelop(rect);
}

Rect Arc_Arrow::calc_box2d() const
{
  return arc_.box2d();
}
bool Arc_Arrow::snap_endpointme(Point& pt,const Rect& rect) const
{
  return arc_.snap_endpoint(pt,rect);
// 	Point st,ed;
//   st=pt1_;
//   ed=pt3_;
// 	//get_end_point(st,ed);
// 	if(st.envelop(rect)){
// 		pt = st;
// 		return true;
// 	}
// 	if(ed.envelop(rect)){
// 		pt = ed;
// 		return true;
// 	}
// 	return false;
}
bool Arc_Arrow::snap_center_pointme(Point& pt,const Rect& rect) const
{
  return arc_.snap_center_point(pt,rect);
// 	if(center_.envelop(rect)){
// 		pt = center_;
// 		return true;
// 	}
// 	return false;
}
//bool Arc_Arrow::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////	Entity_Snap_Implement<RArc> imp(*this);
////	//Entity_Snap_Implement<Line> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Arc_Arrow::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,arc_);
}

//bet
bool Arc_Arrow::snap_nearest_pointme(Point& pt,const Rect& rect)const
{
  return arc_.snap_nearest_point(pt,rect);
// 	Point o;
// 	o.x = (rect.xmax()+rect.xmin())/2.0;
// 	o.y = (rect.ymax()+rect.ymin())/2.0;
// 
//   Normal nor;
//   nor.set_data(center_, o);
//   nor.set_unit();
//   Point arcpt = center_.polarTo(radius_, nor);
//   if(arcpt.envelop(rect)){
//     pt = arcpt;
//     return true;
//   }
//   return false;
}
bool Arc_Arrow::snap_middle_pointme(Point& pt,const Rect& rect)const
{
  return arc_.snap_middle_point(pt,rect);
//   Point midpt = get_middle_pt();
//   if(midpt.envelop(rect)){
//     pt = midpt;
//     return true;
//   }
//   return false;
}
 
void Arc_Arrow::setctrl(const std::vector<Point>& pts)
{
  show_change(true);
  assert(pts.size()>=3);
  set(pts[0],pts[1],pts[2]);
}
void Arc_Arrow::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(start());
  pts.push_back(path());
  pts.push_back(end());
}
int Arc_Arrow::pt_count()const
{
  return 3;
} 
void Arc_Arrow::setdrag(const std::vector<Point>& pts, int index)
{
  show_change(true);
  arc_.setdrag(pts,index);
//  if(pts.size()<4){
//    return;
//  }
//  //Point nor = pts[0]-center_;
//  switch(index)
//  {
//  case 0:
//    center(pts[0]);
//    break;
//  case 1:
//    set_start_pt(pts[1]);
//    break;
//  case 2:
//    set_path_pt (pts[2]);
//    break;
//  case 3:
//    set_end_pt  (pts[3]);
//    break;
//  }
}
void Arc_Arrow::getdrag(std::vector<Point>& pts)const
{
  arc_.getdrag(pts);
//  pts.push_back(center_);
//  pts.push_back(pt1_   );
//  pts.push_back(pt2_   );
//  pts.push_back(pt3_   );
//  //  pts.push_back(middle());
//  //  pts.push_back(start ());
//  //  pts.push_back(end   ());
}


Float Arc_Arrow::length_p()const
{
  return arc_.length();
}

Float Arc_Arrow::length_p(const Normal& nor)const
{
  return arc_.length(nor);
}

Point Arc_Arrow::polarTo_p(Float len, bool orderway)const
{
  return arc_.polarTo(len,orderway);
}

// void Arc_Arrow::intersectme(const Entity& e , std::vector<Point>& pts)const
// {
//   if(&e == this){
//     return;
//   }
//   e.intersect(*this, pts);
// }

void Arc_Arrow::get_line(std::vector<Entity*>& es)const
{
  RArc * ln = RArc::create_me();
  *ln = arc_;
  ln->color_index(dim_style_val_.line_color());
  ln->line_style(line_style());
  es.push_back(ln);
}
void Arc_Arrow::get_show(std::vector<Entity*>& es)const
{
  get_line(es);
  dim_style_val_.get_arrow(arc_,es);
}


//namespace
}
