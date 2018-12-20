// DimInfo_IO.cpp: implementation of the DimInfo_IO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "DimInfo_IO.h"

#include "DB_View.h"
#include "Global.h"
#include "Mgr_Lua.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DimInfo_IO::DimInfo_IO()
{

}

DimInfo_IO::~DimInfo_IO()
{

}
void DimInfo_IO::save(CString file)
{
	std::vector<dlhml::Entity*> ents;
	dlhml::entity_iterator it= DB_View::instance()->database()->entity_begin();
	for(; it != DB_View::instance()->database()->entity_end(); ++it){
		if(!(*it)){
			continue;
		}
		if(strcmp((*it)->layer_name().c_str(),"APDIM") == 0){		
			ents.push_back(*it);
		}
	}
	CString str = file +".dim.rei";
	save_lua(str.GetBuffer(0),ents);

}