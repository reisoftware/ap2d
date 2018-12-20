// Dlg_Project_Paths_Save.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Project_Paths_Save.h"
#include "Mgr_File.h"


#include<shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Project_Paths_Save dialog


Dlg_Project_Paths_Save::Dlg_Project_Paths_Save(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Project_Paths_Save::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Project_Paths_Save)
	edit_path_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Project_Paths_Save::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Project_Paths_Save)
	DDX_Control(pDX, IDC_LIST_PRO_PAHTS_SAVE, list_save_paths_);
	DDX_Text(pDX, IDC_EDIT_PRO_PATH, edit_path_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Project_Paths_Save, CDialog)
	//{{AFX_MSG_MAP(Dlg_Project_Paths_Save)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PRO_PAHTS_SAVE, OnDblclkListProPahtsSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PRO_PAHTS_SAVE, OnClickListProPahtsSave)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PATH, OnButtonOpenPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Project_Paths_Save message handlers

void Dlg_Project_Paths_Save::init_list_style()
{

	CRect rc;
  CWnd *pWnd = GetDlgItem(IDC_LIST_PRO_PAHTS_SAVE);//参数为控件ID
  pWnd->GetClientRect(&rc);//rc为控件的大小。
	int nWid = rc.Width();//获得控件宽度

	list_save_paths_.InsertColumn(0,"",LVCFMT_LEFT,(float)nWid);

	DWORD dwStyle = list_save_paths_.GetExtendedStyle();

	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	list_save_paths_.SetExtendedStyle(dwStyle); //设置扩展风格
}

void Dlg_Project_Paths_Save::save_to_file()
{
	CStdioFile file;
	std::string path =  exe_path();
	CString all_path = path.c_str() + save_data_ifo_file_name_;
	if (!file.Open(all_path,CFile::modeCreate|CFile::modeWrite | CFile::typeText)){
		#ifdef _DEBUG
     afxDump << "Unable to open file" << "\n";
		#endif
		exit( 1 );
	}
	for (int i = 0 ;i < paths_.GetSize() ; i++ ){
		file.WriteString(paths_[i]);
		file.WriteString("\n");
	}
	file.Close();
}

void Dlg_Project_Paths_Save::show_data()
{
	list_save_paths_.DeleteAllItems();
	int nums = 0;
	CString temp_str = "";
	for (int i = 0 ; i < paths_.GetSize() ; i++ ){
		if (paths_[i].Find("text_title = ") <  0 ){
			list_save_paths_.InsertItem(nums,"");
			list_save_paths_.SetItemText(nums,0,paths_[i]);
			nums++;
		}
		else
		{
			int pos = paths_[i].ReverseFind( '=' );
			temp_str = paths_[i].Right(paths_[i].GetLength() - pos - 1);
			temp_str.TrimLeft();
			SetDlgItemText(IDC_EDIT_PRO_PATH,temp_str);
		}
	}
	if ( temp_str.Compare("") != 0 ){
		for ( i= 0 ; i < list_save_paths_.GetItemCount() ; i++ ){
			if (list_save_paths_.GetItemText(i,0).Compare(temp_str) == 0){
				list_save_paths_.SetItemState( i, LVNI_SELECTED|LVNI_FOCUSED, LVNI_SELECTED|LVNI_FOCUSED);
				break;
			}
		}
	}

}

void Dlg_Project_Paths_Save::get_file_Data_show()
{
	paths_.RemoveAll();
	std::string path =  exe_path();
	save_data_ifo_file_name_ = "Project_Paths_Save_File.txt";
	CString all_path = path.c_str() + save_data_ifo_file_name_;
	CStdioFile file;
	if (!file.Open(all_path,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead | CFile::typeText)){
		#ifdef _DEBUG
     afxDump << "Unable to open file" << "\n";
		#endif
		exit( 1 );
	}
	CString temp_str;
	while(file.ReadString(temp_str)){
		paths_.Add(temp_str);
	}
	file.Close();
	show_data();
}

BOOL Dlg_Project_Paths_Save::OnInitDialog() 
{
	CDialog::OnInitDialog();
	cur_sel_path_ = "";
	init_list_style();
	get_file_Data_show();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void Dlg_Project_Paths_Save::OnDblclkListProPahtsSave(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnOK();
	*pResult = 0;
}

void Dlg_Project_Paths_Save::OnClickListProPahtsSave(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_save_paths_.GetFirstSelectedItemPosition( );
	int nitem = list_save_paths_.GetNextSelectedItem(pos);
	CString sel_text  = list_save_paths_.GetItemText(nitem,0);
	if ( sel_text.Compare("") != 0 )
		SetDlgItemText(IDC_EDIT_PRO_PATH,sel_text);
	*pResult = 0;
}

BOOL Dlg_Project_Paths_Save::is_have_same(CString temp_str)
{
	for (int i = 0 ; i < paths_.GetSize() ; i++ ){
		CString cur_str = paths_[i];
		if ( cur_str.Compare(temp_str) == 0 )
			return true;
	}
	return false;
}

void Dlg_Project_Paths_Save::OnButtonOpenPath() 
{
	// TODO: Add your control notification handler code here
	std::string path = select_dir();
	CString temp_str = path.c_str();
	if (temp_str.Compare("") != 0){
		if (!is_have_same(temp_str)){
			paths_.Add(temp_str);
			show_data();
			save_to_file();
			SetDlgItemText(IDC_EDIT_PRO_PATH,temp_str);
		}
	}

}

void Dlg_Project_Paths_Save::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItemText(IDC_EDIT_PRO_PATH,cur_sel_path_);
	if (PathFileExists(cur_sel_path_)){	
		int states=0;
		for (int i = 0 ; i < paths_.GetSize() ; i++ ){
			if (paths_[i].Find("=") >= 0 ){
				paths_[i] = "text_title = " + cur_sel_path_;
				states = 1;
			}
		}
		if (states == 0){
			CString temp_str = "text_title = " + cur_sel_path_;
			paths_.Add(temp_str);
		}
		save_to_file();
		CDialog::OnOK();
	}
	else{
		AfxMessageBox("The path has been deleted ! Please selected again!");
		for (int i = 0 ; i < paths_.GetSize() ; i++ ){
			if (paths_[i].Find("=") < 0 ){
				if (paths_[i].Compare(cur_sel_path_) == 0 ){
					paths_.RemoveAt(i);
					show_data();
					SetDlgItemText(IDC_EDIT_PRO_PATH,"");
				}
			}
		}
	}
	
}

void Dlg_Project_Paths_Save::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

CString Dlg_Project_Paths_Save::get_dir()
{
	return cur_sel_path_;
}


