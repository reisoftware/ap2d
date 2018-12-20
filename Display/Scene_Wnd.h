// Scene_Wnd.h: interface for the Scene_Wnd class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SCENE_WND_H__E54FA05A_EE4E_4F1D_AB02_89E7540B6805__INCLUDED_
#define AFX_SCENE_WND_H__E54FA05A_EE4E_4F1D_AB02_89E7540B6805__INCLUDED_

#include "display_export.h"

namespace dlhml{
class Rect;
class Painter;
class DISPLAY_API Scene_Wnd  
{
public:
	Scene_Wnd();
	virtual ~Scene_Wnd();

	virtual void close() = 0;

	virtual void invalidate() = 0;
	virtual void invalidate_rect(RECT rc) = 0;
	virtual Rect client_rect() = 0;

	virtual Painter* get_painter() = 0;

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_SCENE_WND_H__E54FA05A_EE4E_4F1D_AB02_89E7540B6805__INCLUDED_)
