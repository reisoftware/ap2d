// DrawingDataChange.h: interface for the CDrawingDataChange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWINGDATACHANGE_H__F0C028A4_4BDB_47F9_BAF6_8EAD64E3CDF0__INCLUDED_)
#define AFX_DRAWINGDATACHANGE_H__F0C028A4_4BDB_47F9_BAF6_8EAD64E3CDF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDrawingDataChange  
{
public:
	CDrawingDataChange();
	virtual ~CDrawingDataChange();

	static COLORREF GetColor(int color);
	static void GetLtype(char* ch_ltype_old,char* ch_ltype);
};

#endif // !defined(AFX_DRAWINGDATACHANGE_H__F0C028A4_4BDB_47F9_BAF6_8EAD64E3CDF0__INCLUDED_)
