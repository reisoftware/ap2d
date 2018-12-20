
#include "StdAfx.h"
#include "Multi_Insert_Command.h"

#include "Matrix_d.h"
#include "Entity.h"
#include "Line.h"
#include "Block.h"

#include "../object/Global.h"

namespace dlhml
{


bool Mulit_Insert_Command::cad_cammand(const Line& ln)
{
  if(side_<=0){
    return false;
  }
  if(!xor_it_ || !symbol_ || !dis_ || dis_->empty()){
    return false;
  }
  const std::vector<double>& d = *dis_;
  if(!new_){
    return false;
  }
  std::vector<Entity*>& n = *new_;

	double ent_rad = radian(xor_it_);

  int pt_size=0;
  Point spt, ept;
  std::vector<Point> pts;
  bool way=false;
  int i=0;
  
  Matrix mat;
  Point f;
  Point pt;
  Block* block=Block::create_me();
  Entity* symbol_it=NULL;
  for(i=0; i<d.size(); i++){
    pts.clear();
    xor_it_->getctrl(pts);
    pt_size = pts.size();
    if(pt_size<2){
      continue;
    }
    spt = pts[0];
    ept = pts[pt_size-1];
    way = spt.y <= ept.y ? true : false ;
    pt = xor_it_->polarTo(d[i], way);

    int s=0;
    for(s=0; s<side_; s++){
      symbol_it=symbol_->clone();
      rotate_symbol(symbol_it, ((double)s/side_)*pi2 + ent_rad);
      f=symbol_it->focus();
      mat.set_move(f,pt);
      symbol_it->transformby(mat);
      block->push_back(symbol_it);
    }
  }
  if(block->size()>0){
    block->focus(block->front()->focus());
  }

  n.push_back(block);

  return true;

//  Entity * e = entity_->clone();
//  Point f = e->focus();
//  Matrix mat;
//  mat.set_move(f,ln.end());
//  e->transformby(mat);
//  n.push_back(e);
}

void Mulit_Insert_Command::rotate_symbol(Entity* e, double radian)
{
  Matrix mat;
  mat.set_move(symbol_->focus(), Point(0,0));
  e->transformby(mat);
  mat.set_z_rotation_radian(radian);
  e->transformby(mat);
  mat.set_move(Point(0,0), symbol_->focus());
  e->transformby(mat);
}

}//namespace
