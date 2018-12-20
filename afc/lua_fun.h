#ifndef _AFC_LUA_H_
#define _AFC_LUA_H_

#include "export.h"
#include <fstream>
#include <string>
#include <vector>
#include "iolua.h"
#include "../include/lua.h"
#include "../include/lua.hpp"

namespace lua{

AFCAPI void val_save(std::ofstream &out,const char *val,int tab_num);
AFCAPI void begin_table(std::ofstream &out,const char *name,int tab_num);
AFCAPI void end_table(std::ofstream &out,int tab_num);

AFCAPI bool int_save(std::ofstream &out,const char *name,int val,int tab_num); 
AFCAPI bool double_save(std::ofstream &out,const char *name,double val,int tab_num); 
AFCAPI bool float_save(std::ofstream &out,const char *name,float val,int tab_num); 
AFCAPI bool bool_save(std::ofstream &out,const char *name,bool val,int tab_num); 
AFCAPI bool string_save(std::ofstream &out,const char *name,std::string val,int tab_num); 
AFCAPI bool lpstr_save(std::ofstream &out,const char *name,LPTSTR val,int tab_num); 
AFCAPI bool lpstr_zkh_save(std::ofstream &out,const char *name,LPTSTR val,int tab_num); 
AFCAPI bool byte_save(std::ofstream &out, const char *name, BYTE val, int tab_num);
AFCAPI bool string_all_save(std::ofstream &out,const char *name,std::string val,int tab_num) ;

AFCAPI bool save(std::ofstream &out,const char *name,int val,int tab_num);

AFCAPI bool save(std::ofstream &out,const char *name,const std::vector<std::string>& val,int tab_num);

AFCAPI bool open(lua_State * l, const char *name, std::vector<std::string>& val);

//生成实体
// void create_line_arrow(lua_State *l);

}
#endif
