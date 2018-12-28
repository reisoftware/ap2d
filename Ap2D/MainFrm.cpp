// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Ap2D.h"

#include "MainFrm.h"
#include "Dlg_Login.h"
#include "Dlg_Project_Mgr.h"
#include "Mgr_File.h"
#include <string>
#include "Global.h"
#include "DB_View.h"
#include "getrace.h"
#include "Dlg_Layer_DB.h"
#include "Mgr_Dxfs.h"
#include "Dlg_Input.h"
#include "dir.h"
#include "Dlg_Hot_Key.h"

#include "hk_edit_dlg.h"

#include "Dlg_Setting.h"
#include "net_ap.h"
#include "hk_fhit.h"
#include "Mgr_Control.h"

#include "hotkey.h"
#include "Ap2DView.h"
#include "Mgr_Detail.h"
#include "Dlg_File_Mgr.h"
#include "DB_Blocks.h"

#include "Dlg_Project_Paths_Save.h"
#include "DB_Font_Width_Factor.h"

#define  EDIT_WIDTH  80  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
#define IDD_REIWORKSPACE WM_USER +110
#define TOOLBAR_DRAW_BUTTON_WIDTH 16

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_BUT_SETUP, OnButSetup)
	ON_COMMAND(ID_BUT_OPEN_PROJECT_PATH, OnButOpenProjectPath)
	ON_COMMAND(ID_BUT_NEW_VIEW, OnButNewView)
	ON_COMMAND(ID_BUT_LOGIN, OnButLogin)
	ON_COMMAND(ID_BUT_OPEN_PROJECT, OnButOpenProject)
	ON_COMMAND(ID_BUT_INPUT_DXFS, OnButInputDxfs)
	ON_COMMAND(ID_BUT_LOAD_LAYER, OnButLoadLayer)
	ON_COMMAND(ID_BUT_CREATE_TABLE, OnButCreateTable)
	ON_COMMAND(ID_BUT_SAVE_SERVER, OnButSaveServer)
	ON_COMMAND(ID_BUT_OPEN_SERVER, OnButOpenServer)
	ON_CBN_SELCHANGE(ID_TOOL_COMBO, OnEditchangeCombo_Tool)
	ON_COMMAND(ID_MENU_OPEN_PROJECT, OnMenuOpenProject)
	ON_COMMAND(ID_MENU_CREATE_PROJECT, OnMenuCreateProject)
	ON_COMMAND(ID_MENU_CLOSE_PROJECT, OnMenuCloseProject)
	ON_COMMAND(ID_MENU_ADD_VIEW, OnMenuAddView)
	ON_COMMAND(ID_MENU_DELETE_VIEW, OnMenuDeleteView)
	ON_COMMAND(ID_MENU_EDIT_VIEW, OnMenuEditView)
	ON_COMMAND(ID_BUT_HOT_KEY, OnButHotKey)
	ON_COMMAND(ID_BUT_HOT_KEY_P, OnButHotKeyP)
	ON_COMMAND(ID_BUT_IN_LUA, OnButInLua)
	ON_COMMAND(ID_BUT_OUT_LUA, OnButOutLua)
	ON_COMMAND(ID_BUT_IN_LUA_P, OnButInLuaP)
	ON_COMMAND(ID_BUT_OUT_LUA_P, OnButOutLuaP)
	ON_COMMAND(ID_BUT_COMPARE_XSTEEL, OnButCompareXsteel)
	ON_COMMAND(ID_BUT_COMPARE_XSTEEL_P, OnButCompareXsteelP)
	ON_COMMAND(ID_BUT_FILE_MAMAGE, OnButFileMamage)
	ON_COMMAND(ID_BUT_FILE_MAMAGE_p, OnBUTFILEMAMAGEp)
	ON_COMMAND(ID_MENU_OPEN_PROJECT_CHECK, OnMenuOpenProjectCheck)
	ON_COMMAND(ID_MENU_CREATE_PROJECT_CHECK, OnMenuCreateProjectCheck)
	ON_COMMAND(ID_MENU_CLOSE_PROJECT_CHECK, OnMenuCloseProjectCheck)
	ON_COMMAND(ID_MENU_SET_COMPLATE_CHECK, OnMenuSetComplateCheck)
	ON_COMMAND(ID_MENU_SET_COMPLATE_CHECK_P, OnMenuSetComplateCheckP)
	ON_COMMAND(ID_MENU_UPDATE, OnMenuUpdate)
	ON_COMMAND(ID_MENU_CREATE_DXF, OnMenuCreateDxf)
	ON_COMMAND(ID_MENUITEM_SAVE, OnMenuSave)
	ON_COMMAND(ID_MENU_SET_ERROR_CHECK_P, OnMenuSetErrorCheckP)
	ON_COMMAND(ID_MENU_CLEAR_STATUS_, OnMenuClearStatus)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	left_mgr_ = NULL;
	//TRACE_INIT;
}
void CMainFrame::close_global()
{
	DB_View::instance()->close();
}
CMainFrame::~CMainFrame()
{
	close_global();

/*
	if(left_mgr_){
		left_mgr_->CloseWindow();
		delete left_mgr_;
		left_mgr_ = NULL;
	}

*/

	//TRACE_CLOSE;
}
void CMainFrame::init_eidt_bar()
{
	//edit工具条
	if (!edit_toolBar_.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!edit_toolBar_.LoadToolBar(IDR_TOOLBAR_EDIT))
	{
		TRACE0("Failed to create toolbar\n");
		return ;      // fail to create
	}
	edit_toolBar_.ModifyStyle(0, TBSTYLE_FLAT);
	edit_toolBar_.LoadTrueColorToolBar(TOOLBAR_DRAW_BUTTON_WIDTH,IDB_BMP_EDIT,IDB_BMP_EDIT);
}
void CMainFrame::init_snap_bar()
{
	//第二个工具条
	if (!snap_toolbar_.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!snap_toolbar_.LoadToolBar(IDR_TOOLBAR_SNAP))
	{
		TRACE0("Failed to create toolbar\n");
		return ;      // fail to create
	}
	snap_toolbar_.ModifyStyle(0, TBSTYLE_FLAT);
	snap_toolbar_.LoadTrueColorToolBar(TOOLBAR_DRAW_BUTTON_WIDTH,IDB_BMP_SNAP,IDB_BMP_SNAP);

	//
}
void CMainFrame::init_layer_bar()
{
	if (!layer_toolBar_.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!layer_toolBar_.LoadToolBar(IDR_TOOLBAR_LAYER))
	{
		TRACE0("Failed to create toolbar\n");
		return ;      // fail to create
	}
	layer_toolBar_.ModifyStyle(0, TBSTYLE_FLAT);
//	layer_toolBar_.LoadTrueColorToolBar(TOOLBAR_DRAW_BUTTON_WIDTH,IDB_BMP_SNAP,IDB_BMP_SNAP);

	//
}
void CMainFrame::init_entity_bar()
{
	if (!entity_toolbar_.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!entity_toolbar_.LoadToolBar(IDR_TOOLBAR_ENTITY))
	{
		TRACE0("Failed to create toolbar\n");
		return ;      // fail to create
	}
	entity_toolbar_.ModifyStyle(0, TBSTYLE_FLAT);
//	entity_toolbar_.LoadTrueColorToolBar(TOOLBAR_DRAW_BUTTON_WIDTH,IDB_BMP_SNAP,IDB_BMP_SNAP);
	
}
void CMainFrame::DockControlBarLeftOf(CToolBar *Bar,CToolBar *LeftOf)  
{  
	CRect       rect;           
	DWORD       dw;        
	UINT       n=0;        
	RecalcLayout();       
	LeftOf->GetWindowRect(&rect);        
	rect.OffsetRect(1,0);               
	dw=LeftOf->GetBarStyle();        
	n=(dw&CBRS_ALIGN_TOP)?AFX_IDW_DOCKBAR_TOP:n;        
	n=(dw&CBRS_ALIGN_BOTTOM&&n==0)?AFX_IDW_DOCKBAR_BOTTOM:n;        
	n=(dw&CBRS_ALIGN_LEFT&&n==0)?AFX_IDW_DOCKBAR_LEFT:n;        
	n=(dw&CBRS_ALIGN_RIGHT&&n==0)?AFX_IDW_DOCKBAR_RIGHT:n;        
	DockControlBar(Bar,n,&rect);        
}      
void CMainFrame::init_right_toolbar()
{
	if (!right_toolbar_.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!right_toolbar_.LoadToolBar(IDR_TOOLBAR_RIGHT))
	{
		TRACE0("Failed to create toolbar\n");
		return ;      // fail to create
	}
	right_toolbar_.ModifyStyle(0, TBSTYLE_FLAT);
//	right_toolbar_.LoadTrueColorToolBar(TOOLBAR_DRAW_BUTTON_WIDTH,IDB_BMP_CREATE,IDB_BMP_CREATE);
}

void CMainFrame::init_combo_toolbar()
{
 	if (!combo_toolbar_.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
 		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
 		!combo_toolbar_.LoadToolBar(IDR_TOOLBAR_COMBO)){
 		TRACE0("Failed to create toolbar\n");
 		return ;      // fail to create
 	}

	int index = 0;
	RECT rect;
	
	//找到指定的工具项
	while(combo_toolbar_.GetItemID(index)!=ID_TOOL_COMBO)
				index++;

	double combo_len = 150;
	combo_toolbar_.SetButtonInfo(index, ID_TOOL_COMBO, TBBS_SEPARATOR, combo_len);
	combo_toolbar_.GetItemRect(index, &rect);

	//设置位置
	rect.top+=2;
	rect.bottom += 200;
	if(!combo_toolbar_.combo_.Create(WS_CHILD|WS_VISIBLE| CBS_AUTOHSCROLL| CBS_DROPDOWNLIST | CBS_HASSTRINGS , rect, 
		&combo_toolbar_, ID_TOOL_COMBO)){
		return ;
	}
	combo_toolbar_.combo_.ShowWindow(SW_SHOW);


	//填充内容
//	combo_toolbar_.combo_.AddString("None");
//	combo_toolbar_.combo_.AddString("Dxf Import");
	combo_toolbar_.combo_.AddString("Dim");




	//取得现在的所有层名
	//选择默认项
	combo_toolbar_.combo_.SetCurSel(0);


		
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

		create_left();

	init_put_bar();

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	init_eidt_bar();
	init_snap_bar();
	init_entity_bar();
	
//	init_layer_bar();

	init_combo_toolbar();
	
//	init_right_toolbar();


	EnableDocking(CBRS_ALIGN_ANY);
	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	entity_toolbar_.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarLeftOf(&entity_toolbar_,&m_wndToolBar);


	snap_toolbar_.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarLeftOf(&snap_toolbar_,&entity_toolbar_);

	edit_toolBar_.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarLeftOf(&edit_toolBar_,&snap_toolbar_);


	//layer_toolBar_.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBarLeftOf(&layer_toolBar_,&edit_toolBar_);

	combo_toolbar_.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarLeftOf(&combo_toolbar_,&edit_toolBar_);


//	write_str_server("ap2d_version","1.0");

//	Global::instance()->db_company().download(Global::instance()->get_company_key());
	

	TRACE_OUT("init_hotkey st.\n");
	init_hotkey();
	CAp2DView::init_hotkey();
	TRACE_OUT("init_hotkey end.\n");


	TRACE_OUT("check_update st.\n");
//	if(check_update("1.0")){
//		AfxMessageBox("The version need updating,please contact REI.");
//	}
	TRACE_OUT("check_update end.\n");
	TRACE_OUT("CMainFrame end.\n");


	DB_Blocks::instance()->set_exe_path(exe_path());

	CString str = exe_path().c_str();
	Model_DB::instance()->open(str+"configure\\partlist.txt");

	DB_Font_Width_Factor::instance()->open();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
CEdit* CMainFrame::in()
{
	return put_bar_.get_in();
}
CEdit* CMainFrame::out()
{
	return put_bar_.get_out();
}

void CMainFrame::set_cur_view(std::string name)
{
/*
	View * v = Project::instance()->get_view(name);
	set_cur_view(v);
	Project::instance()->cur_view(v);

*/
	CMDIChildWnd* pActiveChild = ((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive();
	pActiveChild->SetWindowText(name.c_str());

}
void CMainFrame::create_left()
{
	
	if(left_mgr_){
		if(::IsWindow(left_mgr_->GetSafeHwnd())){
//			left_mgr_->load_tree(Global::instance()->project_info().server_key_);
			left_mgr_->ShowWindow(SW_SHOW);
			RecalcLayout();
			return ;
		}
	}
	left_mgr_ = new Left_Mgr;
	if (!left_mgr_->Create(_T("Views"), this,
		CSize(210,500), TRUE, 123)){
//			TRACE_OUT("Failed to create left_mgr_\n");
			return ;
	}
	EnableDocking(CBRS_ALIGN_ANY);
 left_mgr_->SetBarStyle(left_mgr_->GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC   );
	left_mgr_->EnableDocking(CBRS_ALIGN_LEFT   |CBRS_ALIGN_RIGHT );
	DockControlBar(left_mgr_, AFX_IDW_DOCKBAR_LEFT);
	left_mgr_->SetBorders(0,0,1000,200);
//	left_mgr_->load_tree(Global::instance()->project_info().server_key_);
	left_mgr_->ShowWindow(SW_SHOW);

}
void CMainFrame::init_put_bar()
{
  if (!put_bar_.Create(_T("My Bar"), this, 
						CSize(500,100), TRUE, 123))	//自定义标题文本
  {
      TRACE0("Failed to create mybar\n");
      return ;      // fail to create
	}
	EnableDocking(CBRS_ALIGN_ANY);

  put_bar_.SetBarStyle(put_bar_.GetBarStyle() |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC );
	put_bar_.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&put_bar_, AFX_IDW_DOCKBAR_BOTTOM);
	put_bar_.create_edit();
}

void CMainFrame::OnButSetup() 
{
	// TODO: Add your command handler code here
//	std::string
//	del_all(const_cast<char*>(Global::instance()->get_detail_db_key().c_str()),Global::instance()->ap2d());
	//删除公司信息
	del_all(const_cast<char*>(Global::instance()->get_company_key().c_str()),Global::instance()->ap2d());
	Dlg_Setting setting;
	setting.DoModal();

}

void CMainFrame::OnButOpenProjectPath() 
{
	// TODO: Add your command handler code here
	CString path = "explorer " ;
	path += afc::dir::exe_path().c_str();
	::WinExec(path,SW_SHOW); 
}

void CMainFrame::OnButNewView() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButLogin() 
{
	// TODO: Add your command handler code here
	Dlg_Login dlg;
	dlg.DoModal();
}

void CMainFrame::OnButOpenProject() 
{
	// TODO: Add your command handler code here
	Dlg_Project_Mgr dlg;
	dlg.DoModal();
	
}
void CMainFrame::open_dir_create_tree()
{
	std::string dir_path,path,file_name;
	dir_path = select_dir();
	Global::instance()->project_info().dir_path = dir_path;

	Global::instance()->db_company().set_project_path(Global::instance()->project_info().company_,Global::instance()->project_info().name_,dir_path);

/*
	if(left_mgr_){
//		left_mgr_->load_tree(dir_path);
		//2012-3-8改成文件格式
		left_mgr_->load_tree_file(dir_path);
		Global::instance()->project_info().dir_path = dir_path;

	}
*/
	DB_View::instance()->cur_view()->scene()->invalidate();

}
void CMainFrame::OnButInputDxfs() 
{
	// TODO: Add your command handler code here
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	std::string dir_path,path,file_name;
	dir_path = select_dir();
	Global::instance()->db_company().set_project_path(Global::instance()->project_info().company_,Global::instance()->project_info().name_,dir_path);
	Global::instance()->project_info().dir_path = dir_path;
	strings files;
	get_files(dir_path,"dxf",files);


	//需要上传的库清空
	Global::instance()->db_file().clear();

	for(int i=0;i<files.size();i++){

		if(!Global::instance()->db_file_date().change(files[i])){
			//TRACE_OUT("the file %s isn't changed.\n",files[i].c_str());
			continue;			
		}else{
			TRACE_OUT("the file %s is changed.\n",files[i].c_str());
		}

		TItems::iterator iter = Global::instance()->db_tree().find(files[i]);
		if(iter != Global::instance()->db_tree().end()){
			//树中存在该文件
			iter->status_ = get_dxf_status_by_file(files[i]);			
			deal_dxf(files[i]);
			Global::instance()->db_file_date().edit(files[i]);
		}else{
			//不存在时
			TItem item;
			item.name_ = files[i];
			item.parent_ = "ROOT";
			item.status_ = STATUS_EDIT;
	
			item.parent_ = Global::instance()->db_tree().get_parent(item.name_);

			deal_dxf(files[i]);
			Global::instance()->db_file_date().edit(files[i]);

			Global::instance()->db_tree().push(item);
		}
	}
	Global::instance()->db_file_date().save_std();
/*
	for(int i=0;i<files.size();i++){
		TItems::iterator iter = Global::instance()->db_tree().find(files[i]);
		if(iter != Global::instance()->db_tree().end()){
			//树中存在该文件
			iter->status_ = get_dxf_status(files[i]);			
		}else{
			//不存在时
			TItem item;
			item.name_ = files[i];
			item.parent_ = "ROOT";q
			item.status_ = STATUS_EDIT;
	
			item.parent_ = Global::instance()->db_tree().get_parent(item.name_);
			Mgr_Dxfs mgr_dxf;
			mgr_dxf.upload_dxf_by_layers(dir_path,item.name_);

			Global::instance()->db_tree().push(item);
		}
	}

	
	if(left_mgr_){
		left_mgr_->update_tree();
	}
*/
	Global::instance()->db_tree().upload(Global::instance()->get_tree_key());
	//需要上传lua层级别的
	Global::instance()->db_file().upload_ser();
	
	upload_files(Global::instance()->project_info().server_ip_,Global::instance()->get_need_upload_files_path());

	SetCursor(LoadCursor(NULL,IDC_CROSS));

}

void CMainFrame::import_dxf()
{
	open_dir_create_tree() ;
}
void CMainFrame::set_status_str(std::string info)
{
   m_wndStatusBar.SetPaneText(0,info.c_str()); 

}

void CMainFrame::OnButLoadLayer() 
{
	// TODO: Add your command handler code here
	Dlg_Layer_DB lay_db;
	lay_db.DoModal();
}
void CMainFrame::set_status_num(int num)
{
	CString s;
	s.Format("%d",num);
	
   m_wndStatusBar.SetPaneText(2,s); 
}


void CMainFrame::OnButCreateTable() 
{
	// TODO: Add your command handler code here
	CString str = exe_path().c_str();
	CString aptable = str+"aptable\\winxls.exe ";
	::WinExec(aptable,SW_SHOW); 
	
}

void CMainFrame::load_tree(std::string pro_name,std::string company_name)
{
	/*
	if(left_mgr_){
		std::string tree_ser = Global::instance()->get_tree_key();
		int num = get_key_count(const_cast<char*>(tree_ser.c_str()),const_cast<char*>(tree_ser.c_str()),Global::instance()->ap2d());
		if(num>0){
			left_mgr_->download_tree();
			Global::instance()->db_tree().show(left_mgr_->tree_);
		}else{
			AfxMessageBox("The file tree isn't exist,please import dxfs.");
			open_dir_create_tree() ;

		}
	}
*/
}

void CMainFrame::OnButSaveServer() 
{
	// TODO: Add your command handler code here
	upload_layers(DB_View::instance()->cur_view()->scene()->database());

	Global::instance()->db_tree().upload(Global::instance()->get_tree_key());
	Global::instance()->db_company().upload(Global::instance()->get_company_key());

	
}

void CMainFrame::OnButOpenServer() 
{
	// TODO: Add your command handler code here
	OnButOpenProject() ;
}
void CMainFrame::load_layers()
{
//	Global::instance()->db_layer().show(combo_toolbar_.combo_);
	Global::instance()->db_detail().show(Global::instance()->get_cur_detail_name(),combo_toolbar_.combo_);

}
std::string CMainFrame::get_layer_name()
{
	CString str;
	combo_toolbar_.combo_.GetWindowText(str);

	return str.GetBuffer(0);
}
void CMainFrame::set_combo_toolbar(int id,bool status)
{
	check(combo_toolbar_, Global::instance()->mgr_toolbar().layer_combo_,id,status);

}
void CMainFrame::OnEditchangeCombo_Tool() 
{
	// TODO: Add your control notification handler code here
	CString str;
	combo_toolbar_.combo_.GetWindowText(str);

	ApLayer aplayer;
	BOOL have = Global::instance()->db_layer().get(str.GetBuffer(0),aplayer);
	if(have)
		set_combo_toolbar(ID_TOOL_SHOW_LAYER,aplayer.show_);
	
}

void CMainFrame::OnMenuOpenProject() 
{
	// TODO: Add your command handler code here
	OnButOpenProject() ;
}

void CMainFrame::OnMenuCreateProject() 
{
	// TODO: Add your command handler code here
	OnButOpenProject() ;
	
}

void CMainFrame::OnMenuCloseProject() 
{
	// TODO: Add your command handler code here
//	left_mgr_->tree_.DeleteAllItems();
}

void CMainFrame::OnMenuAddView() 
{
	// TODO: Add your command handler code here
/*
	Dlg_Input in;
	if(in.DoModal() == IDOK){
		HTREEITEM parent = left_mgr_->tree_.GetSelectedItem();
		left_mgr_->tree_.InsertItem(in.val_.c_str(),parent);
		left_mgr_->tree_.UpdateWindow();
		
	}
	*/
}
void CMainFrame::OnMenuDeleteView() 
{
	// TODO: Add your command handler code here
	SetCursor(LoadCursor(NULL,IDC_WAIT));
/*
	HTREEITEM cur_sel = left_mgr_->tree_.GetSelectedItem();
	CString draw = left_mgr_->tree_.GetItemText(cur_sel);
	detail::delete_detail(draw.GetBuffer(0));
	left_mgr_->tree_.DeleteItem(cur_sel);	

	Global::instance()->db_tree().delete_item(draw.GetBuffer(0));

	SetCursor(LoadCursor(NULL,IDC_CROSS));
	*/
}

void CMainFrame::OnMenuEditView() 
{
	// TODO: Add your command handler code here
/*
	HTREEITEM cur_sel = left_mgr_->tree_.GetSelectedItem();
	if(cur_sel == left_mgr_->tree_.GetRootItem())
		return;
	CString old = left_mgr_->tree_.GetItemText(cur_sel);
	Dlg_Input in;
	in.str_ = old;
	if(in.DoModal()!=IDOK)
		return;
	CString view_new = in.val_.c_str();
	if(view_new == "")
		return;
	left_mgr_->tree_.SetItemText(cur_sel,view_new);
*/
}

void CMainFrame::OnButHotKey() 
{
	// TODO: Add your command handler code here
	Dlg_Hot_Key dlg;
	dlg.DoModal();

}

void CMainFrame::OnButHotKeyP() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButInLua() 
{
	// TODO: Add your command handler code here
	CString strFile,strName;
	static char szFilter[] = "file format(*.rei) |*.rei|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL );
	dlg.m_ofn.lpstrTitle = "Open File";
	if(dlg.DoModal()== IDOK){
		DB_View::instance()->cur_view()->scene()->database()->open_lua(dlg.GetPathName().GetBuffer(0),DB_View::instance()->cur_view()->scene()->database());
	}
	DB_View::instance()->cur_view()->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(0,0));

}

void CMainFrame::OnButOutLua() 
{
	// TODO: Add your command handler code here
	CString strFile,strName;
	static char szFilter[] = "lua file format (*.rei)|*.rei|All Files (*.*)|*.*||";
	
	CFileDialog dlg(FALSE, _T(".rei"), Global::instance()->dxf_name(), OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL);
	dlg.m_ofn.lpstrTitle = "Save File";
	if(dlg.DoModal()== IDOK){
		DB_View::instance()->cur_view()->scene()->database()->save_lua(dlg.GetPathName().GetBuffer(0));
		Global::instance()->is_eidt_ = false;
	}	
	
}

void CMainFrame::OnButInLuaP() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButOutLuaP() 
{
	// TODO: Add your command handler code here
	
}
bool CMainFrame::hotkey(MSG* pMsg)
{
	if(!::IsWindow(GetSafeHwnd())){
		return false;
	}
	if(pMsg->message == WM_KEYDOWN){
    hk::Fptr<CMainFrame>::PF pf = hk::find<CMainFrame>(pMsg->wParam);
    if(pf){
      (this->*pf)();
      return true;
    }
  }
  return false;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
  if(hotkey(pMsg)){
    return TRUE;
  }
	if(pMsg->message == WM_KEYDOWN){
//		put_bar_.SetFocus();
	}
	
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}
void CMainFrame::show_list_report(Group_Txts &group_txts) 
{
	//left_mgr_->show_reports(group_txts);
}
void CMainFrame::show_same_list_report(Group_Txts &group_txts)
{
	//left_mgr_->show_same_reports(group_txts);
}

void CMainFrame::OnButCompareXsteel() 
{
	// TODO: Add your command handler code here
	CString str = exe_path().c_str();
	CString aptable = str+"apcheck\\check.exe";
//	::WinExec(aptable,SW_SHOW); 
	::ShellExecute(NULL, "open", aptable, "", "", SW_SHOW);
	
}

void CMainFrame::OnButCompareXsteelP() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::init_hotkey()
{

  hk::push_sec("Project");

  hk::push_key("Open Project", &CMainFrame::OnButOpenProject, 'M', true);
  hk::push_key("Login", &CMainFrame::OnButLogin);
  hk::push_key("Input Dxfs", &CMainFrame::OnButInputDxfs);

 // hk::push_key("Hot Key", &CMainFrame::OnButHotKey);
  hk::push_key("Lua in", &CMainFrame::OnButInLua);
  hk::push_key("Lua out", &CMainFrame::OnButOutLua);

  
  hk::load(Global::instance()->get_hotkey_profile().c_str());
  hk::enable(false);

}

void CMainFrame::OnButFileMamage() 
{
	// TODO: Add your command handler code here
	Dlg_File_Mgr dlg;
	dlg.DoModal();
}

void CMainFrame::OnBUTFILEMAMAGEp() 
{
	// TODO: Add your command handler code here
	
}

CString CMainFrame::get_path_dlg()
{
	CString m_FileDir;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = m_hWnd;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	BOOL bRet = FALSE;
	TCHAR szFolder[MAX_PATH*2];
	szFolder[0] = _T('\0');
	if (pidl){
		if (SHGetPathFromIDList(pidl, szFolder))
			bRet = TRUE;
			IMalloc *pMalloc = NULL;
			if (SUCCEEDED(SHGetMalloc(&pMalloc))&& pMalloc){
				pMalloc->Free(pidl);
				pMalloc->Release();
			}
		}
	m_FileDir = szFolder;//选择的文件夹路径
	return m_FileDir;
}

void CMainFrame::OnMenuOpenProjectCheck() 
{
	// TODO: Add your command handler code here
//	std::string path = select_dir();
	Dlg_Project_Paths_Save dlg;
	int nstate = dlg.DoModal();
	if (nstate == IDOK){
		CString cur_sel_path = dlg.get_dir();
		if ( cur_sel_path.Compare("") != 0 ){
			//cur_sel_path = cur_sel_path  + "\\";
			if ( cur_sel_path.Find(":") > 0 )
				left_mgr_->load_tree(LPCSTR(cur_sel_path));
		}
		
	}	
}

void CMainFrame::OnMenuCreateProjectCheck() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuCloseProjectCheck() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuSetComplateCheck() 
{
	// TODO: Add your command handler code here
	
	left_mgr_->set_complate();
}

void CMainFrame::OnMenuSetComplateCheckP() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuUpdate() 
{
	// TODO: Add your command handler code here
	left_mgr_->update_tree();
	
}

void CMainFrame::OnMenuCreateDxf() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuSave()
{
	DB_Font_Width_Factor::instance()->save();
	Global::instance()->is_eidt_ = false;
	CString cur_states = left_mgr_->save_as_cur_view(left_mgr_->get_pos());
	if ( cur_states.Compare("") != 0)
		DB_View::instance()->cur_view()->scene()->database()->save_lua(cur_states.GetBuffer(0));


}

void CMainFrame::OnMenuSetErrorCheckP()
{
	left_mgr_->set_error();
}
void CMainFrame::OnMenuClearStatus()
{
	left_mgr_->clear_status();
}


void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	DB_Font_Width_Factor::instance()->save();

	if(Global::instance()->is_eidt_)
	{
		int res = MessageBox("Please Save the file.","Close the file",MB_YESNO);
		if(res == IDYES)
		{
			return;

		}
	}
	CMDIFrameWnd::OnClose();
}
