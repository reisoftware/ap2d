
#include "StdAfx.h"
#include "Del_Dim_Command.h"
#include "../object/Global.h"

#include "Entity.h"
#include "Line.h"
#include "Ln_Dim.h"
#include "Ln_Dim_Block.h"

#include "Paint_Entity_Tools.h"

namespace dlhml
{

bool Del_Dim_Command::cad_cammand(const Line& ln)
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
  if(block->size()<2){
    return false;
  }
  int pos=0;
  Ln_Dim * sel_exln = block->select_from_extendline(pos, rc_);
  if(!sel_exln || (block->mode()==PILEUP_DIM && pos==1) ){
    return false;
  }
  block->erase(sel_exln);
  
  //recal_spt();
  Paint_Entity_Tools::recal_dim_block(*block);

  return true;
}

}//namespace
