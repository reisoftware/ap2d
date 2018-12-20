// DimInfo_IO.h: interface for the DimInfo_IO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMINFO_IO_H__2A9AF38E_7DC6_4C53_B014_546FA91A1294__INCLUDED_)
#define AFX_DIMINFO_IO_H__2A9AF38E_7DC6_4C53_B014_546FA91A1294__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DimInfo_IO  
{
public:
	DimInfo_IO();
	virtual ~DimInfo_IO();

	void save(CString file);

};

#endif // !defined(AFX_DIMINFO_IO_H__2A9AF38E_7DC6_4C53_B014_546FA91A1294__INCLUDED_)
