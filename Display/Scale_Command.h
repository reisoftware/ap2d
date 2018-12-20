
#ifndef _TIAN_DISPLAY_CAD_SCALE_COMMAND_H_
#define _TIAN_DISPLAY_CAD_SCALE_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Scale_Command : public Cad_Command
{
public:
  Scale_Command()MCT_INIT1("Scale_Command"){}
  virtual ~Scale_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
  virtual Point key_cammand(const Point& begin, const Point& way, double val);
  virtual LPCTSTR  endpt_cmd_out();
	virtual bool is_keep_begin(){return true;}
	virtual bool is_reset_begin(){return false;}

	virtual CADTYPE cadtype()const{return SCALECMD;}
	
private:
	MCT_DEF
};

}

#endif//FILE
