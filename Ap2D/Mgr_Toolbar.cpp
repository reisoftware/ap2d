// Mgr_Toolbar.cpp: implementation of the Mgr_Toolbar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Mgr_Toolbar.h"
#include "resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
static int BAR_LINE = -1;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Toolbar::Mgr_Toolbar()
{
	init_snap_bar_ids();
	init_create_bar_ids();
	init_edit_bar_ids();
	init_layer_bar_ids();

	init_layer_combo_bar_ids();
	

}

Mgr_Toolbar::~Mgr_Toolbar()
{

}


void Mgr_Toolbar::init_snap_bar_ids()
{	
	std::vector<Cmd>& ids = snap_;
	ids.clear();
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_ORTHO, "Ortho"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SANP_END_PT, "Snap End Pt"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SANP_CROSS_PT, "Snap Cross Pt"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SANP_LINE_PT, "Snap Line Pt"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SANP_MID_PT, "Snap Mid Pt"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SANP_PERPENDICULAR, "Snap Perpendicular"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SNAP_CIRCLE_PT, "Snap Circle Pt"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SANP_PT, "Snap Pt"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SANP_ALL, "Snap All"));
}
void Mgr_Toolbar::init_layer_bar_ids()
{	
	std::vector<Cmd>& ids = layer_;
	ids.clear();
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYER_PART, "Layer Part"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYER_SHEET, "Layer Sheet"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYER_CUT, "Layer Part"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYER_VIEW, "Layer View"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYER_DIM, "Layer Dim"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYER_MARK, "Layer Mart"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYER_APDIM, "Layer Apdim"));
}
void Mgr_Toolbar::init_layer_combo_bar_ids()
{	
	std::vector<Cmd>& ids = layer_combo_;
	ids.clear();
	ids.push_back(std::make_pair<UINT,CString>(ID_TOOL_COMBO, "Layer Name"));
	ids.push_back(std::make_pair<UINT,CString>(ID_TOOL_SHOW_LAYER_P, "Layer Show"));
	ids.push_back(std::make_pair<UINT,CString>(ID_TOOL_LOCK_LAYER_P, "Layer Lock"));
	ids.push_back(std::make_pair<UINT,CString>(ID_TOOL_SELECT_P, "Select Ents"));
	ids.push_back(std::make_pair<UINT,CString>(BAR_LINE, ""));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_ONE_IN_P, "Diff dxfs"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_CREATE_REPORT_P, "Create Report"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SELECT_TEXT_P, "Select Text"));
	ids.push_back(std::make_pair<UINT,CString>(BAR_LINE, ""));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_REVERSE_COLOR_P, "Reverse Color"));

}
void Mgr_Toolbar::init_create_bar_ids()
{
	std::vector<Cmd>& ids = create_;
	ids.clear();
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LINE, "Create Line Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_CIRCLE_P, "Create Arc Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_ARC_P, "Create Break Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SPLINE, "Create Section"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_RECT, "Create Plate"));
	ids.push_back(std::make_pair<UINT,CString>(BAR_LINE, ""));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_POLYGON, "Create Plate Stand"));
//	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_INSERT_BLOCK, "Create Plate Stand"));
//	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SAVE_BLOCK, "Create Plate Stand"));
	ids.push_back(std::make_pair<UINT,CString>(BAR_LINE, ""));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_LEAD, "Create Jnt"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_ORTHO_CLOSED, "Auto Create Jnt"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_ALIGN_CLOSED, "Create Assistand Line"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_ALIGN_PILEUP, "Create Circle"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_ORTHO_PILEUP, "Create Axis"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_ANGLE, "Create Block"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_RADIUS, "Set Group"));
	ids.push_back(std::make_pair<UINT,CString>(BAR_LINE, ""));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_MOVE_DIM_LINE, "Dim Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYOUT_DIM_LINE, "Dim Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_ADD_DIM, "Dim Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DEL_DIM, "Dim Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_LAYOUT_DIM_BASE, "Dim Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_RE0, "Dim Steel"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM_TXT_P, "Dim Text"));
}

void Mgr_Toolbar::init_edit_bar_ids()
{
	std::vector<Cmd>& ids = edit_;
	ids.clear();
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_ERASE,"Erase"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_MOVE,"Move"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_COPY,"Copy"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_PASTE,"Paste"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_ARRAY,"Array"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_ROTATE,"Rotate"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_SCALE,"Scale"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_MIRROR,"Mirror"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DECOMPOSE,"Decompose"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_OFFSET,"Offset"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_DIM,"Dim"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_TRIM,"Trim"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_EXTEND,"Extend"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_BREAK_P,"Break"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_MULTIBREAK,"MultiBreak"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_STRETCHES_P,"Stretches"));
	ids.push_back(std::make_pair<UINT,CString>(BAR_LINE,""));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_UNDO,"Undo"));
	ids.push_back(std::make_pair<UINT,CString>(ID_BUT_REDO,"Redo"));
}




int find_pos(const std::vector<Cmd>& cmds, UINT id)
{
	for(int i=0; i<cmds.size(); ++i){
		if(cmds[i].first == id){
			return i;
		}
	}
	return -1;
}
////是否按下
bool is_check(CToolBar& bar, int pos)
{
	//UINT nNewStyle = bar.GetButtonStyle(0) &~ (TBBS_INDETERMINATE);
	UINT nNewStyle = bar.GetButtonStyle(pos);
	UINT aaa = TBBS_CHECKED;
	UINT ccc = TBBS_INDETERMINATE;
	UINT bbb = nNewStyle & TBBS_CHECKED;
	return nNewStyle & TBBS_CHECKED ? true : false;
	//return nNewStyle & TBBS_CHECKED ? false : true;
}
bool is_check(CToolBar& bar, std::vector<Cmd> ids, UINT id)
{
	int pos = find_pos(ids, id);
	if(pos == -1){
		return false;
	}
	return is_check(bar, pos);
}

////设置按下状态
void check(CToolBar& bar, int pos, bool bCheck)
{ 
	//&~ (TBBS_INDETERMINATE)
	UINT nNewStyle = bar.GetButtonStyle(pos) ;
	UINT aaa = TBBS_CHECKED;
	if(bCheck){
		nNewStyle |= TBBS_CHECKED;
	}
	else{
		nNewStyle &= (~TBBS_CHECKED);
	}
	//nNewStyle |= TBBS_CHECKBOX;
	bar.SetButtonStyle(pos, nNewStyle);
}
void check(CToolBar& bar, std::vector<Cmd> ids, UINT id, bool bCheck)
{
	int pos = find_pos(ids, id);
	if(pos == -1){
		return;
	}
	check(bar, pos, bCheck);
}

////反转按下状态
void check(CToolBar& bar, int pos)
{ 
	bool bCheck = is_check(bar, pos);
	check(bar, pos, !bCheck);
}
void check(CToolBar& bar, std::vector<Cmd> ids, UINT id)
{
	int pos = find_pos(ids, id);
	if(pos == -1){
		return;
	}
	check(bar, pos);
}



void snap_style(dlhml::Scene& scene, dlhml::Snap::Flag snapStyle, BOOL bSnap)
{
	
	if(bSnap){
		scene.get_snap_flag()->add_flag(snapStyle);
	}
	else{
		scene.get_snap_flag()->remove_flag(snapStyle);
	}
}
void snap_all(dlhml::Scene& scene, CToolBar& bar, std::vector<Cmd> ids, bool bsnap)
{
	for(int i = 0; i < 8; ++i)
		check(bar, i, bsnap);

	scene.ortho(bsnap);
	snap_style(scene, dlhml::Snap::Endpoint, bsnap);	
	snap_style(scene, dlhml::Snap::Intersect, bsnap);
	snap_style(scene, dlhml::Snap::Nearest, bsnap);
	snap_style(scene, dlhml::Snap::Middle, bsnap);
	snap_style(scene, dlhml::Snap::Perpendicular, bsnap);
	snap_style(scene, dlhml::Snap::Center, bsnap);		
	snap_style(scene, dlhml::Snap::Anypoint, bsnap);
}
////抬起全部
static void checkup_whole_toolbar(CToolBar& bar, const std::vector<Cmd>& ids)
{
	int i=0;
	for(i=0; i<ids.size(); ++i){
		if(ids[i].first != -1){
			check(bar, i, false);
		}
	}
}

void Mgr_Toolbar::check_all_toolbar()
{
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	checkup_whole_toolbar(pM->get_create_bar(), create_);
	checkup_whole_toolbar(pM->get_edit_bar(), edit_);
//	checkup_whole_toolbar(pM->get_snap_bar(), snap_);
	checkup_whole_toolbar(pM->get_layer_bar(), layer_);
	checkup_whole_toolbar(pM->get_combo_layer_bar(), layer_combo_);
}
void Mgr_Toolbar::check_all_toolbar_no_snap()
{
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	checkup_whole_toolbar(pM->get_create_bar(), create_);
	checkup_whole_toolbar(pM->get_edit_bar(), edit_);
	checkup_whole_toolbar(pM->get_edit_bar(), edit_);

}
//
void Mgr_Toolbar::check_snap_toolbar(UINT id,CToolBar& bar_cmd)
{
	check_all_toolbar();
	int pos = find_pos(snap_, id);
	if(pos == BAR_LINE){
		return;
	}
	check(bar_cmd, pos, true);
}
void Mgr_Toolbar::check_create_toolbar(UINT id,CToolBar& bar_cmd)
{
	check_all_toolbar_no_snap();
	int pos = find_pos(create_, id);

	if(pos == BAR_LINE){
		return;
	}
	check(bar_cmd, pos, true);
}
void Mgr_Toolbar::check_edit_toolbar(UINT id,CToolBar& bar_cmd)
{
	check_all_toolbar_no_snap();
	int pos = find_pos(edit_, id);

	if(pos == BAR_LINE){
		return;
	}
	check(bar_cmd, pos, true);
}
void Mgr_Toolbar::check_combo_toolbar(UINT id,CToolBar& bar_cmd)
{
	check_all_toolbar();
	int pos = find_pos(layer_combo_, id);

	if(pos == BAR_LINE){
		return;
	}
	check(bar_cmd, pos, true);
}
