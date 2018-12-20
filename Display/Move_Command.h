
#ifndef _TIAN_DISPLAY_CAD_MOVE_COMMAND_H_
#define _TIAN_DISPLAY_CAD_MOVE_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Move_Command : public Cad_Command
{
public:
  Move_Command()MCT_INIT1("Move_Command"){}
  virtual ~Move_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	
private:
	MCT_DEF
};

}

#endif//FILE
