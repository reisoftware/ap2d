// Pt3D.h: interface for the CPt3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PT3D_H__562A3EB8_C5BC_40CA_9829_46F81981B6D6__INCLUDED_)
#define AFX_PT3D_H__562A3EB8_C5BC_40CA_9829_46F81981B6D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "export.h"
#include "counter.h"


namespace TIAN_GA_BETTER{

class CGeNorm;
class GEOAPI TPoint  
{
public:

	void MirrorYZ();
	void MirrorXZ();
	void MirrorXY();

	void RotateX(double beta);
	void RotateY(double beta);
	void RotateZ(double beta);

	void Scale(double dScale);
	double Len(TPoint& rhs);
	TPoint PolarTo(float len,CGeNorm* pNormal);

	TPoint(double xx, double yy, double zz);
	TPoint(const TPoint& rhs);
	TPoint();
	~TPoint();

	
	TPoint& operator = (const TPoint& rhs);
	TPoint operator + (const TPoint& rhs) const;
	TPoint operator - (const TPoint& rhs) const;
	BOOL operator == (const TPoint& rhs) const;
	double x;
	double y;
	double z;
private:
	MCT_DEF
};
typedef TPoint CPt3D_Pri;

class GEOAPI CGeNorm  
{
public:
	static CGeNorm& X();
	static CGeNorm& X1();
	static CGeNorm& Y();
	static CGeNorm& Y1();
	static CGeNorm& Z();
	static CGeNorm& Z1();

	void Set(TPoint& pt1,TPoint& pt2);
	double len() const;
	double Angle2Norm(const CGeNorm& rhs);
	double Dot(const CGeNorm& rhs);
	
	CGeNorm(double x, double y,double z);
	CGeNorm();
	virtual ~CGeNorm();
	CGeNorm(TPoint pt1,TPoint pt2);

	BOOL IsZero();
	void normalize();

	
	BOOL operator == (const CGeNorm& Rhs);
	CGeNorm& operator = (const CGeNorm& normRight);
	CGeNorm operator * (const CGeNorm& normRight);

	double m_x;
	double m_y;
	double m_z;
private:
	MCT_DEF
};

}

#endif // !defined(AFX_PT3D_H__562A3EB8_C5BC_40CA_9829_46F81981B6D6__INCLUDED_)
