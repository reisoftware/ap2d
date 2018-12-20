#ifndef _AFC_RPT_BOOK_H_
#define _AFC_RPT_BOOK_H_

#include "export.h"
#include "rpt_sheet.h"
#include "rpt_style_db.h"
#include "xls_book.h"
#include "../include/lua.hpp"

namespace afc{
namespace rpt{


class AFCAPI Book
{
public:
// 	void set_callback(rpt::PF pf);
	void output(xls::Book& xbook);

public:
	void open_lua_starting(LPCTSTR file);
  void open_lua(lua_State * l, LPCTSTR key);

private:
	SDB sdb_;

private:
	afc::string name_;
	std::vector<Sheet> sheets_;
};


}//namespace
}//namespace


#endif//FILE