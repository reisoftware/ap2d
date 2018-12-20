// Object1.cpp: implementation of the Object class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Object1.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace dlhml{

Runtime_Class* Runtime_Class::classinit = NULL;

Runtime_Class* Runtime_Class::load(LPCSTR name)
{
	Runtime_Class* pR = NULL;

	for(pR=Runtime_Class::classinit; pR!=NULL; pR=pR->pnext){
		if(lstrcmpA(name, pR->classname) == 0)
			return pR;
	}
	return pR;
}

Object* Runtime_Class::createob() const
{
	if(pfncreateob == NULL)
		return NULL;
	Object* pO = NULL;
	pO = (*pfncreateob)();
	return pO;
}

BOOL Runtime_Class::derived_from(const Runtime_Class* pBaseClass) const
{
	if (pBaseClass == NULL)
		return FALSE;

	// simple SI case
	const Runtime_Class* pClassThis = this;
	while (pClassThis != NULL){
		if (pClassThis == pBaseClass)
			return TRUE;
		pClassThis = pClassThis->pbaseclass;
	}
	return FALSE;       // walked to the top, no match
}

Class_Init::Class_Init(Runtime_Class* pRC)
MCT_INIT1("Class_Init")
{
	pRC->pnext = Runtime_Class::classinit;
	Runtime_Class::classinit = pRC;
}

struct Runtime_Class Object::classObject =
	{ "Object", NULL, NULL, NULL };

Runtime_Class* Object::GetRuntimeClass() const
{
	return MY_RUNTIME_CLASS(Object);
}

BOOL Object::iskindof(const Runtime_Class* pClass) const
{
	// simple SI case
	Runtime_Class* pClassThis = GetRuntimeClass();
	return pClassThis->derived_from(pClass);
}

BOOL Object::isa(const Runtime_Class* pClass) const
{
	Runtime_Class* pClassThis = GetRuntimeClass();
	return (0 == lstrcmpA(pClassThis->classname,pClass->classname));
}

std::string Object::my_class_name() const
{
  Runtime_Class* pClassThis = GetRuntimeClass();
  return pClassThis->classname;
}

Object::Object()
MCT_INIT1("Object")
{

}

Object::~Object()
{

}

}
