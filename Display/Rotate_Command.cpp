
#include "StdAfx.h"
#include "Rotate_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Entity.h"
#include "Normal.h"
#include "Line.h"

namespace dlhml
{

bool Rotate_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;
  copy(x, n);

  Matrix mat0;
  Point pt0;
  mat0.set_move(pt0 - ln.start());
  matcal<Entity>(n, mat0);

  Matrix mat;
  Normal nor(ln);
  Float gamma;
  normal2d_2_radian(nor,gamma);
  mat.set_z_rotation_radian(gamma);
  matcal<Entity>(n, mat);

  mat0.set_move(ln.start());
  matcal<Entity>(n, mat0);

  return true;
}
Point Rotate_Command::key_cammand(const Point& begin, const Point& way, double val)
{
  Normal nor;
  if(nor.is_zero_normal()){
    nor.x(1);
  }
  degree_2_normal2d(val, nor);
	return begin.polarTo(100, nor);
}
LPCTSTR Rotate_Command::endpt_cmd_out()
{
  return "Specify the rotary angle(degree).";
}

}//namespace
