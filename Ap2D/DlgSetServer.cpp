// DlgSetServer.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "DlgSetServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSetServer dialog


DlgSetServer::DlgSetServer(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSetServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSetServer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgSetServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSetServer)
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_ip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSetServer, CDialog)
	//{{AFX_MSG_MAP(DlgSetServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSetServer message handlers

void DlgSetServer::OnOK() 
{
	// TODO: Add extra validation here
	BYTE nf1,nf2,nf3,nf4; 
	m_ip.GetAddress(nf1,nf2,nf3,nf4); 

	m_ip_str.Format("%d.%d.%d.%d",nf1,nf2,nf3,nf4);//这里的nf得到的值是IP值了

	CDialog::OnOK();
}
