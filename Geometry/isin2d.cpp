#include "StdAfx.h"
#include "isin2d.h"
#include "calculate.h"
#include <vector>
#include "Point.h"
#include "LLine.h"
#include "RLine.h"
#include "SLine.h"
#include "getrace.h"

namespace geo{


bool isin2d(const Point& pt, const LLine& ln)
{
	Float dis = distance(project(pt),project(ln)); 
	return equ(dis,0);
}

bool isin2d(const Point& pt, const RLine& rl)
{
	return relation(project(pt),project(rl));
}

bool isin2d(const Point& pt, const SLine& sl)
{
	TRACE_OUT("isin2d :start!\n"); 
	TRACE_OUT("x = %f ; y = %f ;z = %f !\n",pt.x,pt.y,pt.z); 
	TRACE_OUT("sl'st:\n"); 
	TRACE_OUT("start : x = %f ; y = %f ;z = %f !\n",sl.pt1.x,sl.pt1.y,sl.pt1.z); 
	TRACE_OUT("end: x = %f ; y = %f ;z = %f !\n",sl.pt2.x,sl.pt2.y,sl.pt2.z); 
	bool v =  relation(project(pt),project(sl));
	TRACE_OUT("isin2d :ok!\n"); 
	return v;
}


}//namespace
