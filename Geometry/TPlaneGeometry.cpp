		// TPlaneGeometry.cpp: implementation of the TPlane class.
		//
		//////////////////////////////////////////////////////////////////////

		//**********************************************************************
		//<Author>:Tian Baijie
		//****************************************


		#include "stdafx.h"
		#include "TPlaneGeometry.h"
		#include "TGlobal.h"

		#include <assert.h>

		#ifdef _DEBUG
		#undef THIS_FILE
		static char THIS_FILE[]=__FILE__;
		#define new DEBUG_NEW
		#endif

		//////////////////////////////////////////////////////////////////////
		// Construction/Destruction
		//////////////////////////////////////////////////////////////////////

		namespace TIAN_GA_BETTER{


		using namespace std;


		/***********************************************************************
								TLine
		***********************************************************************/

		TLine::TLine(const TPoint& p1,const TPoint& p2)
		:pt1(p1)
		,pt2(p2)
		MCT_INIT2("GA:TLine")
		{}
		TLine::TLine()
		MCT_INIT1("GA:TLine")
		{pt1=TPoint(0,0,0);pt2=TPoint(1,1,1);}
		TLine::~TLine()
		{}
		TRayLine::TRayLine(const TPoint& p1,const TPoint& p2)
		:TLine(p1,p2)
		MCT_INIT2("GA:TRayLine")//pt1(p1),pt2(p2)
		{}
		TRayLine::~TRayLine()
		{}
		TSegLine::TSegLine(const TPoint& p1,const TPoint& p2)
		:TRayLine(p1,p2)
		MCT_INIT2("GA:TSegLine")//pt1(p1),pt2(p2)
		{}
		TSegLine::~TSegLine()
		{}	

		void TLine::Set(TPoint pt, CGeNorm normal, double dis)
		{
			normal.normalize();
			pt1 = pt;
			pt2 = pt.PolarTo(dis, &normal);
		}
		void TLine::Set(const TPoint& p1,const TPoint& p2)
		{
			pt1 = p1;
			pt2 = p2;
		}
		void TLine::Reverse()
		{
			TPoint pt;
			pt  = pt1;
			pt1 = pt2;
			pt2 = pt;
		}
		void TLine::PedalUnclockwise(EOrgPt eOrg)
		{
			if (eOrg != TPO_ORGPT1 && eOrg != TPO_ORGPT2)	
				return;
			if (eOrg == TPO_ORGPT2)	
				Reverse();

			pt2 = pt2 - pt1;
			pt2.RotateZ(90.0);
			pt2 = pt2 + pt1;

			if (eOrg == TPO_ORGPT2)					
				Reverse();
		}
		void TLine::PedalClockwise(EOrgPt eOrg)
		{
			if (eOrg != TPO_ORGPT1 && eOrg != TPO_ORGPT2)	return;
			if (eOrg == TPO_ORGPT2)	Reverse();

			pt2 = pt2 - pt1;
			pt2.RotateZ(270.0);
			pt2 = pt2 + pt1;

			if (eOrg == TPO_ORGPT2)					Reverse();
		}

		bool TLine::IsPtInLine(const TPoint& pt) const
		{
			CGeNorm nmLn1(pt1, pt2);
			nmLn1.normalize();
			CGeNorm nmLn2(pt2, pt1);
			nmLn2.normalize();
			CGeNorm nmPt(pt1, pt );
			nmPt.normalize();
			return nmPt == nmLn1 || nmPt == nmLn2 ? true : false;
		}
		bool TRayLine::IsPtInLine(const TPoint& pt) const
		{
			CGeNorm nmLn(pt1, pt2);
			nmLn.normalize();
			CGeNorm nmPt(pt1, pt );
			nmPt.normalize();
			return nmPt == nmLn ? true : false;
		}

		bool TSegLine::IsPtInLine(const TPoint& pt) const
		{
			CGeNorm nmLn1(pt1, pt2);
			nmLn1.normalize();
			CGeNorm nmLn2(pt2, pt1);
			nmLn2.normalize();
			CGeNorm nmPt(pt1, pt );
			nmPt.normalize();
			return nmPt == nmLn1 && nmPt == nmLn2 ? true : false;
		}


		/************************************************************************/
		/*                   TArc                                               */
		/************************************************************************/
		TArc::TArc()
		:_ptCentre(gc_ptOrg)
		,_r(0)
		,_stArc(0)
		,_edArc(0)
		MCT_INIT2("GA:TArc")
		{
		}
		TArc::TArc(TPoint ptCentre, double r, double stArc, double edArc)
		:_ptCentre(ptCentre)
		,_r(r)
		,_stArc(stArc)
		,_edArc(edArc)
		MCT_INIT2("GA:TArc")
		{
		}
		TArc::TArc(TPoint ptCentre, double r, TPoint ptSt, TPoint ptEd)
		:_ptCentre(ptCentre)
		,_r(r)
		MCT_INIT2("GA:TArc")
		{
			Init(ptSt,ptEd);
		}
		TArc::TArc(TPoint pt1, TPoint pt2, TPoint pt3)
		MCT_INIT1("GA:TArc")
		{
			Init(pt1,pt2,pt3);
		}

		TArc::~TArc()
		{}

		void TArc::Set(TPoint ptCentre, double r, double stArc, double edArc)
		{
			_ptCentre = ptCentre;
			_r				= r;
			_stArc		= stArc;
			_edArc		= edArc;
		}

		void TArc::Set(TPoint ptCentre, double r, TPoint ptSt, TPoint ptEd)
		{
			_ptCentre = ptCentre;
			_r				= r;
			Init(ptSt, ptEd);
		}

		void TArc::Set(TPoint pt1, TPoint pt2, TPoint pt3)
		{
			Init(pt1,pt2,pt3);
		}

		TPoint TArc::PtSt() const
		{
			TPoint ptSt;
			ptSt.x = _ptCentre.x + _r*cos(_stArc);
			ptSt.y = _ptCentre.y + _r*sin(_stArc);
			ptSt.z = 0;
			return ptSt;
		}
		TPoint TArc::PtEd() const
		{
			TPoint ptEd;
			ptEd.x = _ptCentre.x + _r*cos(_edArc);
			ptEd.y = _ptCentre.y + _r*sin(_edArc);
			ptEd.z = 0;
			return ptEd;
		}
		TLine TArc::LineSt() const
		{
			return TLine(_ptCentre, PtSt());
		}
		TLine TArc::LineEd() const
		{
			return TLine(_ptCentre, PtEd());
		}


		void TArc::Init(TPoint ptSt, TPoint ptEd)
		{
		//	CGeNorm gnSt(_ptCentre, ptSt);	////起始点对圆心的差值
		//	CGeNorm gnEd(_ptCentre, ptEd);	////终止点对圆心的差值
			_stArc = TPlaneGeometry::Radian(ptSt, _ptCentre);
			_edArc = TPlaneGeometry::Radian(ptEd, _ptCentre);
		}
		////获得穿过三点的正圆的圆心和半径
		////如果三点成直线返回值：FALSE
		bool TArc::Init(TPoint pt1,TPoint pt2,TPoint pt3)
		{
			double x1=pt1.x, x2=pt2.x, x3=pt3.x;
			double y1=pt1.y, y2=pt2.y, y3=pt3.y;

			if((x1==x2)&&(x2==x3))
			{
				return false;
			}
			if((x1!=x2)&&(x2!=x3))
			{
				double k1 = (y2-y1)/(x2-x1);
				double k2 = (y2-y3)/(x2-x3);
				if(k1==k2)
				{
					return false;
				}
			}
			
			double a=2*(x2-x1);
			double b=2*(y2-y1);
			double c=x2*x2+y2*y2-x1*x1-y1*y1;
			double d=2*(x3-x2);
			double e=2*(y3-y2);
			double f=x3*x3+y3*y3-x2*x2-y2*y2;
			double x=(b*f-e*c)/(b*d-e*a);
			double y=(d*c-a*f)/(b*d-e*a);
			double r=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));

			_ptCentre.x = x;
			_ptCentre.y = y;
			_ptCentre.z = 0;
			_r = r;

			double asin1 = TPlaneGeometry::Radian(pt1, _ptCentre);
			double asin2 = TPlaneGeometry::Radian(pt2, _ptCentre);
			double asin3 = TPlaneGeometry::Radian(pt3, _ptCentre);
			bool bIncrease = IsIncrease(asin1,asin2,asin3);////获得3点的方向(是否逆时针)

			if (bIncrease)
			{
				Init(pt1,pt3);
			}
			else
			{
				Init(pt3,pt1);
			}


			return false;
		}
		bool TArc::IsIncrease(double asin1, double asin2, double asin3)
		{
			if(asin1<asin3)
			{
				if(asin1<asin2 && asin2<asin3)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
			else
			{
				if(asin1>asin2 && asin2>asin3)
				{
					return FALSE;
				}
				else
				{
					return TRUE;
				}
			}
		}

		double TArc::Length() const
		{
			return _r*(TPlaneGeometry::Radian(_edArc-_stArc));
		}
		double TArc::LenPtToCentre(const TPoint& pt) const
		{
			return sqrt(pow(_ptCentre.x-pt.x,2)+pow(_ptCentre.y-pt.y,2));
		}


		/***********************************************************************
								TPlaneGeometry
		***********************************************************************/
		//////////////////////////////////////////////////////////
		TPlaneGeometry::TPlaneGeometry()
		MCT_INIT1("GA:TPlaneGeometry")
		{

		}

		TPlaneGeometry::~TPlaneGeometry()
		{

		}
		TPlaneGeometry& TPlaneGeometry::Instance()
		{
			static TPlaneGeometry tool;
			return tool;
		}

		////直线和线段
		bool TPlaneGeometry::Intersect(const TLine &ll, const TSegLine& sl,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										ll.pt1.x,ll.pt1.y,ll.pt2.x,ll.pt2.y,
										sl.pt1.x,sl.pt1.y,sl.pt2.x,sl.pt2.y
										);

			if (bResult && IsIntersectInsideLine(pt, sl))	
			{
				return true;
			}

			return false;
		}


		////两条直线
		bool TPlaneGeometry::Intersect(const TLine &ll1, const TLine &ll2,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										ll1.pt1.x, ll1.pt1.y,ll1.pt2.x,ll1.pt2.y,
										ll2.pt1.x, ll2.pt1.y,ll2.pt2.x,ll2.pt2.y
										);
			if (bResult)	////包括延长相交适用于直线
			{
				return true;
			}

			return false;
		}

		////直线和射线
		bool TPlaneGeometry::Intersect(const TLine &ll1, const TRayLine &rl,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										ll1.pt1.x, ll1.pt1.y,ll1.pt2.x,ll1.pt2.y,
										rl.pt1.x,  rl.pt1.y, rl.pt2.x, rl.pt2.y
										);

			if (bResult && IsIntersectInsideLine(pt, rl))	
			{
				return true;
			}

			return false;
		}

		////两条线段(暂不考虑z坐标)
		bool TPlaneGeometry::Intersect(const TSegLine &sl1, const TSegLine &sl2,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										sl1.pt1.x, sl1.pt1.y,sl1.pt2.x,sl1.pt2.y,
										sl2.pt1.x, sl2.pt1.y,sl2.pt2.x,sl2.pt2.y
										);
			if (bResult							&& 
				IsIntersectInsideLine(pt, sl1)	&& 
				IsIntersectInsideLine(pt, sl2)	)	////直接相交适用于线段
			{
				return true;
			}

			return false;
		}

		////线段和射线
		bool TPlaneGeometry::Intersect(const TSegLine &sl, const TRayLine &rl,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										sl.pt1.x, sl.pt1.y, sl.pt2.x, sl.pt2.y,
										rl.pt1.x, rl.pt1.y, rl.pt2.x, rl.pt2.y
										);

			if (bResult							&& 
				IsIntersectInsideLine(pt, rl)	&&
				IsIntersectInsideLine(pt, sl)	)	
			{
				return true;
			}

			return false;
		}

		////两条射线
		bool TPlaneGeometry::Intersect(const TRayLine &rl1, const TRayLine &rl2,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										rl1.pt1.x, rl1.pt1.y, rl1.pt2.x, rl1.pt2.y,
										rl2.pt1.x, rl2.pt1.y, rl2.pt2.x, rl2.pt2.y
										);

			if(bResult && IsIntersectInsideLine(pt, rl1) && IsIntersectInsideLine(pt, rl2)	)	
			{
				return true;
			}

			return false;
		}




		////********************************************************************
		////功能：判断平面上的两条线交点
		////返回：true有交点,false平行或者重合
		////参数：承接交点的坐标和两条线(4个点)的坐标
		////注意：必须判断其返回值以确定是否能够相交
		////********************************************************************
		bool TPlaneGeometry::intersect_line2line_2d(double& destpt_x, double& destpt_y, 
											  double line1st_x, double line1st_y,
											  double line1ed_x, double line1ed_y,
											  double line2st_x, double line2st_y, 
											  double line2ed_x, double line2ed_y)
		{
			double a=0,b=0,c=0,d=0,e=0;
			double P1[2],P2[2],P3[2],P4[2],P[2];
			P1[0] = line1st_x,P1[1] = line1st_y;
			P2[0] = line1ed_x,P2[1] = line1ed_y;
			P3[0] = line2st_x,P3[1] = line2st_y;
			P4[0] = line2ed_x,P4[1] = line2ed_y;
			a = P2[0] - P1[0];       ////线段p1p2的x坐标差
			b = P4[0] - P3[0];       ////线段p3p4的x坐标差
			c = P2[1] - P1[1];       ////线段p1p2的y坐标差
			d = P4[1] - P3[1];       ////线段p3p4的y坐标差
			e = a*d - b*c;
			if (fabs(e) < FLOAT_PRECISION)    
				return false;    ////两线段平行或者重合
			P[1] = (c*d*(P3[0] - P1[0]) + a*d*P1[1] - b*c*P3[1])/e;
			if (fabs(c)<FLOAT_PRECISION) 
				P[0] = P3[0] + b*(P[1]-P3[1])/d;
			else 
				P[0] = P1[0] + a*(P[1]- P1[1])/c;

			double temp1 = (P[0]-P1[0])*(P[0]-P2[0]);
			double temp2 = (P[0]-P3[0])*(P[0]-P4[0]);
				
			destpt_x = P[0];
			destpt_y = P[1];

			return true;
		}

		////********************************************************************
		////功能：判断交点是否在直线上
		////注意：交点pt必须是已知在sl直线上的点(已经非必须)
		////********************************************************************
		bool TPlaneGeometry::IsIntersectInsideLine(const TPoint& pt, const TLine	 & tl)
		{
			TRayLine r1(tl.pt1,tl.pt2), r2(tl.pt2,tl.pt1);
			if (IsIntersectInsideLine(pt,r1) || IsIntersectInsideLine(pt,r2))
			{
				return true;
			}
			return false;
		}

		////********************************************************************
		////功能：判断交点是否在射线上
		////注意：交点pt必须是已知在rl直线上的点(已经非必须)
		////********************************************************************
		bool TPlaneGeometry::IsIntersectInsideLine(const TPoint& pt, const TRayLine& rl)
		{
			CGeNorm normRayLine(rl.pt1, rl.pt2);
			normRayLine.m_z;
			normRayLine.normalize();
			CGeNorm normToPt(rl.pt1, pt);
			normRayLine.m_z;
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

		////********************************************************************
		////功能：判断交点是否在线段上
		////注意：交点pt必须是已知在sl直线上的点(已经非必须)
		////********************************************************************
		bool TPlaneGeometry::IsIntersectInsideLine(const TPoint &pt, const TSegLine &sl)
		{
			CGeNorm normSegLine(sl.pt1, sl.pt2);
			CGeNorm normToPt(sl.pt1, pt);
			if (normToPt.len() > normSegLine.len())
			{
				return false;
			}
			normSegLine.normalize();
			normToPt.normalize();
			if (normSegLine == normToPt)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		////********************************************************************
		////功能：变成垂直线
		////注意：以pt1为中心，旋转90度
		////********************************************************************
		TLine TPlaneGeometry::NormLine(TLine &ll) 
		{
			ll.pt2 = ll.pt2 - ll.pt1;
			ll.pt2.RotateZ(90.0);
			ll.pt2 = ll.pt2 + ll.pt1;
			return ll;
		}
		TLine TPlaneGeometry::LinePedal(const TPoint& pt, const TLine& tl)
		{
			if (pt == tl.pt1)
			{
				return LinePedal(tl);
			}
			if(pt == tl.pt2)
			{
				return LinePedal(TLine(tl.pt2,tl.pt1));
			}
			TPoint ptPedal = PtPedal(pt, tl);
			TPoint ptInLine= ptPedal + (tl.pt2 - tl.pt1);
			TLine tLine(ptPedal, ptInLine);
			NormLine(tLine);
			return tLine;
		}
		TLine TPlaneGeometry::LinePedal(const TLine& tl)
		{
			TLine result = tl;
			NormLine(result);
			return result;
		}

		////********************************************************************
		////功能：返回第几坐标轴（1==X, 2==Y, 3== -X, 4== -Y, other == 0）
		////********************************************************************
		int TPlaneGeometry::RadianToCoordAxis(double dRadian)
		{
			dRadian = Radian(dRadian);
			if( TEquFloat(dRadian,0))
			{
				return 1;
			}
			if( TEquFloat(dRadian,PI_R/2))
			{
				return 2;
			}
			if( TEquFloat(dRadian,PI_R))
			{
				return 3;
			}
			if( TEquFloat(dRadian,PI_R*3/2))
			{
				return 4;
			}
			return 0;
		}

		////********************************************************************
		////功能：返回第几象限
		////********************************************************************
		int TPlaneGeometry::RadianToQuadrant(double dRadian)
		{
			dRadian = Radian(dRadian);
			if( TMoreEqu(dRadian,0) &&
				TLessThen(dRadian,PI_R/2))
			{
				return 1;
			}
			if( TMoreEqu(dRadian,PI_R/2) &&
				TLessThen (dRadian,PI_R))
			{
				return 2;
			}
			if( TMoreEqu(dRadian,PI_R) &&
				TLessThen (dRadian,PI_R*3/2))
			{
				return 3;
			}
			if( TMoreEqu(dRadian,PI_R*3/2) &&
				TLessThen (dRadian,PI_R*2))
			{
				return 4;
			}
			return 0;
		}
		////********************************************************************
		////功能：返回第几象限(第1象限不含0含π/2)
		////********************************************************************
		int TPlaneGeometry::RadianToQuadrantRe(double dRadian)
		{
			dRadian = Radian(dRadian);
			if( TMoreThen(dRadian,0) &&
				TLessEqu(dRadian,PI_R/2))
			{
				return 1;
			}
			if( TMoreThen(dRadian,PI_R/2) &&
				TLessEqu(dRadian,PI_R))
			{
				return 2;
			}
			if( TMoreThen(dRadian,PI_R) &&
				TLessEqu(dRadian,PI_R*3/2))
			{
				return 3;
			}
			if( TMoreThen(dRadian,PI_R*3/2) &&
				TLessEqu(dRadian,PI_R*2)	||
				TEquFloat(dRadian, 0))
			{
				return 4;
			}
			return 0;
		}
		////********************************************************************
		////功能：获得一个点的弧度(与X轴正方向的正夹角)
		////注意：返回值在0～2π(不含2π)之间
		////********************************************************************
		double TPlaneGeometry::RadianToQuadrant14(double dRadian)
		{
			//确保调整到0~2π之间
			dRadian = Radian(dRadian);
			if( TMoreThen(dRadian,PI_R/2) &&
				TLessEqu (dRadian,PI_R*3/2))
			{
				dRadian += PI_R;
			}
			dRadian = Radian(dRadian);
			return dRadian;
		}
		////********************************************************************
		////功能：获得一个点的弧度(与X轴正方向的正夹角)
		////注意：返回值在0～2π(不含2π)之间
		////********************************************************************
		double TPlaneGeometry::Radian(const TPoint& pt, const TPoint& ptOrg)
		{
			if(pt == ptOrg)
			{
				return 0;
			}
			TPoint ptTe = pt;
			ptTe.z = 0;
			CGeNorm normPt(ptOrg, ptTe);
			return Radian(normPt);
		}
		double TPlaneGeometry::Radian(const TLine& tl)
		{
			return Radian(tl.pt2, tl.pt1);
		}
		double TPlaneGeometry::Radian(const CGeNorm& norm)
		{
			CGeNorm normTe = norm;
			normTe.m_z = 0;
			if (normTe == CGeNorm(0,0,0)) {
				return 0;
			}
			CGeNorm normX(TPoint(0,0,0),TPoint(1,0,0));
			double dRadian = normTe.Angle2Norm(normX);
			return normTe.m_y >=0 ? dRadian : 2*PI_R-dRadian;
		}
		double TPlaneGeometry::Radian(double dRadian)
		{
			while (dRadian<0)
			{
				dRadian += 2*PI_R;
			}
			while (dRadian>=2*PI_R)
			{
				dRadian -= 2*PI_R;
			}
			return dRadian;
		}

		////********************************************************************
		////功能：判断点是否在三点形成的凸角内
		////注意：pt2为角顶点
		////********************************************************************
		bool TPlaneGeometry::IsPtInSalient(const TPoint& pt, 
							const TPoint& pt1, const TPoint& pt2, const TPoint& pt3)
		{
			CGeNorm normpt1(pt2,pt1);
			CGeNorm normpt3(pt2,pt3);
			CGeNorm normpt (pt2,pt);

			double dRadian1 = Radian(normpt1);
			double dRadian3 = Radian(normpt3);
			double dRadianpt= Radian(normpt);

			double dRadianMax = max(dRadian1, dRadian3);
			double dRadianMin = min(dRadian1, dRadian3);

			if ((dRadianMax - dRadianMin) > PI_R)
			{
				dRadianMin += 2*PI_R;
				if (dRadianpt < PI_R)
				{
					dRadianpt += 2*PI_R;
				}
			}
			if (dRadianMin < dRadianpt && dRadianpt < dRadianMax)
			{
				return true;
			}
			return false;
		}


		////********************************************************************
		////作者：田佰杰
		////功能：获得在平行线上对应的点。
		////参数：ptInput参照点(在基线上)，ll基线，ptConsult参照点(在平行线上)
		////注意：由基线点ptInput求出平行线点函数返回值
		////********************************************************************
		TPoint TPlaneGeometry::PtInParallel(const TPoint & ptBase,
										const TLine ll, const TPoint& ptConsult)
		{
			TLine llParallel	= LineParallel(ptConsult,ll);	////得到平行线

			return PtPedal(ptBase, llParallel);
		}
		////********************************************************************
		////作者：田佰杰
		////功能：获得穿过已知点的平行线。
		////********************************************************************
		TLine TPlaneGeometry::LineParallel(const TPoint & ptBase, const TLine& ll)
		{
			TLine llResult(TPoint(ptBase), (ptBase+(ll.pt2-ll.pt1)));
			return llResult;
		}
		//**********************************************************************
		//<Author>:Tian Baijie
		//<Add>=Date:2007/07/30
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
		bool TPlaneGeometry::LineParallel(TLine& lnResult, const TLine& lnSource,
												const TPoint & ptWay, double dis)
		{
			////如果方向控制点在源直线上，则无法控制方向。
			TPoint ptWayCopy = ptWay;
			ptWayCopy.z = 0;
			if(IsPtInLine(ptWayCopy, lnSource))			
			{
				return false;
			}
			TPoint ptPedal = PtPedal(ptWayCopy, lnSource);
			ptPedal.z = 0;
			CGeNorm nmPedal(ptPedal, ptWayCopy);
			nmPedal.normalize();
			TPoint ptS1 = lnSource.pt1;
			TPoint ptD1 = ptS1.PolarTo(dis, &nmPedal);
			TPoint ptS2 = lnSource.pt2;
			TPoint ptD2 = ptS2.PolarTo(dis, &nmPedal);
			lnResult.Set(ptD1, ptD2);
			return true;
		}
		TLine TPlaneGeometry::LineParallel(const TLine& lnSource,
												const TPoint & ptWay, double dis)
		{
			TLine lnResult;
			if(!LineParallel(lnResult, lnSource, ptWay, dis))
			{
				lnResult = lnSource;
			}
			return lnResult;
		}
		bool TPlaneGeometry::LineParallel(TLine& lnResult, const TLine& lnSource,
															 const TPoint & ptWay)
		{
			double dis = DisPtToLine(ptWay, lnSource);
			return LineParallel(lnResult, lnSource, ptWay, dis);
		}
		TLine TPlaneGeometry::LineParallel(const TLine& lnSource,
															const TPoint & ptWay)
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

		////********************************************************************
		////作者：田佰杰
		////功能：获得点在直线上的垂足。
		////********************************************************************
		TPoint TPlaneGeometry::PtPedal(const TPoint & ptBase, const TLine& ll)
		{
			//如果线本身是一个点
			if(ll.pt1 == ll.pt2)
			{
				return ll.pt1;
			}
			//如果点在线上
			if(IsPtInLine(ptBase, ll))	
			{
				return ptBase;
			}

			TLine llParallel	= LineParallel(ptBase,ll);	////得到平行线
			NormLine(llParallel);

			TPoint ptResult;
			Intersect(TLine(ll),llParallel,ptResult);
			return ptResult;
		}

		////********************************************************************
		////作者：田佰杰
		////功能：获得角分线。
		////********************************************************************
		double TPlaneGeometry::MidArc(const TArc & arc)
		{
			double arcMid = (arc._edArc + arc._stArc) /2;
			if (arc._stArc > arc._edArc)
			{
				arcMid+=PI_R;
			}
			arcMid = Radian(arcMid);
			return arcMid;
		}
		TPoint TPlaneGeometry::MidArcPt(const TArc & arc)
		{
			double arcMid = MidArc(arc);
			TPoint ptMid;
			ptMid.x = arc._ptCentre.x + arc._r*cos(arcMid);
			ptMid.y = arc._ptCentre.y + arc._r*sin(arcMid);
			ptMid.z = 0;
			return ptMid;
		}
		TLine TPlaneGeometry::MidArcLine(const TArc & arc)
		{
			TPoint ptMid = MidArcPt(arc);
			return TLine(TPoint(arc._ptCentre), ptMid);
		}

		////********************************************************************
		////作者：田佰杰
		////功能：获得角分线点的外切线。
		////********************************************************************
		TLine TPlaneGeometry::TangentLine(const TArc & arc)
		{
			TLine llMid = MidArcLine(arc);
			TLine llReverseMid(llMid.pt2,llMid.pt1);
			NormLine(llReverseMid);
			TLine llTangentLine(TPoint(0,0,0),TPoint(1,1,0));
			Intersect(llReverseMid,arc.LineSt(), llTangentLine.pt1);
			Intersect(llReverseMid,arc.LineEd(), llTangentLine.pt2);
			return llTangentLine;
		}

		////********************************************************************
		////作者：田佰杰
		////日期：2007-04-24 to 2007-04-24
		////功能：角度弧度互换。
		////********************************************************************
		double TPlaneGeometry::Angle2Arc(double angle)
		{
			return angle * PI_R / 180.0;
		}
		double TPlaneGeometry::Arc2Angle(double arc)
		{
			return arc * 180.0 / PI_R;
		}

		////********************************************************************
		////作者：田佰杰
		////日期：2007-05-15 to 2007-04-15
		////功能：在给定的线上截取一段。
		////********************************************************************
		TLine TPlaneGeometry::LineIntersect(const TLine& tl, double len, EOrgPt eOrg)
		{
			if (!(eOrg == TPO_ORGPT1 || eOrg == TPO_ORGPT2))	return tl;

			TLine tlOld = eOrg == TPO_ORGPT1 ? tl : Reverse(tl);
			CGeNorm norm(tlOld.pt1, tlOld.pt2);
			norm.normalize();
			TPoint ptNew = tlOld.pt1.PolarTo((float)len, &norm);
			TLine tlNew(tlOld.pt1, ptNew);

			return eOrg == TPO_ORGPT1 ? tlNew : Reverse(tlNew);
		}

		////********************************************************************
		////日期：2007-05-20 to 2007-04-20
		////功能：点到线的距离。
		////注意：返回true则垂足在线段上，返回false则垂足在线延长线上
		////********************************************************************
		bool TPlaneGeometry::Length(double & len, const TPoint& pt, const TLine& tl)
		{
			TPoint ptPedal = PtPedal(pt, tl);
			len = TLine(pt, ptPedal).Length();
			return true;
		}

		bool TPlaneGeometry::Length(double & len, const TPoint& pt, const TRayLine& rl)
		{
			TPoint ptPedal = PtPedal(pt, rl);
			len = TLine(pt, ptPedal).Length();
			if (IsPtInLine(ptPedal, rl))
			{
				return true;
			}
			return false;
		}

		bool TPlaneGeometry::Length(double & len, const TPoint& pt, const TSegLine& sl)
		{
			TPoint ptPedal = PtPedal(pt, sl);
			len = TLine(pt, ptPedal).Length();
			if (IsPtInLine(ptPedal, sl))
			{
				return true;
			}
			return false;
		}
		////********************************************************************
		////日期：2007-07-05 to 2007-07-05
		////功能：两点的距离
		////********************************************************************
		double TPlaneGeometry::DisPt(const TPoint& pt1, const TPoint& pt2)
		{
			return sqrt(pow(pt1.x-pt2.x,2)+pow(pt1.y-pt2.y,2));
		}
		//**********************************************************************
		//<Add>=Date:2007/07/30
		////功能：点到直线的距离
		//****************************************
		double TPlaneGeometry::DisPtToLine(const TPoint& pt, const TLine& ln)
		{
			TPoint ptS = pt;
			ptS.z = 0;
			TPoint ptPedal = PtPedal(ptS, ln);
			ptPedal.z = 0;
			return DisPt(ptS, ptPedal);
		}
		//**********************************************************************
		//<Add>=Date:2007/07/30
		////功能：点到直线的距离，到特定向量上的映射（带方向+-）
		////方向：pt1 -> pt2
		//****************************************
		double TPlaneGeometry::DisPtByNormal(
								TPoint pt1, TPoint pt2, CGeNorm nm)
		{
			//以pt1和nm作直线，求pt2到直线的垂足ptPd，求pt1和ptPd的距离和方向nmPd
			//根据nm和nmPd觉得距离+-符号(相等为+)
			TLine ln(pt1, nm);
			TPoint ptPd = PtPedal(pt2, ln);
			double dis = DisPt(pt1, ptPd);

			CGeNorm nmPd(pt1, ptPd);
			nmPd.normalize();
			nm.normalize();

			return nm == nmPd ? dis : -dis;
		}
		//**********************************************************************
		//<Add>=Date:2007/07/30
		////功能：点到直线的距离，到特定向量上的映射（带方向+-）
		////方向：ln -> pt
		//****************************************
		double TPlaneGeometry::DisPtToLineByNormal(
								TPoint pt, TLine ln, CGeNorm nm)
		{
			//点在直线的垂足求出点和垂足在向量上的距离
			TPoint ptPdLn = PtPedal(pt, ln);
			return DisPtByNormal(ptPdLn, pt, nm);
		}
		//**********


		////********************************************************************
		////作者：田佰杰
		////日期：2007-05-20 to 2007-04-20
		////功能：判断点是否在弧内
		////********************************************************************
		bool TPlaneGeometry::IsPtInArc(const TPoint& pt, const TArc& arc)
		{
			double rArc = Radian(pt, arc._ptCentre);
			if (arc._edArc > arc._stArc)
			{
				if (arc._stArc <= rArc && rArc <=  arc._edArc)
				{
					return true;
				}
			}
			else
			{
				if (arc._stArc <= rArc || rArc <=  arc._edArc)
				{
					return true;
				}
			}
			return false;
		}

		////********************************************************************
		////作者：田佰杰
		////日期：2007-07-03 to 2007-07-03
		////功能：判断点是否在多边形内
		////********************************************************************
		bool TPlaneGeometry::IsPtInPolygon(const TPoint& pt, 
										   const TPoint * pPtPolygon, int nCount)
		{
			if(nCount < 2) return false;
			int nCross = 0; 
			for (int i = 0; i < nCount; i++) 
			{ 
				TPoint p1 = pPtPolygon[i]; 
				TPoint p2 = pPtPolygon[(i+1) % nCount]; 
				//// 求解 y=p.y 与 p1p2 的交点 
				if (TEquFloat(p1.y,p2.y) ) //// p1p2 与 y=p0.y平行 
					continue; 
		//		if ( pt.y < min(p1.y, p2.y) ) //// 交点在p1p2延长线上 
				if (TLessThen(pt.y, min(p1.y, p2.y)) ) //// 交点在p1p2延长线上 
					continue; 
		//		if ( pt.y >= max(p1.y, p2.y) ) //// 交点在p1p2延长线上 
				if (TMoreEqu( pt.y, max(p1.y, p2.y)) ) //// 交点在p1p2延长线上 
					continue; 
				//// 求交点的 X 坐标 
				double x =	(double)(pt.y-p1.y) * 
							(double)(p2.x-p1.x) / 
							(double)(p2.y-p1.y) + p1.x; 
				if (TMoreThen(x, pt.x) ) 
					nCross++; //// 只统计单边交点 
			} 
			//// 单边交点为偶数，点在多边形之外 --- 
			return (bool)(nCross % 2 == 1); 
		}

		bool TPlaneGeometry::IsPtInPolygon(const TPoint& pt, 
										   const vector<TPoint>& vPtPlolygons)
		{
			int nSizePolygon = vPtPlolygons.size();
			if(nSizePolygon < 2) return false;
			////若点恰好在边线上，则直接认定点在多边形内。
			TSegLine slBorder;
			for (int i=0; i< nSizePolygon; i++)
			{
				slBorder.Set(vPtPlolygons[i], vPtPlolygons[(i+1)%nSizePolygon]);
				if (IsPtInLine(pt, slBorder)) {
					return true;
				}
			}
			////判断点是否在多边形内
			return IsPtInPolygon(pt, &vPtPlolygons[0], nSizePolygon);
		}


		////********************************************************************
		////作者：田佰杰
		////日期：2007-07-05 to 2007-07-05
		////功能：线穿过多边形内，求出多边形内、外线段组。
		////********************************************************************
		bool TPlaneGeometry::LineInPolygon(const TSegLine& sl,const vector<TPoint>& vPtsPolygon,
							vector<TSegLine>& vSlsInside, vector<TSegLine>& vSlsOutside)
		{
			int nSizePolygon = vPtsPolygon.size();
			if (nSizePolygon < 2)	return false;

			TSegLine slIn(sl);

			TPoint ptAcross;								////线段与各边交点(临时)
			TSegLine slBorder;							////各边(临时)
			vector<TPoint> vPtsAcross;					////线段与各边交点数组
			vPtsAcross.push_back(sl.pt1);				////把原始线段的两个端点加入
			for (int i=0; i< nSizePolygon; i++)
			{
				slBorder.Set(vPtsPolygon[i], vPtsPolygon[(i+1)%nSizePolygon]);
				slIn.pt1.z = slIn.pt2.z = slBorder.pt1.z = slBorder.pt2.z = 0.0;
				if((slIn.pt1 == slBorder.pt1 && slIn.pt2 == slBorder.pt2)||
					(slIn.pt1 ==  slBorder.pt2&& slIn.pt2 == slBorder.pt1))
				{
					continue;			
				}
				else if (Intersect(slIn, slBorder, ptAcross))
				{
					if (!(IsPtEqu(vPtsAcross[vPtsAcross.size()-1] , ptAcross)))
						vPtsAcross.push_back(ptAcross);		////交点数组
				}
			}
			if (!(IsPtEqu(vPtsAcross[vPtsAcross.size()-1] , sl.pt2)))
				vPtsAcross.push_back(sl.pt2);
			
			SortDisToPt(vPtsAcross, sl.pt1);			////排序

			TSegLine slTemp;								
			for (i=0; i<vPtsAcross.size()-1; i++)
			{											////中点在多边形内
				slTemp.Set(vPtsAcross[i], vPtsAcross[i+1]);
			if(IsPtInPolygon(slTemp.PtCenter(), vPtsPolygon)){
					vSlsInside.push_back(slTemp);
			}
			else{
					vSlsOutside.push_back(slTemp);
			}
			}

			return true;
		}

		////********************************************************************
		////作者：田佰杰
		////日期：2007-07-05 to 2007-07-05
		////功能：根据与点的距离排序(由近到远)
		////********************************************************************
		bool TPlaneGeometry::SortDisToPt(vector<TPoint>& vPts, const TPoint& ptFixed)
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



		BOOL TPlaneGeometry::IfAoRect(vector<TPoint>& pt3dsFront)
		{
			CGeNorm nmlNow, nmlPre, nmlMaxicNow, nmlMaxicPre;////danger
			TPoint ptStart,ptEnd;
			int j=0;
			for(int i=0;i<pt3dsFront.size()+2;i++)
			{
				j = (i+1)%pt3dsFront.size();
				pt3dsFront[i].z = 0;
				ptStart = pt3dsFront[i];
				ptEnd = pt3dsFront[j];
				nmlPre = nmlNow;
				nmlNow.Set(ptStart,ptEnd);

				nmlMaxicPre = nmlNow;
				nmlMaxicNow = nmlNow * nmlPre;

				if (nmlMaxicNow.m_z * nmlMaxicPre.m_z < 0)
					return TRUE;
			}
			return FALSE;
		} 

		////********************************************************************
		////作者：田佰杰
		////日期：2007-07-05 to 2007-07-05
		////功能：根据比例求中间值
		////说明：(x0-x1)/(x2-x1) == m/(m-n)
		////********************************************************************
		double TPlaneGeometry::ScaleMean(double x1, double x2, double m, double n)
		{
			return x1 + (m*(x2-x1))/(m-n);
		}

		////********************************************************************
		////作者：田佰杰
		////日期：2007-07-10 to 2007-07-10
		////功能：去除重合点。
		////********************************************************************
		bool TPlaneGeometry::DeleteRepeatPt(vector<TPoint>& vPts)
		{
			SortDisToPt(vPts, vPts[0]);
			vector<TPoint>::iterator it1 = vPts.end(), it2 = vPts.end();
			while (it1 != vPts.begin() && it2 != vPts.begin())
			{
				it1--;
				if (*it1 == *it2)
				{
					vPts.erase(it1,it2);
					it1--;
					it2--;
				}
				it2--;
			}
			return true;
		}

		////********************************************************************
		////功能：判断点是否在线上
		////********************************************************************
		bool TPlaneGeometry::IsPtInLine(const TPoint& pt, const TLine	 & tl)
		{
			TRayLine r1(tl.pt1,tl.pt2), r2(tl.pt2,tl.pt1);
			if (IsPtInLine(pt,r1) || IsPtInLine(pt,r2))
			{
				return true;
			}
			return false;
		}
		bool TPlaneGeometry::IsPtInLine(const TPoint& pt, const TRayLine& rl)
		{
			CGeNorm normRayLine(rl.pt1, rl.pt2);
			normRayLine.m_z = 0.0;
			normRayLine.normalize();
			CGeNorm normToPt(rl.pt1, pt);
			normToPt.m_z = 0.0;
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
		bool TPlaneGeometry::IsPtInLine(const TPoint &pt, const TSegLine &sl)
		{
			TRayLine r1(sl.pt1,sl.pt2), r2(sl.pt2,sl.pt1);
			if (IsPtInLine(pt,r1) && IsPtInLine(pt,r2))
			{
				return true;
			}
			return false;
		}

		//////********************************************************************
		//////功能：判断点是否相等（忽略z）
		//////********************************************************************
		bool TPlaneGeometry::IsPtEqu(const TPoint& pt1, const TPoint& pt2)
		{
			return (TEquFloat(pt1.x, pt2.x) && TEquFloat(pt1.y, pt2.y));
		}
		//////********************************************************************
		//////功能：判断线段是否在两条平行直线之间(忽略z)
		//////********************************************************************
		bool TPlaneGeometry::IsSegInsideLine(const TSegLine& sl, 
								const TLine& ln1, const TLine& ln2)
		{
			TPoint ptCross;
			if(Intersect(ln1,ln2,ptCross))
				return false;
			double dis_ln1_ln2 =0, dis_sl_Ln1 = 0, dis_sl_ln2 = 0;
			Length(dis_ln1_ln2, ln1.pt1, ln2);
			Length(dis_sl_Ln1 , sl .pt1, ln1);
			Length(dis_sl_ln2 , sl .pt1, ln2);
			if(TMoreThen(dis_sl_Ln1,dis_ln1_ln2) || TMoreThen(dis_sl_ln2,dis_ln1_ln2))
				return false;
			Length(dis_sl_Ln1 , sl .pt2, ln1);
			Length(dis_sl_ln2 , sl .pt2, ln2);
			if(TMoreThen(dis_sl_Ln1,dis_ln1_ln2) || TMoreThen(dis_sl_ln2,dis_ln1_ln2))
				return false;
			return true;
		}

		//**********************************************************************
		//<Author>:Tian Baijie
		//<Add>=Date:2007/07/30
		////判断多边形是否是凸多边形
		//****************************************
		bool TPlaneGeometry::IsPolygonConvex(const vector<TPoint>& vPtsPolygon)
		{
			int iResult = 0;
			int nSizePolygon = vPtsPolygon.size();
			CGeNorm gn1(gc_ptOrg,gc_ptOrg);
			CGeNorm gn2(gn1); 
			CGeNorm gnRusult(gn1);
			for(int i=0; i<nSizePolygon+1; i++)
			{
				gn2 = gn1;
				gn1.Set(TPoint(vPtsPolygon[i%nSizePolygon]),				
						TPoint(vPtsPolygon[(i+1)%nSizePolygon]));
				gn1.normalize();
				if(!(gn2 == gc_gnOrg))
				{
					gnRusult = gn1 * gn2;
					gnRusult.normalize();
					iResult += gnRusult.m_z>=0 ? 1 : -1;
				}
			}
			if(abs(iResult) == nSizePolygon)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//</Add>
		//</Author>
		//**********


		//**********************************************************************
		//<Author>:Tian Baijie
		//<Add>=Date:2007/08/02
		////双向延长线
		//****************************************
		bool TPlaneGeometry::LineExtend(TLine& lnResult, 
										const TLine& lnSource, 
										double dLen)
		{
		  if(!LineExtend(lnResult, lnSource, dLen, dLen))
		  {
			return false;
		  }
		  return true;
		}
		TLine TPlaneGeometry::LineExtend(const TLine& lnSource, double dLen)
		{
		  TLine lnResult;
		  LineExtend(lnSource, dLen);
		  return lnResult;
		}
		bool  TPlaneGeometry::LineExtend(TLine& lnResult, 
										 const TLine& lnSource, 
															   double dLenSt, 
										 double dLenEd)
		{
		  TPoint ptS1 = lnSource.pt1;
		  ptS1.z = 0;
		  TPoint ptS2 = lnSource.pt2;
		  ptS2.z = 0;
		  CGeNorm nmWay(ptS1, ptS2);
		  nmWay.normalize();
		  TPoint ptD2 = ptS2.PolarTo(dLenEd, &nmWay);
		  nmWay.Set(ptS2, ptS1);
		  nmWay.normalize();
		  TPoint ptD1 = ptS1.PolarTo(dLenSt, &nmWay);
		  lnResult.Set(ptD1, ptD2);
		  return true;
		}
		TLine TPlaneGeometry::LineExtend(const TLine& lnSource, 
															   double dLenSt, 
										 double dLenEd)
		{
		  TLine lnResult;
		  LineExtend(lnSource, dLenSt, dLenEd);
		  return lnResult;
		}

		bool TPlaneGeometry::PtOrtho(TPoint& pt, 
									 TLine lnBase, TPoint ptBase)
		{
			TLine lnBaseParallel = LineParallel(lnBase, ptBase);
			pt = PtPedal(pt, lnBaseParallel); 
			return true;
		}
		bool TPlaneGeometry::PtOrtho(TPoint& pt, TLine lnBase)
		{
			pt = PtPedal(pt, lnBase); 
			return true;
		}

		////********************************************************************
		////功能：根据点和角度求点/线。
		////********************************************************************
		TPoint TPlaneGeometry::PtFromAngle(TPoint pt, double angle)
		{
			pt.z = 0;
			pt.x = pt.x + cos(angle);
			pt.y = pt.y + sin(angle);
			return pt;
		}
		TLine TPlaneGeometry::LineFromangle(TPoint pt, double angle)
		{
			return TLine(pt, PtFromAngle(pt, angle));
		}

		CGeNorm TPlaneGeometry::NormalFromAngle(double angle)
		{
			CGeNorm nm;
			nm.m_x = cos(angle) * 1;
			nm.m_y = sin(angle) * 1;
			nm.m_z = 0;
			return nm;
			
		}

		bool TPlaneGeometry::is_line_superpositon(TLine ln1, TLine ln2)
		{
			if(IsPtInLine(ln2.pt1, ln1) && IsPtInLine(ln2.pt2, ln1)){
			  return true;
			}
			return false;
		}

		bool TPlaneGeometry::is_pt_superposition(TPoint pt1, TPoint pt2)
		{
		  pt1.z = 0;
		  pt2.z = 0;
		  if(pt1 == pt2){
			return true;
		  }else{
			return false;
		  }
		}






		//</Author>
		}
		//********** 





