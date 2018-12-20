// DB_Jishou.h: interface for the DB_Jishou class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_JISHOU_H__EDB0E4B4_B54C_494A_924E_A53640EEEE45__INCLUDED_)
#define AFX_DB_JISHOU_H__EDB0E4B4_B54C_494A_924E_A53640EEEE45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <iostream>


class Ji1Shou
{
public:
	Ji1Shou() {};
	virtual ~Ji1Shou() {};
	CString ass_no_;
	CString l_joint_;
	CString r_joint_;
};

typedef std::vector<Ji1Shou> JS;

class DB_Jishou  
{
public:
	DB_Jishou();
	virtual ~DB_Jishou();
	static DB_Jishou* instance();
	JS return_js_db(); 
	void add_data_to_db(Ji1Shou&);
	Ji1Shou get_sel_data();
	void set_sel_data(Ji1Shou& data,BOOL status);
	void change_vector_iter(Ji1Shou& data);
	BOOL re_status();
	void init_jishou_db(JS& datas);
	void del_iter(Ji1Shou& data);
	void init_data();
	void save_cur_file();

private:
	JS JS_db_;
	Ji1Shou sel_data_;
	BOOL edit_;

};

#endif // !defined(AFX_DB_JISHOU_H__EDB0E4B4_B54C_494A_924E_A53640EEEE45__INCLUDED_)
