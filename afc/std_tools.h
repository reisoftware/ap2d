#ifndef _AFC_STD_TOOLS_H_
#define _AFC_STD_TOOLS_H_

#include <vector>

namespace afc{

template<class T>
void push_back(std::vector<T>& dst, const std::vector<T>& src)
{
	int n=src.size();
	int i=0;
	for(i=0; i<n; ++i){
		dst.push_back(src[i]);
	}
}

template<class T>
void push_back_p2o(std::vector<T>& dst, const std::vector<T*>& src)
{
	int n=src.size();
	int i=0;
	for(i=0; i<n; ++i){
		if(src[i]){
			dst.push_back(*src[i]);
		}
	}
}

template<class T>
void push_back_deep(std::vector<T*>& dst, const std::vector<T*>& src)
{
	int n=src.size();
	int i=0;
	for(i=0; i<n; ++i){
		T * t = T::create();
		*t = *src[i];
		dst.push_back(t);
	}
}

template<class T>
void close(std::vector<T*>& ts)
{
	int n=ts.size();
	int i=0;
	for(i=0; i<n; ++i){
		if(!ts[i]){
			continue;
		}
		ts[i]->close();
		ts[i] = NULL;
	}
	ts.clear();
}

// template<class T, class PARAM1>
// class Std
// {
// 	typedef void (T::*PF)(PARAM1&);
// public:
// 	void for_each(std::vector<T>& ts, PARAM1& param1, PF pf)
// 	{
// 		int n=ts.size();
// 		int i=0;
// 		for(i=0; i<n; ++i){
// 			T * t = &ts[i];
// 			(t->*pf)(param1);
// 		}
// 	}
// };

template<class T, class PARAM1>
void for_each(std::vector<T>& ts, PARAM1 param1, void (T::*pf)(PARAM1))
{
	int n=ts.size();
	int i=0;
	for(i=0; i<n; ++i){
		((ts[i]).*pf)(param1);
	}
}
template<class T, class PARAM1>
void for_each(std::vector<T*>& ts, PARAM1 param1, void (T::*pf)(PARAM1))
{
	int n=ts.size();
	int i=0;
	for(i=0; i<n; ++i){
		((ts[i])->*pf)(param1);
	}
}

}//namespace

#endif//FILE
