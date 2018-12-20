// DB_Configure.h: interface for the DB_Configure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_CONFIGURE_H__7D48263B_F1D4_4139_8902_A6B97FE6BAEA__INCLUDED_)
#define AFX_DB_CONFIGURE_H__7D48263B_F1D4_4139_8902_A6B97FE6BAEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DB_Configure  
{
public:
	DB_Configure();
	virtual ~DB_Configure();
	static DB_Configure* instance();
	void close();

	void init_combo_by_names_list(CString,CComboBox &);
	void save_config_file(CString path,CString file_name,const CStringArray &strs);
	void open_config_file(CString path,CString file_name,CStringArray &strs);
	

};

#endif // !defined(AFX_DB_CONFIGURE_H__7D48263B_F1D4_4139_8902_A6B97FE6BAEA__INCLUDED_)
