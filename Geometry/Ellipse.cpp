
#include "StdAfx.h"
#include "Ellipse.h"

namespace geo{

Ellipse::Ellipse()
MCT_INIT1("geo:Ellipse")
{

}

void Ellipse::intersect2d(const LLine& rhs, std::vector<Point>& pts)const
{
  //NOOK
}
void Ellipse::intersect2d(const RLine& rhs, std::vector<Point>& pts)const
{

  //NOOK
}
void Ellipse::intersect2d(const SLine& rhs, std::vector<Point>& pts)const
{
  //NOOK
}
void Ellipse::intersect2d(const Circle& rhs, std::vector<Point>& pts)const
{
  //NOOK
}
void Ellipse::intersect2d(const Arc& rhs, std::vector<Point>& pts)const
{
  //NOOK
}
void Ellipse::intersect2d(const Ellipse& rhs, std::vector<Point>& pts)const
{
  //NOOK
}
  
}//namespace

