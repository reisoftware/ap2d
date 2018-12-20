#include "stdafx.h"
#include "rpt_add_symbol.h"
#include "rpt_api.h"
#include "rpt_rule_state.h"
#include "../include/getrace.h"


namespace afc{
namespace rpt{

namespace the{

static void add_symbol(afc::Tcc &t)
{
	t.add_symbol("TRACE_OUT", TRACE_OUT);
	t.add_symbol("trace", rpt_trace);
	t.add_symbol("trace_i", rpt_trace_i);
	t.add_symbol("trace_f", rpt_trace_f);
	t.add_symbol("trace_s", rpt_trace_s);

	t.add_symbol("get_last_x", rpt_get_last_x);
	t.add_symbol("get_last_y", rpt_get_last_y);
	t.add_symbol("set_start_x", rpt_set_start_x);
	t.add_symbol("set_start_y", rpt_set_start_y);

// 	t.add_symbol("get_sheet_x", rpt_get_sheet_x);
// 	t.add_symbol("get_sheet_y", rpt_get_sheet_y);
// 	t.add_symbol("set_sheet_x", rpt_set_sheet_x);
// 	t.add_symbol("set_sheet_y", rpt_set_sheet_y);

	t.add_symbol("get_table_x", rpt_get_table_x);
	t.add_symbol("get_table_y", rpt_get_table_y);
	t.add_symbol("set_table_x", rpt_set_table_x);
	t.add_symbol("set_table_y", rpt_set_table_y);

	t.add_symbol("set_column_x", rpt_set_column_x);
	t.add_symbol("set_column_y", rpt_set_column_y);
	t.add_symbol("set_column_w", rpt_set_column_w);
	t.add_symbol("set_column_h", rpt_set_column_h);

	t.add_symbol("get_super_dats_size", rpt_get_super_dats_size);
	t.add_symbol("get_table_dats_size", rpt_get_table_dats_size);
	t.add_symbol("get_super_dats_item", rpt_get_super_dats_item);
	t.add_symbol("get_table_dats_item", rpt_get_table_dats_item);
	t.add_symbol("add_table_dat", rpt_add_table_dat);
	t.add_symbol("clear_table_dats", rpt_clear_table_dats);

	t.add_symbol("pass", rpt_pass);
	t.add_symbol("unpass", rpt_unpass);
	t.add_symbol("get_curitem", rpt_get_curitem);

	t.add_symbol("equ", rpt_equ);
	t.add_symbol("unequ", rpt_unequ);
	t.add_symbol("get_item1", rpt_get_item1);
	t.add_symbol("get_item2", rpt_get_item2);

	t.add_symbol("less", rpt_less);
	t.add_symbol("unless", rpt_unless);
	t.add_symbol("get_group1_size", rpt_get_group1_size);
	t.add_symbol("get_group2_size", rpt_get_group2_size);
	t.add_symbol("get_group1_item", rpt_get_group1_item);
	t.add_symbol("get_group2_item", rpt_get_group2_item);

	t.add_symbol("get_curgroup_size", rpt_get_curgroup_size);
	t.add_symbol("get_curgroup_item", rpt_get_curgroup_item);
	t.add_symbol("set_content_i", rpt_set_content_i);
	t.add_symbol("set_content_f", rpt_set_content_f);
	t.add_symbol("set_content_s", rpt_set_content_s);

	t.add_symbol("newsheet", rpt_newsheet);
	t.add_symbol("unnewsheet", rpt_unnewsheet);
}

}//namespace

void add_symbol(afc::Tcc &t)
{
	the::add_symbol(t);
	if(rpt::rule_state().pf.add_api){
		rpt::rule_state().pf.add_api(t);
	}
}


}//namespace
}//namespace
