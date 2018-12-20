
#include "StdAfx.h"
#include "Re0_Dim_Command.h"
#include "../object/Global.h"

#include "Entity.h"
#include "Line.h"
#include "Ln_Dim.h"
#include "Ln_Dim_Block.h"

#include "Paint_Entity_Tools.h"

namespace dlhml
{

bool Re0_Dim_Command::cad_cammand(const Line& ln)
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
  int pos=0;
  Point pt = ln.end();
  Point sel_ept;
  Ln_Dim_Block * block = (Ln_Dim_Block*)n[0];
  if(block->size()<=1){
    return false;
  }
  Ln_Dim * sel_dim = block->select_from_extendline(pos, rc_);
  if(sel_dim){
    if(pos==1){
      return false;
    }
    pt = sel_dim->ept();
    block->erase(sel_dim);    ////此时不可删除////
//    sel_ept = sel_dim->ept();
//    sel_dim->ept(block->opt());
//    block->opt(sel_ept);
//    Paint_Entity_Tools::recal_dim_block(*block);
//    return true;
  }
  else if(block->is_in_beeline_by_entendline(pt)){
    return false;
  }

  Ln_Dim * new_dim = (Ln_Dim*)(block->front()->clone());
//  if(sel_dim){
//    block->insert(sel_dim,new_dim);
//  }
//  else{
//    block->push_back(new_dim);
//  }
  new_dim->ept(block->opt());
  new_dim->opt(pt);
  block->opt(pt);

  block->push_back(new_dim);
//  block->recal_e_pt();
//  pt=new_dim->ept();
//  sel_dim = block->get_insert_pos(pt);
//  block->insert(sel_dim,new_dim);
  //recal_spt();
  Paint_Entity_Tools::recal_dim_block(*block);

  return true;
}

}//namespace
