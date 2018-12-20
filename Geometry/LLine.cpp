
#include "StdAfx.h"
#include "LLine.h"

#include "intersect.h"

namespace geo{

LLine::LLine(const Point& pt1, const Point& pt2)
MCT_INIT1("geo:LLine")
{
  set(pt1, pt2);
}
//void LLine::set(const Point& pt1, const Point& pt2)
//{
//  this->pt1 = pt1;
//  this->pt2 = pt2;
//}

void LLine::intersect2d(const LLine& rhs, std::vector<Point>& pts)const
{
  Point pt;
  int num = geo::intersect2d(*this, rhs, pt);
  if(!num){
    return;
  }
  pts.push_back(pt);
}

}//namespace

