#include "stdafx.h"
#include "ap2d_check.h"

//extern "C"
//{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

//}

int login()
{
	return true;
	/*
	char* rs=0;
	int result = 0;
	lua_State* L = lua_open();
	luaL_openlibs(L);
	if ((luaL_loadfile(L,"ap2d.lua")==0) && lua_pcall(L, 0, 0,0) != 0){
		const char* str = lua_tostring(L,-1);
	    rs = (char*)malloc(strlen(str));
		strcpy(rs,str);
	}
	else{
#include "ap2d_check.loh"
	lua_getglobal(L,"logined");
	result = lua_toboolean(L,-1);
      rs = (char*)calloc(1,16);
	  strcpy(rs,result == 1?"OK":"FALSE");
    }
	lua_pop(L,1);
	lua_close(L);
	return result;
	*/

	//char* rs=0;
	//应该是程序新的验证方式2018-11-9
	int result = 0;
	lua_State* L = lua_open();
	luaL_openlibs(L);
	//if ((luaL_loadfile(L,"ap2d.lua")==0) && lua_pcall(L, 0, 0,0) != 0){
	//	const char* str = lua_tostring(L,-1);
	//    rs = (char*)malloc(strlen(str));
	//	strcpy(rs,str);
	//}

	//else{
#include "ap2d_check.loh"
	lua_getglobal(L,"logined");
	result = lua_toboolean(L,-1);
    //  rs = (char*)calloc(1,16);
	 // strcpy(rs,result == 1?"OK":"FALSE");
    //}
	lua_pop(L,1);
	lua_close(L);
	return result;

}
