
#ifndef _GEOMETRY_PLANE_H_
#define _GEOMETRY_PLANE_H_


#include "export.h"
#include "counter.h"

namespace geo{

class GEOAPI Plane
{
public:
  //Plan();
  Plane(double a=0, double b=0, double c=0, double d=0);
public:
  void set(double a=0, double b=0, double c=0, double d=0);

public:
  double a, b, c, d;
private:
	MCT_DEF
};

}//namespace

#endif//FILE

