
#include "StdAfx.h"
#include "SLine.h"

#include "intersect.h"

namespace geo{
  
SLine::SLine(const Point& pt1, const Point& pt2)
MCT_INIT1("geo:SLine")
{
  set(pt1, pt2);
}
//void SLine::set(const Point& pt1, const Point& pt2)
//{
//  this->pt1 = pt1;
//  this->pt2 = pt2;
//}

void SLine::intersect2d(const LLine& rhs, std::vector<Point>& pts)const
{
  Point pt;
  int num = geo::intersect2d(*this, rhs, pt);
  if(!num){
    return;
  }
  pts.push_back(pt);
}
void SLine::intersect2d(const RLine& rhs, std::vector<Point>& pts)const
{
  Point pt;
  int num = geo::intersect2d(*this, rhs, pt);
  if(!num){
    return;
  }
  pts.push_back(pt);
}
void SLine::intersect2d(const SLine& rhs, std::vector<Point>& pts)const
{
  Point pt;
  int num = geo::intersect2d(*this, rhs, pt);
  if(!num){
    return;
  }
  pts.push_back(pt);
}
  
}//namespace

