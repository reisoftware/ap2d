// Paint_Snap.cpp: implementation of the Paint_Snap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Paint_Snap.h"
#include "Line.h"
#include "Circle.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Paint_Snap::Paint_Snap()
:ondraw_(false)
MCT_INIT2("Paint_Snap")
{
	old_.zero();
	current_.zero();
}

Paint_Snap::~Paint_Snap()
{

}
void Paint_Snap::draw_snap(Draw_Entity& out,Float len)
{
  COLORREF snap_cr = RGB(255,100,255);
	Point st,ed;
	if(old_.endpoint()){
		Line line;
		line.color(snap_cr);

		st.setdata(pt_.x-len,pt_.y-len);
		ed.setdata(pt_.x-len,pt_.y+len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x-len,pt_.y+len);
		ed.setdata(pt_.x+len,pt_.y+len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x+len,pt_.y+len);
		ed.setdata(pt_.x+len,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x+len,pt_.y-len);
		ed.setdata(pt_.x-len,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);
	}else	if(old_.center()){
		Circle cir;
    cir.selected(true);
		cir.color(snap_cr);
		cir.setdata(pt_,len);
		cir.xor_draw(out);
	}else	if(old_.middle()){
		Line line;
		line.color(snap_cr);

		st.setdata(pt_.x-len,pt_.y-len);
		ed.setdata(pt_.x,pt_.y+len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x,pt_.y+len);
		ed.setdata(pt_.x+len,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x+len,pt_.y-len);
		ed.setdata(pt_.x-len,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);
	}else	if(old_.perpendicular()){
		Line line;
		line.color(snap_cr);
		
		st.setdata(pt_.x-len,pt_.y-len);
		ed.setdata(pt_.x-len,pt_.y+len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x-len,pt_.y);
		ed = pt_;
		line.setdata(st,ed);
		line.xor_draw(out);
		st = pt_;
		ed.setdata(pt_.x,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x-len,pt_.y-len);
		ed.setdata(pt_.x+len,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);

	}else if(old_.intersect()){
		Line line;
		line.color(snap_cr);
		
		st.setdata(pt_.x-len,pt_.y);
		ed.setdata(pt_.x+len,pt_.y);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x,pt_.y-len);
		ed.setdata(pt_.x,pt_.y+len);
		line.setdata(st,ed);
		line.xor_draw(out);

		st.setdata(pt_.x-len,pt_.y+len);
		ed.setdata(pt_.x+len,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x-len,pt_.y-len);
		ed.setdata(pt_.x+len,pt_.y+len);
		line.setdata(st,ed);
		line.xor_draw(out);

	}else if(old_.nearest()){
		Line line;
		line.color(snap_cr);
		
		st.setdata(pt_.x-len,pt_.y-len);
		ed.setdata(pt_.x+len,pt_.y+len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x+len,pt_.y+len);
		ed.setdata(pt_.x-len,pt_.y+len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x-len,pt_.y+len);
		ed.setdata(pt_.x+len,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);
		st.setdata(pt_.x+len,pt_.y-len);
		ed.setdata(pt_.x-len,pt_.y-len);
		line.setdata(st,ed);
		line.xor_draw(out);
	}else{}
}
}
