// Dlg_Joint_DB_Edit.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Joint_DB_Edit.h"


#include "Mgr_File.h"

#include "dir.h"
#include <shlwapi.h>
#include "Dlg_Joint_DB.h"
Dlg_Joint_DB dlg_joint_db_;

//#pragma comment(lib,"Shlwapi.lib") //如果没有这行，会出现link错误

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Joint_DB_Edit dialog

void Dlg_Joint_DB_Edit::set_sel_name(CString name)
{
	cur_sel_name_ = name;
}

CString Dlg_Joint_DB_Edit::get_files_path()
{
	CString	files_path = exe_path().c_str();
	files_path = files_path + "configure" + "\\" + "pictures" + "\\";
	return files_path;
}


Dlg_Joint_DB_Edit::Dlg_Joint_DB_Edit(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Joint_DB_Edit::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Joint_DB_Edit)
	//}}AFX_DATA_INIT
}


void Dlg_Joint_DB_Edit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Joint_DB_Edit)
	DDX_Control(pDX, IDC_EDIT_PATH, edit_path_);
	DDX_Control(pDX, IDC_COMBO_NAMES, combo_names_);
	DDX_Control(pDX, IDC_STATIC_PICTURE, static_pics_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Joint_DB_Edit, CDialog)
	//{{AFX_MSG_MAP(Dlg_Joint_DB_Edit)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PATH, OnButtonOpenPath)
	ON_BN_CLICKED(ID_BUT_ADD, OnButAdd)
	ON_BN_CLICKED(ID_BUT_EDIT, OnButEdit)
	ON_BN_CLICKED(ID_BUT_DEL, OnButDel)
	ON_BN_CLICKED(ID_BUT_CLEAR, OnButClear)
	ON_CBN_SELCHANGE(IDC_COMBO_NAMES, OnSelchangeComboNames)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Joint_DB_Edit message handlers

void Dlg_Joint_DB_Edit::show_image(CString strFile)
{
	CBitmap bmp;  
	HBITMAP hbitmap;
	//bmp.LoadBitmap(strFile);  
	if (PathFileExists(strFile)){
		CRect lRect;
		static_pics_.GetClientRect(&lRect);

		hbitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),strFile,IMAGE_BITMAP,lRect.Width(),lRect.Height(),LR_LOADFROMFILE);
		bmp.Attach(hbitmap);
		
		BITMAP bm;
		bmp.GetBitmap(&bm);
		CDC dcMem;
		dcMem.CreateCompatibleDC(GetDC());
		CBitmap *pOldBitmap=(CBitmap*)dcMem.SelectObject(bmp);

		//显示位图
		ScreenToClient(&lRect);
		//StretchBlt(dc, 0,0, lRect.Width(),lRect.Height(),dcMem, 0, 0,bm.bmWidth, bm.bmHeight,SRCCOPY);
		static_pics_.GetDC()->StretchBlt(0,0,lRect.Width(),lRect.Height(),&dcMem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		dcMem.SelectObject(&pOldBitmap); 
		bmp.Detach();
		DeleteObject(bmp);
		dcMem.DeleteDC();  
	}
	else{
		static_pics_.ShowWindow(FALSE); //初始化picture控件显示问题 
		static_pics_.ShowWindow(TRUE);
	}
}

void Dlg_Joint_DB_Edit::OnButtonOpenPath() 
{
//	 TODO: Add your control notification handler code here
		CString strFile;
		static char szFilter[] = "Picture file (*.bmp)|*.bmp";
		CFileDialog dlg(FALSE, _T(".bmp"), "", OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL);
		dlg.m_ofn.lpstrTitle = "Get Picture File";
		if(dlg.DoModal()== IDOK)
		{
			strFile=dlg.GetPathName();
		//SetDlgItemText(IDC_EDIT_PATH,strFile);
			edit_path_.SetWindowText(strFile);
			show_image(strFile);
		}


}

void Dlg_Joint_DB_Edit::init_db()
{

	pics_db_.clear();
	cur_path_ = get_files_path();
	afc::dir::create_floder(cur_path_);
	CString filename = "pic_ifo.txt";
	filename = cur_path_ + filename ;
	CStdioFile file;
	if ( !file.Open(filename,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead | CFile::typeText )){
		 #ifdef _DEBUG
		  afxDump << "Unable to open file" << "\n";
	   #endif
	   exit( 1 );
	}
	CString perline= "" ;
	while(file.ReadString(perline)){
		PICFILE cur_picfile;
		cur_picfile.name_ = perline.Left(perline.Find('='));
		
		cur_picfile.path_ = perline.Right(perline.GetLength() - perline.Find('=') - 1);
		if (PathFileExists(cur_path_ + cur_picfile.path_)){
			pics_db_.push_back(cur_picfile);
		}
	}
	file.Close();
}



void Dlg_Joint_DB_Edit::init_show_dlg()
{
//	combo_names_.Clear();
	combo_names_.ResetContent( );
	for (int i = 0 ; i < pics_db_.size() ; i++ ){
		combo_names_.AddString(pics_db_[i].name_);
	}
}

void Dlg_Joint_DB_Edit::init_sel()
{
	combo_names_.SetWindowText(cur_sel_name_);
	for (int i = 0; i < pics_db_.size() ; i++ ){
		if ( pics_db_[i].name_.Compare(cur_sel_name_) == 0 ){
			edit_path_.SetWindowText(cur_path_ + pics_db_[i].path_);
			show_image(cur_path_ + pics_db_[i].path_);
			break;
		}
	}
}

BOOL Dlg_Joint_DB_Edit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	init_db();
	init_show_dlg();
//	init_sel();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Joint_DB_Edit::save_pic_ifo()
{
	CString filename = "pic_ifo.txt";
	filename = cur_path_ + filename ;
	CStdioFile file;
	if ( !file.Open(filename,CFile::modeCreate | CFile::modeWrite | CFile::typeText )){
		 #ifdef _DEBUG
		  afxDump << "Unable to open file" << "\n";
	   #endif
	   exit( 1 );
	}

	for (int i = 0 ; i < pics_db_.size() ; i++ ){
		file.WriteString(pics_db_[i].name_);
		file.WriteString("=");
		file.WriteString(pics_db_[i].path_);
		file.WriteString("\n");
	}

	file.Close();
}



void Dlg_Joint_DB_Edit::Determine_is_have(CString DlgStr,CString DlgPath)
{
	CString filename = DlgPath.Right(DlgPath.GetLength() - DlgPath.ReverseFind('\\') - 1);
	if ( combo_names_.GetCount( ) != 0 ){
		if ( combo_names_.FindStringExact( -1, DlgStr ) >= 0 ){
			AfxMessageBox("It has been in ! Please rename !");
			SetDlgItemText(IDC_COMBO_NAMES,"");
		}
		else{
				
			CString tempfilename = cur_path_ + DlgStr + ".bmp";
			combo_names_.AddString( DlgStr );
			cur_sel_name_ = DlgStr; 

			if (PathFileExists(tempfilename)){
				 //存在
				int reval = AfxMessageBox("The picture has been exists!You want to Cover it!",MB_OKCANCEL );
				if ( reval == 2 ){
					while(true){
						if (PathFileExists(tempfilename)){
							tempfilename.Replace(".bmp","");
							tempfilename = tempfilename + "_carbon" + ".bmp" ;
						}
						else{
							break;
						}
					}
				}
			}
			PICFILE cur_picfile;
			cur_picfile.name_ = DlgStr;
			cur_picfile.path_ = tempfilename.Right(tempfilename.GetLength() - tempfilename.ReverseFind('\\') - 1);
			pics_db_.push_back(cur_picfile);
			CopyFile(DlgPath, tempfilename, false);
			edit_path_.SetWindowText(tempfilename);
			save_pic_ifo();

		}

	}
	else{
		combo_names_.AddString( DlgStr );
		cur_sel_name_ = DlgStr; 

		//CString tempfilename = cur_path_ + filename;
		CString tempfilename = cur_path_ + DlgStr + ".bmp";
		PICFILE cur_picfile;
		cur_picfile.name_ = DlgStr;
		cur_picfile.path_ = tempfilename.Right(tempfilename.GetLength() - tempfilename.ReverseFind('\\') - 1);
		pics_db_.push_back(cur_picfile);
		CopyFile(DlgPath, tempfilename, false);
		edit_path_.SetWindowText(tempfilename);
		save_pic_ifo();
	}

}

void Dlg_Joint_DB_Edit::OnButAdd() 
{
	// TODO: Add your control notification handler code here
	CString cur_txt,cur_path;
	GetDlgItemText(IDC_EDIT_PATH,cur_path);
	if ( cur_path.Compare("") != 0  ){
		GetDlgItemText(IDC_COMBO_NAMES,cur_txt);
		if ( cur_txt.Compare("") != 0 ){
			Determine_is_have(cur_txt,cur_path);
		}
		else
			AfxMessageBox("Please input name !");
	}
	else
		AfxMessageBox("Please select picture !");	
}

void Dlg_Joint_DB_Edit::edit_btn(int pos,CString name,CString cur_path)
{
	
	CString filename = cur_path.Right(cur_path.GetLength() - cur_path.ReverseFind('\\') - 1);
//	CString tempfilename = cur_path_ + filename;
	CString tempfilename = cur_path_ + name + ".bmp";
	pics_db_[pos].name_ = name;
	if (PathFileExists(tempfilename)){
		int reval = AfxMessageBox("The picture has been exists!You want to Cover it!",MB_OKCANCEL );
		if ( reval == 2 ){
			while(true){
				if (PathFileExists(tempfilename)){
					tempfilename.Replace(".bmp","");
					tempfilename = tempfilename + "_carbon" + ".bmp" ;
					
				}
				else{
					break;
				}
			}	
		}	
	}
	CopyFile(cur_path, tempfilename, false);
//	CFile TempFile;
//	if (cur_path.Compare(tempfilename) != 0)
//		TempFile.Remove(cur_path_ + pics_db_[pos].path_);
	pics_db_[pos].path_ = tempfilename.Right(tempfilename.GetLength() - tempfilename.ReverseFind('\\') - 1);
	edit_path_.SetWindowText(tempfilename);
	show_image(tempfilename);
	save_pic_ifo();
	
}

void Dlg_Joint_DB_Edit::OnButEdit() 
{
	// TODO: Add your control notification handler code here
	if ( cur_sel_name_.Compare("") != 0 ){
		CString cur_str;
		combo_names_.GetWindowText(cur_str);
		if ( cur_str.Compare("") == 0 )
			AfxMessageBox("Please input name ! ");
		else{
			if ( combo_names_.FindStringExact( -1, cur_str ) >= 0 && cur_str.Compare(cur_sel_name_) != 0 ){
					AfxMessageBox("It has been in ! Please re-edit !");
					combo_names_.SetWindowText("");
				}
			else{
				int pos =  combo_names_.FindStringExact( -1, cur_sel_name_ );
				combo_names_.DeleteString(pos);
				combo_names_.InsertString(pos,cur_str);
				combo_names_.SetWindowText(cur_str);
				
				CString cur_path;
				edit_path_.GetWindowText(cur_path);
				if ( cur_path.Compare("") == 0 )
					AfxMessageBox("Please select picture !");	
				else{

					for (int i = 0 ; i < pics_db_.size() ; i++ ){
						if ( pics_db_[i].name_.Compare(cur_sel_name_) == 0){
							edit_btn(i,cur_str,cur_path);
							cur_sel_name_ = cur_str;
							break;
						}
					}
				}
			}
		}
	}
	//GetDlgItemText(IDC_COMBO_NAMES,cur_txt);
}

void Dlg_Joint_DB_Edit::OnButDel() 
{
	// TODO: Add your control notification handler code here

	CString cur_sel_name;
	combo_names_.GetWindowText(cur_sel_name);
	combo_names_.DeleteString(combo_names_.FindStringExact(0,cur_sel_name));
	//std::vector<PICFILE>::iterator iter;
	for (int i = 0 ; i < pics_db_.size() ; i++ ){
		if ( cur_sel_name.Compare(pics_db_[i].name_) == 0 ){
				if(PathFileExists(cur_path_ + pics_db_[i].path_)){
					CFile TempFile;
					TempFile.Remove(cur_path_ + pics_db_[i].path_);
					
				}
				pics_db_.erase(pics_db_.begin() + i);		
				save_pic_ifo();
				break;
		}
	}
	

	edit_path_.SetWindowText("");
	combo_names_.SetWindowText("");
	static_pics_.ShowWindow(FALSE); //初始化picture控件显示问题 
	static_pics_.ShowWindow(TRUE);
}

void Dlg_Joint_DB_Edit::OnButClear() 
{
	// TODO: Add your control notification handler code here
	CFile TempFile;
	for (int i = 0 ; i < pics_db_.size() ; i++ ){
			if (PathFileExists(cur_path_ + pics_db_[i].path_)){
				TempFile.Remove(cur_path_ + pics_db_[i].path_);
			}
	}
	combo_names_.ResetContent( );
	edit_path_.SetWindowText("");
	pics_db_.clear();
	static_pics_.ShowWindow(FALSE); //初始化picture控件显示问题 
	static_pics_.ShowWindow(TRUE);
	save_pic_ifo();
}

void Dlg_Joint_DB_Edit::OnCancel() 
{
	// TODO: Add extra cleanup here
//	dlg_joint_db_.re_call();
	CDialog::OnCancel();
}

void Dlg_Joint_DB_Edit::OnSelchangeComboNames() 
{
	// TODO: Add your control notification handler code here
	int item  = combo_names_.GetCurSel();
	CString cur_sel_name;
	combo_names_.GetLBText(item,cur_sel_name);
	cur_sel_name_ = cur_sel_name; 
	if ( cur_sel_name.Compare("") != 0 ){
		for (int i = 0 ; i < pics_db_.size() ; i++ ){
			if ( cur_sel_name.Compare(pics_db_[i].name_) == 0 ){
				edit_path_.SetWindowText(cur_path_ + pics_db_[i].path_);
				show_image(cur_path_ + pics_db_[i].path_);
				break;
			}
		}
	}
	
}

PICFILES* Dlg_Joint_DB_Edit::instance()
{	
	static PICFILES g;
	return &g;
}


void Dlg_Joint_DB_Edit::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//	DestroyWindow();
	CDialog::OnClose();
}

