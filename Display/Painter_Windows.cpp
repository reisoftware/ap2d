
#include "stdafx.h"
#include "Painter_Windows.h"
#include "Point.h"
#include "Matrix_d.h"

#include <cassert>

#include <stdio.h>

#pragma warning (disable : 4244)

namespace dlhml{

Painter_Windows::Painter_Windows(HWND wnd)
:wnd_(wnd)
MCT_INIT2("Painter_Windows")
{
  dc_ = ::GetDC(wnd_);
  ::SetBkMode(dc_,TRANSPARENT);
  
  memory_ = false;
  
}
Painter_Windows::~Painter_Windows()
{
  ::ReleaseDC(wnd_,dc_);
}
void Painter_Windows::close()
{
  delete this;
}
void Painter_Windows::dptolp(POINT* pt) const
{
  ::DPtoLP(dc_,pt,1);
}
void Painter_Windows::attach_dc(HDC dc)
{
  ::ReleaseDC(wnd_,dc_);
  dc_ = dc;
}
void Painter_Windows::set_memory_dc(COLORREF bkcol,const Matrix& mat)
{
  RECT rect_;
  ::GetClientRect(wnd_,&rect_);
  /**/
  memdc_ = ::CreateCompatibleDC(NULL);
  bitmap_ = ::CreateCompatibleBitmap(dc_,rect_.right-rect_.left,
    rect_.bottom-rect_.top);
  oldBmp_ = (HBITMAP)::SelectObject(memdc_,bitmap_);
  ::SetBkColor(memdc_, bkcol);
  //::SetBkMode(memdc_,TRANSPARENT);
  ::ExtTextOut(memdc_, 0, 0, ETO_OPAQUE, &rect_, NULL, 0, NULL);
  memory_ = true;
  
  if(!memory_){
    ::SetBkColor(dc_, bkcol);
    ::ExtTextOut(dc_, 0, 0, ETO_OPAQUE, &rect_, NULL, 0, NULL);
  }
  
}
void Painter_Windows::display_memory()
{
  if(!memory_)
    return;
  RECT rect_;
  ::GetClientRect(wnd_,&rect_);
  int width = rect_.right-rect_.left;
  int height = rect_.bottom-rect_.top;
  ::BitBlt(dc_,0,0,width,height,memdc_,0,0,SRCCOPY);
  
  ::SelectObject(memdc_,oldBmp_);
  ::DeleteObject(bitmap_);
  ::DeleteDC(memdc_);
  
  memory_ = false;
}
HPEN Painter_Windows::select_pen(HPEN pen)
{
  if(memory_)
    return (HPEN)::SelectObject(memdc_,pen);
  else
    return (HPEN)::SelectObject(dc_,pen);
}
HFONT Painter_Windows::select_font(HFONT font)
{
  if(memory_)
    return (HFONT)::SelectObject(memdc_,font);
  else
    return (HFONT)::SelectObject(dc_,font);
}
COLORREF Painter_Windows::set_text_color(COLORREF col)
{
  if(memory_)
    return ::SetTextColor(memdc_,col);
  else
    return ::SetTextColor(dc_,col);
}
HDC Painter_Windows::current()
{
  if(memory_)
    return memdc_;
  else
    return dc_;
}
void Painter_Windows::line(const Point& st,const Point& ed)
{
  HDC dc = current();
  
  ::MoveToEx(dc,static_cast<int>(st.x),static_cast<int>(st.y),NULL);
  ::LineTo(dc,static_cast<int>(ed.x),static_cast<int>(ed.y));
  
}
void Painter_Windows::xor_line(const Point& st,const Point& ed)
{
  HDC dc = current();
	assert(dc && "Painter_Windows::xor_line");
  
  int old = ::SetROP2(dc,R2_XORPEN);
  ::MoveToEx(dc,static_cast<int>(st.x),static_cast<int>(st.y),NULL);
  ::LineTo(dc,static_cast<int>(ed.x),static_cast<int>(ed.y));
  ::SetROP2(dc,old);
}
void Painter_Windows::fill_rect(const Rect& rc, COLORREF cr)
{
  HDC dc = current();
  
  HBRUSH brush = ::CreateSolidBrush(cr);
  RECT myrc = rc;
  ::FillRect(dc, &myrc, brush);
  //::MoveToEx(dc,static_cast<int>(st.x),static_cast<int>(st.y),NULL);
  //::LineTo(dc,static_cast<int>(ed.x),static_cast<int>(ed.y));
  
}
void Painter_Windows::xor_fill_rect(const Rect& rc, COLORREF cr)
{
  HDC dc = current();
  
  int old = ::SetROP2(dc,R2_XORPEN);
  HBRUSH brush = ::CreateSolidBrush(cr);
  RECT myrc = rc;
  ::FillRect(dc, &myrc, brush);
  //	::MoveToEx(dc,static_cast<int>(st.x),static_cast<int>(st.y),NULL);
  //	::LineTo(dc,static_cast<int>(ed.x),static_cast<int>(ed.y));
  ::SetROP2(dc,old);
}

void Painter_Windows::textout(const Point& pos, LPCTSTR cont, COLORREF cr, bool highlight)
{
  HDC dc = current();
  int old_mode = 0;
  COLORREF old_color = RGB(0,0,0);
  if(highlight){
    old_mode = ::SetBkMode(dc,OPAQUE);
    old_color= ::SetBkColor(dc, cr);
  }else{
    old_mode = ::SetBkMode(dc,TRANSPARENT);
  }
  ::TextOut(dc,static_cast<int>(pos.x),static_cast<int>(pos.y),cont,::lstrlen(cont));
  ::SetBkMode(dc,old_mode);
  ::SetBkColor(dc, old_color);
}

void Painter_Windows::xor_textout(const Point& pos,LPCTSTR cont)
{
  HDC dc = current();
  //get text rect
  SIZE sz;
  ::GetTextExtentPoint32(dc,cont,lstrlen(cont),&sz);
  int length = static_cast<int>(sqrt(sz.cx*sz.cx+sz.cy*sz.cy));
  //get font
  HFONT srcfont = (HFONT)::SelectObject(dc,(HFONT)::GetStockObject(DEFAULT_GUI_FONT));
  //get color
  COLORREF srccol = ::SetTextColor(dc,RGB(255,0,0));
  //create dc,bmp
  HDC memdc = ::CreateCompatibleDC(NULL);
  HBITMAP bitmap = ::CreateCompatibleBitmap(dc,length*2,length*2);
  HBITMAP oldBmp = (HBITMAP)::SelectObject(memdc,bitmap);
  //select font
  HFONT oldFont = (HFONT)::SelectObject(memdc,srcfont);
  //select color
  COLORREF oldCol = ::SetTextColor(memdc,srccol);
  //text out
  int old = ::SetBkMode(memdc,TRANSPARENT);
//   int old = 0;
//   if(highlight){
//     old = ::SetBkMode(dc,OPAQUE);
//   }else{
//     old = ::SetBkMode(dc,TRANSPARENT);
//   }
  ::TextOut(memdc,length,length,cont,::lstrlen(cont));
  ::SetBkMode(memdc,old);
  //select old color
  ::SetTextColor(memdc,oldCol);
  //select old font
  ::SelectObject(memdc,oldFont);
  //xor draw text
  ::BitBlt(dc,static_cast<int>(pos.x-length),static_cast<int>(pos.y-length),
    length*2, length*2, memdc, 0, 0, /*SRCCOPY*/SRCINVERT);
  //delete bmp,dc
  ::SelectObject(memdc,oldBmp);
  ::DeleteObject(bitmap);
  ::DeleteDC(memdc);
  //reset color
  ::SetTextColor(dc,srccol);
  //reset font
  ::SelectObject(dc,srcfont);
  
}
void Painter_Windows::graystring(const Point& pos,LPCTSTR cont,COLORREF col)
{
  HDC dc = current();
  int old = ::SetBkMode(dc,TRANSPARENT);
  //int old = ::SetBkMode(dc,OPAQUE);
  //HBRUSH brush = ::CreateHatchBrush(HS_CROSS,col);
  HBRUSH brush = ::CreateSolidBrush(col);
  ::GrayString(dc,brush,NULL,(LPARAM)cont,::lstrlen(cont),
    static_cast<int>(pos.x),static_cast<int>(pos.y),0,0);
  ::DeleteObject(brush);
  ::SetBkMode(dc,old);
}

void Painter_Windows::ellipse(double left,double top,double right,double bottom,bool fill)
{
  HDC dc = current();
  HBRUSH old = 0;
  if(!fill)
    old = (HBRUSH)::SelectObject(dc,::GetStockObject(NULL_BRUSH));
  ::Ellipse(dc,static_cast<int>(left),static_cast<int>(top),
    static_cast<int>(right),static_cast<int>(bottom));
  if(!fill)
    ::SelectObject(dc,old);
}
void Painter_Windows::xor_ellipse(double left,double top,double right,double bottom,bool fill)
{
  HDC dc = current();
  int old = ::SetROP2(dc,R2_XORPEN);
  HBRUSH oldbrh = 0;
  if(!fill)
    oldbrh = (HBRUSH)::SelectObject(dc,::GetStockObject(NULL_BRUSH));
  ::Ellipse(dc,static_cast<int>(left),static_cast<int>(top),
    static_cast<int>(right),static_cast<int>(bottom));
  if(!fill)
    ::SelectObject(dc,oldbrh);
  ::SetROP2(dc,old);
}
void Painter_Windows::angle_arc(double x,double y,double r,double startangle,double sweepangle)
{
  HDC dc = current();
  
  const float RADIAN = 3.1415926f/180.0f;
  ::MoveToEx(dc,static_cast<int>(x+r*cos(startangle*RADIAN)),
    static_cast<int>(y-r*sin(startangle*RADIAN)),NULL);
  ::AngleArc(dc,static_cast<int>(x),static_cast<int>(y),static_cast<DWORD>(r),
    static_cast<FLOAT>(startangle),static_cast<FLOAT>(sweepangle));
  
}
void Painter_Windows::xor_angle_arc(double x,double y,double r,double startangle,double sweepangle)
{
  HDC dc = current();
  int old = ::SetROP2(dc,R2_XORPEN);
  const float RADIAN = 3.1415926f/180.0f;
  ::MoveToEx(dc,static_cast<int>(x+r*cos(startangle*RADIAN)),
    static_cast<int>(y-r*sin(startangle*RADIAN)),NULL);
  ::AngleArc(dc,static_cast<int>(x),static_cast<int>(y),static_cast<DWORD>(r),
    static_cast<FLOAT>(startangle),static_cast<FLOAT>(sweepangle));
  ::SetROP2(dc,old);
}
void Painter_Windows::xor_arc(const Point& lt,const Point& rb,const Point& st,const Point& ed)
{
  HDC dc = current();
  int old = ::SetROP2(dc,R2_XORPEN);
  ::Arc(dc,static_cast<int>(lt.x),static_cast<int>(lt.y),static_cast<int>(rb.x),
    static_cast<int>(rb.y),static_cast<int>(st.x),static_cast<int>(st.y),
    static_cast<int>(ed.x),static_cast<int>(ed.y));
  ::SetROP2(dc,old);
}

void Painter_Windows::get_client_rect(LPRECT rc)
{
  ::GetClientRect(wnd_, rc);
}



}//namespace
