#include "stdafx.h"
#include "rpt_rule.h"
#include "rpt_api_state.h"
#include "rpt_rule_state.h"
#include "rpt_add_symbol.h"
#include "call_tcc.h"
#include "std_tools.h"
#include "trace.h"

namespace afc{
namespace rpt{

namespace the{

static afc::string format(LPCTSTR str, LPCTSTR arg1)
{
	assert(str);
	afc::string param1 = arg1;
	if(!arg1){
		 param1 = "";
	}
  char buf[2048];
  sprintf(buf, str, param1);
	return buf;
}

static afc::string rule_inc()
{
	afc::string str;
	str += "#include ";
	str += "\"";
	str += "..\\script\\rpt\\rpt.c";
	str += "\"";
	str += "\n";
	return str;
}

static afc::string get_code(LPCTSTR fname, LPCTSTR arg1)
{
	afc::string str = 
	the::rule_inc() +
	"void %s()\n"
	"{\n"
	"%s\n"
	"}\n";
	assert(str);
	assert(fname);
	afc::string param1 = arg1;
	if(!arg1){
		 param1 = "";
	}
  char buf[2048];
  sprintf(buf, str, fname, param1);
	return buf;
}



}//namespace

static afc::string fstr_pos_ = 
the::rule_inc() +
"void pos()\n"
"{\n"
"%s\n"
"}\n";
void pos()
{
	afc::string code = the::format(fstr_pos_, rpt_rule.pos);
	afc::call_code(&rpt::add_symbol, code, "pos");
}

static afc::string fstr_init_ = 
the::rule_inc() +
"void dat_init()\n"
"{\n"
"%s\n"
"}\n";
void init()
{
	afc::string code = the::format(fstr_init_, rpt_rule.init);
	afc::call_code(&rpt::add_symbol, code, "dat_init");
}

static afc::string fstr_filter_ = 
the::rule_inc() +
"void filter()\n"
"{\n"
"%s\n"
"}\n";
bool filter(afc::Dat * t)
{
	assert(t);
	rpt_api.cur_dat = t;
	rpt_api.filter = false;
	afc::string code = the::format(fstr_filter_, rpt_rule.filter);
	afc::call_code(&rpt::add_symbol, code, "filter");
	return rpt_api.filter;
}

static afc::string fstr_group_ = 
the::rule_inc() +
"void group()\n"
"{\n"
"%s\n"
"}\n";
bool group(afc::Dat * t1, afc::Dat * t2)
{
	assert(t1);
	assert(t2);
	rpt_api.dat1 = t1;
	rpt_api.dat2 = t2;
	rpt_api.group = false;	//无法分组规则，即不分组（equ）
	afc::string code = the::format(fstr_group_, rpt_rule.group);
	afc::call_code(&rpt::add_symbol, code, "group");
	return rpt_api.group;
}

static afc::string fstr_sort_ = 
the::rule_inc() +
"void sort()\n"
"{\n"
"%s\n"
"}\n";
bool sort(std::vector<afc::Dat*> * g1, std::vector<afc::Dat*> * g2)
{
	rpt_api.group1 = g1;
	rpt_api.group2 = g2;
	rpt_api.sort = false;
	afc::string code = the::format(fstr_sort_, rpt_rule.sort);
	afc::call_code(&rpt::add_symbol, code, "sort");
	return rpt_api.sort;
}


static afc::string fstr_cell_content_ = 
the::rule_inc() +
"void cell_content()\n"
"{\n"
"%s\n"
"}\n";
void cell_content()
{
	afc::string code = the::format(fstr_cell_content_, rpt_rule.cell_content);
	afc::call_code(&rpt::add_symbol, code, "cell_content");
}


bool newsheet()
{
	rpt_api.newsheet = false;
	afc::string fname = "f_newsheet";
	afc::string code = the::get_code(fname,rpt_rule.newsheet);
	afc::call_code(&rpt::add_symbol, code, fname);
	return rpt_api.newsheet;
}


}//namespace
}//namespace
