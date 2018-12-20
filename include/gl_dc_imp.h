// GlDc.h: interface for the GlDc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLDC_H__133CDC37_6886_4C1C_94FB_696A15E3838E__INCLUDED_)
#define AFX_GLDC_H__133CDC37_6886_4C1C_94FB_696A15E3838E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <gl/gl.h>
#include <gl/glu.h>
#include <exception>
class CModel;
namespace gelib{

const int FONTLISTBASE = 1000;

class Win_Dc
{
	HDC hdc_;
	HWND hWnd_;
public:
	explicit Win_Dc(HWND hWnd):hWnd_(hWnd) {hdc_ = GetDC(hWnd);}
	~Win_Dc()  {ReleaseDC(hWnd_,hdc_);}
	operator HDC() { return hdc_; }

};

class Gl_Dc_Imp  
{
public:
	Gl_Dc_Imp& operator<<(char* s);
public:
	explicit Gl_Dc_Imp(HWND hWnd,CModel& model);
	~Gl_Dc_Imp() { wglDeleteContext(hrc_); }

	void set_main_gl(CModel& model);
	void attach(HWND hWnd) { 
		HDC hdc = GetDC(hWnd);
		wglMakeCurrent(hdc,hrc_);
	}
	void detach(HWND hWnd) {
		HDC hdc = wglGetCurrentDC();
		wglMakeCurrent(NULL,NULL);
		ReleaseDC(hWnd,hdc);
	}

	class Gl_Exception:public std::exception{
		const char* str_;
		public:
			Gl_Exception(const char* str):str_(str) {}
			const char* what() const {return str_;}
		};
private:
	HGLRC hrc_;
//	static HGLRC main_hrc_;
private:
	bool set_window_pixel_format(HDC hDC);
	bool create_gl_dc(HDC hDC);
};
}
#endif // !defined(AFX_GLDC_H__133CDC37_6886_4C1C_94FB_696A15E3838E__INCLUDED_)
