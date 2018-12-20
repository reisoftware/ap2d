#ifndef _GELIB_ATTRIBUTE_H_
#define _GELIB_aTTRIBUTE_H_
#include <map>
#include <vector>
namespace gelib{
	template<class T>
		class Attribute{
			typedef std::map<int,T> ARRAY;
		  ARRAY arys_;

			int index_;
			ARRAY::iterator it_;
			public:

				typedef ARRAY::iterator iterator;

				iterator begin()
				{
					return arys_.begin();
				}

				iterator end()
				{
					return arys_.end();
				}
				T& operator[](iterator& it)
				{
					return it->second;
				}

				int GetSize()
				{
					return arys_.size();
				}
				T* get(int key)
				{
					ARRAY::iterator it;
					it = arys_.find(key);
					if(it != arys_.end())
						return &(it->second);
					else
						return NULL;
				}
				T& operator[](int index)
				{
					if(it_ != arys_.end() && index_ < index){
					for(int i= index_; i < index; ++i)
						++it_;
					index_ = index;
					}
					else {
						it_ = arys_.begin();
						for(int i = 0; i < index; ++i)
							++it_;
						index_ = index;
					}
					return it_->second;
				}
			
				void RemoveAll()
				{
					arys_.clear();
					index_ = -1;
					it_ = arys_.end();
				}
				T& Add(T& t)
				{
					arys_[t.iIndex] = t;
					index_ = -1;
					it_ = arys_.end();
					return arys_[t.iIndex];
				}
				template <class FUN> for_each(FUN fun){
					ARRAY::iterator it;
					for(it = arys_.begin(); it != arys_.end(); ++it){
						T* t = &(it->second);
						if(fun(t) == 1)
							break;
					}

				}

		};
}
#endif