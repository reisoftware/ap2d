// Database_Private.cpp: implementation of the Database_Private class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Database_Private.h"
#include "Entity.h"
#include <algorithm>
#include <cassert>
#include <functional>
#include "File.h"
#include "Rect.h"
#include "Snap.h"
#include "Layer.h"
#include "Line_Type.h"
#include "Text_Style.h"
#include "Paint_Snap.h"
#include "Dimension_Style.h"
#include "Block.h"
#include "iolua.h"
#include "Lua_Tab.h"
#include "getrace.h"

static dlhml::Database *g_db = NULL;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

namespace dlhml{

std::vector<Entity*> g_ents_luafile_;

const ULONG Database_Private::START_ENTITY_NO = 100;

Database_Private::Database_Private()
:index_(0)
MCT_INIT2("Database_Private")
{
	box2d_.set_reverse_minmax();

	Line_Type* type = Line_Type::create_me();
	type->name("Continuous");
	linetypelist_.push_back(type);

	Line_Type* type1 = Line_Type::create_me();
	type1->name("dot");
	DWORD style1[]={1,1};
	type1->set_style(style1,sizeof(style1)/sizeof(DWORD));
	linetypelist_.push_back(type1);

	Line_Type* type2 = Line_Type::create_me();
	type2->name("center");
	DWORD style2[]={5,1,1,1};
	type2->set_style(style2,sizeof(style2)/sizeof(DWORD));
	linetypelist_.push_back(type2);

	LOGFONT lf;
	HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	::GetObject(hFont,sizeof(LOGFONT),&lf);
	Text_Style* ts = Text_Style::create_me();
	ts->name("Standard");
	strcpy(ts->PrimaryFontFilename,"txt");
	ts->logfont(lf);
	textstylelist_.push_back(ts);

	Dimension_Style* ds = Dimension_Style::create_me();
	ds->name("Standard");
	dimensionstylelist_.push_back(ds);
}

Database_Private::~Database_Private()
{
	clear_entity();
	clear_layer();
	clear_linetype();
	clear_textstyle();
	clear_dimensionstyle();
	clear_group_ents();
}
void Database_Private::close()
{
	delete this;
}
void Database_Private::clear_layer()
{
	std::for_each(layerlist_.begin(),layerlist_.end(),
		std::mem_fun<bool,Layer>(&Layer::close));
	layerlist_.clear();
}
layer_iterator Database_Private::layer_begin()
{
	return layerlist_.begin();

}
layer_iterator Database_Private::layer_end()
{
	return layerlist_.end();
}

void Database_Private::clear_linetype()
{
	std::for_each(linetypelist_.begin(),linetypelist_.end(),
		std::mem_fun<bool,Line_Type>(&Line_Type::close));
	linetypelist_.clear();
}
void Database_Private::clear_textstyle()
{
	std::for_each(textstylelist_.begin(),textstylelist_.end(),
		std::mem_fun<bool,Text_Style>(&Text_Style::close));
	textstylelist_.clear();
}
void Database_Private::clear_dimensionstyle()
{
	std::for_each(dimensionstylelist_.begin(),dimensionstylelist_.end(),
		std::mem_fun<bool,Dimension_Style>(&Dimension_Style::close));
	dimensionstylelist_.clear();
}
void Database_Private::clear_group_ents()
{
	////已经随着databa一同清空了
}
//void Database_Private::clear_group_ents()
//{
//	std::for_each(group_ents_.begin(),group_ents_.end(),
//		std::mem_fun<bool,Group_Ents>(&Group_Ents::close));
//	group_ents_.clear();
//}
Rect Database_Private::current_rect() const
{
	return box2d_;
}
void Database_Private::update_rect(const Entity* pEnt)
{
	Rect temp = pEnt->box2d();
	box2d_.xmin(min(box2d_.xmin(),temp.xmin()));
	box2d_.ymin(min(box2d_.ymin(),temp.ymin()));
	box2d_.xmax(max(box2d_.xmax(),temp.xmax()));
	box2d_.ymax(max(box2d_.ymax(),temp.ymax()));
}
entity_iterator Database_Private::entity_begin()
{
	return entlist_.begin();
}
entity_iterator Database_Private::entity_end()
{
	return entlist_.end();
}
int Database_Private::entity_size() const
{
	return entlist_.size();
}
void Database_Private::clear_entity()
{
//	std::for_each(entlist_.begin(),
//								entlist_.end(),
//								std::mem_fun<bool,Entity>(&Entity::close));
	int aaa = entlist_.size();
	int i=0;
	for(; i<entlist_.size(); i++){
		if(entlist_[i]){
			entlist_[i]->close();
			entlist_[i] = NULL;
		}
	}
	entlist_.clear();
//	clear_group_ents();

	index_ = 0;
}
entity_iterator Database_Private::find(const Entity_ID& id)
{ 
	for(entity_iterator iter=entlist_.begin();iter!=entlist_.end();++iter){
		if((*iter)->entity_id() == id)
			return iter;
	}
	return entlist_.end();
}
entity_const_iterator Database_Private::find(const Entity_ID& id) const
{
	for(std::vector<Entity*>::const_iterator iter=entlist_.begin();iter!=entlist_.end();++iter){
		if((*iter)->entity_id() == id)
			return iter;
	}
	return entlist_.end();
}
errorinfo Database_Private::erase_entity(const Entity_ID& id)
{
	entity_iterator iter = find(id);
	(*iter)->close();
	entlist_.erase(iter);
	return Error::OK;
}
errorinfo Database_Private::remove_entity(const Entity_ID& id)
{
	//NOOK 为什么不把实体从对应的组中去掉？
	entity_iterator iter = find(id);
	//把实体从对应的组中去掉
//	remove_ent_in_group(id);
	if(iter == entlist_.end())
		return Error::NullObjectP;
	entlist_.erase(iter);
	return Error::OK;
}

errorinfo Database_Private::entity_from_id(Entity*& pEnt,const Entity_ID& id) const
{
	std::vector<Entity*>::const_iterator iter = find(id);
	if(iter != entlist_.end()){
		pEnt = *iter;
		return Error::OK;
	}
	return Error::NullObjectP;
}

void Database_Private::calc_index(Entity* pEnt,Entity_ID& id)
{  
  assert(pEnt && "pEnt mustn't be null.");
  if(pEnt->id_.is_default()){
    pEnt->id_.entity_id(++index_);
  }
  else if(find(pEnt->id_) != entity_end()){
    pEnt->id_.entity_id(++index_);
  }
  id = pEnt->id_;
//   assert(pEnt && "pEnt mustn't be null.");
//   entity_const_iterator it = find(pEnt->id_);
//   if(pEnt->id_.is_default() || it != entity_end()){
//     pEnt->id_.entity_id(index);
//   }
//   id = pEnt->id_;
}

errorinfo Database_Private::entity_push_back(Entity* pEnt,Entity_ID& id)
{
	if(!pEnt)
		return Error::NullObjectP;
  index_ = max(pEnt->entity_id().entity_id(), index_);
  // 	index_++;
	calc_index(pEnt,id);
	entlist_.push_back(pEnt);
	update_rect(pEnt);
	return Error::OK;
}
errorinfo Database_Private::save_file(std::string filename) const
{
	Error::info error;
	File file;
	error = file.open(filename.c_str(),TEXT("wb"));
	if(error == Error::OK){
		save_entity(file);
		file.close();
	}
	return error;
}
errorinfo Database_Private::open_file(std::string filename)
{
	Error::info error;
	File file;
	error = file.open(filename.c_str(),TEXT("rb"));
	if(error == Error::OK){
		load_entity(file);
		file.close();
	}
	return error;
}

// void Database_Private::lua_save(oLua_File &fout)const
// {
// 	fout.save_array("entlist_", entlist_.begin(), entlist_.end());
// 	fout.save_array("layerlist_", layerlist_.begin(), layerlist_.end());
// 	fout.save_array("linetypelist_", linetypelist_.begin(), linetypelist_.end());
// 	fout.save_array("textstylelist_", textstylelist_.begin(), textstylelist_.end());
// 	fout.save_array("dimensionstylelist_", dimensionstylelist_.begin(), dimensionstylelist_.end());
// }
// void Database_Private::lua_load(iLua_File &fin)
// {
// }

void Database_Private::load_entity(File& in)
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
		Entity_ID id;
		pEnt->post2db(*this,id);
	}
}
void Database_Private::load_entity_to_id(File& in,EntityIDArray& ents)
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
		Entity_ID id;
		pEnt->post2db(*this,id);
		ents.push_back(id);
	}
}
void Database_Private::save_entity(const File& out) const
{
	int num = entlist_.size();
	out << num;
	std::vector<Entity*>::const_iterator iter = NULL;
	iter = entlist_.begin();
	for( ; iter != entlist_.end(); ++iter){
		Runtime_Class* pR = (*iter)->GetRuntimeClass();
		out << pR->classname;
		(*iter)->save(out);
	}
}
void Database_Private::load_entity_order(File& in,std::vector<EntityIDArray>& orders)
{
	int idvecnum = 0;
	in >> idvecnum;
	int i=0;
	for(i=0;i<idvecnum;++i){
		EntityIDArray ids;
		int subnum = 0;
		in >> subnum;
		for(int j=0;j<subnum;++j){
			char* classname = NULL;
			in >> classname;
			Runtime_Class* pR = NULL;
			pR = Runtime_Class::load(classname);
			delete [] classname;
			Object* pO = NULL;
			pO = pR->createob();
			Entity* pEnt = static_cast<Entity*>(pO);
			pEnt->load(in);
			Entity_ID id;
			pEnt->post2db(*this,id);
			ids.push_back(id);
		}
		orders.push_back(ids);
	}
	int leftnum=0;
	in >> leftnum;
	for(i=0;i<leftnum;++i){
		char* classname = NULL;
		in >> classname;
		Runtime_Class* pR = NULL;
		pR = Runtime_Class::load(classname);
		delete [] classname;
		Object* pO = NULL;
		pO = pR->createob();
		Entity* pEnt = static_cast<Entity*>(pO);
		pEnt->load(in);
		Entity_ID id;
		pEnt->post2db(*this,id);
	}
}
void Database_Private::save_entity_order(const File& out,const std::vector<EntityIDArray>& orders) const
{
	int ordertotal = 0;
	int idvecnum = orders.size();
	out << idvecnum;
	for(int i=0;i<idvecnum;++i){
		int subnum = orders[i].size();
		out << subnum;
		ordertotal += subnum;
		EntityIDArray::const_iterator iter =0;
		iter = orders[i].begin();
		for(;iter!=orders[i].end();++iter){
			Entity* ent=0;
			entity_from_id(ent,*iter);
			Runtime_Class* pR = ent->GetRuntimeClass();
			out << pR->classname;
			ent->save(out);
		}
	}
	int leftnum = entlist_.size()-ordertotal;
	out << leftnum;
	std::vector<Entity*>::const_iterator iter = 0;
	iter = entlist_.begin();
	for( ; iter != entlist_.end(); ++iter){
		Entity_ID id = (*iter)->entity_id();
		int j=0;
		for(;j<idvecnum;++j){
			EntityIDArray::const_iterator it=0;
			it=std::find(orders[j].begin(),orders[j].end(),id);
			if(it!=orders[j].end())
				break;
		}
		if(j<idvecnum)
			continue;
		Runtime_Class* pR = (*iter)->GetRuntimeClass();
		out << pR->classname;
		(*iter)->save(out);
	}
}
errorinfo Database_Private::group_entity_rect(Rect& rect,const EntityIDArray& ents) const
{
	if(ents.size() == 0)
		return Error::NullObjectIdAry;
	rect.set_reverse_minmax();
	EntityIDArray::const_iterator iter = NULL;
	iter = ents.begin();
	Entity* pEnt = NULL;
	for(; iter != ents.end(); ++iter){
		if(Error::OK == entity_from_id(pEnt,*iter)){
			Rect temp = pEnt->box2d();
			rect.xmin(min(rect.xmin(),temp.xmin()));
			rect.ymin(min(rect.ymin(),temp.ymin()));
			rect.xmax(max(rect.xmax(),temp.xmax()));
			rect.ymax(max(rect.ymax(),temp.ymax()));
		}
	}
	return Error::OK;
}
errorinfo Database_Private::all_entity_rect(Rect& rect) const
{
	if(entlist_.size() == 0)
		return Error::NullObjectIdAry;
	rect.set_reverse_minmax();

	std::vector<Entity*>::const_iterator iter = NULL;
	iter = entlist_.begin();
	for( ; iter != entlist_.end(); ++iter){
		Rect temp = (*iter)->box2d();
		rect.xmin(min(rect.xmin(),temp.xmin()));
		rect.ymin(min(rect.ymin(),temp.ymin()));
		rect.xmax(max(rect.xmax(),temp.xmax()));
		rect.ymax(max(rect.ymax(),temp.ymax()));
	}
	return Error::OK;
}
bool Database_Private::select_block(Block*& block,const Point& pt) const
{
	int num = 0;
	Block* temp = 0;
	std::vector<Entity*>::const_iterator iter = 0;
	for(iter = entlist_.begin();iter != entlist_.end(); ++iter){
		if((*iter)->isa(MY_RUNTIME_CLASS(Block))){
			Block* block1 = (Block*)(*iter);
			if(block1->pt_in(pt)){
				temp = block1;
				++num;
			}
			if(num>1)
				return false;
		}
	}
	if(num==1){
		block = temp;
		return true;
	}
	return false;
}

bool Database_Private::snap_endpt(Paint_Snap& ps,
																	 Point& pt,
																	 const Rect& rect,
																	 const Snap& flag,
																	 const Point& o) const
{
  std::vector<Entity*>::const_iterator iter = NULL;
  for(iter=entlist_.begin(); iter!=entlist_.end();++iter){
    Rect temp = (*iter)->box2d();
    if(temp.xmax() < rect.xmin())
      continue;
    if(temp.xmin() > rect.xmax())
      continue;
    if(temp.ymax() < rect.ymin())
      continue;
    if(temp.ymin() > rect.ymax())
      continue;
    if(!(*iter)->intersect(rect))
      continue;
    if(flag.endpoint()){
      if((*iter)->snap_endpoint(pt,rect)){
        ps.set_snap(Snap::Endpoint);
        return true;
      }
    }
  }
  ps.set_zero();
  return false;
}

bool Database_Private::snap_middle(Paint_Snap& ps,
																	 Point& pt,
																	 const Rect& rect,
																	 const Snap& flag,
																	 const Point& o) const
{
  std::vector<Entity*>::const_iterator iter = NULL;
  for(iter=entlist_.begin(); iter!=entlist_.end();++iter){
    Rect temp = (*iter)->box2d();
    if(temp.xmax() < rect.xmin())
      continue;
    if(temp.xmin() > rect.xmax())
      continue;
    if(temp.ymax() < rect.ymin())
      continue;
    if(temp.ymin() > rect.ymax())
      continue;
    if(!(*iter)->intersect(rect))
      continue;
    if(flag.middle()){
      if((*iter)->snap_middle_point(pt,rect)){
        ps.set_snap(Snap::Middle);
        return true;
      }
    }
  }
  ps.set_zero();
  return false;
}

bool Database_Private::snap_center(Paint_Snap& ps,
																	 Point& pt,
																	 const Rect& rect,
																	 const Snap& flag,
																	 const Point& o) const
{
  std::vector<Entity*>::const_iterator iter = NULL;
  for(iter=entlist_.begin(); iter!=entlist_.end();++iter){
    Rect temp = (*iter)->box2d();
    if(temp.xmax() < rect.xmin())
      continue;
    if(temp.xmin() > rect.xmax())
      continue;
    if(temp.ymax() < rect.ymin())
      continue;
    if(temp.ymin() > rect.ymax())
      continue;
    if(!(*iter)->intersect(rect))
      continue;
    if(flag.center()){
      if((*iter)->snap_center_point(pt,rect)){
        ps.set_snap(Snap::Center);
        return true;
      }
    }
  }
  ps.set_zero();
  return false;
}

bool Database_Private::snap_perpendicular(Paint_Snap& ps,
																	 Point& pt,
																	 const Rect& rect,
																	 const Snap& flag,
																	 const Point& o) const
{
  std::vector<Entity*>::const_iterator iter = NULL;
  for(iter=entlist_.begin(); iter!=entlist_.end();++iter){
    Rect temp = (*iter)->box2d();
    if(temp.xmax() < rect.xmin())
      continue;
    if(temp.xmin() > rect.xmax())
      continue;
    if(temp.ymax() < rect.ymin())
      continue;
    if(temp.ymin() > rect.ymax())
      continue;
    if(!(*iter)->intersect(rect))
      continue;
    if(flag.perpendicular()){
      Point pp;
      if((*iter)->snap_perpendicular_point(pp,rect,o)){
        if(o==pp)
          continue;
        pt = pp;
        ps.set_snap(Snap::Perpendicular);
        return true;
      }
    }
  }
  ps.set_zero();
  return false;
}

bool Database_Private::snap_intersect(Paint_Snap& ps,
																	 Point& pt,
																	 const Rect& rect,
																	 const Snap& flag,
																	 const Point& o) const
{
  std::vector<Entity*>::const_iterator iter = NULL;
  for(iter=entlist_.begin(); iter!=entlist_.end();++iter){
    Rect temp = (*iter)->box2d();
    if(temp.xmax() < rect.xmin())
      continue;
    if(temp.xmin() > rect.xmax())
      continue;
    if(temp.ymax() < rect.ymin())
      continue;
    if(temp.ymin() > rect.ymax())
      continue;
    if(!(*iter)->intersect(rect))
      continue;

    if(flag.intersect()){
      std::vector<Entity*>::const_iterator it;
      for(it=entlist_.begin();it!=entlist_.end();++it){
        //				if(*it == *iter)
        //					continue;
        Rect temp1 = (*it)->box2d();
        if(temp1.xmax() < rect.xmin())
          continue;
        if(temp1.xmin() > rect.xmax())
          continue;
        if(temp1.ymax() < rect.ymin())
          continue;
        if(temp1.ymin() > rect.ymax())
          continue;
        if(!(*it)->intersect(rect))
          continue;
        if((*it)->snap_intersect_point(pt,*(*iter),rect)){
          ps.set_snap(Snap::Intersect);
          return true;
        }
      }
    }
  }
  ps.set_zero();
  return false;
}

bool Database_Private::snap_nearest(Paint_Snap& ps,
																	 Point& pt,
																	 const Rect& rect,
																	 const Snap& flag,
																	 const Point& o) const
{
  std::vector<Entity*>::const_iterator iter = NULL;
  for(iter=entlist_.begin(); iter!=entlist_.end();++iter){
    Rect temp = (*iter)->box2d();
    if(temp.xmax() < rect.xmin())
      continue;
    if(temp.xmin() > rect.xmax())
      continue;
    if(temp.ymax() < rect.ymin())
      continue;
    if(temp.ymin() > rect.ymax())
      continue;
    if(!(*iter)->intersect(rect))
      continue;

    if(flag.nearest()){
      if((*iter)->snap_nearest_point(pt,rect)){
        ps.set_snap(Snap::Nearest);
        return true;
      }
    }
  }
  ps.set_zero();
  return false;
}

bool Database_Private::snap_entity(Paint_Snap& ps,
																	 Point& pt,
																	 const Rect& rect,
																	 const Snap& flag,
																	 const Point& o) const
{
	if(snap_endpt(ps, pt, rect, flag, o)){
		return true;
	}
	if(snap_middle(ps, pt, rect, flag, o)){
		return true;
	}
	if(snap_center(ps, pt, rect, flag, o)){
		return true;
	}
	if(snap_perpendicular(ps, pt, rect, flag, o)){
		return true;
	}
	if(snap_intersect(ps, pt, rect, flag, o)){
		return true;
	}
	if(snap_nearest(ps, pt, rect, flag, o)){
		return true;
	}
  ps.set_zero();
  return false;

	////
  std::vector<Entity*>::const_iterator iter = NULL;
  for(iter=entlist_.begin(); iter!=entlist_.end();++iter){
    Rect temp = (*iter)->box2d();
    if(temp.xmax() < rect.xmin())
      continue;
    if(temp.xmin() > rect.xmax())
      continue;
    if(temp.ymax() < rect.ymin())
      continue;
    if(temp.ymin() > rect.ymax())
      continue;
    if(!(*iter)->intersect(rect))
      continue;
    if(flag.endpoint()){
      if((*iter)->snap_endpoint(pt,rect)){
        ps.set_snap(Snap::Endpoint);
        return true;
      }
    }
    if(flag.middle()){
      if((*iter)->snap_middle_point(pt,rect)){
        ps.set_snap(Snap::Middle);
        return true;
      }
    }
    if(flag.center()){
      if((*iter)->snap_center_point(pt,rect)){
        ps.set_snap(Snap::Center);
        return true;
      }
    }
    if(flag.perpendicular()){
      Point pp;
      if((*iter)->snap_perpendicular_point(pp,rect,o)){
        if(o==pp)
          continue;
        pt = pp;
        ps.set_snap(Snap::Perpendicular);
        return true;
      }
    }
    if(flag.intersect()){
      std::vector<Entity*>::const_iterator it;
      for(it=entlist_.begin();it!=entlist_.end();++it){
        //				if(*it == *iter)
        //					continue;
        Rect temp1 = (*it)->box2d();
        if(temp1.xmax() < rect.xmin())
          continue;
        if(temp1.xmin() > rect.xmax())
          continue;
        if(temp1.ymax() < rect.ymin())
          continue;
        if(temp1.ymin() > rect.ymax())
          continue;
        if(!(*it)->intersect(rect))
          continue;
        if((*it)->snap_intersect_point(pt,*(*iter),rect)){
          ps.set_snap(Snap::Intersect);
          return true;
        }
      }
    }
    if(flag.nearest()){
      if((*iter)->snap_nearest_point(pt,rect)){
        ps.set_snap(Snap::Nearest);
        return true;
      }
    }
    //if(flag.center()){
    //if((*iter)->snap_center_point(pt,rect)){
    //ps.set_snap(Snap::Center);
    //UINT
    //}
    //}
  }
  ps.set_zero();
  return false;
}
void Database_Private::layer_push_back(Layer* layer)
{
	layerlist_.push_back(layer);
}
bool Database_Private::get_layer(Layer*& layer,std::string name) const
{
	std::vector<Layer*>::const_iterator iter = 0;
	iter = layerlist_.begin();
	for( ; iter != layerlist_.end(); ++iter){
		if(0==strcmp((*iter)->name().c_str(),name.c_str())){
			layer = *iter;
			return true;
		}
	}
	return false;
}
void Database_Private::linestyle_push_back(Line_Type* type)
{
	linetypelist_.push_back(type);
}
bool Database_Private::get_linetype(Line_Type*& type,std::string name) const
{
	std::vector<Line_Type*>::const_iterator iter = NULL;
	iter = linetypelist_.begin();
	for( ; iter != linetypelist_.end(); ++iter){
		if(0==strcmp((*iter)->name(),name.c_str())){
			type = *iter;
			return true;
		}
	}
	return false;
}
void Database_Private::textstyle_push_back(Text_Style* style)
{
	textstylelist_.push_back(style);
}
bool Database_Private::get_textstyle(Text_Style*& style,std::string name) const
{
	std::vector<Text_Style*>::const_iterator iter = NULL;
	iter = textstylelist_.begin();
	for( ; iter != textstylelist_.end(); ++iter){
		Text_Style *ss = (*iter);
		if(0==strcmp((*iter)->name().c_str(),name.c_str())){
			style = *iter;
			return true;
		}
	}
	return false;
}
void Database_Private::dimensionstyle_pushback(Dimension_Style* style)
{
	Dimension_Style* ds = 0;
	get_dimensionstyle(ds,style->name());
	if(ds){
		style->close();
		return;
	}
	dimensionstylelist_.push_back(style);
}
bool Database_Private::delete_dimstyle(std::string name)
{
	Dimension_Style* ds = 0;
	get_dimensionstyle(ds,name);
	if(!ds)
		return false;
	std::vector<Dimension_Style*>::iterator iter = std::find(dimensionstylelist_.begin(),dimensionstylelist_.end(),ds);
	if(iter == dimensionstylelist_.end())
		return false;
	dimensionstylelist_.erase(iter);
	return true;

}
bool Database_Private::get_dimensionstyle(Dimension_Style*& style,std::string name) const
{
	std::vector<Dimension_Style*>::const_iterator iter = 0;
	iter = dimensionstylelist_.begin();
	for(; iter != dimensionstylelist_.end(); ++iter){
		if(0==strcmp((*iter)->name().c_str(),name.c_str())){
			style = *iter;
			return true;
		}
	}
	return false;
}
txt_style_iterator Database_Private::text_style_begin()
{
	return textstylelist_.begin();
}
txt_style_iterator Database_Private::text_style_end()
{
	return textstylelist_.end();
}
dim_style_iterator Database_Private::dim_style_begin()
{
	return dimensionstylelist_.begin();
}
dim_style_iterator Database_Private::dim_style_end()
{
	return dimensionstylelist_.end();
}
ltype_iterator Database_Private::lstyle_begin()
{
	return linetypelist_.begin();
}
ltype_iterator Database_Private::lstyle_end()
{
	return linetypelist_.end();
}

void Database_Private::push_group_ent(Group_Ents* group_ent)
{
	entlist_.push_back(group_ent);
}
//void Database_Private::push_group_ent(Group_Ents* group_ent)
//{
//	if(have(group_ent)){
//	}
//	else{
//		group_ents_.push_back(group_ent);
//	}
//}
bool Database_Private::have(Group_Ents* group_ent)
{
	std::vector<Group_Ents*> gps;
	get_group_ents(gps);
	if(gps.empty()){
		return false;
	}
	else{
		return true;
	}
}
//bool Database_Private::have(Group_Ents* group_ent)
//{
//	std::vector<Group_Ents*>::iterator iter = group_ents_.begin();
//	for(;iter != group_ents_.end();++iter){
//		if((*iter)->id() == group_ent->id()){
//			(*iter) = group_ent;
//			return true;
//		}
//	}
//	return false;
//}
void Database_Private::remove_group_ent(Group_Ents* group_ent)
{
	erase_entity(group_ent->entity_id());
}
//void Database_Private::remove_group_ent(Group_Ents* group_ent)
//{
//	std::vector<Group_Ents*>::iterator iter = group_ents_.begin();
//	for(;iter != group_ents_.end();++iter){
//		if(group_ent == *iter){
//			(*iter)->delete_ids();
//			group_ents_.erase(iter);
//			return ;
//		}
//	}
//}
bool Database_Private::select_group(Group_Ents*& group,const Point& pt)
{
	std::vector<Group_Ents*> gps;
	get_group_ents(gps);
	std::vector<Group_Ents*>::iterator iter = gps.begin();
	for(;iter != gps.end();++iter){
		if((*iter)->isin(pt)){
			group = *iter;
			return true;
		}
	}
	return false;
}
//bool Database_Private::select_group(Group_Ents*& group,int id)
//{
//	std::vector<Group_Ents*> gps;
//	get_group_ents(gps);
//	std::vector<Group_Ents*>::iterator iter = gps.begin();
//	for(;iter != gps.end();++iter){
//		if((*iter)->id() == id){
//			group = *iter;
//			return true;
//		}
//	}
//	return false;
//}
bool Database_Private::select_group(Group_Ents*& group,const Entity& ent)
{
	std::vector<Group_Ents*> gps;
	get_group_ents(gps);
	int i=0;
	for(i=0; i<gps.size(); ++i){
		if(gps[i]->isin(&ent)){
			group = gps[i];
			return true;
		}
	}
	return false;
}
bool Database_Private::select_group(Group_Ents*& group,const Entity_ID& id)
{
	Entity * e = NULL;
	entity_from_id(e, id);
	return select_group(group, *e);
//	std::vector<Group_Ents*> gps;
//	std::vector<Group_Ents*>::iterator iter = gps.begin();
//	for(;iter != gps.end();++iter){
//		if((*iter)->id_in(id)){
//			group = *iter;
//			return true;
//		}
//	}
//	return false;
}
//bool Database_Private::select_group(Group_Ents*& group,const Entity& ent)
//{
//  Entity_ID id = ent.entity_id();
//  return select_group(group, id);
////	std::vector<Group_Ents*>::iterator iter = group_ents_.begin();
////	for(;iter != group_ents_.end();++iter){
////		if((*iter)->id_in(id)){
////			group = *iter;
////			return true;
////		}
////	}
////	return false;
//}
//bool Database_Private::select_group(Group_Ents*& group,const Entity_ID& id)
//{
//	std::vector<Group_Ents*> gps;
//	std::vector<Group_Ents*>::iterator iter = gps.begin();
//	for(;iter != gps.end();++iter){
//		if((*iter)->id_in(id)){
//			group = *iter;
//			return true;
//		}
//	}
//	return false;
//}
//std::vector<Group_Ents*>::iterator Database_Private::group_ents_begin()
//{
//	return group_ents_.begin();
//}
//std::vector<Group_Ents*>::iterator Database_Private::group_ents_end()
//{
//	return group_ents_.end();
//}

void Database_Private::erase_ent_in_group(const Entity * ent)
{
	std::vector<Group_Ents*> gps;
	get_group_ents(gps);
	int i=0;
	for(i=0; i<gps.size(); ++i){
		gps[i]->erase(ent);
	}
}

//void Database_Private::remove_ent_in_group(const Entity_ID& id)
//{
//	std::vector<Group_Ents*> gps;
//	get_group_ents(gps);
//	std::vector<Group_Ents*>::iterator iter = gps.begin();
//	for(;iter != gps.end();++iter){
//		(*iter)->erase(id);
//	}
//}

void Database_Private::selected_all(bool sel)
{
  std::vector<Entity*>::const_iterator it = NULL;
  for(it=entlist_.begin(); it!=entlist_.end(); it++){
    (*it)->selected(sel);
  }
}

void Database_Private::get_group_ents(std::vector<Group_Ents*>& gps)const
{
  std::vector<Entity*>::const_iterator it = NULL;
  for(it=entlist_.begin(); it!=entlist_.end(); it++){
    if((*it)->isa(MY_RUNTIME_CLASS(Group_Ents))){
			gps.push_back((Group_Ents*)(*it));
    }
  }
}

void Database_Private::save_lua(char *file_name) const
{
	std::ofstream out(file_name);
	int tab_num = 0;
	lua::val_save(out,"database {",tab_num);	

//	TRACE_OUT("dimstyle num = %d \n",dimensionstylelist_.size());
	lua::begin_table(out,"dimensionstylelist_",tab_num+1);
	for(int i=0;i<dimensionstylelist_.size();i++)
		dimensionstylelist_[i]->save_lua(out,NULL,tab_num+2);
	lua::end_table(out,tab_num+1);

//	TRACE_OUT("entities num = %d \n",entlist_.size());
	lua::begin_table(out,"entlist_",tab_num+1);
	for( i=0;i<entlist_.size();i++)
		entlist_[i]->save_lua(out,NULL,tab_num+2);
	lua::end_table(out,tab_num+1);
	
	lua::val_save(out,"}",tab_num);	
}
void Database_Private::save_lua(std::vector<Entity*> &ents,std::string file_name) const
{
	std::ofstream out(file_name.c_str());
	int tab_num = 0;
	lua::val_save(out,"database {",tab_num);	

//	TRACE_OUT("dimstyle num = %d \n",dimensionstylelist_.size());
	lua::begin_table(out,"dimensionstylelist_",tab_num+1);
	for(int i=0;i<dimensionstylelist_.size();i++)
		dimensionstylelist_[i]->save_lua(out,NULL,tab_num+2);
	lua::end_table(out,tab_num+1);

//	TRACE_OUT("entities num = %d \n",ents.size());
	lua::begin_table(out,"entlist_",tab_num+1);
	for( i=0;i<ents.size();i++)
		ents[i]->save_lua(out,NULL,tab_num+2);
	lua::end_table(out,tab_num+1);
	
	lua::val_save(out,"}",tab_num);	
}

static void deal_dimstyles(lua_State *l,std::string kind)
{
	dlhml::Dimension_Style *style =  dlhml::Dimension_Style ::create_me();
	style->open_lua(l,NULL);
	g_db->dimensionstyle_pushback(style);
}
static void get_dimstylelist(lua_State *l)
{
	Lua_Tab luatab(l,"dimensionstylelist_");
	int index = lua_gettop(l);
	lua_pushnil(l);
	std::string kind;
	while(lua_next(l,index) != 0){
		get_value(string,l,kind,"kind");
		deal_dimstyles(l,kind);
		lua_pop(l,1);
	}

}
static void deal_entlists(lua_State *l,std::string kind)
{
	dlhml::Entity *ent = dlhml::create_me(kind.c_str());
	if(!ent){
		TRACE_OUT("class kind = %s invaild.\n",kind.c_str());
		return;
	}
	ent->open_lua(l,NULL);
	dlhml::Entity_ID id;
	ent->post2db(*g_db,id);
	g_ents_luafile_.push_back(ent);
}

static void get_entlist(lua_State *l)
{
	g_ents_luafile_.clear();

	Lua_Tab luatab(l,"entlist_");
	int index = lua_gettop(l);
	lua_pushnil(l);
	std::string kind;
	int num=0;
	while(lua_next(l,index) != 0){
		TRACE_OUT("the num =  %d entity\n",num++);
		if(num == 208){
			int i=0;
		}
		get_value(string,l,kind,"kind");
		deal_entlists(l,kind);
		lua_pop(l,1);
	}
}
static int open_db(lua_State *l)
{
	get_dimstylelist(l);
	get_entlist(l);

	return 0;
}
void Database_Private::open_lua(char *file_name,Database *db)
{
	g_db = db;
	lua_State *L = lua_open();      /* opens Lua */ 
	luaopen_base(L);                /* opens the basic library */ 
	luaopen_table(L);               /* opens the table library */ 
	luaopen_io(L);                  /* opens the I/O library */ 
	luaopen_string(L);              /* opens the string lib. */ 
	luaopen_math(L);                /* opens the math lib. */ 
	lua_pushcfunction(L,&open_db);
	lua_setglobal(L,"database");
	luaL_loadfile(L, file_name);
	lua_pcall(L,0,0,0);
	lua_close(L);
}

void Database_Private::get_ents_by_luafile(std::vector<Entity*> &ents)
{
	
	std::copy(g_ents_luafile_.begin(), g_ents_luafile_.end(), std::back_inserter(ents));
}


//namespace
}