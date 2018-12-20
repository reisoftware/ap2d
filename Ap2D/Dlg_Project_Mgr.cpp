// Dlg_Project_Mgr.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Project_Mgr.h"

#include "Global.h"
#include "Dlg_Input.h"
#include "MainFrm.h"
#include "mgr_File.h"
#include "DB_View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Project_Mgr dialog


Dlg_Project_Mgr::Dlg_Project_Mgr(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Project_Mgr::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Project_Mgr)
	project_path_ = _T("");
	//}}AFX_DATA_INIT
	cur_company_name_ = "";
}


void Dlg_Project_Mgr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Project_Mgr)
	DDX_Control(pDX, IDC_LIST_COMPANY, list_company_);
	DDX_Control(pDX, IDC_LIST_PROJECT, list_projects_);
	DDX_Text(pDX, IDC_EDIT_PROJECT_PATH, project_path_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Project_Mgr, CDialog)
	//{{AFX_MSG_MAP(Dlg_Project_Mgr)
	ON_BN_CLICKED(ID_BUT_OPEN, OnButOpen)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COMPANY, OnClickListCompany)
	ON_BN_CLICKED(ID_BUT_SAVE, OnButSave)
	ON_BN_CLICKED(ID_BUT_SAVE_PROJECT, OnButSaveProject)
	ON_BN_CLICKED(ID_BUT_NEW_COMPANY, OnButNewCompany)
	ON_BN_CLICKED(ID_BUT_EDIT_COMPANY, OnButEditCompany)
	ON_BN_CLICKED(ID_BUT_DEL_COMPANY, OnButDelCompany)
	ON_BN_CLICKED(ID_BUT_NEW_PROJECT, OnButNewProject)
	ON_BN_CLICKED(ID_BUT_EDIT_PROJECT, OnButEditProject)
	ON_BN_CLICKED(ID_BUT_DELETE_PROJECT, OnButDeleteProject)
	ON_BN_CLICKED(ID_BUT_CLOSE, OnButClose)
	ON_BN_CLICKED(ID_BUT_DEL_TREE_INFO, OnButDelTreeInfo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROJECT, OnClickListProject)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PROJECT, OnDblclkListProject)
	ON_BN_CLICKED(ID_BUT_PROJECT_PATH, OnButProjectPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Project_Mgr message handlers
void Dlg_Project_Mgr::init_list()
{
	CString heads;
	list_projects_.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	heads.Format("%s,250;","Name");
	list_projects_.set_headings(_T(heads));

	list_company_.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	heads.Format("%s,250;","Name");
	list_company_.set_headings(_T(heads));
/*

	list_company_.add_item( _T("dahe"));
	list_company_.add_item( _T("dubian"));
	list_company_.add_item( _T("nanteijian"));

	list_projects_.add_item( _T("project1"));
	list_projects_.add_item( _T("project2"));
	list_projects_.add_item( _T("project3"));
*/

}
BOOL Dlg_Project_Mgr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	init_list();
	Global::instance()->db_company().show_companys(list_company_);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Project_Mgr::OnButOpen() 
{
	// TODO: Add your control notification handler code here

	SetCursor(LoadCursor(NULL,IDC_WAIT));

	std::vector<std::string> names;
	list_company_.get_select_rows(names);
	if(names.size()>0){
		Global::instance()->project_info().company_ = names[0];
	}
	names.clear();
	list_projects_.get_select_rows(names);
	if(names.size()>0){
		Global::instance()->project_info().name_ = names[0];
	}

	if(cur_company_name_ == ""){
		AfxMessageBox("Please select the company.");
		return ;
	}
	if(cur_project_name_ == ""){
		AfxMessageBox("Please select the project.");
		return ;
	}
	if(project_path_ == ""){
		AfxMessageBox("Please select the project path.");
		return ;
	}
	Global::instance()->project_info().dir_path = Global::instance()->db_company().get_project_path(cur_company_name_,cur_project_name_);

	//生成工程文件夹下的所需要的路径
	std::string path = Global::instance()->project_info().dir_path+"server\\";
	CreateDirectory(path.c_str(),NULL);
	path = Global::instance()->project_info().dir_path+"local\\";
	CreateDirectory(path.c_str(),NULL);

	//已知公司和工程后，需要初始化的内容
	//下载图纸数据库
	Global::instance()->db_detail().download(Global::instance()->get_detail_db_key());
//	Global::instance()->project_info().dir_path = "E:\\1_project\\";


	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->load_tree(Global::instance()->project_info().name_,Global::instance()->project_info().company_);

	//上传图纸数据库
	Global::instance()->db_tree().upload(Global::instance()->get_tree_key());
	Global::instance()->db_detail().upload(Global::instance()->get_detail_db_key());


	upload_files(Global::instance()->project_info().server_ip_,Global::instance()->get_need_upload_files_path());

//	Global::instance()->db_file_date().read();
	Global::instance()->db_file_date().read_std();

	SetCursor(LoadCursor(NULL,IDC_CROSS));

	DB_View::instance()->database()->clear_entity();

	//删除工程下的lua文件
	strings files;
	get_files(Global::instance()->project_info().dir_path,"lua",files);
	std::string str ;
	for(int i=0;i<files.size();i++){
		str = Global::instance()->project_info().dir_path + files[i];
		DeleteFile(str.c_str());
	}


	CDialog::OnOK();
}

void Dlg_Project_Mgr::OnClickListCompany(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_company_.GetFirstSelectedItemPosition();
	int nItem = list_company_.GetNextSelectedItem(pos);
	if(nItem == -1)
		return;
	cur_company_name_ = list_company_.GetItemText(nItem,0).GetBuffer(0);	
	Global::instance()->project_info().company_ = cur_company_name_;

	Global::instance()->db_company().show_projects(cur_company_name_,list_projects_);

	*pResult = 0;
}

void Dlg_Project_Mgr::OnButSave() 
{
	// TODO: Add your control notification handler code here
	Global::instance()->db_company().upload(Global::instance()->get_company_key());
}

void Dlg_Project_Mgr::OnButSaveProject() 
{
	// TODO: Add your control notification handler code here
	if(strcmp(cur_company_name_.c_str(),"")==0){
		AfxMessageBox("Please select the company.");
		return;
	}



	std::vector<std::string> names;
	list_projects_.get_rows(names);
	Projects pros;
	Project pro;
	for(int i=0;i<names.size();i++){
		pro.name_ = names[i];
		pros.push_back(pro);
	}
	Company com;
	com.name_ = cur_company_name_;
	com.pros_ = pros;
	Global::instance()->db_company().edit(com);
	Global::instance()->db_company().upload(Global::instance()->get_company_key());
	




}

void Dlg_Project_Mgr::OnButNewCompany() 
{
	// TODO: Add your control notification handler code here
	Dlg_Input in;
	if(in.DoModal() == IDOK){
		Company c;
		c.name_ =  in.val_;
		Global::instance()->db_company().push(c);
		list_company_.add_item(in.val_.c_str());
	}
}

void Dlg_Project_Mgr::OnButEditCompany() 
{
	// TODO: Add your control notification handler code here
	Dlg_Input in;
	if(in.DoModal() == IDOK){
		Company c;
		Company old;
		c.name_ =  in.val_;
		old.name_ =  in.val_;
		if(Global::instance()->db_company().get(c.name_,old)){
			c.pros_ = old.pros_;
		}
		Global::instance()->db_company().edit(c);
		POSITION pos = list_company_.GetFirstSelectedItemPosition();
		int nItem = list_company_.GetNextSelectedItem(pos);
		list_company_.SetItemText(nItem,0,c.name_.c_str());


	}
	
}

void Dlg_Project_Mgr::OnButDelCompany() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_company_.GetFirstSelectedItemPosition();
	int nItem = list_company_.GetNextSelectedItem(pos);
	list_company_.DeleteItem(nItem);
	Global::instance()->db_company().delete_item(cur_company_name_);
	
}

void Dlg_Project_Mgr::OnButNewProject() 
{
	// TODO: Add your control notification handler code here
	if(cur_company_name_ == ""){
		AfxMessageBox("Please select the company.");
		return ;
	}
	UpdateData(FALSE);
	Dlg_Input in;
	if(in.DoModal() == IDOK){
		list_projects_.add_item(in.val_.c_str());
		Project pro;
		pro.name_ = in.val_;
		pro.dir_path_ = project_path_;
		Global::instance()->db_company().push_project(cur_company_name_,pro);

	}
}

void Dlg_Project_Mgr::OnButEditProject() 
{
	// TODO: Add your control notification handler code here
	Dlg_Input in;
	if(in.DoModal() == IDOK){
		UpdateData(FALSE);
		POSITION pos = list_projects_.GetFirstSelectedItemPosition();
		int nItem = list_projects_.GetNextSelectedItem(pos);
		list_projects_.change(in.val_.c_str(),nItem);
		list_projects_.SetItemText(nItem,0,in.val_.c_str());

		Global::instance()->db_company().edit_project_name(cur_company_name_,in.val_,project_path_.GetBuffer(0));

	}
}

void Dlg_Project_Mgr::OnButDeleteProject() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_projects_.GetFirstSelectedItemPosition();
	int nItem = list_projects_.GetNextSelectedItem(pos);

	std::string name = list_projects_.GetItemText(nItem,0).GetBuffer(0);	
	Global::instance()->db_company().del_project_name(cur_company_name_,name);

	list_projects_.DeleteItem(nItem);

	
}

void Dlg_Project_Mgr::OnButClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void Dlg_Project_Mgr::OnButDelTreeInfo() 
{
	// TODO: Add your control notification handler code here
	std::string key = Global::instance()->get_tree_key();
	del_all(const_cast<char*>(key.c_str()),Global::instance()->ap2d());

	del_all(const_cast<char*>(Global::instance()->get_detail_db_key().c_str()),Global::instance()->ap2d());
	
	Global::instance()->db_file_date().del();

}

void Dlg_Project_Mgr::OnClickListProject(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_projects_.GetFirstSelectedItemPosition();
	int nItem = list_projects_.GetNextSelectedItem(pos);
	if(nItem == -1)
		return;
	std::string pro_name = list_projects_.GetItemText(nItem,0).GetBuffer(0);	
	cur_project_name_ = pro_name;
	project_path_ = Global::instance()->db_company().get_project_path(cur_company_name_,cur_project_name_).c_str();
	Global::instance()->project_info().name_ = pro_name;

	Global::instance()->project_info().dir_path = project_path_;

	UpdateData(FALSE);

	
	*pResult = 0;
}

void Dlg_Project_Mgr::OnDblclkListProject(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = list_projects_.GetFirstSelectedItemPosition();
	int nItem = list_projects_.GetNextSelectedItem(pos);
	if(nItem == -1)
		return;
	std::string pro_name = list_projects_.GetItemText(nItem,0).GetBuffer(0);	
	cur_project_name_ = pro_name;
	Global::instance()->project_info().name_ = pro_name;
	
	OnButOpen();
	*pResult = 0;
}

void Dlg_Project_Mgr::OnButProjectPath() 
{
	// TODO: Add your control notification handler code here
	std::string path = select_dir();
	project_path_ = path.c_str();


	Global::instance()->db_company().edit_project_name(cur_company_name_,cur_project_name_,project_path_.GetBuffer(0));


	UpdateData(FALSE);

}
