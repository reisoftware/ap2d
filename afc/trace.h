#ifndef _AFC_TRACE_H_
#define _AFC_TRACE_H_

#include "export.h"

namespace afc{

class AFCAPI Trace
{
public:
	Trace();
	~Trace();

public:
	void trace(const char * tip);
	void trace(const char * tip, int i);
	void trace(const char * tip, double f);
	void trace(const char * tip, const char * s);

};


}//namespace


#endif//FILE