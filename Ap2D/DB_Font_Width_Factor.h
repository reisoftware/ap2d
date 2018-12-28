// DB_Font_Width_Factor.h: interface for the DB_Font_Width_Factor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_FONT_WIDTH_FACTOR_H__9571ADFE_9030_46D4_822F_E24FA55E3555__INCLUDED_)
#define AFX_DB_FONT_WIDTH_FACTOR_H__9571ADFE_9030_46D4_822F_E24FA55E3555__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Font_WF  
{
public:
	Font_WF();
	virtual ~Font_WF();
	
	CString height_;
	CString width_factor_;

};


class DB_Font_Width_Factor  
{
public:
	DB_Font_Width_Factor();
	virtual ~DB_Font_Width_Factor();

	static DB_Font_Width_Factor* instance();
	void close();

	void add(CString height,CString width_factor);
	void edit(CString height,CString width_factor);
	void del(CString height);
	CString find(CString height);

	void save();
	void open();
	std::vector<Font_WF> retrun_db();

	
	CString get_replace_string(CString txt,CString cur_char);


	void show(CListCtrl &list);
private:
	std::vector<Font_WF> db_;

};

#endif // !defined(AFX_DB_FONT_WIDTH_FACTOR_H__9571ADFE_9030_46D4_822F_E24FA55E3555__INCLUDED_)
