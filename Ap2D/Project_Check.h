// Project_Check.h: interface for the Project_Check class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECT_CHECK_H__83BA002C_D18E_4025_92C0_8AF2E29C3D86__INCLUDED_)
#define AFX_PROJECT_CHECK_H__83BA002C_D18E_4025_92C0_8AF2E29C3D86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Project_Check  
{
public:
	Project_Check();
	virtual ~Project_Check();

	static Project_Check* instance();
	void close(); 


	void open_project(CString pro_path);
};

#endif // !defined(AFX_PROJECT_CHECK_H__83BA002C_D18E_4025_92C0_8AF2E29C3D86__INCLUDED_)
