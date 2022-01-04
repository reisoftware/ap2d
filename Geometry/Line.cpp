	
#include "StdAfx.h"
#include "Line.h"

namespace geo{


Line::Line(const Point& pt1, const Point& pt2)
MCT_INIT1("geo:Line")
{
  set(pt1, pt2);
}
void Line::set(const Point& pt1, const Point& pt2)
{
  this->pt1 = pt1;
  this->pt2 = pt2;
}

bool Line::operator == (const Line& o)const
{
  if(pt1 == o.pt1 && pt2 == o.pt2){
    return true;
  }
  if(pt1 == o.pt2 && pt2 == o.pt1){
    return true;
  }
  return false;
}

Point Line::middle()const
{
  return (pt1 + pt2) / 2 ;
}


//void Line::start(const Point& st)
//{
//  st_ = st;
//}
//void Line::end(const Point& ed)
//{
//  ed_ = ed;
//}
//Point Line::start()const
//{
//  return st_;
//}
//Point Line::end()const
//{
//  return ed_;
//}


}//namespace


