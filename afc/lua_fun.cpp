#include "stdafx.h"
#include "str.h"
#include "lua_fun.h"
#include "Lua_Tab.h"
#include "lua_tools.h"
// #include "Line_Arrow.h"
#include <iomanip>


namespace lua{


static bool number_save(std::ofstream &out, const char *name, double val, int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if (NULL != name)
		out << name << " = ";
	if (val)
    out << std::setprecision(15) << val << ",\n";
	else
		out << "0" << ",\n";
	return true;
}

static bool str_save(std::ofstream &out,const char *name,const char *val,int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if (name)
		out << name << " = ";
	if (val)
		out << "[[" << val << "]],\n";
	else
		out << "[[" << "null" << "]],\n";
	return true;
}

void val_save(std::ofstream &out,const char *val,int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if (val)
		out << val << "\n";
	else
		out << "null" << "\n";
}
void begin_table(std::ofstream &out,const char *name,int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if(name)
		out << name << " = { "<<"\n";
	else
		out << "{" <<"\n";

}

		/*
static bool number_save(std::ofstream &out, const char *name, double val, int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if (NULL != name)
		out << name << " = ";
	if (val)
    out << std::setprecision(15) << val << ",";
	else
		out << "0" << ",";
	return true;
}

static bool str_save(std::ofstream &out,const char *name,const char *val,int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if (name)
		out << name << " = ";
	if (val)
		out << "[[" << val << "]],\n";
	else
		out << "[[" << "null" << "]],\n";
	return true;
}

void val_save(std::ofstream &out,const char *val,int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if (val)
		out << val << " ";
	else
		out << "null" << " ";
}
void begin_table(std::ofstream &out,const char *name,int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if(name)
		out << name << " = { "<<" ";
	else
		out << "{" <<" ";

}
*/



void end_table(std::ofstream &out,int tab_num)
{
	val_save(out,"},",tab_num);
}

bool int_save(std::ofstream &out,const char *name,int val,int tab_num)
{
	return number_save(out, name, val, tab_num);
}
bool double_save(std::ofstream &out,const char *name,double val,int tab_num) 
{
	return number_save(out, name, val, tab_num);
}
bool float_save(std::ofstream &out,const char *name,float val,int tab_num) 
{
	return number_save(out, name, val, tab_num);
}
bool bool_save(std::ofstream &out,const char *name,bool val,int tab_num)
{
	return number_save(out, name, val, tab_num);
}

bool string_save(std::ofstream &out,const char *name,std::string val,int tab_num) 
{
	return str_save(out, name, val.c_str(), tab_num);
}
bool string_all_save(std::ofstream &out,const char *name,std::string val,int tab_num) 
{
	char *v = const_cast<char*>(val.c_str());
	return lpstr_zkh_save(out, name,v , tab_num);
}
bool lpstr_save(std::ofstream &out,const char *name,LPTSTR val,int tab_num) 
{	
	return str_save(out, name, val, tab_num);
}
bool lpstr_zkh_save(std::ofstream &out,const char *name,LPTSTR val,int tab_num) 
{	
	while (0 < tab_num--)
		out << "\t";
	if (name)
		out << name << " = ";
	if (val)
		out << "[=[" << val << "]=],\n";
	else
		out << "[=[" << "null" << "]=],\n";
	return true;
}
bool byte_save(std::ofstream &out, const char *name, BYTE val, int tab_num)
{
	return number_save(out, name, val, tab_num);
}


bool save(std::ofstream &out,const char *name,int val,int tab_num)
{
	return int_save(out,name,val,tab_num);
}

bool save(std::ofstream &out,const char *name,const std::vector<std::string>& val,int tab_num)
{
	begin_table(out,name,tab_num);
	std::vector<std::string>::const_iterator it = NULL;
	for(it=val.begin();it!=val.end();++it){
		string_save(out,NULL,*it,tab_num);
	}
	end_table(out,tab_num);
	return true;
}


bool open(lua_State * l, const char *name, std::vector<std::string>& val)
{
	Lua_Tab lt(l, name);
	int index = lua_gettop(l);
	lua_pushnil(l);
	val.clear();
	while(lua_next(l, index) != 0){
		std::string t;
	//	t.open_lua(l, NULL);
		get_value_index(string, l, t, index);
		val.push_back(t);
		lua_pop(l, 1);
	}
	return true;
}

//生成实体
// void create_line_arrow(lua_State *l)
// {
// 	dlhml::Line_Arrow *v =  dlhml::Line_Arrow::create_me();
// 	v->open_lua(l,"");
// //v->post2db()
// 
// }

}//namespace
