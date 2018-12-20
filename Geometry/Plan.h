
#ifndef _GEOMETRY_PLAN_H_
#define _GEOMETRY_PLAN_H_


#include "Geometry_Ext.h"

namespace geo{

class GEOAPI Plan
{
public:
  //Plan();
  Plan(double a=0, double b=0, double c=0, double d=0);
public:
  void set(double a=0, double b=0, double c=0, double d=0);

public:
  double a, b, c, d;
};

}//namespace

#endif//FILE

