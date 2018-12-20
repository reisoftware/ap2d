
#ifndef _GEOMETRY_LINE_H_
#define _GEOMETRY_LINE_H_

#include "export.h"
#include "Point.h"
#include "../afc/counter.h"

namespace geo{

class GEOAPI Line 
{
public:
  Point pt1;
  Point pt2;
  
public:
  Line(const Point& pt1=ORG, const Point& pt2=ORG);
  void set(const Point& pt1=ORG, const Point& pt2=ORG);

public:
  bool operator == (const Line& o)const;

public:
  Point middle()const;
private:
	MCT_DEF
};


////直线
//class GEOAPI LLine
//{
//public:
//  Point pt1;
//  Point pt2;
//
//public:
//  void intersect(const LLine& )
//};
////射线
//class GEOAPI RLine
//{
//public:
//  Point pt1;
//  Point pt2;
//};
////线段
//class GEOAPI SLine
//{
//public:
//  Point pt1;
//  Point pt2;
//};

//class GEOAPI Line 
//{
//public:
//  void  start(const Point& st);
//  void  end  (const Point& ed);
//  Point start()const;
//  Point end  ()const;
//
//private:
//  Point st_;
//  Point ed_;
//};

}

#endif//FILE
