#include "print.h"

#include "Point.h"
#include <iostream>
#include "Line.h"
#include "Arc.h"
#include "Circle.h"
#include "LLine.h"
#include "RLine.h"
#include "SLine.h"
#include "Normal.h"

void print_space()
{
	std::cout << "-------------------------\n";
}
void print_point(const geo::Point &pt)
{
	std::cout <<"pt:  "<<pt.x <<" " << pt.y << " " << pt.z <<"\n" ;
}
void print_nor(const geo::Normal &nor)
{
	std::cout <<"nor:  "<<nor.x <<" " << nor.y << " " << nor.z <<"\n" ;
}
void print_points(const std::vector<geo::Point> &pts)
{
	for(int i=0;i<pts.size();i++)
		print_point(pts[i]);
}
void print_head()
{
	print_space();
	std::cout << "test data:\n";
	
}
void print_lline(const geo::LLine &lline)
{
	std::cout <<"LLine:\n" ;
	print_point(lline.pt1);
	print_point(lline.pt2);	
}
void print_sline(const geo::SLine &sline)
{
	std::cout <<"SLine:\n" ;
	print_point(sline.pt1);
	print_point(sline.pt2);	
}
void print_rline(const geo::RLine &rline)
{
	std::cout <<"RLine:\n" ;
	print_point(rline.pt1);
	print_point(rline.pt2);	
}
void print_arc(const geo::Arc &arc)
{
	std::cout <<"Arc:\n" ;
	print_point(arc.start);
	print_point(arc.path);	
	print_point(arc.end);	
}
void print_circle(const geo::Circle &circle)
{
	std::cout <<"Circle:\n" ;
	print_point(circle.center);
	std::cout << "r:  "<<circle.radius << "\n";
	print_nor(circle.nor);
}
void print_fun_info(std::string name)
{
	std::cout <<"************"<< name.c_str() <<"**************"<< std::endl;
}

void print_test_start()
{
	std::cout << "test funtion start\n";
}
bool print_test_end(std::string name)
{
	if(strcmp(name.c_str(),"END") == 0){
		std::cout <<"test funtion end\n";
		return false;
	}
	return true;
}
