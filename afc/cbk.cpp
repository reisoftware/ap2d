#include "stdafx.h"
#include "cbk.h"

namespace afc{

bool with_ctrl()
{  
  return ((::GetKeyState(VK_CONTROL)&(1<<(sizeof(SHORT)*8-1)))!=0);
}
bool with_shift()
{ 
  return ((::GetKeyState(VK_SHIFT	)&(1<<(sizeof(SHORT)*8-1)))!=0);
}

bool is_cbk(unsigned int n)
{
  if(n == VK_CONTROL){
    return true;
  }
  if(n == VK_SHIFT){
    return true;
  }
  return false;
}

}//namespace