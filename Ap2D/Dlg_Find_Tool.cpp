// Dlg_Find_Tool.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"

#include "Mgr_Control.h"
#include "Mgr_File.h"
#include "DB_View.h"
#include "Mgr_Database.h"
#include "Dlg_Find_Tool.h"
#include "dir.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Find_Tool dialog




Dlg_Find_Tool::Dlg_Find_Tool(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Find_Tool::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Find_Tool)
	edit_text_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Find_Tool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Find_Tool)
	DDX_Control(pDX, IDC_COMBO_TPL_NAMES, combo_tpl_names_);
	DDX_Control(pDX, IDC_COMBO_TYPE, combo_type_);
	DDX_Control(pDX, IDC_CHECK_TYPE, check_type_);
	DDX_Control(pDX, IDC_COMBO_COLOR, combo_color_);
	DDX_Control(pDX, IDC_COMBO_LINE_STYLE, combo_line_);
	DDX_Control(pDX, IDC_CHECK_COLOR_FIND, check_color_find_);
	DDX_Control(pDX, IDC_CHECK_TYPE_FIND, check_type_line_);
	DDX_Control(pDX, IDC_CHECK_TEXT, check_text_);
	DDX_Text(pDX, IDC_EDIT_TEXT, edit_text_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Find_Tool, CDialog)
	//{{AFX_MSG_MAP(Dlg_Find_Tool)
	ON_BN_CLICKED(IDC_BUT_TPL_SAVE, OnButTplSave)
	ON_BN_CLICKED(IDC_BUT_TPL_DEL, OnButTplDel)
	ON_BN_CLICKED(IDC_BUT_SAVE_AS, OnButSaveAs)
	ON_CBN_SELCHANGE(IDC_COMBO_TPL_NAMES, OnSelchangeComboTplNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void Dlg_Find_Tool::init_combo_type()
{
	combo_type_.InsertString(0,"Line");
	combo_type_.InsertString(1,"Circle");
	combo_type_.InsertString(2,"Arc");
	combo_type_.InsertString(3,"Text");
	combo_type_.InsertString(4,"Dim");
	combo_type_.InsertString(5,"Other");
	combo_type_.SetCurSel(0);
}



void Dlg_Find_Tool::init()
{
	files_path_ = exe_path().c_str();
	files_path_ = files_path_ + "configure" + "\\" + "Find Tool" + "\\";
	configure_db.init_combo_by_names_list(files_path_,combo_tpl_names_);
	init_combo_type();
	set_combo_line_type(combo_line_);
	combo_line_.SetCurSel(0);
	combo_color_.init_color();
	combo_color_.SetCurSel(0);
}



/////////////////////////////////////////////////////////////////////////////
// Dlg_Find_Tool message handlers

void Dlg_Find_Tool::set_checks(BOOL check)
{
	check_color_find_.SetCheck(check);
	check_type_line_.SetCheck(check);
	check_text_.SetCheck(check);
	check_type_.SetCheck(check);
}

void Dlg_Find_Tool::load_info()
{
//	set_combo_color(color_,Global::instance()->cur_val().page_common_.color_);
//	color_.set_color_index(Global::instance()->cur_val().page_common_.color_-1);
//	set_combo_txt(line_type_,Global::instance()->cur_val().page_common_.line_type_.c_str());

//	UpdateData(FALSE);
}


BOOL Dlg_Find_Tool::OnInitDialog() 
{
	CDialog::OnInitDialog();
	init();
	set_checks(FALSE);
	load_info();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Find_Tool::deal_text_sel(std::vector<dlhml::Entity*>  data,std::vector<dlhml::Entity*>&  show_data)
{
	if(check_text_.GetCheck())
	{
		CString str;
		GetDlgItemText(IDC_EDIT_TEXT,str);
		find_tool_text_sel(data,show_data,str);
	}
}

void 	Dlg_Find_Tool::deal_line_type_sel(std::vector<dlhml::Entity*>  data,std::vector<dlhml::Entity*>&  show_data)
{
	if(check_type_line_.GetCheck())
	{
		CString str;
		combo_line_.GetWindowText(str);
		find_tool_line_type_sel(data,show_data,str);
	}
}

void 	Dlg_Find_Tool::deal_type(std::vector<dlhml::Entity*>  data,std::vector<dlhml::Entity*>&  show_data)
{
	if(check_type_.GetCheck())
	{
		CString str;
		combo_type_.GetWindowText(str);
		find_tool_type_sel(data,show_data,str);
	}
}
void Dlg_Find_Tool::deal_color_sel(std::vector<dlhml::Entity*>  data,std::vector<dlhml::Entity*>  show_data)
{
	if(check_color_find_.GetCheck())
	{
		int cur_color_index = combo_color_.GetCurSel();
		cur_color_index += 1;
		if (show_data.empty())
			find_tool_color_sel(data,cur_color_index);
		else 
			find_tool_color_sel(show_data,cur_color_index);
	}
}
void Dlg_Find_Tool::OnOK() 
{
	std::vector<dlhml::Entity*> ents,sel_ents,show_datas;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	// TODO: Add extra validation here
	if ( sel_ents.empty() )
			get_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);
	deal_text_sel(sel_ents,show_datas);
	deal_line_type_sel(sel_ents,show_datas);
	deal_type(sel_ents,show_datas);
	deal_color_sel(sel_ents,show_datas);

	CDialog::OnOK();
}

void Dlg_Find_Tool::add_data_to_files(CStringArray &files)
{
	
	if(check_text_.GetCheck()){
		CString str; 
		GetDlgItemText(IDC_EDIT_TEXT,str);
		files.Add("text=" + str);
	}
	if(check_type_line_.GetCheck()){
		CString str; 
		combo_line_.GetWindowText(str);
		files.Add("ltype=" + str);
	}
	if(check_type_.GetCheck()){
		CString str; 
		
		combo_type_.GetWindowText(str);
		files.Add("type=" + str);
	}
	if(check_color_find_.GetCheck()){
		CString str; 
		int cur_color_index = combo_color_.GetCurSel();
		cur_color_index += 1;
		str.Format( "%d",cur_color_index);
		files.Add("color=" + str);
	}

}


void 	Dlg_Find_Tool::save_data_to_file(CString get_text)
{
	if ( get_text.Compare("") == 0 )
	{
		AfxMessageBox("Filename do not be allowed to be empty!");
	}
	else 
	{
		CStringArray files;
		add_data_to_files(files);
		configure_db.save_config_file(files_path_,get_text,files);
		configure_db.init_combo_by_names_list(files_path_,combo_tpl_names_);
	}
	
}

void Dlg_Find_Tool::deal_get_files_input_dlg(CStringArray& files)
{
	CString compare_str = "=";
	

	for (int i = 0 ; i < files.GetSize() ; i++ ){
		int len = files[i].GetLength();
		int npos = files[i].Find(compare_str);
		CString left_str = files[i].Left(npos);
		CString right_str = files[i].Right(len - npos - 1);
		if ( left_str.Compare("text") == 0 ){
			check_text_.SetCheck(false);
			if ( right_str && right_str.Compare("")!= 0){
				SetDlgItemText(IDC_EDIT_TEXT,right_str);
				check_text_.SetCheck(true);
			}
			else{
				SetDlgItemText(IDC_EDIT_TEXT,"");
			}
		}
	 else if ( left_str.Compare("type") == 0 ){
			check_type_.SetCheck(true);
			combo_type_.SetCurSel(combo_type_.FindString( -1, right_str ));
		}
	 else if ( left_str.Compare("ltype") == 0 ){
			check_type_line_.SetCheck(true);
			combo_line_.SetCurSel(combo_line_.FindString( -1, right_str ));
			
		}
	 else if ( left_str.Compare("color") == 0 ){
			check_color_find_.SetCheck(true);
			combo_color_.SetCurSel(atoi(right_str) - 1);
		}
	}
}

void Dlg_Find_Tool::OnButTplSave() 
{
	// TODO: Add your control notification handler code here
	afc::dir::create_floder(files_path_);
	CString get_text;
	GetDlgItemText(IDC_COMBO_TPL_NAMES,get_text);

	save_data_to_file(get_text);
	combo_tpl_names_.SetCurSel(combo_tpl_names_.FindString( -1, get_text ));

	CStringArray files;
	if ( get_text.Compare("") != 0 )
	{
		configure_db.open_config_file(files_path_,get_text,files);
		deal_get_files_input_dlg(files);
	}
	
}

void Dlg_Find_Tool::OnButTplDel() 
{
	// TODO: Add your control notification handler code here
	CString cur_text;
	GetDlgItemText(IDC_COMBO_TPL_NAMES,cur_text);
	if ( combo_tpl_names_.GetCount() != 0 && cur_text.Compare("") != 0)
	{
		CString cur_path = files_path_ + cur_text;
		SetFileAttributes(cur_path,GetFileAttributes(cur_path) & ~FILE_ATTRIBUTE_READONLY); 
		DeleteFile(cur_path);
		configure_db.init_combo_by_names_list(files_path_,combo_tpl_names_);	
//是否需要设置为空
		if ( combo_tpl_names_.GetCount() != 0 )
		{
			combo_tpl_names_.SetCurSel(0);
			CString get_text ;
			combo_tpl_names_.GetLBText(0,get_text );
			CStringArray files;
			if ( get_text.Compare("") != 0 )
			{
				configure_db.open_config_file(files_path_,get_text,files);
				init_show_data();
				deal_get_files_input_dlg(files);
			}
		}
	}
	
}

void Dlg_Find_Tool::OnButSaveAs() 
{
	// TODO: Add your control notification handler code here
	afc::dir::create_floder(files_path_);
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
		if ( get_text.Compare("") != 0 )
		{
			configure_db.open_config_file(files_path_,cur_sel_text,files);
			init_show_data();
			deal_get_files_input_dlg(files);
		}

	}
	
	
}

void Dlg_Find_Tool::init_show_data()
{
	set_checks(false);
	SetDlgItemText(IDC_EDIT_TEXT,"");
	combo_type_.SetCurSel(0);
	combo_line_.SetCurSel(0);
	combo_color_.SetCurSel(0);

}

void Dlg_Find_Tool::OnSelchangeComboTplNames() 
{
	// TODO: Add your control notification handler code here
	CString get_text ;
	int nIndex = combo_tpl_names_.GetCurSel( );
	combo_tpl_names_.GetLBText(nIndex,get_text );

	CStringArray files;
	if ( get_text.Compare("") != 0 )
	{
		configure_db.open_config_file(files_path_,get_text,files);
		init_show_data();
		deal_get_files_input_dlg(files);
	}
	
}
