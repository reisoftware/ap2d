#ifndef _AFC_XLS_POS_H_
#define _AFC_XLS_POS_H_

#include "export.h"
#include "../include/lua.hpp"


namespace afc{
namespace xls{

class AFCAPI Pos
{
public:
	int x;
	int y;
	int w;
	int h;


public:
	Pos();
	void set_rc(int x=1, int y=1, int w=1, int h=1);
	void set_pt(int x1, int y1, int x2, int y2);

public:
	int left()const;
	int right()const;
	int top()const;
	int bottom()const;

public:
	void open_lua(lua_State * l, LPCTSTR key);
};

AFCAPI Pos uniset(const Pos& pos1, const Pos& pos2);

}//namespace
}//namespace

#endif//FILE
