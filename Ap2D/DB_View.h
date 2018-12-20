// DB_View.h: interface for the DB_View class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_DB_H__CA04D7A1_E00B_4EDA_AEAD_90D6A162C2A3__INCLUDED_)
#define AFX_VIEW_DB_H__CA04D7A1_E00B_4EDA_AEAD_90D6A162C2A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "View.h"

class DB_View  
{
public:
	DB_View();
	virtual ~DB_View();
	static DB_View* instance();
	void close(); 

	void cur_view(View *cur){cur_ = cur;}
	View *cur_view(){return cur_;}

	dlhml::Database *database();
	View *get_view(std::string)const;
	View * add_view(std::string name);

	bool find_view(std::string name)const;
	bool erase_view(std::string name);
	void change_name(std::string old,std::string new_name);



	void clear_select();

private:
	View *cur_;
	std::vector<View*> vs_;




	bool erase_view(View *view);
};

#endif // !defined(AFX_VIEW_DB_H__CA04D7A1_E00B_4EDA_AEAD_90D6A162C2A3__INCLUDED_)
