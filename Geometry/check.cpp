#include "check.h"
#include "LLine.h"
#include "Arc.h"
#include "Point.h"
#include <iostream>
#include <algorithm>


void check_result(const Points &pts,const Points &crosses)
{
	print_space();
	std::cout << "input corss:\n";
	if(crosses.size() == 0)
		std::cout<<  "no corss\n";
	else
		print_points(crosses);
	print_space();
	std::cout << "calculate corss:\n";
	print_points(pts);
	print_space();
	std::cout << "test result:\n";
	if(pts.size()==0 && crosses.size()==0)
		std::cout<<  "OK\n";
	else if(equ_crosses(pts,crosses))
		std::cout<<  "OK\n";
	else
		std::cout <<"ERROR\n";
}
bool equ_crosses(const Points &pts,const Points &crosses)
{
	if(pts.size() != crosses.size())
		return false;
	int count=0;
	for(int i=0;i<pts.size();i++){
		Points::const_iterator iter = std::find(crosses.begin(),crosses.end(),pts[i]);
		if(iter != crosses.end())
			count++;
	}
	if(count == pts.size())
		return true;
	return false;
}
void check_arc_ll(const geo::Arc &arc,const geo::LLine &ll,const Points &pts,const Points &crosses)
{
	print_head();
	print_arc(arc);
	print_line(ll);
	check_result(pts,crosses);
}
void check_arc_circle(const geo::Arc &arc,const geo::Circle &cir,const Points &pts,const Points &crosses)
{
	print_head();
	print_arc(arc);
	print_circle(cir);
	check_result(pts,crosses);
}
void check_arc_arc(const geo::Arc &arc1,const geo::Arc &arc2,const Points &pts,const Points &crosses)
{
	print_head();
	print_arc(arc1);
	print_arc(arc2);
	check_result(pts,crosses);
}
void check_circle_circle(const geo::Circle &cir1,const geo::Circle &cir2,const Points &pts,const Points &crosses)
{
	print_head();
	print_circle(cir1);
	print_circle(cir2);
	check_result(pts,crosses);
}
void check_pt_in_polygon(const Points &polygon,const geo::Point &input_pt,bool input_in,bool cal_in)
{
	print_head();
	std::cout << "Polygon:\n";
	print_points(polygon);
	std::cout << "input ";
	print_point(input_pt);
	print_space();
	std::cout << "input if in:\n";
	std::cout << input_in << "\n";
	print_space();
	std::cout << "cal if in:\n";
	std::cout << cal_in << "\n";
	print_space();
	std::cout << "test result:\n";
	if(input_in == cal_in)
		std::cout << CAL_OK.c_str();
	else
		std::cout << CAL_ERROR.c_str();

}