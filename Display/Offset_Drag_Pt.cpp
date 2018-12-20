
#include "StdAfx.h"
#include "Offset_Drag_Pt.h"

#include "Line_Arrow.h"
#include "Arc_Arrow.h"
#include "Circle.h"
#include "Cloud_Line.h"

namespace dlhml{

bool Offset_Drag_Pt::visit_line_arrow (Line_Arrow & la)
{
  Line ln;
  la.getdata(ln);
  pt_ = ln.middle();
  return true;
}
bool Offset_Drag_Pt::Visit_Arc_Arrow  (Arc_Arrow  & aa)
{
  RArc ac;
  ac = aa.get();
  pt_ = ac.middle();
  return true;
}
bool Offset_Drag_Pt::Visit_Circle     (Circle     & cr)
{
  std::vector<Point> pts;
  cr.getdrag(pts);
  if(pts.empty()){
    pt_=cr.center();
  }
  else{
    pt_=pts.back();
  }
  return true;
}
bool Offset_Drag_Pt::Visit_Cloud_Line (Cloud_Line & cl)
{
  if(!cl.line()){
    return false;
  }

  std::vector<Point> pts;
  cl.getdata(pts);
  if(pts.size()<2){
    return false;
  }
  else{
    Line ln;
    ln.setdata(pts[0],pts[1]);
    pt_=ln.middle();
  }
  return true;
}



}//namespace




