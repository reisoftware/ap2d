
#ifndef _TIAN_DISPLAY_CAD_EDIT_COMMAND_H_
#define _TIAN_DISPLAY_CAD_EDIT_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Edit_Command : public Cad_Command
{
public:
  Edit_Command();
  virtual ~Edit_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
  //virtual void close();

public:
  virtual void set_edit(int ent, int pt);

protected:
  int red_ent_;
  int red_pt_ ;
	
private:
	MCT_DEF
};

}

#endif//FILE
