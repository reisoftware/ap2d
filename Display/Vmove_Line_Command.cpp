
#include "StdAfx.h"
#include "Vmove_Line_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Normal.h"
#include "Entity.h"
#include "Line.h"

namespace dlhml
{

bool Vmove_Line_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;
  copy(x, n);
  Matrix mat;
  mat.set_move(ln);
  matcal<Entity>(n, mat);

  return true;
}

Point Vmove_Line_Command::key_cammand(const Point& begin, const Point& end)
{
  if(!xor_ || xor_->empty()){
    return end;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Point> pts;
  xor_->back()->getctrl(pts);
  if(pts.size()<2){
    return end;
  }
  Line ln(pts.front(),pts.back());
  double dis = ln.distanceto(end);
  return key_cammand(begin, end, dis);
}
Point Vmove_Line_Command::key_cammand(const Point& begin, const Point& way, double val)
{
  if(!xor_ || xor_->empty()){
    return way;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Point> pts;
  xor_->back()->getctrl(pts);
  if(pts.size()<2){
    return way;
  }
  Normal nor(pts.front(),pts.back());
  nor.rota_z(90);
  Point ext = begin.polarTo(val, nor);
  Line ln(begin,ext);
  Point dicular = ln.perpendicular(way); // ´¹×ã
  nor.set_data(begin,dicular);
  return begin.polarTo(val, nor);
}

}//namespace
