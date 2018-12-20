// View.cpp: implementation of the View class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "View.h"

#include "MainFrm.h"
#include "assert.h"

#include <cassert>
#include "ap2dView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

View::View()
{
	edit_ = false;
}

View::~View()
{
}
View * View::create()
{
	return new View;
}
void View::close()
{
	delete this;
}
View* open_view(std::string name,int &judge)
{
	if(name == "")
		return NULL;
/*

	View *v = Project::instance()->get_view(name);
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	assert(pM && "Project::open_view");
	if(v){
		if(pM->is_open(v)){
			 pM->set_cur_view(name);
			judge = 1;
			return NULL;
		}else{
		}
	}
	if(!v){
		v = Project::instance()->add_view(name);
	}
	((CAp2DApp*)AfxGetApp())->open_new();
	CMDIChildWnd* pActiveChild = ((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive();
	pActiveChild->SetWindowText(name.c_str());
	CView* view = pActiveChild->GetActiveView();
	CAp2DView* pView = static_cast<CAp2DView*>(view);
	pView->set_view(v);
	v->scene()->invalidate();
	v->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(100,100));
	pM->set_cur_view(name);
	judge = 0;
	return v;
*/

	return NULL;


}