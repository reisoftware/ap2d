#include "stdafx.h"
#include "ary.h"

#include <stdlib.h>
#include <cassert>

namespace afc{

//////////////////////////// << static >> /////////////////////////////

namespace the{

static void * offset(void * p, int dis)
{
	return (char*)p + dis;
}

}//namespace


//////////////////////////// << Array >> /////////////////////////////
Array::Array(int unitsize)
:ptr_(NULL)
,count_(0)
,realcount_(8)
,unitsize_(unitsize)
{
	assert(unitsize_ > 0);
	ptr_ = this->create(ptr_, realcount_);
}

Array::~Array()
{
	this->destroy(ptr_);
	ptr_ = NULL;
}

int Array::size()const
{
	return count_;
}

void Array::resize(int n)
{
	assert(n >= 0);
	expandto(n);
}

void Array::push_back(const void * o)
{
	assert(o);
	expandto(count_+1);
	void * p = offset(ptr_, count_-1);
	copy(p, o);
}

void Array::clear()
{
	resize(0);
}

void Array::at(int index, const void * o)
{
	assert(index >= 0);
	assert(index < count_);
	void * p = this->offset(ptr_, index);
	copy(p, o);
}

void * Array::at(int index)
{
	assert(index >= 0);
	assert(index < count_);
	return offset(ptr_, index);
}

const void * Array::at(int index)const
{
	assert(index >= 0);
	assert(index < count_);
	return offset(ptr_, index);
}


void Array::loop(PF_LOOP pf)
{
	int n=size();
	int i=0;
	for(i=0; i<n; ++i){
		//void * p = at(i);
		pf(at(i));
	}
} 


//////////////////////////// << private >> /////////////////////////////
void * Array::offset(void * p, int dis)const
{
	return the::offset(p, dis*unitsize_);
}

void * Array::create(void * p, int n)const
{
	return realloc(p, n*unitsize_);
}

void Array::destroy(void *& p)const
{
	if(p){
		free(p);
		p = NULL;
	}
}

void Array::expandto(int n)
{
	count_ = n;
	if(count_ <= realcount_){
		return;
	}
	realcount_ *= 2;
	ptr_ = create(ptr_, realcount_);
}

void Array::copy(void * dst, const void * src)const
{
	memcpy(dst, src, unitsize_);
}



}//namespace
