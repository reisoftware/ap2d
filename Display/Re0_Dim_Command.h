
#ifndef _TIAN_DISPLAY_CAD_RE0_DIM_COMMAND_H_
#define _TIAN_DISPLAY_CAD_RE0_DIM_COMMAND_H_

#include "Cad_Command.h"
#include "Rect.h"

namespace dlhml
{

class Re0_Dim_Command : public Cad_Command
{
public:
  Re0_Dim_Command()MCT_INIT1("Re0_Dim_Command"){}
  virtual ~Re0_Dim_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
  virtual void set_rect(const Rect& rc){rc_=rc;}

private:
  Rect rc_;
	
private:
	MCT_DEF
};

}

#endif//FILE
