// Mgr_Control.cpp: implementation of the Mgr_Control class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Control.h"
#include "Mgr_Convert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Control::Mgr_Control()
{

}

Mgr_Control::~Mgr_Control()
{

}
void set_combo_line_type(CComboBox &combo)
{
	combo.AddString(ltype_continues);
	combo.AddString(ltype_dot);
	combo.AddString(ltype_center);

}
void set_combo_arrow_pos(CComboBox &combo)
{
	combo.AddString("start_pos");
	combo.AddString("end_pos");
	combo.AddString("two_side");
	combo.AddString("no");
}
void set_combo_arrow_style(CComboBox &combo)
{
	combo.InsertString(0,"common");
	combo.InsertString(0,"circle");
	combo.InsertString(0,"lean line");
	combo.InsertString(0,"no");
}
void set_combo_dim_kind(CComboBox &combo)
{
	combo.InsertString(0,"Base Line Dim");
	combo.InsertString(0,"Continue Line Dim");
}
void set_combo_text_pos(CComboBox &combo)
{
	combo.InsertString(0,"Up");
	combo.InsertString(0,"Down");
	combo.InsertString(0,"Center");

}
void set_combo_frame_kind(CComboBox &combo)
{
	combo.InsertString(0,g_dimKindRectFrame);
	combo.InsertString(0,g_dimKindNoFrame);
	combo.InsertString(0,g_dimKindArcFrame);
	combo.InsertString(0,g_dimKindArrowFrame);
	combo.InsertString(0,g_dimKindBaseLineFrame);
}

void set_combo_arrow_num(CComboBox &combo)
{	
	combo.InsertString(0,"0");
	combo.InsertString(0,"1");
	combo.InsertString(0,"2");
	combo.InsertString(0,"3");
}

void set_combo_txt(CComboBox &combo,CString str)
{
	int item = combo.FindString(0,str);
	combo.SetCurSel(item);
}
void set_combo_color(CComboBox &combo,int color_index)
{
/*
	CString color;
	color.Format("%d",color_index);	
	combo.SetWindowText(color);
*/
	if(color_index == 0)
		color_index = 1;

	combo.SetCurSel(color_index-1);

}


