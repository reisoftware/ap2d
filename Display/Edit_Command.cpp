
#include "StdAfx.h"
#include "Edit_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Entity.h"
#include "Line.h"
#include "Ln_Dim_Block.h"
#include "Paint_Entity_Tools.h"

namespace dlhml
{

Edit_Command::Edit_Command()
:red_ent_(0)
,red_pt_ (0)
MCT_INIT2("Edit_Command")
{
}

bool Edit_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;

  copy(x, n);
  std::vector<Point> pts;
  n[red_ent_]->getdrag(pts);
  pts[red_pt_] = ln.end();
  n[red_ent_]->setdrag(pts,red_pt_);

  if(n[0]->myclass() == LINE_DIM_BLOCK){
    Ln_Dim_Block * block = static_cast<Ln_Dim_Block*>(n[0]);
    if(block->mode() == PILEUP_DIM){
      //Paint_Entity_Tools::reset_dim_text_pos_layer(*block);
    }
    else{
      //Paint_Entity_Tools::reset_dim_text_pos_layer_closed(*block);
    }
  }
  return true;
}

void Edit_Command::set_edit(int ent, int pt)
{
  red_ent_ = ent;
  red_pt_  = pt ;
}

}//namespace
