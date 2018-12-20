#ifndef _AFC_RPT_RULE_STATE_H_
#define _AFC_RPT_RULE_STATE_H_

#include "export.h"
#include "dat.h"
#include "dat_mgr.h"
#include "rpt_fptr.h"

namespace afc{
namespace rpt{

class Rule_State
{
public:
	afc::string newsheet;

public:
	afc::string init;
	afc::string filter;
	afc::string group;
	afc::string sort;
	afc::string pos;
	afc::string cell_content;

public:
	PF pf;
};

AFCAPI Rule_State& rule_state();
#define rpt_rule afc::rpt::rule_state()

// class rule_cell_content
// {
// public:
// 	rule_cell_content(LPCTSTR str);
// 	~rule_cell_content();
// };

}//namespace
}//namespace

#endif//FILE
