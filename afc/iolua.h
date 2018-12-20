
#ifndef _AFC_IOLUA_H_
#define _AFC_IOLUA_H_

#include <fstream>
#include "export.h"
#include "../include/lua.hpp"

#define get_value(TYPE,L,T,S) \
  lua_pushstring(L,S); \
  lua_gettable(L,-2); \
	T = lua_to##TYPE(L,-1);\
  lua_pop(L,1)
#define get_table(name,L,T,Func) \
	lua_pushstring(L,name); \
	lua_gettable(L,-2); \
	Func(L,T); \
	lua_pop(L,1)

#define get_value_index(TYPE,L,T,S) \
  lua_pushnumber(L,S); \
  lua_gettable(L,-2); \
	T = lua_to##TYPE(L,-1);\
  lua_pop(L,1)

// using std::ofstream;


// 
// /*
//  * class iLua_File
//  * 
//  */
// class OBJECT_API iLua_File
// {
// 
// };
// 
// /*
//  * class oLua_File
//  * parameter : ofile - the output file's full path 
//  */
// class OBJECT_API oLua_File : public ofstream
// {
// private:
// 	unsigned short cur_level_;
// public:
// 	oLua_File(const char *ofile);
// 	~oLua_File();
// 	unsigned short add_level() {return ++cur_level_;}
// 	unsigned short sub_level() {return --cur_level_;}
// 	oLua_File& ident();
// 
// 
// 	template<class T>
// 		oLua_File& save_value(const char *key, T val)
// 	{
// 		if (NULL == key) {
// 			val->lua_save(*this);
// 			return *this;
// 		}
// 		ident();
// 		(*this) << key << " = {\n";
// 		add_level();
// 		val->lua_save(*this);
// 		sub_level();
// 		ident();
// 		(*this) << "},\n";
// 		return *this;
// 	}
// 
// 	template<> oLua_File& save_value(const char *key, int val)
// 	{
// 		return _save(key, val);
// 	}
// 
// 	template<> oLua_File& save_value(const char *key, unsigned long val)
// 	{
// 		return _save(key, val);
// 	}
// 
// 	template<> oLua_File& save_value(const char *key, long val)
// 	{
// 		return _save(key, val);
// 	}
// 
// 	template<> oLua_File& save_value(const char *key, double val)
// 	{
// 		return _save(key, val);
// 	}
// 
// 	template<> oLua_File& save_value(const char *key, const char *val)
// 	{
// 		char buf[] = "val";
// 		if (NULL == key)
// 			key = buf;
// 		this->ident();
// 		(*this) << key << " = [[" << val << "]]" << ",\n";
// 		return *this;
// 	}
// 
// 	template<> oLua_File& save_value(const char *key, LPTSTR val)
// 	{
// 		char buf[] = "val";
// 		if (NULL == key)
// 			key = buf;
// 		this->ident();
// 		(*this) << key << " = [[" << val << "]]" << ",\n";
// 		return *this;
// 	}
// 
// 	template<> oLua_File& save_value(const char *key, unsigned char val)
// 	{
// 		return _save(key, (unsigned int)val);
// 	}
// 
// 	template<> oLua_File& save_value(const char *key, bool val)
// 	{
// 		return _save(key, val);
// 	}
// 	
// 	template<class RanIt> 
// 		oLua_File& save_array(const char *key, RanIt first, RanIt last)
// 	{
// 		ident();
// 		(*this) << key << " = {\n";
// 		add_level();
// 		while (first != last) {
// 			ident();
// 			(*this) << "{\n";
// 			add_level();
// 			save_value(NULL, *first);
// 			sub_level();
// 			ident();
// 			(*this) << "},\n";
// 			++first;
// 		}
// 		sub_level();
// 		ident();
// 		(*this) << "},\n";
// 		return *this;
// 	}
// private:
// 	template<class T>
// 		oLua_File& _save(const char *key, T val)
// 	{
// 		char buf[] = "val";
// 		if (NULL == key)
// 			key = buf;
// 		this->ident();
// 		(*this) << key << " = " << val << ",\n";
// 		return *this;
// 	}
// 
// };
// 
// oLua_File& save_value(oLua_File &fout, const char *key, const LOGFONT *val);

#endif
