// Cmd_Draw_Middle.h: interface for the Cmd_Draw_Middle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_DRAW_MIDDLE_H__CDDBC8DE_0D94_4916_8BF8_5B5209213E3E__INCLUDED_)
#define AFX_CMD_DRAW_MIDDLE_H__CDDBC8DE_0D94_4916_8BF8_5B5209213E3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Create_Entity.h"
#include "Mgr_Dxfs.h"

class Cmd_Draw_Middle : public dlhml::Create_Entity  
{
public:
	Cmd_Draw_Middle(dlhml::Scene& scene);
	virtual ~Cmd_Draw_Middle();
private:
	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void right_button_down_p(UINT nFlags, const dlhml::Point& pt);

private:
	std::vector<dlhml::Point> pts_;
	std::vector<dlhml::Entity_ID> temp_ids_;
 
	void draw_mid_point();

	void deal_lines_pt(Entitys &lines);
	void deal_arrow_lines_pt(Entitys &arrow_lines);
	void add_pt(const dlhml::Point &pt);
	void draw_corss(const dlhml::Point &pt);
	void clear_temp_lines();


//***选中辅助功能代码***************************************************************
private:
	Entitys sel_ents_;
	void mouse_move_p(UINT nFlags, const dlhml::Point& pt);
	void get_select_ents(Entitys &ents) ;
	void xor_select_rect();
	void select_point();
//***选中辅助功能代码***************************************************************

};

#endif // !defined(AFX_CMD_DRAW_MIDDLE_H__CDDBC8DE_0D94_4916_8BF8_5B5209213E3E__INCLUDED_)
