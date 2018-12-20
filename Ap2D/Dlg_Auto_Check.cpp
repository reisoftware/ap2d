// Dlg_Auto_Check.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Auto_Check.h"
#include "DB_Jishou.h"
#include "Dlg_Jishou_add.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Auto_Check dialog


Dlg_Auto_Check::Dlg_Auto_Check(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Auto_Check::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Auto_Check)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Auto_Check::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Auto_Check)
	DDX_Control(pDX, IDC_LIST_DATA, list_add_data_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Auto_Check, CDialog)
	//{{AFX_MSG_MAP(Dlg_Auto_Check)
	ON_BN_CLICKED(ID_BUT_ADD, OnButAdd)
	ON_BN_CLICKED(IDEDIT, OnEdit)
	ON_BN_CLICKED(ID_DELETE, OnDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DATA, OnClickListData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Auto_Check message handlers




void 	Dlg_Auto_Check::init_dlg_type()
{
	CRect rc;
  CWnd *pWnd = GetDlgItem(IDC_LIST_DATA);//参数为控件ID
  pWnd->GetClientRect(&rc);//rc为控件的大小。
	int nWid = rc.Width();//获得控件宽度
	DWORD dwStyle1 = list_add_data_.GetExtendedStyle();
  dwStyle1 |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
  dwStyle1 |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
//	dwStyle1 |= LVS_SINGLESEL;
  list_add_data_.SetExtendedStyle(dwStyle1); //设置扩展风格
	list_add_data_.InsertColumn(0,"Assembley No",LVCFMT_LEFT,(float)nWid/3);
	list_add_data_.InsertColumn(1,"Left Joint",LVCFMT_LEFT,(float)nWid/3);	
	list_add_data_.InsertColumn(2,"Right Joint",LVCFMT_LEFT,(float)nWid/3);	
}

void Dlg_Auto_Check::init_data()
{
	DB_Jishou::instance()->init_data();
	update_data();
}

BOOL Dlg_Auto_Check::OnInitDialog() 
{
	CDialog::OnInitDialog();
	init_dlg_type();
	init_data();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void 	Dlg_Auto_Check::update_data()
{
	list_add_data_.DeleteAllItems();
	JS jishous = DB_Jishou::instance()->return_js_db();
	for (int i = 0 ; i < jishous.size() ; i++ ){
		list_add_data_.InsertItem(i,"");
		list_add_data_.SetItemText(i,0,jishous[i].ass_no_ );
		list_add_data_.SetItemText(i,1,jishous[i].l_joint_ );
		list_add_data_.SetItemText(i,2,jishous[i].r_joint_ );
	}
}


void Dlg_Auto_Check::OnButAdd() 
{
	// TODO: Add your control notification handler code here
	Dlg_Jishou_add dlg;
	Ji1Shou cur_data;
	DB_Jishou::instance()->set_sel_data(cur_data,false);
	if ( dlg.DoModal() == IDOK ){
		DB_Jishou::instance()->save_cur_file();
		update_data();
		
	}

}



void Dlg_Auto_Check::OnEdit() 
{
	// TODO: Add your control notification handler code here
		
		POSITION pos = list_add_data_.GetFirstSelectedItemPosition( ) ;
		int nitem = list_add_data_.GetNextSelectedItem(pos);
		if ( nitem >= list_add_data_.GetItemCount() || nitem < 0 ) {
			AfxMessageBox("Please select a line data for editing !");
		}else
		{
			Dlg_Jishou_add dlg;
			Ji1Shou cur_data;
			cur_data.ass_no_ = list_add_data_.GetItemText(nitem,0);
			cur_data.l_joint_ = list_add_data_.GetItemText(nitem,1);
			cur_data.r_joint_ = list_add_data_.GetItemText(nitem,2);
			DB_Jishou::instance()->set_sel_data(cur_data,true);
			if ( dlg.DoModal() == IDOK ){
			//	DB_Jishou::instance()->change(cur_data);
				DB_Jishou::instance()->save_cur_file();
				update_data();
			
			}

		}
		
}

void Dlg_Auto_Check::OnDelete() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_add_data_.GetFirstSelectedItemPosition( ) ;
	int nitem = list_add_data_.GetNextSelectedItem(pos);
	if ( nitem >= list_add_data_.GetItemCount() || nitem < 0 ) 
		AfxMessageBox("Please select a line data for deleting !");
	else
	{
		Ji1Shou cur_data;
		cur_data.ass_no_ = list_add_data_.GetItemText(nitem,0);
		cur_data.l_joint_ = list_add_data_.GetItemText(nitem,1);
		cur_data.r_joint_ = list_add_data_.GetItemText(nitem,2);
		DB_Jishou::instance()->del_iter(cur_data);
		DB_Jishou::instance()->save_cur_file();
		update_data();
	}
	
}

void Dlg_Auto_Check::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void Dlg_Auto_Check::OnClickListData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
