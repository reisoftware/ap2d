#ifndef _AFC_ARRAY_H_
#define _AFC_ARRAY_H_


#include "export.h"

namespace ary{
  
  
  AFCAPI int size(void * p, int unitsize);
  AFCAPI void resize(void ** pp, int newcount, int unitsize);
  AFCAPI void add_size(void ** pp, int unitsize);
  AFCAPI void push_back(void ** pp, void * p, int unitsize);
  
  
}//namespace




#endif//FILE
