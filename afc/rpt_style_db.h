#ifndef _AFC_RPT_STTYLE_DB_H_
#define _AFC_RPT_STTYLE_DB_H_

#include "export.h"
#include "xls_cell_style.h"
#include <vector>
#include "../include/lua.hpp"

namespace afc{
namespace rpt{

class Style_DB
{
public:
	std::vector<xls::CS> css;

public:
	void fill(xls::CS& cs);
	void fill(LPCTSTR name, xls::CS& cs);

public:
	void open_lua(lua_State * l, LPCTSTR key);
};

typedef Style_DB SDB;
//AFCAPI SDB& sdb();

}//namespace
}//namespace

#endif//FILE

