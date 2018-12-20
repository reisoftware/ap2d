#ifndef _AFC_CBK_H_
#define _AFC_CBK_H_

#include "export.h"

namespace afc{

  AFCAPI bool with_ctrl();
  AFCAPI bool with_shift();

  AFCAPI bool is_cbk(UINT n);
}//namespace

#endif//FILE
