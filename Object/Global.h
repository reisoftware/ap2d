
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


OBJECT_API std::vector<Entity*>::iterator find(const Entity * const e,std::vector<Entity*>& es);
OBJECT_API int  find (const Entity * const e, const std::vector<Entity*>& es);
OBJECT_API bool is_in(const Entity * const e, const std::vector<Entity*>& es);

OBJECT_API void color  (std::vector<Entity*>& e, int cr);
OBJECT_API void line_style(std::vector<Entity*>& e, LPCTSTR style);
OBJECT_API void strech (std::vector<Entity*>& e, const Matrix& mat);
OBJECT_API void select (std::vector<Entity*>& e, bool sel);
OBJECT_API void extend (std::vector<Entity*>& e, const Line& ln);
OBJECT_API void trim   (std::vector<Entity*>& e, const Line& ln);
OBJECT_API void draw   (std::vector<Entity*>& e, Draw_Entity& out, bool xor=true);
// OBJECT_API void post2db(std::vector<Entity*>& e, dlhml::Database& db);

OBJECT_API void box2d(Rect& rc, const std::vector<Entity*>& es);

OBJECT_API void destory(std::vector<Entity*>& e);

OBJECT_API void destory(Entity*& e);
OBJECT_API void destory(std::vector<Entity*>& e);
OBJECT_API void destory(std::vector<Line  *>& e);
OBJECT_API void destory(std::vector<RArc  *>& e);
OBJECT_API void destory(std::vector<Circle*>& e);

OBJECT_API void erase(std::vector<Entity*>& es, const Entity * e);

////克隆后加入
OBJECT_API void copy(const std::vector<Entity*>& s, 
										 std::vector<Entity*>& d);
OBJECT_API void copy(const std::vector<Lead_Dimension*>& s, 
										 std::vector<Lead_Dimension*>& d);

OBJECT_API void copy(const std::vector<Entity*>& s, 
										 std::vector<Entity*>& d, 
										 const Matrix& mat);

//template<class T>
//void copy(const std::vector<T*>& s, std::vector<T*>& d);

////直接把加入指针，不克隆
//inline void push(const std::vector<Entity*>& s, std::vector<Entity*>& d);
//inline void push(const std::vector<Line  *>& s, std::vector<Entity*>& d);
//inline void push(const std::vector<RArc  *>& s, std::vector<Entity*>& d);
//inline void push(const std::vector<Circle*>& s, std::vector<Entity*>& d);
//
OBJECT_API void push(const std::vector<Entity*>& s, std::vector<Line  *>& d);

////直接把加入指针，不克隆
// template<class T>
// void push_back(const T * s, std::vector<T*>& d);
template<class T>
void push_back(const T * s, std::vector<Entity*>& d);
template<class T>
void push_back(const std::vector<T*>& s, std::vector<Entity*>& d);

template<class T>
void push_back(std::vector<Entity*>::iterator sb,
											std::vector<Entity*>::iterator se,
											std::vector<T*>& d);

template<class T>
bool swap_entity(Entity *ent1, Entity *ent2,T* sign);

OBJECT_API bool swap(Entity *ent1,Entity *ent2);


////矩阵运算角度
OBJECT_API void transformby2d_radian  (const Matrix& mat, Float& rad);
OBJECT_API void transformby2d_distance(const Matrix& mat, Float& dis);

//inline void line_style(std::vector<Entity*>& e, const std::string& ln_style);
//bool intersect(const std::vector<Entity*>& e, const Rect& rc);

//template<class T>

OBJECT_API bool get(const Entity * ent, Point& st, Point& ed);
OBJECT_API double radian(const Entity * ent);

OBJECT_API void parse(std::vector<std::string>& d, const std::string& s, const std::string& sp); 
OBJECT_API std::string std_str(const std::string& s, const std::string& sp); 


template<class Entity>
void post2db(std::vector<Entity*>& es, Database * db);



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

//*********************************************************************
//inline void push(const std::vector<Entity*>& s, std::vector<Entity*>& d)
//{
//  int i=0;
//  for(i=0; i<s.size(); i++){
//		if(!is_in(s[i], d)){
//			d.push_back(s[i]);
//		}
//  }
//}
//
//inline void push(const std::vector<Line*>& s, std::vector<Entity*>& d)
//{
//  int i=0;
//  for(i=0;i<s.size();i++){
//    if(s[i]==NULL){
//      continue;
//    }
//    d.push_back((Entity*)(s[i]));
//  }
//}
//
//inline void push(const std::vector<RArc*>& s, std::vector<Entity*>& d)
//{
//  int i=0;
//  for(i=0;i<s.size();i++){
//    if(s[i]==NULL){
//      continue;
//    }
//    d.push_back((Entity*)(s[i]));
//  }
//}
//
//inline void push(const std::vector<Circle*>& s, std::vector<Entity*>& d)
//{
//  int i=0;
//  for(i=0;i<s.size();i++){
//    if(s[i]==NULL){
//      continue;
//    }
//    d.push_back((Entity*)(s[i]));
//  }
//}

// template<class T>
// void push_back(const T * s, std::vector<T*>& d)
// {
// 	if(!s){
// 		return;
// 	}
// 	std::vector<Entity*>::iterator it=NULL;
// 	it = find(s, d);
// 	if(it){
// 		return;
// 	}
// 	d.push_back(const_cast<T*>(s));
// }

template<class T>
void push_back(const T * s, std::vector<Entity*>& d)
{
	if(!s){
		return;
	}
	std::vector<Entity*>::iterator it=NULL;
	it = find(s, d);
	if(it){
		return;
	}
	d.push_back(static_cast<Entity*>(const_cast<T*>(s)));
}

template<class T>
void push_back(const std::vector<T*>& s, std::vector<Entity*>& d)
{
  int i=0;
  for(i=0;i<s.size();i++){
    if(s[i]==NULL){
      continue;
    }
    //d.push_back((Entity*)(s[i]));
		dlhml::push_back<T>(s[i], d);
  }
}

template<class T>
void push_back(std::vector<Entity*>::iterator sb,
											std::vector<Entity*>::iterator se,
											std::vector<T*>& d)
{
	vector<Entity*>::iterator it = sb;
	for(; it != se; ++it){
		T * the = static_cast<T*>(*it);
		d.push_back(the);
	}
}


template<class T>
void box2d(const std::vector<T*>& es, Rect& rc)
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



template<class T>
bool swap_entity(Entity *ent1, Entity *ent2,T* sign)
{
	T* entemp1 = dynamic_cast<T*>(ent1);
	if(!entemp1)
		return false;
	T* entemp2 = dynamic_cast<T*>(ent2);
	if(!entemp2)
		return false;
	T *temp = static_cast<T*>(entemp1->clone());
	*entemp1 = *entemp2;
	*entemp2 = *temp;
	delete temp;
	return true;
}

template<class Entity>
void post2db(std::vector<Entity*>& es, Database&  db)
{
  Entity_ID id;
  int i=0;
  for(i=0; i<es.size(); i++){
    if(es[i]==NULL){
      continue;
    }
    es[i]->post2db(db, id);
  }
}



}//namespace
#endif//FILE

