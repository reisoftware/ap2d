#include "test_pt_in_polygon.h"
#include "test_global.h"
#include "read.h"
#include "global.h"
#include "check.h"

extern std::string fun_name;

void test_case()
{
	std::string type;
	std::cin >> type;
	Points polygon;
	geo::Point pt;
	geo::Point input_pt;
	std::cin >> type;
	while(strcmp(type.c_str(),"pt:") == 0){
		read_pt(pt);
		polygon.push_back(pt);
		std::cin >> type;
	}
	read_pt(input_pt);
	std::cin >> type;
	bool input_in = false;
	std::cin >> input_in;


	bool cal_in = geo::isin(input_pt,polygon);
	check_pt_in_polygon(polygon,input_pt,input_in,cal_in);
	std::cin >> type;//¶à¶Á¸öcase_end
}
void test_pt_in_polygon()
{
	print_fun_info(fun_name);
	std::string type;
	std::cin >> type;
	int index=1;
	while(type == "%case"){
		std::cin >> index;
		std::cout <<"\n";
		std::cout <<"case"<<index<<":\n";
		test_case();
		std::cin >> type;
	}
}