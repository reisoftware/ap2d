// Mgr_Memory.h: interface for the Mgr_Memory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_MEMORY_H__53060F4F_A81F_4F0A_94A1_95363FD710BD__INCLUDED_)
#define AFX_MGR_MEMORY_H__53060F4F_A81F_4F0A_94A1_95363FD710BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Mgr_Memory  
{
public:
	Mgr_Memory();
	virtual ~Mgr_Memory();

};

void clear_memory();//清空全局内存块

#endif // !defined(AFX_MGR_MEMORY_H__53060F4F_A81F_4F0A_94A1_95363FD710BD__INCLUDED_)
