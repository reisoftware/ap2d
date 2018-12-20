
#include "StdAfx.h"
#include "Split_Block_Command.h"

#include "Matrix_d.h"
#include "Entity.h"

namespace dlhml
{

bool Split_Block_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;

  std::vector<Entity*> temp;
  int i=0;
  for(i=0; i<x.size(); i++){
    x[i]->get_ptr(temp);
  }
  for(i=0; i<temp.size(); i++){
    Entity* e = temp[i]->clone();
    n.push_back(e);
  }

  return true;
}

}//namespace
