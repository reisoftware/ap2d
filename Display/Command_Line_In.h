// Command_Line_In.h: interface for the Command_Line_In class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_COMMAND_LINE_IN_H__F5B5AB64_AF9D_47DD_8F34_46247BDF2D5C__INCLUDED_
#define AFX_COMMAND_LINE_IN_H__F5B5AB64_AF9D_47DD_8F34_46247BDF2D5C__INCLUDED_

#include "Command_Line.h"

namespace dlhml{
class Command_Line_In : public Command_Line  
{
public:
	Command_Line_In();
	virtual ~Command_Line_In();

	void close();

	void show_command(LPCTSTR info,bool update);
	bool get_two_value(Float& val1,Float& val2) const;
	bool get_one_value(Float& val) const;
	int get_string(LPTSTR str) const;

	void show_coord(LPCTSTR info);

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_COMMAND_LINE_IN_H__F5B5AB64_AF9D_47DD_8F34_46247BDF2D5C__INCLUDED_)
