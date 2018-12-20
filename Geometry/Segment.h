
#ifndef _GEOMETRY_SEGMENT_H_
#define _GEOMETRY_SEGMENT_H_

#include <vector>
#include "Geometry_Ext.h"
//#include "Point.h"

namespace geo{

class Point;

class GEOAPI Segment
{
public:
  void intersect(const Segment& seg, std::vector<Point>& pts);
};


}

#endif

