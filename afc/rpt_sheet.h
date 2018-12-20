#ifndef _AFC_RPT_SHEET_H_
#define _AFC_RPT_SHEET_H_

#include "export.h"
#include "rpt_fptr.h"
#include "rpt_table.h"
#include "xls_sheet.h"
#include "../include/lua.hpp"

namespace afc{
namespace rpt{

class Cell_Mgr;

class AFCAPI Sheet
{
public:
	Sheet();

public:
// 	void set_callback(rpt::PF pf);
	bool output(xls::Sheet& xsheet);

public:
	void cal_pos();

public:
  void open_lua(lua_State * l, LPCTSTR key);
	
private:
	afc::string name_;
	afc::string pos_rule_;
	std::vector<Table> tables_;

private:
	xls::Pos pos_;

private:
// 	int breakpoint_;
	int output_id_;

};

}//namespace
}//namespace

#endif//FILE

