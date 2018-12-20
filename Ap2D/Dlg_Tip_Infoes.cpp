// Dlg_Tip_Infoes.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Tip_Infoes.h"

#include "dir.h"
#include "Mgr_File.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Tip_Infoes dialog


Dlg_Tip_Infoes::Dlg_Tip_Infoes(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Tip_Infoes::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Tip_Infoes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Tip_Infoes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Tip_Infoes)
	DDX_Control(pDX, IDC_LIST_TIPS, list_tip_datas_);
	DDX_Control(pDX, IDC_EDIT_TIP, edit_tip_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Tip_Infoes, CDialog)
	//{{AFX_MSG_MAP(Dlg_Tip_Infoes)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TIPS, OnClickListTips)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TIPS, OnDblclkListTips)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Tip_Infoes message handlers


void Dlg_Tip_Infoes::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	CString cur_text;
	edit_tip_.GetWindowText(cur_text);
	int status = 0;
	if ( cur_text.Compare("") != 0 ){
		for (int i = 0;i < tips_db_.GetSize() ; i++ ){
			if ( cur_text.Compare(tips_db_[i]) == 0 )
				status = 1;
		}
		if ( status == 0 ){
			tips_db_.Add(cur_text);
			save_db();
			int itemcounts = list_tip_datas_.GetItemCount();
			list_tip_datas_.InsertItem(itemcounts,"");
			list_tip_datas_.SetItemText(itemcounts,0,cur_text);
			edit_tip_.SetWindowText("");
		}
		else{
			AfxMessageBox("Text has been exist ! ");
			edit_tip_.SetWindowText("");
		}
		
		
	}
	else
		AfxMessageBox("Content can not be empty !");
	
}

void Dlg_Tip_Infoes::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	CString tip_txt;
	edit_tip_.GetWindowText(tip_txt);
	if ( tip_txt.Compare("") != 0 ){
		edit_tip_.SetWindowText("");
		for (int i = 0 ; i < list_tip_datas_.GetItemCount() ; i++ ){
			if ( tip_txt.Compare(list_tip_datas_.GetItemText(i,0)) == 0 ){
				list_tip_datas_.DeleteItem( i );
				break;
			}
		}
		for (int j = 0 ; j < tips_db_.GetSize() ; j++ ){
			if ( tip_txt.Compare(tips_db_[j]) == 0 ){
				tips_db_.RemoveAt(j,1);	
				save_db();
				break;
			}
		}	
	}
	
}

void Dlg_Tip_Infoes::OnClickListTips(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	POSITION pos = list_tip_datas_.GetFirstSelectedItemPosition();
	int nItem = list_tip_datas_.GetNextSelectedItem(pos);
	CString sel_txt = list_tip_datas_.GetItemText(nItem,0);
	if ( sel_txt.Compare("") != 0 ){
		edit_tip_.SetWindowText(sel_txt);
		cur_txt_ = sel_txt;
	}
		
	*pResult = 0;
}

void Dlg_Tip_Infoes::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

CString Dlg_Tip_Infoes::get_files_path()
{
	CString	files_path = exe_path().c_str();
	files_path = files_path + "configure" + "\\";
	return files_path;
}

void Dlg_Tip_Infoes::init_dlg_type()
{
	CRect rc;
  CWnd *pWnd = GetDlgItem(IDC_LIST_TIPS);//参数为控件ID
  pWnd->GetClientRect(&rc);//rc为控件的大小。
	int nWid = rc.Width();//获得控件宽度
	DWORD dwStyle1 = list_tip_datas_.GetExtendedStyle();
  dwStyle1 |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
  dwStyle1 |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
//	dwStyle1 |= LVS_SINGLESEL;
  list_tip_datas_.SetExtendedStyle(dwStyle1); //设置扩展风格
	list_tip_datas_.InsertColumn(0,"",LVCFMT_LEFT,nWid);	
}

void Dlg_Tip_Infoes::init_db()
{
	CStdioFile file;
	if (!file.Open(file_path_,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead | CFile::typeText)){
		#ifdef _DEBUG
      afxDump << "Unable to open file" << "\n";
   #endif
   exit( 1 );
	}
	CString per_line;
	while ( file.ReadString(per_line) ){
		if ( per_line.Compare("") != 0 )
			tips_db_.Add(per_line);
	}
	file.Close();
}


void Dlg_Tip_Infoes::init_dlg_show()
{
	for (int i = 0 ;i < tips_db_.GetSize() ; i++ ){
		list_tip_datas_.InsertItem(i,"");
		list_tip_datas_.SetItemText(i,0,tips_db_[i]);
	}
	
}

void Dlg_Tip_Infoes::init()
{
	cur_txt_ = "";
	file_path_ = file_path_ + "tip_datas.txt";
	tips_db_.RemoveAll();
	list_tip_datas_.DeleteAllItems( );
	init_dlg_type();
	init_db();
	init_dlg_show();
}
BOOL Dlg_Tip_Infoes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	file_path_ = get_files_path();
	afc::dir::create_floder(file_path_);
	// TODO: Add extra initialization here
	init();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Tip_Infoes::save_db()
{
	CStdioFile file;
	if (!file.Open(file_path_,CFile::modeCreate | CFile::modeWrite | CFile::typeText)){
		#ifdef _DEBUG
      afxDump << "Unable to open file" << "\n";
   #endif
   exit( 1 );
	}
	CString per_line;
	for (int i = 0 ; i < tips_db_.GetSize() ; i++ ){
		file.WriteString(tips_db_[i]);
		file.WriteString("\n");
	}
	file.Close();
}

CString Dlg_Tip_Infoes::get_str()
{

	return cur_txt_;
}

void Dlg_Tip_Infoes::OnDblclkListTips(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnClickListTips(pNMHDR,pResult) ;
	OnOK() ;
	*pResult = 0;
}
