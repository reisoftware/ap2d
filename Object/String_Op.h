// String_Op.h: interface for the String_Op class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRING_OP_H__B8FD9C06_2876_48C2_9BD4_9C758B649245__INCLUDED_)
#define AFX_STRING_OP_H__B8FD9C06_2876_48C2_9BD4_9C758B649245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using namespace std;

class String_Op  
{
public:
	String_Op();
	virtual ~String_Op();

	string del_space(string str);
	string del_left_space(string str);
	string del_right_space(string str);

};

#endif // !defined(AFX_STRING_OP_H__B8FD9C06_2876_48C2_9BD4_9C758B649245__INCLUDED_)
