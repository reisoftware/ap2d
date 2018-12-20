#include "stdafx.h"
#include "dat.h"

#include <stdlib.h>

namespace afc{

namespace the{

static void destroy(void*& ptr)
{
	if(ptr){
		free(ptr);
		ptr = 0;
	}
}

static void * create(int size)
{
	return malloc(size);
}

static void copy(void*& dst, const void* src, int size)
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
	destroy(dst);
	dst = create(size);
	memcpy(dst, src, size);
}

}//namespace


Dat::Dat()
{
	init();
}

Dat::Dat(const void * ptr, int size, LPCTSTR type)
{
	init();
	set(ptr, size, type);
}

Dat::Dat(const Dat& o)
{
	init();
	*this = o;
}

Dat::~Dat()
{
	the::destroy(ptr_);
}

void Dat::set(const void * ptr, int size, LPCTSTR type)
{
	the::copy(ptr_, ptr, size);
	size_ = size;
	type_ = type;
}

Dat& Dat::operator = (const Dat& o)
{
	set(o.ptr_, o.size_, o.type_);
	return *this;
}

// Dat::operator const void * ()const
// {
// 	return ptr_;
// }
	
void * Dat::ptr()
{
	return ptr_;
}

const void * Dat::ptr()const
{
	return ptr_;
}

int Dat::size()const
{
	return size_;
}

afc::string Dat::type()const
{
	return type_;
}

//////////////////////////// << private >> /////////////////////////////
void Dat::init()
{
	ptr_ = NULL;
	size_ = 0;
	type_ = NULL;
}




}//namespace
