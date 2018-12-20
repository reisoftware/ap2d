// Model_DB.h: interface for the Model_DB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_DB_H__2F3C2E5C_B4C8_49B4_8112_AD3173795AE3__INCLUDED_)
#define AFX_MODEL_DB_H__2F3C2E5C_B4C8_49B4_8112_AD3173795AE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
////////////////////////////////

#include <vector>
#include <iostream>

#include "DB_Text_Replace.h"

class Part  
{
public:
	Part();
	virtual ~Part();
	CString partno_;
	CString name_;
	CString section_;
	CString numbers_;
	CString matrial_;
	CString lengths_;
	CString area_ ;
	CString weights_;
};

typedef std::vector<Part> Parts;


///////////////////////////////////
//partlist.txt
class Model_DB  
{
public:
	Model_DB();
	virtual ~Model_DB();
	DB_Text_Replace model_db_text_replace;
	static Model_DB* instance();
	void close();
	CString get_file_path();
	void create_db(CString file);
	CString get_section(CString);
	CString	get_matrail(CString);
	BOOL get_part(CString,Part&);
	void dim_name_styles_strs(CStringArray&);
	void set_dim_name_style( CStringArray&);
	void get_dim_name_strs(CString name,CStringArray&);
	void get_name_strs(Part,CStringArray&);
	void get_names(CStringArray& names);
	void 	deal_data_to_db(CString s);
	void open(CString file);
	void save(CString file);
	Parts retrun_model_db();
//	Part get_part_from_name(CString name);
private:
	Parts db_;
	CStringArray dim_name_styles_;
	CStringArray save_per_line;
	void Model_DB::init_dim_styles();
};

#endif // !defined(AFX_MODEL_DB_H__2F3C2E5C_B4C8_49B4_8112_AD3173795AE3__INCLUDED_)
