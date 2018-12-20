#ifndef _AFC_BOOL_H_
#define _AFC_BOOL_H_

//#include "export.h"

// typedef int Bool;


namespace afc{

template<class T>
bool tobool(T b)
{
  return b ? true : false;
}


}//namespace

#endif//FILE
