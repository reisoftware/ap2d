// File.h: interface for the File class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_FILE_H__BEB08E98_655F_4413_9443_43C4A3E8797E__INCLUDED_
#define AFX_FILE_H__BEB08E98_655F_4413_9443_43C4A3E8797E__INCLUDED_

#include "export.h"
#include <string>
#include "../afc/counter.h"

namespace dlhml{
class OBJECT_API File  
{
public:
	File();
	~File();

	errorinfo open(LPCTSTR szName, LPCTSTR szMode);	//open tobe close
	errorinfo close();
	bool isload() const;

	// insertion operations
	const File& operator<<(bool b) const;
	const File& operator<<(BYTE by) const;
	const File& operator<<(WORD w) const;
	const File& operator<<(LONG l) const;
	const File& operator<<(DWORD dw) const;
	const File& operator<<(float f) const;
	const File& operator<<(double d) const;

	const File& operator<<(int i) const;
	const File& operator<<(short w) const;
	const File& operator<<(char ch) const;
	const File& operator<<(unsigned u) const;

	const File& operator<<(LPCTSTR str) const;

	// extraction operations
	File& operator>>(bool& b);
	File& operator>>(BYTE& by);
	File& operator>>(WORD& w);
	File& operator>>(DWORD& dw);
	File& operator>>(LONG& l);
	File& operator>>(float& f);
	File& operator>>(double& d);

	File& operator>>(int& i);
	File& operator>>(short& w);
	File& operator>>(char& ch);
	File& operator>>(unsigned& u);

	File& operator>>(LPTSTR& str);
	File& operator>>(LPCTSTR& str);


	const File& operator<<(std::string str) const;
	File& operator>>(std::string &str);

	//don`t call close() function when call this fun
	void attach(HANDLE hFile,bool isload=false);

	void WriteBytes(const void *pData, size_t sz) const;
	void ReadBytes(void *pData, size_t sz) ;
private :
	HANDLE file_handle_;
	bool load_;

	File(const File& rhs);
	File& operator=(const File& rhs);

private:
	MCT_DEF
};
}
#endif // !defined(AFX_FILE_H__BEB08E98_655F_4413_9443_43C4A3E8797E__INCLUDED_)
