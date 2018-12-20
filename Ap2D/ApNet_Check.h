// ApNet_Check.h: interface for the ApNet_Check class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APNET_CHECK_H__203C4B40_D3AD_4490_9235_ACEF45D1CFBE__INCLUDED_)
#define AFX_APNET_CHECK_H__203C4B40_D3AD_4490_9235_ACEF45D1CFBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ApNet_Check  
{
public:
	ApNet_Check();
	virtual ~ApNet_Check();

	BOOL check(CString user,CString password);
	BOOL check_data(CString user,CString password);
	
	void save(CString user,CString password);
	void open(CString &user,CString &password);
};

#endif // !defined(AFX_APNET_CHECK_H__203C4B40_D3AD_4490_9235_ACEF45D1CFBE__INCLUDED_)
