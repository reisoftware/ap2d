// DB_File_Date.h: interface for the DB_File_Date class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_FILE_DATE_H__8350123C_31F1_4A8C_B1FA_63185FAAF1A9__INCLUDED_)
#define AFX_DB_FILE_DATE_H__8350123C_31F1_4A8C_B1FA_63185FAAF1A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "DB_Templete.h"

class ApFile_Date 
{
public:
	ApFile_Date(){}
	virtual ~ApFile_Date(){;}
	bool operator==(const ApFile_Date& rhs)
	{
		if(strcmp(name_.c_str(),rhs.name_.c_str()) == 0 )
			return true;
		return false;
	}	

	std::string name_;
	std::string date_;


};
typedef std::vector<ApFile_Date> ApFile_Dates;

class DB_File_Date : public DB_Templete<ApFile_Dates,ApFile_Date>  
{
public:
	DB_File_Date();
	virtual ~DB_File_Date();

	void save();
	void read();
	void del();

	void save_std();
	void read_std();
	bool change(std::string file);
	void push(const strings &files);

	int find_name(std::string name);

	void edit(std::string file);

};

#endif // !defined(AFX_DB_FILE_DATE_H__8350123C_31F1_4A8C_B1FA_63185FAAF1A9__INCLUDED_)
