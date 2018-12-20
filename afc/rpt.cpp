#include "stdafx.h"
#include "rpt.h"
#include "rpt_rule_state.h"

namespace afc{

Report::Report()
{
}

void Report::output(xls::Book& xbook, LPCTSTR file, afc::PF_ADD_SYMBOL pf)
{
	set_book(file);
	set_callback(pf);
	output(xbook);
}

// Report::Report(LPCTSTR book_file)
// {
// 	set_book(book_file);
// }

void Report::set_book(LPCTSTR file)
{
	book_.open_lua_starting(file);
}

void Report::set_callback(afc::PF_ADD_SYMBOL pf)
{
	rpt::rule_state().pf.add_api = pf;
// 	book_.set_callback(pf);
}

void Report::output(xls::Book& xbook)
{
	book_.output(xbook);
}

}//namespace