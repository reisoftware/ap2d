#include "StdAfx.h"
#include "Global.h"
#include "Circle.h"
#include "Line.h"
#include "RArc.h"
#include "Block.h"
#include "Cloud_Line.h"
#include "Cut_Section.h"
#include "Group.h"
#include "Group_Ents.h"
#include "Ln_Dim_Block.h"
#include "Rectentity.h"
#include "Text.h"
#include "Three_Pt_Dimension_Block.h"
#include "Angle_Dimension.h"
#include "Arc_Arrow.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Lead_Dimension_Info.h"
#include "Line_Arrow.h"
#include "Lead_Dimension_Block.h"
#include "Ln_Dim.h"
#include "Radius_Dimension.h"
#include "Text_Dimension.h"
#include "Text_Dimension_Info.h"
#include "Three_Pt_Dimension.h"

namespace dlhml
{
////在集合中查找某个实体，不在返回NULL
std::vector<Entity*>::iterator find(const Entity * const e,std::vector<Entity*>& es)
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
int find(const Entity * const e,const std::vector<Entity*>& es)
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
bool is_in(const Entity * const e,const std::vector<Entity*>& es)
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
void strech (std::vector<Entity*>& e, const Matrix& mat)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->strech(mat);
  }
}
void select(std::vector<Entity*>& e, bool sel)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->selected(sel);
  }
}
 
void color(std::vector<Entity*>& e, int cr)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->color_index(cr);
  }
}
void line_style(std::vector<Entity*>& e, LPCTSTR style)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->line_style(style);
  }
}

void extend(std::vector<Entity*>& e, const Line& ln)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->extend(ln);
  }
}

void trim(std::vector<Entity*>& e, const Line& ln)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(!e[i]){
      continue;
    }
    e[i]->trim(ln);
  }
}

void draw(std::vector<Entity*>& e, Draw_Entity& out, bool xor)
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

// void post2db(std::vector<Entity*>& e, dlhml::Database& db)
// {
//   dlhml::Entity_ID id;
// 	int n=e.size();
// 	int i=0;
// 	for(; i<n; ++i){
// 		if(e[i]){
// 			e[i]->post2db(db,id);	
// 		}
// 	}
// }


void box2d(Rect& rc, const std::vector<Entity*>& es)
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
void destory(Entity*& e)
{
  if(e){
    e->close();
    e=NULL;
  }
}

void destory(std::vector<Entity*>& e)
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

void destory(std::vector<Line*>& e)
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

void destory(std::vector<RArc*>& e)
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

void destory(std::vector<Circle*>& e)
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

void erase(std::vector<Entity*>& es, const Entity * e)
{
	std::vector<Entity *>::iterator it = es.begin();
	for( ; it != es.end(); ++it){
		if(*it == const_cast<Entity*>(e)){
			es.erase(it);
			return;
		}
	}
}

void copy(const std::vector<Entity*>& s,std::vector<Entity*>& d)
{
  Entity* ent = NULL;
  int i=0;
  for(i=0; i<s.size(); i++){
    ent = s[i]->clone();
    d.push_back(ent);
  }
}

void copy(const std::vector<Entity*>& s,std::vector<Entity*>& d, const Matrix& mat)
{
  Entity* ent = NULL;
  int i=0;
  for(i=0; i<s.size(); i++){
    ent = s[i]->clone();
		ent->transformby(mat);
    d.push_back(ent);
  }
}

void copy(const std::vector<Lead_Dimension*>& s, std::vector<Lead_Dimension*>& d)
{
  Lead_Dimension* ent = NULL;
  int i=0;
  for(i=0; i<s.size(); i++){
    ent = static_cast<Lead_Dimension*>(s[i]->clone());
    d.push_back(ent);
  }
}
void copy(const std::vector<Lead_Dimension_MT*>& s, std::vector<Lead_Dimension_MT*>& d)
{
  Lead_Dimension_MT* ent = NULL;
  int i=0;
  for(i=0; i<s.size(); i++){
    ent = static_cast<Lead_Dimension_MT*>(s[i]->clone());
    d.push_back(ent);
  }
}
void copy(const std::vector<Lead_Dimension_Info*>& s, std::vector<Lead_Dimension_Info*>& d)
{
  Lead_Dimension_Info* ent = NULL;
  int i=0;
  for(i=0; i<s.size(); i++){
    ent = static_cast<Lead_Dimension_Info*>(s[i]->clone());
    d.push_back(ent);
  }
}
void copy(const std::vector<Text_Dimension_Info*>& s, std::vector<Text_Dimension_Info*>& d)
{
  Text_Dimension_Info* ent = NULL;
  int i=0;
  for(i=0; i<s.size(); i++){
    ent = static_cast<Text_Dimension_Info*>(s[i]->clone());
    d.push_back(ent);
  }
}
void push(const std::vector<Entity*>& s, std::vector<Line*>& d)
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
void transformby2d_radian(const Matrix& mat, Float& rad)
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
void transformby2d_distance(const Matrix& mat, Float& dis)
{
  Point bas, way;
  way.x = dis;

  bas.transformby2d(mat);
  way.transformby2d(mat);

  dis = bas.distanceto2d(way);
}

bool get(const Entity * ent, Point& st, Point& ed)
{
	if(!ent){
		return false;
	}
	if(ent->isa(MY_RUNTIME_CLASS(Line))){
		const Line * e = static_cast<const Line*>(ent);
		st = e->start();
		ed = e->end();
		return true;
	}
	if(ent->isa(MY_RUNTIME_CLASS(RArc))){
		const RArc * e = static_cast<const RArc*>(ent);
		st = e->start();
		ed = e->end();
		return true;
	}
	return false;
}

double radian(const Entity * ent)
{
	double rad = 0;
	Point st, ed;
	dlhml::get(ent, st, ed);
	dlhml::normal2d_2_radian(Normal(st,ed), rad);
	return rad;
}
bool swap(Entity *ent1,Entity *ent2)
{
	if(swap_entity(ent1,ent2,(Line*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Circle*)(0)))
		return true;
	/*
	if(swap_entity(ent1,ent2,(Dimension*)(0)))
		return true;*/
	if(swap_entity(ent1,ent2,(Block*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Cloud_Line*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Cut_Section*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Group*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(RArc*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Group_Ents*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Ln_Dim_Block*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Text*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Rectentity*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Three_Pt_Dimension_Block*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Angle_Dimension*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Arc_Arrow*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Lead_Dimension*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Lead_Dimension_MT*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Lead_Dimension_Info*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Line_Arrow*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Lead_Dimension_Block*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Ln_Dim*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Radius_Dimension*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Text_Dimension*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Text_Dimension_Info*)(0)))
		return true;
	if(swap_entity(ent1,ent2,(Three_Pt_Dimension*)(0)))
		return true;
	return false;
}

void parse(std::vector<std::string>& d, const std::string& s, const std::string& sp) 
{
  std::string item;
  int source_length = s.length();
  for (int i=0; i<source_length; i++) {
		//if (source[i] != separator) {
    if(sp.find(s[i]) == std::string::npos) {
      item += s[i];
    }else{
      if (!item.empty()) {
        d.push_back(item);
        item = "";
      }
    }
  }
  if (!item.empty()) {
    d.push_back(item);
    item = "";
  }
}

std::string std_str(const std::string& s, const std::string& sp)
{
	std::string d = s;
	while(!d.empty()&&  !sp.empty() && sp.find(d[0])!=std::string::npos){
		d.erase(d.begin());
	}
	while(!d.empty() && !sp.empty() && sp.find(d[s.size()-1])!=std::string::npos){
		d.erase(d.end()-1);
	}
	return d;
}



}//namespace


