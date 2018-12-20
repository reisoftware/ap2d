
#include "StdAfx.h"
#include "Red_Rect_Frame.h"
/*
#include "Rect.h"
#include "Paint_Entity.h"
#include "Painter.h"
#include "Point.h"
#include "Scene_d.h"

namespace dlhml
{

Red_Rect_Frame::Red_Rect_Frame(Scene& scene)
: scene_(scene)
{
}

Red_Rect_Frame::~Red_Rect_Frame()
{
}

void Red_Rect_Frame::get_rect(const Point& pt,Rect& rc)
{
  Float len = pick_rect_edge_length() * scene_.screen_to_world().value(0,0);
  rc.xmin(pt.x-len);
  rc.xmax(pt.x+len);
  rc.ymin(pt.y-len);
  rc.ymax(pt.y+len);
}

Float Red_Rect_Frame::pick_rect_edge_length()
{
  return 5;
}

void Red_Rect_Frame::clear()
{
  pts_.clear();
}

void Red_Rect_Frame::push_back(const Point& pt, 
                               void(*selected_fptr)(), 
                               void(*drag_fptr)(Scene&,Entity&,Point),
                               void(*reset_fptr)(Entity&,Point))
{
  pts_.push_back(pt);

  selected_fptrs_.push_back(selected_fptr);
  drag_fptrs_.push_back(drag_fptr);
  reset_fptrs_.push_back(reset_fptr);

}

int Red_Rect_Frame::find_rect(const Point& pt)
{
  Rect rc;
  int pts_count = pts_.size();
  for(int i=0; i<pts_count; i++){
    get_rect(pts_[i], rc);
    if(pt.envelop(rc)){
      return i;
    }
  }
  return -1;
  
}

void Red_Rect_Frame::selected(const Point& pt)
{
  cur_index_ = find_rect(pt);
  if(cur_index_<0){
    return;
  }
  selected_fptrs_[cur_index_]();
}
 
void Red_Rect_Frame::drag(Scene& scene, Entity& ent, Point pt)
{
  drag_fptrs_[cur_index_](scene, ent,pt);
}

void Red_Rect_Frame::reset(Entity& ent, Point pt)
{
  reset_fptrs_[cur_index_](ent,pt);
}

void Red_Rect_Frame::xor_draw()
{
  Painter* painter = scene_.get_painter();
  Paint_Entity paint(scene_, *painter);

  Rect rc;
  std::vector<Point>::iterator it = pts_.begin();
  for(; it!=pts_.end(); it++){
    get_rect(*it, rc);
    paint.xor_draw_rect(rc);  
  }
}

}//namespace

*/
