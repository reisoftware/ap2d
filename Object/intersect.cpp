#include "StdAfx.h"
#include "intersect.h"
#include "Point.h"
#include "Line.h"
#include "RArc.h"
#include "Circle.h"
#include "geo_obj.h"
#include "../geometry/intersect.h"
#include "../include/getrace.h"

namespace dlhml{

bool is_disjoint(const Rect& rc1, const Rect& rc2)
{
  if(rc1.xmax() < rc2.xmin()){
    return true;
  }
  if(rc1.xmin() > rc2.xmax()){
    return true;
  }
  if(rc1.ymax() < rc2.ymin()){
    return true;
  }
  if(rc1.ymin() > rc2.ymax()){
    return true;
  }
  return false;
}



int intersect2d_l_l(const Line& lline1, const Line& lline2, Point& pt)
{
	geo::LLine gline1, gline2;
	geo::Point gpt;
	convert(lline1, gline1);
	convert(lline2, gline2);
	int inum = geo::intersect2d(gline1, gline2, gpt);
	pt = convert(gpt);
	return inum;
}
int intersect2d_l_r(const Line& lline, const Line& rline, Point& pt)
{
	geo::LLine glline;
	geo::RLine grline;
	convert(lline, glline);
	convert(rline, grline);
	geo::Point gpt;
	int inum = geo::intersect2d(grline, glline, gpt);
	pt = convert(gpt);
	return inum;
}
int intersect2d_l_s(const Line& lline, const Line& sline, Point& pt)
{
	geo::LLine glline;
	geo::SLine gsline;
	convert(lline, glline);
	convert(sline, gsline);
	geo::Point gpt;
	int inum = geo::intersect2d(gsline, glline,gpt);
	pt = convert(gpt);
	return inum;
}

int intersect2d_r_r(const Line& rline1, const Line& rline2, Point& pt)
{
	geo::RLine grline1;
	geo::RLine grline2;
	convert(rline1, grline1);
	convert(rline2, grline2);
	geo::Point gpt;
	int inum = geo::intersect2d(grline1, grline2,gpt);
	pt = convert(gpt);
	return inum;
}
int intersect2d_r_s(const Line& rline, const Line& sline, Point& pt)
{
	geo::RLine grline;
	geo::SLine gsline;
	convert(rline, grline);
	convert(sline, gsline);
	geo::Point gpt;
	int inum = geo::intersect2d(gsline, grline,gpt);
	pt = convert(gpt);
	return inum;
}

int intersect2d_s_s(const Line& sline1, const Line& sline2, Point& pt)
{
	geo::SLine gsline1;
	geo::SLine gsline2;
	convert(sline1, gsline1);
	convert(sline2, gsline2);
	geo::Point gpt;
	int inum = geo::intersect2d(gsline1, gsline2,gpt);
	pt = convert(gpt);
	return inum;
}

int intersect2d_c_l(const Circle& lhs, const Line & rhs, Point& pt1, Point& pt2)
{
	geo::Circle gcircle = convert(lhs);
	geo::LLine glline;
	convert(rhs, glline);
	geo::Point gpt1, gpt2;
	int inum = geo::intersect2d(gcircle, glline, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}
int intersect2d_c_r(const Circle& lhs, const Line & rhs, Point& pt1, Point& pt2)
{
	geo::Circle gcircle = convert(lhs);
	geo::RLine grline;
	convert(rhs, grline);
	geo::Point gpt1, gpt2;
	int inum = geo::intersect2d(gcircle, grline, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}
int intersect2d_c_s(const Circle& lhs, const Line & rhs, Point& pt1, Point& pt2)
{
	geo::Circle gcircle = convert(lhs);
	geo::SLine gsline;
	convert(rhs, gsline);
	geo::Point gpt1, gpt2;
	int inum = geo::intersect2d(gcircle, gsline, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}
int intersect2d_c_c(const Circle& lhs, const Circle& rhs, Point& pt1, Point& pt2)
{
	geo::Circle gcircle1 = convert(lhs);
	geo::Circle gcircle2 = convert(rhs);
	geo::Point gpt1, gpt2;
	int inum = geo::intersect2d(gcircle1, gcircle2, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}

int intersect2d_a_l(const RArc& lhs, const Line & lline, Point& pt1, Point& pt2)
{
	geo::Arc garc = lhs.get();
	geo::LLine glline;
	convert(lline, glline);
	geo::Point gpt1,gpt2;
	int inum = geo::intersect2d(garc, glline, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}
int intersect2d_a_r(const RArc& lhs, const Line & rline, Point& pt1, Point& pt2)
{
	geo::Arc garc = lhs.get();
	geo::RLine grline;
	convert(rline, grline);
	geo::Point gpt1, gpt2;
	int inum = geo::intersect2d(garc, grline, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}
int intersect2d_a_s(const RArc& lhs, const Line & sline, Point& pt1, Point& pt2)
{
	geo::Arc garc = lhs.get();
	geo::SLine gsline;
	convert(sline, gsline);
	geo::Point gpt1,gpt2;
	int inum = geo::intersect2d(garc, gsline, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}
int intersect2d_a_c(const RArc& lhs, const Circle& rhs, Point& pt1, Point& pt2)
{
	geo::Arc garc = lhs.get();
	geo::Circle gcircle = convert(rhs);
	geo::Point gpt1, gpt2;
	int inum = geo::intersect2d(garc, gcircle, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}
int intersect2d_a_a(const RArc& lhs, const RArc & rhs, Point& pt1, Point& pt2)
{
	geo::Arc garc1 = lhs.get();
	geo::Arc garc2 = rhs.get();
	geo::Point gpt1, gpt2;
	int inum = geo::intersect2d(garc1, garc2, gpt1, gpt2);
	pt1 = convert(gpt1);
	pt2 = convert(gpt2);
	return inum;
}

static bool equ_pt(const Point & pt, std::vector<Point> & pts)
{
	if (pts.empty()){
		return false;
	}
	for (int i = 0; i < pts.size(); i ++){
		if (pts[i] == pt){
			return true;
		}
	}
	return false;
}
static void push_pt(int pt_num, const Point& pt1, const Point& pt2, std::vector<Point> & pts)
{
  switch(pt_num){
  case 0:
    break;
  case 1:
		if (!equ_pt(pt1, pts)){
			pts.push_back(pt1);
		}
    break;
  case 2:
		if (!equ_pt(pt1, pts)){
			pts.push_back(pt1);
		}
		if (!equ_pt(pt2, pts)){
			pts.push_back(pt2);
		}
    break;
  }
}
static void push_point(const Line & sl1, const Line & sl2,  std::vector<Point> & pts)
{
	Point pt;
	if (!intersect2d_s_s(sl1, sl2, pt) && !equ_pt(pt, pts)){
		pts.push_back(pt);
	}
}
void intersect2d_rt_s(const Rect& rect, const Line& sline, std::vector<Point>& pts)
{
	Point pt1(rect.xmin(), rect.ymin()), pt2(rect.xmin(), rect.ymax());
	Point pt3(rect.xmax(), rect.ymin()), pt4(rect.xmax(), rect.ymax());
	Line l1(pt1, pt2), l2(pt1, pt3), l3(pt2, pt4), l4(pt3, pt4);
	
	push_point(sline, l1, pts);
	push_point(sline, l2, pts);
	push_point(sline, l3, pts);
	push_point(sline, l4, pts);
}

static void push_point(const Circle & c, const Line & sline, std::vector<Point> & pts)
{
	Point pt1, pt2;
	int n = intersect2d_c_s(c, sline, pt1, pt2);
	push_pt(n, pt1, pt2, pts);
}
void intersect2d_rt_c(const Rect & rect, const Circle & c, std::vector<Point> & pts)
{
	Point pt1(rect.xmin(), rect.ymin()), pt2(rect.xmin(), rect.ymax());
	Point pt3(rect.xmax(), rect.ymin()), pt4(rect.xmax(), rect.ymax());
	Line l1(pt1, pt2), l2(pt1, pt3), l3(pt2, pt4), l4(pt3, pt4);

	push_point(c, l1, pts);
	push_point(c, l2, pts);
	push_point(c, l3, pts);
	push_point(c, l4, pts);
}

static void push_point(const RArc & arc, const Line & sline, std::vector<Point> & pts)
{
	Point pt1, pt2;
	int n = intersect2d_a_s(arc, sline, pt1, pt2);
	push_pt(n, pt1, pt2, pts);
}
void intersect2d_rt_a(const Rect & rect, const RArc & arc, std::vector<Point> & pts)
{
	Point pt1(rect.xmin(), rect.ymin()), pt2(rect.xmin(), rect.ymax());
	Point pt3(rect.xmax(), rect.ymin()), pt4(rect.xmax(), rect.ymax());
	Line l1(pt1, pt2), l2(pt1, pt3), l3(pt2, pt4), l4(pt3, pt4);

	push_point(arc, l1, pts);
	push_point(arc, l2, pts);
	push_point(arc, l3, pts);
	push_point(arc, l4, pts);
}


void push_xpt(int xpt_count, const Point& pt1, const Point& pt2, std::vector<Point>& pts)
{
  switch(xpt_count)
  {
  case 0:
    break;
  case 1:
    pts.push_back(pt1);
    break;
  case 2:
    pts.push_back(pt1);
    pts.push_back(pt2);
    break;
  }
}



}//namespace
