// MemType.h: interface for the CMemType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMTYPE_H__CDEA4E8F_AB4B_4870_A83C_1A87CCAFD671__INCLUDED_)
#define AFX_MEMTYPE_H__CDEA4E8F_AB4B_4870_A83C_1A87CCAFD671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CMember;
class CMemType  
{
public:
	CMemType();
	virtual ~CMemType();
	
	CString sName;
	BOOL bName;

	CString sSection;
	BOOL bSection;

	float cr[3];
	BOOL bCr;

	int indexMin;
	int indexMax;
	BOOL bIndex;
	
	IsLike(CMember* pMember);
};

#endif // !defined(AFX_MEMTYPE_H__CDEA4E8F_AB4B_4870_A83C_1A87CCAFD671__INCLUDED_)
