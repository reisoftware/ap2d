
#ifndef _TIAN_DISPLAY_CAD_ADD_DIM_COMMAND_H_
#define _TIAN_DISPLAY_CAD_ADD_DIM_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Add_Dim_Command : public Cad_Command
{
public:
  Add_Dim_Command()MCT_INIT1("Add_Dim_Command"){}
  virtual ~Add_Dim_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);

private:
	MCT_DEF
};


}

#endif//FILE
