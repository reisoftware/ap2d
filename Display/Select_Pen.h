// Select_Pen.h: interface for the Select_Pen class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SELECT_PEN_H__D165970B_2075_44CF_935D_2892751E4BCB__INCLUDED_
#define AFX_SELECT_PEN_H__D165970B_2075_44CF_935D_2892751E4BCB__INCLUDED_

#include "display_export.h"

namespace dlhml{
class Painter;
class Entity;
class Line_Type;
class Select_Pen  
{
public:
	Select_Pen(Painter& painter,const Entity& ent,const Line_Type* lt);
	~Select_Pen();

private:
	Painter& painter_;

	HPEN pen_;
	HPEN old_pen_;
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_SELECT_PEN_H__D165970B_2075_44CF_935D_2892751E4BCB__INCLUDED_)
