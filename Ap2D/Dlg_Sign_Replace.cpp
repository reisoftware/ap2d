// Dlg_Sign_Replace.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Sign_Replace.h"
#include "DB_Text_Replace.h"
#include "Model_DB.h"
#include "Replace_String.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Sign_Replace dialog


Dlg_Sign_Replace::Dlg_Sign_Replace(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Sign_Replace::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Sign_Replace)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Sign_Replace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Sign_Replace)
	DDX_Control(pDX, IDC_COMBO_TEXT, combo_text_);
	DDX_Control(pDX, IDC_LIST_SIGNS, list_signs_);
	DDX_Control(pDX, IDC_COMBO_SIGNS, combo_signs_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Sign_Replace, CDialog)
	//{{AFX_MSG_MAP(Dlg_Sign_Replace)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(ID_BUT_REPLACE, OnButReplace)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SIGNS, OnClickListSigns)
	ON_BN_CLICKED(IDC_BUT_SAVE_PATH, OnButSavePath)
	ON_BN_CLICKED(IDC_BUT_LOAD_PATH, OnButLoadPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Sign_Replace message handlers


void  Dlg_Sign_Replace::set_DropDownSize(CComboBox& box, UINT LinesToDisplay)
/*-------------------------------------------------------------------------- 
* Purpose: Set the proper number of lines in a drop-down list or 
* combo box. 
* Description: Resizes the combo box window to fit the proper number 
* of lines. The window must exist before calling this function. 
* This function should be called when the combo box is created, and when 
* the font of the combo box changes. (e.g. WM_SETTINGCHANGE) 
* Testing needed: 
* Are there cases where SM_CYBORDER should be used instead of SM_CYEDGE? 
* owner-draw variable height combo box 
* Subclassed combo box with horizontal scroll-bar 
* Returns: nothing 
* Author: KTM 
*--------------------------------------------------------------------------*/ 
{ 
    ASSERT(IsWindow(box)); // Window must exist or SetWindowPos won't work 

    CRect cbSize; // current size of combo box 
    int Height; // new height for drop-down portion of combo box 

    box.GetClientRect(cbSize); 
    Height = box.GetItemHeight(-1); // start with size of the edit-box portion 
    Height += box.GetItemHeight(0) * LinesToDisplay; // add height of lines of text 

    // Note: The use of SM_CYEDGE assumes that we're using Windows '95 
    // Now add on the height of the border of the edit box 
    Height += GetSystemMetrics(SM_CYEDGE) * 2; // top & bottom edges 

    // The height of the border of the drop-down box 
    Height += GetSystemMetrics(SM_CYEDGE) * 2; // top & bottom edges 

    // now set the size of the window 
    box.SetWindowPos(NULL, // not relative to any other windows 
    0, 0, // TopLeft corner doesn't change 
    cbSize.right, Height, // existing width, new height 
    SWP_NOMOVE | SWP_NOZORDER // don't move box or change z-ordering. 
    ); 
}


void Dlg_Sign_Replace::init_combo_data()
{
	combo_signs_.InsertString(0,"Circle");
	combo_signs_.InsertString(1,"Hide");
	combo_signs_.InsertString(2,"Rect");
	//combo_signs_.InsertString(2,"Cross");
	//combo_signs_.InsertString(2,"Triangle");
	combo_signs_.SetCurSel(0);

}


static CString get_file_path()
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	CString tmpdir;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径也就是当前运行程序的全路径利用方法一的解析路径的方法，即可得到程序所在路径。

	tmpdir = exeFullPath;
	tmpdir=tmpdir.Left(tmpdir.ReverseFind('\\'));	
	return tmpdir;
}

void Dlg_Sign_Replace::init_list()
{

	CRect rc;
  CWnd *pWnd = GetDlgItem(IDC_LIST_SIGNS);//参数为控件ID
  pWnd->GetClientRect(&rc);//rc为控件的大小。
	int nWid = rc.Width();//获得控件宽度
	DWORD dwStyle1 = list_signs_.GetExtendedStyle();
  dwStyle1 |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
  dwStyle1 |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
//	dwStyle1 |= LVS_SINGLESEL;
  list_signs_.SetExtendedStyle(dwStyle1); //设置扩展风格
	list_signs_.InsertColumn(0,"Text",LVCFMT_LEFT,(float)nWid/4);
	list_signs_.InsertColumn(1,"Style",LVCFMT_LEFT,(float)nWid/4);
	list_signs_.InsertColumn(2,"Sign",LVCFMT_LEFT,(float)nWid/4);
	list_signs_.InsertColumn(3,"Postfix",LVCFMT_LEFT,(float)nWid/4);

	CString cur_path = get_file_path();
	file_all_path = cur_path + "\\" + "signs_replace.txt";		
}	


void Dlg_Sign_Replace::update_db()
{
	list_signs_.DeleteAllItems();
	std::vector<Text_Replace> db = DB_Text_Replace::instance()->retrun_db();
	for (int i = 0 ; i < db.size()  ; i++ )
	{
			list_signs_.InsertItem(i,"");
			list_signs_.SetItemText(i, 0,db[i].txt_);
			list_signs_.SetItemText(i, 1,db[i].replace_);
			list_signs_.SetItemText(i, 2,db[i].char_);
			list_signs_.SetItemText(i, 3,db[i].postfix_);
	}
}


void Dlg_Sign_Replace::init_combo_text()
{
	CString str = get_file_path();
	Model_DB::instance()->open(str+"\\"+"configure\\partlist.txt");
	Parts db_text_ = Model_DB::instance()->retrun_model_db();

	Parts temp_parts;
	int states;
	int add_i = 0;
	for(int i = 0 ; i < db_text_.size(); i++ )
	{
		states = 0;
		for (int j = 0; j < temp_parts.size(); j++ )
		{
			if ( temp_parts[j].matrial_.Compare(db_text_[i].matrial_) == 0 )
			{
				states = 1;
			}

		}
		if ( states != 1 )
		{
			temp_parts.push_back(db_text_[i]);
			combo_text_.InsertString(add_i,db_text_[i].matrial_);
			add_i++;
		}
	}

	combo_text_.SetCurSel(0);

}

BOOL Dlg_Sign_Replace::OnInitDialog() 
{
	
	CDialog::OnInitDialog();
	set_DropDownSize(combo_signs_, 5);
	init_combo_data();
	init_combo_text();
	init_list();
	DB_Text_Replace::instance()->open(file_all_path);
	update_db();
	
	SetDlgItemText(IDC_EDIT_FILE_PATH,get_file_path());



	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*

*/
void Dlg_Sign_Replace::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	CString text;
	GetDlgItemText(IDC_COMBO_TEXT,text);
	if ( text.Compare("") == 0 )
		AfxMessageBox("Text can not be empty!");
	else
	{
		
		Text_Replace val;
		val.txt_ = text;
		GetDlgItemText(IDC_EDIT_CHAR,text);
		
		//可能为空
		val.char_ = text;
		GetDlgItemText(IDC_COMBO_SIGNS,	val.replace_);
		GetDlgItemText(IDC_EDIT_POSTFIX,	val.postfix_);
		DB_Text_Replace::instance()->add(val);
		update_db();
	}
	
}
void Dlg_Sign_Replace::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	POSITION pos  = list_signs_.GetFirstSelectedItemPosition();
	int nItem = list_signs_.GetNextSelectedItem(pos);
	if ( nItem >= 0 )
	{
		DB_Text_Replace::instance()->del(nItem);
		update_db();
	}	
}


void Dlg_Sign_Replace::OnButtonEdit() 
{
	// TODO: Add your control notification handler code here
	POSITION pos  = list_signs_.GetFirstSelectedItemPosition();
	int nItem = list_signs_.GetNextSelectedItem(pos);
	if ( nItem >= 0 )
	{
		Text_Replace val;
		GetDlgItemText(IDC_COMBO_TEXT,val.txt_);
		GetDlgItemText(IDC_COMBO_SIGNS,	val.replace_);
		GetDlgItemText(IDC_EDIT_CHAR,val.char_);
		GetDlgItemText(IDC_EDIT_POSTFIX,	val.postfix_);

		//修改list中的值	
		list_signs_.SetItemText(nItem, 0,val.txt_);
		list_signs_.SetItemText(nItem, 1,val.replace_);
		list_signs_.SetItemText(nItem, 2,val.char_);
		list_signs_.SetItemText(nItem, 3,val.postfix_);

		//修改数据库中的值
		DB_Text_Replace::instance()->edit(val);
		update_db();
	}
	OnButtonDel();
}

void Dlg_Sign_Replace::OnOK() 
{
	// TODO: Add extra validation here
	DB_Text_Replace::instance()->save(file_all_path);
	CDialog::OnOK();
}

void Dlg_Sign_Replace::OnButReplace() 
{
	// TODO: Add your control notification handler code here
	Replace_String rep;
	for (int i= 0 ; i < list_signs_.GetItemCount() ; i++ ){
		CString name = list_signs_.GetItemText(i,0);
		CString style = list_signs_.GetItemText(i,1);
		CString sign = list_signs_.GetItemText(i,2);
		CString postfix = list_signs_.GetItemText(i,3);
		
		rep.replace(name,style,sign,postfix);
 

	}

	
}

void Dlg_Sign_Replace::OnClickListSigns(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_signs_.GetFirstSelectedItemPosition();
	int nItem = list_signs_.GetNextSelectedItem(pos);

	CString name = list_signs_.GetItemText(nItem,0);
	CString style = list_signs_.GetItemText(nItem,1);
	CString sign = list_signs_.GetItemText(nItem,2);
	CString postfix = list_signs_.GetItemText(nItem,3);
	
	combo_text_.SetCurSel(combo_text_.FindString( -1, name ));	
	combo_signs_.SetCurSel(combo_signs_.FindString( -1, style ));	
		
	SetDlgItemText(IDC_EDIT_CHAR,list_signs_.GetItemText(nItem,2 ));
	SetDlgItemText(IDC_EDIT_POSTFIX,list_signs_.GetItemText(nItem,3));

	
	*pResult = 0;
}

void Dlg_Sign_Replace::OnButSavePath() 
{
	// TODO: Add your control notification handler code here
	CString strFile,strName;
	static char szFilter[] = "Txt file format (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(FALSE, _T(".txt"),get_file_path(), OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL);
	dlg.m_ofn.lpstrTitle = "Save Matiral Replace File";
	if(dlg.DoModal()== IDOK)
	{
		strFile=dlg.GetPathName();
		
		SetDlgItemText(IDC_EDIT_FILE_PATH,strFile);

		DB_Text_Replace::instance()->save(strFile);

	}
	
	
}

void Dlg_Sign_Replace::OnButLoadPath() 
{
	// TODO: Add your control notification handler code here
	CString strFile,strName;
	static char szFilter[] = "Txt file format(*.txt) |*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL );
	dlg.m_ofn.lpstrTitle = "Open Matiral Replace File";
	if(dlg.DoModal()== IDOK){
		strFile=dlg.GetPathName();
		SetDlgItemText(IDC_EDIT_FILE_PATH,strFile);
		DB_Text_Replace::instance()->open(strFile);
		update_db();

	}
	
}
