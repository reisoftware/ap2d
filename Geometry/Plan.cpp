
#include "StdAfx.h"

#include "Plan.h"

namespace geo{

Plan::Plan(double a, double b, double c, double d)
{
  set(a,b,c,d);
}
void Plan::set(double a, double b, double c, double d)
{
  this->a = a;
  this->b = b;
  this->c = c;
  this->d = d;
}

}//namespace
