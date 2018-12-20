
#ifndef _TIAN_DISPLAY_CAD_BREAK_COMMAND_H_
#define _TIAN_DISPLAY_CAD_BREAK_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{


class Break_Command : public Cad_Command
{
public:
  Break_Command():num_(0),dis_(0)MCT_INIT2("Break_Command"){}
  virtual ~Break_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);
	virtual bool is_reset_begin(){return true;}//	用于需要重新指定begin_

public:
	void num(int n){num_ = n;}
	void dis(double d){dis_ = d;}

private:
	int num_;
	double dis_;

private:
	MCT_DEF
};

}

#endif//FILE
