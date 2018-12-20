
#ifndef _TIAN_DISPLAY_OFFSET_DRAG_PT_H_
#define _TIAN_DISPLAY_OFFSET_DRAG_PT_H_

#include "Visitor.h"
#include "Point.h"

namespace dlhml{

class Offset_Drag_Pt : public Visitor
{
public:
	Offset_Drag_Pt()MCT_INIT1("Offset_Drag_Pt"){}
public:
  Point get_drag_pt()const{return pt_;}
protected:
  virtual bool visit_line_arrow (Line_Arrow & la);
  virtual bool Visit_Arc_Arrow  (Arc_Arrow  & aa);
  virtual bool Visit_Circle     (Circle     & cr);
  virtual bool Visit_Cloud_Line (Cloud_Line & cl);
protected:
  Point pt_;
	
private:
	MCT_DEF
};


}//namespace
#endif//FILE

