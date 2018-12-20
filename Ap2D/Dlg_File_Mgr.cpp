// Dlg_File_Mgr.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_File_Mgr.h"
#include "dir.h"
#include "Mgr_File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_File_Mgr dialog


Dlg_File_Mgr::Dlg_File_Mgr(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_File_Mgr::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_File_Mgr)
	edit_copy_to_ = _T("");
	path_ = _T("");
	edit_postfix_ = _T("");
	delete_str_ = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	i_no_ = 0;
	i_data_= 0;
	i_postfix_= 0;
	i_copy_to_= 0;
	i_delete_= 0;
}


void Dlg_File_Mgr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_File_Mgr)
	DDX_Text(pDX, IDC_EDIT_COPY_TO, edit_copy_to_);
	DDX_Text(pDX, IDC_EDIT_PATH, path_);
	DDX_Text(pDX, IDC_EDIT_POSTFIX, edit_postfix_);
	DDX_Text(pDX, IDC_EDIT_DELETE, delete_str_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_File_Mgr, CDialog)
	//{{AFX_MSG_MAP(Dlg_File_Mgr)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_PATH, OnButPath)
	ON_BN_CLICKED(IDC_BUT_COPY_TO_PATH, OnButCopyToPath)
	ON_BN_CLICKED(IDC_CHECK_COPY_TO, OnCheckCopyTo)
	ON_BN_CLICKED(IDC_RADIO_DATA, OnRadioData)
	ON_BN_CLICKED(IDC_RADIO_PREFIX, OnRadioPrefix)
	ON_BN_CLICKED(IDC_RADIO_NO, OnRadioNo)
	ON_BN_CLICKED(IDC_BUT_DELETE, OnButDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_File_Mgr message handlers
void Dlg_File_Mgr::load_status()
{
	std::string ini_file = afc::dir::exe_path()+"setting.ini";
	std::string val = read(ini_file.c_str(), "Path","Path");
	path_ = read(ini_file.c_str(), "Path","Path").c_str();
	edit_copy_to_ = read(ini_file.c_str(), "Copy To Path","Copy To Path").c_str();
	edit_postfix_ = read(ini_file.c_str(), "Postfix","Postfix").c_str();
	delete_str_ = read(ini_file.c_str(), "Delete","Delete").c_str();

	int check = atoi(read(ini_file.c_str(), "i_no_","i_no_").c_str());
	((CButton *)GetDlgItem(IDC_RADIO_NO))->SetCheck(check);//
	i_no_ = check;

	check = atoi(read(ini_file.c_str(), "i_data_","i_data_").c_str());
	((CButton *)GetDlgItem(IDC_RADIO_DATA))->SetCheck(check);//
	i_data_ = check;

	check = atoi(read(ini_file.c_str(), "i_postfix_","i_postfix_").c_str());
	((CButton *)GetDlgItem(IDC_RADIO_PREFIX))->SetCheck(check);//
	GetDlgItem(IDC_EDIT_POSTFIX)->EnableWindow(check);
	i_postfix_ = check;

	check = atoi(read(ini_file.c_str(), "i_copy_to_","i_copy_to_").c_str());
	((CButton *)GetDlgItem(IDC_CHECK_COPY_TO))->SetCheck(check);//
	GetDlgItem(IDC_EDIT_COPY_TO)->EnableWindow(check);
	i_copy_to_ = check;


	UpdateData(FALSE);
}
BOOL Dlg_File_Mgr::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_POSTFIX)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_COPY_TO)->EnableWindow(FALSE);

	((CButton *)GetDlgItem(IDC_RADIO_DATA))->SetCheck(TRUE);//


	load_status();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Dlg_File_Mgr::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Dlg_File_Mgr::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void Dlg_File_Mgr::OnButPath() 
{
	// TODO: Add your control notification handler code here
	std::string path = select_dir();
	path_ = path.c_str();
	UpdateData(FALSE);
}
CString Dlg_File_Mgr::get_name(CString n)
{
	BOOL b_data = IsDlgButtonChecked(IDC_RADIO_DATA);
	BOOL b_postfex = IsDlgButtonChecked(IDC_RADIO_PREFIX);
	
	CString name;
	int pos = n.ReverseFind('.');
	name = n.Left(pos);

	if(b_data){
		CString temp = path_+n;
		//CString data = get_file_change_time(temp.GetBuffer(0)).c_str();
		CString data = get_file_data(temp.GetBuffer(0)).c_str();
		name = name+"-"+data;

	}else	if(b_postfex){
		name = name+"-"+edit_postfix_;
	}


	name += ".dxf";

	name.Replace(":","-");

	return name;
}
void Dlg_File_Mgr::change_name(CStringArray &files)
{
	CString new_name,old_name;
	for(int i=0;i<files.GetSize();i++){
		old_name = path_+files[i];
		new_name = path_+ get_name(files[i]);
		CFile::Rename(old_name,new_name); 
	}
}
void Dlg_File_Mgr::copy_to(CString path,CStringArray &files) 
{
	CString name,to_name;
	for(int i=0;i<files.GetSize();i++){
		name = path_+files[i];
		to_name = path+files[i];
		BOOL res = CopyFile(name,to_name,FALSE);
		if(!res){
			CString s;
			s.Format("%s copy error.",name);
			//AfxMessageBox(s);
		}
	}

}
void Dlg_File_Mgr::report_files(CStringArray &files) 
{
	if(files.GetSize()<1)
		return;
	CString name = path_+files[0];
	std::string data = get_file_data(name.GetBuffer(0));
	CString file_name = path_+data.c_str()+".txt";
	CStdioFile file;
  if(file.Open(file_name.GetBuffer(0), CFile::modeCreate | CFile::modeWrite)){
		for(int i=0;i<files.GetSize();i++){
      file.WriteString(files[i] + "\n");
		}
	}
  file.Close();
	name = path_+data.c_str()+".txt";
	CString to_name = edit_copy_to_+data.c_str()+".txt";
	BOOL res = CopyFile(name,to_name,FALSE);

}

void Dlg_File_Mgr::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CStringArray files;
	get_files_in_path(path_,"dxf",files);

	//changename
	if(!i_no_)
		change_name(files);
	
	//copy
	CStringArray new_files;
	get_files_in_path(path_,"dxf",new_files);
	if(i_copy_to_){
		copy_to(edit_copy_to_,new_files);
	}
	report_files(new_files);

	std::string ini_file = exe_path()+"setting.ini";
	write(ini_file.c_str(), "Path","Path", path_.GetBuffer(0));
	write(ini_file.c_str(), "Copy To Path","Copy To Path", edit_copy_to_.GetBuffer(0));
	write(ini_file.c_str(), "Postfix","Postfix", edit_postfix_.GetBuffer(0));
	write(ini_file.c_str(), "Delete","Delete", delete_str_.GetBuffer(0));

	CString str;
	str.Format("%d",i_no_);
	write(ini_file.c_str(), "i_no_","i_no_", str.GetBuffer(0));
	str.Format("%d",i_data_);
	write(ini_file.c_str(), "i_data_","i_data_", str.GetBuffer(0));
	str.Format("%d",i_postfix_);
	write(ini_file.c_str(), "i_postfix_","i_postfix_", str.GetBuffer(0));
	str.Format("%d",i_copy_to_);
	write(ini_file.c_str(), "i_copy_to_","i_copy_to_", str.GetBuffer(0));
	



//	AfxMessageBox("The files are dealing  OK.");
//	CDialog::OnOK();
}

void Dlg_File_Mgr::OnButCopyToPath() 
{
	// TODO: Add your control notification handler code here
	edit_copy_to_ = select_dir().c_str();
	UpdateData(FALSE);
	
}

void Dlg_File_Mgr::OnCheckCopyTo() 
{
	// TODO: Add your control notification handler code here
	int check = ((CButton *)GetDlgItem(IDC_CHECK_COPY_TO))->GetCheck();//
	GetDlgItem(IDC_EDIT_COPY_TO)->EnableWindow(check);
	i_copy_to_= check;

}
void Dlg_File_Mgr::init_radio() 
{
	i_no_ = 0;
	i_data_= 0;
	i_postfix_= 0;

}
void Dlg_File_Mgr::OnRadioData() 
{
	// TODO: Add your control notification handler code here
	BOOL show = IsDlgButtonChecked(IDC_RADIO_DATA);
	GetDlgItem(IDC_EDIT_POSTFIX)->EnableWindow(FALSE);

	init_radio();
	i_data_= 1;
	
}

void Dlg_File_Mgr::OnRadioPrefix() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_POSTFIX)->EnableWindow(TRUE);
	init_radio();
	i_postfix_= 1;
}

void Dlg_File_Mgr::OnRadioNo() 
{
	// TODO: Add your control notification handler code here
	init_radio();
	i_no_= 1;
	
}

static CString get_name_delete(CString del_str,CString str)
{
	str.Replace(del_str,"");
	return str;
}
void Dlg_File_Mgr::OnButDelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CStringArray files;
	get_files_in_path(path_,"*",files);
	CString new_name,old_name;
	for(int i=0;i<files.GetSize();i++){

		old_name = path_+files[i];
		new_name = path_+ get_name_delete(delete_str_,files[i]);
		CFile::Rename(old_name,new_name); 
	}



}
