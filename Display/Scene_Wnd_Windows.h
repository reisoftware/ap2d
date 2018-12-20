// Scene_Wnd_Windows.h: interface for the Scene_Wnd_Windows class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SCENE_WND_WINDOWS_H__48FAECAF_DE2F_4354_B88E_592F47CDA09A__INCLUDED_
#define AFX_SCENE_WND_WINDOWS_H__48FAECAF_DE2F_4354_B88E_592F47CDA09A__INCLUDED_

#include "Scene_Wnd.h"

namespace dlhml{
class DISPLAY_API Scene_Wnd_Windows : public Scene_Wnd
{
public:
	Scene_Wnd_Windows(HWND wnd);
	virtual ~Scene_Wnd_Windows();

	static Scene_Wnd* create_me(HWND wnd);
	void close();

	void invalidate();
	void invalidate_rect(RECT rc);
	Rect client_rect();

	Painter* get_painter();

private:
	HWND wnd_;
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_SCENE_WND_WINDOWS_H__48FAECAF_DE2F_4354_B88E_592F47CDA09A__INCLUDED_)
