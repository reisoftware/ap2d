// DB_Company.h: interface for the DB_Company class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_COMPANY_H__7DC8B875_7B6C_4BA1_B4AD_E25680BF9C95__INCLUDED_)
#define AFX_DB_COMPANY_H__7DC8B875_7B6C_4BA1_B4AD_E25680BF9C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "DB_Templete.h"
#include "Ex_ListCtrl_Sort.h"

class Project
{
public:
	Project(){;}
	virtual ~Project(){;}
	bool operator==(const Project& rhs)
	{
		if(strcmp(name_.c_str(),rhs.name_.c_str()) == 0 )
			return true;
		return false;
	}	
	void set_from_str(char *in);
	void get_str(char *out);

	void set_from_str_sub(char *name);
	void get_str_sub(char *name);

	std::string name_;
	strings groups_;
	
	std::string dir_path_;
};
typedef std::vector<Project> Projects;


class Company
{
public:
	Company(){;}
	virtual ~Company(){;}
	bool operator==(const Company& rhs)
	{
		if(strcmp(name_.c_str(),rhs.name_.c_str()) == 0 )
			return true;
		return false;
	}	
	void set_from_str(char *in);
	void get_str(char *out);

	std::string name_;
	Projects pros_; 


	
};
typedef std::vector<Company> Companys;

class DB_Company  : public DB_Templete<Companys,Company> 
{
public:
	DB_Company();
	virtual ~DB_Company();

	void show_companys(ListCtrl_Sort	&list_ctrl);
	void show_projects(std::string company_name,ListCtrl_Sort	&list_ctrl);
		
	void upload(std::string key);
	void download(std::string key);

	void set_project_path(std::string company_name,std::string project_name,std::string dir_path);
	std::string get_project_path(std::string company_name,std::string project_name);

	void push_project(std::string company_name,Project &pro);
	void edit_project_name(std::string company_name,std::string project_name,std::string project_path);
	void del_project_name(std::string company_name,std::string project_name);
private:
	void create_item(char *in);

};

#endif // !defined(AFX_DB_COMPANY_H__7DC8B875_7B6C_4BA1_B4AD_E25680BF9C95__INCLUDED_)
