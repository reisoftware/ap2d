#ifndef _JNT_AXIS_H_
#define _JNT_AXIS_H_

#ifdef AFX_DATA
#undef AFX_DATA
#endif

#define AFX_DATA AFX_EXT_DATA

#include "GeNorm.h"
class CJoint;
class CMember;
class CGePlate;
class AFX_EXT_CLASS Jnt_Axis{
	CGeAxis axis_;
	CPt3D base_;
	CPt3D offset_;
	double beta_;
	CJoint* jnt_;
	BOOL mirror_;
public:
	Jnt_Axis(CJoint* jnt);
	CGeNorm get_xnorm() const {return axis_.xNorm;}
	CGeAxis  get_axis() const {return axis_;}
	double get_beta() const {return beta_;}
	CPt3D get_offset() const {return offset_;}
	BOOL get_mirror() const {return mirror_;}
	CPt3D& g2l(CPt3D& pt) ;
	CPt3D& l2g(CPt3D& pt) ;
	CGePlate& g2l(CGePlate& pl);
	CGePlate& l2g(CGePlate& pl);
	CPt3D& dis_l2g(CPt3D& pt);
	CPt3D& dis_g2l(CPt3D& pt);
	void adjust_offset(CPt3D move);
private:
};

#undef AFX_DATA
#endif