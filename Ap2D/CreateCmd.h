
#ifndef _CREATE_STEEL_H_
#define _CREATE_STEEL_H_

#include "Create_Command.h"




namespace dlhml
{

class CreateCmd : public Create_Command
{
public:
  CreateCmd(Scene& scene, Entity* org);

protected:
  virtual void closeme(){delete this;}
  virtual Create_Entity* cloneme();



private:
  virtual void insert_to_db_p(Entity* entity);
  virtual void remove_from_db_p(Entity* entity);

};



}//namespace

#endif//FILE
