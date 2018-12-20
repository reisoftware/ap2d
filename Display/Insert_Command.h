
#ifndef _TIAN_DISPLAY_CAD_INSERT_COMMAND_H_
#define _TIAN_DISPLAY_CAD_INSERT_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Entity;

class Insert_Command : public Cad_Command
{
public:
  Insert_Command()MCT_INIT1("Insert_Command"){}
  virtual ~Insert_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);

  void set_insert(const Entity * e);
  void set_insert(std::vector<Entity*>& es);
private:
  //const Entity * entity_;
	std::vector<Entity*> ents_;
	
private:
	MCT_DEF
};

}

#endif//FILE
