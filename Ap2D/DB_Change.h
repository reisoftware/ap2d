// DB_Change.h: interface for the DB_Change class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_Change_H__0B5EA149_E911_44C1_9574_08A3602AD23A__INCLUDED_)
#define AFX_DB_Change_H__0B5EA149_E911_44C1_9574_08A3602AD23A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include "DB_Templete.h"

class Change
{
public:
	Change(){;}
	virtual ~Change(){;}
	bool operator==(const Change& rhs)
	{
		if(strcmp(name_.c_str(),rhs.name_.c_str()) == 0 )
			return true;
		return false;
	}	

	std::string name_;
	int haxi_val_;



};
typedef std::vector<Change>  Changes;

class DB_Change : public DB_Templete<Changes,Change>
{
public:
	DB_Change();
	virtual ~DB_Change();


	bool check(const std::string &name,int haxi_val);

	void upload();
	void download();
private:
	Changes db_;

};

#endif // !defined(AFX_DB_Change_H__0B5EA149_E911_44C1_9574_08A3602AD23A__INCLUDED_)
