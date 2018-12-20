// Cmd_Select_Text.h: interface for the Cmd_Select_Text class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_SELECT_TEXT_H__9AB7C23C_A856_4C93_BD17_575D274C58F1__INCLUDED_)
#define AFX_CMD_SELECT_TEXT_H__9AB7C23C_A856_4C93_BD17_575D274C58F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Create_Entity.h"
#include "Mgr_Dxfs.h"

class Cmd_Select_Text  : public dlhml::Create_Entity 
{
public:
	Cmd_Select_Text(dlhml::Scene& scene);
	virtual ~Cmd_Select_Text();
private:
	void mouse_move_p(UINT nFlags, const dlhml::Point& pt);
	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void right_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags);
	void left_button_dblclk_p(UINT nFlags, const dlhml::Point& pt);
	void xor_select_rect();
	void select_entity();

  void middle_button_down_p(UINT nFlags, const dlhml::Point& pt);

	
	Entitys sel_ents_;
	void get_select_ents(Entitys &ents);  
	void change_error();

};

#endif // !defined(AFX_CMD_SELECT_TEXT_H__9AB7C23C_A856_4C93_BD17_575D274C58F1__INCLUDED_)
