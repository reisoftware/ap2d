// Virtual_Key.cpp: implementation of the Virtual_Key class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Virtual_Key.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Virtual_Key::Virtual_Key()
MCT_INIT1("Virtual_Key")
{

}

Virtual_Key::~Virtual_Key()
{

}
void Virtual_Key::set_data(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(82==nChar) nChar = 11;
	if(79==nChar) nChar = 2;
	if(80==nChar) nChar = 3;
	if(81==nChar) nChar = 4;
	if(75==nChar) nChar = 5;
	if(76==nChar) nChar = 6;
	if(77==nChar) nChar = 7;
	if(71==nChar) nChar = 8;
	if(72==nChar) nChar = 9;
	if(73==nChar) nChar = 10;
	char_ = nChar;
	repcnt_ = nRepCnt;
	flags_ = nFlags;
}
char Virtual_Key::get_char() const
{
	return (char)::MapVirtualKey(char_,1);
}
int Virtual_Key::get_number() const
{
	char ch = get_char();
	return atoi(&ch);
}
bool Virtual_Key::esc() const
{
	return VK_ESCAPE == ::MapVirtualKey(char_,1);
}
bool Virtual_Key::enter() const
{
	return (VK_RETURN==::MapVirtualKey(char_,1)) || (284==char_);
}
bool Virtual_Key::comma() const
{
	return 51 == char_;
}
bool Virtual_Key::dot() const
{
	return (52==char_)||(83==char_);
}
bool Virtual_Key::ctrl() const
{
	return (VK_CONTROL==::MapVirtualKey(char_,1))||(285==char_);
}
bool Virtual_Key::char_char(TCHAR ch) const
{
	return IsCharAlpha(ch)!=0;
}
bool Virtual_Key::character() const
{
	return char_char(::MapVirtualKey(char_,1));
}
bool Virtual_Key::numeric_char(TCHAR ch) const
{
	return !IsCharAlpha(ch) && IsCharAlphaNumeric(ch);
}
bool Virtual_Key::number() const
{
	return numeric_char(::MapVirtualKey(char_,1));
}
bool Virtual_Key::backspace() const
{
	return VK_BACK == ::MapVirtualKey(char_,1);
}
bool Virtual_Key::del() const
{
	return VK_DELETE == ::MapVirtualKey(char_,1) || 339==char_;
}
}
