// Paint_Snap.h: interface for the Paint_Snap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_PAINT_SNAP_H__195F2231_473A_4553_A6B9_9727AC6FCD64__INCLUDED_
#define AFX_PAINT_SNAP_H__195F2231_473A_4553_A6B9_9727AC6FCD64__INCLUDED_

#include "export.h"
#include "Snap.h"
#include "Point.h"

namespace dlhml{
class Draw_Entity;
class OBJECT_API Paint_Snap  
{
public:
	Paint_Snap();
	~Paint_Snap();

	void set_zero()					{current_.zero();}

	void set_snap(Snap::Flag flag){
		current_.zero();
		current_.add_flag(flag);
	}

	void paint_snap(Draw_Entity& out,const Point& snap,Float len){
    if(!ondraw_){
		  draw_snap(out,len);
    }
		old_ = current_;
		pt_ = snap;
		draw_snap(out,len);
    if(ondraw_){
      ondraw_ = false;
    }
	}

	void draw_snap(Draw_Entity& out,Float len);
private:

private:
	Snap old_;
	Snap current_;
	Point pt_;
public:
  void ondraw(){ondraw_ = true;}
private:
  bool ondraw_;
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_PAINT_SNAP_H__195F2231_473A_4553_A6B9_9727AC6FCD64__INCLUDED_)
