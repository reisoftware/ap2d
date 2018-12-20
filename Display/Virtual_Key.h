// Virtual_Key.h: interface for the Virtual_Key class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_VIRTUAL_KEY_H__A1FA46F4_EEA4_46E2_B654_FF234E3B0A38__INCLUDED_
#define AFX_VIRTUAL_KEY_H__A1FA46F4_EEA4_46E2_B654_FF234E3B0A38__INCLUDED_


#include "display_export.h"

namespace dlhml{
class Point;
class DISPLAY_API Virtual_Key  
{
public:
	Virtual_Key();
	~Virtual_Key();

	void set_data(UINT nChar, UINT nRepCnt, UINT nFlags);
	char get_char() const;
	int get_number() const;

	bool esc() const;
	bool enter() const;
	bool comma() const;			//","
	bool dot() const;
	bool ctrl() const;
	bool character() const;
	bool number() const;
	bool backspace() const;
	bool del() const;

private:
	UINT char_;
	UINT repcnt_;
	UINT flags_;

	bool char_char(TCHAR ch) const;
	bool numeric_char(TCHAR ch) const;

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_VIRTUAL_KEY_H__A1FA46F4_EEA4_46E2_B654_FF234E3B0A38__INCLUDED_)
