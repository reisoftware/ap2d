// Replace_String.h: interface for the Replace_String class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPLACE_STRING_H__005FFC7A_E123_4C77_8500_EDBAAE3420C2__INCLUDED_)
#define AFX_REPLACE_STRING_H__005FFC7A_E123_4C77_8500_EDBAAE3420C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mgr_Database.h"

class Replace_String  
{
public:
	Replace_String();
	virtual ~Replace_String();

	void replace(CString rep_str,CString style,CString sign,CString postfix);
	void rep_strings(CString rep_str,Entitys &texts,CString style,CString sign,CString postfix);

	void rep_text(CString rep_str,dlhml::Text *t ,CString style,CString sign,CString postfix);

	//½Ó¿Ú
	void replace_text(dlhml::Text *t,CString style,CString sign);
private:
	void deal_equal(dlhml::Text *t,CString style,CString sign,CString postfix);
	void deal_include(CString rep_str,dlhml::Text *t,CString style,CString sign,CString postfix);


	void deal_head(CString right,CString rep_str,dlhml::Text *t,CString style,CString sign,CString postfix);
	void deal_tail(CString left,CString right,CString rep_str,dlhml::Text *t,CString style,CString sign,CString postfix);

private:
	void add_postfix(dlhml::Text *t,CString right,CString postfix);
	void draw_frame_style(dlhml::Text *t,CString style);
	void draw_circle(dlhml::Text *t);
	void draw_rect(dlhml::Text *t);


};

#endif // !defined(AFX_REPLACE_STRING_H__005FFC7A_E123_4C77_8500_EDBAAE3420C2__INCLUDED_)
