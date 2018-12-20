// Entity.cpp: implementation of the Entity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Entity.h"

#include <TCHAR.H>
#include <cassert>

#include "../include/getrace.h"

#include "File.h"
#include "Layer.h"
#include "Database.h"
#include "Normal.h"
#include "Matrix_d.h"

#include "Line.h"
#include "RArc.h"
#include "Circle.h"

#include "Global.h"
#include "Lua_Tab.h"
#include "encode.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace dlhml{

static int s_count;
static void trace_new()
{
	++s_count;
	//TRACE_OUT("\nnew Entity, count : %d\n", s_count);
}
static void trace_del()
{
	--s_count;
	//TRACE_OUT("\ndel Entity, count : %d\n", s_count);
}

//#define DLHML_ENTITY_CREATE_ME(class_name) static_cast<Entity*>(dlhml::Runtime_Class::load(class_name)->createob())

inline Entity * create_me(LPCTSTR class_name)
{
  assert(class_name);
  dlhml::Runtime_Class * c = dlhml::Runtime_Class::load(class_name);
  //assert(c);
  if(!c){
    return NULL;
  }
  dlhml::Object * o = c->createob();
  assert(o);
  if(!o){
    return NULL;
  }
  Entity * e = static_cast<Entity*>(o);
  assert(e);
  return e;
}


MY_IMPLEMENT_RUNTIME(Entity,Object)
Object* Entity::createob()
{return 0;}

void Entity::init()
{
  box_change(true);
	seled_ = false;

	visibility_ = true;
	linewidth_ = 1;
	linestyle_ = "Continuous";
	layername_ = "Layer0";
	group_ = "";
	color_ = RGB(255,255,255);

  hide_color_ = RGB(150,150,150);
	if_hide_ = false;
	real_color_ = 1;

	is_steel_ = false;

	box_change_ = true;
}
Database* Entity::static_current_db_;
void Entity::set_database(Database* db)
{
	static_current_db_ = db;
}
Entity::Entity()
MCT_INIT1("Entity")
{
  box_change(true);
	init();
}
Entity::Entity(const Entity& rhs)
MCT_INIT1("Entity")
{
  box_change(true);
	init();
	seled_ = rhs.seled_;
	visibility_ = rhs.visibility_;
	linewidth_ = rhs.linewidth_;
	linestyle_ = rhs.linestyle_;
	layername_ = rhs.layername_;
	group_ = rhs.group_;
	color_ = rhs.color_;
	real_color_ = rhs.real_color_;
	id_ = rhs.id_;

	hide_color_ = rhs.hide_color_;
	if_hide_ = rhs.if_hide_;

	is_steel_ = rhs.is_steel_;
}
Entity& Entity::operator=(const Entity& rhs)
{
	if(this == &rhs)
		return *this;
  box_change(true);
	seled_ = rhs.seled_;
	visibility_ = rhs.visibility_;
	linewidth_ = rhs.linewidth_;
	linestyle_ = rhs.linestyle_;
	layername_ = rhs.layername_;
	group_ = rhs.group_;
	color_ = rhs.color_;
	real_color_ = rhs.real_color_;
	id_ = rhs.id_;
	hide_color_ = rhs.hide_color_;
	if_hide_ = rhs.if_hide_;
	is_steel_ = rhs.is_steel_;
  
	return *this;
}
Entity::~Entity()
{
//   dlhml::destory(basic_record_);
}
void Entity::load(File& in)
{
  box_change(true);
	in 
    >> seled_ 
    >> visibility_ 
    >> linewidth_ 
    >> linestyle_ 
    >> layername_ 
    >> group_
		>> real_color_ 
    ;
	seled_ = false;
	color_.load(in);
	id_.load(in);
	loadme(in);
}
void Entity::save(const File& out) const
{
	out << seled_ 
      << visibility_ 
      << linewidth_ 
      << linestyle_ 
      << layername_ 
      << group_
      << real_color_;
	color_.save(out);
	id_.save(out);
	saveme(out);
}

/*
void Entity::lua_save(oLua_File &fout)const
{
	fout.save_value("visibility_", visibility_);
	fout.save_value("linewidth_", linewidth_);
	fout.save_value("linestyle_", linestyle_);
	fout.save_value("layername_", layername_);
	fout.save_value("group_", group_);
	fout.save_value("real_color_", real_color_);
	fout.save_value("color_", &color_);
	fout.save_value("id_", &id_);
}*/



void Entity::edit_property(const Edit_Entity& edit)
{
  box_change(true);
	edit_propertyme(edit);
}
void Entity::draw(Draw_Entity& out) const
{
	if(visibility_)
		drawme(out);
}
void Entity::xor_draw(Draw_Entity& out) const
{
	if(visibility_)
		xor_drawme(out);
}
 void Entity::re_calc_box2d()
 {
  // calc_box2d_record();
 	calc_box2d();
 }
errorinfo Entity::post2db(Database& db,Entity_ID& id)
{
	static_current_db_ = &db;
	errorinfo info = postme2db(db,id);
	return info;
}
void Entity::transformby(const Matrix& mat)
{
  box_change(true);
	//判断图层是否被锁定
//	Layer* layer = NULL;
//	bool if_have = static_current_db_->get_layer(layer,layername_);
//	if(if_have && layer != NULL)
//		if(layer->lock())
//			return;
	transformbyme(mat);
}
void Entity::drag_start(const Matrix& mat)
{
  box_change(true);
	drag_startme(mat);
}
void Entity::drag_end(const Matrix& mat)
{
  box_change(true);
	drag_endme(mat);
}
Entity* Entity::clone() const
{
	return cloneme();
}
bool Entity::close()
{
	closeme();
	return true;
}
void Entity::selected(bool select)
{
  box_change(true);
  seled_=select;
  ////选中点
  if(!seled_){
    std::vector<Point> pts;
    getstrech(pts);
    int i=0;
    for(i=0;i<pts.size();i++){
      pts[i].selected(false);
    }
    setstrech(pts);
  }
}

void Entity::strech(const Matrix& mat)
{ 
  box_change(true);
  ////选中点
  std::vector<Point> pts;
  getctrl(pts);
  int i=0;
  for(i=0;i<pts.size();i++){
    if(pts[i].selected()){
      pts[i].transformby(mat);
    }
  }
  setctrl(pts);
}

//void Entity::intersect(const Cloud_Line& cl, std::vector<Point>& pts)const
//{
//  cl.intersect(*this, pts);
//}

void Entity::intersectme(const Entity& e , std::vector<Point>& pts)const
{
}
void Entity::intersectme(const Line  & ln, std::vector<Point>& pts)const
{
//  ln.intersect(*this,pts);
}
void Entity::intersectme(const RArc  & ac, std::vector<Point>& pts)const
{
//  ac.intersect(*this,pts);
}
void Entity::intersectme(const Circle& cr, std::vector<Point>& pts)const
{
//  cr.intersect(*this,pts);
}


bool Entity::intersect_box2d(const Rect& rect) const
{
	return box2d().intersect(rect);
}
bool Entity::intersect(const Rect& rect) const
{
	return intersectme(rect);
}
bool Entity::envelop(const Rect& rect) const
{
	return envelopme(rect);
}
bool Entity::snap_endpoint(Point& pt,const Rect& rect) const
{
	return snap_endpointme(pt,rect);
}
bool Entity::snap_endpointme(Point& pt,const Rect& rect) const
{
	return false;
}
bool Entity::snap_center_point(Point& pt,const Rect& rect) const
{
	return snap_center_pointme(pt,rect);
}
bool Entity::snap_center_pointme(Point& pt,const Rect& rect) const
{
	return false;
}
bool Entity::snap_middle_point(Point& pt,const Rect& rect) const
{
	return snap_middle_pointme(pt,rect);
}
bool Entity::snap_middle_pointme(Point& pt,const Rect& rect) const
{
	return false;
}
bool Entity::snap_nearest_point(Point& pt,const Rect& rect) const
{
	return snap_nearest_pointme(pt,rect);
}
bool Entity::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
	return false;
}
bool Entity::snap_perpendicular_point(Point& pt,const Rect& rect,const Point& o) const
{
	return snap_perpendicular_pointme(pt,rect,o);
}
bool Entity::snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const
{
	return false;
}
bool Entity::snap_intersect_point(Point& pt,const Entity& ent,const Rect& rect) const
{
	return snap_intersect_pointme(pt,ent,rect);
}

////lINE/ARC/CIRCLE不再单独实现
////DIMESION及其子类在Dimesion类实现,其子类不再单独实现
bool Entity::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
  //SNAP 2009.07.02
  if(&ent == this){
    return false;
  }
  std::vector<Point> pts;
  intersect(ent,pts);
  int i=0;
  for(i=0;i<pts.size();i++){
    if(pts[i].envelop(rect)){
      pt = pts[i];
      return true;
    }
  }
  return false;
}

bool Entity::snap_intersect_point_imp(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap_intersect_pointme(pt,snap,rect);
}


Float Entity::length(const Normal& nor)const
{
  if(EquFloat(nor.z(),0)){
    return length();
  }
  Point ed2d;
  ed2d.setdata(nor);
  if(EquFloat(ed2d.distanceto2d(Point()),0)){
    return 0;
  }
  return length_p(nor);
}
Float Entity::area_min_rect(const Normal& nor)const
{
  if(EquFloat(nor.z(),0)){
    return area_min_rect();
  }
  Point ed2d;
  ed2d.setdata(nor);
  if(EquFloat(ed2d.distanceto2d(Point()),0)){
    return 0;
  }
  return area_min_rect_p(nor);
}


void Entity::moveto(const Point& pt)
{
  box_change(true);
  Matrix mat;
  mat.set_move(focus(), pt);
  transformby(mat);
}



//vector///////

//void line_style(std::vector<Entity*>& e, const std::string& ln_style)
//{
//  int i=0;
//  for(i=0; i<e.size(); i++){
//    e[i]->line_style(ln_style.c_str());
//  }
//}

//bool intersect(const std::vector<Entity*>& e, const Rect& rc)
//{
//  int i=0;
//  for(i=0;i<e.size();i++){
//    if(e[i]==NULL){
//      continue;
//    }
//    if(e[i]->intersect(rc)){
//      return true;
//    }
//  }
//  return false;
//}

void Entity::get_show(std::vector<Entity*>& lns)const
{
  short aaa = this->color_index();
	Entity * e = (this->clone());
  short bbb = e->color_index();
	lns.push_back(e);
}


//RECORD
void Entity::box_change(bool b)
{
  Entity * the = const_cast<Entity*>(this);
  the->box_change_=b;
}

//BOX RECORD
Rect Entity::box2d() const							
{	
  if(box_change_){
    Entity * the = const_cast<Entity*>(this);
    assert(the && "");
    the->box2d_record_ = calc_box2d();
    the->box_change(false);
  }
  return box2d_record_;
}

// void Entity::calc_box2d_record()
// {
//   box2d_record_ = calc_box2d();
// }


//BASIC RECORD
// const std::vector<Entity*>& Entity::get_basic()const
// {
//   if(box_change_){
//     Entity * the = const_cast<Entity*>(this);
//     assert(the && "The ptr is myself.");
//     the->calc_basic_record();
//     the->box_change(false);
//   }
//   return basic_record_;
// }
// 
// void Entity::calc_basic_record()
// {
//   dlhml::destory(basic_record_);
//   Entity * e = (this->clone());
//   basic_record_.push_back(e);
// }
void Entity::save_lua(std::ofstream &out,char *name,int tab_num)
{
	lua::begin_table(out,name,tab_num);
	int pos = tab_num+1;

	lua::string_save(out,"kind",my_class_name(),pos);

	lua::bool_save(out,"seled_",seled_,pos);
	lua::bool_save(out,"visibility_",visibility_,pos);
	lua::int_save(out,"linewidth_",linewidth_,pos);
	lua::string_save(out,"linestyle_",linestyle_,pos);
	lua::string_save(out,"layername_",layername_,pos);
	lua::string_save(out,"group_",group_,pos);
	lua::int_save(out,"real_color_",real_color_,pos);
	color_.save_lua(out,"color_",pos);

	save_luame(out,pos);
	lua::end_table(out,tab_num);
}
void Entity::open_lua(lua_State *l,char *name)  
{
  box_change(true);

	Lua_Tab t(l,name);
	std::string temp;
  get_value(number,l,seled_,"seled_");
	get_value(number,l,visibility_,"visibility_");
	get_value(number,l,linewidth_,"linewidth_");
	get_value(string,l,temp,"linestyle_");
	linestyle_ =  temp;
	get_value(string,l,temp,"layername_");
	layername_ =  temp;
	get_value(string,l,temp,"group_");
	group_ =  temp;
	get_value(number,l,real_color_,"real_color_");

	color_.open_lua(l,"color_");
	open_luame(l);
}
int Entity::get_str(char *out)
{
	get_strme(out);
	return 1;
}
int Entity::set_from_str(char *in)
{
	set_from_strme(in);
	return 1;
}
void Entity::get_str_ent()
{
	rei_add_int(NULL,"seled_",seled_);
	rei_add_int(NULL,"visibility_",visibility_);
	rei_add_int(NULL,"linewidth_",linewidth_);
	rei_add_int(NULL,"real_color_",real_color_);
	

	long red = GetRValue(color_.rgb());
	long green = GetGValue(color_.rgb());
	long blue=GetBValue(color_.rgb());
	rei_add_float(NULL,"red",red);
	rei_add_float(NULL,"green",green);
	rei_add_float(NULL,"blue",blue);

	rei_add_str(NULL,"linestyle_",linestyle_.c_str());
	rei_add_str(NULL,"layername_",layername_.c_str());
	rei_add_str(NULL,"group_",group_.c_str());

}
void Entity::set_from_str_ent()
{
	seled_ = atoi(rei_get("seled_"));
	visibility_ = atoi(rei_get("visibility_"));
	linewidth_ = atoi(rei_get("linewidth_"));
	real_color_ = atoi(rei_get("real_color_"));

	long red = atof(rei_get("red"));
	long green = atof(rei_get("green"));
	long blue = atof(rei_get("blue"));
	color_ = RGB(red,green,blue);
	

	linestyle_ = rei_get("linestyle_");
	layername_ = rei_get("layername_");
	group_ = rei_get("group_");

}
void Entity::get_str_ent_sub(char *name)
{
	char s[MAX_REDIS_STR];
	sprintf(s,"%s.seled_",name);
	rei_add_int(NULL,"seled_",seled_);
	sprintf(s,"%s.visibility_",name);
	rei_add_int(NULL,"visibility_",visibility_);
	sprintf(s,"%s.linewidth_",name);
	rei_add_int(NULL,"linewidth_",linewidth_);
	sprintf(s,"%s.real_color_",name);
	rei_add_int(NULL,"real_color_",real_color_);
	

	long red = GetRValue(color_.rgb());
	long green = GetGValue(color_.rgb());
	long blue=GetBValue(color_.rgb());
	sprintf(s,"%s.red",red);
	rei_add_float(NULL,s,red);
	sprintf(s,"%s.green",red);
	rei_add_float(NULL,s,green);
	sprintf(s,"%s.blue",red);
	rei_add_float(NULL,s,blue);

	sprintf(s,"%s.linestyle_",name);
	rei_add_str(NULL,s,linestyle_.c_str());
	sprintf(s,"%s.layername_",name);
	rei_add_str(NULL,s,layername_.c_str());
	sprintf(s,"%s.group_",name);
	rei_add_str(NULL,s,group_.c_str());

}
void Entity::set_from_str_ent_sub(char *name)
{
	char s[MAX_REDIS_STR];
	sprintf(s,"%s.seled_",name);
	seled_ = atoi(rei_get(s));
	sprintf(s,"%s.visibility_",name);
	visibility_ = atoi(rei_get(s));
	sprintf(s,"%s.linewidth_",name);
	linewidth_ = atoi(rei_get(s));
	sprintf(s,"%s.real_color_",name);
	real_color_ = atoi(rei_get(s));
	
	sprintf(s,"%s.red",name);
	long red = atof(rei_get(s));

	sprintf(s,"%s.green",name);
	long green = atof(rei_get(s));
	sprintf(s,"%s.blue",name);
	long blue = atof(rei_get(s));
	color_ = RGB(red,green,blue);



	sprintf(s,"%s.linestyle_",name);
	linestyle_ = rei_get(s);
	sprintf(s,"%s.layername_",name);
	layername_ = rei_get(s);
	sprintf(s,"%s.group_",name);
	group_ = rei_get(s);

}
void Entity::get_strme(char *out)
{
}
void Entity::set_from_strme(char *in)
{
}


void Entity::save_luame(std::ofstream &out,int tab_num)
{
}
void Entity::open_luame(lua_State *l) 
{
}


//vector///////
////////////
}//namespace
