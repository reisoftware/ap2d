#include <iostream>
#include <string>
#include "getrace.h"
#include "print.h"

#include "test_intersect.h"
#include "test_hiddening.h"
#include "test_pt_in_polygon.h"

std::string fun_name;

//*ptinrect*//////////////////////////////////////////////////
/*
void get_pt(geo::Point &pt)
{
	double x=0,y=0,z=0;
	std::cin >> x >> y >> z;
	pt.set(x,y,z);
}

void read_case(Points &pts,geo::Point &in,std::string &real_pos)
{
	std::string type;
	std::cin >> type;
	geo::Point pt;
	while(type == "pt:"){
		get_pt(pt);
		pts.push_back(pt);
		std::cin >>type;
	}
	if(type == "in:"){
		get_pt(in);
	}
	std::cin >> type;
	std::cin >> real_pos;
}
void test_case(Points &pts,geo::Point &in,std::string &cal_pos)
{
	if(geo::isin(in,pts))
		cal_pos = "in";
	cal_pos = "out";
}

void test_ptinrect()
{
	std::string type;
	std::cin >> type;
	Points pts;
	geo::Point in;
	std::string real_pos,cal_pos;
	while(type == "%case"){
		pts.clear();
		read_case(pts,in,real_pos);
		test_case(pts,in,cal_pos);
		std::cin >> type;
	}
}
/*/
/*ptinrect*//////////////////////////////////////////////////
int main(int argv,char *argc[])
{
	TRACE_INIT;
	print_test_start();
	while(true){
		if(!print_test_end(fun_name))
			return 0;
		std::cin >> fun_name;
		if(strcmp(fun_name.c_str(),"intersect") == 0)
			test_intersect();
		else if(strcmp(fun_name.c_str(),"hiddening")==0)
			test_hiddening();
		else if(strcmp(fun_name.c_str(),"pt_in_polygon")==0)
			test_pt_in_polygon();
		if(!print_test_end(fun_name))
			return 0;
		std::cin >> fun_name;
	}
	TRACE_CLOSE;
	return 0;

}
