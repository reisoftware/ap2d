// Color_ComboBox.cpp : implementation file
//


#include "stdafx.h"
#include "Color_ComboBox.h"

#include "Color.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Color_ComboBox

Color_ComboBox::Color_ComboBox()
{
	//当前鼠标是否在对象上
	m_bOverControl = false;
	color_index_ = 0;
	//小图标尺寸
	iIconX = ::GetSystemMetrics(SM_CXSMICON);
	iIconY = ::GetSystemMetrics(SM_CYSMICON);	
}

Color_ComboBox::~Color_ComboBox()
{
	while(!m_crItem.IsEmpty())
	{
		LPBSCBITEM lpItem = m_crItem.RemoveHead();		
		delete lpItem;
	}

//	delete red_;
//	delete yellow_;
//	delete green_;
//	delete cyan_;
//	delete blue_;
//	delete fuchsin_;
//	delete write_;
//	delete black_;
	
}


BEGIN_MESSAGE_MAP(Color_ComboBox, CComboBox)
	//{{AFX_MSG_MAP(Color_ComboBox)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelendok)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

// Color_ComboBox message handlers
BOOL Color_ComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	DWORD dw = dwStyle;
	//dw |= CBS_OWNERDRAWVARIABLE;
	
	if( !CComboBox::Create(dw, rect, pParentWnd, nID) )
		return false;

	CFont * font = CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
	SetFont(font);

	return true;
}
void Color_ComboBox::init_color(void)
{
/*
	int iMinColor = COLOR_SCROLLBAR, 
		iMaxColor = COLOR_BTNHIGHLIGHT;

	if(WINVER >= 0x0400)
		iMaxColor = COLOR_INFOBK;

	if(WINVER >= 0x0500)
		iMaxColor = 28;
	
	//初始化CB颜色列表框的Item(常见的SysColor值)
	for(int iLoop = iMinColor; iLoop <= iMaxColor; ++iLoop)
	{
		LPBSCBITEM lpItem = new BSCBITEM;
		lpItem->iIndex = AddString(g_color_name[iLoop]);
		lpItem->crColor = ::GetSysColor(iLoop);
		lpItem->lpCaption = g_color_name[iLoop];
		//
		if(m_crItem.IsEmpty())
			m_crItem.AddHead(lpItem);
		else
			m_crItem.AddTail(lpItem);		
	}
*/
	red_ = new BSCBITEM;
	red_->iIndex = AddString("red 1");
	red_->crColor = RGB(255,0,0);
	red_->lpCaption = "red 1";
	if(m_crItem.IsEmpty())
		m_crItem.AddHead(red_);
	else
		m_crItem.AddTail(red_);	

	yellow_ = new BSCBITEM;
	yellow_->iIndex = AddString("yellow 2");
	yellow_->crColor = RGB(255,255,0);
	yellow_->lpCaption = "yellow 2";
	m_crItem.AddTail(yellow_);	

	green_ = new BSCBITEM;
	green_->iIndex = AddString("green 3");
	green_->crColor = RGB(0,255,0);
	green_->lpCaption = "green 3";
	m_crItem.AddTail(green_);	

	LPBSCBITEM cyan_ = new BSCBITEM;
	cyan_->iIndex = AddString("cyan 4");
	cyan_->crColor = RGB(0,255,255);
	cyan_->lpCaption = "cyan 4";
	m_crItem.AddTail(cyan_);	

	LPBSCBITEM blue_ = new BSCBITEM;
	blue_->iIndex = AddString("blue 5");
	blue_->crColor = RGB(0,0,255);
	blue_->lpCaption = "blue 5";
	m_crItem.AddTail(blue_);	

	fuchsin_ = new BSCBITEM;
	fuchsin_->iIndex = AddString("fuchsin 6");
	fuchsin_->crColor = RGB(255,0,255);
	fuchsin_->lpCaption = "fuchsin 6";
	m_crItem.AddTail(fuchsin_);	


	write_ = new BSCBITEM;
	write_->iIndex = AddString("write 7");
	write_->crColor = RGB(255,255,255);
	write_->lpCaption = "write 7";
	m_crItem.AddTail(write_);	

	black_ = new BSCBITEM;
	black_->iIndex = AddString("black 8");
	black_->crColor = RGB(1,0,0);
	black_->lpCaption = "black 8";
	m_crItem.AddTail(black_);	
/*
	add_one_color("red 1",RGB(255,0,0));
	add_one_color("yellow 2",RGB(255,255,0));
	add_one_color("green 3",RGB(0,255,0));
	add_one_color("cyan 4",RGB(0,255,255));
	add_one_color("blue 5",RGB(0,0,255));//
	add_one_color("fuchsin 6",RGB(255,0,255));
	add_one_color("write 7",RGB(255,255,255));
	add_one_color("black 8",RGB(1,0,0));//
*/

	//该Item是为了用户自定义颜色而设置
	LPBSCBITEM lpItem = new BSCBITEM;
	lpItem->iIndex = AddString("More Colors");
	lpItem->crColor = RGB(213, 233, 249);
	lpItem->lpCaption = "More Colors";
	
	if(m_crItem.IsEmpty())
		m_crItem.AddHead(lpItem);
	else
		m_crItem.AddTail(lpItem);		
	//初始化当前颜色
	m_crColor = m_crItem.GetHead()->crColor;
}
void Color_ComboBox::add_one_color(CString color_name,COLORREF col)
{
	LPBSCBITEM lpItem = new BSCBITEM;
	lpItem->iIndex = AddString(color_name);
	lpItem->crColor = col;

	LPCTSTR   lpszTest = (LPSTR)(LPCTSTR)color_name;
	lpItem->lpCaption = lpszTest;
	if(m_crItem.IsEmpty())
		m_crItem.AddHead(lpItem);
	else
		m_crItem.AddTail(lpItem);	
}

void Color_ComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
	
	//画笔
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	ASSERT(pDC->GetSafeHdc());
	
	//绘制区
	RECT rc = lpDrawItemStruct->rcItem;
	RECT rcIcon(rc), rcTxt(rc);
	
	//当前的Item索引号
	LPBSCBITEM lpItem = GetItem(lpDrawItemStruct->itemID);	
	if(lpItem != NULL)
	{		
		//画颜色Icon
		rcIcon.right = rcIcon.left + iIconX;
		rcIcon.top += (rc.bottom - rc.top - iIconY) / 2;
		rcIcon.bottom = rcIcon.top + iIconY;
		
		pDC->FillSolidRect(rcIcon.left, rcIcon.top, 
			rcIcon.right - rcIcon.left, rcIcon.bottom - rcIcon.top, lpItem->crColor);
		
		pDC->DrawEdge(&rcIcon, BDR_RAISEDINNER, BF_RECT);
		//开始画文字
		int nOldBkMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		
		rcTxt.left = rcIcon.right + 5;
		rcTxt.top = rcIcon.top;
		
		pDC->DrawText(lpItem->lpCaption, &rcTxt, 
			DT_VCENTER | DT_END_ELLIPSIS | DT_NOCLIP | DT_SINGLELINE);
		
		pDC->SetBkMode(nOldBkMode);
	}
}

void Color_ComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = iIconY + 5;	
}

void Color_ComboBox::OnPaint() 
{
	CPaintDC dc(this); 
	OnCBPaint(&dc);
	
	// Do not call CComboBox::OnPaint() for painting messages
}
void Color_ComboBox::OnCBPaint(CDC* pDC)
{
	ASSERT(pDC->GetSafeHdc());
	
	//绘制客户区
	CDC dMemDC;
	dMemDC.CreateCompatibleDC(pDC);
	dMemDC.SetMapMode(pDC->GetMapMode());	

	//画动作
	CBitmap mNewBmp;
	RECT rc;
	GetClientRect(&rc);
	mNewBmp.CreateCompatibleBitmap(pDC, rc.right - rc.left, rc.bottom - rc.top);
	CBitmap* pOldBmp = dMemDC.SelectObject(&mNewBmp);

	//子类可以以friend方式来访问父类的protected成员变量和函数
	CWnd::DefWindowProc(WM_PAINT, (WPARAM)dMemDC.m_hDC, 0);
	
	pDC->BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, &dMemDC,
		rc.left ,rc.top, SRCCOPY);
	
	//恢复
	dMemDC.SelectObject(pOldBmp);
	pOldBmp->DeleteObject();
	dMemDC.DeleteDC();

	GetWindowRect(&rc);
	ScreenToClient(&rc);
	pDC->DrawEdge(&rc, (m_bOverControl ? BDR_RAISEDINNER : BDR_SUNKENINNER), BF_RECT);
}
BOOL Color_ComboBox::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	ASSERT(pDC->GetSafeHdc());
	return false;
}

void Color_ComboBox::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 888 && IsWindowEnabled())
	{
		CPoint point;
		::GetCursorPos(&point);

		CRect rect;
		GetWindowRect(&rect);
		if(rect.PtInRect(point))
		{
			m_bOverControl = true;
		}
		else
		{
			m_bOverControl = false;
			KillTimer(nIDEvent);
		}
	}
	CComboBox::OnTimer(nIDEvent);
}

void Color_ComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CComboBox::OnMouseMove(nFlags, point);
}

void Color_ComboBox::OnSelendok() 
{
	// TODO: Add your control notification handler code here
	int iIndex = this->GetCurSel();
	LPBSCBITEM lpTmpItem = GetItem(iIndex);
	if(lpTmpItem != NULL)
	{
		if(lpTmpItem->lpCaption == "More Colors")
		{
			CColorDialog crDlg(RGB(255, 0, 0), CC_FULLOPEN);
			int iRet = crDlg.DoModal();
			if(iRet == IDOK)
			{
				m_crColor = crDlg.GetColor();
				LPBSCBITEM lpItem = m_crItem.GetTail();
				ASSERT(lpItem);
				lpItem->crColor = m_crColor;
				Invalidate();
			}
		}
	}

}

void Color_ComboBox::OnSelchange() 
{
	// TODO: Add your control notification handler code here
	int iIndex = GetCurSel();
	color_index_ = iIndex;
	if(iIndex != CB_ERR && iIndex >= 0)
	{
		CDC* pDC = this->GetDC();
		//绘制区
		RECT rc;
		int iScrollX = ::GetSystemMetrics(SM_CXVSCROLL);
		GetClientRect(&rc);
		
		pDC->FillSolidRect(rc.left + 2, rc.top + 2, 
			rc.right - rc.left - iScrollX - 4, rc.bottom - rc.top - 2, 
			::GetSysColor(COLOR_WINDOW));		
		
		RECT rcIcon(rc), rcTxt(rc);
		
		//当前的Item索引号
		LPBSCBITEM lpItem = GetItem(iIndex);
		if(lpItem != NULL)
		{
			m_crColor = lpItem->crColor;
			
			//画颜色Icon
			rcIcon.left += 2;
			rcIcon.right = rcIcon.left + iIconX;
			rcIcon.top += (rc.bottom - rc.top - iIconY) / 2;
			rcIcon.bottom = rcIcon.top + iIconY;
			
			pDC->FillSolidRect(rcIcon.left, rcIcon.top, 
				rcIcon.right - rcIcon.left, rcIcon.bottom - rcIcon.top, lpItem->crColor);
			
			pDC->DrawEdge(&rcIcon, BDR_RAISEDINNER, BF_RECT);
			//开始画文字
			int nOldBkMode = pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0, 0, 0));
			
			rcTxt.left = rcIcon.right + 5;
			rcTxt.top = rcIcon.top;
			
			CFont* font = CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
			pDC->SelectObject(font);
			pDC->DrawText(lpItem->lpCaption, &rcTxt, 
				DT_VCENTER | DT_END_ELLIPSIS | DT_NOCLIP | DT_SINGLELINE);
			
			pDC->SetBkMode(nOldBkMode);
		}
		pDC->DeleteDC();
	}	
	
}
Color_ComboBox::LPBSCBITEM Color_ComboBox::GetItem(int iIndex)
{
	//当前的Item索引号
	POSITION pos = m_crItem.FindIndex(iIndex);
	if(pos)
	{
		LPBSCBITEM lpItem = m_crItem.GetAt(pos);

		ASSERT(lpItem);
		return lpItem;
	}
	else
		return (LPBSCBITEM)NULL;
}
COLORREF Color_ComboBox::get_color()
{
	if(IsWindowEnabled())
		return m_crColor;
	else
	{
		return (m_crColor = GetItem(this->GetCurSel())->crColor);
	}
}
void Color_ComboBox::get_rgb_color(int* R, int* G, int* B)
{
	*R = GetRValue((DWORD)m_crColor);
	*G = GetGValue((DWORD)m_crColor);
	*B = GetBValue((DWORD)m_crColor);
}
int Color_ComboBox::get_color_index()
{
	if(color_index_ == 8){
		COLORREF colref = get_color();
		dlhml::Color col;
		col = colref;
		return col.index();
	}
	return color_index_+1;
	
}
