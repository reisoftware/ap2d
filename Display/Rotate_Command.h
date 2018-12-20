
#ifndef _TIAN_DISPLAY_CAD_ROTATE_COMMAND_H_
#define _TIAN_DISPLAY_CAD_ROTATE_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Rotate_Command : public Cad_Command
{
public:
  Rotate_Command()MCT_INIT1("Rotate_Command"){}
  virtual ~Rotate_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
  virtual Point key_cammand(const Point& begin, const Point& way, double val);
  virtual LPCTSTR  endpt_cmd_out();

	virtual bool is_there_temp(){return true;}
	virtual bool is_keep_begin(){return true;}
	virtual bool is_reset_begin(){return false;}

	virtual CADTYPE cadtype()const{return ROTACMD;}


private:
	MCT_DEF
};

}

#endif//FILE
