// Three_Pt_Dimension_Block.cpp: implementation of the Three_Pt_Dimension_Block class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Three_Pt_Dimension_Block.h"
#include "Three_Pt_Dimension.h"
#include <algorithm>
#include <functional>
#include "File.h"
#include "Line.h"
#include "Entity_Calculate.h"
#include "Database.h"
#include "Edit_Entity.h"
#include "Normal.h"
#include "Visitor.h"
//#include "..\DrawDll\reitrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Three_Pt_Dimension_Block,Entity)
Three_Pt_Dimension_Block::Three_Pt_Dimension_Block()
MCT_INIT1("Three_Pt_Dimension_Block")
{

}
Three_Pt_Dimension_Block::Three_Pt_Dimension_Block(const Three_Pt_Dimension_Block& rhs)
:Entity(rhs)
MCT_INIT2("Three_Pt_Dimension_Block")
{
	std::vector<Three_Pt_Dimension*>::const_iterator iter;
	for(iter=rhs.list_.begin();iter!=rhs.list_.end();++iter){
		Three_Pt_Dimension* dim = static_cast<Three_Pt_Dimension*>((*iter)->clone());
		list_.push_back(dim);
	}
}
Three_Pt_Dimension_Block& Three_Pt_Dimension_Block::operator=(const Three_Pt_Dimension_Block& rhs)
{
	Entity::operator =(rhs);
	if(this == &rhs)
		return *this;
	std::vector<Three_Pt_Dimension*>::const_iterator iter;
	for(iter=rhs.list_.begin();iter!=rhs.list_.end();++iter){
		Three_Pt_Dimension* dim = static_cast<Three_Pt_Dimension*>((*iter)->clone());
		list_.push_back(dim);
	}
	return *this;
}
Three_Pt_Dimension_Block::~Three_Pt_Dimension_Block()
{
	clear();
}
void Three_Pt_Dimension_Block::clear()
{
	std::for_each(list_.begin(),list_.end(),
		std::mem_fun<bool,Three_Pt_Dimension>(&Three_Pt_Dimension::close));
	list_.clear();
}
bool Three_Pt_Dimension_Block::visit(Visitor& v)
{
	return v.Visit_Three_Pt_Dimension_Block(*this);
}
void Three_Pt_Dimension_Block::loadme(File& in)
{
	list_.clear();
	int num = 0;
	in >> num;
	for(int i=0;i<num;++i){
		Three_Pt_Dimension* dim = Three_Pt_Dimension::create_me();
		dim->load(in);
		list_.push_back(dim);
	}
}
void Three_Pt_Dimension_Block::saveme(const File& out) const
{
	out << list_.size();
	std::vector<Three_Pt_Dimension*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->save(out);
}
void Three_Pt_Dimension_Block::edit_propertyme(const Edit_Entity& edit)
{
//	edit.edit_three_pt_dim_block(*this);
}
void Three_Pt_Dimension_Block::drawme(Draw_Entity& out) const
{
	std::vector<Three_Pt_Dimension*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->draw(out);
}
void Three_Pt_Dimension_Block::xor_drawme(Draw_Entity& out) const
{
	std::vector<Three_Pt_Dimension*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->xor_draw(out);
}
errorinfo Three_Pt_Dimension_Block::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}
void Three_Pt_Dimension_Block::transformbyme(const Matrix& mat)
{
//	REITRACE;
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter)
		(*iter)->transformby(mat);
}
void Three_Pt_Dimension_Block::drag_startme(const Matrix& mat)
{
}
void Three_Pt_Dimension_Block::drag_endme(const Matrix& mat)
{
}
Entity* Three_Pt_Dimension_Block::cloneme() const
{
	return new Three_Pt_Dimension_Block(*this);
}
void Three_Pt_Dimension_Block::closeme()
{
	delete this;
}
bool Three_Pt_Dimension_Block::intersectme(const Rect& rect) const
{
	std::vector<Three_Pt_Dimension*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if((*iter)->intersect(rect))
			return true;
	}
	return false;
}
bool Three_Pt_Dimension_Block::envelopme(const Rect& rect) const
{
	std::vector<Three_Pt_Dimension*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(!(*iter)->envelop(rect))
			return false;
	}
	return true;
}
Rect Three_Pt_Dimension_Block::calc_box2d() const
{
	Rect box2d_;
	box2d_.set_reverse_minmax();
	std::vector<Three_Pt_Dimension*>::const_iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Rect temp = (*iter)->box2d();
		box2d_.xmin(min(box2d_.xmin(),temp.xmin()));
		box2d_.ymin(min(box2d_.ymin(),temp.ymin()));
		box2d_.xmax(max(box2d_.xmax(),temp.xmax()));
		box2d_.ymax(max(box2d_.ymax(),temp.ymax()));
	}
	return box2d_;
}
bool Three_Pt_Dimension_Block::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
	return false;
}
bool Three_Pt_Dimension_Block::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return false;
}
void Three_Pt_Dimension_Block::insert(const Three_Pt_Dimension* pos,Three_Pt_Dimension* dim)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(*iter == pos){
			list_.insert(iter,dim);
			break;
		}
	}
}
void Three_Pt_Dimension_Block::push_back(Three_Pt_Dimension* dim)
{
	list_.push_back(dim);
}
void Three_Pt_Dimension_Block::erase(Three_Pt_Dimension* dim)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(*iter == dim){
			list_.erase(iter);
			dim->close();
			break;
		}
	}
}
Three_Pt_Dimension* Three_Pt_Dimension_Block::front()
{
	return list_.front();
}
Three_Pt_Dimension* Three_Pt_Dimension_Block::back()
{
	return list_.back();
}
Three_Pt_Dimension* Three_Pt_Dimension_Block::previous(const Three_Pt_Dimension* pos)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(*iter == pos)
			return iter==list_.begin()?0:*(iter-1);
	}
	return 0;
}
Three_Pt_Dimension* Three_Pt_Dimension_Block::next(const Three_Pt_Dimension* pos)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		if(*iter == pos)
			return iter+1==list_.end()?0:*(iter+1);
	}
	return 0;
}
bool Three_Pt_Dimension_Block::select_from_dimline(Three_Pt_Dimension*& dim, const Point& pt)
{
//  if(is_in_beeline_by_entendline(pt)){
//    return false;
//  }
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line start,end,dimline;
		(*iter)->get_lines(start,end,dimline);
		Entity_Calculate calc;
		Point pp1;
		calc.line_perpendicular(pp1,dimline,pt);
    if(calc.point_in_linesegment(pp1,dimline)){
      dim = *iter;
			return true;
    }
	}
  dim = 0;
	return true;
}
Three_Pt_Dimension* Three_Pt_Dimension_Block::select_from_dimline(const Rect& rc)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line start,end,dim;
		(*iter)->get_lines(start,end,dim);
		Entity_Calculate calc;
		if(calc.linesegment_insect_rect(dim,rc))
			return *iter;
	}
	return 0;
}
Three_Pt_Dimension* Three_Pt_Dimension_Block::select_from_text(const Rect& rc)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Text text;
		(*iter)->get_text_show(text);
		if(text.intersect(rc))
			return *iter;
	}
	return 0;
}
void Three_Pt_Dimension_Block::select_from_extendline(Three_Pt_Dimension*& prev,Three_Pt_Dimension*& next,const Rect& rc)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line start,end,dim;
		(*iter)->get_lines(start,end,dim);
		Entity_Calculate calc;
		if(calc.linesegment_insect_rect(start,rc)){
			next = *iter;
			if(iter!=list_.begin())
				prev = *(iter-1);
			else
				prev = 0;
			return ;
		}
		if(calc.linesegment_insect_rect(end,rc)){
			prev = *iter;
			if(iter+1!=list_.end())
				next = *(iter+1);
			else
				next = 0;
			return ;
		}
	}
	prev = 0;
	next = 0;
}
bool Three_Pt_Dimension_Block::is_in_beeline_by_entendline(const Rect& rc)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line start,end,dim;
		(*iter)->get_lines(start,end,dim);
		Entity_Calculate calc;
		if(calc.rect_insect_beeline(rc,start) || calc.rect_insect_beeline(rc,end)){
      return true;
		}
  }
  return false;
}
bool Three_Pt_Dimension_Block::is_in_beeline_by_entendline(const Point& pt)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line start,end,dim;
		(*iter)->get_lines(start,end,dim);
		if(start.is_in_line(pt) || end.is_in_line(pt)){
      return true;
		}
  }
  return false;
}
void Three_Pt_Dimension_Block::offset_dimlines(const Normal& nor,Float off)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Point pt = (*iter)->dimension_pt();
		pt = pt.polarTo(off,nor);
		(*iter)->dimension_pt(pt);
		pt = (*iter)->text_position();
		pt = pt.polarTo(off,nor);
		(*iter)->text_position(pt);
	}
}
void Three_Pt_Dimension_Block::layout_dimlines(const Point& pos)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line start,end,dim;
		(*iter)->get_lines(start,end,dim);
		Line line;
		Entity_Calculate calc;
		calc.line_parallel(line,dim,pos);
		Point pt = (*iter)->dimension_pt();
		Point pp;
		calc.line_perpendicular(pp,line,pt);
		(*iter)->dimension_pt(pp);
		Normal nor;
		nor.set_data(pt,pp);
		Point textpos = (*iter)->text_position();
		(*iter)->text_position(textpos.polarTo(pp.distanceto(pt),nor));
	}
}
void Three_Pt_Dimension_Block::layout_base(const Point& pos)
{
	std::vector<Three_Pt_Dimension*>::iterator iter;
	for(iter=list_.begin();iter!=list_.end();++iter){
		Line start,end,dim;
		(*iter)->get_lines(start,end,dim);
		Line line;
		Entity_Calculate calc;
		calc.line_parallel(line,dim,pos);
		Point st;
		calc.line_insect_line(st,line,start);
		(*iter)->start_dim_to(st);
		Point ed;
		calc.line_insect_line(ed,line,end);
		(*iter)->end_dim_to(ed);
	}
}
bool Three_Pt_Dimension_Block::front_or_back_point(const Point& pt)
{
	Three_Pt_Dimension* frontdim = front();
	Line start,end,dim;
	frontdim->get_lines(start,end,dim);
	Point pp;
	Entity_Calculate calc;
	calc.line_perpendicular(pp,start,pt);
	Float stoff = pt.distanceto(pp);

	Three_Pt_Dimension* backdim = back();
	backdim->get_lines(start,end,dim);
	Point pp1;
	calc.line_perpendicular(pp1,end,pt);
	Float edoff = pt.distanceto(pp1);

	if(stoff < edoff)
		return true;
	else
		return false;
}
int Three_Pt_Dimension_Block::size() const
{
	return list_.size();
}

void Three_Pt_Dimension_Block::selected(bool sel)
{
  Entity::selected(sel);
//  sel_ = sel;
  std::vector<Three_Pt_Dimension*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->selected(sel);
  }
}

bool Three_Pt_Dimension_Block::selected() const
{
  return Entity::selected();
//  return sel_;
}

void Three_Pt_Dimension_Block::dim_style(std::string style_name)
{
  std::vector<Three_Pt_Dimension*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    //(*it)->selected(sel);
    (*it)->dim_style_name(style_name);
  }
}
std::string Three_Pt_Dimension_Block::dim_style() const
{
  if(list_.empty()){
    return "";
  }
  //std::vector<Four_Pt_Dimension*>::iterator it = list_.begin();
  return (*list_.begin())->dim_style_name();
}

void Three_Pt_Dimension_Block::line_style(std::string style)
{
  Entity::line_style(style);
  std::vector<Three_Pt_Dimension*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->line_style(style);
  }
}
std::string Three_Pt_Dimension_Block::line_style() const		
{
  return Entity::line_style();
}
void Three_Pt_Dimension_Block::color(COLORREF rgb)	
{
  Entity::color(rgb);
  std::vector<Three_Pt_Dimension*>::iterator it = list_.begin();
  for(; it != list_.end(); it++){
    (*it)->color(rgb);
  }
}
COLORREF Three_Pt_Dimension_Block::color() const				
{
  return Entity::color();
}

//namespace
}
