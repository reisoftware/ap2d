// String_Op.cpp: implementation of the String_Op class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "String_Op.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

String_Op::String_Op()
{

}

String_Op::~String_Op()
{

}
string String_Op::del_space(string str)
{
	std::string s;
	s.erase(0,s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
string String_Op::del_left_space(string str)
{
	std::string s;
	s.erase(0,s.find_first_not_of(" "));
	return s;
}
string String_Op::del_right_space(string str)
{
	std::string s;
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
