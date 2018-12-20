
#include "StdAfx.h"
#include "Mirror_Command.h"
#include "../object/Global.h"

#include "Matrix_d.h"
#include "Entity.h"
#include "Normal.h"
#include "Line.h"

namespace dlhml
{

bool Mirror_Command::cad_cammand(const Line& ln)
{
  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;
  copy(x, n);

  Matrix mat_move;
  Point pt0;
  mat_move.set_move(pt0 - ln.start());
  matcal<Entity>(n, mat_move);

  Matrix mat_rota;
  Normal nor(ln);
  Float  gamma=0;
  normal2d_2_radian(nor, gamma);
  gamma = -gamma;
  std_radian(gamma);
  mat_rota.set_z_rotation_radian(gamma);
  matcal<Entity>(n, mat_rota);

  Matrix mat_mirror;
  mat_mirror.set_x_axis_mirror();
  matcal<Entity>(n, mat_mirror);

//  Matrix mat;
//  Normal nor(ln), n_n;
//  Float mymir=0, n_mir=0, lnmir=0;
//  normal2d_2_radian(nor,lnmir);
//  std::vector<Point> pts;
//  Point pt;
//  int i=0,k=0;
//  for(i=0; i<n.size(); i++){
//    pts.clear();
//    n[i]->getctrl(pts);
//    for(k=0; k<pts.size(); k++){
//      pt=pts[k];
//      if(pt==Point()){
//        continue;
//      }
//      n_n.set_data(pts[k]);
//      normal2d_2_radian(n_n, n_mir);
//      mymir = (lnmir-n_mir)*2;
//      std_radian(mymir);
//      mat.set_z_rotation(mymir);
//      pts[k].transformby(mat);
//      pt=pts[k];
//    }
//    n[i]->setctrl(pts);
//  }

  gamma = -gamma;
  std_radian(gamma);
  mat_rota.set_z_rotation_radian(gamma);
  matcal<Entity>(n, mat_rota);

  mat_move.set_move(ln.start());
  matcal<Entity>(n, mat_move);

  return true;
}



}//namespace
