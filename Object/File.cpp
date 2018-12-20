// File.cpp: implementation of the File class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "File.h"
#include "export.h"
#include <cassert>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
File::File()
:file_handle_(0)
,load_(false)
MCT_INIT2("File")
{

}

File::~File()
{

}
void File::attach(HANDLE hFile,bool isload)
{
	file_handle_ = hFile;
	load_ = isload;
}
errorinfo File::open(LPCTSTR szName, LPCTSTR szMode)
{
	TCHAR mode[MAX_PATH];
	lstrcpy(mode,szMode);
	CharLower(mode);
	if(0 != lstrcmp(TEXT("rb"),mode) && 0 != lstrcmp(TEXT("wb"),mode))
		return Error::FileOpenMode;

	if(0 == lstrcmp(TEXT("wb"),mode)){
		file_handle_ = CreateFile(szName,GENERIC_WRITE,0,
			NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(file_handle_ == INVALID_HANDLE_VALUE){
			TCHAR error[] = TEXT("can`t create ");
			lstrcat(error,szName);
			MessageBox(NULL,error,NULL,MB_OK);
			return Error::FileOpenFalse;
		}
	}
	else if(0 == lstrcmp(TEXT("rb"),mode)){
		file_handle_ = CreateFile(szName,GENERIC_READ,0,
             NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(file_handle_ == INVALID_HANDLE_VALUE){
			TCHAR error[] = TEXT("can`t open ");
			lstrcat(error,szName);
			MessageBox(NULL,error,NULL,MB_OK);
			return Error::FileOpenFalse;
		}
	}else{
		TCHAR error[] = TEXT("please type 'rb' for read or type 'wb' for write!");
		MessageBox(NULL,error,NULL,MB_OK);
		return Error::FileOpenMode;
	}

	if(0 == lstrcmp(TEXT("rb"),mode))
		load_ = TRUE;
	else
		load_ = FALSE;
	return Error::OK;
}

bool File::isload() const
{
	return load_;
}
errorinfo File::close()
{
	if(TRUE != ::CloseHandle(file_handle_))
		return Error::FileCloseFalse;
	return Error::OK;
}
void File::WriteBytes(const void *pData, size_t sz) const
{
	DWORD nWritten;
	if(!::WriteFile(file_handle_, pData, sz, &nWritten, NULL)){
		throw  Error::FileWriteFalse;
	//	MessageBox(NULL,TEXT("can`t write data!"),NULL,MB_OK);
	}
}

void File::ReadBytes(void *pData, size_t sz) 
{
	DWORD dwRead;
	if (!::ReadFile(file_handle_, pData, sz, &dwRead, NULL)){
		throw  Error::FileReadFalse;
	//	MessageBox(NULL,TEXT("can`t read data! please delete drawing.dat in programme path."),NULL,MB_OK);
	}
}

const File& File::operator<<(bool b) const
{
	WriteBytes(&b,sizeof(b));
	return *this;
}
const File& File::operator<<(BYTE by) const
{
	WriteBytes(&by,sizeof(by));
	return *this;
}
const File& File::operator<<(WORD w) const
{
	WriteBytes(&w,sizeof(w));
	return *this;
}
const File& File::operator<<(LONG l) const
{
	WriteBytes(&l,sizeof(l));
	return *this;
}
const File& File::operator<<(DWORD dw) const
{
	WriteBytes(&dw,sizeof(dw));
	return *this;
}
const File& File::operator<<(float f) const
{
	WriteBytes(&f,sizeof(f));
	return *this;
}
const File& File::operator<<(double d) const
{
	WriteBytes(&d,sizeof(d));
	return *this;
}
const File& File::operator<<(int i) const
{
	return File::operator<<((LONG)i);
}
const File& File::operator<<(short w) const
{
	return File::operator<<((WORD)w);
}
const File& File::operator<<(char ch) const
{
	return File::operator<<((BYTE)ch);
}
const File& File::operator<<(unsigned u) const
{
	return File::operator<<((LONG)u);
}
const File& File::operator<<(LPCTSTR str) const
{
	int length = lstrlen(str);
	File::operator <<(length);
	if(length<1)
		return *this;
	WriteBytes(str,length*sizeof(TCHAR));
	return *this;
}


File& File::operator>>(bool& b)
{
	ReadBytes(&b,sizeof(b));
	return *this;
}
File& File::operator>>(BYTE& by)
{
	ReadBytes(&by,sizeof(by));
	return *this;
}
File& File::operator>>(WORD& w)
{
	ReadBytes(&w,sizeof(w));
	return *this;
}
File& File::operator>>(DWORD& dw)
{
	ReadBytes(&dw,sizeof(dw));
	return *this;
}
File& File::operator>>(LONG& l)
{
	ReadBytes(&l,sizeof(l));
	return *this;
}
File& File::operator>>(float& f)
{
	ReadBytes(&f,sizeof(f));
	return *this;
}
File& File::operator>>(double& d)
{
	ReadBytes(&d,sizeof(d));
	return *this;
}
File& File::operator>>(int& i)
{
	return File::operator>>((LONG&)i);
}
File& File::operator>>(short& w)
{
	return File::operator>>((WORD&)w);
}
File& File::operator>>(char& ch)
{
	return File::operator>>((BYTE&)ch);
}
File& File::operator>>(unsigned& u)
{
	return File::operator>>((LONG&)u);
}
File& File::operator>>(LPTSTR& str)
{
	int length;
	File::operator >>(length);
	length /= sizeof(TCHAR);
	if(0 == length)
		return *this;
	if(str)
		delete [] str;
	str = new TCHAR[length+1];
	ReadBytes(str,length);
	str[length] = '\0';
	return *this ;
}
File& File::operator>>(LPCTSTR& str)
{
	assert(false && "File::operator>>(LPCTSTR& str), why? why do you want to write into const char *?");
	int length;
	File::operator >>(length);
	length /= sizeof( TCHAR);
	if(0 == length){
	//	trace("File::operator>>(LPCTSTR& str) 0 == length");		
		return *this;
	}
	LPTSTR temp;
	temp = new TCHAR[length+1];
	ReadBytes(temp,length);
	temp[length] = '\0';
	str = temp;
	return *this;
}

const File& File::operator<<(std::string str) const
{
	return *this << str.c_str();
}
File& File::operator>>(std::string &str)
{
	LPTSTR temp = NULL;
	*this >> temp ;
	if(temp == NULL){
		str = "";
	}else{
		assert(temp && "File::operator>>(std::string &str)");
		str = temp;
	}
	string_delete(temp);
	assert(!temp && "File::operator>>(std::string &str)");
	return *this;
}



}