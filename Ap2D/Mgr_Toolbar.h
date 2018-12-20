// Mgr_Toolbar.h: interface for the Mgr_Toolbar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBAR_MGR_H__940E26BE_D4EC_4D70_8434_FC1ED62A1D2D__INCLUDED_)
#define AFX_TOOLBAR_MGR_H__940E26BE_D4EC_4D70_8434_FC1ED62A1D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include "Scene_d.h"

typedef std::pair<UINT,CString> Cmd;
class Mgr_Toolbar  
{
public:
	Mgr_Toolbar();
	virtual ~Mgr_Toolbar();


	std::vector<Cmd> snap_;
	std::vector<Cmd> create_;
	std::vector<Cmd> edit_;
	std::vector<Cmd> layer_;

	std::vector<Cmd> layer_combo_;
	void check_all_toolbar();
	void check_all_toolbar_no_snap();
	
	void check_snap_toolbar(UINT id,CToolBar& bar_cmd);
	void check_create_toolbar(UINT id,CToolBar& bar_cmd);
	void check_edit_toolbar(UINT id,CToolBar& bar_cmd);
	void check_layer_toolbar(UINT id,CToolBar& bar_cmd);
	void check_combo_toolbar(UINT id,CToolBar& bar_cmd);

private:
	void init_snap_bar_ids();
	void init_create_bar_ids();
	void init_edit_bar_ids();
	void init_layer_bar_ids();
	void init_layer_combo_bar_ids();

};
bool is_check(CToolBar& bar, std::vector<Cmd> ids, UINT id);
void check(CToolBar& bar, std::vector<Cmd> ids, UINT id, bool bCheck);
void snap_style(dlhml::Scene& scene, dlhml::Snap::Flag snapStyle, BOOL bSnap);
void snap_all(dlhml::Scene& scene, CToolBar& bar, std::vector<Cmd> ids, bool bsnap);

#endif // !defined(AFX_TOOLBAR_MGR_H__940E26BE_D4EC_4D70_8434_FC1ED62A1D2D__INCLUDED_)
