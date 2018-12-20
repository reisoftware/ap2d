#if !defined(AFX_INPUTDATA_H__E7CEF562_623F_4472_8D57_2644ED10AACF__INCLUDED_)
#define AFX_INPUTDATA_H__E7CEF562_623F_4472_8D57_2644ED10AACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputData.h : header file
//
#include "geptr.h"
/////////////////////////////////////////////////////////////////////////////
// InputData window
namespace gelib{
	class Scene;
}
class AFX_EXT_CLASS InputData : public CEdit
{
// Construction
public:
	InputData();
	CString data;
	CString indicator;
private:
	CString name_;
	gelib::Scene* s_;
// Attributes
public:
	
	void set_text(CString name,CString str,gelib::Scene* s);
	void set_text(CString str);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InputData)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~InputData();

	// Generated message map functions
protected:
	//{{AFX_MSG(InputData)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDATA_H__E7CEF562_623F_4472_8D57_2644ED10AACF__INCLUDED_)
