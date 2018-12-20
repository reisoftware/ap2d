#include "stdafx.h"
#include "rpt_rule_state.h"
#include "rpt_rule.h"
#include "call_tcc.h"

namespace afc{
namespace rpt{


Rule_State& rule_state()
{
	static Rule_State the;
	return the;
}

// rule_cell_content::rule_cell_content(LPCTSTR str)
// {
// 	rpt::rule_state().cell_content = str;
// }
// rule_cell_content::~rule_cell_content()
// {
// 	rpt::rule_state().cell_content = "";
// }

}//namespace
}//namespace
