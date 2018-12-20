// DB_Layer.h: interface for the DB_Layer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_LAYER_H__21074755_77E6_4B65_A9C6_F81F355C1DD5__INCLUDED_)
#define AFX_DB_LAYER_H__21074755_77E6_4B65_A9C6_F81F355C1DD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include "DB_Templete.h"


namespace dlhml
{
	class Database;
}
class ApLayer 
{
public:
	ApLayer(){show_ = FALSE;lock_ = FALSE;}
	virtual ~ApLayer(){;}
	bool operator==(const ApLayer& rhs)
	{
		if(strcmp(name_.c_str(),rhs.name_.c_str()) == 0 )
			return true;
		return false;
	}	
	void set_from_str(char *in);
	void get_str(char *out);

	std::string name_;
	BOOL show_;
	BOOL lock_;


};
typedef std::vector<ApLayer> ApLayers;
	
class DB_Layer : public DB_Templete<ApLayers,ApLayer> 
{
public:
	DB_Layer();
	virtual ~DB_Layer();

	void create(dlhml::Database *db);
	void upload(std::string key);
	void download(std::string key);

	void show(CComboBox & combo);

	BOOL get_show(std::string name);
	BOOL get_lock(std::string name);


	void download_layers(dlhml::Database *db);
private:
	void create_item(char *in);
};

#endif // !defined(AFX_DB_LAYER_H__21074755_77E6_4B65_A9C6_F81F355C1DD5__INCLUDED_)
