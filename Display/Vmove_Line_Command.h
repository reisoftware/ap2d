
#ifndef _TIAN_DISPLAY_CAD_VMOVE_LINE_COMMAND_H_
#define _TIAN_DISPLAY_CAD_VMOVE_LINE_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Vmove_Line_Command : public Cad_Command
{
public:
  Vmove_Line_Command()MCT_INIT1("Vmove_Line_Command"){}
  virtual ~Vmove_Line_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);

  virtual Point key_cammand(const Point& begin, const Point& end);
  virtual Point key_cammand(const Point& begin, const Point& way, double val);

	
private:
	MCT_DEF
};

}

#endif//FILE
