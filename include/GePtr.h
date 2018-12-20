#ifndef _GE_PTR
#define _GE_PTR

namespace GEXY{
template <class T>
inline T* clone(T* pT)
{
	return pT->clone();
}
template <class T>
inline void Release(T* pT)
{
	delete pT;
}

template <class T>
class CPtr
{
public:
	CPtr(T* t = 0):pT(t),pRef(new int(1)) {}

	CPtr(const CPtr& rhs):pT(rhs.pT),pRef(rhs.pRef)
	{
		++*pRef;
	}
	CPtr& operator =(const CPtr& rhs)
	{
		if(this != &rhs)
		{
			close();
			pT = rhs.pT;
			pRef = rhs.pRef;
			++*pRef;
		}
		return *this;
	}
	void unique()
	{
		if(*pRef != 1)
		{
			close();
			pRef = new int(1);
			pT = clone(pT);
		}
	}

	~CPtr() {
		close();
	}

	operator bool()const {return (pT != NULL);}
	T& operator*()const {return *PT;}
	T* operator->()const {return pT;}
	T* Get()const {return pT;} 
private:
	void close()
	{
		if(--*pRef == 0)
		{
			delete pRef;
			if(pT)
			{
				Release(pT);
				pT = NULL;
			}
		}
	}
	T* pT;
	int* pRef;
};
}
#endif