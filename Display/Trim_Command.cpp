
#include "StdAfx.h"
#include "Trim_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Entity.h"

namespace dlhml
{

bool Trim_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;
  copy(x, n);
  trim(n,ln);

  return true;
}

}//namespace
