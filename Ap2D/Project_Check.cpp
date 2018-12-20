// Project_Check.cpp: implementation of the Project_Check class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Project_Check.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Project_Check::Project_Check()
{

}

Project_Check::~Project_Check()
{

}
Project_Check* Project_Check::instance()
{	
	static Project_Check g;
	return &g;
}

void Project_Check::close()
{
	delete this;
}
void Project_Check::open_project(CString pro_path)
{

}





