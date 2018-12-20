#ifndef _SERIALIZE_STD_H
#define _SERIALIZE_STD_H

#include "serialize.h"
#include <vector>
#include <string>

inline CArchive& operator << (CArchive& ar,std::vector<int>& ary)
{
	return Serialize(ar,ary);
}
inline CArchive& operator << (CArchive& ar,std::string& ary)
{
	return Serialize(ar,ary);
}

inline CArchive& operator >> (CArchive& ar,std::vector<int>& ary)
{
	return Serialize(ar,ary);
}
inline CArchive& operator >> (CArchive& ar,std::string& ary)
{
	return Serialize(ar,ary);
}
#endif
