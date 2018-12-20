// Ap2D.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Ap2D.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "Ap2DDoc.h"
#include "Ap2DView.h"
#include "net_ap.h"
#include "for_net.h"

#include "ApNet_Check.h"
#include "Dlg_ApNet.h"
#include "DlgSetServer.h"
#include "Afxsock.h"
#include "ap2d_check.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAp2DApp

BEGIN_MESSAGE_MAP(CAp2DApp, CWinApp)
	//{{AFX_MSG_MAP(CAp2DApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAp2DApp construction

CAp2DApp::CAp2DApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAp2DApp object

CAp2DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAp2DApp initialization

BOOL CAp2DApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_AP2DTYPE,
		RUNTIME_CLASS(CAp2DDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAp2DView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;





	
/*
	CString year,month;
	CTime time(CTime::GetCurrentTime());
	int iYear = time.GetYear();
	year.Format("%i",iYear);
	int iMonth = time.GetMonth();
	month.Format("%i",iMonth);

	if(year == "2015" && (month == "11"||month == "12")){
	

	}else{
		
		return -1;
	}
*/
	// Parse command line for standard shell commands, DDE, file open
	CString addr = AfxGetApp()->m_lpCmdLine;

	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo)){
		return FALSE;
	}
	//网络验证

/*
	//验证没有返回值，对于用户来说只是程序启动不起来的效果。所以达不到组合模式，按照多长时间连不上就退出的方式。
	if(!login()){
		//用户名密码验证
		AfxSocketInit();
		Dlg_ApNet dlg;
		if(dlg.DoModal() != IDOK){
			AfxMessageBox("Isn't registered! call 86-0411-84753206.");
			return FALSE;
		}	
	
		//AfxMessageBox("the netcard error ,please call 0411-84753206.");
		//return FALSE;
	}	

*/

/*

	//用户名密码验证
	AfxSocketInit();
	Dlg_ApNet dlg;
	if(dlg.DoModal() != IDOK){
		AfxMessageBox("Isn't registered! call 86-0411-84753206.");
		return FALSE;
	}
*/	
	  //验证没有返回值，对于用户来说只是程序启动不起来的效果。所以达不到组合模式，按照多长时间连不上就退出的方式。
	if(!login()){
		AfxMessageBox("the netlink error ,please check net.");
		return FALSE;
	}	
	
/*
		
	DlgSetServer server_dlg;
	if(server_dlg.DoModal() == IDOK){
		//局域网验证
		Entry_Inf net_info;
		net_info.ip = server_dlg.m_ip_str;
		net_info.user = "root";
		net_info.pwd = "123";
		net_info.port = 8000;
		if(!link_server(net_info)){		
			AfxMessageBox("Please link server!");
			return -1;
		}
	
	}


		
	//局域网验证
		Entry_Inf net_info;
		net_info.ip = "192.168.5.228";//180
		net_info.user = "root";
		net_info.pwd = "123";
		net_info.port = 8000;
		if(!link_server(net_info)){		
			AfxMessageBox("Please link server!");
			return -1;
		}	
*/
	//下载公司数据库
	/*2016-5-27

	if(!afc::net::check_redis()){
		AfxMessageBox("Please link server!");
		return -1;
	}

*/

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CAp2DApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAp2DApp message handlers

