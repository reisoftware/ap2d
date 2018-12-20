// Mgr_Tree.cpp: implementation of the Mgr_Tree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Tree.h"
#include "Mgr_File.h"

#include "str_tools.h"
#include "Mgr_Dxfs.h"
#include "getrace.h"
#include "Left_Mgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Tree::Mgr_Tree()
{

}

Mgr_Tree::~Mgr_Tree()
{

}
void Mgr_Tree::create_rules(std::string rule_file,Tree_Rules &rules)
{
	std::string file_name = exe_path()+rule_file;
	try
	{
		CString strInfo,left;
		CStdioFile file;
		strings vals;
		if(!file.Open(file_name.c_str(),CFile::modeRead))
			return;
	
		rules.clear();
		
		while(file.ReadString(strInfo)){
			left = strInfo.Left(strInfo.Find(":"));
			Tree_Rule rule;
			rule.name_ = left;
			strInfo.Delete(0,strInfo.Find(":")+1);
			afc::split_string(rule.son_prefix_,strInfo.GetBuffer(0)," ");
			for(int i=0;i<rule.son_prefix_.size();i++){
				std::string s = rule.son_prefix_[i];
			}
			rules.push_back(rule);			
		}
		file.Close();
	}
	catch(CFileException e) 
	{
		AfxMessageBox("file no find!",MB_OK);
	}	
	

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
static void insert_tree(std::string str,Tree_Rules &rules)
{
	for(int i =0;i<rules.size();i++){
		if(find_prefex(str,rules[i].son_prefix_)){
			rules[i].sons_.push_back(str);

		}
	}
}
void Mgr_Tree::create_tree_sons(const strings &strs,Tree_Rules &rules)
{
	for(int i=0;i<strs.size();i++){
		insert_tree(strs[i],rules);
	}

}
static void insert_son(std::string parent,strings &sons,TItems &items)
{
	for(int i=0;i<sons.size();i++){
		TItem item;
		item.name_ = sons[i];
		item.parent_ = parent;
		//item.status_ = get_dxf_status(sons[i]); //此处需要判断地方
		item.status_ = STATUS_EDIT; //第一次加载，肯定是需要编辑的，所以不用判断
	//	item.status_ = get_dxf_status_lua(sons[i]); //此处需要判断地方
		items.push_back(item);

	}
}
void Mgr_Tree::create_tree(Tree_Rules &rules,TItems &items)
{

	for(int i=0;i<rules.size();i++){
		TItem item;
		item.name_ = rules[i].name_;
		item.parent_ = "ROOT";
		item.status_ = 0; //类别
		items.push_back(item);
		insert_son(item.name_,rules[i].sons_,items);
	}
}
void Mgr_Tree::create(const strings &strs,TItems &items,std::string rule_file)
{
	TRACE_OUT("Mgr_Tree::create start.\n");
	Tree_Rules rules;
	TRACE_OUT("Mgr_Tree::create_rules start.\n");
	create_rules(rule_file,rules);
	TRACE_OUT("Mgr_Tree::create_rules end.\n");

	TRACE_OUT("Mgr_Tree::create_tree_sons start.\n");
	create_tree_sons(strs,rules);
	TRACE_OUT("Mgr_Tree::create_tree_sons end.\n");


	TRACE_OUT("Mgr_Tree::create_tree start.\n");
	create_tree(rules,items);
	TRACE_OUT("Mgr_Tree::create_tree end.\n");

}