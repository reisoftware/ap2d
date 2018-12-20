#include "stdafx.h"
#include "rpt_sheet.h"
#include "rpt_table.h"
#include "rpt_api_state.h"
#include "rpt_rule_state.h"
#include "rpt_rule.h"
#include "lua_tools.h"
#include "lua_fun.h"
#include "Lua_Tab.h"
#include "std_tools.h"
#include "trace.h"


namespace afc{
namespace rpt{

Sheet::Sheet()
//:breakpoint_(0)
:output_id_(0)
{
}

// void Sheet::set_callback(rpt::PF pf)
// {
// 	afc::for_each<Table, rpt::PF>(tables_, pf, &Table::set_callback);
// }

bool Sheet::output(xls::Sheet& xsheet)
{
	afc::Trace at;
	at.trace("Sheet::output");

	bool result = true;
	output_id_ ++;
	cal_pos();
	xsheet.clear();
	xsheet.prefix = name_;
	xsheet.id = output_id_;
	at.trace("the sheet's name is ", xsheet.name());
	// 	afc::for_each<Table,xls::Sheet&>(tables_, xsheet, &Table::output);
	int n=tables_.size();
	int i=0;
	for(i=0; i<n; ++i){
		if(!tables_[i].output(xsheet)){
			result = false;
		}
	}
	return result;
}

void Sheet::cal_pos()
{
	rpt::api_state().last_pos.set_rc();
	rpt::api_state().sheet_pos = &pos_;
	rpt::rule_state().pos = pos_rule_;
	rpt::pos();
}

void Sheet::open_lua(lua_State * l, LPCTSTR key)
{
	Lua_Tab lt(l, key);
  get_value(string, l, name_, "name");
  get_value(string, l, pos_rule_, "pos_rule");
	// 	get_value(string, l, newsheet_rule_, "newsheet_rule");
	afc::open_lua_ts(l, tables_, "tables");
}

}//namespace
}//namespace
