// Joint_DB.h: interface for the Joint_DB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOINT_DB_H__7CE0112E_91CF_4BA3_B58F_E9AF5318217C__INCLUDED_)
#define AFX_JOINT_DB_H__7CE0112E_91CF_4BA3_B58F_E9AF5318217C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Joint  
{
public:
	Joint();
	virtual ~Joint();
	
	CString name_;
	CString pic_name_;

};

class Joint_DB  
{
public:
	Joint_DB();
	virtual ~Joint_DB();

	std::vector<Joint> db_;
};

#endif // !defined(AFX_JOINT_DB_H__7CE0112E_91CF_4BA3_B58F_E9AF5318217C__INCLUDED_)
