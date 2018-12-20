// TSolidGeometry.h: interface for the TSolidGeometry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSOLIDGEOMETRY_H__16CBEF7D_3797_4B54_9338_47DD0A890CE7__INCLUDED_)
#define AFX_TSOLIDGEOMETRY_H__16CBEF7D_3797_4B54_9338_47DD0A890CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "export.h"
#include "TPlaneGeometry.h"
#include "counter.h"
#include <vector>

namespace TIAN_GA_BETTER{


class GEOAPI TPlane
{
public:
	TPlane()MCT_INIT1("GA:TPlane"){a=b=c=d=0;}
	TPlane(double ta, double tb, double tc, double td)MCT_INIT1("GA:TPlane"){Set(ta,tb,tc,td);}
	TPlane(CPt3D_Pri pt1, CPt3D_Pri pt2, CPt3D_Pri pt3)MCT_INIT1("GA:TPlane"){Set(pt1,pt2,pt3);}
	~TPlane(){;}

	void Set(double ta, double tb, double tc, double td){a=ta;b=tb;c=tc;d=td;}
	void Set(CPt3D_Pri pt1, CPt3D_Pri pt2, CPt3D_Pri pt3);

	CGeNorm Normal() const;

  //  数学公式：ax+by+cz+d=0
	double a, b, c, d;
private:
	MCT_DEF
};


class GEOAPI TSolidGeometry  
{
public:

////********************************************************************
////作者：田佰杰
////日期：2007-07-06 to 2007-07-06
////功能：点到平面的距离。
////********************************************************************
	static double DisPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);

////********************************************************************
////作者：田佰杰
////日期：2007-07-06 to 2007-07-06
////功能：点在平面的上中下。
////********************************************************************
	static double DxPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);
	static double DyPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);
	static double DzPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);
////********************************************************************
////作者：田佰杰
////日期：2007-07-09 to 2007-07-09
////功能：带入点，求出等式右端值(点到平面的向量距离)。
////********************************************************************
	static double DNarmalPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);
////********************************************************************
////作者：田佰杰
////日期：2007-07-09 to 2007-07-09
////功能：点到平面的垂足。
////********************************************************************
	static CPt3D_Pri PtPedal(const CPt3D_Pri& pt, const TPlane& pl);

////********************************************************************
////作者：田佰杰
////日期：2007-07-03 to 2007-07-09
////功能：线段消隐。
////********************************************************************
	static bool ShowHideLineInPolygon(const TSegLine& sl, const std::vector<CPt3D_Pri>& vPtsPolygon,
					std::vector<TSegLine>& vSlsHide, std::vector<TSegLine>& vSlsShow);
	static bool ShowHideLineInPolygon(const CPt3D_Pri& pt1, const CPt3D_Pri& pt2, 
					const std::vector<CPt3D_Pri>& vPtsPolygon,
					std::vector<CPt3D_Pri>& vPtsHide, std::vector<CPt3D_Pri>& vPtsShow);

////********************************************************************
////作者：田佰杰
////日期：2007-07-09 to 2007-07-09
////功能：直线与平面的交点。
////********************************************************************
	static bool Intersect(const TLine& ln, const TPlane& pl, CPt3D_Pri& ptCross);

//**********************************************************************
//<Author>:Tian Baijie
//<Edit>=Date:2007/08/31
////功能：按比例求出线段中某点的值(x/y/z)。
//****************************************
	static bool PtScale (CPt3D_Pri& pt, const TLine& ln, double m, double n);
// 	static bool PtScaleX(CPt3D_Pri& pt, const TLine& ln);
// 	static bool PtScaleY(CPt3D_Pri& pt, const TLine& ln);
	static bool PtScaleZ(CPt3D_Pri& pt, const TLine& ln);
//</Edit>
//</Author>
//**********

////********************************************************************
////作者：田佰杰
////日期：2007-07-10 to 2007-07-10
////功能：去除重合点(同时删掉两个点)必须是在同一条直线上并且点有序。
////********************************************************************
	static bool DeleteRepeatPt(std::vector<CPt3D_Pri>& vPts);
	static bool DeleteRepeatLn(std::vector<TSegLine>& vSls);
////********************************************************************
////作者：田佰杰
////日期：2007-07-05 to 2007-07-05
////功能：根据与点的距离排序
////********************************************************************
	static bool SortDisToPt(std::vector<CPt3D_Pri>& vPts, const CPt3D_Pri& ptFixed);
////********************************************************************
////作者：田佰杰
////日期：2007-07-05 to 2007-07-05
////功能：两点的距离
////********************************************************************
	static double DisPt(const CPt3D_Pri& pt1, const CPt3D_Pri& pt2);

////********************************************************************
////功能：判断点是否在射线上
////********************************************************************
	static bool IsPtInLine(const CPt3D_Pri& pt, const TLine	  & tl);
	static bool IsPtInLine(const CPt3D_Pri& pt, const TSegLine& sl);
	static bool IsPtInLine(const CPt3D_Pri& pt, const TRayLine& rl);

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/07/31
////两个平面求夹角(弧度/角度)
//****************************************
	static double ArcBetweenPlane(const TPlane& pl1, const TPlane& pl2);
	static double AngleBetweenPlane(const TPlane& pl1, const TPlane& pl2);
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/01
	////功能：平移一条直线。
	////参数：	lnResult：目标直线。
	////		lnSource：源直线。
	////		ptWay	：方向控制点。
	////		dis		：平移距离。
	////返回：	bool	：成功返回true，失败返回false。
	////		TLine	：返回平移后的目标线。
	////注意：如果方向控制点在源直线上，
	////		bool	：返回false。
	////		TLine	：返回源直线。
//****************************************
	static TLine LineParallel(const TLine& lnSource,
													const CPt3D_Pri & ptWay);
	static bool LineParallel(TLine& lnResult, const TLine& lnSource,
													const CPt3D_Pri & ptWay);
	static TLine LineParallel(const TLine& lnSource,
										const CPt3D_Pri & ptWay, double dis);
	static bool LineParallel(TLine& lnResult, const TLine& lnSource,
										const CPt3D_Pri & ptWay, double dis);
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/01
////双向延长线
//****************************************
	static bool  LineExtend(TLine& lnResult, 
            							const TLine& lnSource, 
                          double dLen);
	static TLine LineExtend(const TLine& lnSource, 
                          double dLen);
	static bool  LineExtend(TLine& lnResult, 
                          const TLine& lnSource, 
							            double dLenSt, 
                          double dLenEd);
	static TLine LineExtend(const TLine& lnSource, 
							            double dLenSt, 
                          double dLenEd);
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/01
////功能：点到直线的距离
//****************************************
	static double DisPtToLine(const CPt3D_Pri& pt, const TLine& ln);
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/31
////功能：获得点在直线上的垂足。
//****************************************
	static CPt3D_Pri PtPedal(const CPt3D_Pri & ptBase, const TLine& ll);
//</Add>
//</Author>
//**********


protected:
	TSolidGeometry();
	virtual ~TSolidGeometry();
private:
	MCT_DEF
};

}

#endif // !defined(AFX_TSOLIDGEOMETRY_H__16CBEF7D_3797_4B54_9338_47DD0A890CE7__INCLUDED_)
