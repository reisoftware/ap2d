

#include "stdafx.h"
#include "Entity_Edit.hpp"
#include "Scene_d.h"

namespace dlhml
{

//.cpp
//template<class T>
Entity_Edit/*<T>*/::Entity_Edit(Scene& scene)
: Create_Entity(scene)
{
  scene_.info_to_command_line("Select entitys, please.", true);
}

//template<class T>
void Entity_Edit/*<T>*/::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  if(vk_.enter()){
    Point pt;
    if(scene_.get_command_line_point(pt)){
      left_button_down_p(NULL, pt);
      scene_.info_to_command_line("", true);
      return;

    }
    return;
  }
}

//template<class T>
bool Entity_Edit/*<T>*/::execute_p()
{
  swap_Lns();
  //scene_.invalidate();
  return true;
}

//template<class T>
bool Entity_Edit/*<T>*/::unexecute_p()
{
  swap_Lns();
  //scene_.invalidate();
  return true;
}

//template<class T>
void Entity_Edit/*<T>*/::swap_Lns()
{
  int i(0);
  int data_size = data_.size();
  for(i=0; i<data_size; i++){
    remove_from_db(*data_[i]);
  }
  int temp_size = temp_.size();
  for(i=0; i<temp_size; i++){
    insert_to_db(*temp_[i]);
  }
  std::swap(data_, temp_);
  //swap_Lns();
  scene_.invalidate();

//  int data_size = data_.size();
//  int temp_size = temp_.size();
//  Line* data_ln = NULL;
//  Line* temp_ln = NULL;
//  for(int i=0; i<min(data_size, temp_size); i++){
//    data_ln = static_cast<T*>(data_[i]);
//    temp_ln = static_cast<T*>(temp_[i]);
//    std::swap(*data_ln, *temp_ln);
//  }
}

void Entity_Edit::push_back_data(Entity* entity)
{
  if(!entity){
    return;
  }
  data_.push_back(entity);
}

void Entity_Edit::push_back_temp(Entity* entity)
{
  if(!entity){
    return;
  }
  temp_.push_back(entity);
}




//namespace
}


