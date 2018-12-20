#ifndef _CHECK_H_
#define _CHECK_H_
#include <vector>
#include "print.h"

const std::string CAL_OK = "OK\n";
const std::string CAL_ERROR = "ERROR\n";
namespace geo
{
class Point;
class Arc;
class Circle;
class RLine;
class LLine;
class SLine;
}

typedef std::vector<geo::Point> Points;

template <class T1,class T2>
void check_lines(T1 &t1,T2 &t2,const Points &pts,const Points &crosses)
{
	print_space();
	std::cout << "test data:\n";
	print_line<T1>(t1);
	print_line<T2>(t2);
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

bool equ_crosses(const Points &pts,const Points &crosses);
void check_arc_ll(const geo::Arc &arc,const geo::LLine &ll,const Points &pts,const Points &crosses);
void check_result(const Points &pts,const Points &crosses);
void check_arc_circle(const geo::Arc &arc,const geo::Circle &cir,const Points &pts,const Points &crosses);
void check_arc_arc(const geo::Arc &arc1,const geo::Arc &arc2,const Points &pts,const Points &crosses);
void check_circle_circle(const geo::Circle &cir1,const geo::Circle &cir2,const Points &pts,const Points &crosses);


template <class T>
void check_arc_l(const geo::Arc &arc,T &t,const Points &pts,const Points &crosses)
{
	print_head();
	print_arc(arc);
	print_line<T>(t);
	check_result(pts,crosses);
}
template <class T>
void check_circle_l(const geo::Circle &circle,T &t,const Points &pts,const Points &crosses)
{
	print_head();
	print_circle(circle);
	print_line<T>(t);
	check_result(pts,crosses);
}


////////////////////////////////////////////////////////
void check_pt_in_polygon(const Points &polygon,const geo::Point &input_pt,bool input_in,bool cal_in);

#endif