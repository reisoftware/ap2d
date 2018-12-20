
#ifndef _TIAN_DISPLAY_CAD_MIRROR_COMMAND_H_
#define _TIAN_DISPLAY_CAD_MIRROR_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Mirror_Command : public Cad_Command
{
public:
  Mirror_Command()MCT_INIT1("Mirror_Command"){}
  virtual ~Mirror_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	virtual bool is_reset_begin(){return true;}
	
private:
	MCT_DEF
};

}

#endif//FILE
