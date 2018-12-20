#ifndef _AFC_DAT_H_
#define _AFC_DAT_H_

#include "export.h"
#include "str.h"

namespace afc{

class AFCAPI Dat
{
public:
	Dat();
	Dat(const void * ptr, int size, LPCTSTR type = NULL);
	Dat(const Dat& str);
	~Dat();

public:
	Dat& operator = (const Dat& o);

public:
	void * ptr();
	const void * ptr()const;
	int size()const;
	afc::string type()const;

public:
	void set(const void * ptr, int size, LPCTSTR type = NULL);

private:
	void init();

private:
	void * ptr_;
	int size_;
	afc::string type_;
};

}//namespace

#endif//FILE
