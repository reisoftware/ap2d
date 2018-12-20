
#include "StdAfx.h"
#include "Circle.h"
#include "intersect.h"

namespace geo{
  
Circle::Circle(const Point& c, Float r, const Normal& n)
MCT_INIT1("geo:Circle")
{
	set(c, r, nor);
}

void Circle::set(const Point& c, Float r, const Normal& n)
{
	this->center = c;
	this->radius = r;
	this->nor		 = n;
}

void Circle::intersect2d(const LLine& rhs, std::vector<Point>& pts)const
{
	Point pt1, pt2;
	int num = geo::intersect2d(*this, rhs, pt1, pt2);
	
	if(num == 1){
		pts.push_back(pt1);
	}
	else if(num == 2){
		pts.push_back(pt1);
		pts.push_back(pt2);
	}
	else{
	}
}
void Circle::intersect2d(const RLine& rhs, std::vector<Point>& pts)const
{
	Point pt1, pt2;
	int num = geo::intersect2d(*this, rhs, pt1, pt2);
	
	if(num == 1){
		pts.push_back(pt1);
	}
	else if(num == 2){
		pts.push_back(pt1);
		pts.push_back(pt2);
	}
	else{
	}
}
void Circle::intersect2d(const SLine& rhs, std::vector<Point>& pts)const
{
	Point pt1, pt2;
	int num = geo::intersect2d(*this, rhs, pt1, pt2);
	
	if(num == 1){
		pts.push_back(pt1);
	}
	else if(num == 2){
		pts.push_back(pt1);
		pts.push_back(pt2);
	}
	else{
	}
}
void Circle::intersect2d(const Circle& rhs, std::vector<Point>& pts)const
{
  //NOOK
}
  
}//namespace

