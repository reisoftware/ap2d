
#include "StdAfx.h"
#include "Move_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Entity.h"

namespace dlhml
{

bool Move_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;

	std::vector<Entity*> t1, t2;
	dlhml::push_back<Entity>(x, t1);

	if(count_ <= 0){
		count_ = 1;
	}

	int i=0;
	for(i=0; i<count_; ++i){
		dlhml::copy(t1, t2);
		Matrix mat;
		mat.set_move(ln);
		matcal<Entity>(t2, mat);
		dlhml::push_back<Entity>(t2, n);
		t1.clear();
		dlhml::push_back<Entity>(t2, t1);
		t2.clear();
	}

	count_ = 1;////»Ö¸´1

  return true;
}

}//namespace
