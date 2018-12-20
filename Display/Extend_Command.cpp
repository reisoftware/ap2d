
#include "StdAfx.h"
#include "Extend_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Entity.h"

namespace dlhml
{

bool Extend_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;
  copy(x, n);
  extend(n,ln);

  return true;
//  int i=0;
//  for(i=0; i<n.size(); i++){
//    n[i]->extend(ln);
//  }
}

}//namespace
