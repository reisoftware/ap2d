#ifndef _GEOMETRY_BOX_H_
#define _GEOMETRY_BOX_H_

#include "export.h"
#include "Point.h"
#include <string>

namespace geo{

class GEOAPI Box
{
public:
	std::string name_;
  Point max_;
  Point min_;

public:
  Box();
  ~Box();
};

struct Rect_Box{
	std::string name_;
  Point max_;
  Point min_;
};
}//namespace

#endif//FILE
