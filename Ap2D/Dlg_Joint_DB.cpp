// Dlg_Joint_DB.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Joint_DB.h"

#include "Dlg_Joint_DB_Edit.h"

#include "dir.h"
#include <shlwapi.h>

Dlg_Joint_DB_Edit db_edit_;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Joint_DB dialog


Dlg_Joint_DB::Dlg_Joint_DB(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Joint_DB::IDD, pParent)
{
	dlg_status_ = FALSE;
	//{{AFX_DATA_INIT(Dlg_Joint_DB)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}




void Dlg_Joint_DB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Joint_DB)
	DDX_Control(pDX, IDC_STATIC_PICTURE, static_pictures_);
	DDX_Control(pDX, IDC_COMBO1, combo_joint_name_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Joint_DB, CDialog)
	//{{AFX_MSG_MAP(Dlg_Joint_DB)
	ON_BN_CLICKED(ID_BUT_EDIT_DB, OnButEditDb)
	ON_CBN_SELCHANGE(IDC_COMBO_JOINT_NAME, OnSelchangeComboJointName)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Joint_DB message handlers

Dlg_Joint_DB::~Dlg_Joint_DB()
{
	dlg_status_ = FALSE;
}


void Dlg_Joint_DB::OnButEditDb() 
{
	// TODO: Add your control notification handler code here
//	Dlg_Joint_DB_Edit dlg;
//	CString cur_name_;
//	combo_joint_name_.GetWindowText(cur_name_);
//	dlg.set_sel_name(cur_name_);
//	dlg.DoModal();
	OnCancel();
	combo_joint_name_.GetWindowText(sel_name_);
	Dlg_Joint_DB_Edit *dlg  = new Dlg_Joint_DB_Edit();
	dlg->set_sel_name(sel_name_);
	dlg->Create(IDD_DLG_JOINT_EDIT_DB);
	dlg->ShowWindow(SW_SHOW);
	dlg->init_sel();
//	dlg->DoModal();
	
}

void Dlg_Joint_DB::get_datas()
{
	CString filename = "pic_ifo.txt";
	filename = file_path_ + filename ;
	CStdioFile file;
	if ( !file.Open(filename,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead | CFile::typeText )){
		 #ifdef _DEBUG
		  afxDump << "Unable to open file" << "\n";
	   #endif
	   exit( 1 );
	}
	CString perline= "" ;
	while(file.ReadString(perline)){
		PICFILE cur_picfile;
		cur_picfile.name_ = perline.Left(perline.Find('='));
		cur_picfile.path_ = perline.Right(perline.GetLength() - perline.Find('=') - 1);
		if (PathFileExists(file_path_ +	cur_picfile.path_)){
			db_edit_.instance()->push_back(cur_picfile);
		}
		
	}
	file.Close();

}

void Dlg_Joint_DB::show_data_to_dlg()
{
	combo_joint_name_.ResetContent();
	for (int i = 0 ;i < db_edit_.instance()->size() ; i++ ){
	//	AfxMessageBox((*Dlg_Joint_DB_Edit::instance())[i].name_);
		combo_joint_name_.AddString((*db_edit_.instance())[i].name_);
	}
}

void 	Dlg_Joint_DB::init_db()
{
	Dlg_Joint_DB_Edit::instance()->clear();
	get_datas();
	show_data_to_dlg();
}

void 	Dlg_Joint_DB::set_sel_name(CString name)
{
	if (name.Compare("") == 0 && sel_name_.Compare("") != 0 )
		sel_name_ = sel_name_;
	else 
		sel_name_ = name;
}


void Dlg_Joint_DB::show_image(CString strFile)
{

	CBitmap bmp;  
	HBITMAP hbitmap;
	//bmp.LoadBitmap(strFile);  
	if (PathFileExists(strFile)){
		CRect lRect;
		static_pictures_.GetClientRect(&lRect);

		hbitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),strFile,IMAGE_BITMAP,lRect.Width(),lRect.Height(),LR_LOADFROMFILE);
		bmp.Attach(hbitmap);
//		DIBSECTION ds;
//		BITMAPINFOHEADER &bminfo  = ds.dsBmih;
//
//		bmp.GetObject(sizeof(ds),&ds);
//		int cs = bminfo.biWidth;
//		int cy = bminfo.biHeight;
//
//		CPaintDC dc(GetDlgItem(IDC_STATIC_PICTURE)); 
		
		BITMAP bm;
		bmp.GetBitmap(&bm);
		CDC dcMem;
		dcMem.CreateCompatibleDC(GetDC());
		CBitmap *pOldBitmap=(CBitmap*)dcMem.SelectObject(bmp);
		
		//显示位图
		ScreenToClient(&lRect);

		static_pictures_.GetDC()->SetStretchBltMode ( HALFTONE) ;
		static_pictures_.GetDC()->StretchBlt(0,0, lRect.Width(),lRect.Height(),&dcMem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);//
		dcMem.SelectObject(&pOldBitmap); 
		bmp.Detach();
		DeleteObject(bmp);
		dcMem.DeleteDC();  
	}
	else{
		static_pictures_.ShowWindow(FALSE); //初始化picture控件显示问题 
		static_pictures_.ShowWindow(TRUE);
	}
/*
	if (bmp.m_hObject != NULL )
		bmp.DeleteObject();
	HBITMAP hbitmap;
	//bmp.LoadBitmap(strFile);  
	if (PathFileExists(strFile)){
		hbitmap=(HBITMAP)::LoadImage(NULL,strFile,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADFROMFILE);
		bmp.Attach(hbitmap);
		DIBSECTION ds;
		BITMAPINFOHEADER &bminfo = ds.dsBmih;
		bmp.GetObject(sizeof(ds),&ds);
		BITMAP bm;
		bmp.GetBitmap(&bm);
		int cx=bminfo.biWidth; //得到图像宽度
		int cy=bminfo.biHeight; //得到图像高度

		//CDC dcMem;
	//	dcMem.CreateCompatibleDC(GetDC());
	//	CBitmap *pOldBitmap=(CBitmap*)dcMem.SelectObject(bmp);

		CRect lRect;
		//static_pictures_.GetClientRect(&lRect);
		static_pictures_.GetWindowRect(&lRect);
		//显示位图
		ScreenToClient(&lRect);
		//static_pictures_.GetDC()->StretchBlt(0,0,lRect.Width(),lRect.Height(),&dcMem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		static_pictures_.MoveWindow(lRect.left,lRect.top,cx,cy,true);
	//	dcMem.SelectObject(&pOldBitmap); 
	//	bmp.Detach();
	//	DeleteObject(bmp);
		//dcMem.DeleteDC();  
	
	}
	else{
		static_pictures_.ShowWindow(FALSE); //初始化picture控件显示问题 
		static_pictures_.ShowWindow(TRUE);
	}
		*/
}


/*
void Dlg_Joint_DB::show_image(CString strFile)
{

	HBITMAP hBitmap; 
	CRect lRect;
	static_pictures_.GetClientRect(&lRect);
	hBitmap =(HBITMAP)LoadImage(AfxGetInstanceHandle(), 
strFile, 
IMAGE_BITMAP,0,0, 
LR_LOADFROMFILE);



//关联图片ID 
	
	


//获得指向静态控件的指针 
//CStatic *pStatic=(CStatic *)GetDlgItem(IDC_STATIC_PIC);//控件ID 
//设置静态控件的样式，使其可以使用位图，并试位标显示使居中 
static_pictures_.ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE); 
	//设置静态控件显示位图 
static_pictures_.SetBitmap(hBitmap); 

}
*/
/*
void Dlg_Joint_DB::show_image(CString strFile)
{
		HBITMAP hbitmap;
    //将pStatic指向要显示的地方

    //根据ID获取Static控件
    //装载资源*.bmp
    hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),strFile,
        IMAGE_BITMAP,0,0,LR_LOADFROMFILE);


    CBitmap hbmp;
    hbmp.Attach(hbitmap);
    //获取图片内容
    BITMAP bm;
    hbmp.GetBitmap(&bm);
    CDC dcMem;

    //创建兼容DC
    dcMem.CreateCompatibleDC(GetDC());
    CBitmap *pOldBitmap=(CBitmap*)dcMem.SelectObject(hbmp);
    CRect lRect;

    //获取Static控件的大小范围
   static_pictures_.GetClientRect(&lRect);
    //在Static控件上显示位图
   static_pictures_.GetDC()->StretchBlt(lRect.left ,lRect.top ,lRect.Width(),lRect.Height(),
        &dcMem,0 ,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
   dcMem.SelectObject(&pOldBitmap);


}

*/

/*
BOOL Dlg_Joint_DB::show_picture(CString imgPath)
{
	int height, width;
	CRect rect;//定义矩形类
	CRect rect1;
	CBitmap image;  
	HBITMAP hbitmap;
	//CImage image; //创建图片类
	//image.Load(imgPath);
	hbitmap=(HBITMAP)::LoadImage(NULL,imgPath,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	height = hbitmap.GetHeight();
	width = hbitmap.GetWidth();


	static_pictures_.GetClientRect(&rect); //获得pictrue控件所在的矩形区域
	CDC *pDc = static_pictures_.GetDC();//获得pictrue控件的Dc
	SetStretchBltMode(pDc->m_hDC,STRETCH_HALFTONE); 


	if(width<=rect.Width() && height<=rect.Width()) //小图片，不缩放
	{
	rect1 = CRect(rect.TopLeft(), CSize(width,height));
	image.StretchBlt(pDc->m_hDC,rect1,SRCCOPY); //将图片画到Picture控件表示的矩形区域
	return TRUE;
	}
	else
	{
	float xScale=(float)rect.Width()/(float)width;
	float yScale=(float)rect.Height()/(float)height;
	float ScaleIndex=(xScale>=yScale:xScale,yScale);
	rect1 = CRect(rect.TopLeft(), CSize((int)width*ScaleIndex,(int)height*ScaleIndex));
	image.StretchBlt(pDc->m_hDC,rect1,SRCCOPY); //将图片画到Picture控件表示的矩形区域
	}
	ReleaseDC(pDc);//释放picture控件的Dc
	return TRUE;
}

	*/
void Dlg_Joint_DB::init_sel()
{
//	combo_joint_name_.SetWindowText(sel_name_);
	int status = 0;
	for (int i = 0 ;i < db_edit_.instance()->size() ; i++ ){
		if ( (*db_edit_.instance())[i].name_.Compare(sel_name_) == 0 ){
			status = 1;
			combo_joint_name_.SetCurSel(combo_joint_name_.FindStringExact(0,sel_name_));
			show_image(file_path_ + (*db_edit_.instance())[i].path_);
			break;	
		}
	}
	if( status == 0 ){
		combo_joint_name_.AddString(sel_name_);
		combo_joint_name_.SetCurSel(combo_joint_name_.FindStringExact(0,sel_name_));
	}
		

}

void Dlg_Joint_DB::re_call()
{
	OnInitDialog() ;
	set_sel_name(sel_name_);
	init_sel();
}

BOOL Dlg_Joint_DB::OnInitDialog() 
{

	
	CDialog::OnInitDialog();
	dlg_status_ = TRUE;
	file_path_ = db_edit_.get_files_path();
	afc::dir::create_floder(file_path_);
	init_db();
	//init_sel();

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void Dlg_Joint_DB::OnSelchangeComboJointName() 
{
	// TODO: Add your control notification handler code here
	int item  = combo_joint_name_.GetCurSel();
	CString cur_sel_name;
	combo_joint_name_.GetLBText(item,cur_sel_name);
	int cur_status_ = 0 ;
	for (int i = 0 ;i < db_edit_.instance()->size() ; i++ ){
	//	AfxMessageBox((*Dlg_Joint_DB_Edit::instance())[i].name_);
		if ( (*db_edit_.instance())[i].name_.Compare(cur_sel_name) == 0 ){
			show_image(file_path_ + (*db_edit_.instance())[i].path_);
			cur_status_ = 1;
			break;
		}
	}
	if (cur_status_ == 0 ){
		static_pictures_.ShowWindow(FALSE); //初始化picture控件显示问题 
		static_pictures_.ShowWindow(TRUE);
	}

}


void Dlg_Joint_DB::OnCancel() 
{
	// TODO: Add extra cleanup here
	dlg_status_ = FALSE;
	CDialog::OnCancel();
}

void Dlg_Joint_DB::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

void Dlg_Joint_DB::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	dlg_status_ = FALSE;
//	DestroyWindow();
	CDialog::OnClose();
//	OnCancel();
//	OnCancel();
}


BOOL Dlg_Joint_DB::dlg_is_have()
{
	return dlg_status_;
}




void Dlg_Joint_DB::OnOK() 
{
	// TODO: Add extra validation here
	dlg_status_ = FALSE;
	CDialog::OnOK();
}
/*
void Dlg_Joint_DB::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
//	CPaintDC dc(GetDlgItem(IDC_STATIC_PICTURE));
//	CRect rcclient;
//
//	GetDlgItem(IDC_STATIC_PICTURE)->GetClientRect(&rcclient);
//
//	CDC memdc;
//
//	memdc.CreateCompatibleDC(&dc);
//
//	CBitmap bitmap;
//
//	bitmap.CreateCompatibleBitmap(&dc, rcclient.Width(), rcclient.Height());
//
//	memdc.SelectObject( &bitmap );
//
//	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memdc.m_hDC , 0);
//
//	CDC maskdc;
//
//	maskdc.CreateCompatibleDC(&dc);
//
//	CBitmap maskbitmap;
//
//	maskbitmap.CreateBitmap(rcclient.Width(), rcclient.Height(), 1, 1, NULL);
//
//	maskdc.SelectObject( &maskbitmap );
//
//	maskdc.BitBlt( 0, 0, rcclient.Width(), rcclient.Height(), &memdc,
//
//	rcclient.left, rcclient.top, SRCCOPY);
//
//	CBrush brush;
//
//	brush.CreatePatternBrush(&bmp);
//
//	dc.FillRect(rcclient, &brush);
//
//	dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(),
//
//	&memdc, rcclient.left, rcclient.top,SRCPAINT);
//
//	brush.DeleteObject();


	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
*/