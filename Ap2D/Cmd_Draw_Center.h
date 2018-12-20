// Cmd_Draw_Center.h: interface for the Cmd_Draw_Center class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_DRAW_CENTER_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_)
#define AFX_CMD_DRAW_CENTER_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Create_Entity.h"
#include "Mgr_Dxfs.h"

class Cmd_Draw_Center : public dlhml::Create_Entity  
{
public:
	Cmd_Draw_Center(dlhml::Scene& scene);
	virtual ~Cmd_Draw_Center();
private:
	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void right_button_down_p(UINT nFlags, const dlhml::Point& pt);

private:
	std::vector<dlhml::Point> pts_;
	std::vector<dlhml::Entity_ID> temp_ids_;
 
	void draw_center_point();

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

#endif // !defined(AFX_CMD_DRAW_CENTER_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_)
