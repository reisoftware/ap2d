
#include "StdAfx.h"
#include "Insert_Command.h"

#include "../include/getrace.h"

#include "Matrix_d.h"
#include "Entity.h"
#include "Line.h"

#include "Create_Entity.h"

#include "../object/Global.h"

namespace dlhml
{

bool Insert_Command::cad_cammand(const Line& ln)
{
//	TRACE_OUT("\nInsert_Command::cad_cammand()\n");
  if(!new_){
    return false;
  }
  //std::vector<Entity*>& o = *old_;
  std::vector<Entity*>& n = *new_;
  

  if(ents_.empty()){
//		TRACE_OUT("ents_.empty()\n");
    return false;
  }
  Matrix mat;
  mat.set_move(ln);
	std::vector<Entity*> es;
	dlhml::copy(ents_, es, mat);
	////要求备份
	if(cur_){
		cur_->copy_bk(ents_, es);
	}
	dlhml::push_back<Entity>(es, n);
  return true;
}
// bool Insert_Command::cad_cammand(const Line& ln)
// {
//   if(!new_){
//     return false;
//   }
//   //std::vector<Entity*>& o = *old_;
//   std::vector<Entity*>& n = *new_;
//   
// 
//   if(!entity_){
//     return false;
//   }
//   Entity * e = entity_->clone();
//   Point f = e->focus();
//   Matrix mat;
//   mat.set_move(f,ln.end());
//   e->transformby(mat);
//   n.push_back(e);
// 
//   return true;
// }

void Insert_Command::set_insert(const Entity * e)
{
	ents_.clear();
	ents_.push_back(const_cast<Entity*>(e));
}
void Insert_Command::set_insert(std::vector<Entity*>& es)
{
	ents_=es;
}


}//namespace
