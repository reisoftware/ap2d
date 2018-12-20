
#include "StdAfx.h"
#include "../object/calculate.h"
#include "../object/Line.h"
#include "../object/Circle.h"
#include "../object/RArc.h"

#include "../geometry/calculate.h"
#include "../geometry/intersect.h"

#include "../Geometry/Point.h"
#include "../Geometry/Normal.h"
#include "../Geometry/Plane.h"
#include "../Geometry/LLine.h"
#include "../Geometry/SLine.h"
#include "../Geometry/RLine.h"
#include "../Geometry/Circle.h"
#include "../Geometry/Arc.h"

#include "geo_obj.h"


namespace dlhml{


Float area_min_rect(const std::vector<Point>& pts)
{
  std::vector<geo::Point> ptgs;
  int i;
  for(i = 0;i < pts.size();i++){
    ptgs.push_back(convert(pts[i]));
  }
  return geo::get_min_area(ptgs);
}


}//namespace

