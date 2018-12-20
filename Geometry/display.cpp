#include "calculate.h"
#include "Point.h"
#include "Plane.h"
namespace geo{

void display(const Point pt)
{
	std::cout << "(" << pt.x << "," << pt.y << "," << pt.z << ")" << std::endl;
}

void display(const Plane pla)
{
	std::cout << "(" << pla.a << "," << pla.b << "," << pla.c 
		<< "," << pla.d << ")" << std::endl;
}

}//namespace