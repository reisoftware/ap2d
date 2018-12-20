// Lua_Tab.cpp: implementation of the Lua_Tab class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lua_tab.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Lua_Tab::Lua_Tab(lua_State * l, LPCTSTR key)
:l_(l)
,key_(key)
{
  if(key_){
    lua_pushstring(l,key_);
    lua_gettable(l,-2);
  }
}

Lua_Tab::~Lua_Tab()
{
	if(key_){
		lua_pop(l_,1);
	}
}
