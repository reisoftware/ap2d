
#ifndef _TIAN_DISPLAY_CAD_SPLIT_BLOCK_COMMAND_H_
#define _TIAN_DISPLAY_CAD_SPLIT_BLOCK_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Split_Block_Command : public Cad_Command
{
public:
  Split_Block_Command()MCT_INIT1("Split_Block_Command"){}
  virtual ~Split_Block_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	
private:
	MCT_DEF
};

}

#endif//FILE
