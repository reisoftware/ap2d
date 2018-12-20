// Scene_Wnd_Windows.cpp: implementation of the Scene_Wnd_Windows class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Scene_Wnd_Windows.h"
#include "Rect.h"
#include "Painter_Windows.h"


////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Scene_Wnd_Windows::Scene_Wnd_Windows(HWND wnd)
:wnd_(wnd)
MCT_INIT2("Scene_Wnd_Windows")
{

}

Scene_Wnd_Windows::~Scene_Wnd_Windows()
{

}
Scene_Wnd* Scene_Wnd_Windows::create_me(HWND wnd)
{
	return new Scene_Wnd_Windows(wnd);
}
void Scene_Wnd_Windows::close()
{
	delete this;
}
void Scene_Wnd_Windows::invalidate()
{
	::InvalidateRect(wnd_,NULL,TRUE);
}
void Scene_Wnd_Windows::invalidate_rect(RECT rc)
{
	::InvalidateRect(wnd_,&rc,TRUE);
}
Rect Scene_Wnd_Windows::client_rect()
{
	RECT rc;
	::GetClientRect(wnd_,&rc);
	return Rect(rc);
}
Painter* Scene_Wnd_Windows::get_painter()
{
//#if defined(USE_GL)
//	return new Painter_Windows_Opengl(wnd_);
//#elif defined(USE_IMAGE)
//	return new Painter_Windows_Image(wnd_);
//#else
//	return new Painter_Windows(wnd_);
//#endif
	return new Painter_Windows(wnd_);

}
}
