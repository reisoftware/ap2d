// object.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "export.h"
#include <TCHAR.H>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	return TRUE;
}

extern "C" OBJECT_API
bool string_copy(LPTSTR& dest,LPCTSTR src)
{
	if(dest == src)
		return true;
	if(NULL != dest)
		delete [] dest;
	dest = 0;
	if(!src)
		return true;
	int length = lstrlen(src);
	dest = new TCHAR[length+1];
	_tcscpy(dest,src);
	dest[length] = '\0';
	return true;
}

extern "C" OBJECT_API 
void string_delete(LPTSTR& str)
{
	delete [] str;
	str = NULL;
}
