// Create_Dim_Text_Dimension.h: interface for the Create_Dim_Text_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREATE_DIM_TEXT_DIMENSION_H__BCA425A8_DB7D_4A72_9D27_5C223754720E__INCLUDED_)
#define AFX_CREATE_DIM_TEXT_DIMENSION_H__BCA425A8_DB7D_4A72_9D27_5C223754720E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Create_Entity.h"
#include "Entity_ID.h"
#include <string>
#include <vector>

namespace dlhml{
class Text_Dimension;
#ifndef DISPLAYTIAN_EXPORTS
class Create_Dim_Text_Dimension : public Create_Entity  
#else
class DISPLAY_API Create_Dim_Text_Dimension : public Create_Entity  
#endif
{
public:
	Create_Dim_Text_Dimension(Scene& scene);
	virtual ~Create_Dim_Text_Dimension();
	void close(){delete this;}
private:
	void mouse_move_p(UINT nFlags, const Point& pt);
	void left_button_down_p(UINT nFlags, const Point& pt);
	void right_button_up_p(UINT nFlags, const Point& pt);
	void key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags);

	void xor_draw_p(Draw_Entity& paint);
	void add_txt(char* txt);

	bool execute_p();
	bool unexecute_p();
private:
	std::string dim_txt_;
	Text_Dimension* pText_dim_;
	//保证每次只redo一个，需要重新生成命令
	void cmd_start();

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_CREATE_DIM_TEXT_DIMENSION_H__BCA425A8_DB7D_4A72_9D27_5C223754720E__INCLUDED_)
