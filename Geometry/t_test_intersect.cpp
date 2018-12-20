
#pragma warning (disable : 4273)

#include "StdAfx.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "intersect.h"
#include "calculate.h"
#include "relating.h"

#include "Point.h"
#include "Plane.h"
#include "LLine.h"
#include "SLine.h"
#include "RLine.h"
#include "Circle.h"
#include "Arc.h"

using namespace geo;


int main(int argc, char * argv[])
{
	LLine ln1,ln2;
	ln1.pt1.set(6440.1,-1219.97,0);
	ln1.pt2.set(6387.55,-1585.15,0);
	ln2.pt1.set(6779.87,-1232.26,0);
	ln2.pt2.set(6420.13,-1232.26,0);
	Point pt;
	double dis = distance(ln1,ln2,20,pt);
	std::cout << dis << std::endl;
	return 0;
}

