#ifndef _AFC_ARY_H_
#define _AFC_ARY_H_

#include "export.h"

namespace afc{

class AFCAPI Array
{
	typedef void(*PF_LOOP)(void*);
public:
	explicit Array(int unitsize);
	~Array();

private:
	Array(const Array& o){}
	Array& operator = (const Array& o){return *this;}

public:
	int size()const;
	void resize(int n);
	void push_back(const void * o);
	void clear();

public:
	void at(int index, const void * o);
	void * at(int index);
	const void * at(int index)const;

public:
	void loop(PF_LOOP pf);

private:
	void * offset(void * p, int dis)const;
	void * create(void * p, int n)const; 
	void destroy(void *& p)const;
	void expandto(int n);
	void copy(void * dst, const void * src)const;
	
private:
	void * ptr_;
	int count_;
	int realcount_;
	int unitsize_;
};

}//namespace

#endif//FILE
