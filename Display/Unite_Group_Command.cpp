
#include "StdAfx.h"
#include "Unite_Group_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Entity.h"

namespace dlhml
{

bool Unite_Group_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;
  copy(x, n);

  Entity * main_e = n.front();
  std::string group_name = main_e->group();
  if(group_name.empty()){
    const int pt_format_buf_size = 128;
	  char buf[pt_format_buf_size];
	  int len = sprintf(buf, "%d\0", main_e->entity_id().entity_id());
    group_name = buf;
  }
  int i=0;
  for(i=0; i<n.size(); i++){
    n[i]->group(group_name.c_str());
  }

  return true;
}
  

}//namespace
