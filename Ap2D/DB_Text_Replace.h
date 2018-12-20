// DB_Text_Replace.h: interface for the DB_Text_Replace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_TEXT_REPLACE_H__FD3DDC21_8122_4C8B_95B2_6A69BAD2816F__INCLUDED_)
#define AFX_DB_TEXT_REPLACE_H__FD3DDC21_8122_4C8B_95B2_6A69BAD2816F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Lead_Dimension_Info.h"

class Text_Replace  
{
public:
	Text_Replace();
	virtual ~Text_Replace();
	
	CString txt_;
	CString replace_;
	CString char_;
	CString postfix_;

};


class DB_Text_Replace  
{
public:
	DB_Text_Replace();
	virtual ~DB_Text_Replace();
	static DB_Text_Replace* instance();
	void close();
	
public:
	void add(Text_Replace&);
	void edit(const Text_Replace &val);
	void del(int);

	void save(CString file);
	void open(CString file);
	std::vector<Text_Replace> retrun_db();

	
	CString get_replace_string(CString txt,CString cur_char);

	void get_obj_format(std::vector<dlhml::Text_Rep_Obj> &reps);
private:
	std::vector<Text_Replace> db_;
};

#endif // !defined(AFX_DB_TEXT_REPLACE_H__FD3DDC21_8122_4C8B_95B2_6A69BAD2816F__INCLUDED_)
