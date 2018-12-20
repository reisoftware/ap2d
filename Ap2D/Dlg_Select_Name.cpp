// Dlg_Select_Name.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Select_Name.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Name dialog


Dlg_Select_Name::Dlg_Select_Name(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Select_Name::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Select_Name)
	name_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Select_Name::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Select_Name)
	DDX_Control(pDX, IDC_LIST_NAMES, names_);
	DDX_Text(pDX, IDC_EDIT_NAME, name_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Select_Name, CDialog)
	//{{AFX_MSG_MAP(Dlg_Select_Name)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NAMES, OnClickListNames)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NAMES, OnDblclkListNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Name message handlers
void Dlg_Select_Name::set_names(const CStringArray& names)
{
	names_ary_.Copy(names);
}
BOOL Dlg_Select_Name::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	DWORD dwStyle = names_.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	names_.SetExtendedStyle(dwStyle); //设置扩展风格

	names_.InsertColumn( 0, "ID",LVCFMT_LEFT,400);//插入列
	int ncount = names_ary_.GetSize();
	for(int i=0;i<ncount; i++)
	{
	//	int nIndex = names_.GetItemCount();
		names_.InsertItem(i,names_ary_[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
CString Dlg_Select_Name::get_name()
{
	return str_name_;
}

void Dlg_Select_Name::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(name_ == ""){
		MessageBox("Please input name.");
		return;
	}
	str_name_ = name_;
	CDialog::OnOK();
}

void Dlg_Select_Name::OnClickListNames(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = names_.GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{	
		int nItem = names_.GetNextSelectedItem(pos);		
		CString str= names_ .GetItemText(nItem,0);
		name_ = str;
		UpdateData(FALSE);
	}	
	*pResult = 0;
}




void Dlg_Select_Name::deal_find_str_show(CString str)
{

	int count = names_.GetItemCount();
	int strlen = str.GetLength();
	int states = 0;
	for (int i = 0;i < count;i++)
	{
	
		CString newstr = names_.GetItemText(i,0);
		CString findstr =  newstr.Left(strlen);
		if ((findstr.GetLength() == newstr.GetLength() ) && ( str.CompareNoCase( findstr ) == 0  ))
		{
			states = 1;
			break;
		}
		if ( str.CompareNoCase( findstr ) == 0  )
		{
			states = 1;
			names_.EnsureVisible(0, FALSE);//用来初始化跳转 为了使跳转时候将该行置顶
			names_.SetHotItem(i); //设置热点 表现形式是该item的文本变色
			POSITION pos = names_.GetFirstSelectedItemPosition();
			int nItem = names_.GetNextSelectedItem(pos);
			int pageitemnums = names_.GetCountPerPage();//得到每页的item个数
			int mod = nItem%pageitemnums;
			if (mod != 0)
				names_.EnsureVisible(i + pageitemnums - 1, FALSE);
			else
				names_.EnsureVisible(i, FALSE);
		//	UINT flag = LVIS_SELECTED|LVIS_FOCUSED;
		//	lv.state = LVIS_DROPHILITED; 
		//	lv.state = LVIS_SELECTED|LVIS_FOCUSED;
		//	listname_.SetItemState(Curpos, ~LVIS_DROPHILITED, LVIS_DROPHILITED);
			
		//	listname_.SetItemState(Curpos, flag,flag);
			break;
		}
	}
	if ( states == 0 && str != "" )
		AfxMessageBox("Not having");
	
}

void Dlg_Select_Name::OnChangeEditName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_EDIT_NAME,str);
	if ( str.GetLength() != 0 )	
		deal_find_str_show(str);
	else
		names_.EnsureVisible(0, FALSE);
}

void Dlg_Select_Name::OnDblclkListNames(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnOK();
	*pResult = 0;
}
