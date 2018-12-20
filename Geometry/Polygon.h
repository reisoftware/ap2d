
#ifndef _GEOMETRY_POLYGON_H_
#define _GEOMETRY_POLYGON_H_

#include <list>
#include "Geometry_Ext.h"
//#include "Point.h"
//#include "Segment.h"

namespace geo{


class Point;
class Rect;
class Segment;

class GEOAPI Polygon
{
public:
  enum COVERPOS{POS_NONE, POS_OVER, POS_DOWN, POS_CROSS};
public:
  Rect box2d();
  bool is_in(const Point& pt);
  COVERPOS compare(const Polygon& datum);
 
private:
  std::list<Segment*> segs_;
};

}//namespace
#endif

