
#ifndef _TIAN_DISPLAY_CAD_BLOCK_COMMAND_H_
#define _TIAN_DISPLAY_CAD_BLOCK_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Block_Command : public Cad_Command
{
public:
  Block_Command()MCT_INIT1("Block_Command"){}
  virtual ~Block_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
private:
	MCT_DEF
};

}

#endif//FILE

