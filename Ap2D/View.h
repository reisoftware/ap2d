// View.h: interface for the View class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__5DC6A80B_A36B_4FB7_9E17_9D023034C292__INCLUDED_)
#define AFX_VIEW_H__5DC6A80B_A36B_4FB7_9E17_9D023034C292__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../display/Scene_d.h"

class View  
{
public:
	View();
	virtual ~View();
	dlhml::Scene *scene(){return &scene_;}
	static View * create();
	void close();
	std::string name(){return name_;}
	void name(std::string n){name_ = n;}
	
	void edit(bool edit){edit_ = edit;}
	bool edit(){return edit_;}
private:
	std::string  name_;
	dlhml::Scene scene_;
	bool edit_;

};
View* open_view(std::string name,int &judge);

#endif // !defined(AFX_VIEW_H__5DC6A80B_A36B_4FB7_9E17_9D023034C292__INCLUDED_)
