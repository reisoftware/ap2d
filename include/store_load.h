#ifndef _STORE_H_
#define _STORE_H_
namespace gelib{
template <class T> inline
CArchive& store_load(CArchive& ar,T& t)
{
	if(ar.IsLoading())
	{
		int count = 0;
		ar >> count;
		t.resize(count);
		for(int i = 0; i< count ; i++)
			t[i].Serialize(ar);;
	}
	else
	{
		int count = t.size();
		ar << count;
		for(int i =0; i< count ; i++)
			t[i].Serialize(ar); 
	}
	return ar;
}
}
#endif