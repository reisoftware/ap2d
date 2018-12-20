
#include "StdAfx.h"

#include "Plane.h"

namespace geo{

Plane::Plane(double a, double b, double c, double d)
MCT_INIT1("geo:Plane")
{
  set(a,b,c,d);
}
void Plane::set(double a, double b, double c, double d)
{
  this->a = a;
  this->b = b;
  this->c = c;
  this->d = d;
}

}//namespace
