 
#include "stdafx.h"
#include "str.h"

#include <stdlib.h>

namespace afc{

namespace the{

static void destroy(char*& str)
{
	if(str){
		free(str);
		str = 0;
	}
}

static char * create(char* str, int newlen)
{
	return (char*)realloc(str, (newlen+1)*sizeof(char));
}

static void copy(char*& dst, const char* src)
{
	//1
	if(!dst && !src){
		return;
	}
	//2
	if(!src){
		destroy(dst);
		return;
	}
	//3,4
	int n = strlen(src);
	dst = create(dst, n);
	strcpy(dst, src);
}

static void cat(char*& dst, const char* src)
{
	//1
	if(!dst && !src){
		return;
	}
	//2
	if(!src){
		return;
	}
	//3
	if(!dst){
		copy(dst, src);
		return;
	}
	//4
	int n = strlen(src) + strlen(dst);
	dst = create(dst, n);
	strcat(dst, src);
}

static bool cmp(const char * str1, const char * str2)
{
	if(!str1 && !str2){
		return true;
	}
	if(!str1 || !str2){
		return false;
	}
	return (strcmp(str1, str2) == 0);
}

}//namespace

string::string()
:str_(NULL)
{
}

string::string(const char * str)
:str_(NULL)
{
	the::copy(str_, str);
}

string::string(const string& str)
:str_(NULL)
{
	*this=str;
}


string::~string()
{
	the::destroy(str_);
}

string& string::operator = (const char * str)
{
	the::copy(str_, str);
	return *this;
}

string& string::operator = (const string& str)
{
	the::copy(str_, str);
	return *this;
}

bool string::operator == (const char * str)
{
	return the::cmp(str_, str);
}

bool string::operator == (const string& str)
{
	return the::cmp(str_, str.str_);
}

string string::operator + (const string& str)
{
	string temp = *this;
	temp += str;
	return temp;
}

string& string::operator += (const string& str)
{
	the::cat(str_, str);
	return *this;
}

string::operator const char * ()const
{
	return str_;
}

const char * string::c_str()const
{
	return str_;
}

int string::size()const
{
	if(!str_){
		return 0;
	}
	return strlen(str_);
}

bool string::empty()const
{
	return !size();
}


}//namespace




