
#ifndef _AFC_LUA_TAB_H_
#define _AFC_LUA_TAB_H_

#include "export.h"
#include "iolua.h"
#include "lua_fun.h"

class AFCAPI Lua_Tab  
{
public:
  Lua_Tab(lua_State * l, LPCTSTR key);
	virtual ~Lua_Tab();
private:
	lua_State * l_;
  LPCTSTR key_;
};

#endif//FILE

