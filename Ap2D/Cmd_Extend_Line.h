// Cmd_Extend_Line.h: interface for the Cmd_Extend_Line class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_EXTEND_LINE_H__16CD6AE4_BB5A_4A2F_888D_439CCD95CAD3__INCLUDED_)
#define AFX_CMD_EXTEND_LINE_H__16CD6AE4_BB5A_4A2F_888D_439CCD95CAD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Create_Entity.h"
#include "Mgr_Dxfs.h"
#include "Line_Arrow.h"

class Cmd_Extend_Line : public dlhml::Create_Entity  
{
	
public:
	Cmd_Extend_Line(dlhml::Scene& scene);
	virtual ~Cmd_Extend_Line();

private:
	void xor_select_rect();
	Entitys sel_ents_;
	void get_select_ents(Entitys &ents) ;
	
	void mouse_move_p(UINT nFlags, const dlhml::Point& pt);
	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void right_button_down_p(UINT nFlags, const dlhml::Point& pt);

	void create_extend_lines();
	void intersect_lines(dlhml::Line *ln,std::vector<dlhml::Point> &pts);
	void draw_pts(const std::vector<dlhml::Point> &pts);

	
	dlhml::EntityIDArray ids_;

};

#endif // !defined(AFX_CMD_EXTEND_LINE_H__16CD6AE4_BB5A_4A2F_888D_439CCD95CAD3__INCLUDED_)
