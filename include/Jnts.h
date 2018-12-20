#ifndef _JNTS_H_
#define _JNTS_H_
#pragma warning(disable: 4786)

#include <map>
#include "CJoint.h"

class AFX_EXT_CLASS Jnts
{
typedef std::map<int,CJoint> MEMS;
	mutable MEMS mems_;
public:
	typedef MEMS::iterator iterator;
private:
	mutable iterator it_;
	mutable int index_;
public:
	iterator begin() const;

	iterator end() const;

	CJoint& operator[](iterator it) const;
	CJoint& operator[](int index) const;
	CJoint& Add(CJoint& t);
	
	CJoint* get(iterator it) const;
	CJoint* get(int key) const;
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