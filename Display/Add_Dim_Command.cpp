
#include "StdAfx.h"
#include "Add_Dim_Command.h"
#include "../object/Global.h"

#include "../object/Entity.h"
#include "Line.h"
#include "Ln_Dim.h"
#include "Ln_Dim_Block.h"

#include "Paint_Entity_Tools.h"

namespace dlhml
{

bool Add_Dim_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;

  copy(x, n);
  if(n.size()!=1 || n[0]->myclass()!=LINE_DIM_BLOCK){
    return false;
  }
  Point pt = ln.end();
  Ln_Dim_Block * block = (Ln_Dim_Block*)n[0];
  if(block->size()<=0){
    return false;
  }
  if(block->is_in_beeline_by_entendline(pt)){
    return false;
  }
  Ln_Dim * back_dim = block->back();
  Ln_Dim * new_dim = (Ln_Dim*)(back_dim->clone());
  new_dim->ept(pt);
  block->push_back(new_dim);
//  Ln_Dim * pos = block->get_insert_pos(pt);
//  block->insert(pos, new_dim);
//  if(pos){
//    block->insert(pos, new_dim);
//  }
//  else{
//      block->push_back(new_dim);
//  }
  //recal_spt();
  Paint_Entity_Tools::recal_dim_block(*block);

  return true;
}

}//namespace
