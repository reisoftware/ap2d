// Dlg_Auto_Check_Main.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Auto_Check_Main.h"
#include "Dlg_Auto_Check.h"
#include "Dlg_Select_Color.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Auto_Check_Main dialog


Dlg_Auto_Check_Main::Dlg_Auto_Check_Main(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Auto_Check_Main::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Auto_Check_Main)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Auto_Check_Main::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Auto_Check_Main)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Auto_Check_Main, CDialog)
	//{{AFX_MSG_MAP(Dlg_Auto_Check_Main)
	ON_BN_CLICKED(IDC_BUT_JISHOU_STANDART, OnButJishouStandart)
	ON_BN_CLICKED(IDC_BUT_JISHOU_STANDART3, OnButJishouStandart3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Auto_Check_Main message handlers

void Dlg_Auto_Check_Main::OnButJishouStandart() 
{
	// TODO: Add your control notification handler code here
	Dlg_Auto_Check dlg;
	dlg.DoModal();
}

void Dlg_Auto_Check_Main::OnButJishouStandart3() 
{
	// TODO: Add your control notification handler code here
	Dlg_Select_Color dlg;
	dlg.DoModal();
}
