// Select_Font.cpp: implementation of the Select_Font class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Select_Font.h"
#include "Painter.h"
#include "Text.h"
#include "Text_Style.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Select_Font::Select_Font(Painter& painter,const Text& text,const Text_Style* ts)
:painter_(painter)
MCT_INIT2("Select_Font")
{
	if(NULL == ts){				//ÎÞ×ÖÐÍ
		font_ = Text_Style::get_null_font(text);
		old_color_ = painter_.set_text_color(RGB(102,127,204));
	}else{
		font_ = ts->get_font(text);
		old_color_ = painter_.set_text_color(text.color());
	}
	old_font_ = painter_.select_font(font_);
}

Select_Font::~Select_Font()
{
	painter_.select_font(old_font_);
	::DeleteObject(font_);
	painter_.set_text_color(old_color_);
}
}
