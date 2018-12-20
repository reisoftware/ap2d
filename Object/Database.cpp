// Database.cpp: implementation of the Database class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Database.h"
#include "Database_Private.h"
#include "Entity.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Database::Database()
MCT_INIT1("Database")
{

}

Database::~Database()
{

}
// void Database::calc_index(Entity* pEnt,Entity_ID& id//,ULONG index)
// {
// 	pEnt->id_.entity_id(index);
// 	id = pEnt->id_;
// }
Database* Database::create_me()
{
	return new Database_Private;
}

//void Database::selected_all(bool sel)
//{
//  //entity_iterator db_begin = m_p_preview_Wnd_->m_scene_.database()->entity_begin();
//  //entity_iterator db_end   = m_p_preview_Wnd_->m_scene_.database()->entity_end()  ;
//  //entity_iterator it = entity_begin();
//  for(entity_iterator it=entity_begin(); it!=entity_end(); it++){
//    (*it)->selected(sel);
//  }
//}

//namespace
}
