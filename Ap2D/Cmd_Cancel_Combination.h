// Cmd_Cancel_Combination.h: interface for the Cmd_Cancel_Combination class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Cmd_Cancel_Combination_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_)
#define AFX_Cmd_Cancel_Combination_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Create_Entity.h"
#include "Mgr_Dxfs.h"

class Cmd_Cancel_Combination : public dlhml::Create_Entity  
{
public:
	Cmd_Cancel_Combination(dlhml::Scene& scene);
	virtual ~Cmd_Cancel_Combination();
private:
	void mouse_move_p(UINT nFlags, const dlhml::Point& pt);
	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void right_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void xor_select_rect();
	void select_entity();

	Entitys sel_ents_;


};

#endif // !defined(AFX_CMD_DRAW_CENTER_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_)
