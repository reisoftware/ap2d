// View_Tree.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "View_Tree.h"

#include "Dlg_Layer_DB.h"
#include "Global.h"
#include "DB_View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// View_Tree

static bool set_view_focus()
{
/*
	CMainFrame * mainframe = static_cast<CMainFrame*>(AfxGetMainWnd());

	CMDIChildWnd * pChild = static_cast<CMDIChildWnd*>(mainframe->GetActiveFrame());
	TRACE_OUT("\n#### CMDIChildWnd ptr: %d\n", pChild);
	if(!pChild){
		return false;
	}
	CAp2dView * apv = static_cast<CAp2dView*>(pChild->GetActiveWindow());
	assert(apv && "Views_Mgr::OnDblclkTree(), apv is mustn't null");
	
	apv->SetFocus();
*/
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// View_Tree

View_Tree::View_Tree()
{
}

View_Tree::~View_Tree()
{
}


BEGIN_MESSAGE_MAP(View_Tree, CTreeCtrl)
	//{{AFX_MSG_MAP(View_Tree)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// View_Tree message handlers
void View_Tree::selected(CString &cur,CString &parent)
{
	HTREEITEM sel = GetSelectedItem();
	HTREEITEM par = GetParentItem(sel);
	if(par == NULL)
		 parent = "";
	else
		 parent = GetItemText(par);
	cur =  GetItemText(sel);
}

void View_Tree::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HTREEITEM sel_item = GetSelectedItem();
	CString sel_name = GetItemText(sel_item);
	Global::instance()->get_cur_detail_name() = sel_name;


//	DB_View::instance()->cur_view()->scene()->database()->clear_entity();
//	download_layers(Global::instance()->layer_info(),DB_View::instance()->cur_view()->scene()->database());

/*
	Dlg_Layer_DB layer_db;
	if(layer_db.DoModal() == IDOK){
		strings layers;
		layer_db.get_select_layers(layers);
		//merge_layers(layers,sel_name);
	}
*/
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
	set_view_focus();

}
void View_Tree::get_parents(HTREEITEM cur,std::vector<std::string> &parents)
{
	if(cur == NULL)
		return ;
 	CString txt = GetItemText(cur);
	parents.push_back(txt.GetBuffer(0));
	HTREEITEM parent = GetParentItem(cur);
	while(parent != NULL){
		txt = GetItemText(parent);
		parents.push_back(txt.GetBuffer(0));
		parent = GetParentItem(parent);
	}
}
HTREEITEM View_Tree::get_uncle_item(HTREEITEM item)
{
  HTREEITEM parent = NULL;
  HTREEITEM uncle  = NULL;
  parent = GetParentItem(item);
  if(parent){
    uncle = GetNextSiblingItem(parent);
  }
  return uncle;
}

HTREEITEM View_Tree::get_next_item(HTREEITEM item)
{
  if(!item){
    return GetFirstVisibleItem();
  }
  HTREEITEM child   = NULL;
  HTREEITEM sibling = NULL;
  HTREEITEM uncle   = NULL;
  child = GetChildItem(item);
  if(child){
    return child;
  }
  sibling = GetNextSiblingItem(item);
  if(sibling){
    return sibling;
  }
  uncle = get_uncle_item(item);
  if(uncle){
    return uncle;
  }
  return NULL;
}

HTREEITEM View_Tree::begin()
{
  return get_next_item(NULL);
}
HTREEITEM View_Tree::end()
{
  return NULL;
}
HTREEITEM View_Tree::next(HTREEITEM item)
{
  return get_next_item(item);
}

HTREEITEM View_Tree::get_item(std::string name)
{
  HTREEITEM it = begin();
  for(; it != end(); it=next(it)){
    if(GetItemText(it) == name.c_str()){
      return it;
    }
  }
  return NULL;
}


void View_Tree::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 	HTREEITEM cur_sel = GetSelectedItem();
//	SetItemState(cur_sel, TVIS_BOLD, TVIS_BOLD);	

	CTreeCtrl::OnRButtonDown(nFlags, point);
}
void View_Tree::create_paths(strings &all_paths)
{
	HTREEITEM root = GetRootItem();
	std::string s;
//	travel_tree(root,TVIS_BOLD,s);

	expand_nodes(NULL,TRUE,s);
	all_paths = all_paths_;


}

void View_Tree::travel_tree(HTREEITEM hItem, UINT  nState,std::string &path) 
{ 
	CString name;
	HTREEITEM   hChildItem,hBrotherItem; 
	//查找子节点，没有就结束 
	hChildItem=GetChildItem(hItem); 
	name = GetItemText(hItem);
	path += name;
	path += ":";
	if(hChildItem!=NULL){ 
	 	name = GetItemText(hChildItem);
		path += name;
		path += ":";
		std::string brother = path;
		//设置子节点的状态与当前节点的状态一致 
		CTreeCtrl::SetItemState(hChildItem,INDEXTOSTATEIMAGEMASK(nState),TVIS_STATEIMAGEMASK); 
		//再递归处理子节点的子节点和兄弟节点 
		travel_tree(hChildItem,nState,path); 
		//处理子节点的兄弟节点和其子节点 
		hBrotherItem=GetNextSiblingItem(hChildItem); 
		while(hBrotherItem){ 
			//设置子节点的兄弟节点状态与当前节点的状态一致 
			int nState1 = GetItemState(hBrotherItem,TVIS_STATEIMAGEMASK); 
			if(nState1!=0){ 
				CTreeCtrl::SetItemState(hBrotherItem,INDEXTOSTATEIMAGEMASK(nState),TVIS_STATEIMAGEMASK); 
			} 
			//再递归处理子节点的兄弟节点的子节点和兄弟节点 
			travel_tree(hBrotherItem,nState,brother); 
			hBrotherItem=GetNextSiblingItem(hBrotherItem); 
		} 
	} else{
		all_paths_.push_back(path);
	}
} 

void View_Tree::expand_nodes(HTREEITEM root, BOOL expand,std::string &path)
{
	UINT nCode = expand?TVE_EXPAND:TVE_COLLAPSE;
	CString r,item;
	if (NULL == root){
	 // 可能有多个根节点
	 root = GetRootItem();
	 r = GetItemText(root);
	 r+= ":";
	 while(NULL != root){
		expand_nodes(root, expand,path);
		root = GetNextItem(root, TVGN_NEXT);
	 }
	 return;
	}
	HTREEITEM hSon = NULL;
	Expand(root,nCode);  
	r = GetItemText(root);
	r+= ":";
	// 遍历子节点
	hSon = GetNextItem(root,TVGN_CHILD);
	while(NULL != hSon){
//   Expand(hSon, nCode);
//	 TRACE("cur:%s,Expand son:%s\n", GetItemText(root), GetItemText(hSon));
	 CString s = GetItemText(hSon);
	 std::string ff = r.GetBuffer(0);
	 path += r.GetBuffer(0);
	 path += s.GetBuffer(0);
	//	r+= ":";
	 expand_nodes(hSon, expand,ff);  
	 all_paths_.push_back(path);
	 path= "";
	 hSon = GetNextItem(hSon,TVGN_NEXT);
	}
}

void View_Tree::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


void View_Tree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM sel_item = pNMTreeView->itemNew.hItem;
	CString sel_name = GetItemText(sel_item);
	Global::instance()->get_cur_detail_name() = sel_name;

	*pResult = 0;
}

