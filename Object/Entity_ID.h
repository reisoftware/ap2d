// Entity_ID.h: interface for the Entity_ID class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_ENTITY_ID_H__D5908136_596B_4101_9D44_5D71FB4FD755__INCLUDED_
#define AFX_ENTITY_ID_H__D5908136_596B_4101_9D44_5D71FB4FD755__INCLUDED_

#include "export.h"
#include <vector>
#include <fstream>
#include "../afc/counter.h"
// using namespace std;

//class iLua_File;
//class oLua_File;
namespace dlhml{
class File;
class OBJECT_API Entity_ID  
{
public:
	Entity_ID();
	~Entity_ID();

public:
  bool is_default()const;

	//serialize
	void load(File& in);
	void save(const File& out) const;

// 	void lua_load(iLua_File &fin);
// 	void lua_save(oLua_File &fout) const;

	void save_lua(std::ofstream &out,char *name,int tab_num);

	void entity_id(ULONG id){
		id_ = id;
	}
	ULONG entity_id() const{
		return id_;
	}

	bool operator<(const Entity_ID& rhs) const{
		return id_ < rhs.id_;
	}
	bool operator==(const Entity_ID& rhs) const{
		return id_ == rhs.id_;
	}

private:
	ULONG id_;
private:
	MCT_DEF
};

typedef std::vector<Entity_ID> OBJECT_API EntityIDArray;
typedef std::vector<Entity_ID> OBJECT_API EntIDs;

}
#endif // !defined(AFX_ENTITY_ID_H__D5908136_596B_4101_9D44_5D71FB4FD755__INCLUDED_)
