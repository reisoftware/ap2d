
#ifndef _TIAN_DISPLAY_CAD_STRECH_COMMAND_H_
#define _TIAN_DISPLAY_CAD_STRECH_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Strech_Command : public Cad_Command
{
public:
  Strech_Command()MCT_INIT1("Strech_Command"){}
  virtual ~Strech_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	virtual CADTYPE cadtype()const{return STRECHCMD;}
	
private:
	MCT_DEF
};

}

#endif//FILE
