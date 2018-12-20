// Decompose_Entity.cpp: implementation of the Decompose_Entity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Decompose_Entity.h"


#include "Lead_Dimension_Info.h"
#include "Text_Dimension_Info.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Decompose_Entity::Decompose_Entity()
{

}

Decompose_Entity::~Decompose_Entity()
{

}
void Decompose_Entity::add_db(Entitys &ents)
{
	for(int i=0;i<ents.size();i++){
		dlhml::Entity_ID id;
		ents[i]->post2db(*DB_View::instance()->database(),id);
	}

}

void Decompose_Entity::decompose_lead_dims(Entitys &lead_dims)
{
	for(int i=0;i<lead_dims.size();i++){
		dlhml::Lead_Dimension_Info *dim = (dlhml::Lead_Dimension_Info *)lead_dims[i];
		Entitys ents;
		dim->get_show(ents);
		//已经存在了，所以不需要重新添加到数据库中，只需要把Lead_Dimension_Info消除即可
	//	add_db(ents);
	}

	for(i=0;i<lead_dims.size();i++){
		DB_View::instance()->database()->remove_entity(lead_dims[i]->entity_id());
	}

}
void Decompose_Entity::decompose_text_dims(Entitys &lead_dims)
{
	for(int i=0;i<lead_dims.size();i++){
		dlhml::Text_Dimension_Info *dim = (dlhml::Text_Dimension_Info *)lead_dims[i];
		Entitys ents;
		dim->get_show(ents);
		//已经存在了，所以不需要重新添加到数据库中，只需要把Lead_Dimension_Info消除即可
		add_db(ents);
	}

	for(i=0;i<lead_dims.size();i++){
		DB_View::instance()->database()->remove_entity(lead_dims[i]->entity_id());
	}

}

void Decompose_Entity::decompose()
{
	
	Entitys all_ents,lead_dims,text_dims;
	get_ents(DB_View::instance()->database(),all_ents);	
	//处理lead_dims
	get_lead_dim_infos(DB_View::instance()->database(),all_ents,lead_dims);
	decompose_lead_dims(lead_dims);

	//处理Text_Dimension_Info
	get_text_dim_infos(DB_View::instance()->database(),all_ents,lead_dims);
	decompose_text_dims(lead_dims);

	

	



}
