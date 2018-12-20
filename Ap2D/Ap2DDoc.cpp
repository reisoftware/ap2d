// Ap2DDoc.cpp : implementation of the CAp2DDoc class
//

#include "stdafx.h"
#include "Ap2D.h"

#include "Ap2DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAp2DDoc

IMPLEMENT_DYNCREATE(CAp2DDoc, CDocument)

BEGIN_MESSAGE_MAP(CAp2DDoc, CDocument)
	//{{AFX_MSG_MAP(CAp2DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAp2DDoc construction/destruction

CAp2DDoc::CAp2DDoc()
{
	// TODO: add one-time construction code here

}

CAp2DDoc::~CAp2DDoc()
{
}

BOOL CAp2DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAp2DDoc serialization

void CAp2DDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAp2DDoc diagnostics

#ifdef _DEBUG
void CAp2DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAp2DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAp2DDoc commands
