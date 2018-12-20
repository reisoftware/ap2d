// Dlg_Replace_Material.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Replace_Material.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Replace_Material dialog


Dlg_Replace_Material::Dlg_Replace_Material(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Replace_Material::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Replace_Material)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Replace_Material::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Replace_Material)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Replace_Material, CDialog)
	//{{AFX_MSG_MAP(Dlg_Replace_Material)
	ON_BN_CLICKED(ID_BUT_REPLACE, OnButReplace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Replace_Material message handlers

void Dlg_Replace_Material::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void Dlg_Replace_Material::OnButReplace() 
{
	// TODO: Add your control notification handler code here
	
}
