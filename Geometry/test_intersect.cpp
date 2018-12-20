#include "test_intersect.h"
#include <iostream>

#include "Point.h"
#include "LLine.h"
#include "RLine.h"
#include "SLine.h"
#include "Arc.h"
#include "Circle.h"

#include "check.h"
#include "getrace.h"
#include "test_global.h"
#include "read.h"

extern std::string fun_name;

void	test_case(Points &pts_input,Points &crosses,Points &pts)
{
	std::string type1,type2;
	std::cin >> type1;
	geo::LLine ll1,ll2;
	geo::RLine rl1,rl2;
	geo::SLine sl1,sl2;
	geo::Arc arc1,arc2;
	geo::Circle cir1,cir2;
	GETRACE;
	TRACE_OUT("kind is : %s",type1.c_str());
	if(type1 == ll_kind)
		read_lline(ll1);
	else if(type1 == rl_kind)
		read_rline(rl1);
	else if(type1 == sl_kind)
		read_sline(sl1);
	else if(type1 == arc_kind)
		read_arc(arc1);
	else if(type1 == circle_kind)
		read_circle(cir1);
	std::cin >> type2;
	if(type2 == ll_kind)
		read_lline(ll2);
	else if(type2 == rl_kind)
		read_rline(rl2);
	else if(type2 == sl_kind)
		read_sline(sl2);
	else if(type2 == arc_kind)
		read_arc(arc2);
	else if(type2 == circle_kind)
		read_circle(cir2);

	std::string type_cross;
	std::cin >> type_cross;
	geo::Point pt;
	while(type_cross == "cross:"){
		read_pt(pt);
		crosses.push_back(pt);
		std::cin >> type_cross;
	}

	if(type1 == ll_kind && type2 == ll_kind){
		ll1.intersect2d(ll2,pts);
		check_lines(ll1,ll2,pts,crosses);
	}
	else if(type1 == ll_kind && type2 == rl_kind){
		rl2.intersect2d(ll1,pts);
		check_lines(ll1,rl2,pts,crosses);
	}	
	else if(type1 == ll_kind && type2 == sl_kind){
		sl2.intersect2d(ll1,pts);
		check_lines(ll1,sl2,pts,crosses);
	}	
	else if(type1 == ll_kind && type2 == arc_kind){
		arc2.intersect2d(ll1,pts);
//		check_arc_ll(arc2,ll1,pts,crosses);
		check_arc_l(arc2,ll1,pts,crosses);
	}
	else if(type1 == ll_kind && type2 == circle_kind){
		cir2.intersect2d(ll1,pts);
		check_circle_l(cir2,ll1,pts,crosses);
	}
	else if(type1 == rl_kind && type2 == ll_kind){
		rl1.intersect2d(ll2,pts);
		check_lines(rl1,ll2,pts,crosses);
	}	
	else if(type1 == rl_kind && type2 == rl_kind){
		rl2.intersect2d(rl1,pts);
		check_lines(rl1,rl2,pts,crosses);
	}
	else if(type1 == rl_kind && type2 == sl_kind){
		sl2.intersect2d(rl1,pts);
		check_lines(rl1,sl2,pts,crosses);
	}	
	else if(type1 == rl_kind && type2 == arc_kind){
		arc2.intersect2d(rl1,pts);
		check_arc_l(arc2,rl1,pts,crosses);
	}
	else if(type1 == rl_kind && type2 == circle_kind){
		cir2.intersect2d(rl1,pts);
		check_circle_l(cir2,rl1,pts,crosses);
	}
	else if(type1 == sl_kind && type2 == ll_kind){
		sl1.intersect2d(ll2,pts);
		check_lines(sl1,ll2,pts,crosses);
	}	
	else if(type1 == sl_kind && type2 == rl_kind){
		sl1.intersect2d(rl2,pts);
		check_lines(sl1,rl2,pts,crosses);
	}	
	else if(type1 == sl_kind && type2 == sl_kind){
		sl2.intersect2d(sl1,pts);
		check_lines(sl1,sl2,pts,crosses);
	}	
	else if(type1 == sl_kind && type2 == arc_kind){
		arc2.intersect2d(sl1,pts);
		check_arc_l(arc2,sl1,pts,crosses);
	}
	else if(type1 == sl_kind && type2 == circle_kind){
		cir2.intersect2d(sl1,pts);
		check_circle_l(cir2,sl1,pts,crosses);
	}
	else if(type1 == arc_kind && type2 == ll_kind){
		arc1.intersect2d(ll2,pts);
		check_arc_l(arc1,ll2,pts,crosses);
	}
	else if(type1 == arc_kind && type2 == rl_kind){
		arc1.intersect2d(rl2,pts);
		check_arc_l(arc1,rl2,pts,crosses);
	}
	else if(type1 == arc_kind && type2 == sl_kind){
		arc1.intersect2d(sl2,pts);
		check_arc_l(arc1,sl2,pts,crosses);
	}
	else if(type1 == arc_kind && type2 == arc_kind){
		arc1.intersect2d(arc2,pts);
		check_arc_arc(arc1,arc2,pts,crosses);
	}
	else if(type1 ==arc_kind && type2 == circle_kind){
		arc1.intersect2d(cir2,pts);
		check_arc_circle(arc1,cir2,pts,crosses);
	}
	else if(type1 == circle_kind && type2 == ll_kind){
		cir1.intersect2d(ll2,pts);
		check_circle_l(cir1,ll2,pts,crosses);
	}
	else if(type1 == circle_kind && type2 == rl_kind){
		cir1.intersect2d(rl2,pts);
		check_circle_l(cir1,rl2,pts,crosses);
	}
	else if(type1 == circle_kind && type2 == sl_kind){
		cir1.intersect2d(sl2,pts);
		check_circle_l(cir1,sl2,pts,crosses);
	}
	else if(type1 == circle_kind && type2 == arc_kind){
		arc2.intersect2d(cir1,pts);
		check_arc_circle(arc2,cir1,pts,crosses);
	}
	else if(type1 == circle_kind && type2 ==circle_kind){
		cir1.intersect2d(cir2,pts);
		check_circle_circle(cir1,cir2,pts,crosses);
	}
}
void test_intersect()
{
	print_fun_info(fun_name);
	std::string type;
	std::cin >> type;
	int index=1;
	Points pts_cal,pts_input,crosses;
	geo::Point cross;
	while(type == "%case"){
		pts_cal.clear();
		pts_input.clear();
		crosses.clear();
		std::cin >> index;
		std::cout <<"\n";
		std::cout <<"case"<<index<<":\n";
		test_case(pts_input,crosses,pts_cal);
		std::cin >> type;
		index++;
	}
}