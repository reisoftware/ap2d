// Cmd_Select_Joint.h: interface for the Cmd_Select_Joint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_SELECT_JOINT_H__A9029A88_29FE_40A9_AFC2_7936BF56C14D__INCLUDED_)
#define AFX_CMD_SELECT_JOINT_H__A9029A88_29FE_40A9_AFC2_7936BF56C14D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Create_Entity.h"
#include "Mgr_Dxfs.h"
#include "Line_Arrow.h"
#include "Dlg_Joint_DB.h"

class Cmd_Select_Joint : public dlhml::Create_Entity   
{
public:
	Cmd_Select_Joint(dlhml::Scene& scene);
	virtual ~Cmd_Select_Joint();
	BOOL status_;
	//Dlg_Joint_DB *dlg;
	Dlg_Joint_DB *dlg;
	BOOL get_message();

private:
	void mouse_move_p(UINT nFlags, const dlhml::Point& pt);
	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);

	void xor_select_rect();
	Entitys sel_ents_;
	void get_select_ents(Entitys &ents);

	void show_joint_info(Entitys &texts);

};

#endif // !defined(AFX_CMD_SELECT_JOINT_H__A9029A88_29FE_40A9_AFC2_7936BF56C14D__INCLUDED_)
