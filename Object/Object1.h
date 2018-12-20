// Object1.h: interface for the Object class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_OBJECT1_H__283BA293_6852_425F_AC25_B9ABBB5A8808__INCLUDED_
#define AFX_OBJECT1_H__283BA293_6852_425F_AC25_B9ABBB5A8808__INCLUDED_

#include "export.h"
#include <string>
#include "../afc/counter.h"


namespace dlhml{

class Object;
struct OBJECT_API Runtime_Class
{
	static Runtime_Class* load(LPCSTR name);
	Object* createob() const;
	BOOL derived_from(const Runtime_Class* pBaseClass) const;

	LPCSTR classname;
	Object* (*pfncreateob)();
	Runtime_Class* pbaseclass;
	Runtime_Class* pnext;
	static Runtime_Class* classinit;

};

struct OBJECT_API Class_Init
{
	Class_Init(Runtime_Class* pRC);
private:
	MCT_DEF
};

class OBJECT_API Object 
{
	Object(const Object& rhs);
	void operator=(const Object& rhs);
	static Runtime_Class classObject;
protected:
	Object();
public:
	virtual ~Object();

	virtual Runtime_Class* GetRuntimeClass() const;

	BOOL iskindof(const Runtime_Class* pClass) const;
	BOOL isa(const Runtime_Class* pClass) const;
  std::string my_class_name() const;

private:
	MCT_DEF

};

#define MY_RUNTIME_CLASS(class_name) ((Runtime_Class*)(&class_name::class##class_name))

#define MY_DECLARE_RUNTIME(class_name) \
public: \
	static Runtime_Class class##class_name; \
	virtual Runtime_Class* GetRuntimeClass() const; \


#define MY_DECLARE_DYNCREATE(class_name) \
	MY_DECLARE_RUNTIME(class_name) \
public: \
	static Object* createob(); \
	static class_name* create_me(); \
private: \
	static void* operator new(size_t size); \
	static void operator delete(void* ptr); \


#define MY_IMPLEMENT_RUNTIME(class_name,base_class_name) \
Runtime_Class class_name::class##class_name = { \
			#class_name,class_name::createob,MY_RUNTIME_CLASS(base_class_name),NULL}; \
Runtime_Class* class_name::GetRuntimeClass() const \
{ return MY_RUNTIME_CLASS(class_name); } \


#define MY_IMPLEMENT_DYNCREATE(class_name,base_class_name) \
	MY_IMPLEMENT_RUNTIME(class_name,base_class_name) \
Object* class_name::createob() \
{ return new class_name; } \
class_name* class_name::create_me() \
{ return new class_name;} \
void* class_name::operator new(size_t size) \
{ return ::operator new(size); } \
void class_name::operator delete(void* ptr) \
{ ::operator delete(ptr); } \
Class_Init init##class_name(MY_RUNTIME_CLASS(class_name)); \

}

#endif // !defined(AFX_OBJECT1_H__283BA293_6852_425F_AC25_B9ABBB5A8808__INCLUDED_)
