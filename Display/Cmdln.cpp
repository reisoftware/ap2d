#include "StdAfx.h"
#include "Cmdln.h"
#include "../object/Point.h"
#include "../object/export.h"
#include "../object/Normal.h"


namespace dlhml{
//input: x,y(绝对坐标)
bool absolute_coordinates(Point base, std::string input, int pos, Point & target)
{
	int str_len = input.length();
	std::string front, back;
	front = input.substr(0, pos);
	back = input.substr(pos + 1, str_len - pos);
	if(front.empty() || back.empty()){
		return false;
	}
	target.x = base.x + atof(front.c_str());
	target.y = base.y + atof(back.c_str());
	return true;
}
//input: d(距离)
bool distance(Point base, std::string input, Point normal, Point & target)
{
	int str_len = input.length();
	int pos = input.find("@");
	std::string str;
	if (input.find("@") == 0){
		str = input.substr(1, str_len - 1);
	}else{
		str = input;
	}
//	int str = input.substr();
	Float d = atof(str.c_str());
	Normal nor(normal);	
	target = base.polarTo(d, nor);
	return true;
}
//input: @x,y(相对坐标)
bool relative_coordinates(Point base, std::string input, int pos, Point & target)
{
	int str_len = input.length();
	std::string front, back;
	front = input.substr(1, pos - 1);
	back = input.substr(pos +1, str_len - pos -1);
	if(front.empty() || back.empty()){
		return false;
	}
	target.x = base.x + atof(front.c_str());
	target.y = base.y + atof(back.c_str());
	return true;
}
//input: @d<α(极坐标：距离和角度)
bool polar_coordinates(Point base, std::string input, int pos, Point & target)
{
	int str_len = input.length();
	std::string front, back;
	if(input.find("@") == 0){
		front = input.substr(1, pos - 1);
	}else{
		front = input.substr(0,pos);
	}

//	front = input.substr(1, pos - 1);
	back = input.substr(pos +1, str_len - pos -1);
	if(front.empty() || back.empty()){
		return false;
	}
	Float d = atof(front.c_str());
	Float angle = atof(back.c_str());
	Normal nor;
	degree_2_normal2d(angle, nor);
	target = base.polarTo(d, nor);
	return true;
}
//input: @d<x,y(距离和方向)
bool distance_normal(Point base, std::string input, int pos, Point & target)
{
	int str_len = input.length();
	std::string front, back;
	if (input.find("@") == 0){
		front = input.substr(1, pos - 1);
	}else{
		front = input.substr(0,pos);
	}
	back = input.substr(pos +1, str_len - pos -1);
	int poss = back.find(",");
	Float d = atof(front.c_str());
	std::string sx = back.substr(0, poss);
	std::string sy = back.substr(poss + 1, back.length() - poss);
	if(front.empty() || sx.empty() || sy.empty()){
		return false;
	}	
	Float px = atof(sx.c_str());
	Float py = atof(sy.c_str());
	Normal nor(px, py, 0);
	target = base.polarTo(d, nor);
	return true;
}
bool chk_absolute_coordinates(std::string str)
{
	for(int i = 0; i < str.length(); i++){
		if((str[i] <= '9' && str[i] >= '0') || str[i] == ',' || str[i] == '-' ||
				str[i] == '.'){
			continue;	
		}else{
			return false;
		}
	}
	return true;
}
bool chk_distance(std::string str)
{
	for(int i = 0; i < str.length(); i++){
		if((str[i] <= '9' && str[i] >= '0') || str[i] == '-' || str[i] == '.' ||
			  str[i] == '@'){
			continue;	
		}else{
			return false;
		}
	}
	return true;
}
bool chk_relative_coordinates(std::string str)
{
	for(int i = 0; i < str.length(); i++){
		if((str[i] <= '9' && str[i] >= '0') || str[i] == ',' || str[i] == '-' ||
				str[i] == '.' || str[i] == '@'){
			continue;	
		}else{
			return false;
		}
	}
	return true;
}
bool chk_polar_coordinates(std::string str)
{
	for(int i = 0; i < str.length(); i++){
		if((str[i] <= '9' && str[i] >= '0') || str[i] == '<' || str[i] == '-' ||
				str[i] == '.' || str[i] == '@'){
			continue;	
		}else{
			return false;
		}
	}
	return true;
}
bool chk_distance_normal(std::string str)
{
	for(int i = 0; i < str.length(); i++){
		if((str[i] <= '9' && str[i] >= '0') || str[i] == '<' || str[i] == ',' ||
				str[i] == '-' || str[i] == '.' || str[i] == '@'){
			continue;	
		}else{
			return false;
		}
	}
	return true;
}
bool cmdln(const Point& base, const Point& normal, std::string input, Point & target)
{
	std::string front, back;
	int str_len = input.length();
	int pos1 = input.find(",");
	int pos2 = input.find("@");
	int pos3 = input.find("<");	

	if(pos1 != -1 && pos1 != 0 && pos2 == -1 && pos3 == -1){
		//input: x,y
		if(!chk_absolute_coordinates(input)){
			return false;
		}
		return absolute_coordinates(base, input, pos1, target);
	}else	if(pos1 == -1 && pos3 == -1){
		//input: d	
		if(!chk_distance(input)){
			return false;
		}
		return distance(base, input, normal, target);
	}else	if(pos1 != -1 && pos2 == 0 && pos3 == -1){
		//input: @x,y
		if(!chk_relative_coordinates(input)){
			return false;
		}
		return relative_coordinates(base, input, pos1, target);
	}else	if(pos1 == -1 && pos3 != -1){
		//input: @d<α
		if(!chk_polar_coordinates(input)){
			return false;
		}
		return polar_coordinates(base, input, pos3, target);
	}else	if(pos1 != -1 && pos3 != -1){
		//input: @d<x,y
		if(!chk_distance_normal(input)){
			return false;
		}
		return distance_normal(base, input, pos3, target);
	}else{
		return false;
	}
}


}//namespace



