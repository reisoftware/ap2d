// Paint_Entity_Tools.cpp: implementation of the Paint_Entity_Tools class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <cassert>

#include "Circle.h"
#include "Cloud_Line.h"
#include "Create_Entity.h"
#include "Database.h"
#include "Dimension_Style.h"
#include "Line.h"
#include "Line_Type.h"
#include "myalgorithm.h"
#include "Normal.h"
#include "Paint_Entity.h"
#include "Paint_Entity_Tools.h"
#include "Painter.h"
#include "Point.h"
#include "RArc.h"
#include "Scene_d.h"
#include "Select_Font.h"
#include "Select_Pen.h"
#include "Text.h"
#include "Text_Style.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{

  const double text_hei_dis = 1.1;

  using namespace TIAN_GA_BETTER;

  typedef TIAN_GA_BETTER::TPlaneGeometry	TPG;
  typedef TIAN_GA_BETTER::CPt3D_Pri				TPoint;

  //typedef TIAN_GA_BETTER::TPt3D           TPoint;


  Paint_Entity_Tools::Paint_Entity_Tools(Scene& scene)
  :scene_(scene)
  MCT_INIT2("Paint_Entity_Tools")
  {
  }
  Paint_Entity_Tools::~Paint_Entity_Tools()
  {
  }

  CPt3D_Pri Paint_Entity_Tools::PointToPt3D_Pri(const Point& pt)
  {
    TPoint temp_pt;
    temp_pt.x = pt.x;
    temp_pt.y = pt.y;
    temp_pt.z = pt.z;
    return temp_pt;
  }
  Point Paint_Entity_Tools::Pt3D_PriToPoint(const TPoint& pt)
  {
    Point temp_pt;
    temp_pt.setdata(pt.x, pt.y,pt.z);
    return temp_pt;
  
  }

  TPoint Paint_Entity_Tools::LPoint2TPoint(const Point& pt)
  {
    TPoint temp_pt;
    temp_pt.x = pt.x;
    temp_pt.y = pt.y;
    temp_pt.z = pt.z;
    return temp_pt;
  }
  Point Paint_Entity_Tools::TPoint2LPoint(const TPoint & pt)
  {	
    Point temp_pt;
    temp_pt.setdata(pt.x, pt.y,pt.z);
    return temp_pt;
  }

  Point Paint_Entity_Tools::get_mid_point(const Point& ptStart,const Point& ptEnd)
  {
    Point ptMid;
    ptMid.setdata((ptStart.x+ptEnd.x)/2.0f,(ptStart.y+ptEnd.y)/2.0f,(ptStart.z+ptEnd.z)/2.0f);
    return ptMid;
  
  }
  double Paint_Entity_Tools::GetAngle(const Point& ptStart,const Point& ptEnd)
  {
    double fAngle =0;
    if(EquFloat(ptStart.x,ptEnd.x))
      fAngle = pi/2.0f;
    else if(EquFloat(ptStart.y,ptEnd.y))
      fAngle = 0;
    else
    {
      float k=0,b=0;
      GetLineKAndB(ptStart,ptEnd,k,b);
      fAngle = atan(k);
    }
    return fAngle;
  }
  float Paint_Entity_Tools::GetTwoPointSlope(const Point& ptStart,const Point& ptEnd)
  {
    float k =0;
    float a = ptEnd.y-ptStart.y;
    float b = ptEnd.x-ptStart.x;
    if(ptEnd.x != ptStart.x )
      k = a/b;
    else 
      k = 90.0;
    return k;
  
  }
  void Paint_Entity_Tools::GetLineKAndB(Point ptStart,Point ptEnd,float& k,float& b)
  {
    k = GetTwoPointSlope(ptStart,ptEnd);
    b = ptStart.y - k*ptStart.x;	
  }

  Line Paint_Entity_Tools::TLine2LLine(const TLine & line)
  {
    Line lLine;
    lLine.setdata(GetPoint(line.pt1), GetPoint(line.pt2));
    return lLine;
  }
  TLine Paint_Entity_Tools::LLine2TLine(const Line & line)
  {
    TLine tLine(GetPt3D(line.start()),GetPt3D(line.end()));
    return tLine;
  }
  //  //
  TRayLine Paint_Entity_Tools::LLine2TRayLine(const Line & line)
  {
    TRayLine tLine(GetPt3D(line.start()),GetPt3D(line.end()));
    return tLine;
  }
  TSegLine Paint_Entity_Tools::LLine2TSegLine(const Line & line)
  {
    TSegLine tLine(GetPt3D(line.start()),GetPt3D(line.end()));
    return tLine;
  }


  RArc Paint_Entity_Tools::TArc2Larc(const TArc & tArc)
  {
    Point lptCentre = GetPoint(tArc._ptCentre);
    float r = tArc._r;
    float stAngle = TTool::Arc2Angle(tArc._stArc);
    float edAngle = TTool::Arc2Angle(tArc._edArc);
    RArc lArc;
    lArc.set_degree2d(lptCentre, r, stAngle, edAngle);
    return lArc;
  }
  TArc Paint_Entity_Tools::LArc2Tarc(const RArc & lArc)
  {
    TPoint ptCentre = GetPt3D(lArc.center());
    double r = lArc.radius();
    double stAngle = TTool::Angle2Arc(lArc.start_degree2d());
    double edAngle = TTool::Angle2Arc(lArc.end_degree2d());
    TArc tArc(ptCentre, r, stAngle, edAngle);
    return tArc;
  }
  TPoint Paint_Entity_Tools::GetPt3D(const Point& pt)
  {
    TPoint ptResult;
    ptResult.x = pt.x;
    ptResult.y = pt.y;
    ptResult.z = pt.z;
    return ptResult;
  }
  Point Paint_Entity_Tools::GetPoint(const TPoint & pt)
  {
    Point ptResult;
    ptResult.x = pt.x;
    ptResult.y = pt.y;
    ptResult.z = pt.z;
    return ptResult;
  }

  Normal Paint_Entity_Tools::TNormal2Normal(CGeNorm nm)
  {
    Normal nmResult;
    nmResult.set_data(nm.m_x, nm.m_y, nm.m_z);
    return nmResult;
  }

  CGeNorm Paint_Entity_Tools::Normal2TNormal(Normal nm)
  {
    CGeNorm tnm;
    tnm.m_x = nm.x();
    tnm.m_y = nm.y();
    tnm.m_z = nm.z();
    return tnm;
  }

  Circle Paint_Entity_Tools::Arc2Circle(RArc myarc)
  {
    Circle mycircle;
    mycircle.setdata(myarc.center(), myarc.radius());
    return mycircle;
  }


  ////利用TArc确保得到穿过3点的弧////LArc的弧线3点不能处理非逆时针的情况
  RArc Paint_Entity_Tools::LArcFrom3LPoint(Point pt1, Point pt2, Point pt3)
  {
    TPoint tpt1 = Paint_Entity_Tools::LPoint2TPoint(pt1);
    TPoint tpt2 = Paint_Entity_Tools::LPoint2TPoint(pt2);
    TPoint tpt3 = Paint_Entity_Tools::LPoint2TPoint(pt3);
    TArc tXorArc(tpt1, tpt2, tpt3);
    return Paint_Entity_Tools::TArc2Larc(tXorArc);
  }

  Line Paint_Entity_Tools::LineParallel(Line lnBase, Point ptExt)
  {
    TPoint t_ptExt = PointToPt3D_Pri(ptExt);
    TIAN_GA_BETTER::TLine	  t_lnBase= LLine2TLine(lnBase);
    TIAN_GA_BETTER::TLine	  t_lnResult = 
      TPlaneGeometry::LineParallel(t_lnBase, t_ptExt);
    Line lnResult = TLine2LLine(t_lnResult);
    return lnResult;
  }
  Line Paint_Entity_Tools::LinePedal(Line lnBase, Point ptExt)
  {
    TPoint t_ptExt = PointToPt3D_Pri(ptExt);
    TIAN_GA_BETTER::TLine	  t_lnBase= LLine2TLine(lnBase);
    TIAN_GA_BETTER::TLine	  t_lnResult = 
      TPlaneGeometry::LinePedal(t_ptExt, t_lnBase);
    Line lnResult = TLine2LLine(t_lnResult);
    return lnResult;
  }
  Point Paint_Entity_Tools::PointPedal(Point ptExt, Line lnBase)
  {
    TPoint t_ptExt = PointToPt3D_Pri(ptExt);
    TIAN_GA_BETTER::TLine	  t_lnBase= LLine2TLine(lnBase);
    TPoint t_ptResult = 
      TPlaneGeometry::PtPedal(t_ptExt, t_lnBase);
    Point ptResult = Pt3D_PriToPoint(t_ptResult);
    return ptResult;
  }


  bool Paint_Entity_Tools
  ::GetRectFrom3Point(Point& ptExtBegin, Point& ptExtEnd, 
                      Point ptBegin, Point ptEnd, Point ptExt)
  {
    Line lnBase(ptBegin, ptEnd);
    Line lnExt	= LineParallel(lnBase, ptExt);
    ptExtBegin	= PointPedal(ptBegin, lnExt);
    ptExtEnd	= PointPedal(ptEnd, lnExt);
    return true;
  }

  bool Paint_Entity_Tools
  ::GetRectFrom3PointAndExtAngle(Point& ptExtBegin, Point& ptExtEnd, 
                                 Point ptBegin, Point ptEnd, Point ptExt, double dExtAngle)
  {
    Line lnBase;
    GetLineBaseFromPtAndExtAngle(lnBase, ptBegin, dExtAngle);
    Line lnExt	= LineParallel(lnBase, ptExt);
    ptExtBegin	= PointPedal(ptBegin, lnExt);
    ptExtEnd	= PointPedal(ptEnd, lnExt);
    return true;
  }
  bool Paint_Entity_Tools
  ::GetRectFrom3PointAndDimAngle(Point& ptExtBegin, Point& ptExtEnd, 
                                 Point ptBegin, Point ptEnd, Point ptExt, double dDimAngle)
  {
    Line lnBase;
    GetLineBaseFromPtAndDimAngle(lnBase, ptBegin, dDimAngle);
    Line lnExt	= LineParallel(lnBase, ptExt);
    ptExtBegin	= PointPedal(ptBegin, lnExt);
    ptExtEnd	= PointPedal(ptEnd, lnExt);
    return true;
  }
  bool Paint_Entity_Tools
  ::GetRectFrom4PointAndAngle(Point& ptExtBegin, Point& ptExtEnd, 
                              Point ptBegin, Point ptEnd, Point ptExt1, Point ptExt2, 
                              double dDimAngle)
  {
    Line lnBase;
    GetLineBaseFromPtAndDimAngle(lnBase, ptBegin, dDimAngle);
    Line lnExt1	= LineParallel(lnBase, ptExt1);
    Line lnExt2	= LineParallel(lnBase, ptExt2);
    ptExtBegin	= PointPedal(ptBegin, lnExt1);
    ptExtEnd	= PointPedal(ptEnd, lnExt2);
    return true;
  }

  bool Paint_Entity_Tools
  ::GetLineBaseFromPtAndExtAngle(Line& lnBase, Point pt, double dExtAngle)
  {
    double dBaseAngle = TPG::Radian(
      dExtAngle + TIAN_GA_BETTER::PI_R/2);
    lnBase = LineFromPointAndAngle(pt, dBaseAngle);
    return true;
  }
  bool Paint_Entity_Tools
  ::GetLineBaseFromPtAndDimAngle(Line& lnBase, Point pt, double dDimAngle)
  {
    //	double dBaseAngle = TPG::Radian(
    //		dExtAngle + TIAN_GA_BETTER::PI_R/2);
    //	lnBase = LineFromPointAndAngle(pt, dBaseAngle);
    lnBase = LineFromPointAndAngle(pt, dDimAngle);
    return true;
  }

  Line Paint_Entity_Tools
  ::LineFromPointAndAngle(Point pt, double dAngle)
  {
    TPoint tpt = PointToPt3D_Pri(pt);
    TIAN_GA_BETTER::TLine ln 
      = TPG::LineFromangle(tpt, dAngle);
    return TLine2LLine(ln);
  }

  double Paint_Entity_Tools::Radian(Point pt, Point ptOrg /* = Point */)
  {
    TPoint t_pt = PointToPt3D_Pri(pt);
    TPoint t_org= PointToPt3D_Pri(ptOrg);
    return TPlaneGeometry::Radian(t_pt, t_org);
  }

  //沿固定线方向移动点
  bool Paint_Entity_Tools::PtOrtho(Point& pt, Line lnBase, Point ptBase)
  {
    TPoint tpt = PointToPt3D_Pri(pt);
    TPoint tptBase = PointToPt3D_Pri(ptBase);
    TIAN_GA_BETTER::TLine     tlnBase = LLine2TLine(lnBase);
    TPG::PtOrtho(tpt, tlnBase, tptBase);
    pt = Pt3D_PriToPoint(tpt);
    return true;
  }
  //沿固定线方向移动点
  bool Paint_Entity_Tools::PtOrtho(Point& pt, Line lnBase)
  {
    TPoint tpt = PointToPt3D_Pri(pt);
    TIAN_GA_BETTER::TLine     tlnBase = LLine2TLine(lnBase);
    TPG::PtOrtho(tpt, tlnBase);
    pt = Pt3D_PriToPoint(tpt);
    return true;
  }


  void Paint_Entity_Tools
  ::draw_dim_block( 
                   Scene& scene, Three_Pt_Dimension_Block& dimBlock)
  {
    xor_draw_dim_block(scene, dimBlock, false);
  }
  void Paint_Entity_Tools
  ::draw_dim_block( 
                   Scene& scene, Ln_Dim_Block& dimBlock)
  {
    xor_draw_dim_block(scene, dimBlock, false);
  }

  void Paint_Entity_Tools
  ::xor_draw_dim( Scene& scene, 
                 Angle_Dimension* pdim, bool xor, COLORREF cr)
  {
    if (!pdim) {
      return;
    }
    ////若夹角小于0，画直线
    if (TIAN_GA_BETTER::TLessEqu(AngleFromDim(pdim),TIAN_GA_BETTER::FLOAT_ZERO)) {
      Line ln;
      ln.setdata(pdim->vertex(), pdim->start());
      xor_draw_line(scene, ln);
      return;
    }
    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);	
    COLORREF cr_old = pdim->color();
    pdim->color(cr);
    if(xor){
      pdim->xor_draw(paint);
    }else{
      pdim->draw(paint);
    }
    pdim->color(cr_old);

  #ifdef _DEBUG
    RArc ar = ArcFromDim(pdim);
    Point ptArcCenter = ar.center();
    Line lnExt1, lnExt2, lnCC;
    lnExt1.setdata(ptArcCenter, pdim->start());
    lnExt2.setdata(ptArcCenter, pdim->end());
    lnCC.setdata(ptArcCenter, pdim->vertex());

    if(xor){
      xor_draw_line(scene, lnExt1, RGB(255,0,0));
      xor_draw_line(scene, lnExt2, RGB(255,0,0));
      xor_draw_line(scene, lnCC, RGB(255,0,0));
    }else{
      xor_draw_line(scene, lnExt1, false, RGB(255,0,0));
      xor_draw_line(scene, lnExt2, false, RGB(255,0,0));
      xor_draw_line(scene, lnCC, false, RGB(255,0,0));
  
    }
  #endif

  }
  // 2009.02.13 //
  void Paint_Entity_Tools
  ::xor_draw_dim( Scene& scene, 
                 Radius_Dimension* pdim, bool xor, COLORREF cr)
  {
    if(!pdim){
      return;
    }
    if(is_dim_0(pdim)){
      return;
    }
    COLORREF cr_old = pdim->color();
    pdim->color(cr);
    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);
    if(xor){
      pdim->xor_draw(paint);
    }else{
      pdim->draw(paint);
    }
    pdim->color(cr_old);
  }

  void Paint_Entity_Tools
  ::xor_draw_dim( Scene& scene, 
                 Three_Pt_Dimension * pdim, bool xor, COLORREF cr)
  {
    if(!pdim){
      return;
    }
    if(is_dim_0(pdim)){
      return;
    }
    COLORREF cr_old = pdim->color();
    pdim->color(cr);
    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);
    if(xor){
      pdim->xor_draw(paint);
    }else{
      pdim->draw(paint);
    }
    pdim->color(cr_old);
  }

  void Paint_Entity_Tools
  ::xor_draw_dim( Scene& scene, 
                 Ln_Dim * pdim, bool xor, COLORREF cr)
  {
    if(!pdim){
      return;
    }
    if(is_dim_0(pdim)){
      return;
    }
    COLORREF cr_old = pdim->color();
    pdim->color(cr);
    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);
    if(xor){
      pdim->xor_draw(paint);
    }else{
      pdim->draw(paint);
    }
    pdim->color(cr_old);
  }



  void Paint_Entity_Tools::xor_draw_dim_block(Scene& scene, 
                                              Three_Pt_Dimension_Block& dimBlock, 
                                              bool xor)
  {
    if(dimBlock.size() == 0){
      //
      //if(dimBlock.drag_startme()){
      //  
      //}
      //
      return;
    }
    Three_Pt_Dimension* pDimFront = dimBlock.front();
    Three_Pt_Dimension* pDimBack  = dimBlock.back();

    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);

    Three_Pt_Dimension* pDimIter  = pDimFront;	

    //	bool bBreak = false;
    pDimIter  = pDimFront;	
    while (pDimIter) {
      if (xor) {
        pDimIter->xor_draw(paint);	
      }else{
        pDimIter->draw(paint);
      }
      pDimIter  = dimBlock.next(pDimIter);
      //		Sleep(500);
    }
  }
  void Paint_Entity_Tools
  ::xor_draw_dim_block( 
                       Scene& scene, Ln_Dim_Block& dimBlock, bool xor)
  {
    if (dimBlock.size() == 0) {
      return;
    }
    Ln_Dim* pDimFront = dimBlock.front();
    Ln_Dim* pDimBack  = dimBlock.back();

    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);

    Ln_Dim* pDimIter  = pDimFront;	

    //#ifdef _DEBUG
    //	int i = 0;
    //#endif
    pDimIter  = pDimFront;	
    while (pDimIter) {
      if (xor) {
        pDimIter->xor_draw(paint);	
      }else{
        //#ifdef _DEBUG
        //			i++;char buf[BUFSIZ];
        //			buf[0] = '\0';
        //			sprintf(buf, "%d%s\0", i, pDimIter->dim_text2());
        //			pDimIter->dim_text2(buf);
        //#endif
        pDimIter->draw(paint);
      }
      pDimIter  = dimBlock.next(pDimIter);
      //		Sleep(500);
    }
  }



  void Paint_Entity_Tools
  ::xor_draw_circle(Scene& scene,	Circle mycircle, COLORREF cr)
  {
    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);
  
    mycircle.color(cr);
    paint.xor_draw_circle(mycircle);
  }

  void Paint_Entity_Tools
  ::xor_draw_arc(Scene& scene,	RArc myarc, COLORREF cr)
  {
    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);
  
    myarc.color(cr);
    paint.xor_draw_arc(myarc);
  }


  void Paint_Entity_Tools
  ::xor_draw_pt4( Scene& scene, const Point (&pt)[4], COLORREF cr)
  {
    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);
    Line line;
    line.color(cr);
  
    line.setdata(pt[0], pt[1]);
    paint.xor_draw_line(line);
  
    line.setdata(pt[1], pt[2]);
    paint.xor_draw_line(line);
  
    line.setdata(pt[2], pt[3]);
    paint.xor_draw_line(line);
  
    line.setdata(pt[3], pt[0]);
    paint.xor_draw_line(line);
  }

  void Paint_Entity_Tools::xor_draw_rect(Scene& scene, const Rect& rect, COLORREF color)
  {
    Painter* painter = scene.get_painter();
    Paint_Entity paint(scene,*painter);
    Point st,ed;
    Line line;
    line.color(color);
  
    st.setdata(rect.xmin(),rect.ymin());
    ed.setdata(rect.xmin(),rect.ymax());
    line.setdata(st, ed);
    paint.xor_draw_line(line);
  
    st.setdata(rect.xmax(),rect.ymax());
    line.setdata(st, ed);
    paint.xor_draw_line(line);
  
    ed.setdata(rect.xmax(),rect.ymin());
    line.setdata(st, ed);
    paint.xor_draw_line(line);
  
    st.setdata(rect.xmin(),rect.ymin());
    line.setdata(st, ed);
    paint.xor_draw_line(line);
  }
  //2009.03.06

  void Paint_Entity_Tools::xor_draw_hint_dim(Scene& scene, const Rect& rect)
  {
	  Painter* painter = scene.get_painter();
	  Paint_Entity paint(scene,*painter);
	  Point st,ed;
	  Line line;
	  line.color(RGB(255,0,255));

	  st.setdata(rect.xmin(),rect.ymin());
	  ed.setdata(rect.xmin(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmax(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  ed.setdata(rect.xmax(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmin(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);
  }
  void Paint_Entity_Tools::xor_draw_hint_txt(Scene& scene, const Rect& rect)
  {
	  Painter* painter = scene.get_painter();
	  Paint_Entity paint(scene,*painter);
	  Point st,ed;
	  Line line;
	  line.color(RGB(255,0,255));

	  st.setdata(rect.xmin(),rect.ymin());
	  ed.setdata(rect.xmin(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmax(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  ed.setdata(rect.xmax(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmin(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);
  }
  void Paint_Entity_Tools::xor_draw_hint_add(Scene& scene, const Rect& rect)
  {
	  Painter* painter = scene.get_painter();
	  Paint_Entity paint(scene,*painter);
	  Point st,ed;
	  Line line;
	  line.color(RGB(255,0,255));

	  st.setdata(rect.xmin(),rect.ymin());
	  ed.setdata(rect.xmin(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmax(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  ed.setdata(rect.xmax(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmin(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);
  }
  void Paint_Entity_Tools::xor_draw_hint_l(Scene& scene, const Rect& rect)
  {
	  Painter* painter = scene.get_painter();
	  Paint_Entity paint(scene,*painter);
	  Point st,ed;
	  Line line;
	  line.color(RGB(0,255,0));

	  st.setdata(rect.xmin(),rect.ymin());
	  ed.setdata(rect.xmin(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmax(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  ed.setdata(rect.xmax(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmin(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);
  }
  void Paint_Entity_Tools::xor_draw_hint_r(Scene& scene, const Rect& rect)
  {
	  Painter* painter = scene.get_painter();
	  Paint_Entity paint(scene,*painter);
	  Point st,ed;
	  Line line;
	  line.color(RGB(0,200,255));

	  st.setdata(rect.xmin(),rect.ymin());
	  ed.setdata(rect.xmin(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmax(),rect.ymax());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  ed.setdata(rect.xmax(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);

	  st.setdata(rect.xmin(),rect.ymin());
	  line.setdata(st, ed);
	  paint.xor_draw_line(line);
  }

void Paint_Entity_Tools
::xor_draw_line(Scene& scene, 
				Point pt1, 
				Point pt2, 
				COLORREF cr /* = RGB(255 ,255,255)*/)
{
	Line ln(pt1, pt2);
	xor_draw_line(scene, ln, cr);
}

void Paint_Entity_Tools
::xor_draw_line(Scene& scene, 
				Line ln,
				COLORREF cr /* = RGB(255 ,255,255)*/)
{
	Painter* painter = scene.get_painter();
	Paint_Entity paint(scene,*painter);
	ln.color(cr);
	paint.xor_draw_line(ln);
}
void Paint_Entity_Tools
::xor_draw_line(Scene& scene, 
				Line ln,
				bool xor,
				COLORREF cr)
{
	Painter* painter = scene.get_painter();
	Paint_Entity paint(scene,*painter);
	ln.color(cr);
	if (xor) {
	    paint.draw_line(ln);
	}else {
		paint.xor_draw_line(ln);
	}
}

Point Paint_Entity_Tools::world_to_screen(Scene& scene,const Point& pt)
{
	Point p(pt);
	scene.world_to_screen_point(p);
	return p;
}

double Paint_Entity_Tools::DisPtByNormal(Point pt1, Point pt2, Normal nm)
{
	TPoint tpt1 = PointToPt3D_Pri(pt1);
	TPoint tpt2 = PointToPt3D_Pri(pt2);
	CGeNorm	  tnm  = Normal2TNormal(nm);
	return TPG::DisPtByNormal(tpt1, tpt2, tnm);
}

double Paint_Entity_Tools::DisPtToLineByNormal(Point pt, Line ln, Normal nm)
{
	TPoint tpt = PointToPt3D_Pri(pt);
	TLine	  tln = LLine2TLine(ln);
	CGeNorm	  tnm = Normal2TNormal(nm);
	return TPG::DisPtToLineByNormal(tpt, tln, tnm);
}
double Paint_Entity_Tools::DisPtToLine(Point pt, Line ln)
{
	TPoint tpt = PointToPt3D_Pri(pt);
	TLine	  tln = LLine2TLine(ln);
	return TPG::DisPtToLine(tpt, tln);
}


double Paint_Entity_Tools
::dim_text_height(Three_Pt_Dimension* pDim)
{
	Point ptBox[4];
	dim_text_4pt(ptBox, pDim);
	double disTxtHei = ptBox[0].distanceto(ptBox[1]) *1;
	return disTxtHei;
}
double Paint_Entity_Tools::dim_text_height_closed(Ln_Dim* pDim)
{
//	Point ptBox[4];
//	dim_text_4pt_closed(ptBox, pDim);
//	double disTxtHei = ptBox[0].distanceto(ptBox[1]) *1;
//	return disTxtHei;
//  Text txt;
//  pDim->get_text_show(txt);
//  return txt.height();
  double hei = pDim->dim_style_val().text_gdi_height();
  return hei;
}
double Paint_Entity_Tools
::dim_text_width(Three_Pt_Dimension* pDim)
{
	Point ptBox[4];
	dim_text_4pt(ptBox, pDim);
	double disTxtHei = ptBox[0].distanceto(ptBox[3]) *1;
	return disTxtHei;
}
double Paint_Entity_Tools
::dim_text1_height(Ln_Dim* pDim)
{
//	Point ptBox[4];
//	dim_text1_4pt(ptBox, pDim);
//	double disTxtHei = ptBox[0].distanceto(ptBox[1]) *1;
//	return disTxtHei;
  double hei = pDim->dim_style_val().text_gdi_height();
  return hei;
}
double Paint_Entity_Tools
::dim_text1_width(Ln_Dim* pDim)
{
	Point ptBox[4];
	dim_text1_4pt(ptBox, pDim);
	double disTxtHei = ptBox[0].distanceto(ptBox[3]) *1;
	return disTxtHei;
}
double Paint_Entity_Tools
::dim_text2_height(Ln_Dim* pDim)
{
//	Point ptBox[4];
//	dim_text2_4pt(ptBox, pDim);
//	double disTxtHei = ptBox[0].distanceto(ptBox[1]) *1;
//	return disTxtHei;
  double hei = pDim->dim_style_val().text_gdi_height();
  return hei;
}
double Paint_Entity_Tools
::dim_text2_width(Ln_Dim* pDim)
{
	Point ptBox[4];
	dim_text2_4pt(ptBox, pDim);
	double disTxtHei = ptBox[0].distanceto(ptBox[3]) *1;
	return disTxtHei;
}

//void Paint_Entity_Tools::a_word_size(SIZE& sz)
//{
//  Text txt;
//  pDim->get_text_show(txt);
//  txt.a_word_size(sz);
//}
//double Paint_Entity_Tools::a_word_cx()
//{
//  SIZE sz;
//  a_word_size(sz);
//  return sz.cx;
//}
//double Paint_Entity_Tools::a_word_cy()
//{
//  SIZE sz;
//  a_word_size(sz);
//  return sz.cy;
//}
void Paint_Entity_Tools::dim_text_4pt(Point (&pt)[4], Three_Pt_Dimension* pDim)
{
	Text txt;
	pDim->get_text_show(txt);
	//txt.real_box_point(pt);
  //const std::vector<Point>& ptbox = txt.real_box_point();
	std::vector<Point> ptbox;
	txt.real_box_pt(ptbox);
	assert(ptbox.size()==4);
  pt[0]=ptbox[0];
  pt[1]=ptbox[1];
  pt[2]=ptbox[2];
  pt[3]=ptbox[3];
}
void Paint_Entity_Tools::dim_text_4pt_closed(Point (&pt)[4], Ln_Dim* pDim)
{
	Text txt;
	pDim->get_text_show(txt);
//	txt.real_box_point(pt);
  //const std::vector<Point>& ptbox = txt.real_box_point();
	std::vector<Point> ptbox;
	txt.real_box_pt(ptbox);
	assert(ptbox.size()==4);
  pt[0]=ptbox[0];
  pt[1]=ptbox[1];
  pt[2]=ptbox[2];
  pt[3]=ptbox[3];
}
void Paint_Entity_Tools
::dim_text1_4pt(Point (&pt)[4], Ln_Dim* pDim)
{
	Text txt;
	pDim->get_text_show(txt);
//	txt.real_box_point(pt);
  //const std::vector<Point>& ptbox = txt.real_box_point();
	std::vector<Point> ptbox;
	txt.real_box_pt(ptbox);
	assert(ptbox.size()==4);
  pt[0]=ptbox[0];
  pt[1]=ptbox[1];
  pt[2]=ptbox[2];
  pt[3]=ptbox[3];
}
void Paint_Entity_Tools
::dim_text2_4pt(Point (&pt)[4], Ln_Dim* pDim)
{
	Text txt;
	pDim->get_text2_show(txt);
//	txt.real_box_point(pt);
  //const std::vector<Point>& ptbox = txt.real_box_point();
	std::vector<Point> ptbox;
	txt.real_box_pt(ptbox);
	assert(ptbox.size()==4);
  pt[0]=ptbox[0];
  pt[1]=ptbox[1];
  pt[2]=ptbox[2];
  pt[3]=ptbox[3];
}

////3点标注文本的层次
int Paint_Entity_Tools
::get_dim_text_pos_layer(Three_Pt_Dimension * pDim)
{
	if (!pDim) {
		return 0;
	}
	double disTxtHei = dim_text_height(pDim);
////
	Line lnDim = LineDimFromDim(pDim);
	Line lnExt1= LineExt1FromDim(pDim);
	Normal nmExt;
//	nmExt.set_data(lnExt1.start(), lnExt1.end());
	nmExt = LNormalFromAngle(pDim->extend_radian());
	Normal2TopOrLeft(nmExt);
	double disTxtPos = DisPtToLineByNormal(
						pDim->text_position(), lnDim, nmExt);
	double dLayer = disTxtPos / disTxtHei;
	return int(dLayer);
}
////3点标注文本的层次
int Paint_Entity_Tools::get_dim_text_pos_layer_closed(Ln_Dim * pDim)
{
	if(!pDim){
		return 0;
	}
	double disTxtHei = dim_text_height_closed(pDim)*1.2;
////
  Line sexln,eexln,sdmln;
  pDim->get_s_lines(sexln,eexln,sdmln);
	Normal nmExt;
  radian_2_normal2d(pDim->ext_line_radian(), nmExt);
	Normal2TopOrLeft(nmExt);
	double disTxtPos = DisPtToLineByNormal(
						pDim->text_position(), sdmln, nmExt);
	double dLayer = disTxtPos / disTxtHei;
	return int(dLayer);
}
////4点标注文本的层次
int Paint_Entity_Tools::get_dim_text_pos_layer(Ln_Dim * pDim)
{
	if(!pDim) {
		return 0;
	}
	double disTxtHei = dim_text1_height(pDim);
  Line exln, dmln;
  pDim->get_o_lines(exln,dmln);
	Normal nmExt;
  nmExt.set_data(exln);
  nmExt.set_unit();
  Line oeln(pDim->odm(),pDim->edm());
	double disTxtPos = oeln.length_by_way(nmExt);
	double dLayer = disTxtPos / disTxtHei;
	return int(dLayer);
}

void Paint_Entity_Tools::set_dim_text_pos_layer(
	Three_Pt_Dimension * pDim, int iLayer)
{
	if (!pDim) {
		return;
	}
	double disHight = dim_text_height(pDim)*text_hei_dis;
////
	Line lnDim = LineDimFromDim(pDim);
	Line lnExt1= LineExt1FromDim(pDim);
	Normal nm1;
//	nm1.set_data(lnExt1.start(), lnExt1.end());
	nm1 = LNormalFromAngle(pDim->extend_radian());
	Normal2TopOrLeft(nm1);////
	double disLayer = disHight * iLayer;
	Point ptDimCen0 = (lnDim.start()+lnDim.end())/2;
	Point ptDimCen1 = ptDimCen0.polarTo(disLayer, nm1);
	Point ptTxtPos = pDim->text_position();
	PtOrtho(ptTxtPos, lnDim, ptDimCen1);
	pDim->text_position(ptTxtPos);
}
void Paint_Entity_Tools::set_dim_text_pos_layer_closed(Ln_Dim * pDim, int iLayer)
{
	if(!pDim){
		return;
	}
	double disHight = dim_text_height_closed(pDim)*1.21;
////
  Line sexln,eexln,sdmln;
  pDim->get_s_lines(sexln,eexln,sdmln);
	Normal nm1;
  radian_2_normal2d(pDim->ext_line_radian(),nm1);
	Normal2TopOrLeft(nm1);////
	double disLayer = disHight * iLayer;
	Point ptDimCen0 = sdmln.middle();
	Point ptDimCen1 = ptDimCen0.polarTo(disLayer, nm1);
	Point ptTxtPos = pDim->text_position();
	PtOrtho(ptTxtPos, sdmln, ptDimCen1);
	pDim->text_position(ptTxtPos);
}
void Paint_Entity_Tools::set_dim_text_pos_layer(Ln_Dim * pDim, int iLayer)
{
	if(!pDim){
		return;
	}
	double disHight = dim_text1_height(pDim)*text_hei_dis;
  Line exln, dmln;
  pDim->get_o_lines(exln,dmln);
	Normal nm1;
  nm1.set_data(exln);
	double disLayer = disHight * iLayer;
  pDim->re0_dm();
  pDim->offset_dm(nm1,disLayer,2);
}

//  两个标注文本是否干涉（是否同层，若同层中心距是否小于文本宽的和）
static bool is_intervene_box(Point (&ptBox1)[4], Point (&ptBox2)[4])
{
  Point ptCen1, ptCen2;
  ptCen1 = (ptBox1[0]+ptBox1[2])/2;
  ptCen2 = (ptBox2[0]+ptBox2[2])/2;
  double disCen = ptCen1.distanceto2d(ptCen2);			////两个文本中心距
  double disBox1= ptBox1[0].distanceto2d(ptBox1[3]);	////第一个文本宽度
  double disBox2= ptBox2[0].distanceto2d(ptBox2[3]);	////第二个文本宽度
  double disTxtHei = ptBox1[0].distanceto2d(ptBox1[1]);	////文本高度
  if(TIAN_GA_BETTER::TMoreThen(disCen, (disBox1+disBox2)/2+disTxtHei*1)){
    return false;
  }
  return true;
}


////两个标注文本是否干涉（是否同层，若同层中心距是否小于文本宽的和）
bool Paint_Entity_Tools::is_intervene(Three_Pt_Dimension* pDim1, 
			                                Three_Pt_Dimension* pDim2)
{
	if(!pDim1 || !pDim2){
	  return false;
	}

	int layer1 = get_dim_text_pos_layer(pDim1);
	int layer2 = get_dim_text_pos_layer(pDim2);
	if (layer1 != layer2) {
	    return false;
	}
//	Text txt1, txt2;
//	pDim1->get_text_show(txt1);
//	pDim2->get_text_show(txt2);
//	txt1.re_calc_box2d();
//	txt2.re_calc_box2d();
	Point ptBox1[4], ptBox2[4];
//	txt1.real_box_point(ptBox1);
//	txt2.real_box_point(ptBox2);
	dim_text_4pt(ptBox1, pDim1);
	dim_text_4pt(ptBox2, pDim2);

  return is_intervene_box(ptBox1, ptBox2);

// 	Point ptCen1, ptCen2;
// 	ptCen1 = (ptBox1[0]+ptBox2[3])/2;
// 	ptCen2 = (ptBox2[0]+ptBox2[3])/2;
// 	double disCen = ptCen1.distanceto(ptCen2);			////两个文本中心距
// 	double disBox1= ptBox1[0].distanceto(ptBox1[3]);	////第一个文本宽度
// 	double disBox2= ptBox2[0].distanceto(ptBox2[3]);	////第二个文本宽度
// 	double disTxtHei = ptBox1[0].distanceto(ptBox1[1]);	////文本高度
// 	if (TIAN_GA_BETTER::TMoreThen(disCen, (disBox1+disBox2)/2+disTxtHei*0)) {
// 	    return false;
// 	}
// 	return true;
}
////两个标注文本是否干涉（是否同层，若同层中心距是否小于文本宽的和）
bool Paint_Entity_Tools::is_intervene_closed(Ln_Dim* pDim1,Ln_Dim* pDim2)
{
	if(!pDim1 || !pDim2){
	  return false;
	}
	int layer1 = get_dim_text_pos_layer_closed(pDim1);
	int layer2 = get_dim_text_pos_layer_closed(pDim2);
	if (layer1 != layer2) {
	    return false;
	}
	Point ptBox1[4], ptBox2[4];
	dim_text_4pt_closed(ptBox1, pDim1);
	dim_text_4pt_closed(ptBox2, pDim2);

  return is_intervene_box(ptBox1, ptBox2);

//   Point ptCen1, ptCen2;
// 	ptCen1 = (ptBox1[0]+ptBox2[3])/2;
// 	ptCen2 = (ptBox2[0]+ptBox2[3])/2;
// 	double disCen = ptCen1.distanceto(ptCen2);			////两个文本中心距
// 	double disBox1= ptBox1[0].distanceto(ptBox1[3]);	////第一个文本宽度
// 	double disBox2= ptBox2[0].distanceto(ptBox2[3]);	////第二个文本宽度
// 	double disTxtHei = ptBox1[0].distanceto(ptBox1[1]);	////文本高度
// 	if (TIAN_GA_BETTER::TMoreThen(disCen, (disBox1+disBox2)/2+disTxtHei*0)) {
// 	    return false;
// 	}
// 	return true;
}
// 累加
bool Paint_Entity_Tools::is_intervene(Ln_Dim* pDim1, Ln_Dim* pDim2)
{
	if(!pDim1 || !pDim2) {
	  return false;
	}
  ////如果不是累计
  if(pDim1->mode() != dlhml::PILEUP_DIM){
    return false;
  }
  if(pDim2->mode() != dlhml::PILEUP_DIM){
    return false;
  }

	int layer1 = get_dim_text_pos_layer(pDim1);
	int layer2 = get_dim_text_pos_layer(pDim2);
	if(layer1 != layer2) {
	  return false;
	}
	Point ptBox1[4], ptBox2[4];
	dim_text2_4pt(ptBox1, pDim1);
	dim_text2_4pt(ptBox2, pDim2);

  return is_intervene_box(ptBox1, ptBox2);

// 	Point ptCen1, ptCen2;
// 	ptCen1 = (ptBox1[0]+ptBox2[3])/2;
// 	ptCen2 = (ptBox2[0]+ptBox2[3])/2;
// 	double disCen = ptCen1.distanceto(ptCen2);			////两个文本中心距
// 	double disBox1= ptBox1[0].distanceto(ptBox1[3]);	////第一个文本宽度
// 	double disBox2= ptBox2[0].distanceto(ptBox2[3]);	////第二个文本宽度
// 	double disTxtHei = ptBox1[0].distanceto(ptBox1[1]);	////文本高度
// 	if (TIAN_GA_BETTER::TMoreThen(disCen, (disBox1+disBox2)/2+disTxtHei*0)) {
// 	    return false;
// 	}
// 	return true;
}

static bool is_intervene_0(Ln_Dim_Block& block, int cur)
{
  if(cur <= 0){
    return false;
  }
  int count = block.size();
  if(cur >= count){
    return false;
  }

  ////如果不是累加
  if(block.mode() != dlhml::PILEUP_DIM){
    return false;
  }
  ////如果不显示0，则不会干涉
  if(block[0]->show0()){
    return false;
  }
  ////如果不显示尺寸线，则不会干涉
  if(block[cur]->end_show()){
    return false;
  }
  
	Point ptBox1[4], ptBox2[4];
  Paint_Entity_Tools::dim_text1_4pt(ptBox1, block[0]);
	Paint_Entity_Tools::dim_text2_4pt(ptBox2, block[cur]);


	Point ptCen1, ptCen2;
	ptCen1 = (ptBox1[0]+ptBox2[3])/2;
	ptCen2 = (ptBox2[0]+ptBox2[3])/2;

  return is_intervene_box(ptBox1, ptBox2);


// 	double disCen = ptCen1.distanceto(ptCen2);			////两个文本中心距
// 	double disBox1= ptBox1[0].distanceto(ptBox1[3]);	////第一个文本宽度
// 	double disBox2= ptBox2[0].distanceto(ptBox2[3]);	////第二个文本宽度
// 	double disTxtHei = ptBox1[0].distanceto(ptBox1[1]);	////文本高度
// 	if (TIAN_GA_BETTER::TMoreThen(disCen, (disBox1+disBox2)/2+disTxtHei*1)) {
// 	    return false;
// 	}
// 	return true;
}

//  是否自己干涉（累加标注）
bool Paint_Entity_Tools::is_intervene(Ln_Dim* pDim)
{
	if(!pDim){
	  return false;
	}
  ////如果不是累加
  if(pDim->mode() != dlhml::PILEUP_DIM){
    return false;
  }
  ////如果不显示0，则自身不会干涉
  if(!pDim->show0()){
    return false;
  }
  ////如果不显示尺寸线，则自身不会干涉
  if(!pDim->end_show()){
    return false;
  }

	Point ptBox1[4], ptBox2[4];
	dim_text1_4pt(ptBox1, pDim);
	dim_text2_4pt(ptBox2, pDim);

  return is_intervene_box(ptBox1, ptBox2);

// 	Point ptCen1, ptCen2;
// 	ptCen1 = (ptBox1[0]+ptBox2[3])/2;
// 	ptCen2 = (ptBox2[0]+ptBox2[3])/2;
// 	double disCen = ptCen1.distanceto(ptCen2);			////两个文本中心距
// 	double disBox1= ptBox1[0].distanceto(ptBox1[3]);	////第一个文本宽度
// 	double disBox2= ptBox2[0].distanceto(ptBox2[3]);	////第二个文本宽度
// 	double disTxtHei = ptBox1[0].distanceto(ptBox1[1]);	////文本高度
// 	if (TIAN_GA_BETTER::TMoreThen(disCen, (disBox1+disBox2)/2+disTxtHei*1)) {
// 	    return false;
// 	}
// 	return true;
}


void Paint_Entity_Tools::add_dim_text_pos_layer(Ln_Dim * pDim)
{
	int iLayer = get_dim_text_pos_layer(pDim);
  //iLayer = add_dim_text_pos_layer(iLayer);
	iLayer++;
	set_dim_text_pos_layer(pDim, iLayer);
}
////增加标注文本的层次(0,-1,1,-2,2,-3,3,...)
void Paint_Entity_Tools::add_dim_text_pos_layer_closed(Ln_Dim * pDim)
{
	int iLayer = get_dim_text_pos_layer_closed(pDim);
	iLayer = add_dim_text_pos_layer(iLayer);
	set_dim_text_pos_layer_closed(pDim, iLayer);
}
void Paint_Entity_Tools::add_dim_text_pos_layer(Three_Pt_Dimension * pDim)
{
	int iLayer = get_dim_text_pos_layer(pDim);
	iLayer = add_dim_text_pos_layer(iLayer);
	set_dim_text_pos_layer(pDim, iLayer);
}

////增加标注文本的层次(0,-1,1,-2,2,-3,3,...)
int Paint_Entity_Tools
::add_dim_text_pos_layer(int iLayer)
{
	if (iLayer == 0){
	    return -1;
	}else if (iLayer < 0){
	    return -iLayer;
	}else if (iLayer > 0){
	    return 0-iLayer-1;
	}else{
	    return 0;
	}
	return 0;
}


void Paint_Entity_Tools
::re0_dim_text_pos_layer(Three_Pt_Dimension * pDim)
{
	set_dim_text_pos_layer(pDim, 0);
}
void Paint_Entity_Tools::re0_dim_text_pos_layer_closed(Ln_Dim * pDim)
{
	set_dim_text_pos_layer_closed(pDim, 0);
}
void Paint_Entity_Tools
::re0_dim_text_pos_layer(Ln_Dim * pDim)
{
	set_dim_text_pos_layer(pDim, 0);
}

void Paint_Entity_Tools
::reset_dim_text_pos_layer(Three_Pt_Dimension_Block& dimBlock)
{
	Three_Pt_Dimension* pDimFront = dimBlock.front();
	Three_Pt_Dimension* pDimBack  = dimBlock.back();
	if (!pDimFront || !pDimBack){
	    return;
	}
	re0_dim_text_pos_layer(pDimFront);
	////比较当前标注和下一个标注，若干涉，则改变下一个标注的位置
	////pDimItem当前标注（不经历back()）
	////pDimNext下个标注（不经历front()）
	Three_Pt_Dimension* pDimIter= pDimFront;	
	Three_Pt_Dimension* pDimNext= dimBlock.next(pDimIter);
	Three_Pt_Dimension* pDimPre	= NULL;
	for(pDimIter  = pDimFront; 
		pDimIter != NULL; 
		pDimIter  = dimBlock.next(pDimIter)) 
	{
		re0_dim_text_pos_layer(pDimIter);
		for(pDimPre = dimBlock.front();
			pDimPre!= pDimIter;
			pDimPre = dimBlock.next(pDimPre)) 
		{
			if(is_intervene(pDimIter, pDimPre)) {
			    add_dim_text_pos_layer(pDimIter);
				////干涉之后立刻重新判断
//				pDimPre = dimBlock.front();
			}   
		}
	}
}

static void re0_dimblock_text_pos_layer_closed(Ln_Dim_Block& block)
{
  int i=0;
  for(i=0; i<block.size(); ++i){
    Paint_Entity_Tools::re0_dim_text_pos_layer_closed(block[i]);
  }
}

static void reset_cur_dim__pos_layer_closed(Ln_Dim_Block& block, int cur)
{
  int i=0;
  for(i=0; i<cur; ++i){
    if(Paint_Entity_Tools::is_intervene_closed(block[i], block[cur])){
      Paint_Entity_Tools::add_dim_text_pos_layer_closed(block[cur]);
    }
  }
}

static void reset_all_dim__pos_layer_closed(Ln_Dim_Block& block)
{  
  int i=0;
  for(i=1; i<block.size(); ++i){
    reset_cur_dim__pos_layer_closed(block, i);
  }
}

void Paint_Entity_Tools::reset_dim_text_pos_layer_closed(Ln_Dim_Block& dimBlock)
{
	Ln_Dim* pDimFront = dimBlock.front();
	Ln_Dim* pDimBack  = dimBlock.back();
	if(!pDimFront || !pDimBack){
	  return;
	}

  ////全部等高
  dimBlock.layout_dimlines(dimBlock[0]->odm());
  ////全部回0层
  re0_dimblock_text_pos_layer_closed(dimBlock);
  ////判断没一组是否和前面所有组干涉
  reset_all_dim__pos_layer_closed(dimBlock);
  return;


	re0_dim_text_pos_layer_closed(pDimFront);
	////比较当前标注和下一个标注，若干涉，则改变下一个标注的位置
	////pDimItem当前标注（不经历back()）
	////pDimNext下个标注（不经历front()）
	Ln_Dim* pDimIter= pDimFront;	
	Ln_Dim* pDimNext= dimBlock.next(pDimIter);
	Ln_Dim* pDimPre	= NULL;
	for(pDimIter=pDimFront; pDimIter!= NULL; pDimIter=dimBlock.next(pDimIter)){
    ////先将所有的文本回0
		re0_dim_text_pos_layer_closed(pDimIter);
  }
  for(pDimIter=pDimFront; pDimIter!= NULL; pDimIter=dimBlock.next(pDimIter)){
		//re0_dim_text_pos_layer_closed(pDimIter);
		for(pDimPre=dimBlock.front(); pDimPre!=pDimIter; pDimPre = dimBlock.next(pDimPre)){
			if(is_intervene_closed(pDimIter, pDimPre)){
			    add_dim_text_pos_layer_closed(pDimIter);
				  ////干涉之后立刻重新判断
//				pDimPre = dimBlock.front();
			}   
		}
	}
}
////////若只判断下三个标注的干涉
//	Three_Pt_Dimension* pDimIter  = pDimFront;	
//	Three_Pt_Dimension* pDimNext  = dimBlock.next(pDimIter);
//	Three_Pt_Dimension* pDimNext2 = NULL;
//	Three_Pt_Dimension* pDimNext3 = NULL;
//	for(pDimIter  = pDimFront; pDimIter != pDimBack; pDimIter  = pDimNext) {
//		pDimNext  = dimBlock.next(pDimIter);	////下个标注
//		if (is_intervene(pDimIter, pDimNext)) {
//		    ////若干涉next增加一层
//			add_dim_text_pos_layer(pDimNext);
//		}
//		pDimNext2 = dimBlock.next(pDimNext);	////下二个标注
//		if (is_intervene(pDimIter, pDimNext2)) {
//		    add_dim_text_pos_layer(pDimNext2);
//		}
//		pDimNext3 = dimBlock.next(pDimNext2);	////下三个标注
//		if (is_intervene(pDimIter, pDimNext3)) {
//		    add_dim_text_pos_layer(pDimNext3);
//		}
//	}

////累加标注，全部回0层
static void re0_dimblock_text_pos_layer(Ln_Dim_Block& dimBlock)
{
  int i=0;
  for(i=0; i<dimBlock.size(); ++i){
    Paint_Entity_Tools::re0_dim_text_pos_layer(dimBlock[i]);
  }
}

//
static void reset_first_dim_pos_layer(Ln_Dim_Block& dimBlock)
{
  Ln_Dim* dim = dimBlock.front();
  if(!dim){
    return;
  }
  if(Paint_Entity_Tools::is_intervene(dim)){
    Paint_Entity_Tools::add_dim_text_pos_layer(dim);
  }
}

static void reset_cur_dim_pos_layer(Ln_Dim_Block& dimBlock, int cur)
{
  if(is_intervene_0(dimBlock, cur)){
    Paint_Entity_Tools::add_dim_text_pos_layer(dimBlock[cur]);
  }
  int i=0;
  for(i=0; i<cur; ++i){
    if(Paint_Entity_Tools::is_intervene(dimBlock[i], dimBlock[cur])){
      Paint_Entity_Tools::add_dim_text_pos_layer(dimBlock[cur]);
      i=0;
    }
  }
}

//  从第二组开始
static void reset_all_dim__pos_layer(Ln_Dim_Block& dimBlock)
{
  int i=0;
  for(i=1; i<dimBlock.size(); ++i){
    reset_cur_dim_pos_layer(dimBlock, i);
  }
}

//  累加尺寸
void Paint_Entity_Tools::reset_dim_text_pos_layer(Ln_Dim_Block& dimBlock)
{
	Ln_Dim* pDimFront = dimBlock.front();
	Ln_Dim* pDimBack  = dimBlock.back();
	if (!pDimFront || !pDimBack){
	    return;
	}
	////0点为基准高度，前后都调整。
	////不在需要调整第一个标注高度。
	////任何标注都比较和0点是否干涉。（所有0点高度必须保证一致）
  //	re0_dim_text_pos_layer(pDimFront);
	////比较当前标注和下一个标注，若干涉，则改变下一个标注的位置
	////pDimItem当前标注（不经历back()）
	////pDimNext下个标注（不经历front()）
  //	for(pDimIter  = pDimFront; pDimIter != NULL; pDimIter  = dimBlock.next(pDimIter)) 
  //	{
  //    ////先将所有的文本回0
  //    re0_dim_text_pos_layer(pDimIter);
  //  }

  ////全部回0层
  re0_dimblock_text_pos_layer(dimBlock);
  ////判断第一组是否自己干涉
  reset_first_dim_pos_layer(dimBlock);
  ////判断没一组是否和前面所有组干涉
  reset_all_dim__pos_layer(dimBlock);
  return;

  int i_layer=0, j_layer=0;
	int i = 0, j = 0;
  for(i=0; i<dimBlock.size(); i++){
    i_layer = get_dim_text_pos_layer(dimBlock[i]);
    if(is_intervene(dimBlock[i])){
      add_dim_text_pos_layer(dimBlock[i]);
      i_layer = get_dim_text_pos_layer(dimBlock[i]);
    }
    int intervene_limit = (i>4) ? (i-4) : 0;
    for(j=i-1; j>intervene_limit; --j){
      j_layer = get_dim_text_pos_layer(dimBlock[j]);
      if(is_intervene(dimBlock[i],dimBlock[j])){
        add_dim_text_pos_layer(dimBlock[i]);
        i_layer = get_dim_text_pos_layer(dimBlock[i]);
        j=i;
      }
    }
  }
//    for(j=0; j<i; j++){
//      j_layer = get_dim_text_pos_layer(dimBlock[j]);
//      if(is_intervene(dimBlock[i],dimBlock[j])){
//        add_dim_text_pos_layer(dimBlock[i]);
//        i_layer = get_dim_text_pos_layer(dimBlock[i]);
//        j-=4;
//        if(j<-1){
//          j=-1;
//        }
//      }
//    }
//  }

//	Ln_Dim* pDimIter  = pDimFront;	
//	Ln_Dim* pDimNext  = dimBlock.next(pDimIter);
//	Ln_Dim* pDimPre;
//	for(pDimIter=pDimFront; pDimIter!=NULL; pDimIter=dimBlock.next(pDimIter)){
//		i++;
//		j=0;
//		if(is_intervene(pDimIter)){
//		  add_dim_text_pos_layer(pDimIter);
//		}
//		pDimPre = dimBlock.front();
//		for(;pDimPre!= pDimIter; pDimPre = dimBlock.next(pDimPre)){
//			j++;
//      if(i==j){
//        break;
//      }
//			if(is_intervene(pDimIter, pDimPre)){
//			    add_dim_text_pos_layer(pDimIter);
//				////干涉之后立刻重新判断
//				pDimPre = dimBlock.front();
//        j=0;
//			}   
//		}
//	}
}


Line Paint_Entity_Tools::LineBaseFromDim(Three_Pt_Dimension* pDim)
{
	Line ln;
	GetLineBaseFromPtAndExtAngle(ln, 
		pDim->start_dim_to(), pDim->extend_radian());
	return ln;
}
Line Paint_Entity_Tools::LineBaseFromDim(Ln_Dim* pDim)
{
	Line ln;
	GetLineBaseFromPtAndDimAngle(ln, pDim->opt(), pDim->dim_line_radian());
	return ln;
}


Line Paint_Entity_Tools::LineDimFromDim(Three_Pt_Dimension* pDim)
{
	Point ptExt1, ptExt2;
	Paint_Entity_Tools::GetRectFrom3PointAndExtAngle(ptExt1, ptExt2, 
		pDim->start_dim_to(), pDim->end_dim_to(), 
		pDim->dimension_pt(), pDim->extend_radian());
	return Line(ptExt1, ptExt2);
}
Line Paint_Entity_Tools::LineDim1FromDim(Ln_Dim* pDim)
{
	Point ptExt1, ptExt2;
	////以3点方式分别求标注线1和2
	Paint_Entity_Tools::GetRectFrom3PointAndDimAngle(ptExt1, ptExt2, 
		pDim->opt(), pDim->ept(), 
		pDim->odm(), pDim->dim_line_radian());
	return Line(ptExt1, ptExt2);
}
Line Paint_Entity_Tools::LineDim2FromDim(Ln_Dim* pDim)
{
	Point ptExt1, ptExt2;
	////以3点方式分别求标注线1和2
	Paint_Entity_Tools::GetRectFrom3PointAndDimAngle(ptExt1, ptExt2, 
		pDim->opt(), pDim->ept(), 
		pDim->edm(), pDim->dim_line_radian());
	return Line(ptExt1, ptExt2);
}

bool Paint_Entity_Tools::LineExtFromDim(Line& lnExt1, Line& lnExt2, 
										Three_Pt_Dimension* pDim)
{
	Line lnDim = LineDimFromDim(pDim);
	lnExt1.setdata(pDim->start_dim_to(), lnDim.start());
	lnExt2.setdata(pDim->end_dim_to(), lnDim.end());
	return true;
}
bool Paint_Entity_Tools::LineExtFromDim(Line& lnExt1, Line& lnExt2, 
										Ln_Dim* pDim)
{
	Line lnDim1 = LineDim1FromDim(pDim);
	Line lnDim2 = LineDim2FromDim(pDim);

	lnExt1.setdata(pDim->opt(), lnDim1.start());
	lnExt2.setdata(pDim->ept(), lnDim2.end  ());
	return true;
}

Line Paint_Entity_Tools::LineExt1FromDim(Three_Pt_Dimension* pDim)
{
	Line lnExt1, lnExt2;
	LineExtFromDim(lnExt1, lnExt2, pDim);
	return lnExt1;
}
Line Paint_Entity_Tools::LineExt1FromDim(Ln_Dim* pDim)
{
	Line lnExt1, lnExt2;
	LineExtFromDim(lnExt1, lnExt2, pDim);
	return lnExt1;
}

Line Paint_Entity_Tools::LineExt2FromDim(Three_Pt_Dimension* pDim)
{
	Line lnExt1, lnExt2;
	LineExtFromDim(lnExt1, lnExt2, pDim);
	return lnExt2;
}
Line Paint_Entity_Tools::LineExt2FromDim(Ln_Dim* pDim)
{
	Line lnExt1, lnExt2;
	LineExtFromDim(lnExt1, lnExt2, pDim);
	return lnExt2;
}




double Paint_Entity_Tools::Length(Line ln)
{
	return ln.start().distanceto(ln.end());
}


double Paint_Entity_Tools::WideFromDim(Three_Pt_Dimension* pDim)
{
	Line lnDim = LineDimFromDim(pDim);
	return Length(lnDim);
}
double Paint_Entity_Tools::WideFromDim(Ln_Dim* pDim)
{
	Line lnDim1 = LineDim1FromDim(pDim);
	return Length(lnDim1);
}
////求夹角
double Paint_Entity_Tools::AngleFromDim(Angle_Dimension* pDim)
{
	double dis = pDim->start().distanceto(pDim->end());
	if (TIAN_GA_BETTER::TLessEqu(dis, 0)) {
	    return 0;
	}
	RArc ar = ArcFromDim(pDim);
	return TPG::
		Radian(ar.end_degree2d() - ar.start_degree2d());
}

double Paint_Entity_Tools::LenFromDim(Radius_Dimension* pDim)
{
	return pDim->head().distanceto(pDim->tail());
}

RArc Paint_Entity_Tools
::ArcFromDim(Angle_Dimension* pDim)
{
	RArc ar;
	ar.set(pDim->start(), pDim->dim(), pDim->end());
	return ar;
}

void Paint_Entity_Tools::DimSetByArc(Angle_Dimension& dim, RArc ar)
{
	TArc tar = LArc2Tarc(ar);
	TPoint tptSrt = tar.PtSt();
	TPoint tptEnd = tar.PtEd();
	TPoint tptMid = TPG::MidArcPt(tar);
	Point ptArcCenter	= ar.center();
	Point ptArcStr		= TPoint2LPoint(tptSrt);
	Point ptArcEnd		= TPoint2LPoint(tptEnd);
	Point ptArcMid		= TPoint2LPoint(tptMid);

	dim.vertex(ptArcCenter);
	dim.start(ptArcStr);
	dim.end(ptArcEnd);
	dim.dim(ptArcMid);
}

void Paint_Entity_Tools::DimSet(Angle_Dimension& dim, 
		                            const Point& ptCen  , 
                                const Point& ptSrt  , 
                                const Point& ptEnd  , 
                                const Point& ptDim  )
{
	double r = ptCen.distanceto(ptDim);
	double angleSrt = Radian(ptSrt, ptCen);
	double angleEnd = Radian(ptEnd, ptCen);
	double angle = TTool::Radian(angleEnd-angleSrt);
	angleSrt = TTool::Arc2Angle(angleSrt);
	angleEnd = TTool::Arc2Angle(angleEnd);
	RArc ar;
	if(angle < T_PI){
		ar.set_degree2d(ptCen, r, angleSrt, angleEnd);
	}else{
		ar.set_degree2d(ptCen, r, angleEnd, angleSrt);
	}
	DimSetByArc(dim, ar);
	dim_text_recal(dim);
}

void Paint_Entity_Tools::dim_re0(Three_Pt_Dimension* pDim)
{
	pDim->start_dim_to(Point(0,0,0));
	pDim->end_dim_to(Point(0,0,0));
	pDim->dimension_pt(Point(0,0,0));
}
void Paint_Entity_Tools::dim_re0(Ln_Dim* pDim)
{
	pDim->opt(Point(0,0,0));
	pDim->ept(Point(0,0,0));
	pDim->odm(Point(0,0,0));
	pDim->edm(Point(0,0,0));
}
void Paint_Entity_Tools::dim_re0(Angle_Dimension* pDim)
{
	pDim->vertex(Point(0,0,0));
	pDim->start(Point(0,0,0));
	pDim->end(Point(0,0,0));
	pDim->dim(Point(0,0,0));
}
void Paint_Entity_Tools::dim_re0(Radius_Dimension* pDim)
{
//	pDim->setdata(Point(0,0,0),Point(0,0,0),Point(0,0,0));
}

bool Paint_Entity_Tools::is_dim_0(Three_Pt_Dimension* pDim)
{
	return TIAN_GA_BETTER::TLessEqu(
		WideFromDim(pDim),TIAN_GA_BETTER::FLOAT_ZERO)
		? true : false;
}
bool Paint_Entity_Tools::is_dim_0(Ln_Dim* pDim)
{
	return TIAN_GA_BETTER::TLessEqu(
		WideFromDim(pDim),TIAN_GA_BETTER::FLOAT_ZERO)
		? true : false;
}
bool Paint_Entity_Tools::is_dim_0(Angle_Dimension* pDim)
{
	return TIAN_GA_BETTER::TLessEqu(
		AngleFromDim(pDim),TIAN_GA_BETTER::FLOAT_ZERO)
		? true : false;
}
bool Paint_Entity_Tools::is_dim_0(Radius_Dimension* pDim)
{
	return TIAN_GA_BETTER::TLessEqu(
		LenFromDim(pDim),TIAN_GA_BETTER::FLOAT_ZERO)
		? true : false;
}


Normal Paint_Entity_Tools
::LNormalFromDim(Ln_Dim* pDim)
{
	return LNormalFromAngle(pDim->dim_line_radian());
}


Normal Paint_Entity_Tools
::LNormalExtFromDim(Ln_Dim* pDim)
{
	Normal nm;
	Line lnExt1 = LineExt1FromDim(pDim);
	if (lnExt1.start() != lnExt1.end()) {
	nm.set_data(lnExt1.start(), lnExt1.end());
	}else {
		nm = LNormalFromAngle(pDim->dim_line_radian() 
			+ TIAN_GA_BETTER::PI_R/2);
	}
	return nm;
}


bool Paint_Entity_Tools
::is_dim_order(Ln_Dim* pDim, Ln_Dim_Block* pBlock)
{
	return TIAN_GA_BETTER::TEquFloat(pDim->dim_line_radian(),
									pBlock->dim_line_radian())
									? true : false;
}

void Paint_Entity_Tools::dim_order_recal(Ln_Dim& dim, Ln_Dim_Block* pBlock)
{
  if(!pBlock){
    return;
  }

  Point opt = dim.opt();
  Point ept = dim.ept();
  Line ln;
  ln.setdata(opt, ept);
  Normal nor;
  Float block_radian = pBlock->dim_line_radian();
  radian_2_normal2d(block_radian,nor);
  Float len = ln.length_by_way(nor);
  if(MoreEqu(len,0)){
    dim.dim_line_radian(block_radian);
  }else{
    block_radian+=pi;
    std_radian(block_radian);
    dim.dim_line_radian(block_radian);
  }

//	Normal nmBlcok = LNormalFromAngle(pBlock->dim_line_radian());
//	double dis = DisPtByNormal(dim.opt(), dim.ept(), nmBlcok);
//	if (TIAN_GA_BETTER::TMoreEqu(dis, 0)) {
//	    dim.dim_line_radian(pBlock->dim_line_radian());
//	}else {
//		dim.dim_line_radian(TPG::Radian(pBlock->dim_line_radian()+T_PI));
//	}
}

void Paint_Entity_Tools::Normal2TopOrLeft(Normal& nm)
{
	CGeNorm tnm = Normal2TNormal(nm);
	double angle = TPG::Radian(tnm);
	if(TPG::RadianToQuadrantRe(angle) 
		== 3) 
	{
		nm.set_reverse();
	}
	else if(TPG::RadianToQuadrantRe(angle) 
		== 4)
	{
		nm.set_reverse();
	}
	angle = TPG::Radian(angle);
}

void Paint_Entity_Tools
::dim_get_namal_dis(Three_Pt_Dimension* pDim, 
					Point bg, Point ed , Normal& nm, double& dis)
{
	nm = LNormalFromAngle(pDim->extend_radian());
	dis = DisPtByNormal(bg, ed, nm);
}
void Paint_Entity_Tools
::dim_get_namal_dis(Ln_Dim* pDim, 
					Point bg, Point ed , Normal& nm, double& dis)
{
	nm = LNormalExtFromDim(pDim);
	dis = DisPtByNormal(bg, ed, nm);
}

void Paint_Entity_Tools
::dim_txt_get_namal_dis(Three_Pt_Dimension* pDim, 
					Point bg, Point ed , Normal& nm, double& dis)
{
	double angel = TPG::Radian(
		pDim->extend_radian() + TIAN_GA_BETTER::PI_R/2);
	nm = LNormalFromAngle(angel);
	dis = DisPtByNormal(bg, ed, nm);
}

Point Paint_Entity_Tools
::dim_pt(Ln_Dim* pDim, int pos)
{
	Point ptDimPt;
	switch(pos) {
	case 1:
		ptDimPt = pDim->odm();
		break;
	case 2:
	case 3:
		ptDimPt = pDim->edm();
		break;
	}
	return ptDimPt;
}
void Paint_Entity_Tools
::dim_move(Angle_Dimension* pDim, Point ed)
{
	RArc ar = ArcFromDim(pDim);
	Point ptArcCenter = ar.center();
	dim_move(pDim, ptArcCenter, ed);
}
void Paint_Entity_Tools
::dim_move(Angle_Dimension* pDim, Point bg, Point ed)
{
	Normal nm;
	RArc ar = ArcFromDim(pDim);
	Point ptArcCenter = ar.center();
	Point ptDimCenter = pDim->vertex();
	if(ptDimCenter == ptArcCenter){
		nm.set_data(ptArcCenter, pDim->start());
	}else{
	  nm.set_data(ptArcCenter, ptDimCenter);
	}
	double dis = DisPtByNormal(bg, ed, nm);

	dim_move(pDim, nm, dis);
}
void Paint_Entity_Tools
::dim_move(Angle_Dimension* pDim, Point ed,
		   Line lnExt1, Line lnExt2)
{
	RArc ar = ArcFromDim(pDim);
	Point ptArcCenter = ar.center();
	dim_move(pDim, ptArcCenter, ed, lnExt1, lnExt2);
}
void Paint_Entity_Tools
::dim_move(Angle_Dimension* pDim, Point bg, Point ed,
		Line lnExt1, Line lnExt2)
{
	Normal nm;
	double dis1 = DisPtToLine(ed, lnExt1);
	double dis2 = DisPtToLine(ed, lnExt2);
	if (dis1 < dis2) {
		nm.set_data(lnExt1.start(), lnExt1.end());
	}else {
		nm.set_data(lnExt2.start(), lnExt2.end());
	}
	double dis = DisPtByNormal(bg, ed, nm);
	dim_move(pDim, nm, dis);
}
void Paint_Entity_Tools
::dim_move(Angle_Dimension* pDim, Normal nm, double dis)
{
	pDim->start(pDim->start().polarTo(dis, nm));
	pDim->end(pDim->end().polarTo(dis, nm));
	pDim->dim(pDim->dim().polarTo(dis, nm));
	pDim->text_position(pDim->text_position().polarTo(dis, nm));
}

void Paint_Entity_Tools
::dim_move(Radius_Dimension* pDim, Point ptArrowTail)
{
//	double r = pDim->center().distanceto(pDim->head());
//	Point ptArrowHead = dim_arrow_head(pDim->center(), ptArrowTail, r);
//	pDim->tail(ptArrowTail);
//	pDim->head(ptArrowHead);
//	dim_text_recal(*pDim);
}

void Paint_Entity_Tools
::dim_move(Three_Pt_Dimension* pDim, Point bg, Point ed)
{
	Normal nm;
	double dis = 0;
	dim_get_namal_dis(pDim, bg, ed, nm, dis);
	dim_move(pDim, nm, dis);
}
void Paint_Entity_Tools
::dim_move(Three_Pt_Dimension* pDim, Normal nm, double dis)
{
	Point ptDim = (pDim->dimension_pt()).polarTo(dis, nm);
	Point ptTxt = (pDim->text_position()).polarTo(dis, nm);
	pDim->dimension_pt(ptDim);
	pDim->text_position(ptTxt);
}
void Paint_Entity_Tools
::dim_move(Ln_Dim* pDim, Point ptMoveTo, int pos)
{
	Normal nm;
	double dis = 0;
	Point ptMoveStart = dim_pt(pDim, pos);
	dim_get_namal_dis(pDim, ptMoveStart, ptMoveTo, nm, dis);
	dim_move(pDim, nm, dis, pos);
}
void Paint_Entity_Tools
::dim_move(Ln_Dim* pDim, Normal nm, double dis, int pos)
{
	switch(pos){
	case 1:
		dim_move1(pDim, nm, dis);
		break;
	case 2:
		dim_move2(pDim, nm, dis);
		break;
//	case 3:
//		dim_move3(pDim, nm, dis);
//		break;
	}
}
void Paint_Entity_Tools
::dim_move1(Ln_Dim* pDim, Point ptMoveTo/*, int pos*/)
{
	Normal nm;
	double dis = 0;
	Point ptMoveStart = dim_pt(pDim, 1/*pos*/);
	dim_get_namal_dis(pDim, ptMoveStart, ptMoveTo, nm, dis);
	dim_move1(pDim, nm, dis);
}
void Paint_Entity_Tools
::dim_move1(Ln_Dim* pDim, Normal nm, double dis)
{
	Point ptDim0 = (pDim->odm()).polarTo(dis, nm);
	Point ptTxt0 = (pDim->text_position()).polarTo(dis, nm);
	pDim->odm(ptDim0);
	pDim->text_position(ptTxt0);
}void Paint_Entity_Tools
::dim_move2(Ln_Dim* pDim, Point ptMoveTo/*, int pos*/)
{
	Normal nm;
	double dis = 0;
	Point ptMoveStart = dim_pt(pDim, 2/*pos*/);
	dim_get_namal_dis(pDim, ptMoveStart, ptMoveTo, nm, dis);
	dim_move2(pDim, nm, dis);
}
void Paint_Entity_Tools
::dim_move2(Ln_Dim* pDim, Normal nm, double dis)
{
	Point ptDim2 = (pDim->edm()).polarTo(dis, nm);
	Point ptTxt2 = (pDim->text2_position()).polarTo(dis, nm);
	pDim->edm(ptDim2);
	pDim->text2_position(ptTxt2);
}
//void Paint_Entity_Tools
//::dim_move2by0(Ln_Dim* pDim, Normal nm, double dis)
//{
//  pDim->offset_dm(nm,dis,2);
//	////以0点为标准
////	Point ptDim2 = (pDim->odm()).polarTo(dis, nm);
////	dim_move2(pDim, ptDim2);
//}
//void Paint_Entity_Tools
//::dim_move3(Ln_Dim* pDim, Point ptMoveTo/*, int pos*/)
//{
//	Normal nm;
//	double dis = 0;
//	Point ptMoveStart = dim_pt(pDim, 3/*pos*/);
//	dim_get_namal_dis(pDim, ptMoveStart, ptMoveTo, nm, dis);
//	dim_move3(pDim, nm, dis);
//}
//void Paint_Entity_Tools
//::dim_move3(Ln_Dim* pDim, Normal nm, double dis)
//{
//	Point ptTxt3 = (pDim->text3_position()).polarTo(dis, nm);
//	pDim->text3_position(ptTxt3);
//}
//void Paint_Entity_Tools
//::dim_move3by0(Ln_Dim* pDim, Normal nm, double dis)
//{
//							////以0点为标准
//	Point ptTxt3 = (pDim->text_position()).polarTo(dis, nm);
//	dim_move3(pDim, ptTxt3);
////	pDim->text3_position(ptTxt3);
//}

void Paint_Entity_Tools
::dim_move_all0(Ln_Dim_Block* pblock, Point ptMoveTo)
{
	if(!pblock){
	  return;  
	}
	Ln_Dim* it = NULL;
	for (it = pblock->front(); it != NULL; it = pblock->next(it)){
    dim_move1(it, ptMoveTo);
	}
}



void Paint_Entity_Tools
::dim_txt_move(Three_Pt_Dimension* pDim, Normal nm, double dis)
{
	Point ptTxt = (pDim->text_position()).polarTo(dis, nm);
	pDim->text_position(ptTxt);
}
void Paint_Entity_Tools
::dim_txt_move(Three_Pt_Dimension* pDim, Point bg, Point ed)
{
	Normal nm;
	double dis = 0;
	dim_txt_get_namal_dis(pDim, bg, ed, nm, dis);
	dim_txt_move(pDim, nm, dis);
}


void Paint_Entity_Tools
::dim_copy(Three_Pt_Dimension& dimD, const Three_Pt_Dimension& dimS)
{
	dimD.color(dimS.color());
	dimD.dim_style_name(dimS.dim_style_name());
	dimD.extend_radian(dimS.extend_radian());

	dimD.start_dim_to(dimS.start_dim_to());
	dimD.end_dim_to(dimS.end_dim_to());
	dimD.dimension_pt(dimS.dimension_pt());

	dimD.dim_text(dimS.dim_text());
	dimD.text_position(dimS.text_position());
	dimD.text_rotation(dimS.text_rotation());
	dimD.align_point(dimS.align_point());
}
void Paint_Entity_Tools
::dim_copy(Ln_Dim& dimD, const Ln_Dim& dimS)
{
	dimD.color(dimS.color());
	dimD.dim_style_name(dimS.dim_style_name());
	dimD.show0(dimS.show0());
	
	dimD.dim_line_radian(dimS.dim_line_radian());

	dimD.opt(dimS.opt());
	dimD.ept(dimS.ept());
	dimD.odm(dimS.odm());
	dimD.edm(dimS.edm());
	dimD.dim_line_radian(dimS.dim_line_radian());

	dimD.dim_text(dimS.dim_text());
	dimD.text_position(dimS.text_position());
	dimD.text_rotation(dimS.text_rotation());
	dimD.align_point(dimS.align_point());
	
	dimD.dim_text2(dimS.dim_text2());
	dimD.text2_position(dimS.text2_position());
	dimD.text2_rotation(dimS.text2_rotation());
	dimD.align_point2(dimS.align_point2());
	
//	dimD.dim_text3(dimS.dim_text3());
//	dimD.text3_position(dimS.text3_position());
//	dimD.text3_rotation(dimS.text3_rotation());
//	dimD.align_point3(dimS.align_point3());
}
void Paint_Entity_Tools
::dim_copy(Angle_Dimension& dimD, const Angle_Dimension& dimS)
{
	dimD.color(dimS.color());
	dimD.dim_style_name(dimS.dim_style_name());
	
	dimD.vertex(dimS.vertex());
	dimD.start(dimS.start());
	dimD.end(dimS.end());
	dimD.dim(dimS.dim());

	dimD.dim_text(dimS.dim_text());
	dimD.text_position(dimS.text_position());
	dimD.text_rotation(dimS.text_rotation());
	dimD.align_point(dimS.align_point());
}

void Paint_Entity_Tools
::dim_block_copy(Three_Pt_Dimension_Block& blockD, 
				 Three_Pt_Dimension_Block& blockS)
{
	if (blockS.size() == 0){
	    return;
	}
	int i = blockS.size();
	blockD.clear();
	Three_Pt_Dimension* pDim = blockS.front();
	Three_Pt_Dimension* pTemp= NULL;
	for(; pDim != NULL; pDim = blockS.next(pDim)){
		pTemp = Three_Pt_Dimension::create_me();
		dim_copy(*pTemp, *pDim);
	    blockD.push_back(pTemp);
	}
}
void Paint_Entity_Tools::dim_block_copy(Ln_Dim_Block& blockD, 
				                                Ln_Dim_Block& blockS)
{
	if(blockS.size() == 0) {
	  return;
	}
	int i = blockS.size();
	blockD.clear();
	Ln_Dim* pDim = blockS.front();
	Ln_Dim* pTemp= NULL;
	for(; pDim != NULL; pDim = blockS.next(pDim)) 
	{
		pTemp = Ln_Dim::create_me();
		dim_copy(*pTemp, *pDim);
		//dim_text_recal(*pDim, scene);
    blockD.push_back(pTemp);
	}
}
void Paint_Entity_Tools::dim_block_copy(Angle_Dimension& blockD, 
                                        Angle_Dimension& blockS)
{
	dim_copy(blockD, blockS);
}

void Paint_Entity_Tools::dim_extend_angle_recal(Three_Pt_Dimension& dim)
{
	Line lnExt = LineExt1FromDim(&dim);
	if (lnExt.start() != lnExt.end()) {
	    double angleExt = Radian(lnExt.end(), lnExt.start());
		dim.extend_radian(angleExt);
	}
}

void Paint_Entity_Tools::dim_text_recal(Three_Pt_Dimension& dim)
{
	if(Paint_Entity_Tools::is_dim_0(&dim)){
	    return;
	}
	dim_text_content (dim);
	dim_text_position(dim);
	dim_text_rotation(dim);
	dim_text_alignpt (dim);
}
void Paint_Entity_Tools::dim_text_recal_closed(Ln_Dim& dim)
{
	if(Paint_Entity_Tools::is_dim_0(&dim)){
	    return;
	}
	dim_text_content_closed (dim);
	dim_text_position(dim);
	dim_text_rotation(dim);
	dim_text_alignpt(dim);
}
void Paint_Entity_Tools::dim_text_recal(Ln_Dim& dim)
{
	if(Paint_Entity_Tools::is_dim_0(&dim)){
	  return;
	}
	dim_text_content(dim);
	dim_text_position(dim);
	dim_text_rotation(dim);
	dim_text_alignpt(dim);
}
void Paint_Entity_Tools::dim_text_recal(Angle_Dimension& dim)
{
	if(Paint_Entity_Tools::is_dim_0(&dim)){
	    return;
	}
	dim_text_content(dim);
	dim_text_position(dim);
	dim_text_rotation(dim);
	dim_text_alignpt(dim);
}
void Paint_Entity_Tools::dim_text_recal(Radius_Dimension& dim)
{
	if(Paint_Entity_Tools::is_dim_0(&dim)){
	    return;
	}
	dim_text_content(dim);
	dim_text_position(dim);
	dim_text_rotation(dim);
	dim_text_alignpt(dim);
}


void Paint_Entity_Tools::dim_text_content(Three_Pt_Dimension& dim)
{
	Point ptExt1, ptExt2;
	Paint_Entity_Tools::GetRectFrom3PointAndExtAngle(ptExt1, ptExt2, 
		dim.start_dim_to(), dim.end_dim_to(), 
		dim.dimension_pt(), dim.extend_radian());
	TCHAR buf[TGC_INT_DIM_TEXT_MAXSIZE];
	double dis = ptExt1.distanceto(ptExt2);
	int len = sprintf(buf, TEXT("%f\0"), dis);
	dim.dim_text(buf);
}
void Paint_Entity_Tools::dim_text_content_closed(Ln_Dim& dim)
{
  Line sexln, eexln, sdmln;
  dim.get_s_lines(sexln,eexln,sdmln);
	TCHAR buf[TGC_INT_DIM_TEXT_MAXSIZE];
	double dis = sdmln.length();
	int len = sprintf(buf, TEXT("%f\0"), dis);
	dim.dim_text(buf);
}
void Paint_Entity_Tools::dim_text_content(Ln_Dim& dim)
{
 	if(dim.user_content_){
		return;
	}
//	if(dim.pf_content_){
//		dim.pf_content_(dim);
//		return;
//	}

	if(dim.mode() == PILEUP_DIM){
    //bet dfx
	  dim.dim_text("0");
    Line oexln, eexln, odmln, edmln;
    dim.get_o_lines(oexln, odmln);
    dim.get_e_lines(eexln, edmln);
    Point pedal_in_odm = PointPedal(eexln.end(), oexln);
	  TCHAR buf[TGC_INT_DIM_TEXT_MAXSIZE];
	  double dis = pedal_in_odm.distanceto(eexln.end());
	  int len = sprintf(buf, TEXT("%f\0"), dis);
	  dim.dim_text2(buf);
  }
  else if(dim.mode() == CLOSED_DIM){
    Line sexln, eexln, sdmln;
    dim.get_s_lines(sexln,eexln,sdmln);
	  TCHAR buf[TGC_INT_DIM_TEXT_MAXSIZE];
	  double dis = sdmln.length();
	  int len = sprintf(buf, TEXT("%f\0"), dis);
	  dim.dim_text(buf);
	  dim.dim_text2("");	
  }
	////第三个文本置空////暂时
	//dim.dim_text3("");	

//bet 2009.06.15
//    //bet dfx
//	  dim.dim_text("0");
//    Line lnExt1, lnExt2;
//    Line lnDim1, lnDim2;
//    dim.get_o_lines(lnExt1, lnDim1);
//    dim.get_e_lines(lnExt2, lnDim2);
//    Point ptPedalExt1 = PointPedal(lnExt2.end(), lnExt1);
//	  TCHAR buf[TGC_INT_DIM_TEXT_MAXSIZE];
//	  double dis = ptPedalExt1.distanceto(lnExt2.end());
//	  int len = sprintf(buf, TEXT("%f\0"), dis);
//	  dim.dim_text2(buf);
//
//	////第三个文本置空////暂时
//	dim.dim_text3("");	
//ter 2009.06.15

}
void Paint_Entity_Tools::dim_text_content(Angle_Dimension& dim)
{
	double b = Radian(dim.start(), dim.vertex());
	double e = Radian(dim.end(), dim.vertex());
	double ar= TPG::Radian(e-b);
	double an= TPG::Arc2Angle(ar);
	int    du= int(an);
	int    fe= int((an-du)*60);
	TCHAR buf[TGC_INT_DIM_TEXT_MAXSIZE];
	int len = sprintf(buf, TEXT("%d並%d\'\0"), du, fe);
	dim.dim_text(buf);
}
void Paint_Entity_Tools
::dim_text_content(Radius_Dimension& dim)
{
//	double r = dim.center().distanceto(dim.head());
//	TCHAR buf[TGC_INT_DIM_TEXT_MAXSIZE];
//	int len = sprintf(buf, TEXT("%f\0"), r);
//	dim.dim_text(buf);
}


void Paint_Entity_Tools
::dim_text_position(Three_Pt_Dimension& dim)
{
	Point ptExt1, ptExt2;
	Paint_Entity_Tools::GetRectFrom3PointAndExtAngle(ptExt1, ptExt2, 
		dim.start_dim_to(), dim.end_dim_to(), 
		dim.dimension_pt(), dim.extend_radian());
	Point ptTxtPos = (ptExt1+ptExt2)/2;
	dim.text_position(ptTxtPos);
	
}
//void Paint_Entity_Tools::dim_text_position_closed(Ln_Dim& dim)
//{
//  Line sexln,eexln,sdmln;
//  dim.get_s_lines(sexln,eexln,sdmln);
//	//Point ptTxtPos = (ptExt1+ptExt2)/2;
//	dim.text_position(sdmln.middle());
//	
//}
void Paint_Entity_Tools::dim_text_position(Ln_Dim& dim)
{
  Line oexln, sexln, eexln, odmln, edmln;
  if(dim.mode() == PILEUP_DIM){
    dim.get_o_lines(oexln, odmln);
    dim.get_e_lines(eexln, edmln);
    Point pos1 = odmln.middle();
    Point pos2 = edmln.middle();
    dim.text_position (pos1);
    dim.text2_position(pos2);
    //dim.text3_position(pos2);	////第三个文本
  }else if(dim.mode() == CLOSED_DIM){
    dim.get_s_lines(sexln, eexln, edmln);
    Point pos1 = edmln.middle();
    dim.text_position (pos1);
    dim.text2_position(pos1);
    //dim.text3_position(pos1);	////第三个文本
  }


  
//bet 2009.06.15
////bet dfx
////  Point ptDim1, ptDim2;
////  Paint_Entity_Tools::GetRectFrom4PointAndAngle(ptDim1, ptDim2, 
////    dim.start(), dim.end(), 
////    dim.dim_start_pt(), dim.dim_end_pt(),
////    dim.dim_line_radian());
//
//  //Point ptExt1, ptExt2;     // enxtend point
//  Line  lnExt1, lnExt2;     // enxtend line
//  //Point ptDim1, ptDim2;     // dimension point
//  Line  lnDim1, lnDim2;     // dimension line
//  dim.get_o_lines(lnExt1, lnDim1);
//  dim.get_e_lines(lnExt2, lnDim2);
////  ptDim1 = lnDim1.end();
////  ptDim2 = lnDim2.end();
////  
////  Normal nmDim = LNormalFromAngle(dim.dim_line_radian());
////  Point ptTxtBox1[4], ptTxtBox2[4];
////  dim_text1_4pt(ptTxtBox1, &dim);
////  dim_text2_4pt(ptTxtBox2, &dim);
////  double disTxtMove1 = ptTxtBox1[0].distanceto(ptTxtBox1[3])/2;
////  double disTxtMove2 = ptTxtBox2[0].distanceto(ptTxtBox2[3])/2;
////
////  if(scene != NULL){
////    Dimension_Style* ds = NULL;
////    scene->database()->get_dimensionstyle(ds, dim.dim_style());
////    double arrow_size = ds->arrow_size();
////
////    //disTxtMove1 += arrow_size;
////    disTxtMove2 += arrow_size;
////  }
////
////  Point ptTxtMove1, ptTxtMove2;
////  ptTxtMove1 = ptDim1.polarTo(+disTxtMove1, nmDim);
////  ptTxtMove2 = ptDim2.polarTo(-disTxtMove2, nmDim);
////  
////  dim.text_position (ptTxtMove1);
////  dim.text2_position(ptTxtMove2);
////  dim.text3_position(ptTxtMove2);	////第三个文本
//
//  Point pos1 = (lnDim1.start()+lnDim1.end())/2;
//  Point pos2 = (lnDim2.start()+lnDim2.end())/2;
//  dim.text_position (pos1);
//  dim.text2_position(pos2);
//
//
//  dim.text3_position(pos2);	////第三个文本
//bet 2009.06.15

}
void Paint_Entity_Tools::dim_text_position(Angle_Dimension& dim)
{
	dim.text_position(dim.dim());
}
void Paint_Entity_Tools::dim_text_position(Radius_Dimension& dim)
{
	dim.text_position((dim.tail()+dim.head())/2);
}

void Paint_Entity_Tools::dim_text_rotation(Three_Pt_Dimension& dim)
{
	Line lnDim = LineDimFromDim(&dim);
	double dTxtRota = Radian(lnDim.end(), lnDim.start());
	if(TPG::RadianToQuadrantRe(dTxtRota)      == 2){
		dTxtRota += TIAN_GA_BETTER::PI_R;
	}
	else if(TPG::RadianToQuadrantRe(dTxtRota) == 3){
		dTxtRota -= TIAN_GA_BETTER::PI_R;
	}
	dTxtRota = TPG::Radian(dTxtRota);
	dim.text_rotation(dTxtRota);
}
void Paint_Entity_Tools::dim_text_rotation(Ln_Dim& dim)
{
	double dTxtRota = dim.dim_line_radian();
	if(TPG::RadianToQuadrantRe(dTxtRota)       == 2){
		dTxtRota += TIAN_GA_BETTER::PI_R;
	}
	else if(TPG::RadianToQuadrantRe(dTxtRota)	 == 3){
		dTxtRota -= TIAN_GA_BETTER::PI_R;
	}
	dTxtRota = TPG::Radian(dTxtRota);
	dim.text_rotation(dTxtRota);
	dim.text2_rotation(dTxtRota);

	////第三个文本还有待处理
	//dim.text3_rotation(dTxtRota);
}
void Paint_Entity_Tools::dim_text_rotation(Angle_Dimension& dim)
{
	RArc ar = ArcFromDim(&dim);
	TArc tarc = LArc2Tarc(ar);
	double dAngleMid = TPG::MidArc(tarc);
	double dTxtRota = TPG::Radian(
		dAngleMid+T_PI/2);
	if(TPG::RadianToQuadrantRe(dTxtRota) 
		== 2) 
	{
		dTxtRota += TIAN_GA_BETTER::PI_R;
	}
	else if(TPG::RadianToQuadrantRe(dTxtRota) 
		== 3)
	{
		dTxtRota -= TIAN_GA_BETTER::PI_R;
	}
	dTxtRota = TPG::Radian(dTxtRota);
	dim.text_rotation(dTxtRota);
}
//void Paint_Entity_Tools::dim_text_rotation(Angle_Dimension& dim)
//{
//	RArc ar = ArcFromDim(&dim);
//	TArc tarc = LArc2Tarc(ar);
//	double dAngleMid = TPG::MidArc(tarc);
//	double dTxtRota = TPG::Radian(
//		dAngleMid+T_PI/2);
//	if(TPG::RadianToQuadrantRe(dTxtRota) 
//		== 2) 
//	{
//		dTxtRota += TIAN_GA_BETTER::PI_R;
//	}
//	else if(TPG::RadianToQuadrantRe(dTxtRota) 
//		== 3)
//	{
//		dTxtRota -= TIAN_GA_BETTER::PI_R;
//	}
//	dTxtRota = TPG::Radian(dTxtRota);
//	dim.text_rotation(dTxtRota);
//}
void Paint_Entity_Tools::dim_text_rotation(Radius_Dimension& dim)
{
	double dTxtRota = Radian(dim.tail(), dim.head());
	if(TPG::RadianToQuadrantRe(dTxtRota)      == 2){
		dTxtRota += TIAN_GA_BETTER::PI_R;
	}
	else if(TPG::RadianToQuadrantRe(dTxtRota) == 3){
		dTxtRota -= TIAN_GA_BETTER::PI_R;
	}
	dTxtRota = TPG::Radian(dTxtRota);
	dim.text_rotation(dTxtRota);
}


void Paint_Entity_Tools::dim_text_alignpt(Three_Pt_Dimension& dim)
{
//	dim.align_point(Text::center_bottom);
}
void Paint_Entity_Tools::dim_text_alignpt(Ln_Dim& dim)
{
//  dim.align_point (Text::center_bottom);
//  dim.align_point2(Text::center_bottom);
//  dim.align_point3(Text::center_bottom);
}
void Paint_Entity_Tools::dim_text_alignpt(Angle_Dimension& dim)
{
	dim.align_point(Text::center_bottom);
}
void Paint_Entity_Tools::dim_text_alignpt(Radius_Dimension& dim)
{
	dim.align_point(Text::center_bottom);
}

Normal Paint_Entity_Tools::LNormalFromAngle(double angle)
{
  TIAN_GA_BETTER::CGeNorm tnm	= TPG::NormalFromAngle(angle);
  return TNormal2Normal(tnm);
}

void Paint_Entity_Tools::dim_block_split(Three_Pt_Dimension_Block& blockOld, 
				                                 Three_Pt_Dimension_Block& blockNew, 
				                                 Three_Pt_Dimension * pdimSlipt)
{
	if(blockOld.size() == 0){
	    return;
	}
	if(!pdimSlipt){
	    return;
	}
	blockNew.clear();
	Three_Pt_Dimension* pDimNew;
	Three_Pt_Dimension* itNext  = blockOld.next(pdimSlipt);	
	for(; itNext != NULL; itNext=blockOld.next(pdimSlipt)){
		pDimNew = Three_Pt_Dimension::create_me();
		dim_copy(*pDimNew, *itNext);
		blockNew.push_back(pDimNew);
		blockOld.erase(itNext);
	}
	blockOld.erase(pdimSlipt);
}


////必须有某个标注正在显示状态
//void Paint_Entity_Tools::block_dim_show0(Ln_Dim_Block* pblock)
//{
//  if(!pblock || pblock->size() == 0){
//    return;
//  }
//  Ln_Dim* first = pblock->front();
//  Ln_Dim* last	 = pblock->back();
//  Ln_Dim* it = first;
//  
//  for(; it != NULL; it = pblock->next(it)){
//    it->show0(false);
//  }
//  last->show0(true);
//}

void Paint_Entity_Tools
::block_it_move_pre(Ln_Dim** ppdim, 
			   Ln_Dim_Block* pblock, int pos)
{
	for(int i=0; i< pos && ppdim != NULL && *ppdim != NULL; i++){
		*ppdim = pblock->previous(*ppdim);
	}
}

void Paint_Entity_Tools
::block_it_move_pre_or_to_first(Ln_Dim** ppdim, 
								Ln_Dim_Block* pblock, int pos)
{
	if (!ppdim){
		return;
	}
	block_it_move_pre(ppdim, pblock, pos);
	if (!(*ppdim)){
		*ppdim = pblock->front();
	}
}
 

void Paint_Entity_Tools::dim_angle_pt(Point& st, 
                                      Point& ed, 
                                      Point cen, 
                                      Point dim)
{
  double r = cen.distanceto(dim);
  TPoint tst = LPoint2TPoint(st);
  TPoint ted = LPoint2TPoint(ed);
  TPoint tce = LPoint2TPoint(cen);
  TArc tarc(tce, r, tst, ted);
  tst = tarc.PtSt();
  ted = tarc.PtEd();
  st = TPoint2LPoint(tst);
  ed = TPoint2LPoint(ted);
}

void Paint_Entity_Tools
::dim_angle_pt(Angle_Dimension& dim)
{
	Point st = dim.start();
	Point ed = dim.end();
	dim_angle_pt(st, ed, dim.vertex(), dim.dim());
	dim.start(st);
	dim.end(ed);
}


bool Paint_Entity_Tools
::is_intervene(Angle_Dimension* pDim1, Angle_Dimension* pDim2)
{
	Normal nm;
	Line lnExt1;
	if (lnExt1.start() != lnExt1.end()){
	nm.set_data(lnExt1.start(), lnExt1.end());
	}
	return true;
}


////圆心点+箭尾点+半径 ==》 箭头点
Point Paint_Entity_Tools::dim_arrow_head(Point c, Point tail, double r)
{
	Normal nm;
	nm.set_data(c, tail);
	return c.polarTo(r, nm);
//  Normal nm;
//  nm.set_data(c,tail);
// double dis = c.distanceto2d(head);
//  if(dis)
}


bool Paint_Entity_Tools::is_line_superpositon(Line ln1, Line ln2)
{
	TLine tln1 = LLine2TLine(ln1);
	TLine tln2 = LLine2TLine(ln2);
	return TPG::is_line_superpositon(tln1, tln2);
}

void Paint_Entity_Tools::recal_block_order(Ln_Dim_Block& dimBlock)
{
  Ln_Dim * it = dimBlock.front();
  for(; it!=NULL; it=dimBlock.next(it)){
    dim_order_recal(*it,&dimBlock);
  }
}
void Paint_Entity_Tools::recal_block_text(Ln_Dim_Block& dimBlock)
{
  Ln_Dim * it = dimBlock.front();
  for(; it!=NULL; it=dimBlock.next(it)){
    dim_text_recal(*it);
  }
}
void Paint_Entity_Tools::recal_block_text_closed(Ln_Dim_Block& dimBlock)
{
  Ln_Dim * it = dimBlock.front();
  for(; it!=NULL; it=dimBlock.next(it)){
    dim_text_recal_closed(*it);
  }
}

// void Paint_Entity_Tools::recal_dim_block(Ln_Dim_Block& dimBlock)
// {
//   dimBlock.recal_e_pt();
//   recal_block_order(dimBlock);
//   recal_dim_spt(dimBlock);
//   //dimBlock.opt(dimBlock.opt());
//   if(dimBlock.mode() == PILEUP_DIM){
//     recal_block_text(dimBlock);
//     reset_dim_text_pos_layer(dimBlock);
//     //dimBlock.recal_show0();
//     //block_dim_show0(&dimBlock);
//   }else if(dimBlock.mode() == CLOSED_DIM){
//     recal_block_text_closed(dimBlock);
//     reset_dim_text_pos_layer_closed(dimBlock);
//     //block_dim_show0(&dimBlock);
//   }
// }

void Paint_Entity_Tools::recal_dim_block(Ln_Dim_Block& dimBlock)
{
  recal_dim_block_pt(dimBlock);
  recal_dim_block_txt(dimBlock);
  recal_dim_block_show0(dimBlock);
}

void Paint_Entity_Tools::repos_dim_block(Ln_Dim_Block& dimBlock)
{
  recal_dim_block(dimBlock);
  recal_dim_block_txtpos(dimBlock);
}

void Paint_Entity_Tools::recal_dim_block_pt(Ln_Dim_Block& dimBlock)
{
  dimBlock.recal_e_pt();
  recal_block_order(dimBlock);
  recal_dim_spt(dimBlock);
  //dimBlock.opt(dimBlock.opt());
}

void Paint_Entity_Tools::recal_dim_block_txt(Ln_Dim_Block& dimBlock)
{
  if(dimBlock.mode() == PILEUP_DIM){
    recal_block_text(dimBlock);
  }else if(dimBlock.mode() == CLOSED_DIM){
    recal_block_text_closed(dimBlock);
  }
}

void Paint_Entity_Tools::recal_dim_block_show0(Ln_Dim_Block& dimBlock)
{
  if(dimBlock.mode() == PILEUP_DIM){
    dimBlock.recal_show0();
    //block_dim_show0(&dimBlock);
  }else if(dimBlock.mode() == CLOSED_DIM){
    //reset_dim_text_pos_layer_closed(dimBlock);
    //block_dim_show0(&dimBlock);
  }
}

void Paint_Entity_Tools::recal_dim_block_txtpos(Ln_Dim_Block& dimBlock)
{
  if(dimBlock.mode() == PILEUP_DIM){
    reset_dim_text_pos_layer(dimBlock);
  }else if(dimBlock.mode() == CLOSED_DIM){
    reset_dim_text_pos_layer_closed(dimBlock);
  }
}



void Paint_Entity_Tools::recal_dim_spt(Ln_Dim_Block& block)
{
  Ln_Dim * it = block.front();
  for(; it!=NULL; it=block.next(it)){
    if(is_dim_order(it, &block)){ 
      ////顺序
      Ln_Dim * prev_dim = block.previous(it);
      if(prev_dim && is_dim_order(prev_dim, &block)){
        ////前一个也是顺序
        it->spt(prev_dim->ept());
      }
      else{
        ////前一个不存在或者前一个是逆序
        it->spt(it->opt());
      }
    }
    else{
      ////逆序
      Ln_Dim * next_dim = block.next(it);
      if(next_dim && !is_dim_order(next_dim, &block)){
        ////后一个也是逆序
        it->spt(next_dim->ept());
      }
      else{
        ////后一个不存在或者后一个是顺序
        it->spt(it->opt());
      }
    }
  }
}
bool Paint_Entity_Tools::is_0_position(Ln_Dim_Block * block_1, 
                                       Ln_Dim_Block * block_2)
{
	if(block_1 == block_2){
	  return false;
	}

	Line ln1 = LineExt1FromDim(block_1->front());
	Line ln2 = LineExt1FromDim(block_2->front());
	//  两条直线是否重合
	if(is_line_superpositon(ln1, ln2)){
	  return true;
	}else{
	  return false;
	}
}



}//namespace