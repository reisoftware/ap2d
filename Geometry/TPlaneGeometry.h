// TPlane.h: interface for the TPlane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPLANE_H__D69A5040_39AB_4FA9_986F_99AC8F0FD71E__INCLUDED_)
#define AFX_TPLANE_H__D69A5040_39AB_4FA9_986F_99AC8F0FD71E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//**********************************************************************
//<Author>:Tian Baijie
//****************************************

#include <vector>
#include <math.h>

#include "export.h"

#include "TPt3D.h"
#include "counter.h"


namespace TIAN_GA_BETTER{

const TPoint gc_ptOrg = TPoint(0,0,0);
const CGeNorm gc_gnOrg = CGeNorm(gc_ptOrg,gc_ptOrg);

enum EOrgPt {TPO_ORGPT1 = 1, TPO_ORGPT2 = 2
};

class GEOAPI TLine////直线
{
public:
	void Set(TPoint pt,CGeNorm normal,double dis = 1);
	void Set(const TPoint& p1,const TPoint& p2);
	void Reverse();
////********************************************************************
////求垂线(以某个点为轴，顺逆时针旋转)
////********************************************************************
	void PedalUnclockwise(EOrgPt eOrg = TPO_ORGPT1);
	void PedalClockwise(EOrgPt eOrg = TPO_ORGPT1);
////********************************************************************

	TPoint PtCenter()const{return TPoint((pt1.x+pt2.x)/2, (pt1.y+pt2.y)/2, (pt1.z+pt2.z)/2);}

	double Length(){return sqrt(pow(pt1.x-pt2.x,2)+pow(pt1.y-pt2.y,2)+pow(pt1.z-pt2.z,2));}

	TLine(const TPoint& p1,const TPoint& p2);
	TLine(TPoint pt,CGeNorm normal,double dis = 1)MCT_INIT1("GA:TLine"){Set(pt,normal,dis);}
	TLine();
	~TLine();

	virtual bool IsPtInLine(const TPoint& pt) const;

	TPoint pt1;

	TPoint pt2;
private:
	MCT_DEF
};
class GEOAPI TRayLine : public TLine////射线
{
public:
	TRayLine(const TPoint& p1,const TPoint& p2);
	TRayLine()MCT_INIT1("GA:TRayLine"){pt1=TPoint(0,0,0);pt2=TPoint(1,1,1);}
	~TRayLine();

	virtual bool IsPtInLine(const TPoint& pt) const;
private:
	MCT_DEF
};
class GEOAPI TSegLine : public TRayLine//线段
{
public:
//	TPoint pt1;
//	TPoint pt2;

	TSegLine(const TPoint& p1,const TPoint& p2);
	TSegLine()MCT_INIT1("GA:TSegLine"){pt1=TPoint(0,0,0);pt2=TPoint(1,1,1);}
	~TSegLine();

	virtual bool IsPtInLine(const TPoint& pt) const;
private:
	MCT_DEF
};

class GEOAPI TArc//角(单位：弧度)
{
public:
	TArc();
	TArc(TPoint ptCentre, double r, double stArc, double edArc);
	TArc(TPoint ptCentre, double r, TPoint ptSt, TPoint ptEd);
	TArc(TPoint pt1, TPoint pt2, TPoint pt3);
	~TArc();
	
	void Set(TPoint ptCentre, double r, double stArc, double edArc);
	void Set(TPoint ptCentre, double r, TPoint ptSt, TPoint ptEd);
	void Set(TPoint pt1, TPoint pt2, TPoint pt3);

	TPoint PtSt() const;
	TPoint PtEd() const;

	TLine LineSt()	const;
	TLine LineEd()	const;

	double Length() const;
	double LenPtToCentre(const TPoint& pt) const;

	TPoint  _ptCentre;
	double _r;

	double _stArc;
	double _edArc;

private:
	void Init(TPoint ptSt, TPoint ptEd);
	bool Init(TPoint pt1,TPoint pt2,TPoint pt3);

//是否是逆时针
	bool IsIncrease(double asin1, double asin2, double asin3);

private:
	MCT_DEF
};


typedef  class GEOAPI TPlaneGeometry  
{
public:
	static bool Intersect(const TLine	& ll1,	const TRayLine	&rl ,TPoint& pt);
	static bool Intersect(const TLine	& ll1,	const TLine		&ll2,TPoint& pt);
	static bool Intersect(const TLine	& ll ,	const TSegLine	&sl ,TPoint& pt);
	static bool Intersect(const TSegLine& sl1,	const TSegLine	&sl2,TPoint& pt);
	static bool Intersect(const TSegLine& sl ,	const TRayLine	&rl ,TPoint& pt);
	static bool Intersect(const TRayLine& rl1,	const TRayLine	&rl2,TPoint& pt);
	static TPlaneGeometry& Instance();	~TPlaneGeometry();

////********************************************************************
////功能：求穿过已知点的垂直线
////注意：如果没有给出已知点(则默认为已知线的pt1点)
////********************************************************************
	static TLine NormLine(TLine & tl);
	static TLine LinePedal(const TPoint& pt, const TLine& tl);
	static TLine LinePedal(const TLine& tl);
////********************************************************************
////功能：返回第几象限(第1象限含0不含π/2)
////********************************************************************
	static int RadianToQuadrant(double dRadian);
////********************************************************************
////功能：返回第几象限(第1象限不含0含π/2)
////********************************************************************
	static int RadianToQuadrantRe(double dRadian);
////********************************************************************
////功能：返回第几坐标轴（1==X, 2==Y, 3== -X, 4== -Y, other == 0）
////********************************************************************
	static int RadianToCoordAxis(double dRadian);
////********************************************************************
////功能：获得一个点(差/弧度)的弧度(与X轴正方向的正夹角)
////注意：返回值在1.4象限内，即0～π/2和3π/2~2π之间（含小不含大）
////********************************************************************
	static double RadianToQuadrant14(double dRadian);
////********************************************************************
////功能：获得一个点(差/弧度)的弧度(与X轴正方向的正夹角)
////注意：返回值在0～2π(不含2π)之间
////********************************************************************
	static double Radian(const TPoint& pt, const TPoint& ptOrg = TPoint(0,0,0));
	static double Radian(const TLine& tl);
	static double Radian(const CGeNorm& norm);
	static double Radian(double dRadian);
////********************************************************************
////功能：判断点是否在三点形成的凸角内
////注意：pt2为角顶点
////********************************************************************
	static bool   IsPtInSalient(const TPoint& pt, 
					const TPoint& pt1, const TPoint& pt2, const TPoint& pt3);
////********************************************************************
////作者：田佰杰
////日期：2007-04-16 to 2007-04-19
////功能：获得在平行线上对应的点。
////********************************************************************
	static TPoint PtInParallel(const TPoint & ptBase,
									const TLine ll, const TPoint& ptConsult);

////********************************************************************
////作者：田佰杰
////功能：获得穿过已知点的平行线。
////********************************************************************
	static TLine LineParallel(const TPoint & ptBase, const TLine& ll);
////********************************************************************
////功能：沿固定线方向异动点。
////********************************************************************
	static bool PtOrtho(TPoint& pt, TLine lnBase, TPoint ptBase);
	static bool PtOrtho(TPoint& pt, TLine lnBase);
//**********************************************************************
//<Add>=Date:2007/07/30
////功能：  平移一条直线。
////参数：	lnResult：目标直线。
////		    lnSource：源直线。
////		    ptWay	：方向控制点。
////		    dis		：平移距离。
////返回：	bool	：成功返回true，失败返回false。
////		    TLine	：返回平移后的目标线。
////注意：  如果方向控制点在源直线上，
////		    bool	：返回false。
////		    TLine	：返回源直线。
//****************************************
	static TLine LineParallel(const TLine& lnSource,
													const TPoint & ptWay);
	static bool LineParallel(TLine& lnResult, const TLine& lnSource,
													const TPoint & ptWay);
	static TLine LineParallel(const TLine& lnSource,
										const TPoint & ptWay, double dis);
	static bool LineParallel(TLine& lnResult, const TLine& lnSource,
										const TPoint & ptWay, double dis);
//**********************************************************************
//<Add>=Date:2007/08/02
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
////********************************************************************
////功能：根据点和角度求点/线。
////********************************************************************
	static TPoint PtFromAngle(TPoint pt, double angle);
	static TLine LineFromangle(TPoint pt, double angle);
////********************************************************************
////日期：2007-04-20 to 2007-04-20
////功能：获得点在直线上的垂足。
////********************************************************************
	static TPoint PtPedal(const TPoint & ptBase, const TLine& ll);
////********************************************************************
////日期：2007-04-24 to 2007-04-24
////功能：获得角分线。
////********************************************************************
	static double MidArc(const TArc & arc);
	static TPoint  MidArcPt(const TArc & arc);
	static TLine  MidArcLine(const TArc & arc);
////********************************************************************
////日期：2007-04-24 to 2007-04-24
////功能：获得角分线点的外切线。
////********************************************************************
	static TLine TangentLine(const TArc & arc);
////********************************************************************
////日期：2007-04-24 to 2007-04-24
////功能：角度弧度互换。
////********************************************************************
	static double Angle2Arc(double angle);
	static double Arc2Angle(double arc);
////********************************************************************
////日期：2007-05-15 to 2007-04-15
////功能：在给定的线上截取一段。
////注意：iWay:表示截取方向，1：在pt1方向截取，2：在pt2方向截取
//********************************************************************
	static TLine LineIntersect(const TLine& tl, double len, EOrgPt eOrg = TPO_ORGPT1);
////********************************************************************
////日期：2007-05-15 to 2007-04-15
////功能：获得反向线。
////********************************************************************
	static TLine Reverse(TLine tl){return TLine(tl.pt2, tl.pt1);}
////********************************************************************
////日期：2007-05-20 to 2007-04-20
////功能：点到线的距离。
////注意：返回true则垂足在线段上，返回false则垂足在线延长线上
////********************************************************************
	static bool Length(double & len, const TPoint& pt, const TLine& tl);
	static bool Length(double & len, const TPoint& pt, const TRayLine& rl);
	static bool Length(double & len, const TPoint& pt, const TSegLine& sl);

	static double DisPt(const TPoint& pt1, const TPoint& pt2);
	static double DisPtByNormal(TPoint pt1, TPoint pt2, CGeNorm nm);
	static double DisPtToLine(const TPoint& pt, const TLine& ln);
	static double DisPtToLineByNormal(TPoint pt, TLine ln, CGeNorm nm);
////********************************************************************
////作者：田佰杰
////日期：2007-05-20 to 2007-04-20
////功能：判断点是否在弧内
////********************************************************************
	static bool IsPtInArc(const TPoint& pt, const TArc& arc);
////********************************************************************
////作者：田佰杰
////日期：2007-07-03 to 2007-07-03
////功能：判断点是否在多边形内
////********************************************************************
	static bool IsPtInPolygon(const TPoint& pt, 
					const TPoint * pPtPolygon, int nCount);
	static bool IsPtInPolygon(const TPoint& pt, 
					const std::vector<TPoint>& vPtPlolygons);
  template<class PtIt>
	static bool IsPtInPolygon(const TPoint& pt, 
								   PtIt first, PtIt last)
	{
		std::vector<TPoint> vPts;
		PtIt it = first;
		while (it != last)
		{
			vPts.push_back(*it);
			it++;
		}
		return IsPtInPolygon(pt, vPts);
	}

////********************************************************************
////作者：田佰杰
////日期：2007-07-05 to 2007-07-05
////功能：线穿过多边形内，求出多边形内、外线段组。
////********************************************************************
	static bool LineInPolygon(const TSegLine& sl,const std::vector<TPoint>& vPtsPolygon,
					std::vector<TSegLine>& vSlsInside, std::vector<TSegLine>& vSlsOutside);
	
////********************************************************************
////作者：田佰杰
////日期：2007-07-05 to 2007-07-05
////功能：根据与点的距离排序
////********************************************************************
	static bool SortDisToPt(std::vector<TPoint>& vPts, const TPoint& ptFixed);


////********************************************************************
////作者：田佰杰
////日期：2007-07-05 to 2007-07-05
////功能：根据比例求中间值
////********************************************************************
	static double ScaleMean(double x1, double x2, double m, double n);
////********************************************************************
////日期：2007-07-10 to 2007-07-10
////功能：去除重合点(同时删掉两个点)。
////********************************************************************
	static bool DeleteRepeatPt(std::vector<TPoint>& vPts);

//**********************************************************************
//<Add>=Date:2007/07/30
////判断多边形是否是凸多边形
//****************************************
	static bool IsPolygonConvex(const std::vector<TPoint>& vPtsPolygon);
//**********
//**********************************************************************
////角度（弧度）求normal
//****************************************
	static CGeNorm NormalFromAngle(double angle);
	
	static bool is_line_superpositon(TLine ln1, TLine ln2);
  static bool is_pt_superposition(TPoint pt1, TPoint pt2);

	
//**********
	
	static BOOL IfAoRect(std::vector<TPoint>& pt3dsFront);

////********************************************************************
////功能：判断交点是否在线段/射线上
////注意：交点pt必须是已知在rl/sl直线上的点(已经非必须)，已考虑z坐标
////		不考虑z坐标可用函数IsPtInLine
////		  考虑z坐标可用函数TSolidGeometry::IsPtInLine
////********************************************************************
	static bool IsIntersectInsideLine(const TPoint& pt, const TLine	 & tl);
	static bool IsIntersectInsideLine(const TPoint& pt, const TSegLine& sl);
	static bool IsIntersectInsideLine(const TPoint& pt, const TRayLine& rl);
//////********************************************************************
//////功能：判断点是否在线上
//////********************************************************************
	static bool IsPtInLine(const TPoint& pt, const TLine	  & tl);
	static bool IsPtInLine(const TPoint& pt, const TSegLine& sl);
	static bool IsPtInLine(const TPoint& pt, const TRayLine& rl);
//////********************************************************************
//////功能：判断点是否相等（忽略z）
//////********************************************************************
	static bool IsPtEqu(const TPoint& pt1, const TPoint& pt2);
//////********************************************************************
//////功能：判断线段是否在两条平行直线之间(忽略z)
//////********************************************************************
	static bool IsSegInsideLine(const TSegLine& sl, 
						const TLine& ln1, const TLine& ln2);





protected:

////********************************************************************
////功能：判断平面上的两条线交点
////返回：true有交点,false平行或者重合
////参数：承接交点的坐标和两条线(4个点)的坐标
////注意：必须判断其返回值以确定是否能够相交
////********************************************************************
	static bool intersect_line2line_2d(double& destpt_x, double& destpt_y, 
								double line1st_x, double line1st_y,
								double line1ed_x, double line1ed_y,
								double line2st_x, double line2st_y, 
								double line2ed_x, double line2ed_y	);


private:
	TPlaneGeometry();
private:
	MCT_DEF
} TTool, TGeometry, TGeo;


}
//</Author>
//********** 

#endif // !defined(AFX_TPLANE_H__D69A5040_39AB_4FA9_986F_99AC8F0FD71E__INCLUDED_)
