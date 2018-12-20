// Cmd_Check_Text.h: interface for the Cmd_Check_Text class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_CHECK_TEXT_H__027F8298_2CBA_41E5_AA46_FC7112324E90__INCLUDED_)
#define AFX_CMD_CHECK_TEXT_H__027F8298_2CBA_41E5_AA46_FC7112324E90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Create_Entity.h"
#include "Mgr_Dxfs.h"

class Cmd_Check_Text  : public dlhml::Create_Entity 
{
public:
	Cmd_Check_Text(dlhml::Scene& scene);
	virtual ~Cmd_Check_Text();

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

};

#endif // !defined(AFX_CMD_CHECK_TEXT_H__027F8298_2CBA_41E5_AA46_FC7112324E90__INCLUDED_)
