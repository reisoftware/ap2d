#include "stdafx.h"
#include "xls_cell_style.h"
#include "lua_tools.h"
#include "lua_fun.h"
#include "Lua_Tab.h"

namespace afc{
namespace xls{

const int TEXT_SIZE = 10;
const int HALIGN_DEFAULT = 1;
const int VALIGN_DEFAULT = 2;

Cell_Style::Cell_Style()
:size(TEXT_SIZE)
,text_color(0)
,back_color(0)
,blod(FALSE)
,italic(FALSE)
,h_align(HALIGN_DEFAULT)
,v_align(VALIGN_DEFAULT)
,precision(1)
,bit(0)
,addends(FALSE)
{

}


void Cell_Style::open_lua(lua_State * l, LPCTSTR key)
{
	get_value(string, l, name, "name");
	get_value(string, l, font, "font");
	get_value(number, l, size, "size");
	get_value(number, l, text_color, "text_color");
	get_value(number, l, back_color, "back_color");
	get_value(number, l, blod, "blod");
	get_value(number, l, italic, "italic");
	get_value(number, l, h_align, "h_align");
	get_value(number, l, v_align, "v_align");
	get_value(number, l, precision, "precision");
	get_value(number, l, bit, "bit");
	get_value(number, l, addends, "addends");

	size = size<=0 ? TEXT_SIZE : size;
	h_align = h_align<=0 ? HALIGN_DEFAULT : h_align;
	v_align = v_align<=0 ? VALIGN_DEFAULT : v_align;
// 	precision = precision<=0 ? 1 : precision;
}


}//namespace
}//namespace
