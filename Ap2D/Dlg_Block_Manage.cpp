// Dlg_Block_Manage.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Block_Manage.h"

#include "Mgr_File.h"
#include "DB_View.h"
#include "Mgr_lua.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Block_Manage dialog


Dlg_Block_Manage::Dlg_Block_Manage(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Block_Manage::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Block_Manage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Block_Manage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Block_Manage)
	DDX_Control(pDX, IDC_LIST_BLOCK_NAMES, list_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Block_Manage, CDialog)
	//{{AFX_MSG_MAP(Dlg_Block_Manage)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BLOCK_NAMES, OnDblclkListBlockNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Block_Manage message handlers


BOOL Dlg_Block_Manage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	std::string exe = exe_path()+"blk\\";
	CStringArray files;
	get_files_in_path(exe.c_str(),"blk",files);
	for(int i=0;i<files.GetSize();i++){
		list_.InsertItem(i, files[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void Dlg_Block_Manage::get_ents(std::vector<dlhml::Entity*> &ents) 
{
	std::copy(ents_.begin(), ents_.end(), std::back_inserter(ents));
	
}

void Dlg_Block_Manage::OnOK() 
{
	// TODO: Add extra validation here
	POSITION pos = list_.GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{	
		int nItem = list_.GetNextSelectedItem(pos);		
		CString str= list_ .GetItemText(nItem,0);

		
		std::string exe = exe_path()+"blk\\";
		CString file_blk = exe.c_str()+str;

		open_lua(file_blk.GetBuffer(0),DB_View::instance()->cur_view()->scene()->database());
		DB_View::instance()->cur_view()->scene()->database()->get_ents_by_luafile(ents_);
	}
	CDialog::OnOK();
}

void Dlg_Block_Manage::OnDblclkListBlockNames(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnOK();
	*pResult = 0;
}
