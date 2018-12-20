#ifndef _AFC_RPT_COLUMN_H_
#define _AFC_RPT_COLUMN_H_

#include "export.h"
#include "str.h"
#include "dat.h"
#include "rpt_fptr.h"
#include "xls_sheet.h"
#include "../include/lua.hpp"

namespace afc{
namespace rpt{

class Column
{
public:
	Column();

public:
// 	void set_callback(rpt::PF pf);
	void output(xls::Sheet& xsheet);
private:
	void cal_pos(xls::Cell& cell);
	void cal_centent(xls::Cell& cell);
	void cal_style(xls::Cell& cell);
	void cal_size(xls::Sheet& xsheet);

public:
	void open_lua(lua_State * l, LPCTSTR key);

public:
	afc::string content_;
	afc::string content_rule_;
	afc::string style_;
	afc::string pos_rule_;

public:
	double w_;
	double h_;



private:
	xls::Pos pos_;

// 	afc::string stype_;
// 	afc::string stype_rule_;

private:
	//PF pf_;
};


}//namespace
}//namespace


#endif//FILE
