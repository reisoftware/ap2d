
#include "StdAfx.h"
#include "Scale_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Entity.h"
#include "Normal.h"
#include "Line.h"

namespace dlhml
{

bool Scale_Command::cad_cammand(const Line& ln)
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
  Float myscale = ln.length();
  myscale /= 100;
  mat.set_scale(myscale,myscale,myscale);
  matcal<Entity>(n, mat);

  mat0.set_move(ln.start());
  matcal<Entity>(n, mat0);

  return true;
}
Point Scale_Command::key_cammand(const Point& begin, const Point& way, double val)
{
	Normal nor;
	nor.set_data(begin, way);
  if(nor.is_zero_normal()){
    nor.x(1);
  }
  val *= 50;
	return begin.polarTo(val, nor);
}
LPCTSTR Scale_Command::endpt_cmd_out()
{
  return "Specify the magnifier's times.";
}

}//namespace
