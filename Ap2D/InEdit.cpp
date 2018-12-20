// InEdit.cpp : implementation file
//

#include "stdafx.h"
#include "InEdit.h"
#include "MainFrm.h"

#include <cassert>

#include "Scene_d.h"
#include "ap2dView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InEdit

InEdit::InEdit()
{
}

InEdit::~InEdit()
{
}


BEGIN_MESSAGE_MAP(InEdit, CEdit)
	//{{AFX_MSG_MAP(InEdit)
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InEdit message handlers

void InEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
}

void InEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	TRACE_OUT("\n#### InEdit::OnKeyDown %c, ASCII: %d\n", nChar, nChar);
	//TRACE_OUT("\n#### InEdit::OnKeyDown \n");
	// TODO: Add your message handler code here and/or call default

	CMainFrame * mf = static_cast<CMainFrame*>(AfxGetMainWnd());
	assert(mf && "InEdit::OnKeyDown()");
	CMDIChildWnd * cw = static_cast<CMDIChildWnd*>(mf->GetActiveFrame());
	if(!cw){
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}
	CAp2DView * apv = static_cast<CAp2DView*>(cw->GetActiveView());
	if(!apv){
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}
	dlhml::Scene * scn = apv->get_view()->scene();
	assert(scn && "InEdit::OnKeyDown()");

	if(nChar == VK_RETURN){
		scn->cmdin();
		apv->SetFocus();
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}

	if(nChar == VK_ESCAPE){
		apv->SetFocus();
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}


	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void InEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	TRACE_OUT("\n#### InEdit::OnChar %c, ASCII: %d\n", nChar, nChar);
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void InEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	TRACE_OUT("\n#### InEdit::OnKeyUp %c, ASCII: %d\n", nChar, nChar);
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL InEdit::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_CHAR){
//		TRACE_OUT("\n#### InEdit::PreTranslateMessage %c, ASCII: %d\n", pMsg->wParam, pMsg->wParam);
		//NOOK 临时输出，仍然未能解决WM_CHAR ‘p’不能接收的问题
// 		UGLYCODE
// 		if(pMsg->wParam == 'p'){
// 			CString str;
// 			GetWindowText(str);
// 			str += "p";
// 			SetWindowText(str);
// 		}
	}
	// TODO: Add your specialized code here and/or call the base class
	
	return CEdit::PreTranslateMessage(pMsg);
}
