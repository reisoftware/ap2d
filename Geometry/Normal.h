
#ifndef _GEOMETRY_NORMAL_H_
#define _GEOMETRY_NORMAL_H_

#include "export.h"
#include "Float.h"
#include "counter.h"

namespace geo{

class Point;

class GEOAPI Normal
{
public:
  Float x;
  Float y;
  Float z;

public:
  void normalize();

public:
  bool iszero() const;

public:
  //Normal();
  Normal(Float x=0, Float y=0, Float z=0);
  
public:
  void set(Float x=0, Float y=0, Float z=0);
  void set(const Point& ed);
  void set(const Point& st, const Point& ed);
  
public:
  bool operator == (const Normal& rhs) const;
  bool operator != (const Normal& rhs) const;
  
  Normal operator * (const Normal& rhs) const;
private:
	MCT_DEF
};

const Normal ZUNIT;
  
}

#endif


