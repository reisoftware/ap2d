// Mgr_Detail.cpp: implementation of the Mgr_Detail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Detail.h"

#include "Database.h"
#include "Dxfs_Mgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Detail::Mgr_Detail()
{

}

Mgr_Detail::~Mgr_Detail()
{

}
void Mgr_Detail::upload(std::string name,dlhml::Database &db)
{
/*
	std::string head = ap2d::Model::instance()->cur_detail_path();
	del_all(const_cast<char*>(head.c_str()),ap2d::Model::instance()->ap2d());
	TRACE_OUT("the all ents's num = %d\n",Project::instance()->cur_view()->scene()->database()->entity_size());

	std::vector<Entitys> parts;
	Entitys commons;
	Database_Ent::instance()->get_common_ents(commons);
	TRACE_OUT("the common ents's num = %d\n",commons.size());

	int ent_num = 800;
	part_ents(commons,parts,ent_num);

	upload_parts(head,parts);*/


}
void Mgr_Detail::download(std::string name,dlhml::Database &db)
{

}

void get_layer_str(dlhml::Database *db,std::string layer_name,std::string &str)
{
	Entitys ents;
	get_ents_by_layer(db,layer_name);

}
