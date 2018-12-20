// Entity_ID.cpp: implementation of the Entity_ID class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Entity_ID.h"
#include "File.h"
#include "iolua.h"
#include "lua.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace dlhml{

const ULONG default_id_ = 0;

Entity_ID::Entity_ID()
:id_(default_id_)
MCT_INIT2("Entity_ID")
{

}

Entity_ID::~Entity_ID()
{

}

bool Entity_ID::is_default()const
{
  return id_ == default_id_;
}

void Entity_ID::load(File& in)
{
	in >> id_;
}
void Entity_ID::save(const File& out) const
{
	out << id_;
}

// void Entity_ID::lua_load(iLua_File &fin)
// {
// 	
// }
// 
// void Entity_ID::lua_save(oLua_File &fout) const
// {
// 	fout.save_value("id_", id_);
// }

// void Entity_ID::save_lua(ofstream &out,char *name,int tab_num)
// {
// 	lua::begin_table(out,name,tab_num);
// 
// 	lua::int_save(out,"id_",id_,tab_num+1);
// 	
// 	lua::end_table(out,tab_num);
// 
// }


}
