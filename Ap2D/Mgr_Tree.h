// Mgr_Tree.h: interface for the Mgr_Tree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_TREE_H__C43C86B4_DDFD_4625_8157_DD63D26D22F9__INCLUDED_)
#define AFX_MGR_TREE_H__C43C86B4_DDFD_4625_8157_DD63D26D22F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DB_Tree.h"

class Tree_Rule  
{
public:
	Tree_Rule(){;}
	virtual ~Tree_Rule(){;}

	std::string name_;
	strings son_prefix_;
	
	strings sons_;
};
typedef std::vector<Tree_Rule> Tree_Rules; 


class Mgr_Tree  
{
public:
	Mgr_Tree();
	virtual ~Mgr_Tree();

	void create_rules(std::string rule_file,Tree_Rules &rules);
	void create(const strings &strs,TItems &items,std::string rule_file);

private:
	void create_tree_sons(const strings &strs,Tree_Rules &rules);
	void create_tree(Tree_Rules &rules,TItems &items);

	Tree_Rules tree_rules_;
	
};

#endif // !defined(AFX_MGR_TREE_H__C43C86B4_DDFD_4625_8157_DD63D26D22F9__INCLUDED_)
