
#ifndef _DISPLAY_CAD_ARRAY_COMMAND_H_
#define _DISPLAY_CAD_ARRAY_COMMAND_H_

//
#include "Cad_Command.h"
#include "Entity_Array.h"

namespace dlhml
{

class Array_Command : public Cad_Command
{
public:
  Array_Command()MCT_INIT1("Array_Command"){}
  virtual ~Array_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);

  virtual void set_array(const Entity_Array& ary){ary_ = ary;}

protected:
  Entity_Array ary_;

protected:
	void clone_col(const std::vector<Entity*>& seed, 
											 std::vector<Entity*>& fruit)const;
	void clone_row(const std::vector<Entity*>& seed,
											 std::vector<Entity*>& fruit)const;
private:
	MCT_DEF
};

}//namespace
#endif//FILE
