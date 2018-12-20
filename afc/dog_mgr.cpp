#include "stdafx.h"
#include "dog_mgr.h"
#include "Dog_Check.h"


namespace afc{
  
bool dog()
{
//    return true;
#ifdef NDEBUG
  gelib::Dog_Check dog;
  if(!dog.valid_dog()){
    ::MessageBox(NULL, "Check the guard dog, please.", "Guard Dog", MB_OK);
    return false;
  }
#endif //NDEBUG
  return true;
}
  
}//namespace

