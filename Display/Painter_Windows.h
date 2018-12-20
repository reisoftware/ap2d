
#ifndef _TIAN_DISPLAY_PAINTER_WINDOWS_H_
#define _TIAN_DISPLAY_PAINTER_WINDOWS_H_

#include "Painter.h"

namespace dlhml{
  
  class Rect;
  
  class DISPLAY_API Painter_Windows : public Painter
  {
  public:
    Painter_Windows(HWND wnd);
    virtual ~Painter_Windows();
    
    void attach_dc(HDC dc);
    
    void close();
    
    void dptolp(POINT* pt) const;
    
    void set_memory_dc(COLORREF bkcol,const Matrix& mat);
    void display_memory();
    
    HPEN select_pen(HPEN pen);
    HFONT select_font(HFONT font);
    COLORREF set_text_color(COLORREF col);
    
    void line(const Point& st,const Point& ed);
    void xor_line(const Point& st,const Point& ed);
    void fill_rect(const Rect& rc, COLORREF cr);
    void xor_fill_rect(const Rect& rc, COLORREF cr);
    
    void textout(const Point& pos, LPCTSTR cont, COLORREF cr, bool highlight);
    void xor_textout(const Point& pos,LPCTSTR cont);
    void graystring(const Point& pos,LPCTSTR cont,COLORREF col);
    
    void ellipse(double left,double top,double right,double bottom,bool fill=false);
    void xor_ellipse(double left,double top,double right,double bottom,bool fill=false);
    
    void angle_arc(double x,double y,double r,double startangle,double sweepangle);
    void xor_angle_arc(double x,double y,double r,double startangle,double sweepangle);
    void xor_arc(const Point& lt,const Point& rb,const Point& st,const Point& ed);
    

    virtual void get_client_rect(LPRECT rect);


  private:
    HWND wnd_;
    HDC dc_;
    
    bool memory_;
    HDC memdc_;
    HBITMAP bitmap_;
    HBITMAP oldBmp_;
    
    HDC current();
    
		
	private:
		MCT_DEF
	};
}
#endif // !defined(AFX_PAINTER_WINDOWS_H__A1CDE877_55EF_40CC_A234_59509815A0B2__INCLUDED_)
