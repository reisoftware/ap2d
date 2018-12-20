// Draw_Entities.h: interface for the Draw_Entities class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAW_ENTITIES_H__3BFBC7D0_03F0_437E_B496_49512D1A91A9__INCLUDED_)
#define AFX_DRAW_ENTITIES_H__3BFBC7D0_03F0_437E_B496_49512D1A91A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mgr_Database.h"



class Draw_Entities  
{
public:
	Draw_Entities();
	virtual ~Draw_Entities();

	void draw_circle(const dlhml::Point &center,int color,float r);
	void draw_rect(const dlhml::Point &center,int color,float r);
	void draw_rect(const dlhml::Rect &rect,int color);
};

#endif // !defined(AFX_DRAW_ENTITIES_H__3BFBC7D0_03F0_437E_B496_49512D1A91A9__INCLUDED_)
