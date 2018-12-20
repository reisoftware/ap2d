#include "StdAfx.h"
#include "tools2d.h"

using namespace geo;
namespace geo{

Float degree_2_radian(Float a)
{
  return a*pi()/circ_half();
}

Float radian_2_degree(Float r)
{
  return r*circ_half()/pi();
}

void std_degree(Float& a)
{
  while(more_equ(a,circ())){
    a-=circ();
  }
  while(less_than(a,0)){
    a+=circ();
  }
}

void std_radian(Float& r)
{
  while(more_equ(r,pi2())){
    r-=(pi2());
  }
  while(less_than(r,0)){
    r+=(pi2());
  }
}
  
  
}//namespace

