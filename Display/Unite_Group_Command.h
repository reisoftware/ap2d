
#ifndef _TIAN_DISPLAY_CAD_UNITE_GROUP_COMMAND_H_
#define _TIAN_DISPLAY_CAD_UNITE_GROUP_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Unite_Group_Command : public Cad_Command
{
public:
  Unite_Group_Command()MCT_INIT1("Unite_Group_Command"){}
  virtual ~Unite_Group_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	
private:
	MCT_DEF
};

}

#endif//FILE
