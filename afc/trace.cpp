#include "stdafx.h"
#include "trace.h"
#include "str.h"
#include "../include/getrace.h"



namespace afc{

namespace the{
	static int tab_ = 0;
	static afc::string get_trace_str()
	{
		afc::string str;
		int i=0;
		for(; i<tab_; ++i){
			str += "  ";
		}
		return str;
	}
}//namespace the


Trace::Trace()
{
	the::tab_ ++;
}

Trace::~Trace()
{
	the::tab_ --;
}


void Trace::trace(const char * tip)
{
	afc::string str = the::get_trace_str();
	str += "%s\n";
	TRACE_OUT(const_cast<char*>(str.c_str()), tip);
}

void Trace::trace(const char * tip, int i)
{
	afc::string str = the::get_trace_str();
	str += "%s%i\n";
	TRACE_OUT(const_cast<char*>(str.c_str()), tip, i);
}

void Trace::trace(const char * tip, double f)
{
	afc::string str = the::get_trace_str();
	str += "%s%f\n";
	TRACE_OUT(const_cast<char*>(str.c_str()), tip, f);
}

void Trace::trace(const char * tip, const char * s)
{
	afc::string str = the::get_trace_str();
	str += "%s%s\n";
	TRACE_OUT(const_cast<char*>(str.c_str()), tip, s);
}


}//namespace
