

#ifndef _Flags_h_
#define _Flags_h_

#include <vector>
#include "counter.h"

#pragma warning (disable:4251)

namespace dlhml{

  class Flags
  {
  public:
    Flags();
    Flags(int size);

  public:
    int  size()const;
    void resize(int size);
    void init();

  public:
    bool& operator[] (int index);
    const bool& operator[] (int index)const;

    const Flags& operator= (const Flags& rhs);

  public:
    void reverse(int index);
    void setat(int index, bool b);
    void radio(int index);

  private:
  private:
    int size_;
    std::vector<bool> flags_;
		
	private:
		MCT_DEF
	};

  
}

#endif//FILE





