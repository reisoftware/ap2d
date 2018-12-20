#ifndef _DRAG_POLYGON_H_
#define _DRAG_POLYGON_H_
#include "segment.h"
#include "polygon.h"
#include "GeNorm.h"

class Drag_Polygon:public Visitor_Segment{
	
	vector<apcad::Polygon> polygons_;
	double len_;
	CGeNorm norm_;
	
	public:
		Drag_Polygon(double len,CGeNorm norm);
		vector<apcad::Polygon> get_polygons() const;
		
		int do_it(Line& line);
		int do_it(CArc& arc);
};
#endif