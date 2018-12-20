// Tool_Arithmetic.cpp: implementation of the Tool_Arithmetic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tool_Arithmetic.h"

#include "TSolidGeometry.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace TIAN_GA_BETTER{

Tool_Arithmetic::Tool_Arithmetic()
MCT_INIT1("Tool_Arithmetic")
{

}

Tool_Arithmetic::~Tool_Arithmetic()
{

} 


TLine Tool_Arithmetic::draw_dis_line(const CPt3D_Pri& ptStart, const CPt3D_Pri& ptEnd,const CPt3D_Pri& ptDirect, float fDis)
{
	TLine line;
	TLine lnS(ptStart, ptEnd);
	TLine lnD;
	if(!TSolidGeometry::LineParallel(lnD, lnS, ptDirect, fDis)){



		return lnD;
	}
	return lnD;	
}

}