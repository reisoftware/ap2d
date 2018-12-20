// cmd.h: interface for the cmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_H__F1D03975_9736_4254_A42B_6324844A2242__INCLUDED_)
#define AFX_CMD_H__F1D03975_9736_4254_A42B_6324844A2242__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "geptr.h"
namespace gelib{
class Cmd  
{
public:
	virtual ~Cmd() {};
	virtual bool execute() = 0;
	virtual bool unexecute() {return false;}
	virtual void add_cmd(GEXY::CPtr<Cmd>& c) {}
};
}
#endif // !defined(AFX_CMD_H__F1D03975_9736_4254_A42B_6324844A2242__INCLUDED_)
