#ifndef _SERIALIZE_H
#define _SERIALIZE_H

template <class T> inline
CArchive& Serialize(CArchive& ar,T& t)
{
	if(ar.IsLoading())
	{
		int count = 0;
		ar >> count;
		t.resize(count);
		for(int i = 0; i< count ; i++)
			ar >> t[i];
	}
	else
	{
		int count = t.size();
		ar << count;
		for(int i =0; i< count ; i++)
			ar << t[i]; 
	}
	return ar;
}

#endif
