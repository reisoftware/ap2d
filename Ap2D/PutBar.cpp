// PutBar.cpp: implementation of the CPutBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PutBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CPutBar, baseBar)
	//{{AFX_MSG_MAP(CMyBar)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPutBar::CPutBar()
{
}

CPutBar::~CPutBar()
{

}
void CPutBar::create_edit()
{
	ASSERT(::IsWindow(GetSafeHwnd()));
	CRect rc;
	in_.Create(WS_CHILD|WS_VISIBLE|ES_WANTRETURN |ES_MULTILINE   ,rc,this,1);
	CFont *pFont=CFont::FromHandle((HFONT)::GetStockObject(ANSI_VAR_FONT));
	in_.SetFont(pFont);
	out_.Create(WS_CHILD|WS_VISIBLE|ES_MULTILINE|WS_VSCROLL,rc,this,1);
	out_.SetFont(pFont);

	tip_.Create(WS_CHILD|WS_VISIBLE|ES_READONLY,rc,this,1);
	tip_.SetFont(pFont);
	tip_.SetWindowText("Command : ");
}
CEdit* CPutBar::get_in()
{
	return &in_;
}
CEdit* CPutBar::get_out()
{
	return &out_;
}
int CPutBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (baseBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	return 0;
}

void CPutBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
//	baseBar::OnLButtonDblClk(nFlags, point);
}
//

void CPutBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	baseBar::OnLButtonDown(nFlags, point);
}
//

void CPutBar::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(::IsWindow(in_.GetSafeHwnd()) && 
		::IsWindow(out_.GetSafeHwnd()) &&
		::IsWindow(tip_.GetSafeHwnd())){
		int height = 18;
		int width = 55;
		tip_.MoveWindow(0,cy-height,width,height);
		in_.MoveWindow(width,cy-height,cx-width,height);
		out_.MoveWindow(0,0,cx,cy-height-1);
	}
}
void CPutBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect(&rc,RGB(255,255,255));
	dc.MoveTo(rc.left,rc.bottom-19);
	dc.LineTo(rc.right,rc.bottom-19);
	// Do not call CWnd::OnPaint() for painting messages
}
