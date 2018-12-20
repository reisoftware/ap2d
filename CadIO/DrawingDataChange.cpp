// DrawingDataChange.cpp: implementation of the CDrawingDataChange class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawingDataChange.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawingDataChange::CDrawingDataChange()
{

}

CDrawingDataChange::~CDrawingDataChange()
{

}
//<Author>:zhong
//<Add>=Date:2007/11/19
COLORREF CDrawingDataChange::GetColor(int color)
{
	COLORREF col;
	if(color == 0)
		col = RGB(255,255,255);
	else if(color == 1)//红色
		col = RGB(255,0,0);
	else if(color == 2)//黄色
		col = RGB(255,255,0);
	else if(color == 3)//绿色
		col = RGB(0,255,0);
	else if(color == 4)//青色
		col = RGB(0,255,255);
	else if(color == 5)//蓝色
		col = RGB(0,0,255);
	else if(color == 6)//品红色
		col = RGB(255,0,255);
	else
		col = RGB(255,255,255);


	return col;
}
void CDrawingDataChange::GetLtype(char* ch_ltype_old,char* ch_ltype)
{
	if(strcmp(ch_ltype_old,"CENTER") == 0)
		strcpy(ch_ltype,"center");
	else if(strcmp(ch_ltype_old,"HIDDEN") == 0)
		strcpy(ch_ltype,"dot");
	else 
		strcpy(ch_ltype,"");


	
}
//</Add>
//</Author>
