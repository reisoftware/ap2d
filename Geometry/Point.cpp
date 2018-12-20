
#include "StdAfx.h"
#include "math.h"

#include "Point.h"
#include "Normal.h"

namespace geo{

//Point::Point()
//:x(0)
//,y(0)
//,z(0)
//{
//}
Point::Point(Float x, Float y, Float z)
:x(x)
,y(y)
,z(z)
MCT_INIT2("geo:Point")
{
}
void Point::set(Float x, Float y, Float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

//const Point& Point::operator = (const Point& rhs)
//{
//}

bool Point::operator == (const Point& rhs) const
{
  return equ(x, rhs.x) && equ(y,rhs.y) && equ(z,rhs.z);
  //return true;
}
bool Point::operator != (const Point& rhs) const
{
  return !(*this == rhs);
}

Point Point::operator + (const Point& rhs) const
{
  Point pt;
  pt.x = x + rhs.x;
  pt.y = y + rhs.y;
  pt.z = z + rhs.z;
  return pt;
}
Point Point::operator - (const Point& rhs) const
{
  Point pt;
  pt.x = x - rhs.x;
  pt.y = y - rhs.y;
  pt.z = z - rhs.z;
  return pt;
}
//Point Point::operator * (Float f) const
//{
//  Point pt;
//  pt.x = x * f;
//  pt.y = y * f;
//  pt.z = z * f;
//  return pt;
//}
Point Point::operator / (Float f) const
{
  Point pt;
  pt.x = x / f;
  pt.y = y / f;
  pt.z = z / f;
  return pt;
}
Point& Point::operator +=(const Point& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}
Point& Point::operator -=(const Point& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  return *this;
}

Float Point::distance(const Point & rhs) const
{
  return sqrt( (rhs.x - x)*(rhs.x - x)
              +(rhs.y - y)*(rhs.y - y)
              +(rhs.z - z)*(rhs.z - z) );
}
Float Point::distance2d(const Point & rhs) const
{
  return sqrt( (rhs.x - x)*(rhs.x - x)
              +(rhs.y - y)*(rhs.y - y) );
  //          +(rhs.z - z)*(rhs.z - z)
}
Point Point::polarto (const Normal& nor, Float dis) const
{
  Point pt;
  pt.x = x + dis * nor.x;
  pt.y = y + dis * nor.y;
  pt.z = z + dis * nor.z;
  return pt;
}


//void Point::x(Float x)
//{
//  x_ = x;
//}
//void Point::y(Float y)
//{
//  y_ = y;
//}
//void Point::z(Float z)
//{
//  z_ = z;
//}
//Float Point::x()const
//{
//  return x_;
//}
//Float Point::y()const
//{
//  return y_;
//}
//Float Point::z()const
//{
//  return z_;
//}

}//namespace

