#include "stdafx.h"
#include "Group_Ents.h"
#include "Point.h"
#include "Database.h"
//#include "Paint_Entity.h"
#include <algorithm>
//#include "..\DrawDll\reitrace.h"

#include "Line.h"
#include "./global.h"

#include <assert.h>

using namespace std;

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Group_Ents,Entity)
Group_Ents::Group_Ents()
MCT_INIT1("Group_Ents")
{
//	id_ = 0;
}
Group_Ents::~Group_Ents()
{

}
//Group_Ents* Group_Ents::create_me()
//{
//	return new Group_Ents();
//}
//bool Group_Ents::close()
//{
//	delete this;
//	return true;
//}
Group_Ents::Group_Ents(const Group_Ents& rhs)
:Entity(rhs)
MCT_INIT2("Group_Ents")
{
	db_ = rhs.db_;
	id_ = rhs.id_;
//	EntityIDArray::const_iterator iter;
//	for(iter=rhs.ids_.begin();iter!=rhs.ids_.end();++iter){
//		ids_.push_back(*iter);
//	}
	////同时克隆所关联的实体
	dlhml::copy(rhs.ents_, ents_);

	lt_ = rhs.lt_;
	rb_ = rhs.rb_;
}
Group_Ents& Group_Ents::operator=(const Group_Ents& rhs)
{
  Entity::operator=(rhs);

	if(this == &rhs)
		return *this;
	id_ = rhs.id_;
	db_ = rhs.db_;
//	EntityIDArray::const_iterator iter;
//	for(iter=rhs.ids_.begin();iter!=rhs.ids_.end();++iter){
//		ids_.push_back(*iter);
//	}
	////同时克隆所关联的实体
	dlhml::copy(rhs.ents_, ents_);

	lt_ = rhs.lt_;
	rb_ = rhs.rb_;

	return *this;
}
bool Group_Ents::operator==(const Group_Ents& rhs)
{
	if(id_ == rhs.id_)
		return false;
	return true;
	/*
	if(ids_.size() != rhs.ids_.size())
		return FALSE;
	int count=0;
	for(int i=0;i<rhs.ids_.size();i++){
		EntityIDArray::iterator iter = std::find(ids_.begin(),ids_.end(),rhs.ids_[i]);
		if(iter != ids_.end())
			count++;
	}
	if(count != ids_.size())
		return false;
	return true;
	*/
}

void Group_Ents::get_lines(vector<Entity*>& lns)const
{
	Point rt(rb_.x, lt_.y);
	Point lb(lt_.x, rb_.y);

	Line * ln1 = Line::create_me();
	ln1->setdata(lt_, rt);
	ln1->color_index(color_index());
	lns.push_back(ln1);
	Line * ln2 = Line::create_me();
	ln2->setdata(rt, rb_);
	ln2->color_index(color_index());
	lns.push_back(ln2);
	Line * ln3 = Line::create_me();
	ln3->setdata(rb_, lb);
	ln3->color_index(color_index());
	lns.push_back(ln3);
	Line * ln4 = Line::create_me();
	ln4->setdata(lb, lt_);
	ln4->color_index(color_index());
	lns.push_back(ln4);
}

//****************
void Group_Ents::loadme(File& in)
{
	box_change(true);
	lt_.load(in);
	rb_.load(in);
}
void Group_Ents::saveme(const File& out) const
{
	lt_.save(out);
	rb_.save(out);
}

void Group_Ents::edit_propertyme(const Edit_Entity& edit)
{	
	box_change(true);
}
void Group_Ents::drawme(Draw_Entity& out) const
{
	vector<Entity*> es;
	get_lines(es);
	dlhml::select(es, seled_);
	dlhml::draw(es, out, false);
	destory(es);
}
void Group_Ents::xor_drawme(Draw_Entity& out) const
{
	vector<Entity*> es;
	get_lines(es);
	dlhml::select(es, seled_);
	dlhml::draw(es, out, true);
	destory(es);
}
errorinfo Group_Ents::postme2db(Database& db,Entity_ID& id)
{
	box_change(true);
	return db.entity_push_back(this,id);
}
void Group_Ents::transformbyme(const Matrix& mat)
{
	box_change(true);
	tramsfromby_content(mat);
	lt_.transformby(mat);
	rb_.transformby(mat);
}
void Group_Ents::drag_startme(const Matrix& mat)
{
	box_change(true);
}
void Group_Ents::drag_endme(const Matrix& mat)
{
	box_change(true);
}
Entity* Group_Ents::cloneme() const
{
	return new Group_Ents(*this);
}
void Group_Ents::closeme()
{
	box_change(true);
	delete this;
}
bool Group_Ents::intersectme(const Rect& rect) const
{
	vector<Entity*>	es;
	get_lines(es);
	bool thereuslt = false;
	int i=0;
	for(i=0; i<es.size(); ++i){
		if(es[i] && es[i]->intersect(rect)){
			thereuslt = true;
		}
	}
	destory(es);
	return thereuslt;
}
bool Group_Ents::envelopme(const Rect& rect) const
{
	vector<Entity*>	es;
	get_lines(es);
	bool thereuslt = true;
	int i=0;
	for(i=0; i<es.size(); ++i){
		if(es[i] && !es[i]->envelop(rect)){
			thereuslt = false;
			break;
		}
	}
	destory(es);
	return thereuslt;
}
void Group_Ents::update_box2d()
{
	Rect rc = box2d_content();
	lt_.x = rc.xmin();
	lt_.y = rc.ymax();
	rb_.x = rc.xmax();
	rb_.y = rc.ymin();
}
Rect Group_Ents::calc_box2d() const
{
	Rect box2d_;
	box2d_.xmin(min(lt_.x, rb_.x));
	box2d_.ymin(min(lt_.y, rb_.y));
	box2d_.xmax(max(lt_.x, rb_.x));
	box2d_.ymax(max(lt_.y, rb_.y));
	return box2d_;
}
bool Group_Ents::snap_endpointme(Point& pt,const Rect& rect) const
{
	return false;
}
bool Group_Ents::snap_center_pointme(Point& pt,const Rect& rect) const
{
	return false;
}
bool Group_Ents::snap_middle_pointme(Point& pt,const Rect& rect) const
{
	return false;
}
bool Group_Ents::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
	return false;
}
bool Group_Ents::snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const
{
	return false;
}
bool Group_Ents::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
	return false;
}
bool Group_Ents::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return false;
}
//****************






void Group_Ents::push_back(Entity * e)
{
	box_change(true);
	assert(e);
	ents_.push_back(e);
}
void Group_Ents::push_back(const Entity_ID& id)
{
	box_change(true);
	Entity * e = NULL;
	db_->entity_from_id(e, id);
	push_back(e);
}

void Group_Ents::push_back(const std::vector<Entity*>& es)
{
	box_change(true);
	dlhml::push_back<Entity>(es, ents_);
}
int Group_Ents::entity_count()const
{
  //NOOK
//	box_change(true);
	return ents_.size();
}



//void Group_Ents::push_back(const Entity_ID& id)
//{
////	ids_.push_back(id);
//	Entity * e = NULL; 
//	if(db_->entity_from_id(e, id) == Error::OK){
//		ents_.push_back(e);
//	}
//}
//void Group_Ents::push_back(const EntityIDArray& ids)
//{
//	EntityIDArray::const_iterator iter;
//	for(iter=ids.begin();iter!=ids.end();++iter)
//		ids_.push_back(*iter);
//}
//const EntityIDArray::iterator Group_Ents::begin()const
//{
//	return ids_.begin();
//}
//const EntityIDArray::iterator Group_Ents::end()const
//{
//	return ids_.end();
//}
//int Group_Ents::ids_count()
//{
//	return ids_.size();
//}
//void Group_Ents::delete_ids()
//{
//	for(int i=0;i<ids_.size();i++){
//		db_->remove_entity(ids_[i]);
//	}
////	EntityIDArray::const_iterator iter;
////	for(iter=ids_.begin();iter!=ids_.end();++iter){
////		db_->remove_entity(*iter);
////	}
//}
void Group_Ents::clear()
{
	box_change(true);
	ents_.clear();
}
void Group_Ents::erase(const Entity * e)
{
	box_change(true);
	dlhml::erase(ents_, e);
}
//bool Group_Ents::remove(Entity_ID id)
//{
//	EntityIDArray::iterator iter;
//	for(iter=ids_.begin();iter!=ids_.end();++iter){
//		if(id == (*iter)){
//			ids_.erase(iter);
//			return true;
//		}
//	}
//	return false;
//}

void Group_Ents::setat(int i, Entity * e)
{
	box_change(true);
	ents_[i] = e;
}
Entity * Group_Ents::getat(int i)const
{
	return ents_[i];
}

Entity * Group_Ents::operator[] (int i)
{
	box_change(true);
	return ents_[i];
}
const Entity * Group_Ents::operator[] (int i) const
{
	return ents_[i];
}


bool Group_Ents::isin(const Point& pt) const
{
	Rect rect = box2d();
	return pt.envelop(rect);
}
bool Group_Ents::isin(const Entity* e) const
{
	if(!e) return false;
	int i=0;
	for(i=0;i<ents_.size();i++){
		if(e == ents_[i])
			return true;
	}
	return false;
}
//bool Group_Ents::isin(Entity * e)
//{
//	if(!e) return false;
//	int i=0;
//	for(i=0;i<ents_.size();i++){
//		if(id == ids_[i])
//			return true;
//	}
//	return false;
//}

void Group_Ents::selected(bool b)
{
	Entity::selected(b);
	dlhml::select(ents_, b);
}

Rect Group_Ents::box2d_content() const
{
	Rect box2d;
	box2d.set_reverse_minmax();
	int i=0;
	for(i=0; i<ents_.size(); ++i){
		Entity * e = ents_[i];
		if(e == NULL)
			continue;
		Rect temp = e->box2d();
		box2d.xmin(min(box2d.xmin(),temp.xmin()));
		box2d.ymin(min(box2d.ymin(),temp.ymin()));
		box2d.xmax(max(box2d.xmax(),temp.xmax()));
		box2d.ymax(max(box2d.ymax(),temp.ymax()));
	}
	return box2d;
}
void Group_Ents::tramsfromby_content(const Matrix& mat)
{
	box_change(true);
	int i=0;
	for(i=0; i<ents_.size(); ++i){
		Entity * e = ents_[i];
		if(e ==NULL)
			continue;
		e->transformby(mat);
	}
}
//Rect Group_Ents::box2d_content() const
//{
//	Rect box2d;
//	box2d.set_reverse_minmax();
//	EntityIDArray::const_iterator iter;
//	for(iter=ids_.begin();iter!=ids_.end();++iter){
//		Entity * e = NULL;
//		db_->entity_from_id(e,*iter);
//		if(e == NULL)
//			continue;
//		Rect temp = e->box2d();
//		box2d.xmin(min(box2d.xmin(),temp.xmin()));
//		box2d.ymin(min(box2d.ymin(),temp.ymin()));
//		box2d.xmax(max(box2d.xmax(),temp.xmax()));
//		box2d.ymax(max(box2d.ymax(),temp.ymax()));
//	}
//	return box2d;
//}
//void Group_Ents::tramsfromby_content(const Matrix& mat)
//{
//	REITRACE;
//	EntityIDArray::const_iterator iter;
//	for(iter=ids_.begin();iter!=ids_.end();++iter){
//		Entity * e = NULL;
//		db_->entity_from_id(e,*iter);
//		if(e ==NULL)
//			continue;
//		REITRACE;
//		e->transformby(mat);
//		REITRACE;
//	}
//}
//void Group_Ents::add_selected(Paint_Entity & paint,std::vector<Entity*>& ents)
//{
//	EntityIDArray::const_iterator iter;
//	for(iter=ids_.begin();iter!=ids_.end();++iter){
//		Entity * e = NULL;
//		db_->entity_from_id(e,*iter);
//		if(e == NULL)
//			continue;
//		e->xor_draw(paint);
//		e->selected(true);
//		e->draw(paint);
//		ents.push_back(e);
//	}
//}
//void Group_Ents::show_ids(Paint_Entity & paint)
//{
//	EntityIDArray::const_iterator iter;
//	for(iter=ids_.begin();iter!=ids_.end();++iter){
//		Entity * e = NULL;
//		db_->entity_from_id(e,*iter);
//		if(e == NULL)
//			continue;
//		e->xor_draw(paint);
//		e->selected(true);
//		e->draw(paint);
//	}
//}


//*************************
Point Group_Ents::focus()const
{
  Rect box = box2d();
  double x = ( box.xmin()+box.xmax() )/2;
  double y = ( box.ymin()+box.ymax() )/2;
  return Point(x,y);
}

void Group_Ents::setctrl(const std::vector<Point>& pts)
{
	box_change(true);
	assert(pts.size() >= 2);
	lt_ = pts[0];
	rb_ = pts[1];
}
void Group_Ents::getctrl(std::vector<Point>& pts) const
{
	pts.push_back(lt_);
	pts.push_back(rb_);
}
int  Group_Ents::pt_count()const
{
	return 2;
}
void Group_Ents::setdrag(const std::vector<Point>& pts, int index)
{
	box_change(true);
	if(pts.size() < 8){
		return;
	}
//	Point rt = pts[2];
//	Point lb = pts[3];
	switch(index)
	{
		case 0:
			lt_ = pts[0];
			break;
		case 1:
			rb_ = pts[1];
			break;
		case 2:
			rb_.x = pts[2].x;
			lt_.y = pts[2].y;
			break;
		case 3:
			lt_.x = pts[3].x;
			rb_.y = pts[3].y;
			break;
		case 4:
			lt_.y = pts[4].y;
			break;
		case 5:
			rb_.y = pts[5].y;
			break;
		case 6:
			lt_.x = pts[6].x;
			break;
		case 7:
			rb_.x = pts[7].x;
			break;
	}
}
void Group_Ents::getdrag(std::vector<Point>& pts) const
{
	Point rt(rb_.x, lt_.y);
	Point lb(lt_.x, rb_.y);
	Point top((rb_.x + lt_.x)/2, lt_.y);
	Point bottom((rb_.x + lt_.x)/2, rb_.y);
	Point left(lt_.x, (lt_.y + rb_.y)/2);
	Point right(rb_.x, (lt_.y + rb_.y)/2);
	////4个角控制0:lt_, 1:rb_, 2:rt, 3:lb.
	pts.push_back(lt_);
	pts.push_back(rb_);
	pts.push_back(rt);
	pts.push_back(lb);
	////4个边控制4:top, 5:bottom, 6:left, 7:right.
	pts.push_back(top);
	pts.push_back(bottom);
	pts.push_back(left);
	pts.push_back(right);
}


}//namespace
