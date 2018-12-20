
#ifndef _TIAN_DISPLAY_CAD_MULIT_INSERT_COMMAND_H_
#define _TIAN_DISPLAY_CAD_MULIT_INSERT_COMMAND_H_

#include "Cad_Command.h"

namespace dlhml
{

class Entity;

class Mulit_Insert_Command : public Cad_Command
{
public:
  Mulit_Insert_Command():xor_it_(NULL),symbol_(NULL),side_(1)MCT_INIT2("Mulit_Insert_Command"){}
  virtual ~Mulit_Insert_Command(){}

public:
  virtual bool cad_cammand(const Line& ln);

  void rotate_symbol(Entity* e, double radian);

  void set_dis(const std::vector<double>* dis){dis_=dis;}
  void set_xor_it(const Entity * e){xor_it_=e;}
  void set_symbol(const Entity * e){symbol_=e;}
  void set_side(int side){side_=side;}
private:
  const Entity * xor_it_;
  const Entity * symbol_;
  int side_;
  const std::vector<double>* dis_;
	
private:
	MCT_DEF
};

}

#endif//FILE
