
#include "stdafx.h"
#include "Ln_Dim_Block.h"
#include "Ln_Dim.h"
#include <algorithm>
#include <functional>
#include "File.h"
#include "Line.h"
#include "Entity_Calculate.h"
#include "Database.h"
#include "Edit_Entity.h"
#include "Normal.h"
#include <cassert>
#include "visitor.h"

#include "Dimension_Style.h"

#include "Matrix_d.h"
#include "Global.h"
#include "Lua_Tab.h"
#include "getrace.h"
#include "encode.h"
//#include "..\DrawDll\reitrace.h"

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Ln_Dim_Block,Entity)
Ln_Dim_Block::Ln_Dim_Block()
MCT_INIT1("Ln_Dim_Block")
{
  dim_count_ = 0;
  dim_mode_ = PILEUP_DIM;
	dim_line_radian_ = 0;
  show0_ = true;
  text_row_dis_ = 0;   //  行间距

}
Ln_Dim_Block::Ln_Dim_Block(const Ln_Dim_Block& rhs)
:Entity(rhs)
MCT_INIT2("Ln_Dim_Block")
{
  dim_count_ = rhs.dim_count_;
  show0_=rhs.show0_;
  text_row_dis_ = rhs.text_row_dis_;
  dim_mode_=rhs.dim_mode_;
	dim_line_radian_ = rhs.dim_line_radian_;
  list_.clear();
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=rhs.list_.begin();iter!=rhs.list_.end();++iter){
		Ln_Dim* dim = static_cast<Ln_Dim*>((*iter)->clone());
		list_.push_back(dim);
	}
}
Ln_Dim_Block& Ln_Dim_Block::operator=(const Ln_Dim_Block& rhs)
{
	Entity::operator =(rhs);
	if(this == &rhs)
		return *this;
  dim_count_ = rhs.dim_count_;
  show0_=rhs.show0_;
  text_row_dis_ = rhs.text_row_dis_;
  dim_mode_=rhs.dim_mode_;
	dim_line_radian_ = rhs.dim_line_radian_;
  list_.clear();
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=rhs.list_.begin();iter!=rhs.list_.end();++iter){
		Ln_Dim* dim = static_cast<Ln_Dim*>((*iter)->clone());
		list_.push_back(dim);
	}
	return *this;
}
Ln_Dim_Block::~Ln_Dim_Block()
{
	clear();
}
void Ln_Dim_Block::clear()
{
	std::for_each(list_.begin(),list_.end(),
		std::mem_fun<bool,Ln_Dim>(&Ln_Dim::close));
	list_.clear();
}
bool Ln_Dim_Block::visit(Visitor& v)
{
	return v.Visit_Ln_Dim_Block(*this);
}
void Ln_Dim_Block::loadme(File& in)
{
	list_.clear();
  in >> show0_;
  in >> dim_mode_;
	in >> dim_line_radian_;
	int num = 0;
	in >> num;
	for(int i=0;i<num;++i){
		Ln_Dim* dim = Ln_Dim::create_me();
		dim->load(in);
		list_.push_back(dim);
	}
}
void Ln_Dim_Block::saveme(const File& out) const
{
  out << show0_;
  out << dim_mode_;
	out << dim_line_radian_;
	out << list_.size();
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->save(out);
}
void Ln_Dim_Block::save_luame(std::ofstream &out,int tab_num)
{
	lua::bool_save(out,"show0_",show0_,tab_num);
	lua::int_save(out,"dim_mode_",dim_mode_,tab_num);
	lua::double_save(out,"dim_line_radian_",dim_line_radian_,tab_num);

	lua::begin_table(out,"list_",tab_num);
	std::vector<Ln_Dim*>::const_iterator iter;
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

void Ln_Dim_Block::open_luame(lua_State *l)  
{
	TRACE_OUT("Ln_Dim_Block::open_luame() start\n");
	get_value(number,l,show0_,"show0_");
	get_value(number,l,dim_mode_,"dim_mode_");
	get_value(number,l,dim_line_radian_,"dim_line_radian_");
	
	Lua_Tab luatab(l,"list_");
	int index = lua_gettop(l);
	lua_pushnil(l);
	std::string kind;
	while(lua_next(l,index) != 0){
		get_value(string,l,kind,"kind");
		Entity *e = deal_entlists(l,kind);
		if(e)
			list_.push_back((Ln_Dim *)e);
		lua_pop(l,1);
	}
	
	TRACE_OUT("Ln_Dim_Block::open_luame() end\n");


}

void Ln_Dim_Block::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","OBJ_LN_DIM_BLK");
	get_str_ent();
	//////////////////////////
	rei_add_int(NULL,"show0_",show0_);
	rei_add_int(NULL,"dim_mode_",dim_mode_);
	rei_add_float(NULL,"dim_line_radian_",dim_line_radian_);

	int count = list_.size();
	rei_add_int(NULL,"lndims_num",count);
	char field_name[MAX_REDIS_STR];
	for (int i = 0; i < count; i++){
			sprintf(field_name,"lndims_num%d",i);
			list_[i]->get_str_sub(field_name);
	}
	rei_get_encode(out);
}

void Ln_Dim_Block::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	////////////////////////////////////////////////////////////
	show0_ = atoi(rei_get("show0_"));
	dim_mode_ = atoi(rei_get("dim_mode_"));
	dim_line_radian_ = atof(rei_get("dim_line_radian_"));

	int count  = atoi(rei_get("lndims_num"));
	char field_name[MAX_REDIS_STR];
	for (int i = 0; i < count; i++){
		Ln_Dim *lead = Ln_Dim::create_me();
			sprintf(field_name,"lndims_num%d",i);
			lead->set_from_str_sub(field_name);
			list_.push_back(lead);
	}
	rei_quit();
}


void Ln_Dim_Block::edit_propertyme(const Edit_Entity& edit)
{
//	edit.edit_four_pt_dim_block(*this);
}
//  out.draw_ln_dim_block(*this);
//  int i=0;
//  for(i=0; i<list_.size(); i++){
//#ifdef _DEBUG
//    list_[i]->s_circle_->radius(i*2+2);
//    list_[i]->s_circle_->radius(i*2+2);
//#endif
//    list_[i]->draw(out);
//  }
void Ln_Dim_Block::drawme(Draw_Entity& out) const
{
	std::vector<Ln_Dim*>::const_iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter){
		(*iter)->draw(out);
  }
}
//  out.xor_draw(*this);
void Ln_Dim_Block::xor_drawme(Draw_Entity& out) const
{
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->xor_draw(out);
}
errorinfo Ln_Dim_Block::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}
void Ln_Dim_Block::transformbyme(const Matrix& mat)
{
	std::vector<Ln_Dim*>::iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter){
		(*iter)->transformby(mat);
  }
  dlhml::transformby2d_radian(mat, dim_line_radian_);
}

//BET
//************************************************************************
//                    matrix's type                                                                        
//************************************************************************
//void Ln_Dim_Block::transformbyme(const Matrix& mat)
//{
//	REITRACE;
//	std::vector<Ln_Dim*>::iterator iter;
//  for(iter=list_.begin();iter!=list_.end();++iter){
//		(*iter)->transformby(mat);
//  }
//
//  if(mat.mat_type()==ZRAOTA_MAT){
//    dim_line_radian_ += mat.rota_radian();
//    std_radian(dim_line_radian_);
//  }
//}
//TER

void Ln_Dim_Block::drag_startme(const Matrix& mat)
{
}
void Ln_Dim_Block::drag_endme(const Matrix& mat)
{
}
Entity* Ln_Dim_Block::cloneme() const
{
	return new Ln_Dim_Block(*this);
}
void Ln_Dim_Block::closeme()
{
	delete this;
}
bool Ln_Dim_Block::intersectme(const Rect& rect) const
{
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if((*iter)->intersect(rect))
			return true;
	}
	return false;
}
bool Ln_Dim_Block::envelopme(const Rect& rect) const
{
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(!(*iter)->envelop(rect))
			return false;
	}
	return true;
}
Rect Ln_Dim_Block::calc_box2d() const
{
	Rect box2d_;
	box2d_.set_reverse_minmax();
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp = (*iter)->box2d();
		box2d_.xmin(min(box2d_.xmin(),temp.xmin()));
		box2d_.ymin(min(box2d_.ymin(),temp.ymin()));
		box2d_.xmax(max(box2d_.xmax(),temp.xmax()));
		box2d_.ymax(max(box2d_.ymax(),temp.ymax()));
	}
	return box2d_;
}
bool Ln_Dim_Block::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
	return false;
}
bool Ln_Dim_Block::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return false;
}
void Ln_Dim_Block::insert(const Ln_Dim* pos,Ln_Dim* dim)
{
  if(!pos){
    list_.push_back(dim);
    return;
  }
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(*iter == pos){
			list_.insert(iter,dim);
      dim_count(true);
			break;
		}
	}
}
void Ln_Dim_Block::push_back(Ln_Dim* dim)
{
	list_.push_back(dim);
  dim_count(true);
}
void Ln_Dim_Block::erase(Ln_Dim* dim)
{
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(*iter == dim){
			list_.erase(iter);
			dim->close();
      dim_count(false);
			break;
		}
	}
}
Ln_Dim* Ln_Dim_Block::front()
{
	return list_.front();
}
Ln_Dim* Ln_Dim_Block::back()
{
	return list_.back();
}
Ln_Dim* Ln_Dim_Block::last()
{
  std::vector<Ln_Dim*>::iterator iter = list_.end();
  iter--;
  return* iter;
}
Ln_Dim* Ln_Dim_Block::previous(const Ln_Dim* pos)
{
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(*iter == pos)
			return iter==list_.begin()?0:*(iter-1);
	}
	return 0;
}
Ln_Dim* Ln_Dim_Block::next(const Ln_Dim* pos)
{
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(*iter == pos)
			return iter+1==list_.end()?0:*(iter+1);
	}
	return 0;
}
Ln_Dim* Ln_Dim_Block::first_same_angle() const
{
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(EquFloat((*iter)->dim_line_radian(),dim_line_radian_))
			return *iter;
	}
	return 0;
}
Ln_Dim* Ln_Dim_Block::get_insert_pos(const Point& pt)
{
	if(list_.size()==0)
		return 0;
	if(!pt_in_block_range(pt))
		return front_or_back_point(pt)?front():0;
	Ln_Dim* temp = select_from_dimline(pt);
	assert(temp);
	return EquFloat(temp->dim_line_radian(),dim_line_radian_)?temp:next(temp);
}
Ln_Dim* Ln_Dim_Block::select_from_dimline(const Point& pt)
{
	std::vector<Ln_Dim*>::iterator zero;
	for(zero=list_.begin();zero!=list_.end();++zero){
		if(EquFloat((*zero)->dim_line_radian(),dim_line_radian_))
			break;
	}
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=zero;iter!=list_.end();++iter){
		if((*iter)->pt_in_range(pt))
			return *iter;
	}
	Ln_Dim* temp = 0;
	for(iter=list_.begin();iter!=zero;++iter){
		if((*iter)->pt_in_range(pt))
			temp = *iter;
	}
	return temp;  
}
bool Ln_Dim_Block::is_in_beeline_by_entendline(const Rect& rc)
{
  switch(dim_mode_)
  {
  case PILEUP_DIM:
    break;
  case CLOSED_DIM:
    //NOOK
    break;
  }
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line oln,eln,odim,edim;
		(*iter)->get_o_lines(oln,odim);
		(*iter)->get_e_lines(eln,edim);
		Entity_Calculate calc;
		if(calc.rect_insect_beeline(rc,oln) || calc.rect_insect_beeline(rc,eln)){
      return true;
		}
  }
  return false;
}
bool Ln_Dim_Block::is_in_beeline_by_entendline(const Point& pt)
{
  switch(dim_mode_)
  {
  case PILEUP_DIM:
    break;
  case CLOSED_DIM:
    //NOOK
    break;
  }
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line oln,eln,odim,edim;
		(*iter)->get_o_lines(oln,odim);
		(*iter)->get_e_lines(eln,edim);
		if(oln.is_in_line(pt) || eln.is_in_line(pt)){
      return true;
		}
  }
  return false;
}
//Ln_Dim* Ln_Dim_Block::select(int& pos,const Rect& rc)
//{
//  if(mode() == PILEUP_DIM){
//	  std::vector<Ln_Dim*>::iterator iter;
//	  for(iter=list_.begin();iter!=list_.end();++iter){
//		  Entity_Calculate calc;
//		  Line oln,sln,eln,odm,edm;
//		  (*iter)->get_o_lines(oln,odm);
//		  if(calc.linesegment_insect_rect(odm,rc)){
//			  pos = 1;
//			  return *iter;
//		  }
//		  (*iter)->get_e_lines(eln,edm);
//		  if(calc.linesegment_insect_rect(edm,rc)){
//			  pos = 2;
//			  return *iter;
//		  }
//		  Text text;
//		  (*iter)->get_text_show(text);
//		  if(text.intersect(rc)){
//			  pos = 1;
//			  return *iter;
//		  }
//		  (*iter)->get_text2_show(text);
//		  if(text.intersect(rc)){
//			  pos = 2;
//			  return *iter;
//		  }
//		  if(calc.linesegment_insect_rect(oln,rc)){
//			  pos = 1;
//			  return *iter;
//		  }
//		  if(calc.linesegment_insect_rect(eln,rc)){
//			  pos = 2;
//			  return *iter;
//		  }
//	  }
//  }
//	return 0;
//}
Ln_Dim* Ln_Dim_Block::select_from_dimline(int& pos,const Rect& rc)
{
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Entity_Calculate calc;
		Line oln,eln,odm,edm;
		(*iter)->get_o_lines(oln,odm);
		if(calc.linesegment_insect_rect(odm,rc)){
			pos = 1;
			return *iter;
		}
		(*iter)->get_e_lines(eln,edm);
		if(calc.linesegment_insect_rect(edm,rc)){
			pos = 2;
			return *iter;
		}
	}
	return 0;
}
Ln_Dim* Ln_Dim_Block::select_from_text(int& pos,const Rect& rc)
{
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Text text;
		(*iter)->get_text_show(text);
		if(text.intersect(rc)||rc.envelop(text.box2d())){
			pos = 1;
			return *iter;
		}
		(*iter)->get_text2_show(text);
		if(text.intersect(rc)||rc.envelop(text.box2d())){
			pos = 2;
			return *iter;
		}
		(*iter)->get_text3_show(text);
		if(text.intersect(rc)||rc.envelop(text.box2d())){
			pos = 3;
			return *iter;
		}
	}
	return 0;
}
Ln_Dim* Ln_Dim_Block::select_from_extendline(int& pos,const Rect& rc)
{
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line oln,eln,odm,edm;
		(*iter)->get_o_lines(oln,odm);
		(*iter)->get_e_lines(eln,edm);
		Entity_Calculate calc;
		if(calc.linesegment_insect_rect(oln,rc)){
			pos = 1;
			return *iter;
		}
		if(calc.linesegment_insect_rect(eln,rc)){
			pos = 2;
			return *iter;
		}
	}
	return 0;
}
Ln_Dim* Ln_Dim_Block::select_from_extendline(int& pos,const Point& pt)
{
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line oln,eln,odm,edm;
		(*iter)->get_o_lines(oln,odm);
		(*iter)->get_e_lines(eln,edm);
		Entity_Calculate calc;
		if(oln.is_in_line(pt)){
			pos = 1;
			return *iter;
		}
		if(eln.is_in_line(pt)){
			pos = 2;
			return *iter;
		}
	}
	return 0;
}

void Ln_Dim_Block::offset_dimlines(const Normal& off_nor,Float off)
{
  box_change(true);
  Normal nor = off_nor;
  ext_line_normal(nor);

  std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Point pt = (*iter)->odm();
		pt = pt.polarTo(off,nor);
		(*iter)->odm(pt);
		pt = (*iter)->text_position();
		pt = pt.polarTo(off,nor);
		(*iter)->text_position(pt);

		pt = (*iter)->edm();
		pt = pt.polarTo(off,nor);
		(*iter)->edm(pt);
		pt = (*iter)->text2_position();
		pt = pt.polarTo(off,nor);
		(*iter)->text2_position(pt);

//		pt = (*iter)->text3_position();
//		pt = pt.polarTo(off,nor);
//		(*iter)->text3_position(pt);
	}
}
void Ln_Dim_Block::ext_line_normal(Normal& nor)
{
  Ln_Dim * front_dim = list_.front();
  if(!front_dim){
    return;
  }
  Line oexln,odmln;
  front_dim->get_o_lines(oexln, odmln);
  Point st,ed;
  st  = oexln.start();
  ed  = oexln.start();
  ed += nor;
  Point ed_oex = oexln.perpendicular(ed);
  nor.set_data(st,ed_oex);
}
void Ln_Dim_Block::offset_dimlines(const Normal& off_nor)
{
  box_change(true);
  Normal nor = off_nor;
  ext_line_normal(nor);

	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
    if(!(*iter)){
      continue;
    }
		Point pt = (*iter)->odm();
    pt += nor;
		(*iter)->odm(pt);
		pt = (*iter)->text_position();
    pt += nor;
		(*iter)->text_position(pt);

		pt = (*iter)->edm();
    pt += nor;
		(*iter)->edm(pt);
		pt = (*iter)->text2_position();
    pt += nor;
		(*iter)->text2_position(pt);

//		pt = (*iter)->text3_position();
//    pt += nor;
//		(*iter)->text3_position(pt);
	}
}
void Ln_Dim_Block::layout_dimlines(const Point& pos)
{
  box_change(true);
	std::vector<Ln_Dim*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->align_dim_lines(pos);
}
void Ln_Dim_Block::layout_base(const Point& pos)
{
  box_change(true);
	std::vector<Ln_Dim*>::iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter){
		(*iter)->align_base(pos);
  }
}
bool Ln_Dim_Block::pt_in_block_range(const Point& pt)
{
	std::vector<Ln_Dim*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if((*iter)->pt_in_range(pt))
			break;
	}
	return iter != list_.end();
}
bool Ln_Dim_Block::front_or_back_point(const Point& pt)
{
	assert(!pt_in_block_range(pt));
	Ln_Dim* frontdim = front();
  Line foex, fodm, feex, fedm;
  frontdim->get_o_lines(foex,fodm);
  frontdim->get_e_lines(feex,fedm);
	Line st=EquFloat(frontdim->dim_line_radian(),dim_line_radian_)?foex:feex;
	Ln_Dim* backdim = back();
  Line boex, bodm, beex, bedm;
  frontdim->get_o_lines(boex,bodm);
  frontdim->get_e_lines(beex,bedm);
	Line ed=EquFloat(backdim->dim_line_radian(),dim_line_radian_)?beex:bodm;
	return st.distanceto2d(pt) < ed.distanceto2d(pt);
//bet 2009.06.17
//lm
//	assert(!pt_in_block_range(pt));
//	Ln_Dim* frontdim = front();
//	Point st=EquFloat(frontdim->dim_line_radian(),dim_line_radian_)?
//		frontdim->opt():frontdim->ept();
//	Ln_Dim* backdim = back();
//	Point ed=EquFloat(backdim->dim_line_radian(),dim_line_radian_)?
//		backdim->ept():backdim->opt();
//	return pt.distanceto2d(st) < pt.distanceto2d(ed);
//ter 2009.06.17
}
int Ln_Dim_Block::size() const
{
	return list_.size();
}

void Ln_Dim_Block::selected(bool sel)
{
  Entity::selected(sel);
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->selected(sel);
  }
}
bool Ln_Dim_Block::selected() const
{
  return Entity::selected();
}

void Ln_Dim_Block::dim_style(std::string style_name)
{
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    //(*it)->selected(sel);
    (*it)->dim_style_name(style_name);
  }
}
std::string Ln_Dim_Block::dim_style() const
{
  if(list_.empty()){
    return "";
  }
  //std::vector<Ln_Dim*>::iterator it = list_.begin();
  return (*list_.begin())->dim_style_name();
}

void Ln_Dim_Block::line_style(std::string style)
{
  Entity::line_style(style);
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->line_style(style);
  }
}
std::string Ln_Dim_Block::line_style() const		
{
  return Entity::line_style();
}
void Ln_Dim_Block::color(COLORREF rgb)	
{
  Entity::color(rgb);
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->color(rgb);
  }
}
COLORREF	Ln_Dim_Block::color() const				
{
  return Entity::color();
}

void Ln_Dim_Block::mode(DIM_MODE m)
{
  box_change(true);
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->mode(m);
  }
}
void	Ln_Dim_Block::color_index(int index)
{
	Entity::color_index(index);	
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->color_index(index);
  }
}
int	Ln_Dim_Block::color_index() const		
{
	if(list_.empty()){
		return Entity::color_index();
	}
	return list_.front()->color_index();
}

DIM_MODE Ln_Dim_Block::mode()const
{
  if(list_.empty()){
    return PILEUP_DIM;
  }
  else{
    return list_.front()->mode();
  }
}

void Ln_Dim_Block::recal_show0()
{
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->show0(false);
  }
  if(!list_.empty()){
    last()->show0(show0_);
  }
}
void Ln_Dim_Block::show0(bool b)
{
  show0_ = b;
  recal_show0();
}
bool Ln_Dim_Block::show0()
{
  if(list_.empty()){
    return false;
  }
  return show0_;
//  if(!list_.empty()){
//    return last()->show0();
//  }
//  else{
//    return false;
//  }
}
//bool Ln_Dim_Block::is_0_superposition(const Ln_Dim_Block& rhs)const
//{
//	if(this == rhs){
//	  return false;
//	}
//
//	Line ln1 = TOOLS::LineExt1FromDim(pdim_block_1->front());
//	Line ln2 = TOOLS::LineExt1FromDim(pdim_block_2->front());
//	//  两条直线是否重合
//	if(TOOLS::is_line_superpositon(ln1, ln2)){
//	  return true;
//	}else{
//	  return false;
//	}
//}

void Ln_Dim_Block::setdrag_pileup(const std::vector<Point>& pts, int index)
{
  box_change(true);

  int ptsize = pts.size();
  int dimsize = list_.size();
  assert(ptsize >= dimsize);
  assert(index>=0);
  assert(index < ptsize);
  Point pt = pts[index];

  Point oldpt, newpt;
  Line exln, dmln;
  if(show0_ && index == dimsize){
    oldpt = list_.back()->text_position();
    list_.back()->odm(pt);
    list_.back()->get_o_lines(exln, dmln);
    newpt = dmln.middle();
    list_.back()->text_position(newpt);
  }else{
    oldpt = list_[index]->text_position();
    list_[index]->edm(pt);
    list_[index]->get_e_lines(exln, dmln);
    newpt = dmln.middle();
    list_[index]->text2_position(newpt);
  }
}


void Ln_Dim_Block::getdrag_pileup(std::vector<Point>& pts) const
{
  int dimsize = list_.size();
  int i=0;

  Point pt;
  for(i=0; i<dimsize; ++i){
    pt = list_[i]->text2_position();
    pts.push_back(pt);
  }
  if(show0_){
    pt = list_.back()->text_position();
    pts.push_back(pt);
  }
}

void Ln_Dim_Block::setdrag_closed(const std::vector<Point>& pts, int index)
{
  box_change(true);

  int ptsize = pts.size();
  int dimsize = list_.size();
  assert(ptsize == dimsize);
  assert(index>=0);
  assert(index < ptsize);
  Point pt = pts[index];
  list_[index]->text_position(pt);
}


void Ln_Dim_Block::getdrag_closed(std::vector<Point>& pts) const
{
  if(list_.empty()){
    return;
  }
  const Ln_Dim* f_dim = list_.front();
  const Ln_Dim* b_dim = list_.back();
  if(!f_dim || !b_dim){
    return;
  }
  
  int dimsize = list_.size();
  int i=0;
  for(i=0; i<dimsize; ++i){
    Point pt = list_[i]->text_position();
    pts.push_back(pt);
  }
}

void Ln_Dim_Block::setdrag(const std::vector<Point>& pts, int index)
{
  box_change(true);
  if(list_.empty() || pts.empty() || !list_[0] || index < 0 || index >= pts.size()){
    return;
  }
  Ln_Dim* f_dim = list_.front();
  Ln_Dim* b_dim = list_.back();
  if(!f_dim || !b_dim){
    return;
  }
  if(mode() == CLOSED_DIM){
    setdrag_closed(pts, index);
  }else if(mode() == PILEUP_DIM){
    setdrag_pileup(pts, index);
  }
}

void Ln_Dim_Block::getdrag(std::vector<Point>& pts) const
{  
  if(list_.empty()){
    return;
  }
  const Ln_Dim* f_dim = list_.front();
  const Ln_Dim* b_dim = list_.back();
  if(!f_dim || !b_dim){
    return;
  }

  if(mode() == CLOSED_DIM){
    getdrag_closed(pts);
  }else if(mode() == PILEUP_DIM){
    getdrag_pileup(pts);
  }
}

// void Ln_Dim_Block::setdrag(const std::vector<Point>& pts, int index)
// {
//   box_change(true);
//   if(list_.empty() || pts.empty() || !list_[0] || index < 0 || index >= pts.size()){
//     return;
//   }
//   Ln_Dim* f_dim = list_.front();
//   Ln_Dim* b_dim = list_.back();
//   if(!f_dim || !b_dim){
//     return;
//   }
//   int list_size = list_.size();
//   int pts_count = pts  .size();
//   if(pts_count<list_size){
//     return;
//   }
//   Line  sexln, exln,dmln;
//   Point old_pt, new_pt, txt_pt;
//   if(index < list_size){
//     assert(list_[index]);
//     list_[index]->get_e_lines(exln,dmln);
//     old_pt = dmln.middle();
//     list_[index]->edm(pts[index]);
//     list_[index]->get_e_lines(exln,dmln);
//     new_pt = dmln.middle();
//     
//     if(mode() == PILEUP_DIM){
//       txt_pt = list_[index]->text2_position();
//       txt_pt = txt_pt + new_pt - old_pt;
//       list_[index]->text2_position(txt_pt);
//     }
//     else if(mode() == CLOSED_DIM){
//       txt_pt = list_[index]->text_position();
//       txt_pt = txt_pt + new_pt - old_pt;
//       list_[index]->text_position(txt_pt);
//     }
//   }
//   else{
//     if(mode() == PILEUP_DIM){
//       if(show0_){
//         f_dim->get_o_lines(exln,dmln);
//         old_pt = dmln.middle();
//         odm(pts[index]);
//         f_dim->get_o_lines(exln,dmln);
//         new_pt = dmln.middle();
//         txt_pt = f_dim->text_position();
//         txt_pt = txt_pt + new_pt - old_pt;
//         text_position(txt_pt);
//       }
//     }
//     else if(mode() == CLOSED_DIM){
// ////可以拖动全部文字
//       list_[index-list_size]->text_position(pts[index]);
// ////只能拖动两端文字
// //      if(index == list_size){
// //        f_dim->get_s_lines(sexln,exln,dmln);
// //        txt_pt=dmln.perpendicular(pts[index]);
// //        f_dim->text_position(txt_pt);
// //      }else{
// //        f_dim->get_s_lines(sexln,exln,dmln);
// //        txt_pt=dmln.perpendicular(pts[index]);
// //        b_dim->text_position(txt_pt);
// //      }
//     }
//   }
// 
// 
// //  int i=0;
// //  Line  oexln,sexln,eexln,odmln,edmln;
// //  Point dm_pt, txtpt;
// //  if(mode() == PILEUP_DIM){
// //    ////累加标注只能拖拽标注点，不能拖拽文字点
// //    ////需要拖拽0点
// //    if(show0_){
// //      if(index==1){
// //        for(i=0; i<list_.size(); i++){
// //          list_[i]->odm(pts[0]);
// //          list_[i]->get_o_lines(oexln,odmln);
// //          txtpt=odmln.middle();
// //          list_[i]->text_position(txtpt);
// //        }
// //      }
// //      else{
// //        i=index-1;
// //        if(i<pts.size()-1&&i<list_.size()){
// //          list_[i]->edm(pts[i+1]);
// //          list_[i]->get_e_lines(eexln,edmln);
// //          txtpt=edmln.middle();
// //          list_[i]->text2_position(txtpt);
// //        }
// //      }
// //    }
// //    else{
// //      i=index;
// //      if(i<pts.size()&&i<list_.size()){
// //        list_[i]->edm(pts[i]);
// //        list_[i]->get_e_lines(eexln,edmln);
// //        txtpt=edmln.middle();
// //        list_[i]->text2_position(txtpt);
// //      }
// //    }
// //  }
// //  else if(mode() == CLOSED_DIM){
// //    ////累加标注能拖拽标注点，也能拖拽文字点
// //    ////不需要拖拽0点
// //
// //    ////单个标注
// //    if(list_.size() == 1){
// //      if(index == 1){
// //        i=0;
// //        if(i<list_.size()&&index<pts.size()){
// //          list_[i]->get_s_lines(sexln,eexln,edmln);
// //          Point old_edm = edmln.middle();
// //          list_[i]->edm(pts[index]);
// //          list_[i]->get_s_lines(sexln,eexln,edmln);
// //          Point new_edm = edmln.middle();
// //          txtpt = list_[i]->text_position();
// //          txtpt = txtpt+new_edm-old_edm;
// //          list_[i]->text_position(txtpt);
// //        }
// //      }else if(index==0){
// //        i=0;
// //        if(i<list_.size()&&index<pts.size()){
// //          list_[i]->get_s_lines(sexln,eexln,edmln);
// //          txtpt = edmln.perpendicular(pts[index]);
// //          list_[i]->text_position(txtpt);
// //        }
// //      }
// //    }
// //    ////多个标注
// //    if(list_.size() > 1){
// //      if(index >= 2){
// //        i=index-2; //
// //        if(i<list_.size()&&index<pts.size()){
// //          list_[i]->get_s_lines(sexln,eexln,edmln);
// //          Point old_edm = edmln.middle();
// //          list_[i]->edm(pts[index]);
// //          list_[i]->get_s_lines(sexln,eexln,edmln);
// //          Point new_edm = edmln.middle();
// //          txtpt = list_[i]->text_position();
// //          txtpt = txtpt+new_edm-old_edm;
// //          list_[i]->text_position(txtpt);
// //        }
// //      }else if(index==0){
// //        i=0; //
// //        if(i<list_.size()&&index<pts.size()){
// //          list_[i]->get_s_lines(sexln,eexln,edmln);
// //          txtpt = edmln.perpendicular(pts[index]);
// //          list_[i]->text_position(txtpt);
// //        }
// //      }else if(index==1){
// //        i=list_.size()-1;////
// //        if(i<list_.size()&&index<pts.size()){
// //          list_[i]->get_s_lines(sexln,eexln,edmln);
// //          txtpt = edmln.perpendicular(pts[index]);
// //          list_[i]->text_position(txtpt);
// //        }
// //      }
// //    }
// //  }
// }
// void Ln_Dim_Block::getdrag(std::vector<Point>& pts) const
// {
//   if(list_.empty()){
//     return;
//   }
//   const Ln_Dim* f_dim = list_.front();
//   const Ln_Dim* b_dim = list_.back();
//   if(!f_dim || !b_dim){
//     return;
//   }
//   int list_size = list_.size();
// 
//   Line sexln, exln,dmln;
//   Point pt;
//   Text txt;
//   int i=0;
//   for(i=0; i<list_size; i++){
//     assert(list_[i]);
//     if(mode()==PILEUP_DIM){ 
//       list_[i]->get_e_lines(exln,dmln);
//     }
//     else if(mode()==CLOSED_DIM){
//       list_[i]->get_s_lines(sexln,exln,dmln);
//     }
//     pt = dmln.middle();
//     pts.push_back(pt);
//   }
//   if(mode() == PILEUP_DIM){
//     if(show0_){
//       b_dim->get_o_lines(exln,dmln);
//       pt = dmln.middle();
//       pts.push_back(pt);
//     }
//   }
//   else if(mode() == CLOSED_DIM){
//     for(i=0;i<list_.size();i++){
// ////可以拖动全部文字
//       list_[i]->get_text_show(txt);
//       pt = txt.center();
//       pts.push_back(pt);
//     }
// ////只能拖动两端文字
// //    f_dim->get_text_show(txt);
// //    pt = txt.center();
// //    pts.push_back(pt);
// //    if(list_size >=2){
// //      b_dim->get_text_show(txt);
// //      pt = txt.center();
// //      pts.push_back(pt);
// //    }
//   }
// 
// //  ////文字高度
// //	Point ptBox[4];
// //	Text txt;
// //	f_dim->get_text_show(txt);
// //	txt.real_box_point(ptBox);
// //  Point txt_c;////文字中心点
// //  Point txt_b;////文字基点(下边中点)
// //  txt_c = (ptBox[0]+ptBox[2])/2;
// //  switch(f_dim->dim_style_val_.text_pos())
// //  {
// //  case Dimension_Style::UP:
// //    txt_b = (ptBox[0]+ptBox[3])/2;
// //    break;
// //  case Dimension_Style::CENTER:
// //    txt_b = (ptBox[0]+ptBox[1])/2;
// //    break;
// //  case Dimension_Style::DOWN:
// //    txt_b = (ptBox[1]+ptBox[2])/2;
// //    break;
// //  }
// //  Point txt_nor = txt_c - txt_b;
// 
// 
// //  int i=0;
// //  Line  oexln,sexln,eexln,odmln,edmln;
// //  Point dm_pt, txtpt;
// //  Text txt;
// //  if(mode() == PILEUP_DIM){
// //    ////累加标注只能拖拽标注点，不能拖拽文字点
// //    ////需要拖拽0点
// //    if(show0_){
// //      b_dim->get_o_lines(oexln, odmln);
// //      dm_pt = odmln.middle();
// //      pts.push_back(dm_pt);
// //    }
// //    std::vector<Ln_Dim*>::const_iterator it = list_.begin();
// //    for(; it != list_.end(); it++){
// //      if(*it == NULL){
// //        continue;
// //      }
// //      (*it)->get_e_lines(eexln, edmln);
// //      dm_pt = edmln.middle();
// //      pts.push_back(dm_pt);
// //    }
// //  }
// //  else if(mode() == CLOSED_DIM){
// //    ////累加标注能拖拽标注点，也能拖拽文字点
// //    ////不需要拖拽0点
// //
// //    ////只有单个标注
// //    list_[0]->get_text_show(txt);
// //    txtpt = txt.center();
// //    ////文字拖拽框在文字中心点
// //    pts.push_back(txtpt);
// //    if(list_.size() >= 2){
// //      ////有多个个标注
// //      int last_i = list_.size()-1;
// //      list_[last_i]->get_text_show(txt);
// //      txtpt = txt.center();
// //      ////文字拖拽框在文字中心点
// //      pts.push_back(txtpt);
// //    }
// //
// //    int list_size = list_.size();
// //    int last_i = list_size -1;
// //    for(i=0; i<list_size; i++){
// //      if(list_[i] == NULL){
// //        continue;
// //      }
// //      list_[i]->get_s_lines(sexln, eexln, edmln);
// //      dm_pt = edmln.middle();
// //      if(i==0){
// //        list_[i]->get_text_show(txt);
// //        if(dm_pt==txt.center()){
// //          dm_pt = edmln.start();
// //        }
// //      }else if(i==last_i){
// //        list_[i]->get_text_show(txt);
// //        if(dm_pt==txt.center()){
// //          dm_pt = edmln.end();
// //        }
// //      }
// //      pts.push_back(dm_pt);
// //    }
// //  }
// }

Point Ln_Dim_Block::opt()const
{
  if(list_.empty()){
    return Point(0,0,0);
  }
  Ln_Dim * back_dim = list_.back();
  if(!back_dim){
    return Point(0,0,0);
  }
  return back_dim->opt();
}
void Ln_Dim_Block::opt(const Point& pt)
{
  int i=0;
  for(i=0; i<list_.size(); i++){
    if(list_[i]){
      list_[i]->opt(pt);
    }
  }
}
Point Ln_Dim_Block::odm()const
{
  if(list_.empty()){
    return Point(0,0,0);
  }
  Ln_Dim * front_dim = list_.front();
  if(!front_dim){
    return Point(0,0,0);
  }
  return front_dim->odm();
}
void Ln_Dim_Block::odm(const Point& pt)
{
  int i=0;
  for(i=0; i<list_.size(); i++){
    if(list_[i]){
      list_[i]->odm(pt);
    }
  }
}
Point Ln_Dim_Block::text_position()const
{
  if(list_.empty()){
    return Point(0,0,0);
  }
  Ln_Dim * front_dim = list_.front();
  if(!front_dim){
    return Point(0,0,0);
  }
  return front_dim->text_position();
}
void Ln_Dim_Block::text_position(const Point& pt)
{
  int i=0;
  for(i=0; i<list_.size(); i++){
    if(list_[i]){
      list_[i]->text_position(pt);
    }
  }
}

bool Ln_Dim_Block::is_sort(Ln_Dim* dim1, Ln_Dim* dim2)
{
  if(!dim1 || !dim2){
    return false;
  }
  Normal nor;
  radian_2_normal2d(dim_line_radian_, nor);
  Line ln;
  ln.setdata(dim1->ept(), dim2->ept());
  return MoreThen(ln.length_by_way(nor),0);
}

void Ln_Dim_Block::recal_e_pt()
{
  int i=0, j=0;
  int list_size = list_.size();
  for(i=0; i<list_size; i++){
    for(j=0; j<list_size-1; j++){
      if(!is_sort(list_[j],list_[j+1])){
        std::swap(list_[j],list_[j+1]);
      }
    }
  }
}

void Ln_Dim_Block::set_dim_style(std::string style_name)
{
  Ln_Dim * dim = NULL;
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    dim = *it;
    if(!dim){
      continue;
    }
    dim->set_dim_style(style_name);
  }
}
void Ln_Dim_Block::set_dim_style(const Dimension_Style& style)
{
  Ln_Dim * dim = NULL;
  std::vector<Ln_Dim*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    dim = *it;
    if(!dim){
      continue;
    }
    dim->set_dim_style(style);
  }
}
void Ln_Dim_Block::get_dim_style(Dimension_Style& style)const
{
  if(list_.empty()){
    return;
  }
  Ln_Dim * dim = list_.front();
  assert(dim);
  dim->get_dim_style(style);
}
void Ln_Dim_Block::get_dim_style(std::string& style_name)const
{
  if(list_.empty()){
    return;
  }
  Ln_Dim * dim = list_.front();
  assert(dim);
  dim->get_dim_style(style_name);
}

    //    list_[0]->get_s_lines(sexln, eexln, edmln);
    //    txtpt = list_[0]->text_position();
    //    txtpt = txtpt+txt_nor;
      //      list_[last_i]->get_s_lines(sexln, eexln, edmln);
      //      txtpt = list_[last_i]->text_position();
      //      txtpt = txtpt+txt_nor;


void Ln_Dim_Block::dim_count(bool add)
{
  if(add){
    dim_count_ ++;
  }else{
    dim_count_ --;
  }
}

void  Ln_Dim_Block::dim_line_radian(Float f)	
{
  dim_line_radian_=f;
}
Float Ln_Dim_Block::dim_line_radian()const	  
{
  return dim_line_radian_;
}
void  Ln_Dim_Block::dim_line_degree(Float f)	
{
  Float rad = dlhml::degree_2_radian(f);
  dim_line_radian_ = rad;
}
Float Ln_Dim_Block::dim_line_degree()const	  
{
  Float deg = dlhml::radian_2_degree(dim_line_radian_);
  return deg;
}

void Ln_Dim_Block::get_show(std::vector<Entity*>& es)const
{
  std::vector<Ln_Dim*>::const_iterator iter;
  for(iter=list_.begin();iter!=list_.end();++iter)
    (*iter)->get_show(es);
}



}//namespace
