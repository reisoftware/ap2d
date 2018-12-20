
#ifndef _TIAN_OBJECT_GLOBAL_H_
#define _TIAN_OBJECT_GLOBAL_H_

#include <vector>

#include "Normal.h"
#include "Matrix_d.h"

#include "Entity.h"
#include "DrawEntity.h"

#include "Circle.h"
#include "Line.h"
#include "RArc.h"
#include "Lead_Dimension.h"

namespace dlhml
{

class Entity;
class Draw_Entity;

class Circle;
class Line;
class RArc;

inline std::vector<Entity*>::iterator find(const Entity * const e,std::vector<Entity*>& es);
inline int  find (const Entity * const e, const std::vector<Entity*>& es);
inline bool is_in(const Entity * const e, const std::vector<Entity*>& es);

inline void color  (std::vector<Entity*>& e, int cr);
inline void line_style(std::vector<Entity*>& e, LPCTSTR style);
inline void strech (std::vector<Entity*>& e, const Matrix& mat);
inline void select (std::vector<Entity*>& e, bool sel);
inline void extend (std::vector<Entity*>& e, const Line& ln);
inline void trim   (std::vector<Entity*>& e, const Line& ln);
inline void draw   (std::vector<Entity*>& e, Draw_Entity& out, bool xor=true);

inline void box2d(Rect& rc, const std::vector<Entity*>& es);

inline void destory(std::vector<Entity*>& e);

inline void destory(Entity*& e);
inline void destory(std::vector<Entity*>& e);
inline void destory(std::vector<Line  *>& e);
inline void destory(std::vector<RArc  *>& e);
inline void destory(std::vector<Circle*>& e);

inline void erase(std::vector<Entity*>& es, const Entity * e);

////克隆后加入
inline void copy(const std::vector<Entity*>& s, std::vector<Entity*>& d);
inline void copy(const std::vector<Lead_Dimension*>& s, std::vector<Lead_Dimension*>& d);
//template<class T>
//void copy(const std::vector<T*>& s, std::vector<T*>& d);

////直接把加入指针，不克隆
inline void push(const std::vector<Entity*>& s, std::vector<Entity*>& d);
inline void push(const std::vector<Line  *>& s, std::vector<Entity*>& d);
inline void push(const std::vector<RArc  *>& s, std::vector<Entity*>& d);
inline void push(const std::vector<Circle*>& s, std::vector<Entity*>& d);

inline void push(const std::vector<Entity*>& s, std::vector<Line  *>& d);


////矩阵运算角度
inline void transformby2d_radian  (const Matrix& mat, Float& rad);
inline void transformby2d_distance(const Matrix& mat, Float& dis);

//inline void line_style(std::vector<Entity*>& e, const std::string& ln_style);
//bool intersect(const std::vector<Entity*>& e, const Rect& rc);

//template<class T>






////在集合中查找某个实体，不在返回NULL
inline std::vector<Entity*>::iterator find(const Entity * const e,std::vector<Entity*>& es)
{
	std::vector<Entity*>::iterator it = es.begin();
	for(; it!=es.end(); it++){
    if(!e || !(*it)){
      continue;
    }
		if(e == *it){
			return it;
		}
	}
	return NULL;
}

////在集合中查找某个实体，不在返回-1
inline int find(const Entity * const e,const std::vector<Entity*>& es)
{
	int i=0;
	for(i=0; i<es.size(); i++){
    if(!e || !(es[i])){
      continue;
    }
		if(e == es[i]){
			return i;
		}
	}
	return -1;
}

////实体是否在集合中
inline bool is_in(const Entity * const e,const std::vector<Entity*>& es)
{
	int i=0;
	for(i=0; i<es.size(); i++){
    if(!e || !(es[i])){
      continue;
    }
		if(e == es[i]){
			return true;
		}
	}
	return false;
}

////
inline void strech (std::vector<Entity*>& e, const Matrix& mat)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->strech(mat);
  }
}
inline void select(std::vector<Entity*>& e, bool sel)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->selected(sel);
  }
}
 
inline void color(std::vector<Entity*>& e, int cr)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->color_index(cr);
  }
}
inline void line_style(std::vector<Entity*>& e, LPCTSTR style)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->line_style(style);
  }
}

inline void extend(std::vector<Entity*>& e, const Line& ln)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->extend(ln);
  }
}

inline void trim(std::vector<Entity*>& e, const Line& ln)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->trim(ln);
  }
}

inline void draw(std::vector<Entity*>& e, Draw_Entity& out, bool xor)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    if(xor){
      e[i]->xor_draw(out);
    }
    else{
      e[i]->draw(out);
    }
  }
}

inline void box2d(Rect& rc, const std::vector<Entity*>& es)
{
	if(es.empty())
		return;
	rc.set_reverse_minmax();
	std::vector<Entity*>::const_iterator iter = NULL;
	iter = es.begin();
	for(; iter != es.end(); ++iter){
		Rect temp = (*iter)->box2d();
		rc.xmin(min(rc.xmin(),temp.xmin()));
		rc.ymin(min(rc.ymin(),temp.ymin()));
		rc.xmax(max(rc.xmax(),temp.xmax()));
		rc.ymax(max(rc.ymax(),temp.ymax()));
	}
}

template<class T>
inline void box2d(const std::vector<T*>& es, Rect& rc)
{
	if(es.empty())
		return;
	rc.set_reverse_minmax();
	std::vector<T*>::const_iterator iter = NULL;
	iter = es.begin();
	for(; iter != es.end(); ++iter){
		Rect temp = (*iter)->box2d();
		rc.xmin(min(rc.xmin(),temp.xmin()));
		rc.ymin(min(rc.ymin(),temp.ymin()));
		rc.xmax(max(rc.xmax(),temp.xmax()));
		rc.ymax(max(rc.ymax(),temp.ymax()));
	}
}


inline void destory(Entity*& e)
{
  if(e){
    e->close();
    e=NULL;
  }
}

////
inline void destory(std::vector<Entity*>& e)
{
  for(int i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    destory(e[i]);
    //e[i]->close();
  }
  e.clear();
}

inline void destory(std::vector<Line*>& e)
{
  for(int i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    ((Entity*)(e[i]))->close();
    e[i]=NULL;
  }
  e.clear();
}

inline void destory(std::vector<RArc*>& e)
{
  for(int i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    ((Entity*)(e[i]))->close();
    e[i]=NULL;
  }
  e.clear();
}

inline void destory(std::vector<Circle*>& e)
{
  for(int i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    ((Entity*)(e[i]))->close();
    e[i]=NULL;
  }
  e.clear();
}

inline void erase(std::vector<Entity*>& es, const Entity * e)
{
	std::vector<Entity *>::iterator it = es.begin();
	for( ; it != es.end(); ++it){
		if(*it == const_cast<Entity*>(e)){
			es.erase(it);
			return;
		}
	}
}

////
inline void copy(const std::vector<Entity*>& s,std::vector<Entity*>& d)
{
  Entity* ent = NULL;
  int i=0;
  for(i=0; i<s.size(); i++){
    ent = s[i]->clone();
    d.push_back(ent);
  }
}
inline void copy(const std::vector<Lead_Dimension*>& s, std::vector<Lead_Dimension*>& d)
{
  Lead_Dimension* ent = NULL;
  int i=0;
  for(i=0; i<s.size(); i++){
    ent = static_cast<Lead_Dimension*>(s[i]->clone());
    d.push_back(ent);
  }
}
//template<class T>
//void copy(const std::vector<T*>& s, std::vector<T*>& d)
//{
//  T* ent = NULL;
//  int i=0;
//  for(i=0; i<s.size(); i++){
//    ent = static_cast<T*>(s[i]->clone());
//    d.push_back(ent);
//  }
//}

////
inline void push(const std::vector<Entity*>& s, std::vector<Entity*>& d)
{
  int i=0;
  for(i=0; i<s.size(); i++){
		if(!is_in(s[i], d)){
			d.push_back(s[i]);
		}
  }
}

inline void push(const std::vector<Line*>& s, std::vector<Entity*>& d)
{
  int i=0;
  for(i=0;i<s.size();i++){
    if(s[i]==NULL){
      continue;
    }
    d.push_back((Entity*)(s[i]));
  }
}

inline void push(const std::vector<RArc*>& s, std::vector<Entity*>& d)
{
  int i=0;
  for(i=0;i<s.size();i++){
    if(s[i]==NULL){
      continue;
    }
    d.push_back((Entity*)(s[i]));
  }
}

inline void push(const std::vector<Circle*>& s, std::vector<Entity*>& d)
{
  int i=0;
  for(i=0;i<s.size();i++){
    if(s[i]==NULL){
      continue;
    }
    d.push_back((Entity*)(s[i]));
  }
}

inline void push(const std::vector<Entity*>& s, std::vector<Line*>& d)
{
  int i=0;
  for(i=0;i<s.size();i++){
    if(s[i]==NULL){
      continue;
    }
    if(!s[i]->isa(MY_RUNTIME_CLASS(Line))){
      continue;
    }
    d.push_back((Line*)(s[i]));
  }
}


inline void transformby2d_radian(const Matrix& mat, Float& rad)
{
  Normal nor;
  dlhml::radian_2_normal2d(rad, nor);

  Point  bas;
  Point  way = bas + nor;
  bas.transformby2d(mat);
  way.transformby2d(mat);

  nor.set_data(bas, way);
  dlhml::normal2d_2_radian(nor, rad);
}
inline void transformby2d_distance(const Matrix& mat, Float& dis)
{
  Point bas, way;
  way.x = dis;

  bas.transformby2d(mat);
  way.transformby2d(mat);

  dis = bas.distanceto2d(way);
}


}//namespace
#endif//FILE

