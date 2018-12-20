#ifndef _MEM_AXIS_H_
#define _MEM_AXIS_H_

#include "GeNorm.h"
class CMember;
class CGePlate;
class AFX_EXT_CLASS Mem_Axis{
	CMember* mem_;
	CGeAxis axis_;
public:
	Mem_Axis(CMember* mem);
	CPt3D& g2l(CPt3D& pt);
	CPt3D& l2g(CPt3D& pt);

	CGePlate& g2l(CGePlate& pl);
	CGePlate& l2g(CGePlate& pl);

	CPt3D& dis_g2l(CPt3D& pt);
	CPt3D& dis_l2g(CPt3D& pt);
};
#endif