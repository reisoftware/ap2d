
#ifndef _GEOMETRY_LLINE_H_
#define _GEOMETRY_LLINE_H_

#include <vector>
#include "export.h"
#include "Point.h"
#include "Line.h"
#include "../afc/counter.h"

namespace geo{
////Ö±Ïß
class GEOAPI LLine : public Line
{
public:
  LLine(const Point& pt1=ORG, const Point& pt2=ORG);
	std::string get()const {return "LLine";}
public:
  void intersect2d(const LLine& rhs, std::vector<Point>& pts) const;
private:
	MCT_DEF
};

//public:
//  Point pt1;
//  Point pt2;
//  
//public:
//  void set(const Point& pt1=ORG, const Point& pt2=ORG);
//  

}
#endif
