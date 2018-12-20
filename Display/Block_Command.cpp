
#include "StdAfx.h"
#include "Block_Command.h"

#include "../object/Matrix_d.h"
#include "../object/Entity.h"
#include "../object/Block.h"
#include "Line.h"
#include "DB_Blocks.h"

namespace dlhml
{

bool Block_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;



	Entity * e = NULL; 
  Block * block = Block::create_me();
  int i=0;
  for(i=0; i<x.size(); i++){
		e = x[i]->clone();
    block->push_back(e);
  }
  block->focus(ln.end());
  n.push_back(block);


	

	
	DB_Blocks::instance()->add();



  return true;
}

}//namespace
