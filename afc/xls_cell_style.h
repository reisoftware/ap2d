#ifndef _AFC_XLS_CELL_STYLE_H_
#define _AFC_XLS_CELL_STYLE_H_

#include "export.h"
#include "str.h"
#include "bool.h"
#include "../include/lua.hpp"

namespace afc{
namespace xls{

class AFCAPI Cell_Style
{
public:
	afc::string name;
	afc::string font;
	double size;
	int text_color;
	int back_color;
	BOOL blod;
	BOOL italic;
	int h_align;	//1常规，2左，3中，4右，5填充，6两端对齐，7跨列居中，8分散对齐
	int v_align;	//1上，2中，3下，4两端对齐，5分散对齐
	double precision;
	int bit;
	BOOL addends;

public:
	Cell_Style();
	void open_lua(lua_State * l, LPCTSTR key);
};

typedef Cell_Style CS;

}//namespace
}//namespace

#endif//FILE
