// Edit_Rectentity.h: interface for the Edit_Rectentity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDIT_RECTENTITY_H__9CEF36F6_78C7_4184_88C2_1137E83B0BFE__INCLUDED_)
#define AFX_EDIT_RECTENTITY_H__9CEF36F6_78C7_4184_88C2_1137E83B0BFE__INCLUDED_
/*

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Create_Entity.h"
#include <utility>
#include "Rect.h"
namespace dlhml{
class Rectentity;
#ifndef DISPLAYBHX_EXPORTS
class Edit_Rectentity : public Create_Entity  
#else
class DISPLAY_API Edit_Rectentity : public Create_Entity  
#endif
{
public:
	Edit_Rectentity(Scene& scene,Rectentity& rectEnt);
	virtual ~Edit_Rectentity();
	void close(){delete this;}
private:
	void mouse_move_p(UINT nFlags, const Point& pt);
	void left_button_down_p(UINT nFlags, const Point& pt);
	void right_button_up_p(UINT nFlags, const Point& pt);
	void key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags);

	void left_button_dblclk_p(UINT nFlags, const Point& pt);

private:
	void xor_draw_p(Draw_Entity& paint);
	bool execute_p();
	bool unexecute_p();
private:
	void paint_selected();
	void get_rect(const Point& pt,Rect& rc);
	void drag_rect();
	void get_rect_four_pts(const Rect& rect,Point& lb_pt,Point& lt_pt,Point& rt_pt,Point& rb_pt);
	void xor_draw_rect_four_pts(const Rectentity& rectEnt,Draw_Entity& paint);
	Rect get_new_rect(const Rect& rectOld,const Point& ptMove);

	inline void init_flag(){b_drag_lb_ = false; b_drag_lt_ = false;
	b_drag_rb_ = false; b_drag_rt_ = false;
	}
private:
	Rectentity& rectEnt_;

	Point cur_;			//鼠标当前位置
//	typedef std::pair<Point,Point> crpair;
//	crpair pt2_;  	   //for redo create data 
//	Point moved_pt_;
	Rect moved_rect_;
	Point moved_pt_;
	bool b_drag_lb_;
	bool b_drag_lt_;
	bool b_drag_rt_;
	bool b_drag_rb_;
};
}
*/
#endif // !defined(AFX_EDIT_RECTENTITY_H__9CEF36F6_78C7_4184_88C2_1137E83B0BFE__INCLUDED_)
