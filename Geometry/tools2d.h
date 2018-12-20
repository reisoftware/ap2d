#ifndef _GEOMETRY_TOOLS2D_H_
#define _GEOMETRY_TOOLS2D_H_

#include "export.h"
#include "Float.h"

namespace geo{

GEOAPI Float degree_2_radian(Float a);
GEOAPI Float radian_2_degree(Float r);
GEOAPI void std_degree(Float& a);
GEOAPI void std_radian(Float& r);


}//namespace

#endif//FILE
