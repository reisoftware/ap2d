// Select_Font.h: interface for the Select_Font class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SELECT_FONT_H__AAD2DB81_C1D3_4616_9CAB_8EBCEF42A1D6__INCLUDED_
#define AFX_SELECT_FONT_H__AAD2DB81_C1D3_4616_9CAB_8EBCEF42A1D6__INCLUDED_

#include "display_export.h"

namespace dlhml{
class Painter;
class Text;
class Text_Style;
class Select_Font  
{
public:
	Select_Font(Painter& painter,const Text& text,const Text_Style* ts);
	~Select_Font();

private:
	Painter& painter_;

	HFONT font_;
	HFONT old_font_;

	COLORREF old_color_;
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_SELECT_FONT_H__AAD2DB81_C1D3_4616_9CAB_8EBCEF42A1D6__INCLUDED_)
