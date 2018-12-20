// Group.cpp: implementation of the Group class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Group.h"

#include "File.h"
#include "Database.h"
#include "Edit_Entity.h"
#include <algorithm>
#include <functional>
#include "Entity_Snap_Implement.h"
#include "Point.h"
#include <cassert>
#include "Visitor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Group,Entity)

Group::Group()
MCT_INIT1("Group")
{

}

Group::~Group()
{

}
Group::Group(const Group& rhs)
:Entity(rhs)
MCT_INIT2("Group")
{
	private_db_ = rhs.private_db_;
	EntityIDArray::const_iterator iter;
	for(iter=rhs.ids_.begin();iter!=rhs.ids_.end();++iter){
		ids_.push_back(*iter);
	}
}
Group& Group::operator=(const Group& rhs)
{
	Entity::operator=(rhs);
	if(this == &rhs)
		return *this;
	private_db_ = rhs.private_db_;
	EntityIDArray::const_iterator iter;
	for(iter=rhs.ids_.begin();iter!=rhs.ids_.end();++iter){
		ids_.push_back(*iter);
	}
	return *this;
}
bool Group::visit(Visitor& v)
{
	return v.Visit_Group(*this);
}
void Group::loadme(File& in)
{
/*
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
*/
}
void Group::saveme(const File& out) const
{
/*
	out << list_.size();
	std::vector<Entity*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Runtime_Class* pR = (*iter)->GetRuntimeClass();
		out << pR->classname;
		(*iter)->save(out);
	}
*/
}
void Group::transformby_ent_selected()
{
	
}
void Group::edit_propertyme(const Edit_Entity& edit)
{
	if(!selected_)
		return ;
	selected_->edit_property(edit);
}
void Group::drawme(Draw_Entity& out) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		e->draw(out);
	}
}
void Group::xor_drawme(Draw_Entity& out) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		 e->xor_draw(out);
	}
}
errorinfo Group::postme2db(Database& db,Entity_ID& id)
{
	private_db_ = &db;
	return db.entity_push_back(this,id);
}
void Group::transformbyme(const Matrix& mat)
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		e->transformby(mat);
	}
}
void Group::drag_startme(const Matrix& mat)
{
}
void Group::drag_endme(const Matrix& mat)
{
}
Entity* Group::cloneme() const
{
	return new Group(*this);
}
void Group::closeme()
{
	delete this;
}
bool Group::intersectme(const Rect& rect) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp1 = e->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if(e->intersect(rect)){
			selected_ = e;
			return true;
		}
	}
	return false;
}
bool Group::envelopme(const Rect& rect) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		if(!e->envelop(rect))
			return false;
	}
	return true;
}
Rect Group::calc_box2d() const
{
	Rect box2d_;
	box2d_.set_reverse_minmax();
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp = e->box2d();
		box2d_.xmin(min(box2d_.xmin(),temp.xmin()));
		box2d_.ymin(min(box2d_.ymin(),temp.ymin()));
		box2d_.xmax(max(box2d_.xmax(),temp.xmax()));
		box2d_.ymax(max(box2d_.ymax(),temp.ymax()));
	}
	return box2d_;
}
bool Group::snap_endpointme(Point& pt,const Rect& rect) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp1 = e->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if(e->snap_endpoint(pt,rect))
			return true;
	}
	return false;
}
bool Group::snap_center_pointme(Point& pt,const Rect& rect) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp1 = e->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if(e->snap_center_point(pt,rect))
			return true;
	}
	return false;
}
bool Group::snap_middle_pointme(Point& pt,const Rect& rect) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp1 = e->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if(e->snap_middle_point(pt,rect))
			return true;
	}
	return false;
}
bool Group::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp1 = e->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if(e->snap_nearest_point(pt,rect))
			return true;
	}
	return false;
}
bool Group::snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp1 = e->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if(e->snap_perpendicular_point(pt,rect,o))
			return true;
	}
	return false;
}
bool Group::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp1 = e->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if(e->snap_intersect_point(pt,ent,rect))
			return true;
	}
	return false;
}
bool Group::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	EntityIDArray::const_iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		Entity * e = NULL;
		private_db_->entity_from_id(e,*iter);
		Rect temp1 = e->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if(e->snap_intersect_point_imp(pt,snap,rect))
			return true;
	}
	return false;
}

void Group::push_back_id(const Entity_ID& id)
{
	assert(	private_db_ );
	ids_.push_back(id);
}
EntityIDArray::iterator Group::begin()
{
	return ids_.begin();
}
EntityIDArray::iterator Group::end()
{
	return ids_.end();
}
bool Group::remove(Entity_ID id)
{
	EntityIDArray::iterator iter;
	for(iter=ids_.begin();iter!=ids_.end();++iter){
		if(id == (*iter)){
			ids_.erase(iter);
			return true;
		}
	}
	return false;
}
bool Group::pt_in(const Point& pt) const
{
	return pt.envelop(box2d());
}



}
