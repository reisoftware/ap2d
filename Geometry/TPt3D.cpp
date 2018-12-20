// Pt3D.cpp: implementation of the CPt3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TPt3D.h"
#include "TGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


namespace TIAN_GA_BETTER {
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TPoint::TPoint()
:x(0.0)
,y(0.0)
,z(0.0)
MCT_INIT2("GA:TPoint")
{

}

TPoint::~TPoint()
{

}
void TPoint::MirrorYZ()
{
	x = -x; 
}
void TPoint::MirrorXZ()
{
	y = -y;
}

void TPoint::MirrorXY()
{
	z = -z;
}
void TPoint::RotateX(double beta)
{
	TPoint pt = *this;
	pt.y =0; 
	pt.z =0;
	
	double len = Len(pt);
	if(EquFloat(len,0.0))
		return ;
	double a = acos(y/len);
	if(z < 0)
		a = - a;
	a += beta *PI_R/180.0;

	y = len * cos(a);
	z = len * sin(a);
}
void TPoint::RotateY(double beta)
{
	TPoint pt = *this;
	double a = beta *PI_R/180.0;
	
	pt.x = x * cos(a) + z * sin(a);
	pt.y = y;
	pt.z = -x * sin(a) + z * cos(a);

	*this = pt;
}
void TPoint::RotateZ(double beta)
{
	TPoint pt = *this;
	double a = beta *PI_R/180.0;
	
	pt.x = x * cos(a) - y * sin(a);
	pt.y = x * sin(a) + y * cos(a);
	pt.z = z;

	*this = pt;
}  
void TPoint::Scale(double dScale)
{
	x *= dScale;
	y *= dScale;
	z *= dScale;
}
double TPoint::Len(TPoint &rhs)
{
  //	double l;
  //	double l=sqrt( (rhs.x - x)*(rhs.x - x)
  //				+(rhs.y - y)*(rhs.y - y)
  //				+(rhs.z - z)*(rhs.z - z) );
  //	return l;
	return sqrt( (rhs.x - x)*(rhs.x - x)
							+(rhs.y - y)*(rhs.y - y)
							+(rhs.z - z)*(rhs.z - z) );
}
TPoint TPoint::PolarTo(float len, CGeNorm *pNormal)
{
	TPoint pt;
	pt.x = x + len * pNormal->m_x;
	pt.y = y + len * pNormal->m_y;
	pt.z = z + len * pNormal->m_z;
	return pt;
}
TPoint::TPoint(double xx, double yy, double zz)
:x(xx)
,y(yy)
,z(zz)
MCT_INIT2("GA:TPoint")
{
}

TPoint::TPoint(const TPoint& rhs)
:x(rhs.x)
,y(rhs.y)
,z(rhs.z)
MCT_INIT2("GA:TPoint")
{
}

TPoint TPoint::operator - (const TPoint& rhs) const
{
	TPoint pt;
	pt.x = x - rhs.x ;
	pt.y = y - rhs.y;
	pt.z = z - rhs.z;
	return pt;

}
TPoint TPoint::operator + (const TPoint& rhs) const
{
	TPoint pt;
	pt.x = x + rhs.x ;
	pt.y = y + rhs.y;
	pt.z = z + rhs.z;
	return pt;
}
TPoint& TPoint::operator = (const TPoint& rhs)
{
	if(this == &rhs)
		return *this;

	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}
BOOL TPoint::operator == (const TPoint& rhs) const
{
	return (EquFloat(x,rhs.x) 
		   && EquFloat(y,rhs.y) 
		   && EquFloat(z,rhs.z) );
}
///////////////////////////////////////////////////////////
CGeNorm::CGeNorm()
:m_x(0.0)
,m_y(0.0)
,m_z(0.0)
MCT_INIT2("GA:CGeNorm")
{

} 
CGeNorm::CGeNorm(double x, double y,double z)
:m_x(x)
,m_y(y)
,m_z(z)
MCT_INIT2("GA:CGeNorm")
{

}
CGeNorm::CGeNorm(TPoint pt1, TPoint pt2)
MCT_INIT1("GA:CGeNorm")
{
	m_x = pt2.x - pt1.x;
	m_y = pt2.y - pt1.y;
	m_z = pt2.z - pt1.z;
}
CGeNorm::~CGeNorm()
{

}double CGeNorm::len() const
{
	double len = sqrt( m_x*m_x + m_y*m_y + m_z*m_z);
	return len;
}
void CGeNorm::normalize()
{
	if(IsZero())
		return;
	double len = sqrt( m_x*m_x + m_y*m_y + m_z*m_z);
	m_x = m_x / len;
	m_y = m_y / len;
	m_z = m_z / len;
}

BOOL CGeNorm::IsZero()
{
	return (EquFloat(m_x, 0.0)
			&& EquFloat(m_y, 0.0)
			&& EquFloat(m_z, 0.0) );

}
CGeNorm& CGeNorm::operator = (const CGeNorm& normRight)
{
	m_x = normRight.m_x;
	m_y = normRight.m_y;
	m_z = normRight.m_z;
	return *this;
}
BOOL CGeNorm::operator == (const CGeNorm& Rhs)
{
	return (EquFloat(m_x,Rhs.m_x) &&
		   EquFloat(m_y,Rhs.m_y) &&
		   EquFloat(m_z,Rhs.m_z) );
}
double CGeNorm::Dot(const CGeNorm &rhs)
{
	return ( m_x * rhs.m_x+ m_y * rhs.m_y + m_z * rhs.m_z ); 

}
double CGeNorm::Angle2Norm(const CGeNorm &rhs)
{
	//得到两向量的点积 
 double dot = Dot(rhs); 

 //得到两向量长度的乘积 
 double Len = len() * rhs.len(); 

 //得到两向量夹角 
 double angle = acos( dot/ Len ); 

 //返回角度值 
 return angle; 
}
CGeNorm CGeNorm::operator * (const CGeNorm& normRight)
{

	double x=0,y=0,z=0;
	x= m_y * normRight.m_z - normRight.m_y * m_z;
	y = m_z * normRight.m_x - normRight.m_z * m_x;
	z = m_x * normRight.m_y - normRight.m_x * m_y;
	CGeNorm normResult(x,y,z);
	normResult.normalize();
	return normResult;
}
void CGeNorm::Set(TPoint &pt1, TPoint &pt2)
{
	m_x = pt2.x - pt1.x;
	m_y = pt2.y - pt1.y;
	m_z = pt2.z - pt1.z;
}
CGeNorm& CGeNorm::X()
{
	static CGeNorm normal(1,0,0);
	return normal;
}
CGeNorm& CGeNorm::X1()
{
	static CGeNorm normal(-1,0,0);
	return normal;
}
CGeNorm& CGeNorm::Y()
{
	static CGeNorm normal(0,1,0);
	return normal;
}
CGeNorm& CGeNorm::Y1()
{
	static CGeNorm normal(0,-1,0);
	return normal;
}
CGeNorm& CGeNorm::Z()
{
	static CGeNorm normal(0,0,1);
	return normal;
}
CGeNorm& CGeNorm::Z1()
{
	static CGeNorm normal(0,0,1);
	return normal;
}


}
