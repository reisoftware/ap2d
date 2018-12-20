#ifndef _AFC_COUNTER_H_
#define _AFC_COUNTER_H_


#include <string>

#include "export.h"


///////////////////////
// #define  ENTITY_MY_CLASS_NAME
////////////////////////


///////////////////////
// #ifdef ENTITY_MY_CLASS_NAME
// 
// #define MCT_DEF  
// #define MCT_INIT1(s) :ct_(s),myclass_(s)
// #define MCT_INIT2(s) ,ct_(s),myclass_(s)
///////////////////////


// #define  AFC_MCounter
#ifdef AFC_MCounter

class AFCAPI MCounter
{
public:
  MCounter(LPCTSTR name);
  MCounter(const MCounter& rhs);
  ~MCounter();
  
private:
  std::string name_;
};

#define MCT_DEF  MCounter ct_;
#define MCT_INIT1(s) :ct_(s)
#define MCT_INIT2(s) ,ct_(s)


////////////////////////
#else

#define MCT_DEF   
#define MCT_INIT1(s)  
#define MCT_INIT2(s)  

#endif//AFC_MCounter

#endif//FILE
