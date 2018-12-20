
#ifndef _TIAN_DISPLAY_CAD_OFFSET_COMMAND_H_
#define _TIAN_DISPLAY_CAD_OFFSET_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Offset_Command : public Cad_Command
{
public:
  Offset_Command()MCT_INIT1("Offset_Command"){}
  virtual ~Offset_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);

  virtual Point key_cammand(const Point& begin, const Point& end);
  virtual Point key_cammand(const Point& begin, const Point& way, double val);

  virtual bool is_ortho(){return false;}

private:
  Point output_pt(const Line& ln, const Point& way);
  Point output_pt(const Line& ln, const Point& way, double dis);
	
private:
	MCT_DEF
};

}

#endif//FILE
