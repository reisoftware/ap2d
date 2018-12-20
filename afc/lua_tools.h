#ifndef _AFC_LUA_TOOLS_H_
#define _AFC_LUA_TOOLS_H_

#include <vector>

namespace afc{

#define def_open_lua_starting(class_name, main_key) \
static class_name * this_lua_ = NULL;	\
static int open_lua_ptr(lua_State * l)	\
{	\
	assert(l);	\
	assert(this_lua_);	\
	this_lua_->open_lua(l, main_key);	\
	return 0;	\
}	\
void class_name::open_lua_starting(LPCTSTR file)	\
{	\
  this_lua_ = this;	\
  lua_State *L = lua_open();      /* opens Lua */		\
  luaopen_base(L);                /* opens the basic library */		\
  luaopen_table(L);               /* opens the table library */		\
  luaopen_io(L);                  /* opens the I/O library */		\
  luaopen_string(L);              /* opens the string lib. */		\
  luaopen_math(L);                /* opens the math lib. */		\
  lua_pushcfunction(L,&open_lua_ptr);	\
  lua_setglobal(L,"entry");	\
  luaL_loadfile(L, file);	\
  lua_pcall(L,0,0,0);	\
  lua_close(L);	\
  this_lua_ = NULL;	\
}	


template<class T>
void open_lua_ts(lua_State * l, std::vector<T>& dst, LPCTSTR key)
{
  Lua_Tab lt(l, key);
  int index = lua_gettop(l);
  lua_pushnil(l);
	dst.clear();
  while(lua_next(l, index) != 0){
    T t;
    t.open_lua(l, NULL);
		dst.push_back(t);
    lua_pop(l, 1);
  }
}

template<class T>
void open_lua_tps(lua_State * l, std::vector<T*>& dst, LPCTSTR key)
{
  Lua_Tab lt(l, key);
  int index = lua_gettop(l);
  lua_pushnil(l);
	afc::close<T>(dst);
  while(lua_next(l, index) != 0){
    T * t = T::create();
    t->open_lua(l, NULL);
		dst.push_back(t);
    lua_pop(l, 1);
  }
}


}

#endif//FILE
