// Ap2DDoc.h : interface of the CAp2DDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AP2DDOC_H__D051E6BA_5BFE_43D7_A08B_E540704DF641__INCLUDED_)
#define AFX_AP2DDOC_H__D051E6BA_5BFE_43D7_A08B_E540704DF641__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAp2DDoc : public CDocument
{
protected: // create from serialization only
	CAp2DDoc();
	DECLARE_DYNCREATE(CAp2DDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAp2DDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAp2DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAp2DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AP2DDOC_H__D051E6BA_5BFE_43D7_A08B_E540704DF641__INCLUDED_)
