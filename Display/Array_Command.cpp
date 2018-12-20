
#include "StdAfx.h"
#include "Array_Command.h"

#include <cassert>
#include <algorithm>

#include "../object/Matrix_d.h"
#include "../object/Normal.h"
#include "../object/Entity.h"

#include "../object/Global.h"


namespace dlhml
{


bool Array_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;

	if(ary_.col_num <= 0 || ary_.row_num <= 0){
		return false;
	}

	std::vector<Entity*> es;
	clone_row(x, es);
	assert(!es.empty() && "Array_Command::cad_cammand(");
	clone_col(es, n);
	assert(!n.empty() && "Array_Command::cad_cammand(");
	
	std::vector<Entity*>::iterator it;
	it = std::find(n.begin(), n.end(), x.back());
	assert(it != n.end() && "Array_Command::cad_cammand(");
	++it;
	n.erase(n.begin(), it);

  return true;
}

void Array_Command::clone_col(const std::vector<Entity*>& seed, 
																		std::vector<Entity*>& fruit)const
{
	if(seed.empty()){
		return;
	}

	dlhml::push_back<Entity>(seed, fruit);

	Point st;
	Point ed;
	Normal nor;
	Float deg = ary_.degree;
	dlhml::degree_2_normal2d(deg, nor);
	int i=0;
	for(i=1; i<ary_.col_num; ++i){
		ed = st.polarTo(ary_.col_dis*i, nor);
		Matrix mat;
		mat.set_move(st, ed);
		std::vector<Entity*> es;
		dlhml::copy(seed, es, mat);
		dlhml::push_back<Entity>(es, fruit);
	}
}


void Array_Command::clone_row(const std::vector<Entity*>& seed,
																 std::vector<Entity*>& fruit)const
{
	if(seed.empty()){
		return;
	}
	
	dlhml::push_back<Entity>(seed, fruit);

	Point st;
	Point ed;
	Normal nor;
	Float deg = ary_.degree + 90;
	dlhml::degree_2_normal2d(deg, nor);
	int i=0;
	for(i=1; i<ary_.row_num; ++i){
		ed = st.polarTo(ary_.row_dis*i, nor);
		Matrix mat;			
		mat.set_move(st, ed);
		std::vector<Entity*> es;
		dlhml::copy(seed, es, mat);
		dlhml::push_back<Entity>(es, fruit);
	}
}


}//namespace


