// Toolbar_Combo.cpp: implementation of the Toolbar_Combo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Toolbar_Combo.h"

#include "DB_View.h"
#include "Mgr_Database.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Toolbar_Combo::Toolbar_Combo()
{

}

Toolbar_Combo::~Toolbar_Combo()
{

}

BEGIN_MESSAGE_MAP(Toolbar_Combo, CToolBar)
	//{{AFX_MSG_MAP(Toolbar_Combo)
	ON_CBN_SELCHANGE(ID_TOOL_COMBO, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void Toolbar_Combo::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	CString layer_name;
	combo_.GetWindowText(layer_name);
	Entitys ents;
	show_ents_by_layer(DB_View::instance()->cur_view()->scene()->database(),layer_name.GetBuffer(0),true);
	DB_View::instance()->cur_view()->scene()->invalidate();
	
}
