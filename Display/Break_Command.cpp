
#include "StdAfx.h"
#include "../Display/Break_Command.h"

#include "../Display/Create_Entity.h"

#include "../object/Entity.h"
#include "../object/Line.h"

#include "../object/Global.h"

#include "../include/getrace.h"

namespace dlhml
{

bool Break_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;
//  copy(x, n);
//  extend(n,ln);
//	TRACE_OUT("Break_Command::cad_cammand(const Line& ln)\n");
  int i=0;
  for(i=0; i<x.size(); i++){
    if(!x[i]){
      continue;
    }
		std::vector<Entity*> es;
		if(num_>0){
			x[i]->split(num_, dis_, es);
		}else{
			x[i]->split(ln,es);
		}
//		TRACE_OUT("After break: The %d ln, bk.size == %d\n", i, es.size());
		////要求备份
		if(cur_){
			cur_->copy_bk(x[i], es);
		}
		dlhml::push_back<Entity>(es, n);
  }

  return true;
}

}//namespace
