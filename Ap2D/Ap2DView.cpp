// Ap2DView.cpp : implementation of the CAp2DView class
//

#include "stdafx.h"
#include "Ap2D.h"

#include "Ap2DDoc.h"
#include "Ap2DView.h"

#include "Painter_Windows.h"
#include "Scene_Wnd_Windows.h"
#include "DB_View.h"
#include "MainFrm.h"
#include "Command_Line_Info.h"
#include "DB_View.h"
#include "Dxf_Read.h"
#include "Dxf_Save.h"
#include "Global.h"
#include "Array_Cad_Dlg.h"
#include "Text_Dimension.h"

#include "../object/Line_Arrow.h"
#include "../object/Cloud_Line.h"
#include "../object/Circle.h"
#include "../object/Arc_Arrow.h"
#include "Ln_Dim.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Radius_Dimension.h"
#include "angle_Dimension.h"
#include "CreateCmd.h"
#include "Ln_Dim.h"
#include "Mgr_Dxfs.h"
#include "Mgr_Database.h"
#include "Cmd_Select.h"
#include "Dlg_Compare_Dxf.h"

#include "Cmd_Check_Text.h"
#include "Cmd_Select_Text.h"
#include "Mgr_File.h"
#include "Mgr_Entity.h"

#include "../object/Lead_Dimension_Info.h"
#include "Lead_Dimension_Info.h"

#include "Dlg_Dim_Name_Set.h"
#include "Dlg_Select_Name.h"
#include "Dlg_Sign_Replace.h"
#include "Text_Dimension_Info.h"

#include "Ln_Dim_Direct.h"
#include "Dlg_Input.h"
#include "DB_Blocks.h"

#include "Mgr_lua.h"
#include "Mgr_Database.h"
#include "dir.h"
#include "Dlg_Hot_Key.h"
#include "Dlg_Find_Tool.h"
#include "Dlg_Select_Table_Text.h"
#include "Dlg_Joint_DB.h"
#include "Decompose_Entity.h"
#include "Cmd_Draw_Middle.h"
#include "Cmd_Draw_Center.h"
#include "Cmd_Dim_Solpe.h"
#include "Dim_Angle.h"
#include "Lead_Line_Dim.h"

#include <process.h>

#include "ApNet_Check.h"

//#include <vld.h>
#include "hotkey.h"

#include "Dlg_Block_Manage.h"
#include "Ln_Dim_PlateSide.h"
#include "Cmd_Insert_Block.h"
#include "Cmd_Extend_Line.h"
#include "Cmd_Select_Joint.h"
#include "Dlg_Joint_DB_Edit.h"
#include "Dlg_Joint_DB.h"
#include "Dlg_Auto_Check_Main.h"

#include "Dlg_Replace_Material.h"
#include "Dim_Angle_Lean.h"

#include "Dlg_Setting.h"

#include "DimInfo_IO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAp2DView

IMPLEMENT_DYNCREATE(CAp2DView, CView)

BEGIN_MESSAGE_MAP(CAp2DView, CView)
	//{{AFX_MSG_MAP(CAp2DView)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_COMMAND(ID_BUT_DXF_OUT, OnButDxfOut)
	ON_COMMAND(ID_BUT_DXF_IN, OnButDxfIn)
	ON_COMMAND(ID_BUT_ERASE, OnButErase)
	ON_COMMAND(ID_BUT_MOVE, OnButMove)
	ON_COMMAND(ID_BUT_COPY, OnButCopy)
	ON_COMMAND(ID_BUT_PASTE, OnButPaste)
	ON_COMMAND(ID_BUT_ARRAY, OnButArray)
	ON_COMMAND(ID_BUT_ROTATE, OnButRotate)
	ON_COMMAND(ID_BUT_SCALE, OnButScale)
	ON_COMMAND(ID_BUT_MIRROR, OnButMirror)
	ON_COMMAND(ID_BUT_DECOMPOSE, OnButDecompose)
	ON_COMMAND(ID_BUT_OFFSET, OnButOffset)
	ON_COMMAND(ID_BUT_DIM, OnButDim)
	ON_COMMAND(ID_BUT_TRIM, OnButTrim)
	ON_COMMAND(ID_BUT_EXTEND, OnButExtend)
	ON_COMMAND(ID_BUT_BREAK_P, OnButBreakP)
	ON_COMMAND(ID_BUT_MULTIBREAK, OnButMultibreak)
	ON_COMMAND(ID_BUT_STRETCHES_P, OnButStretchesP)
	ON_COMMAND(ID_BUT_UNDO, OnButUndo)
	ON_COMMAND(ID_BUT_REDO, OnButRedo)
	ON_COMMAND(ID_BUT_TRIM_CAD_P, OnButTrimCadP)
	ON_COMMAND(ID_BUT_LINE, OnButLine)
	ON_COMMAND(ID_BUT_CIRCLE_P, OnButCircleP)
	ON_COMMAND(ID_BUT_ARC_P, OnButArcP)
	ON_COMMAND(ID_BUT_SPLINE, OnButSpline)
	ON_COMMAND(ID_BUT_RECT, OnButRect)
	ON_COMMAND(ID_BUT_POLYGON, OnButPolygon)
	ON_COMMAND(ID_BUT_INSERT_BLOCK, OnButInsertBlock)
	ON_COMMAND(ID_BUT_SAVE_BLOCK, OnButSaveBlock)
	ON_COMMAND(ID_BUT_DIM_LEAD, OnButDimLead)
	ON_COMMAND(ID_BUT_DIM_ORTHO_CLOSED, OnButDimOrthoClosed)
	ON_COMMAND(ID_BUT_DIM_ALIGN_CLOSED, OnButDimAlignClosed)
	ON_COMMAND(ID_BUT_DIM_ALIGN_PILEUP, OnButDimAlignPileup)
	ON_COMMAND(ID_BUT_DIM_ORTHO_PILEUP, OnButDimOrthoPileup)
	ON_COMMAND(ID_BUT_DIM_ANGLE, OnButDimAngle)
	ON_COMMAND(ID_BUT_DIM_RADIUS, OnButDimRadius)
	ON_COMMAND(ID_BUT_MOVE_DIM_LINE, OnButMoveDimLine)
	ON_COMMAND(ID_BUT_LAYOUT_DIM_LINE, OnButLayoutDimLine)
	ON_COMMAND(ID_BUT_ADD_DIM, OnButAddDim)
	ON_COMMAND(ID_BUT_DEL_DIM, OnButDelDim)
	ON_COMMAND(ID_BUT_LAYOUT_DIM_BASE, OnButLayoutDimBase)
	ON_COMMAND(ID_BUT_DIM_RE0, OnButDimRe0)
	ON_COMMAND(ID_BUT_ORTHO, OnButOrtho)
	ON_COMMAND(ID_BUT_SANP_END_PT, OnButSanpEndPt)
	ON_COMMAND(ID_BUT_SANP_CROSS_PT, OnButSanpCrossPt)
	ON_COMMAND(ID_BUT_SANP_LINE_PT, OnButSanpLinePt)
	ON_COMMAND(ID_BUT_SANP_MID_PT, OnButSanpMidPt)
	ON_COMMAND(ID_BUT_SANP_PERPENDICULAR, OnButSanpPerpendicular)
	ON_COMMAND(ID_BUT_SNAP_CIRCLE_PT, OnButSnapCirclePt)
	ON_COMMAND(ID_BUT_SANP_PT, OnButSanpPt)
	ON_COMMAND(ID_BUT_SANP_ALL, OnButSanpAll)
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_COMMAND(ID_BUT_LAYER_PART, OnButLayerPart)
	ON_COMMAND(ID_BUT_LAYER_SHEET, OnButLayerSheet)
	ON_COMMAND(ID_BUT_LAYER_APDIM, OnButLayerApdim)
	ON_COMMAND(ID_BUT_LAYER_CUT, OnButLayerCut)
	ON_COMMAND(ID_BUT_LAYER_DIM, OnButLayerDim)
	ON_COMMAND(ID_BUT_LAYER_MARK, OnButLayerMark)
	ON_COMMAND(ID_BUT_LAYER_VIEW, OnButLayerView)
	ON_COMMAND(ID_BUT_CLEAR, OnButClear)
	ON_COMMAND(ID_BUT_CAD_EE, OnButCadEe)
	ON_COMMAND(ID_BUT_CREATE_XZ, OnButCreateXz)
	ON_COMMAND(ID_BUT_CAD_WW, OnButCadWw)
	ON_COMMAND(ID_BUT_MERGE_NAME, OnButMergeName)
	ON_COMMAND(ID_BUT_CUT_TABLE, OnButCutTable)
	ON_COMMAND(ID_MENU_OK, OnMenuOk)
	ON_COMMAND(ID_MENU_REPEAT, OnMenuRepeat)
	ON_COMMAND(ID_MENU_EXIT_CMD, OnMenuExitCmd)
	ON_COMMAND(ID_MENU_PASTE, OnMenuPaste)
	ON_COMMAND(ID_MENU_DELETE, OnMenuDelete)
	ON_COMMAND(ID_MENU_MOVE, OnMenuMove)
	ON_COMMAND(ID_MENU_COPY, OnMenuCopy)
	ON_COMMAND(ID_MENU_PROP, OnMenuProp)
	ON_COMMAND(ID_MENU_ORTHO, OnMenuOrtho)
	ON_COMMAND(ID_MENU_MIDDLE, OnMenuMiddle)
	ON_COMMAND(ID_MENU_END_PT, OnMenuEndPt)
	ON_COMMAND(ID_MENU_CROSS_P, OnMenuCrossP)
	ON_COMMAND(ID_MENU_SNAP_ALL, OnMenuSnapAll)
	ON_COMMAND(ID_MENU_PT_IN_LINE, OnMenuPtInLine)
	ON_COMMAND(ID_MENU_PREPENDICULIAR_WP, OnMenuPrependiculiarWp)
	ON_COMMAND(ID_MENU_POINT, OnMenuPoint)
	ON_COMMAND(ID_TOOL_SHOW_LAYER, OnToolShowLayer)
	ON_COMMAND(ID_TOOL_LOCK_LAYER, OnToolLockLayer)
	ON_COMMAND(ID_TOOL_SHOW_LAYER_P, OnToolShowLayerP)
	ON_COMMAND(ID_TOOL_LOCK_LAYER_P, OnToolLockLayerP)
	ON_COMMAND(ID_TOOL_SELECT, OnToolSelect)
	ON_COMMAND(ID_TOOL_SELECT_P, OnToolSelectP)
	ON_COMMAND(ID_BUT_DIM_TXT, OnButDimTxt)
	ON_COMMAND(ID_BUT_DIM_TXT_P, OnButDimTxtP)
	ON_UPDATE_COMMAND_UI(ID_BUT_UNDO, OnUpdateButUndo)
	ON_UPDATE_COMMAND_UI(ID_BUT_REDO, OnUpdateButRedo)
	ON_COMMAND(ID_BUT_ONE_IN, OnButOneIn)
	ON_COMMAND(ID_BUT_REVERSE_COLOR, OnButReverseColor)
	ON_COMMAND(ID_BUT_ONE_IN_P, OnButOneInP)
	ON_COMMAND(ID_BUT_REVERSE_COLOR_P, OnButReverseColorP)
	ON_WM_CHAR()
	ON_COMMAND(ID_BUT_CHECK_TEXT, OnButCheckText)
	ON_COMMAND(ID_BUT_SELECT_TEXT, OnButSelectText)
	ON_COMMAND(ID_BUT_CHECK_TEXT_P, OnButCheckTextP)
	ON_COMMAND(ID_BUT_SELECT_TEXT_P, OnButSelectTextP)
	ON_COMMAND(ID_BUT_SHOW_SAME_TEXT, OnButShowSameText)
	ON_COMMAND(ID_BUT_SHOW_SAME_TEXT_P, OnButShowSameTextP)
	ON_COMMAND(ID_BUT_CREATE_REPORT, OnButCreateReport)
	ON_COMMAND(ID_BUT_CREATE_REPORT_P, OnButCreateReportP)
	ON_COMMAND(ID_BUT_SHOW_ALL_P, OnButShowAllP)
	ON_COMMAND(ID_BUT_SELECT_FILE_0, OnButSelectFile0)
	ON_COMMAND(ID_BUTTON32812, OnButton32812)
	ON_COMMAND(ID_BUTTON32812_P, OnButton32812P)
	ON_COMMAND(ID_BUT_SELECT_FILE_01, OnButSelectFile01)
	ON_COMMAND(ID_APP_HELP, OnAppHelp)
	ON_COMMAND(ID_APP_HELP_P, OnAppHelpP)
	ON_COMMAND(ID_BUT_BRUSH, OnButBrush)
	ON_COMMAND(ID_BUT_BRUSH_P, OnButBrushP)
	ON_COMMAND(ID_BUT_IMPORT_NAME_INFO, OnButImportNameInfo)
	ON_COMMAND(ID_BUT_DIM_LEAD_INFO, OnButDimLeadInfo)
	ON_COMMAND(ID_BUT_DIM_NAME_SET, OnButDimNameSet)
	ON_COMMAND(ID_MENU_NEW_FEATURES, OnMenuNewFeatures)
	ON_COMMAND(ID_BUT_DIM_NAME_NOlLINE, OnBUTDIMNAMENOlLINE)
	ON_COMMAND(ID_BUT_DIM_LINE_DIRECT, OnButDimLineDirect)
	ON_COMMAND(ID_BUT_SET_REPLACE_SIGN, OnButSetReplaceSign)
	ON_COMMAND(ID_BUT_DIM_LINE_PLATE_SIDE, OnButDimLinePlateSide)
	ON_COMMAND(ID_BUT_CREATE_BLOCK_NEW, OnButCreateBlockNew)
	ON_COMMAND(ID_BUT_INSERT_BLOCK_P222P, OnButInsertBlockP222p)
	ON_COMMAND(ID_BUT_INSERT_BLOCK111, OnButInsertBlock111)
	ON_COMMAND(ID_BUT_INSERT_BLOCK222, OnButInsertBlock222)
	ON_COMMAND(ID_BUT_HOTKEY_REI, OnButHotkeyRei)
	ON_COMMAND(ID_BUT_CUT_DIM_LINE, OnButCutDimLine)
	ON_COMMAND(ID_MENU_VIEW_LINE, OnMenuViewLine)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_MENU_ERASE, OnMenuErase)
	ON_COMMAND(ID_MENU_VIEW_PASTE, OnMenuViewPaste)
	ON_COMMAND(ID_MENU_VIEW_ARRAY, OnMenuViewArray)
	ON_COMMAND(ID_MENU_VIEW_ROTATE, OnMenuViewRotate)
	ON_COMMAND(ID_MENU_VIEW_SCALE, OnMenuViewScale)
	ON_COMMAND(ID_MENU_VIEW_MIRROR, OnMenuViewMirror)
	ON_COMMAND(ID_MENU_VIEW_BREAK, OnMenuViewBreak)
	ON_COMMAND(ID_MENU_VIEW_OFFSET, OnMenuViewOffset)
	ON_COMMAND(ID_MENU_VIEW_DIM, OnMenuViewDim)
	ON_COMMAND(ID_MENU_VIEW_TRIM, OnMenuViewTrim)
	ON_COMMAND(ID_MENU_VIEW_EXTEND, OnMenuViewExtend)
	ON_COMMAND(ID_MENU_VIEW_CUT, OnMenuViewCut)
	ON_COMMAND(ID_MENU_VIEW_MULTI_CUT, OnMenuViewMultiCut)
	ON_COMMAND(ID_MENU_VIEW_STRETCHES, OnMenuViewStretches)
	ON_COMMAND(ID_MENU_VIEW_CIRCLE, OnMenuViewCircle)
	ON_COMMAND(ID_MENU_VIEW_ARC, OnMenuViewArc)
	ON_COMMAND(ID_MENU_VIEW_SPLINE, OnMenuViewSpline)
	ON_COMMAND(ID_MENU_VIEW_RECT, OnMenuViewRect)
	ON_COMMAND(ID_MENU_VIEW_POLYGON, OnMenuViewPolygon)
	ON_COMMAND(ID_MENU_VIEW_TEXT, OnMenuViewText)
	ON_COMMAND(ID_MENU_VIEW_CRATE_BLOCK, OnMenuViewCrateBlock)
	ON_COMMAND(ID_MENU_VIEW_INSERT_BLOCK, OnMenuViewInsertBlock)
	ON_COMMAND(ID_MENU_VIEW_DIM_LEAD, OnMenuViewDimLead)
	ON_COMMAND(ID_MENU_VIEW_ORTHO_CLOSED, OnMenuViewOrthoClosed)
	ON_COMMAND(ID_MENU_VIEW_ALIGN_CLOSED, OnMenuViewAlignClosed)
	ON_COMMAND(ID_MENU_VIEW_ORTHO_PIPEUP, OnMenuViewOrthoPipeup)
	ON_COMMAND(ID_MENU_VIEW_ALIGN_PIPEUP, OnMenuViewAlignPipeup)
	ON_COMMAND(ID_MENU_VIEW_DIM_ANGLE, OnMenuViewDimAngle)
	ON_COMMAND(ID_MENU_VIEW_DIM_RADIOUS, OnMenuViewDimRadious)
	ON_COMMAND(ID_MENU_VIEW_DIM_LEAD_INFO, OnMenuViewDimLeadInfo)
	ON_COMMAND(ID_MENU_VIEW_DIM_TEXT_INFO, OnMenuViewDimTextInfo)
	ON_COMMAND(ID_MENU_VIEW_DIM_PLATESIDE, OnMenuViewDimPlateside)
	ON_COMMAND(ID_MENU_VIEW_DIM_DIRECT_LINE, OnMenuViewDimDirectLine)
	ON_COMMAND(ID_MENU_VIEW_MOVE_DIM, OnMenuViewMoveDim)
	ON_COMMAND(ID_MENU_VIEW_MOVE_SIGNE_DIM, OnMenuViewMoveSigneDim)
	ON_COMMAND(ID_MENU_VIEW_ADD_DIM, OnMenuViewAddDim)
	ON_COMMAND(ID_MENU_VIEW_DEL_DIM, OnMenuViewDelDim)
	ON_COMMAND(ID_MENU_VIEW_CUT_DIM_LINE, OnMenuViewCutDimLine)
	ON_COMMAND(ID_MENU_VIEW_CHANGE_DIM_0, OnMenuViewChangeDim0)
	ON_COMMAND(ID_MENU_VIEW_CUT_DIM_LINE_NO_SIDE, OnMenuViewCutDimLineNoSide)
	ON_COMMAND(ID_MENU_VIEW_ORTHO, OnMenuViewOrtho)
	ON_COMMAND(ID_MENU_VIEW_END_PT, OnMenuViewEndPt)
	ON_COMMAND(ID_MENU_VIEW_CROSS_PT, OnMenuViewCrossPt)
	ON_COMMAND(ID_MENU_VIEW_PT_IN_LINE, OnMenuViewPtInLine)
	ON_COMMAND(ID_MENU_VIEW_MIDDLE, OnMenuViewMiddle)
	ON_COMMAND(ID_MENU_VIEW_PERPENDICULAR, OnMenuViewPerpendicular)
	ON_COMMAND(ID_MENU_VIEW_CENTER, OnMenuViewCenter)
	ON_COMMAND(ID_MENU_VIEW_PT, OnMenuViewPt)
	ON_COMMAND(ID_MENU_VIEW_ALL, OnMenuViewAll)
	ON_COMMAND(ID_MENU_VIEW_REPLACE_STRING, OnMenuViewReplaceString)
	ON_COMMAND(ID_MENU_VIEW_HOTKEY, OnMenuViewHotkey)
	ON_COMMAND(ID_MENU_VIEW_IMPORT_PARTLIST, OnMenuViewImportPartlist)
	ON_COMMAND(ID_MENU_VIEW_IMPORT_SET_DIM_NAME_STYLE, OnMenuViewImportSetDimNameStyle)
	ON_COMMAND(ID_BUT_FIND_TOOL, OnButFindTool)
	ON_COMMAND(ID_BUT_SELECT_HIDE, OnButSelectHide)
	ON_COMMAND(ID_BUT_SELECT_SHOW, OnButSelectShow)
	ON_COMMAND(ID_BUT_SELECT_REVERSE, OnButSelectReverse)
	ON_COMMAND(ID_BUT_SELECT_SHOWALL, OnButSelectShowall)
	ON_COMMAND(ID_BUT_SELECT_REVERSE_P, OnButSelectReverseP)
	ON_COMMAND(ID_BUT_SELECT_TABLE_TEXT, OnButSelectTableText)
	ON_COMMAND(ID_BUT_SELECT_TEXT_SIGNAL, OnButSelectTextSignal)
	ON_COMMAND(ID_BUT_SELECT_JISHOU, OnButSelectJishou)
	ON_COMMAND(ID_BUT_DRAW_EXTEND_LINE, OnButDrawExtendLine)
	ON_COMMAND(ID_BUT_JOINTDB, OnButJointdb)
	ON_COMMAND(ID_BUT_AUTO_CHECK, OnButAutoCheck)
	ON_COMMAND(ID_BUT_REPLACE_MATRAIL, OnButReplaceMatrail)
	ON_COMMAND(ID_BUT_COMBINATION, OnButCombination)
	ON_COMMAND(ID_BUT_FIND_CENTER, OnButFindCenter)
	ON_COMMAND(ID_BUT_FIND_MID, OnButFindMid)
	ON_COMMAND(ID_BUT_DIM_SOLPE, OnButDimSolpe)
	ON_COMMAND(ID_BUT_CANCEL_COMBINATION, OnButCancelCombination)
	ON_COMMAND(ID_MENU_SETUP, OnMenuSetup)
	ON_WM_KEYUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUT_DIM_LINE_LEAD, OnButDimLineLead)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAp2DView construction/destruction

CAp2DView::CAp2DView()
{
	// TODO: add construction code here
	view_ = NULL;
	repeat_cmd_ = NULL;
	layer_show_.part_ = false;
	layer_show_.sheet_ = false;
	layer_show_.cut_ = false;
	layer_show_.view_ = false;
	layer_show_.dim_ = false;
	layer_show_.mark_ = false;
	layer_show_.apdim_ = false;

	sel_joint_ = NULL;

	b_eidt_ = false;
}

CAp2DView::~CAp2DView()
{
}//
void CAp2DView::set_edit()
{
	b_eidt_ = true;
	Global::instance()->is_eidt_ = true;
}
BOOL CAp2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAp2DView drawing

void CAp2DView::OnDraw(CDC* pDC)
{
	CAp2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->SetBkMode(TRANSPARENT);
	dlhml::Painter_Windows painter(GetSafeHwnd());
	painter.attach_dc(pDC->GetSafeHdc());
	if(!view_)
		return;
	view_->scene()->draw_scene();
}

/////////////////////////////////////////////////////////////////////////////
// CAp2DView printing

BOOL CAp2DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAp2DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAp2DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAp2DView diagnostics

#ifdef _DEBUG
void CAp2DView::AssertValid() const
{
	CView::AssertValid();
}

void CAp2DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAp2DDoc* CAp2DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAp2DDoc)));
	return (CAp2DDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAp2DView message handlers

void CAp2DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	view_->scene()->key_down(nChar,nRepCnt,nFlags);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CAp2DView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	view_->scene()->left_button_dblclk(nFlags,dlhml::Point(point));
	CView::OnLButtonDblClk(nFlags, point);
}

void CAp2DView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	view_->scene()->left_button_down(nFlags,dlhml::Point(point));

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Entitys ents;
	pM->set_status_num(get_select_ents(view_->scene()->database(),ents));
	pM->set_status_num(ents.size());
	
	CView::OnLButtonDown(nFlags, point);
}

void CAp2DView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	view_->scene()->left_button_up(nFlags,dlhml::Point(point));
	
	CView::OnLButtonUp(nFlags, point);
}

void CAp2DView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	view_->scene()->mouse_move(nFlags,dlhml::Point(point));
	CView::OnMouseMove(nFlags, point);
}

BOOL CAp2DView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	ScreenToClient(&pt);
	view_->scene()->mouse_wheel(nFlags,zDelta,dlhml::Point(pt));
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
void CAp2DView::load_menu()
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_CMD_MANAGE);
	CMenu * pSubMenu = menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pSubMenu->TrackPopupMenu(TPM_RIGHTBUTTON ,pt.x,pt.y,this);		
}

void CAp2DView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	view_->scene()->right_button_down(nFlags,dlhml::Point(point));	
//	if(Global::instance()->rignt_but_exit())
	if(Global::instance()->setting().show_right_menu_)
		load_menu();
	else{
		//ok();
		view_->scene()->ok();
		esc();
	}
	CView::OnRButtonDown(nFlags, point);
}
void CAp2DView::OnMButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	view_->scene()->middle_button_dblclk(nFlags,dlhml::Point(point.x,point.y));
	CWnd::OnMButtonDblClk(nFlags, point);
}
void CAp2DView::OnMButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	view_->scene()->middle_button_down(nFlags,dlhml::Point(point.x,point.y));
	CWnd::OnMButtonDown(nFlags, point);
}

void CAp2DView::OnMButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	view_->scene()->middle_button_up(nFlags,dlhml::Point(point.x,point.y));
	CWnd::OnMButtonUp(nFlags, point);
}

void CAp2DView::set_view(View *v)
{
	view_ = v;
	view_->scene()->attach_window(dlhml::Scene_Wnd_Windows::create_me(m_hWnd));
	view_->scene()->background_color(RGB(0,0,0));//RGB(204,232,207)

	view_->scene()->set_vistor(&vis_ent_dblckl_);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	view_->scene()->attach_command_line(new dlhml::Command_Line_Info(*pM->in(),*pM->out()));

	DB_View::instance()->cur_view(v);

	

/*	scene()->set_vistor(&edit_dblclk_);

	//默认命令是选中钢实体
	Cmd_Select_Steel* sel_steel = new Cmd_Select_Steel(*scene());
	scene()->attach_command(sel_steel);

	OnButSanpPt();
*/

}

int CAp2DView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


	
	
	// TODO: Add your specialized creation code here
	set_view(DB_View::instance()->add_view("test"));
	OnButSanpPt() ;
	return 0;
}


void CAp2DView::OnButDxfOut() 
{
	// TODO: Add your command handler code here
	/*	AfxMessageBox("The dxf file can't create.please contact REI by telephone.the number is 0411-84753206!",MB_OK);


	ApNet_Check check;
	BOOL res = check.check_data(Global::instance()->cur_val().user_,Global::instance()->cur_val().password_);
	if(res == FALSE){
		return;
	
	}
*/
	CString strFile,strName;
	static char szFilter[] = "DXF file format (*.dxf)|*.dxf|All Files (*.*)|*.*||";
	CFileDialog dlg(FALSE, _T(".dxf"), Global::instance()->dxf_name(), OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL);
	dlg.m_ofn.lpstrTitle = "Save DXF File";
	if(dlg.DoModal()== IDOK)
	{
		strFile=dlg.GetPathName();
		dlhml::save_dxf(strFile.GetBuffer(0), *DB_View::instance()->database());

		//添加单独保存标注的命令
		DimInfo_IO dim_info;
		dim_info.save(strFile);
	}
}

void CAp2DView::OnButDxfIn() 
{
	// TODO: Add your command handler code here
	set_edit();
	CString strFile,strName;
	static char szFilter[] = "DXF file format(*.dxf) |*.dxf|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL );
	dlg.m_ofn.lpstrTitle = "Open DXF File";
	if(dlg.DoModal()== IDOK){
		strFile=dlg.GetPathName();
		Global::instance()->dxf_name() = dlg.GetFileTitle();
		
		CString path;
		Dxf_Read dxf_read;		
		dxf_read.set_text_scale(Global::instance()->setting().reduce_scale_);
		dxf_read.read(strFile.GetBuffer(0),DB_View::instance()->cur_view()->scene());
		DB_View::instance()->cur_view()->scene()->invalidate();
		DB_View::instance()->cur_view()->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(100,100));

	}


	//添加导入创建的层
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->get_combo_layer_bar().combo_.Clear();
	strings layers;
	get_layers(DB_View::instance()->cur_view()->scene()->database(),layers);
	for(int i=0;i<layers.size();i++){
			pM->get_combo_layer_bar().combo_.AddString(layers[i].c_str());

	}
	pM->get_combo_layer_bar().combo_.AddString("Dim");

}
void CAp2DView::cmd_init()
{
	set_edit();
	view_->scene()->idle_command();
	DB_View::instance()->cur_view()->scene()->idle_command();
	view_->scene()->get_idle()->set_step();
}

void CAp2DView::OnButErase() 
{
	// TODO: Add your command handler code here
	cmd_init();
	view_->scene()->create_delete();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_all_toolbar_no_snap();
//	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_ERASE, pM->get_edit_bar());

	repeat_cmd_ = &CAp2DView::OnButErase;
	
}

void CAp2DView::OnButMove() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_MOVE, pM->get_edit_bar());
	view_->scene()->entity_move();
	repeat_cmd_ = &CAp2DView::OnButMove;
}

void CAp2DView::OnButCopy() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_COPY, pM->get_edit_bar());
	view_->scene()->create_copy();
	repeat_cmd_ = &CAp2DView::OnButCopy;
}

void CAp2DView::OnButPaste() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_PASTE, pM->get_edit_bar());
	view_->scene()->get_idle()->paste();
	repeat_cmd_ = &CAp2DView::OnButPaste;
}

void CAp2DView::OnButArray() 
{
	// TODO: Add your command handler code here
	cmd_init(); 
	CMainFrame* pM =(CMainFrame*)AfxGetMainWnd();
	dlhml::Entity_Array ary;
	if(view_->scene()->get_idle()->xor().empty()){
		Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_ARRAY,pM->get_edit_bar());
		view_->scene()->array_cad(ary);
	}else{
		Global::instance()->mgr_toolbar().check_all_toolbar_no_snap();
		Array_Cad_Dlg dlg;
		if(dlg.DoModal() == IDOK){
			ary = dlg.ary;
			view_->scene()->array_cad(ary);
		}
		view_->scene()->cancel();
	}
	
	repeat_cmd_ = &CAp2DView::OnButArray;

}

void CAp2DView::OnButRotate() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_ROTATE, pM->get_edit_bar());
	view_->scene()->create_rotate();
	repeat_cmd_ = &CAp2DView::OnButRotate;
}

void CAp2DView::OnButScale() 
{
	// TODO: Add your command handler code here
 	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_SCALE, pM->get_edit_bar());
	view_->scene()->create_scale(); 
	repeat_cmd_ = &CAp2DView::OnButScale;
	
}

void CAp2DView::OnButMirror() 
{
	// TODO: Add your command handler code here
 	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_MIRROR, pM->get_edit_bar());
	view_->scene()->create_mirror();
	repeat_cmd_ = &CAp2DView::OnButMirror;
}

void CAp2DView::OnButDecompose() 
{
	// TODO: Add your command handler code here
  cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_DECOMPOSE, pM->get_edit_bar());

	//处理块
	//view_->scene()->split_block();
	//处理组合标注
	Decompose_Entity decomp;
	decomp.decompose();
	
	DB_View::instance()->cur_view()->scene()->invalidate();

	repeat_cmd_ = &CAp2DView::OnButDecompose;
}

void CAp2DView::OnButOffset() 
{
	// TODO: Add your command handler code here
  cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_OFFSET, pM->get_edit_bar());
	view_->scene()->vmove_line();
	repeat_cmd_ = &CAp2DView::OnButOffset;
	
}

void CAp2DView::OnButDim() 
{
	// TODO: Add your command handler code here
	::SetCursor(::LoadCursor(NULL,IDC_CROSS));
	cmd_init();
	view_->scene()->idle_command();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_DIM, pM->get_edit_bar());

	repeat_cmd_ = &CAp2DView::OnButDim;
}


void CAp2DView::OnButTrim() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_TRIM, pM->get_edit_bar());
	view_->scene()->create_trim();
	repeat_cmd_ = &CAp2DView::OnButTrim;
}

void CAp2DView::OnButExtend() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_EXTEND, pM->get_edit_bar());
	view_->scene()->create_extend();
	repeat_cmd_ = &CAp2DView::OnButExtend;
}

void CAp2DView::OnButBreakP() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_BREAK_P, pM->get_edit_bar());
	view_->scene()->create_break();
	repeat_cmd_ = &CAp2DView::OnButBreakP;
}

void CAp2DView::OnButMultibreak() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM =(CMainFrame*)AfxGetMainWnd();
/*
	Dlg_Break dlg;
	if(view_->scene()->get_idle()->xor().empty()){
		Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_MULTIBREAK,pM->get_edit_bar());
		view_->scene()->get_idle()->on_break_cad(dlg.num, dlg.dis);
	}else{
		Global::instance()->mgr_toolbar().check_all_toolbar_no_snap();
		if (dlg.DoModal() == IDOK){	
			view_->scene()->get_idle()->on_break_cad(dlg.num, dlg.dis);
		}	
		view_->scene()->cancel();
	}
*/
	repeat_cmd_ = &CAp2DView::OnButMultibreak;
}

void CAp2DView::OnButStretchesP() 
{
	// TODO: Add your command handler code here
	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_edit_toolbar(ID_BUT_STRETCHES_P, pM->get_edit_bar());
	view_->scene()->strech_cad();
	repeat_cmd_ = &CAp2DView::OnButStretchesP;
	
}

void CAp2DView::OnButUndo() 
{
	// TODO: Add your command handler code here
	if(view_->scene()->can_undo())
		view_->scene()->undo();
	
}

void CAp2DView::OnButRedo() 
{
	// TODO: Add your command handler code here
	cmd_init();
	if(view_->scene()->can_redo())
		view_->scene()->redo();
	
}

void CAp2DView::OnButTrimCadP() 
{
	// TODO: Add your command handler code here
	
}
#define ltype "Continuous"

static int color_index = 1;
static void init_basic_entity(dlhml::Entity & o)
{	
	o.line_style(ltype);
	o.color_index(color_index);
}
void CAp2DView::create_command(dlhml::Entity& seed)
{
	dlhml::Scene & scn = *view_->scene();
	dlhml::CreateCmd * cs = new dlhml::CreateCmd(scn, &seed);
	cs->mode(dlhml::SINGLE);
	scn.create_entity(cs);
}

void CAp2DView::create_basic_entity(dlhml::Entity& seed)
{
	set_edit();
	init_basic_entity(seed);
	create_command(seed);
}

void CAp2DView::OnButLine() 
{
	// TODO: Add your command handler code here
	cmd_init();
	set_edit();
	dlhml::Line_Arrow seed;
	seed.group(USER_ADD_ENTS);
	create_basic_entity(seed);

	init_line_arrow(seed);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_LINE, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButLine;
	view_->scene()->invalidate();
}

void CAp2DView::OnButCircleP() 
{
	// TODO: Add your command handler code here
	set_edit();
	dlhml::Circle seed;
	seed.group(USER_ADD_ENTS);
	create_basic_entity(seed);

	init_circle(seed);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_CIRCLE_P, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButCircleP;
}

void CAp2DView::OnButArcP() 
{
	// TODO: Add your command handler code here
	set_edit();
	dlhml::Arc_Arrow seed;
	seed.group(USER_ADD_ENTS);
	create_basic_entity(seed);

	init_arc_arrow(seed);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_ARC_P, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButArcP;
}
static void init_spline(dlhml::Cloud_Line & o)
{
	o.line_style(ltype);
	o.color_index(color_index);
  o.line(false);
  o.open(false);
}

void CAp2DView::OnButSpline() 
{
	// TODO: Add your command handler code here
	dlhml::Cloud_Line seed;
	seed.open(false);
	seed.group(USER_ADD_ENTS);

	init_spline(seed);

	init_cloud_line(seed);
	create_command(seed);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_SPLINE, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButSpline;
}

void CAp2DView::OnButRect() 
{
	// TODO: Add your command handler code here
	dlhml::Cloud_Line seed;
	seed.color_index(1);
	seed.rect(true);
	seed.line(true);
	seed.open(false);
	seed.group(USER_ADD_ENTS);

	init_cloud_line(seed);
	
	create_command(seed);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_RECT, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButRect;
}

void CAp2DView::OnButPolygon() 
{
	// TODO: Add your command handler code here
	dlhml::Cloud_Line seed;
	seed.color_index(1);
	seed.line(true);
	seed.open(false);
	seed.group(USER_ADD_ENTS);
	init_cloud_line(seed);

	create_command(seed);


	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_POLYGON, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButPolygon;
}

void CAp2DView::OnButInsertBlock() 
{
	// TODO: Add your command handler code here
 	cmd_init();
//	Dlg_Block_Manage dlg;
//	dlg.DoModal();
	
}

void CAp2DView::OnButSaveBlock() 
{
	// TODO: Add your command handler code here
 	cmd_init();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_SAVE_BLOCK, pM->get_create_bar());
	view_->scene()->make_block();
	repeat_cmd_ = &CAp2DView::OnButSaveBlock;
	
}

void CAp2DView::OnButDimLead() 
{
	// TODO: Add your command handler code here
	set_edit();
	dlhml::Lead_Dimension seed;

	seed.color_index(3);
	seed.layer_name(LAYER_AP_DIM);

	// init_dim_lead(seed);
	seed.dim_text(get_select_txt(view_->scene()->database()));

	create_command(seed);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_LEAD, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimLead;
}
/*
void CAp2DView::OnButDimLeadInfo() 
{
	// TODO: Add your command handler code here
	set_edit();
	dlhml::Lead_Dimension_Info seed;

	seed.color_index(3);
	seed.layer_name(LAYER_AP_DIM);

	// init_dim_lead(seed);
	seed.dim_text(get_select_txt(view_->scene()->database()));

	create_command(seed);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_LEAD, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimLead;
}
*/

void CAp2DView::OnButDimLeadInfo() 
{
	// TODO: Add your command handler code here
	CString str_name;
	std::string name = get_select_txt(view_->scene()->database());
	CStringArray names_ary;
	Model_DB::instance()->get_names(names_ary);
	if(name == "" ||name == "Txt" ){
		Dlg_Select_Name dlg_name;
		dlg_name.set_names(names_ary);
		if(dlg_name.DoModal() == IDOK){
			str_name = dlg_name.get_name();
		}

	}else{
		str_name = name.c_str();
	}
	
	CStringArray strs_ary;
	Model_DB::instance()->get_dim_name_strs(str_name,strs_ary);

	std::vector<std::string> strs;

	
	for(int i=0;i<strs_ary.GetSize();i++){
		strs.push_back(strs_ary[i].GetBuffer(0));
	}

	int size = strs.size();

	if(strs_ary.GetSize() == 0){
		//MessageBox("No infoes,please check the model.");
		return;
	}
	dlhml::Lead_Dimension_Info seed;

	seed.color_index(1);


	seed.set_dim_content(strs);
	seed.layer_name(LAYER_AP_DIM);
	
	//需要把整个的替换数据库都设置到Lead_Dimension_Info中，去准备替换
	std::vector<dlhml::Text_Rep_Obj> reps;
	DB_Text_Replace::instance()->get_obj_format(reps);
	seed.set_replace_db(reps);

	init_dim_lead_info(seed);
	seed.dim_text(get_select_txt(view_->scene()->database()));

	create_command(seed);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_LEAD, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimLead;

}


static void set_ln_dim_txt(dlhml::Ln_Dim& dim)
{
/*
	CString str;
	double scale = Global::instance()->scale();
	double real_val = 0;
	if(dim.mode() == dlhml::PILEUP_DIM){
		real_val = dim.get_span_oe();
		real_val *= scale;	
		str.Format("%f",real_val);
		dim.dim_text("0");
		dim.dim_text2(str.GetBuffer(0));
  }else if(dim.mode() == dlhml::CLOSED_DIM){
		real_val = dim.get_span_se();		
		real_val *= scale;	
		str.Format("%f",real_val);
		dim.dim_text(str.GetBuffer(0));
		dim.dim_text2("");
	}
*/
}


void CAp2DView::create_ln_dim(int mode, int rota)
{
	dlhml::Ln_Dim seed;
	//init
	seed.color_index(1);
	seed.mode(mode);
	seed.rota(rota);
//	seed.pf_content_ = set_ln_dim_txt;
	seed.layer_name(LAYER_AP_DIM);

	init_ln_dim(seed);

/*
	Dimension_Style sty;
	sty.text_height(150.0);
	sty.arrow_size(100.0);
	sty.extend_end_off(100);
	sty.extend_start_off(100);
	sty.line_color(7);
	sty.text_color(3);
	sty.text_precision(0);
	sty.arrow_style(dlhml::Dimension_Style::LEAD);

	seed.dim_style_val(sty);
*/

	create_command(seed);
}
 

void CAp2DView::OnButDimOrthoClosed() 
{
	// TODO: Add your command handler code here
	set_edit();
	create_ln_dim(dlhml::CLOSED_DIM, dlhml::ORTHO_DIM);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_ORTHO_CLOSED, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimOrthoClosed;
	
}

void CAp2DView::OnButDimAlignClosed() 
{
	// TODO: Add your command handler code here
	set_edit();
	create_ln_dim(dlhml::CLOSED_DIM, dlhml::ALIGN_DIM);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_ALIGN_CLOSED, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimAlignClosed;
}

void CAp2DView::OnButDimAlignPileup() 
{
	// TODO: Add your command handler code here
	set_edit();
	create_ln_dim(dlhml::PILEUP_DIM, dlhml::ALIGN_DIM);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_ALIGN_PILEUP, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimAlignPileup;
	
}

void CAp2DView::OnButDimOrthoPileup() 
{
	// TODO: Add your command handler code here
	set_edit();
	create_ln_dim(dlhml::PILEUP_DIM, dlhml::ORTHO_DIM);	
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_ORTHO_PILEUP, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimOrthoPileup;
}

void CAp2DView::OnButDimAngle() 
{
	// TODO: Add your command handler code here
	set_edit();
	dlhml::Angle_Dimension seed;
	seed.color_index(1);
	seed.group(USER_ADD_ENTS);
	seed.layer_name(LAYER_AP_DIM);

	init_angle_dim(seed);


	create_command(seed);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_ANGLE, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimAngle;
}

void CAp2DView::OnButDimRadius() 
{
	// TODO: Add your command handler code here
	set_edit();
	dlhml::Radius_Dimension seed;
	seed.color_index(1);
	seed.layer_name(LAYER_AP_DIM);

	init_radius_dim(seed);

	create_command(seed);
	seed.group(USER_ADD_ENTS);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_RADIUS, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimRadius;
	
}

void CAp2DView::OnButMoveDimLine() 
{
	// TODO: Add your command handler code here
	view_->scene()->move_dim_line_cad();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_MOVE_DIM_LINE, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButMoveDimLine;
}

void CAp2DView::OnButLayoutDimLine() 
{
	// TODO: Add your command handler code here
	view_->scene()->layout_dim_line_cad();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_LAYOUT_DIM_LINE, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButLayoutDimLine;
}

void CAp2DView::OnButAddDim() 
{
	// TODO: Add your command handler code here
	view_->scene()->add_dim_cad();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_ADD_DIM, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButAddDim;

	set_edit();
}

void CAp2DView::OnButDelDim() 
{
	// TODO: Add your command handler code here
	set_edit();
	view_->scene()->del_dim_cad();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DEL_DIM, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDelDim;
	
}

void CAp2DView::OnButLayoutDimBase() 
{
	// TODO: Add your command handler code here
	view_->scene()->layout_dim_base_cad();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_LAYOUT_DIM_BASE, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButLayoutDimBase;
}

void CAp2DView::OnButDimRe0() 
{
	// TODO: Add your command handler code here
	set_edit();
	view_->scene()->re0_dim_cad();
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_RE0, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimRe0;
}

void CAp2DView::OnButOrtho() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_ORTHO); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_ORTHO, !bCheck);
	view_->scene()->ortho(!bCheck);
}

void CAp2DView::OnButSanpEndPt() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_END_PT); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_END_PT, !bCheck);
	snap_style(*view_->scene(), dlhml::Snap::Endpoint, !bCheck);
}

void CAp2DView::OnButSanpCrossPt() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_CROSS_PT); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_CROSS_PT, !bCheck);
	snap_style(*view_->scene(), dlhml::Snap::Intersect, !bCheck);
}

void CAp2DView::OnButSanpLinePt() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_LINE_PT); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_LINE_PT, !bCheck);
	snap_style(*view_->scene(), dlhml::Snap::Nearest, !bCheck);
}

void CAp2DView::OnButSanpMidPt() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_MID_PT); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_MID_PT, !bCheck);
	snap_style(*view_->scene(), dlhml::Snap::Middle, !bCheck);
	
}

void CAp2DView::OnButSanpPerpendicular() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_PERPENDICULAR); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_PERPENDICULAR, !bCheck);
	snap_style(*view_->scene(), dlhml::Snap::Perpendicular, !bCheck);

}

void CAp2DView::OnButSnapCirclePt() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SNAP_CIRCLE_PT); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SNAP_CIRCLE_PT, !bCheck);
	snap_style(*view_->scene(), dlhml::Snap::Center, !bCheck);
}

void CAp2DView::OnButSanpPt() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_PT); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_PT, !bCheck);
	snap_style(*view_->scene(), dlhml::Snap::Anypoint, !bCheck);
}

void CAp2DView::OnButSanpAll() 
{
	// TODO: Add your command handler code here
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_ALL); 
	check(pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, ID_BUT_SANP_ALL, !bCheck);
	snap_all(*view_->scene(), pM->get_snap_bar(), Global::instance()->mgr_toolbar().snap_, !bCheck);	
}
void CAp2DView::show_ents(std::string layer_name,bool &show,UINT id)
{
	show_ents_by_layer(view_->scene()->database(),layer_name,show);
	show =!show;
	view_->scene()->invalidate();

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	bool bCheck = is_check(pM->get_layer_bar(), Global::instance()->mgr_toolbar().layer_, id); 
	check(pM->get_layer_bar(), Global::instance()->mgr_toolbar().layer_, id, !bCheck);

}
void CAp2DView::OnButLayerPart() 
{
	// TODO: Add your command handler code here
	show_ents(LAYER_PART,layer_show_.part_,ID_BUT_LAYER_PART);
	

}

void CAp2DView::OnButLayerSheet() 
{
	// TODO: Add your command handler code here
	show_ents(LAYER_SHEET,layer_show_.sheet_,ID_BUT_LAYER_SHEET);
}

void CAp2DView::OnButLayerApdim() 
{
	// TODO: Add your command handler code here
	show_ents(LAYER_AP_DIM,layer_show_.apdim_,ID_BUT_LAYER_APDIM);
}

void CAp2DView::OnButLayerCut() 
{
	// TODO: Add your command handler code here
	show_ents(LAYER_CUT,layer_show_.cut_,ID_BUT_LAYER_CUT);
}

void CAp2DView::OnButLayerDim() 
{
	// TODO: Add your command handler code here
	show_ents(LAYER_DIM,layer_show_.dim_,ID_BUT_LAYER_DIM);
}

void CAp2DView::OnButLayerMark() 
{
	// TODO: Add your command handler code here
	show_ents(LAYER_MARK,layer_show_.mark_,ID_BUT_LAYER_MARK);
}

void CAp2DView::OnButLayerView() 
{
	// TODO: Add your command handler code here
	show_ents(LAYER_VIEW,layer_show_.view_,ID_BUT_LAYER_VIEW);
}

void CAp2DView::OnButClear() 
{
	// TODO: Add your command handler code here
	view_->scene()->database()->clear_entity();
	view_->scene()->invalidate();
}

void CAp2DView::OnButCadEe() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButCreateXz() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButCadWw() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButMergeName() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButCutTable() 
{
	// TODO: Add your command handler code here
	
}
void CAp2DView::esc()
{
	//放置debug时esc时出错误
	//Global::instance()->mgr_toolbar().check_all_toolbar();
	Global::instance()->rignt_but_exit() = 0;
	cmd_init();
	clear_select(view_->scene()->database());
	view_->scene()->get_idle()->clear_selected();
	view_->scene()->get_idle()->clearxor();
 	view_->scene()->invalidate();
	view_->scene()->info_to_command_line("idle.",true);
}

void CAp2DView::key_esc(UINT nChar, bool& pass)
{
		//	esc();
	if(pass){
		return;
	}
	if(nChar == VK_ESCAPE){
			esc();
			pass = true;
	}
}
void CAp2DView::repeat_cmd()
{
	if(!repeat_cmd_){
		cmd_init();
		return;
	}
	(this->*repeat_cmd_)();
}

void CAp2DView::key_space(UINT nChar, bool& pass)
{
	if(pass){
		return;
	}
	if(nChar == VK_SPACE){
		repeat_cmd();
		pass = true;
	}
}

void CAp2DView::key_del(UINT nChar, bool& pass)
{
	if(pass){
		return;
	}
	if(nChar == VK_DELETE){
			OnButErase();
			pass = true;
	}
}


bool CAp2DView::deal_keydown(UINT nChar)
{
  bool pass = false;
	key_esc	 (nChar, pass);
	key_space(nChar, pass);
	key_del	 (nChar, pass);
//	ctrl_tab (nChar, pass);
//	hotkey(nChar, pass);

	return pass;
}
bool CAp2DView::hotkey(MSG* pMsg)
{
	if(!::IsWindow(GetSafeHwnd())){
		return false;
	}
	if(pMsg->message == WM_KEYDOWN){
    hk::Fptr<CAp2DView>::PF pf = hk::find<CAp2DView>(pMsg->wParam);
    if(pf){
      (this->*pf)();
      return true;
    }
  }
  return false;
}


BOOL CAp2DView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(hotkey(pMsg)){
		//啥时候让快捷键无效呢
	}else{
		if(pMsg->message == WM_KEYDOWN){
			if(pMsg->wParam != 16 && pMsg->wParam != 17){
				UINT nChar = pMsg->wParam;
				if(deal_keydown(nChar)){
					return TRUE;
				}
			}
		}
	}
	return CView::PreTranslateMessage(pMsg);
}

void CAp2DView::OnMenuOk() 
{
	// TODO: Add your command handler code here
	view_->scene()->ok();
	cmd_init();
	Global::instance()->mgr_toolbar().check_all_toolbar();	
}

void CAp2DView::OnMenuRepeat() 
{
	// TODO: Add your command handler code here
	if(!repeat_cmd_){
		cmd_init();
		return;
	}
	(this->*repeat_cmd_)();
}

void CAp2DView::OnMenuExitCmd() 
{
	// TODO: Add your command handler code here
	view_->scene()->cancel();
}

void CAp2DView::OnMenuPaste() 
{
	// TODO: Add your command handler code here
	OnButPaste();
}

void CAp2DView::OnMenuDelete() 
{
	// TODO: Add your command handler code here
	OnButErase();
}

void CAp2DView::OnMenuMove() 
{
	// TODO: Add your command handler code here
	OnButMove();
}

void CAp2DView::OnMenuCopy() 
{
	// TODO: Add your command handler code here
	OnButCopy();
}

void CAp2DView::OnMenuProp() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnMenuOrtho() 
{
	// TODO: Add your command handler code here
	OnButOrtho() ;
}

void CAp2DView::OnMenuMiddle() 
{
	// TODO: Add your command handler code here
	OnButSanpMidPt();
}

void CAp2DView::OnMenuEndPt() 
{
	// TODO: Add your command handler code here
	OnButSanpEndPt() ;
}

void CAp2DView::OnMenuCrossP() 
{
	// TODO: Add your command handler code here
	OnButSanpCrossPt();
}

void CAp2DView::OnMenuSnapAll() 
{
	// TODO: Add your command handler code here
	OnButSanpAll() ;
}

void CAp2DView::OnMenuPtInLine() 
{
	// TODO: Add your command handler code here
	OnButSanpLinePt();
}

void CAp2DView::OnMenuPrependiculiarWp() 
{
	// TODO: Add your command handler code here
	OnButSanpPerpendicular();
}

void CAp2DView::OnMenuPoint() 
{
	// TODO: Add your command handler code here
	OnButSanpPt();
}

void CAp2DView::OnToolShowLayer() 
{
	// TODO: Add your command handler code hereU
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	std::string layer_name = pM->get_layer_name();
	Ap_Layer aplayer;
	BOOL show = Global::instance()->db_detail().get_show(Global::instance()->get_cur_detail_name(),layer_name);

	show_ents_by_layer(DB_View::instance()->cur_view()->scene()->database(),layer_name,show);
	
	show = !show;

	Global::instance()->db_detail().edit_show(Global::instance()->get_cur_detail_name(),layer_name,show);
	pM->set_combo_toolbar(ID_TOOL_SHOW_LAYER,show);

	DB_View::instance()->cur_view()->scene()->invalidate();

	
}//

void CAp2DView::OnToolLockLayer() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnToolShowLayerP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnToolLockLayerP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnToolSelect() 
{
	// TODO: Add your command handler code here
	Cmd_Select* cmd = new Cmd_Select(*DB_View::instance()->cur_view()->scene());
	DB_View::instance()->cur_view()->scene()->attach_command(cmd);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_combo_toolbar(ID_TOOL_SELECT_P, pM->get_combo_layer_bar());
	repeat_cmd_ = &CAp2DView::OnButReverseColor;

}

void CAp2DView::OnToolSelectP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButDimTxt() 
{
	// TODO: Add your command handler code here
	set_edit();
	dlhml::Text_Dimension seed;
	
	seed.color_index(3);
	seed.layer_name(LAYER_AP_DIM);

	init_dim_text(seed);
	//seed.dim_text(get_select_txt(view_->scene()->database()));
	
	create_command(seed);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_TXT_P, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimTxt;
}
void CAp2DView::OnButDimTxtP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnUpdateButUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!DB_View::instance()->cur_view()->scene()->can_undo()){
		pCmdUI->Enable(FALSE);
	}
}

void CAp2DView::OnUpdateButRedo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!DB_View::instance()->cur_view()->scene()->can_redo()){
		pCmdUI->Enable(FALSE);
	}
	
}

void CAp2DView::OnButOneIn() 
{
	// TODO: Add your command handler code here
	Dlg_Compare_Dxf dlg;
	if(dlg.DoModal() == IDOK){

	}
}

bool g_show = false;
void CAp2DView::OnButReverseColor() 
{
	// TODO: Add your command handler code here
	g_show = !g_show;
	show_ents_part(Global::instance()->get_old_ents(),g_show);
	DB_View::instance()->cur_view()->scene()->invalidate();
	
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_combo_toolbar(ID_BUT_REVERSE_COLOR_P, pM->get_combo_layer_bar());
	repeat_cmd_ = &CAp2DView::OnButReverseColor;
	
	//	DB_View::instance()->cur_view()->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(0,0));
}

void CAp2DView::OnButOneInP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButReverseColorP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	if(pM){
		CPutBar* putbar = pM->command_line_bar();
		if(putbar){
			InEdit* edit = (InEdit*)(putbar->get_in());
			if(edit && nChar != VK_RETURN ){	////消息在InEdit::OnKeyDown()中处理
				edit->PostMessage(WM_CHAR,nChar,NULL);
				edit->SetFocus();
			}
		}
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CAp2DView::OnButCheckText() 
{
	// TODO: Add your command handler code here
	//Cmd_Check_Text* cmd = new Cmd_Check_Text(*DB_View::instance()->cur_view()->scene());
	Entitys sel_ents;
	get_select_ents(DB_View::instance()->database(),sel_ents);
	check_equ_text(DB_View::instance()->database(),sel_ents);
	DB_View::instance()->cur_view()->scene()->invalidate();

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_combo_toolbar(ID_BUT_CHECK_TEXT_P, pM->get_combo_layer_bar());
	repeat_cmd_ = &CAp2DView::OnButCheckText;

}


void CAp2DView::OnButCheckTextP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButSelectTextP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButShowSameText() 
{
	// TODO: Add your command handler code here
	Entitys sel_ents,texts;
	get_select_ents(DB_View::instance()->database(),sel_ents);
	get_texts(DB_View::instance()->database(),sel_ents,texts);
	show_equ_txts(DB_View::instance()->database(),texts);
	DB_View::instance()->cur_view()->scene()->invalidate();

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_combo_toolbar(ID_BUT_SHOW_SAME_TEXT_P, pM->get_combo_layer_bar());
	repeat_cmd_ = &CAp2DView::OnButShowSameText;
	
}

void CAp2DView::OnButShowSameTextP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButCreateReport() 
{
	// TODO: Add your command handler code here
	create_report(DB_View::instance()->cur_view()->scene()->database());
}

void CAp2DView::OnButCreateReportP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButShowAll() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButShowAllP() 
{
	// TODO: Add your command handler code here
	Entitys ents;
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	show_ents_part(ents,true);
	DB_View::instance()->cur_view()->scene()->invalidate();
}

void CAp2DView::OnButSelectFile0() 
{
	// TODO: Add your command handler code here
	select_ents_by_layer(DB_View::instance()->cur_view()->scene()->database(),true);
	DB_View::instance()->cur_view()->scene()->invalidate();
	
}

void CAp2DView::OnButton32812() 
{
	// TODO: Add your command handler code here
	reserve_select(DB_View::instance()->cur_view()->scene()->database());
	DB_View::instance()->cur_view()->scene()->invalidate();
}

void CAp2DView::OnButton32812P() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButSelectFile01() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnAppHelp() 
{
	// TODO: Add your command handler code here
	std::string help = exe_path()+"help.doc";
	::ShellExecute(NULL, "open", help.c_str(), "", "", SW_SHOW);
}

void CAp2DView::OnAppHelpP() 
{
	// TODO: Add your command handler code here
	
}
void CAp2DView::init_hotkey()
{
  hk::push_sec("Views");
	
  hk::push_key("Clear", &CAp2DView::OnButClear);

  hk::push_sec("Create Entity");
  hk::push_key("Create Line", &CAp2DView::OnButLine,'L');
	hk::push_key("Create Circle", &CAp2DView::OnButCircleP,'C');
	hk::push_key("Create Arc", &CAp2DView::OnButArcP,'A');
	hk::push_key("Create Circle", &CAp2DView::OnButCircleP,'C');
	hk::push_key("Create Spline", &CAp2DView::OnButSpline,'S');

	hk::push_key("Create Rect", &CAp2DView::OnButRect);
	hk::push_key("Create Polygon", &CAp2DView::OnButPolygon);
	hk::push_key("Insert Block", &CAp2DView::OnButInsertBlock);
	hk::push_key("Create Block", &CAp2DView::OnButSaveBlock);

	hk::push_key("Create DimLead", &CAp2DView::OnButDimLead);
	hk::push_key("Create Ortho Closed Dim", &CAp2DView::OnButDimOrthoClosed);
	hk::push_key("Create Dim Align Closed", &CAp2DView::OnButDimAlignClosed);
	hk::push_key("Create Dim Ortho Pileup", &CAp2DView::OnButDimOrthoPileup);
	hk::push_key("Create Dim Angle", &CAp2DView::OnButDimAngle);
	hk::push_key("Create Dim Radius", &CAp2DView::OnButDimRadius);
	
	hk::push_key("Create Dim Lead Info", &CAp2DView::OnButDimLeadInfo);
	hk::push_key("Create Dim Text Info", &CAp2DView::OnBUTDIMNAMENOlLINE);


  hk::push_sec("Edit Dim");
	hk::push_key("Move Dim Line", &CAp2DView::OnButMoveDimLine);
	hk::push_key("Move Layout Dim Line", &CAp2DView::OnButLayoutDimLine);
	hk::push_key("Add Dim Line", &CAp2DView::OnButAddDim);
	hk::push_key("Delete Dim Line", &CAp2DView::OnButDelDim);
	hk::push_key("Layout Dim", &CAp2DView::OnButLayoutDimBase);
	hk::push_key("Reset O", &CAp2DView::OnButDimRe0);

  hk::push_sec("Snaps");
	hk::push_key("Ortho", &CAp2DView::OnButOrtho);
	hk::push_key("Sanp EndPt", &CAp2DView::OnButSanpEndPt);
	hk::push_key("Snap CrossPt", &CAp2DView::OnButSanpCrossPt);
	hk::push_key("Snap LinePt", &CAp2DView::OnButSanpLinePt);
	hk::push_key("Snap MidPt", &CAp2DView::OnButSanpMidPt);
	hk::push_key("Snap Perpendicular", &CAp2DView::OnButSanpPerpendicular);
	hk::push_key("Snap CirclePt", &CAp2DView::OnButSnapCirclePt);
	hk::push_key("Snap Point", &CAp2DView::OnButSanpPt);
	hk::push_key("Snap All", &CAp2DView::OnButSanpAll);

  hk::push_sec("Edit");
	hk::push_key("Erase", &CAp2DView::OnButErase,'D');
	hk::push_key("Move", &CAp2DView::OnButMove,'M');
	hk::push_key("Copy", &CAp2DView::OnButCopy,'C');
	hk::push_key("Paste", &CAp2DView::OnButPaste,'P');
	hk::push_key("Array", &CAp2DView::OnButArray,'A');
	hk::push_key("Rotate", &CAp2DView::OnButRotate,'R');
	hk::push_key("Scale", &CAp2DView::OnButScale,'S');
	hk::push_key("Mirror", &CAp2DView::OnButMirror);
	hk::push_key("Decompose", &CAp2DView::OnButDecompose);
	hk::push_key("Offset", &CAp2DView::OnButOffset,'O');
	hk::push_key("Dim", &CAp2DView::OnButDim);
	hk::push_key("Trim", &CAp2DView::OnButTrim,'T');
	hk::push_key("Extend", &CAp2DView::OnButExtend,'E');
	hk::push_key("Break", &CAp2DView::OnButBreakP,'B');
	hk::push_key("Multibreak", &CAp2DView::OnButMultibreak);
	hk::push_key("Stretches", &CAp2DView::OnButStretchesP);
	
	hk::push_key("Undo", &CAp2DView::OnButUndo,'Z',true);
	hk::push_key("Redo", &CAp2DView::OnButRedo,'Y',true);
	
  hk::load(Global::instance()->get_hotkey_profile().c_str());
	hk::enable(true);
  
}

void CAp2DView::OnButBrush() 
{
	// TODO: Add your command handler code here
	set_edit();
	Entitys sel_ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);

	set_brush_prop(sel_ents,Global::instance()->cur_val().brush_prop_);


	//Global::instance()->get_detail_key(str);


}

void CAp2DView::OnButBrushP() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButImportNameInfo() 
{
	// TODO: Add your command handler code here
	set_edit();
	CString strFile,strName;
	static char szFilter[] = "DXF file format(*.txt) |*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL );
	dlg.m_ofn.lpstrTitle = "Open Txt File";
	if(dlg.DoModal()== IDOK){
		strFile=dlg.GetPathName();
		Model_DB::instance()->create_db(strFile);
		MessageBox("the model's infoes import OK.");
	}
}

void CAp2DView::OnButDimNameSet() 
{
	// TODO: Add your command handler code here
	Dlg_Dim_Name_Set dlg;
	if(dlg.DoModal() == IDOK){
		CStringArray strs_ary;
		dlg.get_dim_styles(strs_ary);
		Model_DB::instance()->set_dim_name_style(strs_ary);
		MessageBox("the dimstyles setting OK.");
	}


}

void CAp2DView::OnMenuNewFeatures() 
{
	// TODO: Add your command handler code here

	char  exepath[MAX_PATH];
    CString  strdir,tmpdir; 
	GetModuleFileName(NULL,exepath,MAX_PATH);
	tmpdir=exepath; 
    strdir=tmpdir.Left(tmpdir.ReverseFind('\\'));

	CString filename = "new_features.doc";
	filename = strdir + "\\" + filename;

	CStdioFile file;
	if( !file.Open( filename, CFile::modeCreate
       | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText ) ) 
	{
	   #ifdef _DEBUG
		  afxDump << "Unable to open file" << "\n";
	   #endif
	   exit( 1 );
	}
	else 
		file.Close();
  //	const char *filename1 = "new_features.doc";
	
	//system(filename1 );
	ShellExecute(NULL, "open", filename,NULL, NULL, SW_SHOW);
}

void CAp2DView::OnBUTDIMNAMENOlLINE() 
{
	// TODO: Add your command handler code here
	CString str_name;
	std::string name = get_select_txt(view_->scene()->database());
	CStringArray names_ary;
	Model_DB::instance()->get_names(names_ary);
	if(name == "" ||name == "Txt" ){
		Dlg_Select_Name dlg_name;
		dlg_name.set_names(names_ary);
		if(dlg_name.DoModal() == IDOK){
			str_name = dlg_name.get_name();
		}

	}else{
		str_name = name.c_str();
	}
	
	CStringArray strs_ary;
	Model_DB::instance()->get_dim_name_strs(str_name,strs_ary);

	int size2 = strs_ary.GetSize();


	std::vector<std::string> strs;

	//因为绘制的循序，此处需要反向字符串
	for(int i=strs_ary.GetSize()-1;i>=0;i--){
		strs.push_back(strs_ary[i].GetBuffer(0));
	}
	/*
	for(int i=0;i<strs_ary.GetSize();i++){
		strs.push_back(strs_ary[i].GetBuffer(0));
	}
	*/

	int size = strs.size();

	if(strs_ary.GetSize() == 0){
		//MessageBox("No infoes,please check the model.");
		return;
	}
	dlhml::Text_Dimension_Info seed;
	seed.layer_name(LAYER_AP_DIM);
	init_dim_text_info(seed);
	seed.set_dim_content(strs);

	//需要把整个的替换数据库都设置到Lead_Dimension_Info中，去准备替换
	std::vector<dlhml::Text_Rep_Obj> reps;
	DB_Text_Replace::instance()->get_obj_format(reps);
	seed.set_replace_db(reps);
	
	create_command(seed);

	
}

void init_ln_dim_direct(dlhml::Ln_Dim_Direct &seed)
{
	seed.line_style(Global::instance()->cur_val().page_common_.line_type_);
	seed.color_index(Global::instance()->cur_val().page_common_.color_);

	dlhml::Dimension_Style dim_style;

	seed.dim_text(Global::instance()->cur_val().page_text_.content_.c_str());
	dim_style = seed.dim_style_val();

	dim_style.text_height(Global::instance()->cur_val().page_text_.hight_);
	dim_style.text_color(Global::instance()->cur_val().page_text_.color_);
	dim_style.line_color(Global::instance()->cur_val().page_text_.frame_color_);


	dim_style.txt_frame(get_txt_frame(Global::instance()->cur_val().page_text_.frame_kind_.c_str()));
	dim_style.text_frame_color(Global::instance()->cur_val().page_text_.frame_color_);

	dim_style.arrow_style(get_arrow_style_by_name(Global::instance()->cur_val().page_arrow_.arrow_style_.c_str()));
	dim_style.arrow_size(Global::instance()->cur_val().page_arrow_.arrow_level_);

	double s = Global::instance()->cur_val().page_text_.precision_;
	dim_style.text_precision(Global::instance()->cur_val().page_text_.precision_);

	seed.dim_style_val(dim_style);


}

void CAp2DView::OnButDimLineDirect() 
{
	// TODO: Add your command handler code here

	dlhml::Ln_Dim_Direct seed;
	//init
	seed.color_index(1);
	seed.mode(dlhml::CLOSED_DIM);
	seed.rota(dlhml::ALIGN_DIM);
	seed.layer_name(LAYER_AP_DIM);

	init_ln_dim_direct(seed);


	create_command(seed);
	
	
}
static void init_ln_dim_plateside(dlhml::Ln_Dim_PlateSide &seed)
{
	seed.line_style(Global::instance()->cur_val().page_common_.line_type_);
	seed.color_index(Global::instance()->cur_val().page_common_.color_);

	dlhml::Dimension_Style dim_style;

	seed.dim_text(Global::instance()->cur_val().page_text_.content_.c_str());
	dim_style = seed.dim_style_val();

	dim_style.text_height(Global::instance()->cur_val().page_text_.hight_);
	dim_style.text_color(Global::instance()->cur_val().page_text_.color_);
	dim_style.line_color(Global::instance()->cur_val().page_text_.frame_color_);


	dim_style.txt_frame(get_txt_frame(Global::instance()->cur_val().page_text_.frame_kind_.c_str()));
	dim_style.text_frame_color(Global::instance()->cur_val().page_text_.frame_color_);

	dim_style.arrow_style(get_arrow_style_by_name(Global::instance()->cur_val().page_arrow_.arrow_style_.c_str()));
	dim_style.arrow_size(Global::instance()->cur_val().page_arrow_.arrow_level_);

	double s = Global::instance()->cur_val().page_text_.precision_;
	dim_style.text_precision(Global::instance()->cur_val().page_text_.precision_);

	seed.dim_style_val(dim_style);


}

void CAp2DView::OnButDimLinePlateSide() 
{
	// TODO: Add your command handler code here
//	create_ln_dim(dlhml::CLOSED_DIM, dlhml::ALIGN_DIM);
	dlhml::Ln_Dim_PlateSide seed;
	//init
	seed.color_index(1);
	seed.mode(dlhml::CLOSED_DIM);
	seed.rota(dlhml::ALIGN_DIM);
	seed.layer_name(LAYER_AP_DIM);

//	init_ln_dim_plateside(seed);


	//create_command(seed);
	
}

void CAp2DView::OnButSetReplaceSign() 
{
	// TODO: Add your command handler code here
	Dlg_Sign_Replace dlg;
	dlg.DoModal();
}




void CAp2DView::OnButCreateBlockNew() 
{
	// TODO: Add your command handler code here	
	cmd_init();

	Dlg_Input in;
	in.str_ = "blk1";
	if(in.DoModal()!=IDOK)
		return;
	CString block_name = in.val_.c_str();
	if(block_name == "")
		return;

	DB_Blocks::instance()->set_cur_name(block_name.GetBuffer(0));
	
	std::vector<dlhml::Entity*> ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	std::string exe = exe_path()+"blk\\";
	afc::dir::create_floder(exe.c_str());

	CStringArray files;
	get_files_in_path(exe.c_str(),"blk",files);



	CString str = exe.c_str()+block_name+".blk";
	save_lua(str.GetBuffer(0),ents);

	
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_SAVE_BLOCK, pM->get_create_bar());
	view_->scene()->make_block();
	repeat_cmd_ = &CAp2DView::OnButSaveBlock;
	
}


void CAp2DView::OnButInsertBlockPp() 
{
	// TODO: Add your command handler code here
 	cmd_init();
	Dlg_Block_Manage dlg;
	dlg.DoModal();
		
}

void CAp2DView::OnButInsertBlockP222p() 
{
	// TODO: Add your command handler code here
	Dlg_Block_Manage dlg;
	dlg.DoModal();
	
}

void CAp2DView::OnButInsertBlock111() 
{
	// TODO: Add your command handler code here
 	cmd_init();

	Cmd_Insert_Block* cmd = new Cmd_Insert_Block(*DB_View::instance()->cur_view()->scene());
	DB_View::instance()->cur_view()->scene()->attach_command(cmd);
	
}

void CAp2DView::OnButInsertBlock222() 
{
	// TODO: Add your command handler code here
	Dlg_Block_Manage dlg;
	dlg.DoModal();
	
}

void CAp2DView::OnButHotkeyRei() 
{
	// TODO: Add your command handler code here
	Dlg_Hot_Key dlg;
	dlg.DoModal();

}

void CAp2DView::OnButCutDimLine() 
{
	// TODO: Add your command handler code here
	
}
////////////////////////////////////////////////////////////////////

void CAp2DView::OnMenuViewLine() 
{
	// TODO: Add your command handler code here
	OnButLine();
}

void CAp2DView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	OnButUndo();
}

void CAp2DView::OnEditRedo() 
{
	// TODO: Add your command handler code here
	OnButRedo();
}

void CAp2DView::OnMenuErase() 
{
	// TODO: Add your command handler code here
	OnButErase();
}

void CAp2DView::OnMenuViewPaste() 
{
	// TODO: Add your command handler code here
	OnButPaste();
}

void CAp2DView::OnMenuViewArray() 
{
	// TODO: Add your command handler code here
	OnButArray();
}

void CAp2DView::OnMenuViewRotate() 
{
	// TODO: Add your command handler code here
	OnButRotate();
}

void CAp2DView::OnMenuViewScale() 
{
	// TODO: Add your command handler code here
	OnButScale();
}

void CAp2DView::OnMenuViewMirror() 
{
	// TODO: Add your command handler code here
	OnButMirror();
}

void CAp2DView::OnMenuViewBreak() 
{
	// TODO: Add your command handler code here
	OnButDecompose();
}

void CAp2DView::OnMenuViewOffset() 
{
	// TODO: Add your command handler code here
	OnButOffset();
}

void CAp2DView::OnMenuViewDim() 
{
	// TODO: Add your command handler code here
	OnButDim();
}

void CAp2DView::OnMenuViewTrim() 
{
	// TODO: Add your command handler code here
	OnButTrim();
}

void CAp2DView::OnMenuViewExtend() 
{
	// TODO: Add your command handler code here
	OnButExtend();
}

void CAp2DView::OnMenuViewCut() 
{
	// TODO: Add your command handler code here
//	OnButBreakP();
}

void CAp2DView::OnMenuViewMultiCut() 
{
	// TODO: Add your command handler code here
//	OnButMultibreak();
}

void CAp2DView::OnMenuViewStretches() 
{
	// TODO: Add your command handler code here
	OnButStretchesP();
}

void CAp2DView::OnMenuViewCircle() 
{
	// TODO: Add your command handler code here
	OnButCircleP();
}

void CAp2DView::OnMenuViewArc() 
{
	// TODO: Add your command handler code here
	OnButArcP();
}

void CAp2DView::OnMenuViewSpline() 
{
	// TODO: Add your command handler code here
	OnButSpline();
}

void CAp2DView::OnMenuViewRect() 
{
	// TODO: Add your command handler code here
	OnButRect();
}

void CAp2DView::OnMenuViewPolygon() 
{
	// TODO: Add your command handler code here
	OnButPolygon();
}

void CAp2DView::OnMenuViewText() 
{
	// TODO: Add your command handler code here
	OnButDimTxtP();
}

void CAp2DView::OnMenuViewCrateBlock() 
{
	// TODO: Add your command handler code here
	OnButCreateBlockNew();
}

void CAp2DView::OnMenuViewInsertBlock() 
{
	// TODO: Add your command handler code here
	OnButInsertBlock222();
}

void CAp2DView::OnMenuViewDimLead() 
{
	// TODO: Add your command handler code here
	OnButDimLead();
}

void CAp2DView::OnMenuViewOrthoClosed() 
{
	// TODO: Add your command handler code here
	OnButDimOrthoClosed();
}

void CAp2DView::OnMenuViewAlignClosed() 
{
	// TODO: Add your command handler code here
	OnButDimAlignClosed();
}

void CAp2DView::OnMenuViewOrthoPipeup() 
{
	// TODO: Add your command handler code here
	OnButDimOrthoPileup();
}

void CAp2DView::OnMenuViewAlignPipeup() 
{
	// TODO: Add your command handler code here
	OnButDimAlignPileup();
}

void CAp2DView::OnMenuViewDimAngle() 
{
	// TODO: Add your command handler code here
	OnButDimAngle();
}

void CAp2DView::OnMenuViewDimRadious() 
{
	// TODO: Add your command handler code here
	OnButDimRadius();
}

void CAp2DView::OnMenuViewDimLeadInfo() 
{
	// TODO: Add your command handler code here
	OnButDimLeadInfo();
}

void CAp2DView::OnMenuViewDimTextInfo() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnMenuViewDimPlateside() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnMenuViewDimDirectLine() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnMenuViewMoveDim() 
{
	// TODO: Add your command handler code here
	OnButMoveDimLine();
}

void CAp2DView::OnMenuViewMoveSigneDim() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnMenuViewAddDim() 
{
	// TODO: Add your command handler code here
	OnButAddDim();
}

void CAp2DView::OnMenuViewDelDim() 
{
	// TODO: Add your command handler code here
	OnButDelDim();
}

void CAp2DView::OnMenuViewCutDimLine() 
{
	// TODO: Add your command handler code here
	OnButCutDimLine();
}

void CAp2DView::OnMenuViewChangeDim0() 
{
	// TODO: Add your command handler code here
	OnButDimRe0();
}

void CAp2DView::OnMenuViewCutDimLineNoSide() 
{
	// TODO: Add your command handler code here
	OnMenuViewCutDimLineNoSide();
}

void CAp2DView::OnMenuViewOrtho() 
{
	// TODO: Add your command handler code here
	OnButOrtho();
}

void CAp2DView::OnMenuViewEndPt() 
{
	// TODO: Add your command handler code here
	OnButSanpEndPt();
}

void CAp2DView::OnMenuViewCrossPt() 
{
	// TODO: Add your command handler code here
	OnButSanpCrossPt();
}

void CAp2DView::OnMenuViewPtInLine() 
{
	// TODO: Add your command handler code here
	OnButSanpLinePt();
}

void CAp2DView::OnMenuViewMiddle() 
{
	// TODO: Add your command handler code here
	OnButSanpMidPt();
}

void CAp2DView::OnMenuViewPerpendicular() 
{
	// TODO: Add your command handler code here
	OnButSanpPerpendicular();
}

void CAp2DView::OnMenuViewCenter() 
{
	// TODO: Add your command handler code here
	OnButSnapCirclePt();
}

void CAp2DView::OnMenuViewPt() 
{
	// TODO: Add your command handler code here
	OnButSanpPt();
}

void CAp2DView::OnMenuViewAll() 
{
	// TODO: Add your command handler code here
	OnButSanpAll();
}

void CAp2DView::OnMenuViewReplaceString() 
{
	// TODO: Add your command handler code here
	OnButSetReplaceSign();
}

void CAp2DView::OnMenuViewHotkey() 
{
	// TODO: Add your command handler code here
	OnButHotkeyRei();
}

void CAp2DView::OnMenuViewImportPartlist() 
{
	// TODO: Add your command handler code here
	OnButImportNameInfo();
}

void CAp2DView::OnMenuViewImportSetDimNameStyle() 
{
	// TODO: Add your command handler code here
	OnButDimNameSet();
}

void CAp2DView::OnButFindTool() 
{
	// TODO: Add your command handler code here
	Dlg_Find_Tool dlg;
	dlg.DoModal();
}

void CAp2DView::OnButSelectHide() 
{
	// TODO: Add your command handler code here
	DB_View::instance()->cur_view()->scene()->idle_command();
	std::vector<dlhml::Entity*> sel_ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);
	for(int i=0;i<sel_ents.size();i++){
		sel_ents[i]->visibility(false);
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
	repeat_cmd_ = &CAp2DView::OnButSelectHide;
	
}

void CAp2DView::OnButSelectShow() 
{
	// TODO: Add your command handler code here
	DB_View::instance()->cur_view()->scene()->idle_command();

	std::vector<dlhml::Entity*> ents,sel_ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	for(int i=0;i<ents.size();i++){
		std::vector<dlhml::Entity*>::iterator iter = std::find(sel_ents.begin(),sel_ents.end(),ents[i]);
		if(iter != sel_ents.end())
			ents[i]->visibility(true);
		else
			ents[i]->visibility(false);
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
	repeat_cmd_ = &CAp2DView::OnButSelectShow;
	
}

void CAp2DView::OnButSelectReverse() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButSelectShowall() 
{
	// TODO: Add your command handler code here
	DB_View::instance()->cur_view()->scene()->idle_command();
	std::vector<dlhml::Entity*> ents;
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	for(int i=0;i<ents.size();i++){
		ents[i]->visibility(true);
	}
	DB_View::instance()->cur_view()->scene()->invalidate();	
	repeat_cmd_ = &CAp2DView::OnButSelectShowall;
	
}

void CAp2DView::OnButSelectReverseP() 
{
	// TODO: Add your command handler code here
	DB_View::instance()->cur_view()->scene()->idle_command();

	std::vector<dlhml::Entity*> ents,sel_ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	for(int i=0;i<ents.size();i++){
		std::vector<dlhml::Entity*>::iterator iter = std::find(sel_ents.begin(),sel_ents.end(),ents[i]);
		if(iter != sel_ents.end())
			DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(ents[i]);
		else
			DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(ents[i]);
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
	repeat_cmd_ = &CAp2DView::OnButSelectReverse;
	
}

void CAp2DView::OnButSelectTableText() 
{
	// TODO: Add your command handler code here
	std::vector<dlhml::Entity*> ents,sel_ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),sel_ents);
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	int states = 0;
	if (sel_ents.size() <= 0)
		AfxMessageBox("Select None!");
	else
	{
		Dlg_Select_Table_Text *dlg  = new Dlg_Select_Table_Text();
		dlg->set_sel_ifo(sel_ents,ents,dlg);
		dlg->Create(IDD_DLG_SELECT_TABLE_TEXT);
		dlg->ShowWindow(SW_SHOW);
	}
	
}


void CAp2DView::OnButSelectText() 
{
	// TODO: Add your command handler code here

	Global::instance()->cur_val().cur_select_text_ = true;

	Cmd_Select_Text* cmd = new Cmd_Select_Text(*DB_View::instance()->cur_view()->scene());
	DB_View::instance()->cur_view()->scene()->attach_command(cmd);

	//CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	//Global::instance()->mgr_toolbar().check_combo_toolbar(ID_BUT_SELECT_TEXT_P, pM->get_combo_layer_bar());
	//repeat_cmd_ = &CAp2DView::OnButSelectText;


}

void CAp2DView::OnButSelectTextSignal() 
{
	// TODO: Add your command handler code here
	Global::instance()->cur_val().cur_select_text_ = false;
	Cmd_Select_Text* cmd = new Cmd_Select_Text(*DB_View::instance()->cur_view()->scene());
	DB_View::instance()->cur_view()->scene()->attach_command(cmd);

	//CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	//Global::instance()->mgr_toolbar().check_combo_toolbar(ID_BUT_SELECT_TEXT_P, pM->get_combo_layer_bar());
	repeat_cmd_ = &CAp2DView::OnButSelectTextSignal;

	
}

void CAp2DView::OnButSelectJishou() 
{
	// TODO: Add your command handler code here
	Global::instance()->cur_val().cur_select_text_ = false;

	//Cmd_Select_Joint* cmd = new Cmd_Select_Joint(*DB_View::instance()->cur_view()->scene());


	if (sel_joint_){
		if (!sel_joint_->get_message())
			sel_joint_ = new Cmd_Select_Joint(*DB_View::instance()->cur_view()->scene());
	}
	else
			sel_joint_ = new Cmd_Select_Joint(*DB_View::instance()->cur_view()->scene());
	//sel_joint_ = new Cmd_Select_Joint(*DB_View::instance()->cur_view()->scene());
	DB_View::instance()->cur_view()->scene()->attach_command(sel_joint_);

	//CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	//Global::instance()->mgr_toolbar().check_combo_toolbar(ID_BUT_SELECT_TEXT_P, pM->get_combo_layer_bar());
	repeat_cmd_ = &CAp2DView::OnButSelectJishou;




}



void CAp2DView::OnButDrawExtendLine() 
{
	// TODO: Add your command handler code here
	set_edit();
	Global::instance()->cur_val().cur_select_text_ = false;
	Cmd_Extend_Line* cmd = new Cmd_Extend_Line(*DB_View::instance()->cur_view()->scene());
	DB_View::instance()->cur_view()->scene()->attach_command(cmd);

	//CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	//Global::instance()->mgr_toolbar().check_combo_toolbar(ID_BUT_SELECT_TEXT_P, pM->get_combo_layer_bar());
	repeat_cmd_ = &CAp2DView::OnButDrawExtendLine;


	
}

void CAp2DView::OnButJointdb() 
{
	// TODO: Add your command handler code here/
	Dlg_Joint_DB_Edit dlg;
	dlg.DoModal();


	
}

void CAp2DView::OnButAutoCheck() 
{
	// TODO: Add your command handler code here
	Dlg_Auto_Check_Main dlg;
	dlg.DoModal();
}

void CAp2DView::OnButReplaceMatrail() 
{
	// TODO: Add your command handler code here
	Dlg_Sign_Replace dlg;
	dlg.DoModal();
}

void CAp2DView::OnButCombination() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnButFindCenter() 
{
	// TODO: Add your command handler code here
	cmd_init();
	Cmd_Draw_Center *cmd = new Cmd_Draw_Center(*DB_View::instance()->cur_view()->scene());
	DB_View::instance()->cur_view()->scene()->attach_command(cmd);

	
	repeat_cmd_ = &CAp2DView::OnButFindCenter;
	
	
}

void CAp2DView::OnButFindMid() 
{
	// TODO: Add your command handler code here
	cmd_init();
	Cmd_Draw_Middle *cmd = new Cmd_Draw_Middle(*DB_View::instance()->cur_view()->scene());
	DB_View::instance()->cur_view()->scene()->attach_command(cmd);

	
	repeat_cmd_ = &CAp2DView::OnButFindMid;
	
}

void CAp2DView::OnButDimSolpe() 
{
	// TODO: Add your command handler code here

	cmd_init();
//	Cmd_Dim_Solpe *cmd = new Cmd_Dim_Solpe(*DB_View::instance()->cur_view()->scene());
//	DB_View::instance()->cur_view()->scene()->attach_command(cmd);
	dlhml::Dim_Angle seed;
	seed.group(LAYER_AP_DIM);
	create_basic_entity(seed);
	seed.line_style(Global::instance()->cur_val().page_common_.line_type_);
	seed.color_index(Global::instance()->cur_val().page_common_.color_);
	repeat_cmd_ = &CAp2DView::OnButDimSolpe;

/*
	cmd_init();
	dlhml::Dim_Angle_Lean seed;
	seed.group(USER_ADD_ENTS);
	create_basic_entity(seed);

//	init_line_arrow(seed);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_LINE, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButLine;
	view_->scene()->invalidate();
	*/
}

void CAp2DView::OnButCancelCombination() 
{
	// TODO: Add your command handler code here
	
}

void CAp2DView::OnMenuSetup() 
{
	// TODO: Add your command handler code here
//	Dlg_Setup dlg;
//	dlg.DoModal();

	Dlg_Setting setting;
	setting.DoModal();

}

void CAp2DView::OnButDimLineLead() 
{
	// TODO: Add your command handler code here
	set_edit();
	dlhml::Lead_Line_Dim seed;

	seed.color_index(3);
	seed.layer_name(LAYER_AP_DIM);

	// init_dim_lead(seed);
	seed.dim_text(get_select_txt(view_->scene()->database()));

	create_command(seed);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	Global::instance()->mgr_toolbar().check_create_toolbar(ID_BUT_DIM_LINE_LEAD, pM->get_create_bar());
	repeat_cmd_ = &CAp2DView::OnButDimLead;

}
