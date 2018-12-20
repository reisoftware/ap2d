// DB_Tree.cpp: implementation of the DB_Tree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "DB_Tree.h"

#include "encode.h"
#include "Global.h"
#include "Left_Mgr.h"
#include "Mgr_Tree.h"
#include "getrace.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void TItem::set_from_str(char *in)
{
	rei_init(in);
	name_ = rei_get("name_");
	parent_ = rei_get("parent_");
	id_ = atoi(rei_get("id_"));
	parent_id_ = atoi(rei_get("parent_id_"));

	status_ = atoi(rei_get("status_"));

	rei_quit();
	
}
void TItem::get_str(char *out)
{
	rei_quit();

	rei_add_str(NULL,"name_",name_.c_str());
	rei_add_str(NULL,"parent_",parent_.c_str());
	rei_add_int(NULL,"id_",id_);
	rei_add_int(NULL,"parent_id_",parent_id_);

	rei_add_int(NULL,"status_",status_);
	
	rei_get_encode(out);

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Tree::DB_Tree()
{

}

DB_Tree::~DB_Tree()
{

}
int DB_Tree::get_root(TItem &root)
{
	for(int i=0;i<items_.size();i++){
		if(strcmp(items_[i].parent_.c_str(),"ROOT") == 0){
			root = items_[i];
			return i;
		}
	}
	return -1;
}
void DB_Tree::get_sons(std::string parent,TItems &sons)
{
	strings names;
	for(int i=0;i<items_.size();i++){
		strings::iterator iter = std::find(names.begin(),names.end(),items_[i].name_);
		if(iter != names.end())
			continue;
		if(strcmp(items_[i].parent_.c_str(),parent.c_str()) == 0){
			names.push_back(items_[i].name_);
			sons.push_back(items_[i]);
		}
	}
}
int DB_Tree::get_status(std::string cur_name,std::string parent)
{
	TItems::iterator iter = find(cur_name);
	if(iter == items_.end())
		return -1;
	return iter->status_;
}

void DB_Tree::insert_tree(HTREEITEM cur_pos,std::string parent,View_Tree &tree)
{
	TItems sons;
	get_sons(parent,sons);
	int count = sons.size();
	HTREEITEM new_pos;
	int status = -1;
	for(int i=0;i<sons.size();i++){
		std::string n = sons[i].name_;
		if(strcmp(n.c_str(),"") == 0)
			continue;
		new_pos = tree.InsertItem(sons[i].name_.c_str(),cur_pos);
		status = get_status(sons[i].name_.c_str(),parent);
		if(status == STATUS_EDIT){
			tree.SetItemImage(new_pos,STATUS_EDIT,STATUS_EDIT);
		}else if(status == STATUS_CHANGE){
			tree.SetItemImage(new_pos,STATUS_CHANGE,STATUS_CHANGE);
		}else if(status == STATUS_COMPLATE){
			tree.SetItemImage(new_pos,STATUS_COMPLATE,STATUS_COMPLATE);
		}		
		insert_tree(new_pos,sons[i].name_,tree);
	}


}

void DB_Tree::insert_tree_pri(HTREEITEM cur_pos,std::string parent,View_Tree &tree)
{
	TItems sons;
	get_sons(parent,sons);
	int count = sons.size();
	HTREEITEM new_pos;
	for(int i=0;i<sons.size();i++){
		std::string n = sons[i].name_;
		if(strcmp(n.c_str(),"") == 0)
			continue;
		new_pos = tree.InsertItem(sons[i].name_.c_str(),cur_pos);
		int status = sons[i].status_;
		tree.SetItemImage(new_pos,sons[i].status_,sons[i].status_);
		insert_tree(new_pos,sons[i].name_,tree);
	}


}
void DB_Tree::show(View_Tree &tree)
{
	tree.DeleteAllItems();
/*
	TItem root;
	TItems sons;
	int pos = get_root(root);
	if(pos == -1){
		AfxMessageBox("the tree file hasn't in server,please create it!");
		return ;
	}
	HTREEITEM cur_pos = tree.InsertItem(root.name_.c_str(),0);
	insert_tree(cur_pos,root.name_,tree);
*/
	for(int i=0;i<items_.size();i++){
		if(strcmp(items_[i].parent_.c_str(),"ROOT")==0){
			HTREEITEM cur_pos = tree.InsertItem(items_[i].name_.c_str(),items_[i].status_,items_[i].status_);
			int status = items_[i].status_;
			//insert_tree(cur_pos,items_[i].name_,tree);
			insert_tree_pri(cur_pos,items_[i].name_,tree);

		}
	}

}
void DB_Tree::show(std::string key,View_Tree &tree)
{

}
void DB_Tree::upload(std::string key)
{
	del_all(const_cast<char*>(key.c_str()),Global::instance()->ap2d());

	int count = items_.size();
	for(int i=0;i<items_.size();i++){
		char val[MAX_REDIS]={0};
		items_[i].get_str(val);		
		int id = new_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d());
  	update_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d(),id,val);
		
	}
}
void DB_Tree::create_item(char *in)
{
	TItem item;
	item.set_from_str(in);
	if(strcmp(item.name_.c_str(), "")==0)
		return;
	items_.push_back(item);

}

void DB_Tree::download(std::string key)
{
	items_.clear();

	if(redis_hgetall(Global::instance()->ap2d()->redis,const_cast<char*>(key.c_str()))){ 
		char str[MAX_REDIS] = {0}; 
		char *rs = NULL; 
		rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
		std::string val = rs;
		rs = strchr(str,'*'); 
		if(!rs) 
			return ; 	
		int num = atoi(rs + 1); 	
		
		for(int i = 0; i < num / 2 ; ++i){ 
			str[0] = 0;
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			if(!rs) 
				return;
			std::string val = rs;
			create_item(const_cast<char*>(val.c_str()));
		}	
	}
}


void DB_Tree::create_data(View_Tree	&tree)
{
	items_.clear();
	
	HTREEITEM root = tree.GetRootItem();
	CString val;

	int status = -1;
	while(root != NULL){
		val = tree.GetItemText(root);
		tree.GetItemImage(root,status,status);
		TItem item;
		item.name_ = val;
		item.parent_ = "ROOT";
		item.status_ = status;
		items_.push_back(item);
		
		root = tree.GetNextItem(root, TVGN_NEXT);
	}

}
void DB_Tree::create(strings &strs)
{
	TRACE_OUT("DB_Tree::create start.\n");
	std::string rule_file = "tree_rules.txt";
	Mgr_Tree mgr_tree;
	mgr_tree.create(strs,items_,rule_file);

	TRACE_OUT("DB_Tree::create end.\n");



}

void DB_Tree::change_status(std::string name,int status)
{
	TItems::iterator iter = find(name);
	if(iter == items_.end())
		return ;
	iter->status_ = status;
}
static bool find_prefex(std::string str,strings &prefixs)
{
	CString src = str.c_str();
	for(int i=0;i<prefixs.size();i++){
		int find = src.Find(prefixs[i].c_str());
		if(find != -1)
			return true;		
		else
			continue;
	}
	return false;
}

std::string DB_Tree::get_parent(std::string name)
{
	std::string rule_file = "tree_rules.txt";

	Tree_Rules rules;
	Mgr_Tree mgr_tree;
	mgr_tree.create_rules(rule_file,rules);

	for(int i =0;i<rules.size();i++){
		if(find_prefex(name,rules[i].son_prefix_)){
			return rules[i].name_;

		}
	}	
	return "ROOT";
}
