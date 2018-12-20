// ommand_Line_Info.h: interface for the Command_Line_Info class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OMMAND_LINE_INFO_H__065E132F_66D5_496A_A663_8D5699E479EB__INCLUDED_)
#define AFX_OMMAND_LINE_INFO_H__065E132F_66D5_496A_A663_8D5699E479EB__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable : 4786)

#include "Command_Line.h"
#include "counter.h"

namespace dlhml{

class Command_Line_Info : public Command_Line  
{
public:
	Command_Line_Info(CEdit& current,CEdit& old);
	virtual ~Command_Line_Info();
	void close();

	void show_command(LPCTSTR info,bool update);
	bool get_two_value(Float& val1,Float& val2) const;
	bool get_one_value(Float& val) const;
	int get_string(LPTSTR str) const;

	void show_coord(LPCTSTR info);

private:
	CEdit& current_;
	CEdit& old_;

	bool numeric_char(TCHAR ch) const;
	bool numeric_str(LPCTSTR str) const;
private:
	MCT_DEF
};
}
#endif // !defined(AFX_OMMAND_LINE_INFO_H__065E132F_66D5_496A_A663_8D5699E479EB__INCLUDED_)
