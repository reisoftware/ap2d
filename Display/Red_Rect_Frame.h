//
//#ifndef __RED_RECT_FRAME_H__
//#define __RED_RECT_FRAME_H__
//
//
//#include <vector>
//#include "Entity.h"
//#include "Point.h"
//#include "Rect.h"
//#include "Scene_d.h"
//
//namespace dlhml
//{
//
//class Entity;
//class Point;
//class Rect;
//class Scene;
//
//
//class Red_Rect_Frame
//{
//public:
//  Red_Rect_Frame(Scene& scene);
//  ~Red_Rect_Frame();
//
//public:
//  void xor_draw();
//
//public:
//  void clear();
//  void push_back( const Point& pt, 
//                  void(*selected_fptr)(), 
//                  void(*drag_fptr)(Scene& scene,Entity&,Point),
//                  void(*reset_fptr)(Entity&,Point));
//  void selected(const Point& pt);
//  void drag(Scene& scene, Entity& ent, Point pt);
//  void reset(Entity& ent, Point pt);
//
//public:
//  void get_rect(const Point& pt, Rect& rc);
//
//private:
//  Float pick_rect_edge_length();
//  int find_rect(const Point& pt);
//
//private:
//  Scene& scene_;
//  std::vector<Point> pts_;
//  std::vector<void(*)()> selected_fptrs_;
//  std::vector<void(*)(Scene&,Entity&,Point)> drag_fptrs_;
//  std::vector<void(*)(Entity&,Point)> reset_fptrs_;
// 
//  int cur_index_;
//};
//
//
//
//}//namespace
//
//
//#endif