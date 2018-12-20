
#ifndef _GEOMETRY_SLINE_H_
#define _GEOMETRY_SLINE_H_

#include <vector>
#include "export.h"
#include "Point.h"
#include "Line.h"
#include "../afc/counter.h"

namespace geo{
  
class LLine;
class RLine;

////Ïß¶Î
class GEOAPI SLine : public Line
{
public:
  SLine(const Point& pt1=ORG, const Point& pt2=ORG);
	std::string get()const{return "SLine";}
public:
  void intersect2d(const LLine& rhs, std::vector<Point>& pts) const;
  void intersect2d(const RLine& rhs, std::vector<Point>& pts) const;
  void intersect2d(const SLine& rhs, std::vector<Point>& pts) const;
private:
	MCT_DEF
};

//public:
//  Point pt1;
//  Point pt2;
//  
//public:
//  void set(const Point& pt1=ORG, const Point& pt2=ORG);
  
  
  
}
#endif
