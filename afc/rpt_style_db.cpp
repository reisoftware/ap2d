#include "stdafx.h"
#include "rpt_style_db.h"
#include "lua_tools.h"
#include "lua_fun.h"
#include "Lua_Tab.h"


namespace afc{
namespace rpt{

// SDB& sdb()
// {
// 	static SDB& the;
// 	return the;
// }

void Style_DB::fill(xls::CS& cs)
{
	fill(cs.name, cs);
}

void Style_DB::fill(LPCTSTR name, xls::CS& cs)
{
	int n=css.size();
	int i=0;
	for(i=0; i<n; ++i){
		if(css[i].name == name){
			cs = css[i];
			return;
		}
	}
}

void Style_DB::open_lua(lua_State * l, LPCTSTR key)
{
	Lua_Tab lt(l, key);
	afc::open_lua_ts(l, css, "css");
}

}//namespace
}//namespace
