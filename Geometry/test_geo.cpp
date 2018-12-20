#include <iostream>

#include "calculate.h"
//#include "Point.h"
#include "Arc.h"
#include "Circle.h"
#include "box.h"
using namespace std;
using namespace geo;
void print_point(const Point &pt)
{
	std::cout << "(" << pt.x << " ," << pt.y << " ," << pt.z << ")" << std::endl;
}
void print_arc(const Arc &arc)
{
	std::cout << "start point: ";
	print_point(arc.start);
	std::cout << "path point: ";
	print_point(arc.path);
	std::cout << "end point: ";
	print_point(arc.end);
}
int main(int argc, char * argv [])
{
  Arc arc;
	arc.start.set(0.5,1,0);
	arc.path.set(1,1,0.5);
	arc.end.set(0.5,1,1);
	Box box = get_arc_box(arc);
	print_point(box.max_);
	print_point(box.min_);
  return 0;
}