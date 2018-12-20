// Edit_Cut_Section.h: interface for the Edit_Cut_Section class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_EDIT_CUT_SECTION_H__0145ECB3_7DF9_476B_B678_A11886EA5583__INCLUDED_
#define AFX_EDIT_CUT_SECTION_H__0145ECB3_7DF9_476B_B678_A11886EA5583__INCLUDED_

#include "Create_Entity.h"

namespace dlhml{
class Cut_Section;
class Edit_Cut_Section : public Create_Entity  
{
public:
	Edit_Cut_Section(Scene& scene,Cut_Section& cut);
	virtual ~Edit_Cut_Section();
	void close();

private:
	void mouse_move_p(UINT nFlags, const Point& pt);
	void left_button_down_p(UINT nFlags, const Point& pt);
	void right_button_up_p(UINT nFlags, const Point& pt);
	void key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags);

	void left_button_dblclk_p(UINT nFlags, const Point& pt);

	//重绘红框
	void mouse_wheel_p(UINT nFlags, short zDelta, const Point& pt);

	void xor_draw_p(Draw_Entity& paint);

	bool execute_p();
	bool unexecute_p();
	void delete_execute_p();
	void delete_unexecute_p();

	void paint_selected();
	void get_rect(const Point& pt,Rect& rc);

	void drag_cut_section();

private:
	//功能：得到当前点的在某条线上的垂足
	Point get_pedal_pt_to_line(const Point& ptCur,const Point& ptStart,const Point& ptEnd);
	void delete_txt_in_cut_section();
	void delete_cut_sign();
private:
	bool drag_start_;
	bool drag_end_;

	Point cur_;			//鼠标当前位置

	Point moved_pt_;
	bool del_;

	Cut_Section& cut_section_;
	Entity_ID id_new_;
	void delete_text(LPCTSTR content);

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_EDIT_CUT_SECTION_H__0145ECB3_7DF9_476B_B678_A11886EA5583__INCLUDED_)
