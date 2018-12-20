
#ifndef _GEOMETRY_GLOBAL_H_
#define _GEOMETRY_GLOBAL_H_

#include "export.h"

#include "Arc.h"

#include "Float.h"

#include <vector>

namespace geo{

class Point;
class Plane;
class Arc;

//globle functions declare...
GEOAPI bool isin(const Point& pt, const Point * pPtPolygon, int nCount);
GEOAPI bool isin(const Point& pt, const std::vector<Point>& polygon);
GEOAPI int compare(const Point& the, const Plane& datum);

GEOAPI Arc  get_arc(const Point& c, Float r, Float sdegree, Float edegree);
GEOAPI bool get_arc(const Arc& arc, Point& c, Float& r, Float& sdegree, Float& edegree);

}//namespace
#endif//FILE
