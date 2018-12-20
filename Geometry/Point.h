
#ifndef _GEOMETRY_POINT_H_
#define _GEOMETRY_POINT_H_

#include "export.h"
#include "Float.h"
#include "../afc/counter.h"

namespace geo{

class Normal;
//class Point;
//typedef Point Normal;

class GEOAPI Point
{
public:
  Float x;
  Float y;
  Float z;

public:
  Float distance(const Point & rhs) const;
  Float distance2d(const Point & rhs) const;
  Point polarto (const Normal& nor, Float dis) const;
  
public:
  //Point();
  //Point(const Point& rhs);
  Point(Float x=0, Float y=0, Float z=0);

public:
  void set(Float x=0, Float y=0, Float z=0);
  
public:
  //const Point& operator = (const Point& rhs);

  bool operator == (const Point& rhs) const;
  bool operator != (const Point& rhs) const;
  
  Point  operator + (const Point& rhs) const;
  Point  operator - (const Point& rhs) const;
  //Point  operator * (Float f) const;
  Point  operator / (Float f) const;
  Point& operator +=(const Point& rhs);
  Point& operator -=(const Point& rhs);


private:
	MCT_DEF
};

const Point ORG;

//class GEOAPI Point
//{
//public:
//  void   x(Float x);
//  void   y(Float y);
//  void   z(Float z); 
//  Float x()const;
//  Float y()const;
//  Float z()const;
//  
//private:
//  Float x_;
//  Float y_;
//  Float z_;
//};

}

#endif


