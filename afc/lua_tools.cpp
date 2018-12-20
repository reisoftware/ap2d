#include "stdafx.h"
#include "lua_tools.h"
#include <iomanip>

namespace afc{
namespace lua{

static afc::string get_left(int n)
{
	afc::string str = "[";
	int i =0;
	for(; i<n; ++i){
		str += "=";
	}
	str += "[";
	return str;
}

static afc::string get_sign(int n)
{
	afc::string str = "]";
	int i =0;
	for(; i<n; ++i){
		str += "=";
	}
	return str;
}

static afc::string get_right(int n)
{
	afc::string str = get_sign(n);;
	str += "]";
	return str;
}

static void save_value(std::ofstream& ofs, cchar * value)
{
	int i = 0;
	afc::string left, sign, right;
	do{
		sign = get_sign(i);
		++i;
	}while(strstr(value, sign.c_str()));
	--i;
	left = get_left(i);
	right = get_right(i);

	ofs<<left.c_str()<<value<<right.c_str()<<",\n";
}

//////////////////////////////////////////////////////////////////////////
void save(std::ofstream& ofs, cchar * key, int value)
{
	lua::save_tab(ofs);
	lua::save_key(ofs, key);
	ofs<<value<<",\n";
}

void save(std::ofstream& ofs, cchar * key, double value)
{
	lua::save_tab(ofs);
	lua::save_key(ofs, key);
	ofs<<std::setprecision(15)<<value<<",\n";
}

void save(std::ofstream& ofs, cchar * key, cchar * value)
{
	lua::save_tab(ofs);
	lua::save_key(ofs, key);
	save_value(ofs, value);
}

void save(std::ofstream& ofs, cchar * key, const string& value)
{
	save(ofs, key, value.c_str());
}


void open(lua_State * l, cchar * key, int& value)
{
	get_value(number, l, value, key);
}

void open(lua_State * l, cchar * key, double& value)
{
	get_value(number, l, value, key);
}

void open(lua_State * l, cchar * key, string& value)
{
	get_value(string, l, value, key);
}

void open(lua_State * l, cchar * key, char * value)
{
	afc::string str;
	get_value(string, l, str, key);
	strcpy(value, str.c_str());
}


}//lua
}//afc