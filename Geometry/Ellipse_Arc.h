
#ifndef _GEOMETRY_ELLIPSE_ARC_H_
#define _GEOMETRY_ELLIPSE_ARC_H_

#include <vector>
#include "export.h"
#include "Point.h"
#include "Normal.h"
#include "counter.h"

namespace geo{
  
class LLine;
class RLine;
class SLine;
class Circle;
class Arc;
class Ellipse;

class GEOAPI Ellipse_Arc
{
public:
  Point center;
  Point axis1;
  Point axis2;
  Float start_param;
  Float end_param;
public:
	Ellipse_Arc();
public:
  void intersect2d(const LLine      & rhs, std::vector<Point>& pts) const;
  void intersect2d(const RLine      & rhs, std::vector<Point>& pts) const;
  void intersect2d(const SLine      & rhs, std::vector<Point>& pts) const;
  void intersect2d(const Circle     & rhs, std::vector<Point>& pts) const;
  void intersect2d(const Arc        & rhs, std::vector<Point>& pts) const;
  void intersect2d(const Ellipse    & rhs, std::vector<Point>& pts) const;
  void intersect2d(const Ellipse_Arc& rhs, std::vector<Point>& pts) const;
private:
	MCT_DEF
};


}

#endif
