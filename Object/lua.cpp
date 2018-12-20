#include "stdafx.h"
#include "lua.h"
#include "Line_Arrow.h"

namespace lua{
/*
static bool number_save(std::ofstream &out, const char *name, double val, int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if (NULL != name)
		out << name << " = ";
	if (val)
		out << val << ",\n";
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
void begin_table(std::ofstream &out,char *name,int tab_num)
{
	while (0 < tab_num--)
		out << "\t";
	if(name)
		out << name << " = { "<<"\n";
	else
		out << "{" <<"\n";

}
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
bool lpstr_save(std::ofstream &out,const char *name,LPTSTR val,int tab_num) 
{	
	return str_save(out, name, val, tab_num);
}
bool byte_save(std::ofstream &out, const char *name, BYTE val, int tab_num)
{
	return number_save(out, name, val, tab_num);
}

//生成实体
void create_line_arrow(lua_State *l)
{
	dlhml::Line_Arrow *v =  dlhml::Line_Arrow::create_me();
	v->open_lua(l,"");
//v->post2db()

}
*/
}
