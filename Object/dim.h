#ifndef _OBJECT_DIM_H_
#define _OBJECT_DIM_H_

#include "export.h"
#include "style.h"

namespace dlhml{

class OBJECT_API Dim
{

protected:
  Style style_;
  std::string fixed_;   //  替代文字(如有内容，则强制使用该文字内容)
};


}//namespace

#endif//FILE
