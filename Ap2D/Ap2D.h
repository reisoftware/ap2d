// Ap2D.h : main header file for the AP2D application
//

#if !defined(AFX_AP2D_H__58E0C8BE_ED37_45BE_B188_CAEBAE908694__INCLUDED_)
#define AFX_AP2D_H__58E0C8BE_ED37_45BE_B188_CAEBAE908694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAp2DApp:
// See Ap2D.cpp for the implementation of this class
//

#pragma warning (disable : 4786)

#include <string>
#include <vector>



typedef std::vector<std::string> strings;

#define TEXT_LEN 3000

class CAp2DApp : public CWinApp
{
public:
	CAp2DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAp2DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAp2DApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AP2D_H__58E0C8BE_ED37_45BE_B188_CAEBAE908694__INCLUDED_)
