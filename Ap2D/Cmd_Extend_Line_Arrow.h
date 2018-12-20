// Cmd_Extend_Line_Arrow_Arrow.h: interface for the Cmd_Extend_Line_Arrow_Arrow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Cmd_Extend_Line_Arrow_ARROW_H__28443FF3_726F_4485_831B_B49A112573D4__INCLUDED_)
#define AFX_Cmd_Extend_Line_Arrow_ARROW_H__28443FF3_726F_4485_831B_B49A112573D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "Create_Entity.h"
#include "Mgr_Dxfs.h"
#include "Line_Arrow.h"

class Cmd_Extend_Line_Arrow : public dlhml::Create_Entity  
{
	
public:
	Cmd_Extend_Line_Arrow(dlhml::Scene& scene);
	virtual ~Cmd_Extend_Line_Arrow();

private:
	void xor_select_rect();
	Entitys sel_ents_;
	void get_select_ents(Entitys &ents) ;
	
	void mouse_move_p(UINT nFlags, const dlhml::Point& pt);
	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void right_button_down_p(UINT nFlags, const dlhml::Point& pt);

	void create_extend_lines();
	void intersect_lines(dlhml::Line_Arrow *ln,std::vector<dlhml::Point> &pts);
	void draw_pts(const std::vector<dlhml::Point> &pts);

	
	dlhml::EntityIDArray ids_;

};




#endif // !defined(AFX_Cmd_Extend_Line_Arrow_ARROW_H__28443FF3_726F_4485_831B_B49A112573D4__INCLUDED_)
