#ifndef _OBJECT_GEO_OBJ_H_
#define _OBJECT_GEO_OBJ_H_


#include "Point.h"
#include "Line.h"
#include "RArc.h"
#include "Circle.h"

#include "../geometry/Point.h"
#include "../geometry/LLine.h"
#include "../geometry/RLine.h"
#include "../geometry/SLine.h"
#include "../geometry/Arc.h"
#include "../geometry/Circle.h"
#include "export.h"

namespace geometry{
	class Point;
	class LLine;
	class RLine;
	class SLine;
	class Arc;
	class Circle;
}

namespace dlhml{

	class Point;
	class Line;
	class RArc;
	class Circle;
	
	typedef dlhml::Point  OPoint;
	typedef dlhml::Line	  OLine;
	typedef dlhml::RArc   OArc;
	typedef dlhml::Circle OCircle;

	typedef geo::Point  GPoint;
	typedef geo::LLine  GLLine;
	typedef geo::RLine  GRLine;
	typedef geo::SLine  GSLine;
	typedef geo::Arc    GArc;
	typedef geo::Circle GCircle;

OBJECT_API	GPoint convert(const OPoint& pt);
OBJECT_API	OPoint convert(const GPoint& pt);

// OBJECT_API	GArc convert(const OArc& arc);
// OBJECT_API	OArc convert(const GArc& arc);

OBJECT_API	GCircle convert(const OCircle& cir);
OBJECT_API	OCircle convert(const GCircle& cir);
	
OBJECT_API	void convert(const OLine & oln, GLLine& gln);
OBJECT_API	void convert(const GLLine& gln, OLine &  oln);
	
OBJECT_API	void convert(const OLine & oln, GRLine& gln);
OBJECT_API	void convert(const GRLine& gln, OLine &  oln);
	
OBJECT_API	void convert(const OLine & oln, GSLine& gln);
OBJECT_API	void convert(const GSLine& gln, OLine &  oln);

}//namespace

#endif//FILE
