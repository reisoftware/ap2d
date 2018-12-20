// Block.cpp: implementation of the Block class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Block.h"
#include "File.h"
#include "Database.h"
#include "Edit_Entity.h"
#include <algorithm>
#include <functional>
#include "Entity_Snap_Implement.h"
#include "Point.h"
#include <cassert>
#include "Visitor.h"
#include "Normal.h"
#include "Matrix_d.h"

#include "Global.h"
#include "Lua_Tab.h"
#include "getrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Block,Entity)
Block::Block()
MCT_INIT1("Block")
{
//	myclass_ = "Block";
	private_db_ = 0;
	//selected_ = 0;
}

Block::~Block()
{
	std::for_each(list_.begin(),list_.end(),
		std::mem_fun<bool,Entity>(&Entity::close));
	list_.clear();
}
Block::Block(const Block& rhs)
:Entity(rhs)
MCT_INIT2("Block")
{

	private_db_ = rhs.private_db_;
	//selected_ = rhs.selected_;
  focus_ = rhs.focus_;
//	myclass_ = rhs.myclass_;
	std::vector<Entity*>::const_iterator iter;
	for(iter=rhs.list_.begin();iter!=rhs.list_.end();++iter)
		list_.push_back((*iter)->clone());
}
Block& Block::operator=(const Block& rhs)
{
	Entity::operator =(rhs);
	if(this == &rhs)
		return *this;
	private_db_ = rhs.private_db_;
//	selected_ = rhs.selected_;
  focus_ = rhs.focus_;
//	myclass_ = rhs.myclass_;
	dlhml::destory(list_);
	std::vector<Entity*>::const_iterator iter;
	for(iter=rhs.list_.begin();iter!=rhs.list_.end();++iter)
		list_.push_back((*iter)->clone());
	return *this;
}
bool Block::visit(Visitor& v)
{
	return v.visit_block(*this);
}
void Block::loadme(File& in)
{
	int num = 0;
	in >> num;
	for(int i=0; i<num; ++i){
		char* classname = NULL;
		in >> classname;
		Runtime_Class* pR = NULL;
		pR = Runtime_Class::load(classname);
		delete [] classname;
		Object* pO = NULL;
		pO = pR->createob();
		Entity* pEnt = static_cast<Entity*>(pO);
		pEnt->load(in);
		list_.push_back(pEnt);
	}
  in >> focus_.x;
  in >> focus_.y;
  in >> focus_.z;
}
void Block::saveme(const File& out) const
{
	out << list_.size();
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Runtime_Class* pR = (*iter)->GetRuntimeClass();
		out << pR->classname;
		(*iter)->save(out);
	}
  out << focus_.x;
  out << focus_.y;
  out << focus_.z;
}
void Block::save_luame(std::ofstream &out,int tab_num)
{
	focus_.save_lua(out,"focus_",tab_num);
	lua::begin_table(out,"list_",tab_num);
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->save_lua(out,NULL,tab_num);
	lua::val_save(out,"}",tab_num);

}

static dlhml::Entity * deal_entlists(lua_State *l,std::string kind)
{
	dlhml::Entity *ent = dlhml::create_me(kind.c_str());
	if(!ent){
		TRACE_OUT("class kind = %s invaild.\n",kind.c_str());
		return NULL;
	}
	ent->open_lua(l,NULL);
	return ent;
}

void Block::open_luame(lua_State *l) 
{
	TRACE_OUT("Block::open_luame()\n");
	focus_.open_lua(l,"focus_");
	Lua_Tab luatab(l,"list_");
	int index = lua_gettop(l);
	lua_pushnil(l);
	std::string kind;
	while(lua_next(l,index) != 0){
		get_value(string,l,kind,"kind");
		Entity *e = deal_entlists(l,kind);
		if(e)
			list_.push_back(e);
		lua_pop(l,1);
	}
  
}
void Block::edit_propertyme(const Edit_Entity& edit)
{
	if(seled_ && list_.empty()){
		list_.front()->edit_property(edit);
	}
//	if(!selected_)
//		return ;
//	selected_->edit_property(edit);
}
void Block::drawme(Draw_Entity& out) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->draw(out);
}
void Block::xor_drawme(Draw_Entity& out) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->xor_draw(out);
}
errorinfo Block::postme2db(Database& db,Entity_ID& id)
{
	private_db_ = &db;
	return db.entity_push_back(this,id);
}
void Block::transformbyme(const Matrix& mat)
{
  focus_.transformby(mat);
	std::vector<Entity*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->transformby(mat);
}
void Block::drag_startme(const Matrix& mat)
{
}
void Block::drag_endme(const Matrix& mat)
{
}
Entity* Block::cloneme() const
{
	return new Block(*this);
}
void Block::closeme()
{
	int i=0;
	for(; i<list_.size(); i++){
		list_[i]->close();
	}
	list_.clear();
	delete this;
}
bool Block::intersectme(const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->intersect(rect)){
//			selected_ = (*iter);
			return true;
		}
	}
	return false;
}
bool Block::envelopme(const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(!(*iter)->envelop(rect))
			return false;
	}
	return true;
}
Rect Block::calc_box2d() const
{
	Rect box2d_;
	box2d_.set_reverse_minmax();
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp = (*iter)->box2d();
		box2d_.xmin(min(box2d_.xmin(),temp.xmin()));
		box2d_.ymin(min(box2d_.ymin(),temp.ymin()));
		box2d_.xmax(max(box2d_.xmax(),temp.xmax()));
		box2d_.ymax(max(box2d_.ymax(),temp.ymax()));
	}
	return box2d_;
}
bool Block::snap_endpointme(Point& pt,const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->snap_endpoint(pt,rect))
			return true;
	}
	return false;
}
bool Block::snap_center_pointme(Point& pt,const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->snap_center_point(pt,rect))
			return true;
	}
	return false;
}
bool Block::snap_middle_pointme(Point& pt,const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->snap_middle_point(pt,rect))
			return true;
	}
	return false;
}
bool Block::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->snap_nearest_point(pt,rect))
			return true;
	}
	return false;
}
bool Block::snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->snap_perpendicular_point(pt,rect,o))
			return true;
	}
	return false;
}
bool Block::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->snap_intersect_point(pt,ent,rect))
			return true;
	}
	return false;
}
bool Block::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->snap_intersect_point_imp(pt,snap,rect))
			return true;
	}
	return false;
}
void Block::push_back(Entity* ent)
{
	list_.push_back(ent);
}
void Block::push_back_id(const Entity_ID& id)
{
	assert(	private_db_ );
	Entity* ent=0;
	if(private_db_->entity_from_id(ent,id)!=Error::OK)
		return ;
	Entity* pnew = ent->clone();
	private_db_->erase_entity(id);
	list_.push_back(pnew);
}
Entity* Block::front()
{
	return list_.front();
}
Entity* Block::back()
{
	return list_.back();
}
Entity* Block::next(const Entity* pos)
{
  std::vector<Entity*>::iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter){
    if(*iter == pos){
      if(iter+1==list_.end())
        return 0;
      return *(iter+1);
    }
  }
  return 0;
}
int Block::size() const
{
	return list_.size();
}
bool Block::erase(Entity* ent)
{
  std::vector<Entity*>::iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter){
    if(ent == (*iter)){
      (*iter)->close();
      list_.erase(iter);
      return true;
    }
  }
  return false;
}
bool Block::remove(Entity* ent)
{
  std::vector<Entity*>::iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter){
    if(ent == (*iter)){
      list_.erase(iter);
      return true;
    }
  }
  return false;
}
bool Block::pt_in(const Point& pt) const
{
	return pt.envelop(box2d());
}

void Block::selected(bool select)
{ 
  seled_ = select;
  int i=0;
  for(i=0; i<list_.size(); i++){
    list_[i]->selected(select);
  }
}
bool Block::selected()const
{          
  //selected(selected_);
  return seled_;
}

Float Block::length()const
{
	Float len=0;
	int i=0;
	for(; i<list_.size(); i++){
		len += list_[i]->length();
	}
	return len;
}

//void Block::moveto_p(const Point& pt)
//{
//  Normal nor;
//  nor.set_data(focus_, pt);
//  Matrix mat;
//  mat.set_move(nor.x(), nor.y(), 0);
//  transformby(mat);
//}

void Block::get_ptr_p(std::vector<Entity*>& ptrs)
{
  int i=0;
  for(; i<list_.size(); i++){
    list_[i]->get_ptr(ptrs);
  }
}

void Block::color_index(int index)
{
  Entity::color_index(index);
  int i=0;
  for(; i<list_.size(); i++){
    list_[i]->color_index(index);
  }
}

void Block::setctrl(const std::vector<Point>& pts)
{
  if(pts.empty()){
    return;
  }
  Matrix mat;
  mat.set_move(focus_, pts[0]);
  transformby(mat);
}
void Block::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(focus_);
}
int Block::pt_count()const
{
  return 1;
}
void Block::get_show(std::vector<Entity*>& lns)const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->get_show(lns);
}



}//namespace
