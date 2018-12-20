// Tab_Entity.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Tab_Entity.h"

#include "Mgr_Dxfs.h"
#include "Mgr_Database.h"
#include "DB_View.h"
#include "Global.h"
#include "dir.h"


	
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Tab_Entity dialog
extern Tab_Entity *g_tab_edit;


Tab_Entity::Tab_Entity(CWnd* pParent /*=NULL*/)
	: CDialog(Tab_Entity::IDD, pParent)
{
	//{{AFX_DATA_INIT(Tab_Entity)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Tab_Entity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Tab_Entity)
	DDX_Control(pDX, IDC_COMBO_TPL_NAMES, combo_tpl_names_);
	DDX_Control(pDX, IDC_TAB_SHEET, tab_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Tab_Entity, CDialog)
	//{{AFX_MSG_MAP(Tab_Entity)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUT_OK, OnButOk)
	ON_BN_CLICKED(IDC_BUT_CANCEL, OnButCancel)
	ON_BN_CLICKED(IDC_BUT_TPL_SAVE, OnButTplSave)
	ON_BN_CLICKED(IDC_BUT_TPL_DEL, OnButTplDel)
	ON_BN_CLICKED(IDC_BUT_SAVE_AS, OnButSaveAs)
	ON_CBN_SELCHANGE(IDC_COMBO_TPL_NAMES, OnSelchangeComboTplNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

// Tab_Entity message handlers


BOOL Tab_Entity::OnInitDialog() 
{
	CDialog::OnInitDialog();
	files_path_ = get_file_path();
	files_path_ = files_path_ + "configure" + "\\" + "Edit Entity" + "\\";
	
	configure_db.init_combo_by_names_list(files_path_,combo_tpl_names_);
	// TODO: Add extra initialization here
	init_sheet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void Tab_Entity::reload()
{
	tab_.DeleteAllItems();
	init_sheet();

}


CString Tab_Entity::get_file_path()
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	CString tmpdir;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径也就是当前运行程序的全路径利用方法一的解析路径的方法，即可得到程序所在路径。

	tmpdir = exeFullPath;
	tmpdir=tmpdir.Left(tmpdir.ReverseFind('\\'));	
	tmpdir = tmpdir + "\\";
	return tmpdir;
}


void Tab_Entity::init_sheet()
{	
	
	Entitys sel_ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);
	tab_.AddPage("Common", &page_common_, IDD_PAGE_COMMON);
	page_common_.set_ents(sel_ents);

	page_show_.RemoveAll();
	CString temp_str;
	int cur_pos = 0;
	if(is_circles(sel_ents) || is_arcs(sel_ents)){
		tab_.AddPage("Radius", &page_radius_, IDD_PAGE_RADIUS);
		page_radius_.set_ents(sel_ents);
		cur_pos = 0;
		temp_str = "page_radius_";
		page_show_.Add(temp_str);
	}
	if(is_arcs(sel_ents) || is_lines(sel_ents)|| is_dims_no_angle(sel_ents)){
		tab_.AddPage("Arrow", &page_arrow_, IDD_PAGE_ARROW);
		page_arrow_.set_ents(sel_ents);
		cur_pos = 0;
		temp_str = "page_arrow_";
		page_show_.Add(temp_str);
	}
	if(is_texts(sel_ents) ){
		tab_.AddPage("Common Text", &page_text_common_, IDD_PAGE_TEXT_COMMON);
		page_text_common_.set_ents(sel_ents);
		cur_pos = 1;
		temp_str = "page_text_common_";
		page_show_.Add(temp_str);
	}
	if(is_dims(sel_ents)){
		tab_.AddPage("Text", &page_text_, IDD_PAGE_TEXT);
		page_text_.set_ents(sel_ents);
		cur_pos = 2;
		temp_str = "page_text_";
		page_show_.Add(temp_str);
	}
	if(is_dims_blk(sel_ents)){
		tab_.AddPage("Dim", &page_dim_, IDD_PAGE_DIM);
		page_dim_.set_ents(sel_ents);
		cur_pos = 2;

		temp_str = "page_dim_";
		page_show_.Add(temp_str);
	}
	if(is_dims_blk(sel_ents)){
		tab_.AddPage("Dim Texts", &page_dim_texts_, IDD_PAGE_DIM_TEXTS);
		page_dim_.set_ents(sel_ents);
		cur_pos = 2;
	}

	

	tab_.Show();	
	
	tab_.SetCurSel(cur_pos);

}

void Tab_Entity::set_current_val() 
{
/*
	page_face_.get_cur_val();
	page_common_.get_cur_val();
*/
}
void Tab_Entity::change_properties() 
{
/*
	std::vector<dlhml::Entity*> ents;
	Deal_Select_Ents::get_select_ents(ents);
	for(int i=0;i<ents.size();i++){
		Edit_Entity_By_Dlg edit_ent;
		edit_ent.set_eidt_kind(dim_kind_);
		ents[i]->visit(edit_ent);
	}
	page_names_.reset_entities();
	Project::instance()->cur_view()->scene()->invalidate();
	*/

}

void Tab_Entity::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
	
	
	if(::IsWindow(g_tab_edit->GetSafeHwnd())){
		g_tab_edit->DestroyWindow();
		g_tab_edit = NULL;
	}
}

void Tab_Entity::OnButOk() 
{
	// TODO: Add your control notification handler code here
	OnClose();
//	CDialog::OnOK();
}

void Tab_Entity::OnButCancel() 
{
	// TODO: Add your control notification handler code here
	OnClose();
//	CDialog::OnCancel();
}






void	Tab_Entity::add_data_to_files(CStringArray &files)
{
		CString temp_data_str;
		CString turn_str;
		temp_data_str = "line_type_=" + (CString)Global::instance()->cur_val().page_common_.line_type_.c_str();
		files.Add(temp_data_str);
		turn_str.Format("%d",Global::instance()->cur_val().page_common_.color_);
		temp_data_str = "line_color_=" + turn_str;
		files.Add(temp_data_str);
		temp_data_str = "arrow_pos_=" + (CString)Global::instance()->cur_val().page_arrow_.arrow_pos_.c_str();
		files.Add(temp_data_str);
		temp_data_str = "arrow_num_=" + (CString)Global::instance()->cur_val().page_arrow_.arrow_num_.c_str();
		files.Add(temp_data_str);
		temp_data_str = "arrow_style_=" + (CString)Global::instance()->cur_val().page_arrow_.arrow_style_.c_str();
		files.Add(temp_data_str);
		turn_str.Format("%f",Global::instance()->cur_val().page_arrow_.arrow_level_);
		temp_data_str = "arrow_height_=" + turn_str;
		files.Add(temp_data_str);

		temp_data_str = "text_content_=" + (CString)Global::instance()->cur_val().page_text_.content_.c_str();
		files.Add(temp_data_str);
		turn_str.Format("%d",Global::instance()->cur_val().page_text_.color_);
		temp_data_str = "text_color_=" + turn_str;
		files.Add(temp_data_str);
		turn_str.Format("%f",Global::instance()->cur_val().page_text_.hight_);
		temp_data_str = "text_hight_=" + turn_str;
		files.Add(temp_data_str);
		turn_str.Format("%f",Global::instance()->cur_val().page_text_.angle_);
		temp_data_str = "text_angle_=" + turn_str;
		files.Add(temp_data_str);
		temp_data_str = "text_pos_=" + (CString)Global::instance()->cur_val().page_text_.text_pos_.c_str();
		files.Add(temp_data_str);
		turn_str.Format("%f",Global::instance()->cur_val().page_text_.precision_);
		temp_data_str = "text_precision_=" + turn_str;
		files.Add(temp_data_str);
		temp_data_str = "text_frame_kind_=" + (CString)Global::instance()->cur_val().page_text_.frame_kind_.c_str();
		files.Add(temp_data_str);
		turn_str.Format("%d",Global::instance()->cur_val().page_text_.frame_color_);
		temp_data_str = "text_frame_color_=" + turn_str;
		files.Add(temp_data_str);

		temp_data_str = "dim_kind_=" + (CString)Global::instance()->cur_val().page_dim_.dim_kind_.c_str();
		files.Add(temp_data_str);
		turn_str.Format("%f",Global::instance()->cur_val().page_dim_.start_offset_);
		temp_data_str = "dim_start_offset_=" + turn_str;
		files.Add(temp_data_str);
		turn_str.Format("%f",Global::instance()->cur_val().page_dim_.end_offset_);
		temp_data_str = "dim_end_offset_=" + turn_str;
		files.Add(temp_data_str);
		turn_str.Format("%f",Global::instance()->cur_val().page_dim_.start_dim_len_);
		temp_data_str = "start_dim_len_=" + turn_str;
		files.Add(temp_data_str);
		turn_str.Format("%f",Global::instance()->cur_val().page_dim_.end_dim_len_);
		temp_data_str = "end_dim_len_=" + turn_str;
		files.Add(temp_data_str);
}
/*
void	Tab_Entity::add_files_data_to_dlg(CStringArray &files)
{

}
*/

void Tab_Entity::deal_get_files_input_dlg(CStringArray& files)
{
	
	for (int i = 0; i < files.GetSize(); i++ )
	{
		CString temp_str;
		CString compare_str = "=";

		
		int len = files[i].GetLength();
		int npos = files[i].Find(compare_str);
		CString left_str = files[i].Left(npos);
		CString right_str = files[i].Right(len - npos - 1);
		if ( left_str.Compare("line_type_") == 0 )
			Global::instance()->cur_val().page_common_.line_type_ = right_str;
		else	if ( left_str.Compare("line_color_") == 0 )
			Global::instance()->cur_val().page_common_.color_  =  atoi(right_str);
		else	if ( left_str.Compare("arrow_pos_") == 0 )
			Global::instance()->cur_val().page_arrow_.arrow_pos_ = right_str;
		else	if ( left_str.Compare("arrow_num_") == 0 )
			Global::instance()->cur_val().page_arrow_.arrow_num_ = right_str;
		else	if ( left_str.Compare("arrow_style_") == 0 )
			Global::instance()->cur_val().page_arrow_.arrow_style_ = right_str;
		else	if ( left_str.Compare("arrow_height_") == 0 )
			Global::instance()->cur_val().page_arrow_.arrow_level_ = atof(right_str);
		else	if ( left_str.Compare("text_content_") == 0 )
			Global::instance()->cur_val().page_text_.content_ = right_str;
		else	if ( left_str.Compare("text_color_") == 0 )
			Global::instance()->cur_val().page_text_.color_ = atoi(right_str);
		else	if ( left_str.Compare("text_hight_") == 0 )
			Global::instance()->cur_val().page_text_.hight_ = atof(right_str);
		else	if ( left_str.Compare("text_angle_") == 0 )
			Global::instance()->cur_val().page_text_.angle_ = atof(right_str)*3.1415926/180;
		else	if ( left_str.Compare("text_pos_") == 0 )
			Global::instance()->cur_val().page_text_.text_pos_ = right_str;
		else	if ( left_str.Compare("text_precision_") == 0 )
			Global::instance()->cur_val().page_text_.precision_ = atof(right_str);
		else	if ( left_str.Compare("text_frame_kind_") == 0 )
			Global::instance()->cur_val().page_text_.frame_kind_ = right_str;
		else	if ( left_str.Compare("text_frame_color_") == 0 )
			Global::instance()->cur_val().page_text_.frame_color_ = atoi(right_str);
		else	if ( left_str.Compare("dim_kind_") == 0 )
			Global::instance()->cur_val().page_dim_.dim_kind_ = right_str;
		else	if ( left_str.Compare("dim_start_offset_") == 0 )
			Global::instance()->cur_val().page_dim_.start_offset_ = atof(right_str);
		else	if ( left_str.Compare("dim_end_offset_") == 0 )
			Global::instance()->cur_val().page_dim_.end_offset_ = atof(right_str);
		else	if ( left_str.Compare("start_dim_len_") == 0 )
			Global::instance()->cur_val().page_dim_.start_dim_len_ = atof(right_str);
		else	if ( left_str.Compare("end_dim_len_") == 0 )
			Global::instance()->cur_val().page_dim_.end_dim_len_ = atof(right_str);
	}
	for ( i = 0;i<page_show_.GetSize();i++)
	{
		CString per_page_str = page_show_.GetAt(i);
		if (per_page_str.Compare("page_radius_") == 0)
			page_radius_.Updata();
		else if(per_page_str.Compare("page_arrow_") == 0)
			page_arrow_.Updata();
		else if(per_page_str.Compare("page_text_") == 0)
			page_text_.Updata();
		else if(per_page_str.Compare("page_dim_") == 0)
			page_dim_.Updata();
	};
	
}

void 	Tab_Entity::save_data_to_file(CString get_text)
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

void Tab_Entity::OnButTplSave() 
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

void Tab_Entity::OnButSaveAs() 
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
			configure_db.open_config_file(files_path_,get_text,files);
			deal_get_files_input_dlg(files);
		}

	}
	
}


void Tab_Entity::OnButTplDel() 
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
				deal_get_files_input_dlg(files);
			}
		}
	}
}


void Tab_Entity::OnSelchangeComboTplNames() 
{
	// TODO: Add your control notification handler code here
	CString get_text ;
	int nIndex = combo_tpl_names_.GetCurSel( );
	combo_tpl_names_.GetLBText(nIndex,get_text );

	CStringArray files;
	if ( get_text.Compare("") != 0 )
	{
		configure_db.open_config_file(files_path_,get_text,files);
		deal_get_files_input_dlg(files);
	}

}
