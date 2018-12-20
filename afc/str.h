
#ifndef _AFC_STR_H_
#define _AFC_STR_H_

#include "export.h"

namespace afc{

class AFCAPI string
{
public:
	string();
	string(const char * str);
	string(const string& str);
	~string();

public:
	string& operator = (const char * str);
	string& operator = (const string& str);

public:
	bool operator == (const char * str);
	bool operator == (const string& str);

public:
	string operator + (const string& str);
	string& operator += (const string& str);

public:
	operator const char * ()const;
	const char * c_str()const;

public:
	int size()const;
	bool empty()const;

private:
	char * str_;
};

}//namespace

#endif//FILE

