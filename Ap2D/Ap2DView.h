// Ap2DView.h : interface of the CAp2DView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AP2DVIEW_H__680256F5_B513_454E_81A4_4A8A7E075139__INCLUDED_)
#define AFX_AP2DVIEW_H__680256F5_B513_454E_81A4_4A8A7E075139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "scene_d.h"
#include "View.h"
#include "Ap2DDoc.h"
#include <string>
#include "Vis_Ent_Dblclk.h"
#include "Model_DB.h"

#include "Cmd_Select_Joint.h"

struct Layer_Show
{
	bool part_;
	bool sheet_;
	bool cut_;
	bool view_;
	bool dim_;
	bool mark_;
	bool apdim_;
};




class CAp2DView : public CView
{
protected: // create from serialization only
	CAp2DView();
	DECLARE_DYNCREATE(CAp2DView)

// Attributes
public:
	CAp2DDoc* GetDocument();
	
	View* get_view(){return view_;}
	void set_view(View *v);
	

	static void init_hotkey();


// Operations
public:
	View *view_;
	Cmd_Select_Joint* sel_joint_; 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAp2DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAp2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	Vis_Ent_Dblclk vis_ent_dblckl_;
	void (CAp2DView::*repeat_cmd_)();		////µ±«∞√¸¡Ó
	void cmd_init();

	void create_ln_dim(int mode, int rota);
	void create_basic_entity(dlhml::Entity& seed);
	void create_command(dlhml::Entity& seed);

	Layer_Show layer_show_;
	void show_ents(std::string layer_name,bool &show,UINT id);


	void key_esc(UINT nChar, bool& pass);
	void key_space(UINT nChar, bool& pass);
	void key_del(UINT nChar, bool& pass);
	bool deal_keydown(UINT nChar);
	void esc();

	void load_menu();

	void repeat_cmd();

	bool hotkey(MSG* pMsg);

	Model_DB model_db_;

	bool b_eidt_;
	void set_edit();
// Generated message map functions
protected:
	//{{AFX_MSG(CAp2DView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButDxfOut();
	afx_msg void OnButDxfIn();
	afx_msg void OnButErase();
	afx_msg void OnButMove();
	afx_msg void OnButCopy();
	afx_msg void OnButPaste();
	afx_msg void OnButArray();
	afx_msg void OnButRotate();
	afx_msg void OnButScale();
	afx_msg void OnButMirror();
	afx_msg void OnButDecompose();
	afx_msg void OnButOffset();
	afx_msg void OnButDim();
	afx_msg void OnButTrim();
	afx_msg void OnButExtend();
	afx_msg void OnButBreakP();
	afx_msg void OnButMultibreak();
	afx_msg void OnButStretchesP();
	afx_msg void OnButUndo();
	afx_msg void OnButRedo();
	afx_msg void OnButTrimCadP();
	afx_msg void OnButLine();
	afx_msg void OnButCircleP();
	afx_msg void OnButArcP();
	afx_msg void OnButSpline();
	afx_msg void OnButRect();
	afx_msg void OnButPolygon();
	afx_msg void OnButInsertBlock();
	afx_msg void OnButSaveBlock();
	afx_msg void OnButDimLead();
	afx_msg void OnButDimOrthoClosed();
	afx_msg void OnButDimAlignClosed();
	afx_msg void OnButDimAlignPileup();
	afx_msg void OnButDimOrthoPileup();
	afx_msg void OnButDimAngle();
	afx_msg void OnButDimRadius();
	afx_msg void OnButMoveDimLine();
	afx_msg void OnButLayoutDimLine();
	afx_msg void OnButAddDim();
	afx_msg void OnButDelDim();
	afx_msg void OnButLayoutDimBase();
	afx_msg void OnButDimRe0();
	afx_msg void OnButOrtho();
	afx_msg void OnButSanpEndPt();
	afx_msg void OnButSanpCrossPt();
	afx_msg void OnButSanpLinePt();
	afx_msg void OnButSanpMidPt();
	afx_msg void OnButSanpPerpendicular();
	afx_msg void OnButSnapCirclePt();
	afx_msg void OnButSanpPt();
	afx_msg void OnButSanpAll();
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButLayerPart();
	afx_msg void OnButLayerSheet();
	afx_msg void OnButLayerApdim();
	afx_msg void OnButLayerCut();
	afx_msg void OnButLayerDim();
	afx_msg void OnButLayerMark();
	afx_msg void OnButLayerView();
	afx_msg void OnButClear();
	afx_msg void OnButCadEe();
	afx_msg void OnButCreateXz();
	afx_msg void OnButCadWw();
	afx_msg void OnButMergeName();
	afx_msg void OnButCutTable();
	afx_msg void OnMenuOk();
	afx_msg void OnMenuRepeat();
	afx_msg void OnMenuExitCmd();
	afx_msg void OnMenuPaste();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuMove();
	afx_msg void OnMenuCopy();
	afx_msg void OnMenuProp();
	afx_msg void OnMenuOrtho();
	afx_msg void OnMenuMiddle();
	afx_msg void OnMenuEndPt();
	afx_msg void OnMenuCrossP();
	afx_msg void OnMenuSnapAll();
	afx_msg void OnMenuPtInLine();
	afx_msg void OnMenuPrependiculiarWp();
	afx_msg void OnMenuPoint();
	afx_msg void OnToolShowLayer();
	afx_msg void OnToolLockLayer();
	afx_msg void OnToolShowLayerP();
	afx_msg void OnToolLockLayerP();
	afx_msg void OnToolSelect();
	afx_msg void OnToolSelectP();
	afx_msg void OnButDimTxt();
	afx_msg void OnButDimTxtP();
	afx_msg void OnUpdateButUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButRedo(CCmdUI* pCmdUI);
	afx_msg void OnButOneIn();
	afx_msg void OnButReverseColor();
	afx_msg void OnButOneInP();
	afx_msg void OnButReverseColorP();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnButCheckText();
	afx_msg void OnButSelectText();
	afx_msg void OnButCheckTextP();
	afx_msg void OnButSelectTextP();
	afx_msg void OnButShowSameText();
	afx_msg void OnButShowSameTextP();
	afx_msg void OnButCreateReport();
	afx_msg void OnButCreateReportP();
	afx_msg void OnButShowAll();
	afx_msg void OnButShowAllP();
	afx_msg void OnButSelectFile0();
	afx_msg void OnButton32812();
	afx_msg void OnButton32812P();
	afx_msg void OnButSelectFile01();
	afx_msg void OnAppHelp();
	afx_msg void OnAppHelpP();
	afx_msg void OnButBrush();
	afx_msg void OnButBrushP();
	afx_msg void OnButImportNameInfo();
	afx_msg void OnButDimLeadInfo();
	afx_msg void OnButDimNameSet();
	afx_msg void OnMenuNewFeatures();
	afx_msg void OnBUTDIMNAMENOlLINE();
	afx_msg void OnButDimLineDirect();
	afx_msg void OnButSetReplaceSign();
	afx_msg void OnButDimLinePlateSide();
	afx_msg void OnButCreateBlockNew();
	afx_msg void OnButInsertBlockPp();
	afx_msg void OnButInsertBlockP222p();
	afx_msg void OnButInsertBlock111();
	afx_msg void OnButInsertBlock222();
	afx_msg void OnButHotkeyRei();
	afx_msg void OnButCutDimLine();
	afx_msg void OnMenuViewLine();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnMenuErase();
	afx_msg void OnMenuViewPaste();
	afx_msg void OnMenuViewArray();
	afx_msg void OnMenuViewRotate();
	afx_msg void OnMenuViewScale();
	afx_msg void OnMenuViewMirror();
	afx_msg void OnMenuViewBreak();
	afx_msg void OnMenuViewOffset();
	afx_msg void OnMenuViewDim();
	afx_msg void OnMenuViewTrim();
	afx_msg void OnMenuViewExtend();
	afx_msg void OnMenuViewCut();
	afx_msg void OnMenuViewMultiCut();
	afx_msg void OnMenuViewStretches();
	afx_msg void OnMenuViewCircle();
	afx_msg void OnMenuViewArc();
	afx_msg void OnMenuViewSpline();
	afx_msg void OnMenuViewRect();
	afx_msg void OnMenuViewPolygon();
	afx_msg void OnMenuViewText();
	afx_msg void OnMenuViewCrateBlock();
	afx_msg void OnMenuViewInsertBlock();
	afx_msg void OnMenuViewDimLead();
	afx_msg void OnMenuViewOrthoClosed();
	afx_msg void OnMenuViewAlignClosed();
	afx_msg void OnMenuViewOrthoPipeup();
	afx_msg void OnMenuViewAlignPipeup();
	afx_msg void OnMenuViewDimAngle();
	afx_msg void OnMenuViewDimRadious();
	afx_msg void OnMenuViewDimLeadInfo();
	afx_msg void OnMenuViewDimTextInfo();
	afx_msg void OnMenuViewDimPlateside();
	afx_msg void OnMenuViewDimDirectLine();
	afx_msg void OnMenuViewMoveDim();
	afx_msg void OnMenuViewMoveSigneDim();
	afx_msg void OnMenuViewAddDim();
	afx_msg void OnMenuViewDelDim();
	afx_msg void OnMenuViewCutDimLine();
	afx_msg void OnMenuViewChangeDim0();
	afx_msg void OnMenuViewCutDimLineNoSide();
	afx_msg void OnMenuViewOrtho();
	afx_msg void OnMenuViewEndPt();
	afx_msg void OnMenuViewCrossPt();
	afx_msg void OnMenuViewPtInLine();
	afx_msg void OnMenuViewMiddle();
	afx_msg void OnMenuViewPerpendicular();
	afx_msg void OnMenuViewCenter();
	afx_msg void OnMenuViewPt();
	afx_msg void OnMenuViewAll();
	afx_msg void OnMenuViewReplaceString();
	afx_msg void OnMenuViewHotkey();
	afx_msg void OnMenuViewImportPartlist();
	afx_msg void OnMenuViewImportSetDimNameStyle();
	afx_msg void OnButFindTool();
	afx_msg void OnButSelectHide();
	afx_msg void OnButSelectShow();
	afx_msg void OnButSelectReverse();
	afx_msg void OnButSelectShowall();
	afx_msg void OnButSelectReverseP();
	afx_msg void OnButSelectTableText();
	afx_msg void OnButSelectTextSignal();
	afx_msg void OnButSelectJishou();
	afx_msg void OnButDrawExtendLine();
	afx_msg void OnButJointdb();
	afx_msg void OnButAutoCheck();
	afx_msg void OnButReplaceMatrail();
	afx_msg void OnButCombination();
	afx_msg void OnButFindCenter();
	afx_msg void OnButFindMid();
	afx_msg void OnButDimSolpe();
	afx_msg void OnButCancelCombination();
	afx_msg void OnMenuSetup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ap2DView.cpp
inline CAp2DDoc* CAp2DView::GetDocument()
   { return (CAp2DDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AP2DVIEW_H__680256F5_B513_454E_81A4_4A8A7E075139__INCLUDED_)
