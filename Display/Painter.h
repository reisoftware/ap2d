// Painter.h: interface for the Painter class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_PAINTER_H__E67AD16A_4C52_4659_AA91_0E4B88B3F52C__INCLUDED_
#define AFX_PAINTER_H__E67AD16A_4C52_4659_AA91_0E4B88B3F52C__INCLUDED_

#include "display_export.h"

namespace dlhml{
class Point;
class Rect;
class Matrix;
class DISPLAY_API Painter  
{
public:
	Painter();
	virtual ~Painter();

	virtual void close() = 0;

	virtual void dptolp(POINT* pt) const = 0;

	virtual void set_memory_dc(COLORREF bkcol,const Matrix& mat) = 0;
	virtual void display_memory() = 0;

	virtual HPEN select_pen(HPEN pen) = 0;
	virtual HFONT select_font(HFONT font) = 0;
	virtual COLORREF set_text_color(COLORREF col) = 0;

	virtual void line(const Point& st,const Point& ed) = 0;
	virtual void xor_line(const Point& st,const Point& ed) = 0;

  virtual void fill_rect(const Rect& rc, COLORREF cr)=0;
  virtual void xor_fill_rect(const Rect& rc, COLORREF cr)=0;

	virtual void textout(const Point& pos,LPCTSTR cont, COLORREF cr, bool highlight) = 0;
	virtual void xor_textout(const Point& pos,LPCTSTR cont) = 0;
	virtual void graystring(const Point& pos,LPCTSTR cont,COLORREF col) = 0;

	virtual void ellipse(double left,double top,double right,double bottom,bool fill=false) = 0;
	virtual void xor_ellipse(double left,double top,double right,double bottom,bool fill=false) = 0;

	virtual void angle_arc(double x,double y,double r,double startangle,double sweepangle) = 0;
	virtual void xor_angle_arc(double x,double y,double r,double startangle,double sweepangle) = 0;
	virtual void xor_arc(const Point& lt,const Point& rb,const Point& st,const Point& ed) = 0;
	
  virtual void get_client_rect(LPRECT rect)=0;

private:
	MCT_DEF
};
}
#endif // !defined(AFX_PAINTER_H__E67AD16A_4C52_4659_AA91_0E4B88B3F52C__INCLUDED_)
