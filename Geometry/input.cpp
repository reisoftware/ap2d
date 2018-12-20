#include "calculate.h"
#include "Point.h"
#include "Plane.h"
#include "LLine.h"
#include "SLine.h"
#include "RLine.h"

namespace geo{



void input(Point &pt)
{
	std::cin >> pt.x >> pt.y >> pt.z;
}

void input(LLine &ln)
{
	input(ln.pt1);
	input(ln.pt2);
}

void input(RLine &rl)
{
	input(rl.pt1);
	input(rl.pt2);
}

void input(SLine &sl)
{
	input(sl.pt1);
	input(sl.pt2);
}

void input(Plane &pla)
{
	std::cin >> pla.a >> pla.b >> pla.c >> pla.d;
}

}//namespace