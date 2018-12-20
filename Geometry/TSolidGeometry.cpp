// TSolidGeometry.cpp: implementation of the TSolidGeometry class.
//
//////////////////////////////////////////////////////////////////////
 
#include "stdafx.h"
#include "TSolidGeometry.h"
#include <algorithm>

#include "TGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//using namespace std;
namespace TIAN_GA_BETTER{

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void TPlane::Set(CPt3D_Pri p1, CPt3D_Pri p2, CPt3D_Pri p3)
{
	  a = ( (p2.y-p1.y)*(p3.z-p1.z)-(p2.z-p1.z)*(p3.y-p1.y) );
    b = ( (p2.z-p1.z)*(p3.x-p1.x)-(p2.x-p1.x)*(p3.z-p1.z) );
    c = ( (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x) );
    d = ( 0-(a*p1.x+b*p1.y+c*p1.z) );
}

CGeNorm TPlane::Normal() const
{
	return CGeNorm(a,b,c);
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TSolidGeometry::TSolidGeometry()
MCT_INIT1("GA:TSolidGeometry")
{

}

TSolidGeometry::~TSolidGeometry()
{

}

////********************************************************************
////作者：田佰杰
////日期：2007-07-06 to 2007-07-06
////功能：点到平面的距离。
////********************************************************************
double TSolidGeometry::DisPtToPlane(const CPt3D_Pri& pt, const TPlane& pl)
{
	return fabs(DNarmalPtToPlane(pt,pl));
}

////********************************************************************
////作者：田佰杰
////日期：2007-07-06 to 2007-07-06
////功能：点在平面的上中下。
////********************************************************************
double TSolidGeometry::DxPtToPlane(const CPt3D_Pri& pt, const TPlane& pl)
{
	return pt.x - PtPedal(pt,pl).x;
}
double TSolidGeometry::DyPtToPlane(const CPt3D_Pri& pt, const TPlane& pl)
{
	return pt.y - PtPedal(pt,pl).y;
}
double TSolidGeometry::DzPtToPlane(const CPt3D_Pri& pt, const TPlane& pl)
{
	return pt.z - PtPedal(pt,pl).z;
}
////********************************************************************
////作者：田佰杰
////日期：2007-07-09 to 2007-07-09
////功能：带入点，求出等式右端值(点到平面的向量距离)。
////********************************************************************
double TSolidGeometry::DNarmalPtToPlane(const CPt3D_Pri& pt, const TPlane& pl)
{
	return (pl.a*pt.x+pl.b*pt.y+pl.c*pt.z+pl.d) / 
			sqrt(pow(pl.a,2)+pow(pl.b,2)+pow(pl.c,2));
}
////********************************************************************
////作者：田佰杰
////日期：2007-07-09 to 2007-07-09
////功能：点到平面的垂足。
////********************************************************************
CPt3D_Pri TSolidGeometry::PtPedal(const CPt3D_Pri& pt, const TPlane& pl)
{
	CPt3D_Pri ptResult = pt;
	CGeNorm norm = pl.Normal();
	norm.normalize();
	return ptResult.PolarTo(-DNarmalPtToPlane(pt,pl),&norm);
}


////********************************************************************
////作者：田佰杰
////日期：2007-07-03 to 2007-07-09
////功能：线段消隐。
////********************************************************************
bool TSolidGeometry::ShowHideLineInPolygon( const TSegLine& sl, 
                                            const vector<CPt3D_Pri>& vPtsPolygon,
					                                  vector<TSegLine>& vSlsHide, 
                                            vector<TSegLine>& vSlsShow)
{
	int nSizePolygon = vPtsPolygon.size();
	if (nSizePolygon < 3) return false;
	
	//  分4种情况进行消隐
	TPlane plPolygon(vPtsPolygon[0], vPtsPolygon[1], vPtsPolygon[2]);
  //  1:平面上
	if( TMoreEqu(DzPtToPlane(sl.pt1, plPolygon),0 ) && 
      TMoreEqu(DzPtToPlane(sl.pt2, plPolygon),0 ) )
	{
		vSlsShow.push_back(sl);
	}
  //  2:平面下
	else if(TLessThen (DzPtToPlane(sl.pt1, plPolygon),  0)  && 
          TLessThen (DzPtToPlane(sl.pt2, plPolygon),  0)	||
			    TLessEqu  (DzPtToPlane(sl.pt1, plPolygon),  0)  && 
          TLessThen (DzPtToPlane(sl.pt2, plPolygon),  0)	||
			    TLessThen (DzPtToPlane(sl.pt1, plPolygon),  0)  && 
          TLessEqu  (DzPtToPlane(sl.pt2, plPolygon),  0)	)
	{
		if(!TPlaneGeometry::LineInPolygon(sl, vPtsPolygon, vSlsHide, vSlsShow))
    {
			return false;
    }
	}
  //  3:1下2上
	else if(TLessThen(DzPtToPlane(sl.pt1, plPolygon),0) && 
          TMoreThen(DzPtToPlane(sl.pt2, plPolygon),0) )
	{
		CPt3D_Pri ptCross;
		Intersect(sl,plPolygon,ptCross);
		TSegLine sl1(sl.pt1, ptCross), sl2(ptCross,sl.pt2);
		if (!TPlaneGeometry::LineInPolygon(sl1, vPtsPolygon, vSlsHide, vSlsShow))
    {
      return false;
    }
		vSlsShow.push_back(sl2);
	}
  //  4:1上2下
	else if(TMoreThen(DzPtToPlane(sl.pt1, plPolygon),0) && 
          TLessThen(DzPtToPlane(sl.pt2, plPolygon),0))
	{
		CPt3D_Pri ptCross;
		Intersect(sl,plPolygon,ptCross);
		TSegLine sl1(sl.pt1, ptCross), sl2(ptCross,sl.pt2);
		vSlsShow.push_back(sl1);
		if (!TPlaneGeometry::LineInPolygon(sl2, vPtsPolygon, vSlsHide, vSlsShow))
    {
      return false;
    }
	}
	////计算z值
	int nSizeSlsHide = vSlsHide.size();
	for (int i=0; i<nSizeSlsHide; i++)
	{
		PtScaleZ(vSlsHide[i].pt1, sl);
		PtScaleZ(vSlsHide[i].pt2, sl);
	}
	int nSizeSlsShow = vSlsShow.size();
	for (i=0; i<nSizeSlsShow; i++)
	{
		PtScaleZ(vSlsShow[i].pt1, sl);
		PtScaleZ(vSlsShow[i].pt2, sl);
	}

	return true;
}
bool TSolidGeometry::ShowHideLineInPolygon(const CPt3D_Pri& pt1, const CPt3D_Pri& pt2, 
					const vector<CPt3D_Pri>& vPtsPolygon,
					vector<CPt3D_Pri>& vPtsHide, vector<CPt3D_Pri>& vPtsShow)
{
	int nSizePolygon = vPtsPolygon.size();
	if (nSizePolygon < 3) return false;

	TSegLine sl(pt1,pt2);
	vector<TSegLine> vSlsHide, vSlsShow;
	if (!ShowHideLineInPolygon(sl,vPtsPolygon,vSlsHide,vSlsShow)) return false;

  int szend_hide = vPtsHide.size();
  vPtsHide.resize(szend_hide+vSlsHide.size()*2);
	for (int i=0; i<vSlsHide.size(); i++)
	{
    vPtsHide[szend_hide+i*2]   = vSlsHide[i].pt1;
    vPtsHide[szend_hide+i*2+1] = vSlsHide[i].pt2;
	}
  int szend_show = vPtsShow.size();
  vPtsShow.resize(szend_show+vSlsShow.size()*2);
	for (i=0; i<vSlsShow.size(); i++)
	{
    vPtsShow[szend_show+i*2]   = vSlsShow[i].pt1;
    vPtsShow[szend_show+i*2+1] = vSlsShow[i].pt2;
	}
// 	for (int i=0; i<vSlsHide.size(); i++)
// 	{
// 		vPtsHide.push_back(vSlsHide[i].pt1);
// 		vPtsHide.push_back(vSlsHide[i].pt2);
// 	}
// 	for (i=0; i<vSlsShow.size(); i++)
// 	{
// 		vPtsShow.push_back(vSlsShow[i].pt1);
// 		vPtsShow.push_back(vSlsShow[i].pt2);
// 	}
	return true;
}


////********************************************************************
////作者：田佰杰
////日期：2007-07-09 to 2007-07-09
////功能：直线与平面的交点。
////********************************************************************
bool TSolidGeometry::Intersect(const TLine& ln, const TPlane& pl, CPt3D_Pri & ptCross)
{
	double m = DNarmalPtToPlane(ln.pt1,pl);
	double n = DNarmalPtToPlane(ln.pt2,pl);
	if (m==n) return false;						////平行
	if (!PtScale(ptCross, ln, m, n)) return false;
	return ln.IsPtInLine(ptCross);
}

//**********************************************************************
//<Author>:Tian Baijie
//<Edit>=Date:2007/08/31
////功能：按比例求出线段中某点的值(x/y/z)。
//****************************************
bool TSolidGeometry::PtScale (CPt3D_Pri& pt, const TLine& ln, double m, double n)
{
	pt.x = TPlaneGeometry::ScaleMean(ln.pt1.x,ln.pt2.x,m,n);
	pt.y = TPlaneGeometry::ScaleMean(ln.pt1.y,ln.pt2.y,m,n);
	pt.z = TPlaneGeometry::ScaleMean(ln.pt1.z,ln.pt2.z,m,n);
	return true;
}
bool TSolidGeometry::PtScaleZ(CPt3D_Pri& pt, const TLine& ln)
{
	if(ln.pt1 == ln.pt2)
	{
		return false;
	}
	double m = TPlaneGeometry::DisPt(pt, ln.pt1);
	if (!m)
	{
		pt.z = ln.pt1.z;
		return true;
	}
	double n = TPlaneGeometry::DisPt(pt, ln.pt2);
	if (TPlaneGeometry::DisPt(pt,ln.pt2) > TPlaneGeometry::DisPt(pt,ln.pt1)	&&
		TPlaneGeometry::DisPt(pt,ln.pt2) > TPlaneGeometry::DisPt(ln.pt1,ln.pt2))
	{
		m = -m;
	}
	if (TPlaneGeometry::DisPt(pt,ln.pt1) < TPlaneGeometry::DisPt(pt,ln.pt2)	||
		TPlaneGeometry::DisPt(pt,ln.pt1) < TPlaneGeometry::DisPt(ln.pt1,ln.pt2))
	{
		n = -n;
	}
	pt.z = TPlaneGeometry::ScaleMean(ln.pt1.z,ln.pt2.z,m,n);
	return true;
}
//</Edit>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Delete>=Date:2007/08/31
//<Remark>:以X方向排序点
//<Notice>:没有处理x相同的情况
//****************************************
/*
bool SortPt3D(const CPt3D_Pri& lft,const CPt3D_Pri& rht)
{
	return lft.x < rht.x;
}
*/
//</Delete>
//</Author>
//**********


////********************************************************************
////作者：田佰杰
////日期：2007-07-10 to 2007-07-10
////功能：去除重合点必须是在同一条直线上并且点有序。
////********************************************************************
bool TSolidGeometry::DeleteRepeatPt(vector<CPt3D_Pri>& vPts)
{
// 	sort(vPts.begin(),vPts.end(),SortPt3D);
	int nSizePts = vPts.size();
	if (nSizePts <= 0 || nSizePts%2 != 0)
	{
		return false;
	}

	vector<CPt3D_Pri> vPtsTemp;
	vector<CPt3D_Pri>::iterator it = vPts.begin();
	vector<CPt3D_Pri>::iterator itend = vPts.end();
	while(it != itend -1)
	{
		if(*it == *(it+1))
		{
			it = it+2;
		}
		else
		{
			vPtsTemp.push_back(*it);
			++it;
		}
	}
	if(it != itend)
		vPtsTemp.push_back(*it);

	vPts.clear();
	copy(vPtsTemp.begin(), vPtsTemp.end(), back_inserter(vPts));

	return true;
}
bool TSolidGeometry::DeleteRepeatLn(vector<TSegLine>& vSls)
{
	vector<CPt3D_Pri> vPts;
	for (int i=0; i<vSls.size(); i++)
	{
		vPts.push_back(vSls[i].pt1);
		vPts.push_back(vSls[i].pt2);
	}
	if (!DeleteRepeatPt(vPts)) 
		return false;

	vSls.clear();
	TSegLine slTemp;
	for (i=0; i<vPts.size(); i+=2)
	{
		slTemp.Set(vPts[i],vPts[i+1]);
		vSls.push_back(slTemp);
	}

	return true;
}

////********************************************************************
////作者：田佰杰
////日期：2007-07-05 to 2007-07-05
////功能：根据与点的距离排序(由近到远)
////********************************************************************
bool TSolidGeometry::SortDisToPt(vector<CPt3D_Pri>& vPts, const CPt3D_Pri& ptFixed)
{
	for (int i=0; i<vPts.size()-1; i++)
	{
		for(int k=0; k<vPts.size()-1; k++)
		{
			if (DisPt(vPts[k],ptFixed) > DisPt(vPts[k+1],ptFixed))
			{
				swap(vPts[k], vPts[k+1]);
			}
		}
	}
	return true;
}
////********************************************************************
////日期：2007-07-05 to 2007-07-05
////功能：两点的距离
////********************************************************************
double TSolidGeometry::DisPt(const CPt3D_Pri& pt1, const CPt3D_Pri& pt2)
{
	return sqrt(pow(pt1.x-pt2.x,2)+pow(pt1.y-pt2.y,2)+pow(pt1.z-pt2.z,2));
}


////********************************************************************
////功能：判断点是否在线上
////********************************************************************
bool TSolidGeometry::IsPtInLine(const CPt3D_Pri& pt, const TLine	 & tl)
{
	TRayLine r1(tl.pt1,tl.pt2), r2(tl.pt2,tl.pt1);
	if (IsPtInLine(pt,r1) || IsPtInLine(pt,r2))
	{
		return true;
	}
	return false;
}
bool TSolidGeometry::IsPtInLine(const CPt3D_Pri& pt, const TRayLine& rl)
{
	CGeNorm normRayLine(rl.pt1, rl.pt2);
	normRayLine.normalize();
	CGeNorm normToPt(rl.pt1, pt);
	normToPt.normalize();

	if (normRayLine == normToPt)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool TSolidGeometry::IsPtInLine(const CPt3D_Pri &pt, const TSegLine &sl)
{
	TRayLine r1(sl.pt1,sl.pt2), r2(sl.pt2,sl.pt1);
	if (IsPtInLine(pt,r1) && IsPtInLine(pt,r2))
	{
		return true;
	}
	return false;
}


//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/07/31
////两个平面求夹角(弧度/角度)
//****************************************
double TSolidGeometry::ArcBetweenPlane(const TPlane& pl1, const TPlane& pl2)
{
	CGeNorm nm1 = pl1.Normal();
	CGeNorm nm2 = pl2.Normal();
	nm1.normalize();
	nm2.normalize();
	double dAngle = nm1.Angle2Norm(nm2);
	dAngle = dAngle > PI_R/2 ? PI_R-dAngle : dAngle;
	return dAngle;
}
double TSolidGeometry::AngleBetweenPlane(const TPlane& pl1, const TPlane& pl2)
{
	return TPlaneGeometry::Arc2Angle(ArcBetweenPlane(pl1, pl2));
}

//**********************************************************************
//<Author>:Tian Baijie
////双向延长线
//****************************************
bool TSolidGeometry::LineExtend(TLine& lnResult, 
										            const TLine& lnSource, 
                                double dLen)
{
	if(!TPlaneGeometry::LineExtend(lnResult, lnSource, dLen))
	{
		return false;
	}
	if(	!PtScaleZ(lnResult.pt1, lnSource)	|| 
		!PtScaleZ(lnResult.pt2, lnSource)	)
	{
		return false;
	}
	return true;
}
TLine TSolidGeometry::LineExtend(const TLine& lnSource, double dLen)
{
	TLine lnResult;
	if(!LineExtend(lnResult, lnSource, dLen))
	{
		lnResult = lnSource;	
	}
	return lnResult;
}
//</Add>

//<Add>=Date:2007/08/02
bool  TSolidGeometry::LineExtend(TLine& lnResult, 
                                 const TLine& lnSource, 
											           double dLenSt, 
                                 double dLenEd)
{
	if(!TPlaneGeometry::LineExtend(lnResult, lnSource, dLenSt, dLenEd))
	{
		return false;
	}
	if(!PtScaleZ(lnResult.pt1, lnSource) || !PtScaleZ(lnResult.pt2, lnSource))
	{
		return false;
	}
	return true;
}
TLine TSolidGeometry::LineExtend(const TLine& lnSource, 
											           double dLenSt, 
                                 double dLenEd)
{
	TLine lnResult;
	if(!LineExtend(lnResult, lnSource, dLenSt, dLenSt))
	{
		lnResult = lnSource;	
	}
	return lnResult;
}
//</Add>
//**********

//**********************************************************************
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
bool TSolidGeometry::LineParallel(TLine& lnResult, const TLine& lnSource,
										const CPt3D_Pri & ptWay, double dis)
{
	if(!TPlaneGeometry::LineParallel(lnResult, lnSource, ptWay, dis))
	{
		return false;
	}
	if(	!PtScaleZ(lnResult.pt1, lnSource)	|| 
		!PtScaleZ(lnResult.pt2, lnSource)	)
	{
		return false;
	}
	return true;
}
TLine TSolidGeometry::LineParallel(const TLine& lnSource,
										const CPt3D_Pri & ptWay, double dis)
{
	TLine lnResult;
	if(!LineParallel(lnResult, lnSource, ptWay, dis))
	{
		lnResult = lnSource;
	}
	return lnResult;
}
bool TSolidGeometry::LineParallel(TLine& lnResult, const TLine& lnSource,
													 const CPt3D_Pri & ptWay)
{
	double dis = DisPtToLine(ptWay, lnSource);
	return LineParallel(lnResult, lnSource, ptWay, dis);
}
TLine TSolidGeometry::LineParallel(const TLine& lnSource,
													const CPt3D_Pri & ptWay)
{
	TLine lnResult;
	if(!LineParallel(lnResult, lnSource, ptWay))
	{
		lnResult = lnSource;
	}
	return lnResult;
}
//</Add>
//</Author>
//**********


//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/01
////功能：点到直线的距离
//****************************************
double TSolidGeometry::DisPtToLine(const CPt3D_Pri& pt, const TLine& ln)
{
	CPt3D_Pri ptPedal = PtPedal(pt, ln);
	return DisPt(pt, ptPedal);
}
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/01
////功能：获得点在直线上的垂足。
//****************************************
CPt3D_Pri TSolidGeometry::PtPedal(const CPt3D_Pri & ptBase, const TLine& ll)
{
	CPt3D_Pri ptResult = TPlaneGeometry::PtPedal(ptBase, ll);
	if(!PtScaleZ(ptResult, ll))
	{
		return gc_ptOrg;
	}
	return ptResult;
}
//</Add>
}
//</Author>
//**********





