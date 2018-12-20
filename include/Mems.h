#ifndef _MEMS_H_
#define _MEMS_H_

#pragma warning(disable: 4786)

#include <map>
#include "CMember.h"

class AFX_EXT_CLASS Mems
{
typedef std::map<int,CMember> MEMS;
	mutable MEMS mems_;
public:
	typedef MEMS::iterator iterator;
private:
	mutable iterator it_;
	mutable int index_;
public:
	iterator begin() const;

	iterator end() const;

	CMember& operator[](iterator it) const;
	CMember& operator[](int index) const;
	CMember& Add(CMember& t);
	
	CMember* get(iterator it) const;
	CMember* get(int key) const;
	int GetSize() const;
	void RemoveAll();
/*
	template<class Fun> for_each(Fun f)
		{
		iterator it;
		for(it = begin(); it != end(); ++it){
			if(f(get(it)) != 0)
				break;
		}
		}
	*/	
};
#endif
