// ReiResource.h: interface for the CReiResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REIRESOURCE_H__174C4FB4_B77C_4F01_8AF5_0652C69C9C15__INCLUDED_)
#define AFX_REIRESOURCE_H__174C4FB4_B77C_4F01_8AF5_0652C69C9C15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*在dll和exe之间进行资源切换的类，每次当资源在dll中时，先定义一个此类型的对象
会自动进行程序的资源切换*/

//##ModelId=42535B43036B
class  CReiResource  
{
public:
	//##ModelId=42535B43036C
	void SetNewResource(HINSTANCE hInst=NULL);
	//##ModelId=42535B43036E
	CReiResource();
	//##ModelId=42535B43037A
	virtual ~CReiResource();
	//##ModelId=42535B43037C
	static HINSTANCE hOldResource;
};

#endif // !defined(AFX_REIRESOURCE_H__174C4FB4_B77C_4F01_8AF5_0652C69C9C15__INCLUDED_)
