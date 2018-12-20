// Left_Mgr.cpp: implementation of the Left_Mgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Left_Mgr.h"

#include "mgr_dxfs.h"
#include "Mgr_File.h"
#include "DB_Detail.h"
#include "Global.h"
#include "MainFrm.h"
#include "Mgr_Detail.h"

#include "Mgr_File.h"
#include "DB_View.h"
#include "Mgr_Database.h"
#include "Mgr_Lua.h"
#include "getrace.h"

#include<shlwapi.h>
#include "Dxf_Read.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

save_file::save_file()
{

}

save_file::~save_file()
{

}

Left_Mgr::Left_Mgr()
{

}

Left_Mgr::~Left_Mgr()
{

}

BEGIN_MESSAGE_MAP(Left_Mgr, CBetterBar)
	//{{AFX_MSG_MAP(CMyBar)
	ON_WM_CREATE()
	ON_NOTIFY(NM_DBLCLK, 0x1005, OnDblclkTree)
	ON_NOTIFY(NM_RCLICK, 0x1005, OnRClick)
	ON_COMMAND(ID_MENU_IMPORT_DXF, OnMenuImportDxf)	
	ON_NOTIFY(NM_CLICK, 0x1005, OnClickTree)
	ON_COMMAND(ID_MENU_SET_COMPLATE, OnMenuSetComplate)
	ON_NOTIFY(NM_DBLCLK, 0x1006, OnDblclkLists)
	ON_NOTIFY(NM_DBLCLK, 0x1006, OnDblclkListSames)
	//ON_COMMAND(0x1005, OnDbclickTree)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void Left_Mgr::create_views_page()
{
	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);
	tree_.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD  | WS_BORDER |WS_CLIPSIBLINGS        
	   | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES |WS_THICKFRAME|TVS_SHOWSELALWAYS,
	   CRect(10, 10, 300, 100), &tab_ctrl_, 0x1005);
	images_.Create(16, 16, ILC_COLORDDB | ILC_MASK, 0, 1);
	CBitmap general,current,open,project,change,error;

	general.LoadBitmap(IDB_GENERAL);
	change.LoadBitmap(IDB_CHANGE);
	

	current.LoadBitmap(IDB_CURRENT);
	open.LoadBitmap(IDB_OPEN);
	project.LoadBitmap(IDB_PROJECT);
	error.LoadBitmap(IDB_BMP_ERROR);
	images_.Add(&general, RGB(192, 192, 192));
	images_.Add(&change, RGB(192, 192, 192));
	images_.Add(&project, RGB(192, 192, 192));
	images_.Add(&error, RGB(192, 192, 192));

/*

	images_.Add(&current, RGB(192, 192, 192));
	images_.Add(&open, RGB(192, 192, 192));
	images_.Add(&project, RGB(192, 192, 192));
*/
	tree_.SetImageList(&images_, TVSIL_NORMAL);



//	Model::instance()->show(tree_);
}
void Left_Mgr::create_list_page()
{
	list_ctrl_.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|
		LVS_SHOWSELALWAYS|LVS_ALIGNTOP |LVS_SORTASCENDING|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT        ,
		CRect(10, 10, 300, 100), &tab_ctrl_, 0x1006);
	CString heads;
	long lExStyleOld = list_ctrl_.GetExtendedStyle();
	list_ctrl_.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	heads.Format("%s,30;%s,50;%s,60;%s,60;","ID","Text" ,"File_0","File_1");
	list_ctrl_.set_headings(_T(heads));


}
void Left_Mgr::create_same_list_page()
{
	same_list_ctrl_.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|
		LVS_SHOWSELALWAYS|LVS_ALIGNTOP |LVS_SORTASCENDING        ,
		CRect(10, 10, 300, 100), &tab_ctrl_, 0x1006);
	CString heads;
	long lExStyleOld = list_ctrl_.GetExtendedStyle();
	same_list_ctrl_.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	heads.Format("%s,30;%s,50;%s,60;%s,60;","ID","Text" ,"File_0","File_1");
	same_list_ctrl_.set_headings(_T(heads));


}

int Left_Mgr::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBetterBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	tab_ctrl_.Create(TCS_DOWN|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),this,125);

	create_views_page();

	create_list_page();
	create_same_list_page();

	tab_ctrl_.AddPage(&tree_,"Project",IDI_ICON1);
	tab_ctrl_.AddPage(&list_ctrl_,"Diff",IDI_ICON2);
	tab_ctrl_.AddPage(&same_list_ctrl_,"Same",IDI_ICON2);
	tab_ctrl_.UpdateWindow();
/*
	create_mems_page();
	create_props_page();
	init_column();
	tab_ctrl_.AddPage(&tree_,"Views",IDI_ICON1);
	tab_ctrl_.AddPage(&mems_list_,"Mems",IDI_ICON2);
	tab_ctrl_.AddPage(&prop_list_,"Prop",IDI_ICON4);
	tab_ctrl_.UpdateWindow();
*/


	return 0;
}

/*
void Left_Mgr::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	DB_View::instance()->cur_view()->scene()->database()->clear_entity();
	//新方法
//	download_layers(Global::instance()->layer_info(),DB_View::instance()->cur_view()->scene()->database());

	
	//下载所有层。
//	Mgr_Dxfs mgr_dxf;
//	mgr_dxf.download_dxf_by_layers(Global::instance()->get_cur_detail_name());

	download_luas(Global::instance()->get_cur_detail_name());

//	Global::instance()->db_layer().download(Global::instance()->get_detail_layers_key(Global::instance()->get_cur_detail_name()));
//	download_layers(Global::instance()->db_layer(),DB_View::instance()->cur_view()->scene()->database());


	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->load_layers();
	

	DB_View::instance()->cur_view()->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(0,0));
	DB_View::instance()->cur_view()->scene()->invalidate();
	SetCursor(LoadCursor(NULL,IDC_CROSS));

	*pResult = 0;
}
*/



void Left_Mgr::create_tree_by_dxf(std::string dir_path,strings &files)
{
//	ap2d::load_tree(tree_);
	Mgr_Dxfs mgr_dxfs;
	TItem item;
	Global::instance()->db_detail().download(Global::instance()->get_detail_db_key());

	
	for(int i=0;i<files.size();i++){
		Detail detail;
		//新的方式，计算hash值和上传dxf分开。
		//mgr_dxfs.get_hash_val(dir_path,files[i],detail);
		mgr_dxfs.get_hash_val_new(dir_path,files[i],detail);
		if(!Global::instance()->db_detail().is_have(Global::instance()->get_detail_db_key())){
			Global::instance()->db_detail().push(detail);
			//新的需要上传
			mgr_dxfs.upload_dxf_by_layers(dir_path,files[i]);
		}
		item.name_ = files[i].c_str();
		item.parent_ = "ROOT";
		item.status_ = STATUS_EDIT;
		Global::instance()->db_tree().push(item);

		//tree_.InsertItem(dir_path,TVI_ROOT);
	 	
		if(Global::instance()->db_detail().is_change(detail)){
			item.name_ = files[i].c_str();
			item.parent_ = "ROOT";
			item.status_ = STATUS_EDIT;
			Global::instance()->db_tree().push(item);
			tree_.InsertItem(_T(files[i].c_str()),STATUS_EDIT,STATUS_EDIT);	
			//新的需要上传
			mgr_dxfs.upload_dxf_by_layers(dir_path,files[i]);
		}else{
			item.name_ = files[i].c_str();
			item.parent_ = "ROOT";
			item.status_ = STATUS_CHANGE;
			Global::instance()->db_tree().push(item);
			tree_.InsertItem(_T(files[i].c_str()),STATUS_CHANGE,STATUS_CHANGE);	
		}
	}

	Global::instance()->db_detail().upload(Global::instance()->get_detail_db_key());

}



void Left_Mgr::load_tree(std::string dir_path)
{
	file_path_ = dir_path.c_str();
	tree_.DeleteAllItems();
	strings files;
	//get_files(dir_path,"dxf",files);
	BrowseCurrenPathtAllTypeFile(dir_path,"dxf",files,dir_path);
	CString change_str =  file_path_;
	int cur_strlen = change_str.GetLength();
	change_str = change_str.Left(cur_strlen-1);
	//create_tree_by_dxf(dir_path,files);
	int var = 0;
	int save_var = 0;
	while (var >= 0){
		var = change_str.Find("\\",var+1);
		if ( var < 0 )
			break;
		save_var = var;
	}
	if ( save_var == 0 )
			change_str = dir_path.c_str();
	else
		change_str =	change_str.Right(cur_strlen - 1 - save_var - 1);
	create_tree_by_dxf_new(LPCSTR(change_str),files);
	/*
	strings files;
	get_files(dir_path,"dxf",files);
	//此处应该有三个状态
	//1、服务器上有保存树的结构，此时利用服务器上的树生成。
	//2、服务器上没有树，但本地有生成树的规则文件“tree_rules.txt”，按照它生成树。
	//3、上面两项都不存在时，利用dxf文件夹下的层生成树。

	download_tree();
	int size = Global::instance()->db_tree().size();
	if(size>0){
		Global::instance()->db_tree().show(tree_);
	}else if(judge_if_have_file(exe_path().c_str(),"tree_rules.txt")){
		Global::instance()->db_tree().create(files);
		Global::instance()->db_tree().show(tree_);
		//因为此树没有生成，所以所有图纸都是新的，都需要上传到服务器中，
		//包含hash值和图纸信息
		upload_new_dxfs(dir_path,files);
	}else{
		create_tree_by_dxf(dir_path,files);

	}
	*/
}

void Left_Mgr::download_tree()
{
	TRACE_OUT("Left_Mgr::download_tree start .\n");
	Global::instance()->db_tree().download(Global::instance()->get_tree_key());
	TRACE_OUT("Left_Mgr::download_tree end .\n");

}
void Left_Mgr::upload_tree()
{
//	Global::instance()->db_tree().create_data(tree_);
	//Global::instance()->db_tree().upload(Global::instance()->get_tree_key());

}
void Left_Mgr::OnRClick(NMHDR* pNMHDR, LRESULT* pResult)
{

	RECT r;
	tree_.GetWindowRect(&r);
	POINT pt;	
	GetCursorPos(&pt);
	tree_.ScreenToClient(&pt);
//	if(!PtInRect(&r,pt))
//		return;

	CMenu menu;  
	menu.LoadMenu(IDR_MENU_TREE_CHECK); 
	CMenu* pMenu=menu.GetSubMenu(0);
	tree_.ClientToScreen(&pt);

	pMenu->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this); 


	*pResult = 0;
}
void Left_Mgr::OnMenuImportDxf()
{
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->import_dxf();
	
}
void Left_Mgr::OnClickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM cur_sel = tree_.GetSelectedItem();
	CString name = tree_.GetItemText(cur_sel);

//	merge_detail(name.GetBuffer(0));
//	if(strcmp(name,"")==0){
//		AfxMessageBox("the Tree's Item isn't selected!");
//		return ;
//	}
		
	std::string info = Global::instance()->db_detail().change_info(name.GetBuffer(0));
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->set_status_str(info);

}
void Left_Mgr::OnMenuSetComplate() 
{
	// TODO: Add your command handler code here
	HTREEITEM cur_sel = tree_.GetSelectedItem();
	CString name = tree_.GetItemText(cur_sel);
	tree_.SetItemImage(cur_sel,STATUS_COMPLATE,STATUS_COMPLATE);
	Global::instance()->db_tree().change_status(name.GetBuffer(0),STATUS_COMPLATE);
}


void Left_Mgr::load_tree_file(std::string dir_path)
{

	tree_.DeleteAllItems();
	strings files;
	get_files(dir_path,"dxf",files);
	//此处应该有三个状态
	//1、服务器上有保存树的结构，此时利用服务器上的树生成。
	//2、服务器上没有树，但本地有生成树的规则文件“tree_rules.txt”，按照它生成树。
	//3、上面两项都不存在时，利用dxf文件夹下的层生成树。

	TRACE_OUT("The files size =  %d\n", files.size());
//	TRACE_OUT("The start time =  %s\n", get_current_time().c_str());
	DWORD start_time = GetTickCount();

	
	download_tree();

	int size = Global::instance()->db_tree().size();
	if(size>0){
		Global::instance()->db_tree().show(tree_);
	}else if(judge_if_have_file(exe_path().c_str(),"tree_rules.txt")){
		Global::instance()->db_tree().create(files);
		Global::instance()->db_tree().show(tree_);
		//因为此树没有生成，所以所有图纸都是新的，都需要上传到服务器中，
		//包含hash值和图纸信息
		deal_new_dxfs(dir_path,files);
	}else{
		create_tree_by_dxf(dir_path,files);

	}
	Global::instance()->db_file_date().push(files);
//	Global::instance()->db_file_date().save();
	Global::instance()->db_file_date().save_std();

	DWORD end_time = GetTickCount();
	int time = end_time-start_time;
	TRACE_OUT("the times =  %d ms.\n",time);
	
//	TRACE_OUT("The end time =  %s\n", get_current_time().c_str());
}
void Left_Mgr::OnDblclkLists(NMHDR* pNMHDR, LRESULT* pResult)
{
	strings sel_strs;
	list_ctrl_.get_select_rows(sel_strs,1);
	if(sel_strs.size()>0)
		show_text(DB_View::instance()->cur_view()->scene()->database(),sel_strs[0]);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->MDIGetActive()->GetActiveView()->SetFocus();
}

void Left_Mgr::OnDblclkListSames(NMHDR* pNMHDR, LRESULT* pResult)
{
	strings sel_strs;
	same_list_ctrl_.get_select_rows(sel_strs,1);
	if(sel_strs.size()>0)
		show_text(DB_View::instance()->cur_view()->scene()->database(),sel_strs[0]);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->MDIGetActive()->GetActiveView()->SetFocus();
}

void Left_Mgr::show_reports(Group_Txts &group_txts)
{
	list_ctrl_.DeleteAllItems();
	CString id,txt,file0,file1;
	for(int i=0;i<group_txts.size();i++){
		id.Format("%d",i);
		txt.Format("%s",group_txts[i].txt_.c_str());
		file0.Format("%d",group_txts[i].count_0_);
		file1.Format("%d",group_txts[i].count_1_);
		list_ctrl_.add_item(_T(id),_T(txt),_T(file0),_T(file1));		
	}

}
void Left_Mgr::show_same_reports(Group_Txts &group_txts)
{
	same_list_ctrl_.DeleteAllItems();
	CString id,txt,file0,file1;
	for(int i=0;i<group_txts.size();i++){
		id.Format("%d",i);
		txt.Format("%s",group_txts[i].txt_.c_str());
		file0.Format("%d",group_txts[i].count_0_);
		file1.Format("%d",group_txts[i].count_1_);
		same_list_ctrl_.add_item(_T(id),_T(txt),_T(file0),_T(file1));		
	}

}

//void Left_Mgr::OnDbclickTree(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	AfxMessageBox("here");
//	*pResult = 0;
//}

//--------------------------------------------------------------------------sjy change -----------------------------------------



void Left_Mgr::travel_tree_node(HTREEITEM item,int status,CString & str)
{

	if (tree_.ItemHasChildren(item)){
		HTREEITEM hChildItem = tree_.GetChildItem(item);   
		while (hChildItem != NULL){
			if (str.Find("\\") > 0 ){
				CString temp_str = str.Left(str.Find("\\"));
				if ( tree_.GetItemText(hChildItem).Compare(temp_str) == 0 ){
						str.Replace(temp_str+"\\",NULL);
						travel_tree_node(hChildItem,status,str);
						break;
				}   
			}
			else
			{
				if ( tree_.GetItemText(hChildItem).Compare(str) == 0 ){
					tree_.SetItemImage(hChildItem,status,status);
					break;
				}
			}
		hChildItem = tree_.GetNextItem(hChildItem, TVGN_NEXT);   
		}
	}
}

void Left_Mgr::init_tree_sel(int status)
{	
	HTREEITEM root_item = tree_.GetRootItem( );
	CString path_str = Global::instance()->dxf_name(); 
	travel_tree_node(root_item,status,path_str);
}

void Left_Mgr::get_tree_all_path(HTREEITEM item,CString & FileName)
{
	HTREEITEM parent_item = tree_.GetParentItem(  item );
	FileName = tree_.GetItemText( parent_item ) + "\\" + FileName;
	if (tree_.GetParentItem(  parent_item  ) ){
		get_tree_all_path( parent_item,FileName);
	}
	else 
		FileName.Replace(tree_.GetItemText(tree_.GetRootItem()) + "\\",NULL);
}

void Left_Mgr::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	HTREEITEM hitem = tree_.GetSelectedItem();
	CString FileName = tree_.GetItemText(hitem);
	get_tree_all_path(hitem,FileName);
	if (FileName.Right(4).Compare(".dxf") == 0 ){
	DB_View::instance()->cur_view()->scene()->database()->clear_entity();
	int states = 0;
	int save_i = 0;
	for (int i = 0; i < files_db_.size(); i++ ){
		if (FileName.Compare(files_db_[i].file_name_) == 0 ){
			states = files_db_[i].file_status_;
			save_i = i;
			break;
		}
	}
	Global::instance()->dxf_name() = FileName;
	FileName = file_path_ + FileName;
		if ( states > 0 ){
			FileName = FileName.Left(FileName.GetLength() - 4);
			
			FileName = FileName + ".rei";
			if (PathFileExists(FileName)){
				DB_View::instance()->cur_view()->scene()->database()->open_lua(FileName.GetBuffer(0),DB_View::instance()->cur_view()->scene()->database());
			}
			else{
				FileName = file_path_ + Global::instance()->dxf_name();
				files_db_[save_i].file_status_ = STATUS_EDIT;
				save_file_fun();
				load_tree(LPCSTR(file_path_));
				Dxf_Read dxf_read;
				dxf_read.read(FileName.GetBuffer(0),DB_View::instance()->cur_view()->scene());
			}
			DB_View::instance()->cur_view()->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(100,100));
		}
		else{
				Dxf_Read dxf_read;
				dxf_read.read(FileName.GetBuffer(0),DB_View::instance()->cur_view()->scene());
				DB_View::instance()->cur_view()->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(100,100));
		}
		
		DB_View::instance()->cur_view()->scene()->invalidate();
	
	}

	*pResult = 0;
}

void 	Left_Mgr::deal_files_Data( )
{
	files_db_.clear();
	CString file_ifo = file_path_;
	file_ifo = file_ifo	+ "save_dxf_ifo.txt";
	CStdioFile file_open;

	if( !file_open.Open( file_ifo, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead | CFile::typeText ) ) {
	 #ifdef _DEBUG
     afxDump << "Unable to open file" << "\n";
		#endif
	 exit( 1 );
	}
	CString temp_str;
	while(file_open.ReadString(temp_str)){
		if (temp_str.Find("=") > 0 ){
			save_file file;
			temp_str.Left(temp_str.Find("="));
			file.file_name_ = temp_str.Left(temp_str.Find("="));
			file.file_name_.TrimRight();
			CString temp_states_str;
			temp_states_str = temp_str.Right(temp_str.GetLength() - temp_str.Find("=") - 1);
			temp_states_str.TrimLeft();
			file.file_status_ = atoi(temp_states_str);
			if 	( file.file_status_ > 0 ){
				CString CurFileName = file_path_ + file.file_name_;
				CurFileName = CurFileName.Left(CurFileName.Find(".dxf"));
				CurFileName = CurFileName + ".rei";
				if (!PathFileExists(CurFileName))
					file.file_status_ = 0;
			}
			if (PathFileExists(file_path_ + file.file_name_))
				files_db_.push_back(file);
		}
	}
	file_open.Close();
}

void Left_Mgr::save_file_fun()
{
	CStdioFile file_open;
	CString file_ifo = file_path_;
	file_ifo = file_ifo	+ "save_dxf_ifo.txt";
	if( !file_open.Open( file_ifo, CFile::modeCreate | CFile::modeWrite | CFile::typeText ) ) {
	 #ifdef _DEBUG
     afxDump << "Unable to open file" << "\n";
		#endif
	 exit( 1 );
	}
	for (int i = 0; i < files_db_.size(); i++ ){
		file_open.WriteString(files_db_[i].file_name_);
		file_open.WriteString("    =    ");
		CString temp_str;
		temp_str.Format("%d",files_db_[i].file_status_);
		file_open.WriteString(temp_str);
		file_open.WriteString("\n");
	}
	file_open.Close();

}
//递归处理树的每一层级
void 	Left_Mgr::deal_floder(CString filename,int file_status,HTREEITEM hCountry)
{
	if ( filename.Find("\\") >= 0 ){
		int pos = filename.Find("\\");
		std::string temp_name = filename.Left(pos); //获得当前层级节点名字
		CString next_file;
		HTREEITEM hCountry_NEW = hCountry;
		int states = 0;
	
			HTREEITEM hNextItem;
			HTREEITEM hChildItem = tree_.GetChildItem(hCountry); 
			hNextItem = hChildItem;
			while (hChildItem != NULL)
			{
				
				CString temp_str = tree_.GetItemText( hNextItem );
				if ( temp_str.Compare(temp_name.c_str()) == 0){
					states = 1;
					hCountry_NEW = hNextItem;
					break;
				}
				hNextItem = tree_.GetNextItem(hChildItem, TVGN_NEXT);
				hChildItem = hNextItem;
			}
		if ( states != 1 ){
				TVINSERTSTRUCT NewTvInsert;
				NewTvInsert.hParent = hCountry;
				NewTvInsert.hInsertAfter = NULL;
				NewTvInsert.item.mask = TVIF_TEXT;
				NewTvInsert.item.pszText =  (char*)temp_name.c_str();
				hCountry_NEW = tree_.InsertItem(&NewTvInsert);
		}
		next_file = filename.Right(filename.GetLength() - pos - 1);
		deal_floder(next_file,file_status, hCountry_NEW);
	}
	else 
		tree_.InsertItem(_T(filename),file_status, file_status, hCountry,NULL);	
}

void Left_Mgr::create_tree_by_dxf_new(std::string name ,strings &files)
{
	
	Mgr_Dxfs mgr_dxfs;
	TItem item;
	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = (char*)name.c_str();
	HTREEITEM hCountry = tree_.InsertItem(&tvInsert);
	deal_files_Data();
	int i = 0;
	if ( files_db_.size() != 0 ){
		for(i=0;i<files.size();i++){
			int states = 0;
			for (int j = 0; j < files_db_.size() ; j++ ){
				if (files_db_[j].file_name_.Compare(files[i].c_str()) == 0){
					deal_floder(files[i].c_str(),files_db_[j].file_status_,hCountry);
					states = 1;
					break;
				}
			}
			if ( states < 1 ){
				save_file file;
				file.file_name_ = files[i].c_str();
				file.file_status_ = STATUS_EDIT;
				files_db_.push_back(file);
				deal_floder(files[i].c_str(),STATUS_EDIT,hCountry);
			}
		}
	}
	else{
		for(i=0;i<files.size();i++){
			save_file file;
			file.file_name_ = files[i].c_str();
			file.file_status_ = STATUS_EDIT;
			files_db_.push_back(file);
			deal_floder(files[i].c_str(),STATUS_EDIT,hCountry);
// 			item.name_ = files[i].c_str();
//			item.parent_ = "ROOT";
//			item.status_ = STATUS_EDIT;
// 			Global::instance()->db_tree().push(item);
		}	
	}
}



void Left_Mgr::set_complate()
{
//	HTREEITEM hItem = tree_.GetSelectedItem();
//	CString get_sel_item = tree_.GetItemText(hItem);
//	get_tree_all_path(hItem,get_sel_item);
	int save_i = -1;
	if (Global::instance()->dxf_name().Compare("") != 0 ){
		for (int i = 0 ; i < files_db_.size() ; i++ ){
			if ( files_db_[i].file_name_.Compare(Global::instance()->dxf_name()) == 0 ){
				files_db_[i].file_status_ = STATUS_COMPLATE;
				save_i = i;
				break;
			}
		}
		CString cur_states = save_as_cur_view(save_i);
		if ( cur_states.Compare("") != 0)
			DB_View::instance()->cur_view()->scene()->database()->save_lua(cur_states.GetBuffer(0));
	}
	else
		message();

	
}
void Left_Mgr::update_tree()
{
	//Global::instance()->db_tree().show(tree_);
	if (file_path_.Compare("") != 0){
		load_tree(LPCSTR(file_path_));
		save_file_fun();
	}
}



int Left_Mgr::get_pos()
{
	int pos = -1;
	if ( Global::instance()->dxf_name().Compare("") == 0 )
		message();
	if (file_path_.Compare("") != 0 && Global::instance()->dxf_name().Compare("") != 0 ){
		for (int i = 0 ; i < files_db_.size() ; i++ ){
			if ( files_db_[i].file_name_.Compare(Global::instance()->dxf_name()) == 0 ){
				pos = i;
				break;
			}
		}
	}
	return pos;
}

CString Left_Mgr::save_as_cur_view(int pos)
{
	CString FileName = "";
	if (pos >= 0 ){
		FileName = file_path_ + Global::instance()->dxf_name();
		if ( FileName.Right(4).Compare(".dxf") == 0 ){
			FileName = FileName.Left(FileName.GetLength() - 4);
			FileName = FileName + ".rei";
		//	DB_View::instance()->cur_view()->scene()->database()->save_lua(FileName.GetBuffer(0));
			if ( files_db_[pos].file_status_ < 1 )
				files_db_[pos].file_status_ = STATUS_CHANGE;
			save_file_fun();
			init_tree_sel(files_db_[pos].file_status_);
		}
	}
	return FileName;
}

void Left_Mgr::set_error()
{
	int save_i = -1;
	if (Global::instance()->dxf_name().Compare("") != 0 ){
		for (int i = 0 ; i < files_db_.size() ; i++ ){
			if ( files_db_[i].file_name_.Compare(Global::instance()->dxf_name()) == 0 ){
				files_db_[i].file_status_ = STATUS_ERROR;
				save_i = i;
				break;
			}
		}
		CString cur_states = save_as_cur_view(save_i);
		if ( cur_states.Compare("") != 0)
			DB_View::instance()->cur_view()->scene()->database()->save_lua(cur_states.GetBuffer(0));
	}
	else
		message();
}
void Left_Mgr::clear_status()
{
	CString FileName;
	if (Global::instance()->dxf_name().Compare("") != 0 ){
		FileName = file_path_ + Global::instance()->dxf_name();
		FileName = FileName.Left(FileName.GetLength() - 4);
		FileName = FileName + ".rei";
		if (PathFileExists(FileName)){
			SetFileAttributes(FileName,FILE_ATTRIBUTE_NORMAL); 
			DeleteFile(FileName);
		}
		for (int i = 0 ; i < files_db_.size() ; i++ ){
			if ( files_db_[i].file_name_.Compare(Global::instance()->dxf_name()) == 0 ){
				files_db_[i].file_status_ = STATUS_EDIT;
				
				save_file_fun();
				init_tree_sel(	files_db_[i].file_status_);
				break;
			}
		}
	}
	else
		message();
}

void Left_Mgr::message()
{
	if ( Global::instance()->dxf_name().Compare("") == 0 )
		AfxMessageBox("Please import a dxf file");
}


