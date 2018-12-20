// DB_Tree.h: interface for the DB_Tree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_TREE_H__F042D6FB_6128_4D06_82B0_803DF9B7B8FE__INCLUDED_)
#define AFX_DB_TREE_H__F042D6FB_6128_4D06_82B0_803DF9B7B8FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include "DB_Templete.h"
#include "View_Tree.h"

class TItem
{
public:
	TItem(){;}
	virtual ~TItem(){id_=-1;parent_id_=-1;status_ = 0;}
	bool operator==(const TItem& rhs)
	{
		if(strcmp(name_.c_str(),rhs.name_.c_str()) == 0 )
			return true;
		return false;
	}	
	void set_from_str(char *in);
	void get_str(char *out);

	std::string name_;
	std::string parent_;

	int id_;
	int parent_id_;
	
	int status_;
	
};
typedef std::vector<TItem> TItems;

class DB_Tree : public DB_Templete<TItems,TItem>
{
public:
	DB_Tree();
	virtual ~DB_Tree();

	void show(View_Tree	&tree);
	void show(std::string key,View_Tree	&tree);

	void upload(std::string key);
	void download(std::string key);

	void create_data(View_Tree	&tree);

	void create(strings &strs);	
	void change_status(std::string name,int status);

	std::string get_parent(std::string name);

private:
	void create_item(char *in);
	int get_root(TItem &root);
	void get_sons(std::string parent,TItems &sons);
	void insert_tree(HTREEITEM cur_pos,std::string parent,View_Tree &tree);
	int get_status(std::string cur_name,std::string parent);

	void insert_tree_pri(HTREEITEM cur_pos,std::string parent,View_Tree &tree);

};

#endif // !defined(AFX_DB_TREE_H__F042D6FB_6128_4D06_82B0_803DF9B7B8FE__INCLUDED_)
