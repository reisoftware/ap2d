// Command_Line_In.cpp: implementation of the Command_Line_In class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Command_Line_In.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Command_Line_In::Command_Line_In()
MCT_INIT1("Command_Line_In")
{

}

Command_Line_In::~Command_Line_In()
{

}
void Command_Line_In::close()
{
	delete this;
}
void Command_Line_In::show_command(LPCTSTR info,bool update)
{
}
bool Command_Line_In::get_two_value(Float& val1,Float& val2) const
{
	return false;
}
bool Command_Line_In::get_one_value(Float& val) const
{
	return false;
}
int Command_Line_In::get_string(LPTSTR str) const
{
	return 0;
}
void Command_Line_In::show_coord(LPCTSTR info)
{
}
}
