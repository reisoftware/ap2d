// Command_Line.h: interface for the Command_Line class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_COMMAND_LINE_H__36F84066_F3D7_445D_B2CE_1DAD993D191C__INCLUDED_
#define AFX_COMMAND_LINE_H__36F84066_F3D7_445D_B2CE_1DAD993D191C__INCLUDED_

#include "display_export.h"
#include "../object/export.h"

namespace dlhml{
class DISPLAY_API Command_Line  
{
public:
	Command_Line();
	virtual ~Command_Line();

	virtual void close() = 0;

	//command line
	virtual void show_command(LPCTSTR info,bool update) = 0;
	virtual bool get_two_value(Float& val1,Float& val2) const = 0;
	virtual bool get_one_value(Float& val) const = 0;
	virtual int get_string(LPTSTR str) const = 0;
	//status 
	virtual void show_coord(LPCTSTR info) = 0;
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_COMMAND_LINE_H__36F84066_F3D7_445D_B2CE_1DAD993D191C__INCLUDED_)
