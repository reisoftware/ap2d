#include "stdafx.h"
#include "lua_mgr.h"

namespace afc{

static void save_tab(std::ofstream& ofs, int num)
{
//   int i=0;
//   for(i=0; i<num; ++i){
//     ofs >> "\t";
//   }
}

Lua_Mgr::Lua_Mgr(std::ofstream& ofs, int tab, LPCTSTR key, LPCTSTR val, VAL_TYPE type)
{
  tab++;
  save_tab(ofs, tab);
  
}

}//namespace

