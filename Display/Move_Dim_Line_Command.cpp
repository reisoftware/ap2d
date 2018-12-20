
#include "StdAfx.h"
#include "Move_Dim_Line_Command.h"
#include "../object/Global.h"

#include "Entity.h"
#include "Normal.h"
#include "Line.h"
#include "Ln_Dim.h"
#include "Ln_Dim_Block.h"

#include "Paint_Entity_Tools.h"

namespace dlhml
{

bool Move_Dim_Line_Command::cad_cammand(const Line& ln)
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
  Normal nor;
  nor.set_data(ln);
  block->offset_dimlines(nor);
  //recal_spt();
  //Paint_Entity_Tools::recal_dim_block(*block);

  return true;
}

}//namespace
