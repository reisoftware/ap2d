// Mgr_Lua.h: interface for the Mgr_Lua class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_LUA_H__1F2C51AE_F67E_4162_947C_8715CF655557__INCLUDED_)
#define AFX_MGR_LUA_H__1F2C51AE_F67E_4162_947C_8715CF655557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Mgr_Dxfs.h"
#include "ApLayer_Ent.h"

#define ELSE_LAYER  "ELSE_LAYER"

class Mgr_Lua  
{
public:
	Mgr_Lua();
	virtual ~Mgr_Lua();

};
void save_lua(std::string lua_file,Entitys &ents);
void save_luas(std::string dxf_file,strings &lua_files);
void create_luas(std::string dxf_file,strings &lua_files,Detail &detail);


void download_luas(std::string detail_name);
void open_lua(std::string lua_file,dlhml::Database *db);



#endif // !defined(AFX_MGR_LUA_H__1F2C51AE_F67E_4162_947C_8715CF655557__INCLUDED_)
