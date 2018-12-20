// Decompose_Entity.h: interface for the Decompose_Entity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECOMPOSE_ENTITY_H__17F5DF5C_1567_4A83_A340_A273BBCE39AE__INCLUDED_)
#define AFX_DECOMPOSE_ENTITY_H__17F5DF5C_1567_4A83_A340_A273BBCE39AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DB_View.h"
#include "Mgr_Database.h"
#include "Draw_Entities.h"


class Decompose_Entity  
{
public:
	Decompose_Entity();
	virtual ~Decompose_Entity();

	void decompose();

private:
	void decompose_lead_dims(Entitys &lead_dims);
	void add_db(Entitys &ents);
	void decompose_text_dims(Entitys &lead_dims);

};

#endif // !defined(AFX_DECOMPOSE_ENTITY_H__17F5DF5C_1567_4A83_A340_A273BBCE39AE__INCLUDED_)
