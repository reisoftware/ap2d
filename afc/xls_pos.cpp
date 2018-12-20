#include "stdafx.h"
#include "xls_pos.h"
#include "lua_tools.h"
#include "lua_fun.h"
#include "Lua_Tab.h"

namespace afc{
namespace xls{

Pos::Pos()
{
	set_rc();
}

void Pos::set_rc(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void Pos::set_pt(int x1, int y1, int x2, int y2)
{
	this->x = min(x1, x2);
	this->y = min(y1, y2);
	this->w = abs(x2-x1+1);
	this->h = abs(y2-y1+1);
}

int Pos::left()const
{
	return x;
}

int Pos::right()const
{
	return x+w-1;
}

int Pos::top()const
{
	return y;
}

int Pos::bottom()const
{
	return y+h-1;
}

void Pos::open_lua(lua_State * l, LPCTSTR key)
{
	Lua_Tab lt(l, key);
	get_value(number, l, x, "x");
	get_value(number, l, y, "y");
	get_value(number, l, w, "w");
	get_value(number, l, h, "h");
	x = x<=0 ? 1 : x;
	y = y<=0 ? 1 : y;
	w = w<=0 ? 1 : w;
	h = h<=0 ? 1 : h;
}

Pos uniset(const Pos& pos1, const Pos& pos2)
{
	int x1 = min(pos1.left(), pos2.left());
	int x2 = max(pos1.right(), pos2.right());
	int y1 = min(pos1.top(), pos2.top());
	int y2 = max(pos1.bottom(), pos2.bottom());
	Pos pos;
	pos.set_pt(x1, y1, x2, y2);
	return pos;
}

}//namespace
}//namespace
