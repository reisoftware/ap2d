// JntBase.h: interface for the CJntBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JNTBASE_H__9A53E513_463D_40B7_8B29_EC07974104FD__INCLUDED_)
#define AFX_JNTBASE_H__9A53E513_463D_40B7_8B29_EC07974104FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef AFX_DATA
#undef AFX_DATA
#define	AFX_DATA AFX_EXT_DATA
#endif

#include "geconnect.h"
#include <vector>

#include "../include/joint.h"
#include "../include/libtcc.h"

class CBolt;
class Jnt_IO:public JOINT_IO{
private:
	char script_name[MAX_BUFFER];
	TCCState *s;
  void *mem;
public:
	Jnt_IO(const char* name);
	int init_script(const char* name);
	~Jnt_IO();
};
class CJntBase  
{
private:
	JOINT* jnt;
public:
	CJntBase();
protected:
	~CJntBase();
public:
	 BOOL AddMembers(std::vector<int>& mems) ; 
	 BOOL SetBasePt(int iIndex);
	 
	 CJntBase* CreateObject();
	 CString GetTypeName();
	 void Serialize(CArchive& ar);
	 void GetConnect(CJoint* pJnt,CGeConnect& cnt);
	 BOOL Edit() ;
	 void Release();
	 void GetBolts(std::vector<CBolt>& bolts,CJoint* jnt);
	 void unmodify_member(CJoint* joint);
	 CPt3D get_offset(int mem_index) ;

	 friend CJntBase* create_jntbase(int type_);
};
namespace GEXY{
	inline void Release(CJntBase* pT)
	{
		pT->Release();
	}
}

#undef AFX_DATA
#define AFX_DATA
#endif // !defined(AFX_JNTBASE_H__9A53E513_463D_40B7_8B29_EC07974104FD__INCLUDED_)
