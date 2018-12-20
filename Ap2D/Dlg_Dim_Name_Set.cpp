// Dlg_Dim_Name_Set.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Dim_Name_Set.h"

#include "MainFrm.h"
#include "Ap2DView.h"
#include "Global.h"
#include "dir.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Dim_Name_Set dialog


Dlg_Dim_Name_Set::Dlg_Dim_Name_Set(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Dim_Name_Set::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Dim_Name_Set)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Dim_Name_Set::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Dim_Name_Set)
	DDX_Control(pDX, IDC_COMBO_TPL_NAMES, combo_tpl_names_);
	DDX_Control(pDX, IDC_LIST_SIGNS, list_signs_);
	DDX_Control(pDX, IDC_LIST_SET_INFO, list_set_name_);
	DDX_Control(pDX, IDC_LIST_NAMES, list_names_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Dim_Name_Set, CDialog)
	//{{AFX_MSG_MAP(Dlg_Dim_Name_Set)
	ON_BN_CLICKED(IDC_BUT_ADD_NAME, OnButAddName)
	ON_BN_CLICKED(IDC_BUT_SUB_NAME, OnButSubName)
	ON_BN_CLICKED(IDC_BUT_ADD_SIGN, OnButAddSign)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NAMES, OnDblclkListNames)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SIGNS, OnDblclkListSigns)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SET_INFO, OnClickListSetInfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SET_INFO, OnDblclkListSetInfo)
	ON_BN_CLICKED(IDC_BUT_TPL_DEL, OnButTplDel)
	ON_BN_CLICKED(IDC_BUT_TPL_SAVE, OnButTplSave)
	ON_CBN_SELCHANGE(IDC_COMBO_TPL_NAMES, OnSelchangeComboTplNames)
	ON_BN_CLICKED(IDC_BUT_SAVE_AS, OnButSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Dim_Name_Set message handlers
void Dlg_Dim_Name_Set::set_list_prop(CListCtrl &list_ctrl) 
{
	LONG lStyle;
	lStyle = GetWindowLong(list_ctrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(list_ctrl.m_hWnd, GWL_STYLE, lStyle);//设置style 
	DWORD dwStyle = list_ctrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	list_ctrl.SetExtendedStyle(dwStyle); //设置扩展风格
}

void Dlg_Dim_Name_Set::init_list_names() 
{

	set_list_prop(list_names_);
	list_names_.InsertColumn( 0, "Info",LVCFMT_LEFT,200);//插入列

	list_names_.InsertItem(0, "PartNo");
	list_names_.InsertItem(1, "Section");
	list_names_.InsertItem(2, "Matrail");
	list_names_.InsertItem(3, "Num");
	list_names_.InsertItem(4, "Length");
	list_names_.InsertItem(5, "Area");
	list_names_.InsertItem(6, "Weight");	
	list_names_.InsertItem(7, "Name");
	
	names_.push_back("PartNo");
	names_.push_back("Section");
	names_.push_back("Matrail");
	names_.push_back("Num");
	names_.push_back("Length");
	names_.push_back("Area");
	names_.push_back("Weight");
	names_.push_back("Name");
	
	


}
void Dlg_Dim_Name_Set::init_list_signs() 
{
	set_list_prop(list_signs_);
	list_signs_.InsertColumn( 0, "Sign",LVCFMT_LEFT,200);//插入列
	list_signs_.InsertItem(0, "*(Enter)*");
	list_signs_.InsertItem(1, "*(Space Link)*");
	list_signs_.InsertItem(1, "*(- Link)*");

	signs_.push_back("*(Enter)*");
	signs_.push_back("*(Space Link)*");
	signs_.push_back("*(- Link)*");
	
}
void Dlg_Dim_Name_Set::init_list_set_name() 
{
	set_list_prop(list_set_name_);
	list_set_name_.InsertColumn( 0, "Set",LVCFMT_LEFT,200);//插入列
	
	list_set_name_.InsertItem(0, "PartNo");
	list_set_name_.InsertItem(1, "*(Enter)*");
	list_set_name_.InsertItem(2, "Matrail");
	list_set_name_.InsertItem(3, "*(Space Link)*");
	list_set_name_.InsertItem(4, "Section");



}

CString get_file_path()
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	CString tmpdir;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径也就是当前运行程序的全路径利用方法一的解析路径的方法，即可得到程序所在路径。

	tmpdir = exeFullPath;
	tmpdir=tmpdir.Left(tmpdir.ReverseFind('\\'));	
	tmpdir = tmpdir + "\\";
	return tmpdir;
}





BOOL Dlg_Dim_Name_Set::OnInitDialog()
{
	CDialog::OnInitDialog();
	states = -1;
	// TODO: Add extra initialization here
	files_path_ = get_file_path();
	files_path_ = files_path_ + "configure" + "\\" + "dim_name_set" + "\\";
	configure_db.init_combo_by_names_list(files_path_,combo_tpl_names_);
	init_list_names();
	init_list_signs();
	init_list_set_name();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
BOOL Dlg_Dim_Name_Set::check_have_name(CString name)
{
	for(int i=0;i<names_.size();i++)
	{
		if(names_[i] == name)
			return TRUE;
	}
	return FALSE;
}
BOOL Dlg_Dim_Name_Set::check_have_sign(CString name)
{
	for(int i=0;i<signs_.size();i++)
	{
		if(signs_[i] == name)
			return TRUE;
	}
	return FALSE;
}
void Dlg_Dim_Name_Set::get_listctrl_strs(CListCtrl &list_ctrl,std::vector<CString> &items) 
{
	int count = list_ctrl.GetItemCount();
	for(int i=0;i<count;i++){	
		items.push_back(list_ctrl.GetItemText(i,0));		
	}	
}
BOOL Dlg_Dim_Name_Set::check_have_name_in_list(CListCtrl &list_ctrl,CString name)
{

	std::vector<CString> items;
	get_listctrl_strs(list_ctrl,items);
	for(int i=0;i<items.size();i++)
	{
		if(items[i] == name)
			return TRUE;
	}
	return FALSE;
}


void Dlg_Dim_Name_Set::OnButAddName() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_names_.GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{	
		int nItem = list_names_.GetNextSelectedItem(pos);		
		CString str= list_names_ .GetItemText(nItem,0);
		int p = list_set_name_.GetItemCount();
		if ( states >= 0 )
			p = states + 1;
	
		
		if(!check_have_name_in_list(list_set_name_,str))
		{
			list_set_name_.InsertItem(p,str);
		}else{
			AfxMessageBox("The item already exist.");
		}
	}
}

void Dlg_Dim_Name_Set::OnButSubName() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_set_name_.GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		int nItem = list_names_.GetNextSelectedItem(pos);	
		list_set_name_.DeleteItem(nItem);
	}
}

void Dlg_Dim_Name_Set::OnButAddSign() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_signs_.GetFirstSelectedItemPosition();
	if (pos == NULL){
	   AfxMessageBox("No sign items were selected!Please select it.\n");
	   return;
	}else{
		int nItem = list_signs_.GetNextSelectedItem(pos);		
		CString str_sign = list_signs_ .GetItemText(nItem,0);

		int p = list_set_name_.GetItemCount();

		POSITION pos = list_set_name_.GetFirstSelectedItemPosition();
		if (pos == NULL)
		   AfxMessageBox("No items were selected!\n");
		else
		{	
			int nItem = list_set_name_.GetNextSelectedItem(pos);		
			CString str_name = list_set_name_.GetItemText(nItem,0);

			if(check_have_name(str_name))
			{
				CString str_next = list_set_name_.GetItemText(nItem+1,0);
				if(check_have_sign(str_next))
				{
					AfxMessageBox("The next is the sign too,Please delete it.");
					return ;
				}else{
					list_set_name_.InsertItem(nItem+1,str_sign);

				}
			}
			else
			{
				AfxMessageBox("Please Select the Info item.");
			}

		
		}		
	}

}



void Dlg_Dim_Name_Set::OnDblclkListNames(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButAddName();
	*pResult = 0;
}

void Dlg_Dim_Name_Set::OnDblclkListSigns(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButAddSign();
	*pResult = 0;
}

void Dlg_Dim_Name_Set::get_dim_styles(CStringArray &strs)
{
	strs.Copy(select_strs_);
}

void Dlg_Dim_Name_Set::OnOK() 
{
	// TODO: Add extra validation here


	std::vector<CString> items;
	get_listctrl_strs(list_set_name_,items);	
	for(int i=0;i<items.size();i++)
	{
		select_strs_.Add(items[i]);
	}

	
	CDialog::OnOK();
}

void Dlg_Dim_Name_Set::OnClickListSetInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_set_name_.GetFirstSelectedItemPosition();
	int nitem = list_set_name_.GetNextSelectedItem(pos);
	if (nitem <= list_set_name_.GetItemCount())
		states = nitem;		
	*pResult = 0;
}

void Dlg_Dim_Name_Set::OnDblclkListSetInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButSubName();
	states = -1;
	*pResult = 0;
}

void Dlg_Dim_Name_Set::OnButTplDel() 
{
	// TODO: Add your control notification handler code here
	CString cur_text;
	GetDlgItemText(IDC_COMBO_TPL_NAMES,cur_text);
	if ( cur_text.Compare("") != 0 )
	{
		CString cur_path = files_path_ + cur_text;
		SetFileAttributes(cur_path,GetFileAttributes(cur_path) & ~FILE_ATTRIBUTE_READONLY); 
		DeleteFile(cur_path);
		configure_db.init_combo_by_names_list(files_path_,combo_tpl_names_);	
		list_set_name_.DeleteAllItems();
	}
}



void Dlg_Dim_Name_Set::OnSelchangeComboTplNames() 
{
	// TODO: Add your control notification handler code here
	CString get_text ;
	int nIndex = combo_tpl_names_.GetCurSel( );
	combo_tpl_names_.GetLBText(nIndex,get_text );
	CStringArray files;
	if ( get_text.Compare("") != 0 )
	{
		list_set_name_.DeleteAllItems();
		configure_db.open_config_file(files_path_,get_text,files);
		for (int i = 0; i < files.GetSize(); i++ )
		{
			list_set_name_.InsertItem(i,files.GetAt(i));
		}
	}


}



void 	Dlg_Dim_Name_Set::save_data_to_file(CString get_text)
{
	if ( get_text.Compare("") == 0 )
	{
		AfxMessageBox("Filename do not be allowed to be empty!");
	}
	else 
	{
		CStringArray files;
		for( int i = 0; i < list_set_name_.GetItemCount(); i++ )
		{
		//	AfxMessageBox(list_set_name_.GetItemText(i,0));
			files.Add(list_set_name_.GetItemText(i,0));
		}
		
		configure_db.save_config_file(files_path_,get_text,files);
		configure_db.init_combo_by_names_list(files_path_,combo_tpl_names_);
	}
	
}

void Dlg_Dim_Name_Set::OnButTplSave() 
{
	// TODO: Add your control notification handler code here
	afc::dir::create_floder(files_path_);
	CString get_text;
	GetDlgItemText(IDC_COMBO_TPL_NAMES,get_text);

	save_data_to_file(get_text);
	combo_tpl_names_.SetCurSel(combo_tpl_names_.FindString( -1, get_text ));	
	//SetDlgItemText(IDC_COMBO_TPL_NAMES,"");
	
	CStringArray files;
	if ( get_text.Compare("") != 0 )
	{
		list_set_name_.DeleteAllItems();
		configure_db.open_config_file(files_path_,get_text,files);
		for (int i = 0; i < files.GetSize(); i++ )
		{
			list_set_name_.InsertItem(i,files.GetAt(i));
		}
	}
}

void Dlg_Dim_Name_Set::OnButSaveAs() 
{
	// TODO: Add your control notification handler code here
	CString get_text;
	GetDlgItemText(IDC_EDIT_TPL_NAME,get_text);

	CString cur_sel_text ;
	GetDlgItemText(IDC_COMBO_TPL_NAMES,cur_sel_text);

	if ( get_text.Compare("") == 0 )
	{
		AfxMessageBox("Filename do not be allowed to be empty!");
	}
	else
	{
		save_data_to_file(get_text);

		combo_tpl_names_.SetCurSel(combo_tpl_names_.FindString( -1, cur_sel_text ));	
		SetDlgItemText(IDC_EDIT_TPL_NAME,"");
		CStringArray files;
		if ( cur_sel_text.Compare("") != 0 )
		{
			list_set_name_.DeleteAllItems();
			configure_db.open_config_file(files_path_,cur_sel_text,files);
			for (int i = 0; i < files.GetSize(); i++ )
			{
				list_set_name_.InsertItem(i,files.GetAt(i));
			}
		}

	}
	
}
