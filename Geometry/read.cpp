#include "read.h"
#include "Point.h"
#include <iostream>
#include <string>
#include "Line.h"
#include "Arc.h"
#include "Circle.h"
#include "LLine.h"
#include "RLine.h"
#include "SLine.h"


void read_pt(geo::Point & pt)
{
	double x=0,y=0,z=0;
	std::cin >> x >> y >> z;
	pt.set(x,y,z);
}

void read_point(geo::Point &pt)
{
	double x=0,y=0,z=0;
	std::string type;
	std::cin >> type;
	std::cin >> x >> y >> z;
	pt.set(x,y,z);
}
template <class T>
void read_line(T &t)
{
	geo::Point start,end;
	read_point(start);
	read_point(end);
	t.set(start,end);
}
void read_lline(geo::LLine &lline)
{
	geo::Point start,end;
	read_point(start);
	read_point(end);
	lline.set(start,end);
}
void read_sline(geo::SLine &sline)
{
	geo::Point start,end;
	read_point(start);
	read_point(end);
	sline.set(start,end);
}
void read_rline(geo::RLine &rline)
{
	geo::Point start,end;
	read_point(start);
	read_point(end);
	rline.set(start,end);
}
void read_arc(geo::Arc &arc)
{
	geo::Point start,path,end;
	read_point(start);
	read_point(path);
	read_point(end);
	arc.start = start;
	arc.end = end;
	arc.path = path;

}
void read_circle(geo::Circle &circle)
{
	geo::Point center,normal;
	geo::Normal nor;
	double radius=0;
	read_point(center);
	std::string type;
	std::cin >> type;
	std::cin >> radius;
	read_point(normal);
	nor.set(normal);
	circle.center = center;
	circle.radius = radius;
	circle.nor = nor;
}
