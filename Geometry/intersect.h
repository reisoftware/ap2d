#ifndef _GEOMETRY_INTERSECT_H_
#define _GEOMETRY_INTERSECT_H_
#include "export.h"
#include <set>

namespace geo{

class Point;
class LLine;
class RLine;
class SLine;
class Circle;
class Arc;
class Box;

////返回值表示交点数量，没有交点返回0.
////交点写入pt参数.
GEOAPI int intersect2d(const LLine& ln1, const LLine& ln2, Point& pt);

GEOAPI int intersect2d(const RLine& ln1, const LLine& ln2, Point& pt);
GEOAPI int intersect2d(const RLine& ln1, const RLine& ln2, Point& pt);

GEOAPI int intersect2d(const SLine& ln1, const LLine& ln2, Point& pt);
GEOAPI int intersect2d(const SLine& ln1, const RLine& ln2, Point& pt);
GEOAPI int intersect2d(const SLine& ln1, const SLine& ln2, Point& pt);

GEOAPI int intersect2d(const Circle& lhs, const LLine & rhs, Point& pt1, Point& pt2);
GEOAPI int intersect2d(const Circle& lhs, const RLine & rhs, Point& pt1, Point& pt2);
GEOAPI int intersect2d(const Circle& lhs, const SLine & rhs, Point& pt1, Point& pt2);
GEOAPI int intersect2d(const Circle& lhs, const Circle& rhs, Point& pt1, Point& pt2);

GEOAPI int intersect2d(const Arc& lhs, const LLine & rhs, Point& pt1, Point& pt2);
GEOAPI int intersect2d(const Arc& lhs, const RLine & rhs, Point& pt1, Point& pt2);
GEOAPI int intersect2d(const Arc& lhs, const SLine & rhs, Point& pt1, Point& pt2);
GEOAPI int intersect2d(const Arc& lhs, const Circle& rhs, Point& pt1, Point& pt2);
GEOAPI int intersect2d(const Arc& lhs, const Arc   & rhs, Point& pt1, Point& pt2);

GEOAPI void intersect2d(const LLine& ln, const Box& box, std::set<Point>& pts);
GEOAPI void intersect2d(const RLine& rl, const Box& box, std::set<Point>& pts);
GEOAPI void intersect2d(const SLine& sl, const Box& box, std::set<Point>& pts);
GEOAPI void intersect2d(const Circle& c, const Box& box, std::set<Point>& pts);
GEOAPI void intersect2d(const Arc& arc, const Box& box, std::set<Point>& pts);
GEOAPI void intersect2d(const Box& box1, const Box& box2, std::set<Point>& pts);

}//namespace


#endif//FILE
