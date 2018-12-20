#include "test_hiddening.h"
#include <string>
#include <iostream>
#include "print.h"


extern std::string fun_name;
void test_case()
{
/*
	std::string type;
	std::cin >> type;
	hidden::Polygons_Groups groups;
	hidden::Projection projection;
//	read.get_polygons(groups);
	for(int i=0;i<groups.size();i++){
		hiddening(groups[i],projection);
		draw_polygons(groups[i],i);
	}
*/
	

}

void test_hiddening()
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
		index++;
	}
}