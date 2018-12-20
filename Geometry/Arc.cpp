
#include "StdAfx.h"
#include "Arc.h"
#include "Circle.h"
#include "box.h"
#include "intersect.h"
#include "calculate.h"
#include "tools2d.h"

namespace geo{

Arc::Arc(const Point& s, const Point& p, const Point& e)
MCT_INIT1("geo:Arc")
{
	set(s, p, e);
}

///////////////////////// << write >> ////////////////////////
void Arc::set(const Point& s, const Point& p, const Point& e)
{
	this->start = s;
	this->path = p;
	this->end = e;
}

void Arc::set(const Point& c, const Point& s, const Point& e, const Point& p)
{
  arc2d(*this, c, s, e, p);
}


void Arc::set_radian2d(const Point& c, Float r, Float srad, Float erad)
{
  arc2d(*this, c, r, srad, erad);
}

void Arc::set_degree2d(const Point& c, Float r, Float sdeg, Float edeg)
{
  Float srad = degree_2_radian(sdeg);
  Float erad = degree_2_radian(edeg);
  set_radian2d(c, r, srad, erad);
}

void Arc::center(const Point& c)
{
  geo::set_arc_center(*this, c);
}

void Arc::radius(Float r)
{
  geo::set_arc_radius(*this, r);
}



///////////////////////// << read >> ////////////////////////
Point Arc::middle()const
{
  if(!geo::is_arc(*this)){
    return Point();
  }
  return geo::arc_middle_pt(*this);
}

Point Arc::center()const
{
  if(!is_arc(*this)){
    return center_;
  }
  Circle cir;
  geo::resume_circle(*this, cir);
  return cir.center;
  //return geo::get_center(*this);
}

Float Arc::radius()const
{
  if(!is_arc(*this)){
    return 0;
  }
  return geo::get_radius(*this);
}

////ÕÅ¿ª½Ç¶È
Float Arc::radian()const
{
  if(!is_arc(*this)){
    return 0;
  }
  return geo::get_angle(*this);
}
Float Arc::degree()const
{
  return geo::radian_2_degree(radian());
}

//start 2d
Float Arc::start_radian2d()const
{
  if(!geo::is_arc2d(*this)){
    return 0;
  }
  return geo::arc2d_srad(*this);
}
Float Arc::start_degree2d()const
{
  return geo::radian_2_degree(start_radian2d());
}

//end 2d
Float Arc::end_radian2d()const
{
  if(!geo::is_arc2d(*this)){
    return 0;
  }
  return geo::arc2d_erad(*this);
}
Float Arc::end_degree2d()const
{
  return geo::radian_2_degree(end_radian2d());
}

//middle
Float Arc::middle_radian2d()const
{
  if(!geo::is_arc(*this)){
    return 0;
  }
  return geo::arc_middle_rad(*this);
}
Float Arc::middle_degree2d()const
{
  return geo::radian_2_degree(middle_radian2d());
}

//2d point
Point Arc::middle2d()const
{
  Point pt = middle();
  pt.z = 0;
  return pt;
}

Point Arc::start2d()const
{
  Point pt;
  if(is_ccw2d()){
    pt = start;
  }else{
    pt = end;
  }
  pt.z = 0;
  return pt;
}

Point Arc::path2d()const
{
  Point pt = path;
  pt.z =0;
  return pt;
}

Point Arc::end2d()const
{
  Point pt;
  if(is_ccw2d()){
    pt = end;
  }else{
    pt = start;
  }
  pt.z = 0;
  return pt;
}



Box Arc::box()const
{
  assert(this);
  return geo::get_arc_box(*this);
}

///////////////////////// << intersect2d >> ////////////////////////
void Arc::intersect2d(const RLine& rhs, std::vector<Point>& pts)const
{
	Point pt1, pt2;
	int num = geo::intersect2d(*this, rhs, pt1, pt2);
	
	if(num == 1){
		pts.push_back(pt1);
	}
	else if(num == 2){
		pts.push_back(pt1);
		pts.push_back(pt2);
	}
	else{
	}
}
void Arc::intersect2d(const SLine& rhs, std::vector<Point>& pts)const
{
	Point pt1, pt2;
	int num = geo::intersect2d(*this, rhs, pt1, pt2);
	
	if(num == 1){
		pts.push_back(pt1);
	}
	else if(num == 2){
		pts.push_back(pt1);
		pts.push_back(pt2);
	}
	else{
	}
}
void Arc::intersect2d(const Circle& rhs, std::vector<Point>& pts)const
{
  //NOOK
}
void Arc::intersect2d(const Arc& rhs, std::vector<Point>& pts)const
{
  //NOOK
}


///////////////////////// << private >> ////////////////////////
bool Arc::is_ccw2d()const
{
  return geo::is_ccw2d(*this);
}

  
}//namespace

