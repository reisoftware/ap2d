#include "stdafx.h"
#include "rpt_book.h"
#include "rpt_api_state.h"
#include "xls_book.h"
#include "lua_tools.h"
#include "lua_fun.h"
#include "Lua_Tab.h"
#include "std_tools.h"
#include "trace.h"

#include <cassert>


namespace afc{
namespace rpt{

// void Book::set_callback(rpt::PF pf)
// {
// 	afc::for_each<Sheet, rpt::PF>(sheets_, pf, &Sheet::set_callback);
// }

void Book::output(xls::Book& xbook)
{
	afc::Trace at;
	at.trace("Book::output");

	rpt::api_state().init();
	rpt::api_state().sdb = &sdb_;
	xls::Sheet t;
	//	afc::for_each<Sheet,xls::Sheet&>(sheets_, xbook.sheets.back(), &Sheet::output);
	int n=sheets_.size();
	int i=0;
	for(i=0; i<n; ++i){
		xbook.sheets.push_back(t);
		if(!sheets_[i].output(xbook.sheets.back())){
			--i;
		}
	}

	xbook.name = name_;
}


////////////////////////// << lua starting >> ////////////////////////
// static Book * lua_ = NULL;
// static int open_lua_ptr(lua_State * l)
// {
// 	assert(l);
// 	assert(lua_);
// 	lua_->open_lua(l, "book");
// 	return 0;
// }
// void Book::open_lua_starting(LPCTSTR file)
// {
//   lua_ = this;
//   lua_State *L = lua_open();      /* opens Lua */ 
//   luaopen_base(L);                /* opens the basic library */ 
//   luaopen_table(L);               /* opens the table library */ 
//   luaopen_io(L);                  /* opens the I/O library */ 
//   luaopen_string(L);              /* opens the string lib. */ 
//   luaopen_math(L);                /* opens the math lib. */ 
//   lua_pushcfunction(L,&open_lua_ptr);
//   lua_setglobal(L,"entry");
//   luaL_loadfile(L, file);
//   lua_pcall(L,0,0,0);
//   lua_close(L);
//   lua_ = NULL;
// }

////////////////////////// << lua >> ////////////////////////
def_open_lua_starting(Book, "book")
void Book::open_lua(lua_State * l, LPCTSTR key)
{
  Lua_Tab lt(l, key);
  get_value(string, l, name_, "name");
	afc::open_lua_ts(l, sheets_, "sheets");
	sdb_.open_lua(l, "style_db");
}


}//namespace
}//namespace
