// GeNorm.h: interface for the CGeNorm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENORM_H__3462BB11_BECD_4D79_8D3D_7F441E982F2E__INCLUDED_)
#define AFX_GENORM_H__3462BB11_BECD_4D79_8D3D_7F441E982F2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "pt3d.h"
#ifdef AFX_DATA
#undef AFX_DATA
#endif

#define	AFX_DATA AFX_EXT_DATA

class AFX_EXT_CLASS CGeNorm  
{
public:
	static CGeNorm& X();
	static CGeNorm& X1();
	static CGeNorm& Y();
	static CGeNorm& Y1();
	static CGeNorm& Z();
	static CGeNorm& Z1();
	void Set(CPt3D& pt1,CPt3D& pt2);
	double len() const;
	double Angle2Norm(const CGeNorm& rhs);
	double Dot(const CGeNorm& rhs);

	CGeNorm(CPt3D pt1,CPt3D pt2);
	explicit CGeNorm(const CPt3D& pt);
	BOOL IsZero();
	void normalize();
	CGeNorm(double x, double y,double z);
	CGeNorm();
	virtual ~CGeNorm();
	
	BOOL operator == (const CGeNorm& Rhs) const;
	CGeNorm& operator = (const CGeNorm& normRight);
	CGeNorm operator * (const CGeNorm& normRight);
	
	CPt3D get_pt() const;

	double m_x;
	double m_y;
	double m_z;
};


class AFX_EXT_CLASS CGeAxis  
{
public:
	void SetUser(const CGeNorm& normal);
	void ChangeCoord(CPt3D& pt) const;
	void G2L(CPt3D& pt) const;
	CGeAxis();
	virtual ~CGeAxis();
	CGeNorm xNorm;
	CGeNorm yNorm;
	CGeNorm zNorm;
};
class CMember;
class CModel;
class CJoint;
class CGePlate;

class AFX_EXT_CLASS CPlane //∆Ω√Ê¿‡
{
public:

	double get_z(double x,double y) const;
	double get_x(double y,double z) const;
	double get_y(double x,double z) const;
	CGeNorm get_normal();
	BOOL perpendicular(CPt3D& pt,vector<CPt3D>& pts);
	BOOL intersect(CPt3D& pt1,CPt3D& pt2,vector<CPt3D>& pts);
	CPt3D intersect(const CPt3D& pt1,const CPt3D& pt2) const;

	void reinitialize();
	BOOL set(CPt3D& pt1,CPt3D& pt2);
	BOOL set(CGeNorm& x,CGeNorm& y,CGeNorm& z,CPt3D ptPlane);

	BOOL IsIn(CPt3D pt) const ;
	void InitGeAxis(CGeAxis* pAxis) const;
	BOOL Set(CMember* pMem1,CMember* pMem2);
		
	BOOL is_inner_or_intersect(CMember* mem);
	BOOL is_inner_or_intersect(CJoint* jnt);
	BOOL is_inner_or_intersect(CGePlate* pl);
	BOOL is_on(CModel* model,CPt3D pt);

	void axis_change();

	void Serialize(CArchive& ar);
//	void reset(double height);
	BOOL operator==(const CPlane& rhs) const;
	double A;
	double B;
	double C;
	double D;
 
	
public:
	double m[4][4];
	CPt3D pt;
	CPlane();
	~CPlane();

	void set_dis(double positive,double minus) 
	{
		positive_dis_ = positive;
		minus_dis_ = minus;
	}
	double get_positive_dis() const {return positive_dis_;}
	double get_minus_dis() const {return minus_dis_;}

	BOOL Set(CPt3D pt1, CPt3D pt2, CPt3D pt3);
private:
	double positive_dis_;
	double minus_dis_;
};

#undef AFX_DATA
#define AFX_DATA
#endif // !defined(AFX_GENORM_H__3462BB11_BECD_4D79_8D3D_7F441E982F2E__INCLUDED_)
