
#ifndef _GEOMETRY_CIRCLE_H_
#define _GEOMETRY_CIRCLE_H_

#include <vector>
#include "export.h"
#include "Point.h"
#include "Normal.h"
#include "counter.h"

namespace geo{

class LLine;
class RLine;
class SLine;

class GEOAPI Circle
{
public:
  Point center; 
  Float radius;
  Normal nor;

public:
	Circle(const Point& c=ORG, Float r=0, const Normal& n=ZUNIT);
	void set(const Point& c=ORG, Float r=0, const Normal& n=ZUNIT);

public:
  void intersect2d(const LLine & rhs, std::vector<Point>& pts) const;
  void intersect2d(const RLine & rhs, std::vector<Point>& pts) const;
  void intersect2d(const SLine & rhs, std::vector<Point>& pts) const;
  void intersect2d(const Circle& rhs, std::vector<Point>& pts) const;
private:
	MCT_DEF
};

}
#endif

