
#ifndef _TIAN_DISPLAY_CAD_TRIM_COMMAND_H_
#define _TIAN_DISPLAY_CAD_TRIM_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{


class Trim_Command : public Cad_Command
{
public:
  Trim_Command()MCT_INIT1("Trim_Command"){}
  virtual ~Trim_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	virtual bool is_reset_begin(){return true;}//	用于需要重新指定begin_
	
private:
	MCT_DEF
};

}

#endif//FILE
