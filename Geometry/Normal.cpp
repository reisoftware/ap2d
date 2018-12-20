#include "StdAfx.h"
#include "Normal.h"
#include "Point.h"

#include <math.h>

namespace geo{

Normal::Normal(Float x, Float y, Float z)
MCT_INIT1("geo:Normal")
{
  set(x,y,z);
}
void Normal::set(Float x, Float y, Float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}
void Normal::set(const Point& ed)
{
  x = ed.x;
  y = ed.y;
  z = ed.z;
}
void Normal::set(const Point& st, const Point& ed)
{
  x = ed.x - st.x;
  y = ed.y - st.y;
  z = ed.z - st.z;
}

bool Normal::operator == (const Normal& rhs) const
{
  return equ(x,rhs.x) && equ(y,rhs.y) && equ(z,rhs.z);
}
bool Normal::operator != (const Normal& rhs) const
{
  return !(*this == rhs);
}

Normal Normal::operator * (const Normal& rhs) const
{
  Float xx=0,yy=0,zz=0;
  xx = this->y * rhs.z - rhs.y * this->z;
  yy = this->z * rhs.x - rhs.z * this->x;
  zz = this->x * rhs.y - rhs.x * this->y;
  Normal nor(xx,yy,zz);
  nor.normalize();
  return nor;
}

void Normal::normalize()
{
  if(iszero()){
    return;
  }
  Float len = sqrt( x*x + y*y + z*z);
  x /= len;
  y /= len;
  z /= len;
}

bool Normal::iszero() const
{
  return equ(x,0) && equ(y,0) && equ(z,0);
}


}//namespace
