// ApLayer_Ent.h: interface for the ApLayer_Ent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APLAYER_ENT_H__6A91A495_71F3_4343_85AA_00388F1B9074__INCLUDED_)
#define AFX_APLAYER_ENT_H__6A91A495_71F3_4343_85AA_00388F1B9074__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Mgr_Dxfs.h"


class ApLayer_Ent  
{
public:
	ApLayer_Ent();
	virtual ~ApLayer_Ent();

	std::string layer_name_;
	Entitys ents_;

};
typedef std::vector<ApLayer_Ent> ApLayer_Ents;

#endif // !defined(AFX_APLAYER_ENT_H__6A91A495_71F3_4343_85AA_00388F1B9074__INCLUDED_)
