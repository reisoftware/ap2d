// Mgr_Convert.h: interface for the Mgr_Convert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_CONVERT_H__13576D8A_6DD7_4ED5_A052_8C25485E27E4__INCLUDED_)
#define AFX_MGR_CONVERT_H__13576D8A_6DD7_4ED5_A052_8C25485E27E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dimension_Style.h"

const CString ltype_continues= "Continuous";
const CString ltype_dot= "dot";
const CString ltype_center= "center";


const CString g_dimKindRectFrame = "RectFrame";
const CString g_dimKindNoFrame = "NoFrame";
const CString g_dimKindArcFrame = "ArcFrame";
const CString g_dimKindArrowFrame = "ArrowFrame";
const CString g_dimKindBaseLineFrame = "BaseLine_Frame";
const CString g_dimKindCircleFrame = "Circle_Frame";
const CString g_jointEnter = "Enter";
const CString g_jointPlace = "Place";
const CString g_jointAddCode = "AddCode";
const CString g_jointShortLine = "ShortLine";

const CString Dim_Kind_Lead_dim = "Lead Dim";
const CString Dim_Kind_Text_dim = "Text Dim";

class Mgr_Convert  
{
public:
	Mgr_Convert();
	virtual ~Mgr_Convert();

};


CString get_arrow_pos(int pos);
int get_arrow_pos(CString str);
int get_arrow_num(CString str);

dlhml::Dimension_Style::Arrow get_arrow_style_by_int(int pos);
dlhml::Dimension_Style::Arrow get_arrow_style_by_name(CString name);
CString get_arrow_style(dlhml::Dimension_Style::Arrow arrow);


dlhml::Dimension_Style::Txt_Frame get_txt_frame(CString name);
CString get_txt_frame(dlhml::Dimension_Style::Txt_Frame txt_style);

CString get_txt_pos(dlhml::Dimension_Style::TextPos txt_pos);

COLORREF index_to_colorref(int index);
int colorref_to_index(COLORREF col);


time_t get_time(std::string time);
#endif // !defined(AFX_MGR_CONVERT_H__13576D8A_6DD7_4ED5_A052_8C25485E27E4__INCLUDED_)
