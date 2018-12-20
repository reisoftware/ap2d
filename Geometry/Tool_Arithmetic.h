// Tool_Arithmetic.h: interface for the Tool_Arithmetic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOL_ARITHMETIC_H__B51F211E_40D5_46D4_B22E_AE3F1AD8B245__INCLUDED_)
#define AFX_TOOL_ARITHMETIC_H__B51F211E_40D5_46D4_B22E_AE3F1AD8B245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TPlaneGeometry.h"
#include "counter.h"

namespace TIAN_GA_BETTER{
class GEOAPI Tool_Arithmetic  
{
public:
	Tool_Arithmetic();
	virtual ~Tool_Arithmetic();

	static TLine Tool_Arithmetic::draw_dis_line(const CPt3D_Pri& ptStart, const CPt3D_Pri& ptEnd,const CPt3D_Pri& ptDirect, float fDis);
private:
	MCT_DEF
};
}


#endif // !defined(AFX_TOOL_ARITHMETIC_H__B51F211E_40D5_46D4_B22E_AE3F1AD8B245__INCLUDED_)
