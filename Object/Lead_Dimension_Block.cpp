// Lead_Dimension_Block.cpp: implementation of the Lead_Dimension_Block class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lead_Dimension_Block.h"
#include "Visitor.h"
#include "Database.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
//#include "Text_Dimension.h"
#include <algorithm>
#include <functional>
#include "File.h"
#include "Edit_Entity.h"
#include "Line.h"
//#include "..\DrawDll\reitrace.h"

#include "Global.h"
#include "geo2d.h"
#include "Lua_Tab.h"
#include "getrace.h"
#include "encode.h"

#include <cassert>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Lead_Dimension_Block,Dimension)
Lead_Dimension_Block::Lead_Dimension_Block()
:lead_(true)
//,outer_(true)
MCT_INIT2("Lead_Dimension_Block")
{
  show_change(true);
  offset_pos_ = 0;
  offset_floor_ = 0;
  offset_degree_ = 0;
  h_offset_way_ = 0;
  h_offset_num_ = 0;
	//base_ = 0;
  text_row_dis_ = 1;

}

void Lead_Dimension_Block::copy(const Lead_Dimension_Block& s, Lead_Dimension_Block& d)
{
  show_change(true);
  d.offset_pos_ = s.offset_pos_;
  d.offset_floor_ = s.offset_floor_;
  d.offset_degree_ = s.offset_degree_;
  d.text_row_dis_ = s.text_row_dis_;

	d.st_ = s.st_;
	d.lead_ = s.lead_;
	d.mem_rc_ = s.mem_rc_;
  d.list_.clear();
	dlhml::copy(s.list_, d.list_);
}

Lead_Dimension_Block::Lead_Dimension_Block(const Lead_Dimension_Block& rhs)
:Dimension(rhs)
MCT_INIT2("Lead_Dimension_Block")
{
	show_change(true);
	//dlhml::copy(rhs.list_, list_);
	copy(rhs, *this);
}

Lead_Dimension_Block& Lead_Dimension_Block::operator=(const Lead_Dimension_Block& rhs)
{
  show_change(true);
	Entity::operator =(rhs);
	if(this == &rhs){
		return *this;
	}
	copy(rhs, *this);
	//dlhml::copy(rhs.list_, list_);
	return *this;
}
//Entity * Lead_Dimension_Block::cloneme() const
//{
//	return new Lead_Dimension_Block(*this);
//}

//Lead_Dimension_Block& Lead_Dimension_Block::operator=(const Lead_Dimension_Block& rhs)
//{
//	Entity::operator =(rhs);
//	if(this == &rhs)
//		return *this;
//
//	base_ = static_cast<Lead_Dimension*>(rhs.base_->clone());
//	std::vector<Text_Dimension*>::const_iterator iter;
//	for(iter=rhs.list_.begin();iter!=rhs.list_.end();++iter){
//		Text_Dimension* dim = static_cast<Text_Dimension*>((*iter)->clone());
//		list_.push_back(dim);
//	}
//	std::vector<Line*>::const_iterator iter_ent;
//	for(iter_ent=rhs.out_frame_line_.begin();iter_ent!=rhs.out_frame_line_.end();++iter_ent){
//		Line* line = static_cast<Line*>((*iter_ent)->clone());
//		out_frame_line_.push_back(line);
//	}
//	for(int i=0;i< rhs.dim_content_.size();i++){
//		dim_content_.push_back(rhs.dim_content_[i]);
//	}
//
//	return *this;
//}
//	std::vector<LPTSTR>::iterator iter_str = rhs.begin_dim_content();
//	for(;iter_str != rhs.end_dim_content();++iter_str){
//		char * str = *iter_str;
//		dim_content_.push_back(str);
//	}
Lead_Dimension_Block::~Lead_Dimension_Block()
{
	clear();
}

//void Lead_Dimension_Block::closeme()
//{
//	delete this;
//}

void Lead_Dimension_Block::clear()
{
  show_change(true);
	std::for_each(list_.begin(),list_.end(),
		std::mem_fun<bool,Lead_Dimension>(&Lead_Dimension::close));
	list_.clear();
}
//Lead_Dimension_Block::~Lead_Dimension_Block()
//{
//	clear();
//}
//void Lead_Dimension_Block::clear()
//{
//	base_->close();
//	clear_text_dim();
//}



//void Lead_Dimension_Block::clear_text_dim()
//{
//	std::for_each(list_.begin(),list_.end(),
//		std::mem_fun<bool,Text_Dimension>(&Text_Dimension::close));
//	list_.clear();
//}
bool Lead_Dimension_Block::visit(Visitor& v)
{
	return v.Visit_Lead_Dimension_Block(*this);
}
//void Lead_Dimension_Block::push_dim_content(LPTSTR item)
//{
//	dim_content_.push_back(item);
//}
//void Lead_Dimension_Block::clear_dim_content()
//{
//	dim_content_.clear();
//}
//std::vector<LPTSTR>::iterator Lead_Dimension_Block::begin_dim_content()
//{
//	return dim_content_.begin();
//}
//std::vector<LPTSTR>::iterator Lead_Dimension_Block::end_dim_content()
//{
//	return dim_content_.end();
//}

void Lead_Dimension_Block::loadme(File& in)
{
  show_change(true);
	list_.clear();
	int num = 0;
	in >> num;
	for(int i=0;i<num;++i){
		Lead_Dimension* dim = Lead_Dimension::create_me();
		dim->load(in);
		list_.push_back(dim);
	}
}

void Lead_Dimension_Block::saveme(const File& out) const
{
	out << list_.size();
	std::vector<Lead_Dimension*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->save(out);
}
void Lead_Dimension_Block::save_luame(std::ofstream &out,int tab_num)
{
	Dimension::save_luame(out,tab_num);
	st_.save_lua(out,"st_",tab_num);
	ed_.save_lua(out,"ed_",tab_num);
	lua::bool_save(out,"lead_",lead_,tab_num);
	
	lua::begin_table(out,"list_",tab_num);
	std::vector<Lead_Dimension*>::const_iterator iter;
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

void Lead_Dimension_Block::open_luame(lua_State *l)  
{
	TRACE_OUT("Lead_Dimension_Block::open_luame() start\n");
	Dimension::open_luame(l);
	st_.open_lua(l,"st_");
	ed_.open_lua(l,"ed_");
	get_value(number,l,lead_,"lead_");

	
	Lua_Tab luatab(l,"list_");
	int index = lua_gettop(l);
	lua_pushnil(l);
	std::string kind;
	while(lua_next(l,index) != 0){
		get_value(string,l,kind,"kind");
		Entity *e = deal_entlists(l,kind);
		if(e)
			list_.push_back((Lead_Dimension *)e);
		lua_pop(l,1);
	}

	txt_change(true);
	TRACE_OUT("Lead_Dimension_Block::open_luame() end\n");
	
}
void Lead_Dimension_Block::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","LEAD_DIM_BLOCK");
	get_str_ent();
	get_str_dim();
	//////////////////////////
	st_.get_str_sub("st_");
	ed_.get_str_sub("ed_");
	rei_add_int(NULL,"lead_",lead_);

	int count = list_.size();
	rei_add_int(NULL,"leads_num",count);
	char field_name[MAX_REDIS_STR];
	for (int i = 0; i < count; i++){
			sprintf(field_name,"leads%d",i);
			list_[i]->get_str_sub(field_name);
	}
	rei_get_encode(out);
}

void Lead_Dimension_Block::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	set_from_str_dim();
	////////////////////////////////////////////////////////////
	st_.set_from_str_sub("st_");
	ed_.set_from_str_sub("ed_");
	lead_ = atoi(rei_get("lead_"));

	int count  = atoi(rei_get("leads_num"));
	char field_name[MAX_REDIS_STR];
	for (int i = 0; i < count; i++){
		Lead_Dimension *lead = Lead_Dimension::create_me();
			sprintf(field_name,"leads%d",i);
			lead->set_from_str_sub(field_name);
			list_.push_back(lead);
	}
	rei_quit();
}


void Lead_Dimension_Block::edit_propertyme(const Edit_Entity& edit)
{
  show_change(true);
//	edit.edit_lead_dim_block(*this);
}

//void Lead_Dimension_Block::drawme(Draw_Entity& out) const
//{
//	std::vector<Lead_Dimension*>::const_iterator iter;
//  for(iter=list_.begin();iter!=list_.end();++iter){
//		(*iter)->draw(out);
//  }
//}
//void Lead_Dimension_Block::xor_drawme(Draw_Entity& out) const
//{
//	std::vector<Lead_Dimension*>::const_iterator iter;
//  for(iter=list_.begin();iter!=list_.end();++iter){
//		(*iter)->xor_draw(out);
//  }
//}

//void Lead_Dimension_Block::drawme(Draw_Entity& out) const
//{
//	//这里需要改变牵引线的位置，使其不压标注名称的线
//	Point pt_new_end = get_txt_rect_pt_by_lead_start();
////	base_->end(pt_new_end );
//	base_->draw(out);
//	std::vector<Text_Dimension*>::const_iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter)
//		(*iter)->draw(out);
//	std::vector<Line*>::const_iterator iter_ent;
//	for(iter_ent=out_frame_line_.begin();iter_ent!=out_frame_line_.end();++iter_ent)
//		(*iter_ent)->draw(out);
//}
//Point Lead_Dimension_Block::get_txt_rect_pt_by_lead_start()const
//{
//	Rect lead_rect = base_->get_txt_rect();
//	std::vector<float> x_maxs,x_mins,y_maxs,y_mins;
//	x_maxs.push_back(lead_rect.xmax());
//	x_mins.push_back(lead_rect.xmin());
//	y_maxs.push_back(lead_rect.ymax());
//	y_mins.push_back(lead_rect.ymin());
//	
//	std::vector<Text_Dimension*>::const_iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		Rect rect = (*iter)->box2d();
//		x_maxs.push_back(rect.xmax());
//		x_mins.push_back(rect.xmin());
//		y_maxs.push_back(rect.ymax());
//		y_mins.push_back(rect.ymin());
//	}
//	std::vector<Line*>::const_iterator iter_ent;
//	for(iter_ent=out_frame_line_.begin();iter_ent!=out_frame_line_.end();++iter_ent){
//		//x
//		if((*iter_ent)->start().x>(*iter_ent)->end().x){
//			x_maxs.push_back((*iter_ent)->start().x);
//			x_mins.push_back((*iter_ent)->end().x);
//		}else{
//			x_mins.push_back((*iter_ent)->start().x);
//			x_maxs.push_back((*iter_ent)->end().x);
//		}
//		//y
//		if((*iter_ent)->start().y>(*iter_ent)->end().y){
//			y_maxs.push_back((*iter_ent)->start().y);
//			y_mins.push_back((*iter_ent)->end().y);
//		}else{
//			y_mins.push_back((*iter_ent)->start().y);
//			y_maxs.push_back((*iter_ent)->end().y);
//		}
//	}
//	Rect re_range;
//	std::vector<float>::iterator iter_max_x = std::max_element(x_maxs.begin(),x_maxs.end());
//	std::vector<float>::iterator iter_min_x = std::min_element(x_mins.begin(),x_mins.end());
//	std::vector<float>::iterator iter_max_y = std::max_element(y_maxs.begin(),y_maxs.end());
//	std::vector<float>::iterator iter_min_y = std::min_element(y_mins.begin(),y_mins.end());
//	re_range.xmax(*iter_max_x);
//	re_range.xmin(*iter_min_x);
//	re_range.ymax(*iter_max_y);
//	re_range.ymin(*iter_min_y);
//	Point rect_center,pt_lead_start,pt_lead_end;
//	pt_lead_start = base_->start();
//	pt_lead_end = base_->end();
//	rect_center.setdata((re_range.xmax()+re_range.xmin())/2.0f,(re_range.ymax()+re_range.ymin())/2.0f);
//	Point end_pt;
//	if(pt_lead_start.x>rect_center.x){
//		if(pt_lead_start.y>rect_center.y){
//			end_pt.setdata(re_range.xmax(),re_range.ymax());
//		}else{
//			end_pt.setdata(re_range.xmax(),re_range.ymin());
//		}
//	}else{
//		if(pt_lead_start.y>rect_center.y){
//			end_pt.setdata(re_range.xmin(),re_range.ymax());
//		}else{
//			end_pt.setdata(re_range.xmin(),re_range.ymin());
//		}
//	}
//	return end_pt;
//}
//void Lead_Dimension_Block::xor_drawme(Draw_Entity& out) const
//{
//	base_->xor_draw(out);
//	std::vector<Text_Dimension*>::const_iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter)
//		(*iter)->xor_draw(out);
//	std::vector<Line*>::const_iterator iter_ent;
//	for(iter_ent=out_frame_line_.begin();iter_ent!=out_frame_line_.end();++iter_ent)
//		(*iter_ent)->xor_draw(out);
//}

errorinfo Lead_Dimension_Block::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Lead_Dimension_Block::transformbyme(const Matrix& mat)
{
  show_change(true);
	std::vector<Lead_Dimension*>::iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter){
		(*iter)->transformby(mat);
  }
	mem_rc_.transformby(mat);
	st_.transformby(mat);
}
//void Lead_Dimension_Block::transformbyme(const Matrix& mat)
//{
//	REITRACE;
//	
//	base_->transformby(mat);
//	//它应该不随着lead_dim的移动而移动。有两种情况，整体移动时改构件矩形框要移动，
//	//当移动lead_dim_blk时不能移动该框
////	mem_rect_.transformby(mat);
//	std::vector<Text_Dimension*>::iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter)
//		(*iter)->transformby(mat);
//	std::vector<Line*>::const_iterator iter_ent;
//	for(iter_ent=out_frame_line_.begin();iter_ent!=out_frame_line_.end();++iter_ent)
//		(*iter_ent)->transformby(mat);
//}
//void Lead_Dimension_Block::transformby_mem_rect(const Matrix& mat)
//{
//	mem_rect_.transformby(mat);
//}
void Lead_Dimension_Block::drag_startme(const Matrix& mat)
{
}
void Lead_Dimension_Block::drag_endme(const Matrix& mat)
{
}

Entity* Lead_Dimension_Block::cloneme() const
{
	return new Lead_Dimension_Block(*this);
}
void Lead_Dimension_Block::closeme()
{
  show_change(true);
	delete this;
}
//bool Lead_Dimension_Block::intersectme(const Rect& rect) const
//{
//	std::vector<Lead_Dimension*>::const_iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		if((*iter)->intersect(rect))
//			return true;
//	}
//	return false;
//}
//bool Lead_Dimension_Block::intersectme(const Rect& rect) const
//{
//	if(base_->intersect(rect))
//		return true;
//	std::vector<Text_Dimension*>::const_iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		if((*iter)->intersect(rect))
//			return true;
//	}
//	std::vector<Line*>::const_iterator iter_ent;
//	for(iter_ent=out_frame_line_.begin();iter_ent!=out_frame_line_.end();++iter_ent){
//		if((*iter_ent)->intersect(rect))
//			return true;
//	}
//	return false;
//}

//bool Lead_Dimension_Block::envelopme(const Rect& rect) const
//{
//	std::vector<Lead_Dimension*>::const_iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		if(!(*iter)->envelop(rect))
//			return false;
//	}
//	return true;
//}
//bool Lead_Dimension_Block::envelopme(const Rect& rect) const
//{
//	if(!base_->envelop(rect))
//		return false;
//	std::vector<Text_Dimension*>::const_iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		if(!(*iter)->envelop(rect))
//			return false;
//	}
//	std::vector<Line*>::const_iterator iter_ent;
//	for(iter_ent=out_frame_line_.begin();iter_ent!=out_frame_line_.end();++iter_ent){
//		if((*iter_ent)->envelop(rect))
//			return true;
//	}
//	return true;
//}

Rect Lead_Dimension_Block::calc_box_dim()const
{
	Rect rc;
	dlhml::box2d<Lead_Dimension>(list_, rc);
	return rc;
}

//Rect Lead_Dimension_Block::calc_box_dim()const
//{
//	Rect box2d_;
//	box2d_.set_reverse_minmax();
//	std::vector<Lead_Dimension*>::const_iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		Rect temp = (*iter)->box2d();
//		box2d_.xmin(min(box2d_.xmin(),temp.xmin()));
//		box2d_.ymin(min(box2d_.ymin(),temp.ymin()));
//		box2d_.xmax(max(box2d_.xmax(),temp.xmax()));
//		box2d_.ymax(max(box2d_.ymax(),temp.ymax()));
//	}
//	return box2d_;
//}

//Rect Lead_Dimension_Block::calc_box2d() const
//{
//	Rect box2d;
//	Rect boxrc = calc_box_dim();
//	box2d.xmin(min(boxrc.xmin(),st_.x));
//	box2d.xmax(max(boxrc.xmax(),st_.x));
//	box2d.ymin(min(boxrc.ymin(),st_.y));
//	box2d.ymax(max(boxrc.ymax(),st_.y));
//	return box2d;
//}

void Lead_Dimension_Block::real_box_pt(std::vector<Point>& pts)const
{
	if(list_.empty()){
		return;
	}
	//NOOK 旋转平衡后，求大框4角坐标，在反向旋转回来，得到真实4角
	Lead_Dimension_Block * temp = static_cast<Lead_Dimension_Block*>(this->cloneme());
	Float rad = temp->front()->text_rotation();
	Matrix mat;
	mat.set_z_rotation_radian(-rad);
	temp->transformby(mat);
	
	Rect realrc = temp->calc_box_dim();

	mat.set_z_rotation_radian(rad);

	Point pt;
	pt.setdata(realrc.xmin(), realrc.ymin());
	pt.transformby(mat);
	pts.push_back(pt);
	pt.setdata(realrc.xmin(), realrc.ymax());
	pt.transformby(mat);
	pts.push_back(pt);
	pt.setdata(realrc.xmax(), realrc.ymax());
	pt.transformby(mat);
	pts.push_back(pt);
	pt.setdata(realrc.xmax(), realrc.ymin());
	pt.transformby(mat);
	pts.push_back(pt);

}

bool Lead_Dimension_Block::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
	return false;
}
bool Lead_Dimension_Block::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return false;
}
//void Lead_Dimension_Block::push_back(Text_Dimension* dim)
//{
//	list_.push_back(dim);
//}
//void Lead_Dimension_Block::erase(Text_Dimension* dim)
//{
//	std::vector<Text_Dimension*>::iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		if(*iter == dim){
//			list_.erase(iter);
//			dim->close();
//			break;
//		}
//	}
//}
//Text_Dimension* Lead_Dimension_Block::front()
//{
//	return list_.front();
//}
//Text_Dimension* Lead_Dimension_Block::back()
//{
//	return list_.back();
//}
//Text_Dimension* Lead_Dimension_Block::previous(const Text_Dimension* pos)
//{
//	std::vector<Text_Dimension*>::iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		if(*iter == pos)
//			return iter==list_.begin()?0:*(iter-1);
//	}
//	return 0;
//}
//Text_Dimension* Lead_Dimension_Block::next(const Text_Dimension* pos)
//{
//	std::vector<Text_Dimension*>::iterator iter;
//	for(iter=list_.begin();iter!=list_.end();++iter){
//		if(*iter == pos)
//			return iter+1==list_.end()?0:*(iter+1);
//	}
//	return 0;
//}
//int Lead_Dimension_Block::text_dim_size() const
//{
//	return list_.size();
//}

/////////////
//void Lead_Dimension_Block::push_back_ent(Line* line)
//{
//	out_frame_line_.push_back(line);
//}
//void Lead_Dimension_Block::erase_ent(Line* line)
//{
//	std::vector<Line*>::iterator iter;
//	for(iter=out_frame_line_.begin();iter!=out_frame_line_.end();++iter){
//		if(*iter == line){
//			out_frame_line_.erase(iter);
//			line->close();
//			break;
//		}
//	}
//}
//Line* Lead_Dimension_Block::front_ent()
//{
//	return out_frame_line_.front();
//}
//Line* Lead_Dimension_Block::back_ent()
//{
//	return out_frame_line_.back();
//}
//Line* Lead_Dimension_Block::next_ent(const Line* pos)
//{
//	std::vector<Line*>::iterator iter;
//	for(iter=out_frame_line_.begin();iter!=out_frame_line_.end();++iter){
//		if(*iter == pos)
//			return iter+1==out_frame_line_.end()?0:*(iter+1);
//	}
//	return 0;
//}
//void Lead_Dimension_Block::clear_out_line()
//{
//	std::for_each(out_frame_line_.begin(),out_frame_line_.end(),
//		std::mem_fun<bool,Line>(&Line::close));
//	out_frame_line_.clear();
//}
//bool Lead_Dimension_Block::if_out_rect()
//{
//	if(base_->start().envelop(mem_rect_))
//		return true;
//	return false;
//}

void Lead_Dimension_Block::push_back(Lead_Dimension * dim)
{
  show_change(true);
	dim->lead(false);
	list_.push_back(dim);
}
void Lead_Dimension_Block::remove(Lead_Dimension * dim)
{
  show_change(true);
	std::vector<Lead_Dimension*>::iterator pos = NULL;
	pos = std::find(list_.begin(), list_.end(), dim);
	if(pos != list_.end()){
		list_.erase(pos);
	}
}
void Lead_Dimension_Block::erase(Lead_Dimension* dim)
{
  show_change(true);
	std::vector<Lead_Dimension*>::iterator pos = NULL;
	pos = std::find(list_.begin(), list_.end(), dim);
	if(pos != list_.end()){
		list_.erase(pos);
		dim->close();
	}
}

Lead_Dimension * Lead_Dimension_Block:: front() const
{
	return list_.front();
}
Lead_Dimension * Lead_Dimension_Block:: back () const
{
	return list_.back();
}
Lead_Dimension * Lead_Dimension_Block:: prev(Lead_Dimension * dim) const
{
	std::vector<Lead_Dimension*>::const_iterator pos = NULL;
	pos = std::find(list_.begin(), list_.end(), dim);
	if(pos == list_.end()){
		return NULL;
	}
	if(pos == list_.begin()){
		return NULL;
	}
	--pos;
	return *pos;
}
Lead_Dimension * Lead_Dimension_Block::next(Lead_Dimension * dim) const
{
	std::vector<Lead_Dimension*>::const_iterator pos = NULL;
	pos = std::find(list_.begin(), list_.end(), dim);
	if(pos == list_.end()){
		return NULL;
	}
	++pos;
	if(pos == list_.end()){
		return NULL;
	}
	return *pos;
}

void  Lead_Dimension_Block::start(const Point& pt)
{
  st_=pt;
  if(!list_.empty()){
    list_.front()->start(pt);
  }
}
Point Lead_Dimension_Block::start()const
{
  return st_;
}

void Lead_Dimension_Block::end(const Point& pt)
{
  ed_ = pt;
}
Point Lead_Dimension_Block::end()const
{
  return ed_;
}


void Lead_Dimension_Block::dim_pos(const Point& ed)
{
	if(list_.empty()){
		return;
	}
	list_.front()->text_position(ed);
}

Point Lead_Dimension_Block::dim_pos()const
{
	if(list_.empty()){
		return st_;
	}
	return list_.front()->text_position();
}

void Lead_Dimension_Block::setdrag(const std::vector<Point>& pts, int index)
{
	if(list_.empty()){
		return;
	}
	assert(pts.size() > index);
  show_change(true);
	switch(index)
  {
	case 0:
		dim_pos(pts[index]);
		break;
	case 1:
		start(pts[index]);
		break;
	}
}
void Lead_Dimension_Block::getdrag(std::vector<Point>& pts) const
{
	if(list_.empty()){
		return;
	}
	pts.push_back(dim_pos());
	if(lead_){
		pts.push_back(st_);
	}
}

void Lead_Dimension_Block::get_block_line(std::vector<Entity*>& es)const
{
	if(list_.empty()){
		return;
	}

	std::vector<Point> pts;
	real_box_pt(pts);

	if(outer()){
		Line * ln1 = Line::create_me();
		ln1->setdata(pts[0], pts[1]);
		es.push_back(ln1);
		Line * ln2 = Line::create_me();
		ln2->setdata(pts[1], pts[2]);
		es.push_back(ln2);
		Line * ln3 = Line::create_me();
		ln3->setdata(pts[2], pts[3]);
		es.push_back(ln3);
		Line * ln4 = Line::create_me();
		ln4->setdata(pts[3], pts[0]);
		es.push_back(ln4);
	}

	////lead
	if(lead_){
		if(outer()){
			Line * ln = Line::create_me();
			int id = geo2d::min_dis(pts, st_);
			ln->setdata(st_, pts[id]);
			list_.front()->lead(false);
		}
		else{
			list_.front()->lead(true);
		}
	}

  ////NOOK block 本身的线型和颜色没有意义
// 	dlhml::color(es, color_index());
// 	dlhml::line_style(es, line_style());
}

void Lead_Dimension_Block::get_line(std::vector<Entity*>& es)const
{
}
void Lead_Dimension_Block::get_show(std::vector<Entity*>& es)const
{
  Lead_Dimension_Block * the = const_cast<Lead_Dimension_Block*>(this);
  the->update_txtpos(PW_UP);
	get_block_line(es);
	std::vector<Lead_Dimension*>::const_iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter){
		(*iter)->get_show(es);
  }
}

bool Lead_Dimension_Block::outer()const
{
  Dimension_Style ds;
  get_dim_style(ds);
  if(ds.txt_frame() == Dimension_Style::Txt_Frame::Only){
    return false;
  }
  return true;
}

void Lead_Dimension_Block::update_txtpos(POSWAY w)
{
  switch(w)
  {
    case PW_UP:
      update_txtpos_up();
      break;
  }
}

void Lead_Dimension_Block::update_txtpos_up()
{
  Point txtpt;  //  第一个的点
  int i=0;
  for(i=1; i<list_.size(); ++i){
    reset_txtpos_up(i);
  }
}

void Lead_Dimension_Block::reset_txtpos_up(int cur)
{
  assert(cur >= 0 && cur < list_.size());

  Text pretxt, curtxt;
  get_txt(cur-1, pretxt);
  get_txt(cur, curtxt);

  Float preh = get_txt_hei(pretxt);// pretxt.height();
  Float curh = get_txt_hei(curtxt);// curtxt.height();

  Float dis = (preh+curh)/2;

  Normal nor;
  radian_2_normal2d(list_[cur-1]->text_rotation()+dlhml::pi/2, nor);

  Point prept, curpt;
  prept = list_[cur-1]->text_position();
  curpt = prept.polarTo(dis, nor);
  list_[cur]->text_position(curpt);
}

void Lead_Dimension_Block::get_txt(int cur, Text& txt)
{
//   Dimension_Style ds;
//   list_[cur]->get_dim_style(ds);
//   ds.get_text(txt);
  list_[cur]->get_text_show(txt);
}

Float Lead_Dimension_Block::get_txt_hei(Text& txt)
{
  std::vector<Point> pts;
  txt.real_box_pt(pts);
  Float hei = pts[0].distanceto(pts[1]);
  return hei;
}

Float Lead_Dimension_Block::get_dim_hei(int cur)
{
  return 0;
}

//  干涉后参与偏移部分的外框
Rect Lead_Dimension_Block::offset_box()
{
  return calc_box_dim();
}   
void Lead_Dimension_Block::offset_pp()
{
//  assert(offset_pos_ >= -1 && offset_pos_ <= 1);

  //0,-1,1,-2,2,-3,3
  if(offset_pos_ < 0){
    offset_pos_ = -offset_pos_;
  }else{
    offset_pos_ = -offset_pos_;
    offset_pos_ --;
  }
  if(offset_pos_ > 5){
    offset_pos_ = 0;
    offset_floor_++;
  }
//   switch(offset_pos_){
//   case 0:
//     offset_pos_ = -1;
//     break;
//   case -1:
//     offset_pos_ = 1;
//     break;
//   case 1:
//     offset_pos_ = 0;
//     offset_floor_ ++;
//     break;
//   }
  offset_text();
}

void Lead_Dimension_Block::offset_degree(Float f)
{
  offset_degree_ = f;
}

void Lead_Dimension_Block::h_offset_way(int i)
{
  h_offset_way_ = i;
}

void Lead_Dimension_Block::h_offset_num(int i)
{
  h_offset_num_ = i;
}

void Lead_Dimension_Block::offset_text()
{
  if(list_.empty()){
    return;
  }
  Rect rc = offset_box();
  Float v_dis = list_.front()->text_gdi_height()+text_row_dis_;////行间距
  Float h_dis = v_dis;


  Point pos = end();
  Normal nor;
  dlhml::degree_2_normal2d(offset_degree_, nor);
  pos = pos.polarTo(v_dis*offset_floor_, nor);
  dlhml::degree_2_normal2d(offset_degree_-90, nor);
  pos = pos.polarTo(h_dis*offset_pos_, nor);  //0,-1,1
  dim_pos(pos);
  update_txtpos(Lead_Dimension_Block::POSWAY::PW_UP);

}

//  起始楼层
int Lead_Dimension_Block::offset_floor()
{
  return offset_floor_;
}

//  占用层数
int Lead_Dimension_Block::span_floor()
{
  return list_.size();
}

//  楼层数
int Lead_Dimension_Block::floor_count()
{
  //PW_UP
  Float txt_up_deg = dlhml::radian_2_degree(text_rotation() + dlhml::pi/2);
  dlhml::std_degree(offset_degree_);
  if(dlhml::EquFloat(txt_up_deg, offset_degree_)){
    return offset_floor()+span_floor();
  }else{
    Float txt_deg = dlhml::radian_2_degree(text_rotation());
    Float angle_deg = offset_degree_ - txt_deg;
    dlhml::std_degree((angle_deg));
    if(dlhml::EquFloat(angle_deg, 0) || dlhml::EquFloat(angle_deg, 180)){
      Rect rc = offset_box();
      Float span = rc.width()/(text_gdi_height()+text_row_dis_)/2;
      return offset_floor()+(int)span+1;
    }
  }
  return offset_floor()+1;
}

}//namespace




