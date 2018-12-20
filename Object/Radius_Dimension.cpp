// Radius_Dimension.cpp: implementation of the Radius_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Radius_Dimension.h"
#include "Global.h"

#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Entity_Snap_Implement.h"
#include "Line.h"
#include "Circle.h"
#include "Entity_Calculate.h"
#include "Normal.h"
#include "Dimension_Style.h"
#include <cassert>
#include "Visitor.h"
#include "encode.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Radius_Dimension,Dimension)
Radius_Dimension::Radius_Dimension()
MCT_INIT1("Radius_Dimension")
{

}
//Radius_Dimension::Radius_Dimension(const Radius_Dimension& rhs)
//: Dimension(rhs)
//{
//	center_ = rhs.center_ ;
//	head_   = rhs.head_   ;
//	tail_   = rhs.tail_   ;
//}
//Radius_Dimension& Radius_Dimension::operator=(const Radius_Dimension& rhs)
//{
//	Dimension::operator =(rhs);
//	if(this == &rhs)
//		return *this;
//	center_ = rhs.center_ ;
//	head_   = rhs.head_   ;
//	tail_   = rhs.tail_   ;
//	return *this;
//}
Radius_Dimension::~Radius_Dimension()
{
}
bool Radius_Dimension::visit(Visitor& v)
{
  show_change(true);
	return v.Visit_Radius_Dimension(*this);
}
void Radius_Dimension::loadme(File& in)
{
  show_change(true);
	load_me(in);
  arc_   .load(in);
	//center_.load(in);
	//head_  .load(in);
	tail_  .load(in);
}
void Radius_Dimension::saveme(const File& out) const
{
	save_me(out);
  arc_   .save(out);
	//center_.save(out);
	//head_  .save(out);
	tail_  .save(out);
}
void Radius_Dimension::save_luame(std::ofstream &out,int tab_num)
{
	Dimension::save_luame(out,tab_num);

	arc_.save_lua(out,"arc_",tab_num);
	tail_.save_lua(out,"tail_",tab_num);

}
void Radius_Dimension::open_luame(lua_State *l)  
{
	Dimension::open_luame(l);
	arc_.open_lua(l,"arc_");
	tail_.open_lua(l,"tail_");
	txt_change(true);
}
void Radius_Dimension::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","RADIUS_DIM");

	get_str_ent();
	get_str_dim();

	////////////////////////////////////////////////////////////
	arc_.get_str_sub();

	rei_add_float(NULL,"tail_.x",tail_.x);
	rei_add_float(NULL,"tail_.y",tail_.y);
	rei_add_float(NULL,"tail_.z",tail_.z);

	rei_get_encode(out);
}

void Radius_Dimension::set_from_strme(char *in)
{
	rei_init(in);


	set_from_str_ent();
	set_from_str_dim();


	////////////////////////////////////////////////////////////
	arc_.set_from_str_sub();

	
	tail_.x = atof(rei_get("tail_.x"));
	tail_.y = atof(rei_get("tail_.y"));
	tail_.z = atof(rei_get("tail_.z"));



	rei_quit();

}
void Radius_Dimension::edit_propertyme(const Edit_Entity& edit)
{
  show_change(true);
//	edit.edit_radius_dim(*this);
}

//void Radius_Dimension::drawme(Draw_Entity& out) const
//{
//	out.draw_radius_dim(*this);
//}
//void Radius_Dimension::xor_drawme(Draw_Entity& out) const
//{
//	out.xor_draw_radius_dim(*this);
//}

errorinfo Radius_Dimension::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Radius_Dimension::transformbyme(const Matrix& mat)
{
  show_change(true);
  Dimension::transformbyme(mat);
	//text_position_.transformby(mat);
  arc_   .transformby(mat);
	//center_.transformby(mat);
	//head_  .transformby(mat);
	tail_  .transformby(mat);
}
void Radius_Dimension::drag_startme(const Matrix& mat)
{
  show_change(true);
}
void Radius_Dimension::drag_endme(const Matrix& mat)
{
  show_change(true);
}

Entity* Radius_Dimension::cloneme() const
{
	return new Radius_Dimension(*this);
}

void Radius_Dimension::closeme()
{
	delete this;
}

void Radius_Dimension::get_line(std::vector<Entity*>& es)const
{
  if(selected()){
    RArc * arc_ln = RArc::create_me();
    arc_ln->color_index(dim_style_val_.line_color());
    arc_ln->line_style(line_style());
    *arc_ln = arc_;
    es.push_back(arc_ln);
  }
  //LINES
  Line * rln = Line::create_me();
  get_line_show(*rln);
  es.push_back(rln);
}

void Radius_Dimension::get_show(std::vector<Entity*>& es)const
{
  //LINES
  get_line(es);
//  Line * rln = Line::create_me();
//  get_line_show(*rln);
//  es.push_back(rln);
  //TEXT AND ITS FRAME
  Text * txt = Text::create_me();
  get_text_frame_show(*txt, es);
  es.push_back(txt);
  //ARROW
  Line ln;
  get_line(ln);
  dim_style_val_.get_arrow(ln,ARROW_END,es);

//  std::vector<Line*> elns;
//  get_arrow_line_show(elns);
//  push(elns,es);
//  std::vector<Circle*> ecrs;
//  get_arrow_circle_show(ecrs);
//  push(ecrs,es);
}


int Radius_Dimension::get_arrow_line_show(std::vector<Line*>& lines) const
{
  Line start;
  get_line(start);
  const Dimension_Style* ds=&dim_style_val_;
  Normal nor;
  Point head = this->head();
  nor.set_data(tail_,head);
  ds->get_arrow_line(head,nor,lines);
  for(int i=0;i<lines.size();++i){
    lines[i]->line_style(line_style());
    //lines[i]->color_index(dim_style_val_.text_frame_color());
  }
  //return num;
  return 0;
}
int Radius_Dimension::get_arrow_circle_show(std::vector<Circle*>& circles) const
{
  Line start;
  get_line(start);
  const Dimension_Style* ds=&dim_style_val_;
  Normal nor;
  Point head = this->head();
  nor.set_data(tail_,head);
  ds->get_arrow_circle(head,circles);
  for(int i=0;i<circles.size();++i){
    circles[i]->line_style(line_style());
    //circles[i]->color_index(dim_style_val_.text_frame_color());
  }
  //return num;
  return 0;
}
void Radius_Dimension::get_line_show(Line& line) const
{
	get_line(line);
	line.line_style(line_style());
	line.color_index(dim_style_val_.line_color());
	//return true;
}
bool Radius_Dimension::get_line(Line& line) const
{
  Point head = this->head();
	line.setdata(tail_,head);
	return true;
}
bool Radius_Dimension::intersectme(const Rect& rect) const
{
	Line line;
	get_line(line);
	Entity_Calculate calc;
	if(calc.linesegment_insect_rect(line,rect))
		return true;
	Text text;
	get_text_show(text);
	if(text.intersect(rect))
		return true;
	return false;
}
bool Radius_Dimension::envelopme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
  Point center = arc_.center();
  Point head = this->head();
	return center.envelop(rect) && head.envelop(rect) && tail_.envelop(rect) 
		&& text.envelop(rect);
}

Rect Radius_Dimension::calc_box2d() const
{
	Rect box2d_;
	Line line;
	get_line(line);
	Text text;
	get_text_show(text);
	std::vector<Entity*> ents;
	ents.push_back(&line);
	ents.push_back(&text);

	dlhml::box2d(box2d_, ents);
//	Entity_Calculate calc;
//	calc.get_ents_rect(box2d_,ents);
	return box2d_;
}

//bool Radius_Dimension::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////	Entity_Snap_Implement<Radius_Dimension> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Radius_Dimension::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}

void Radius_Dimension::recal_text()
{
  show_change(true);
  recal_text_content();
  recal_text_positon();
  recal_text_rotation();
  align_point_ = get_text_align();
}
void Radius_Dimension::recal_text_content()
{
  show_change(true);
	TCHAR buf[MAXSIZE_DIM_TEXT];
	int len = sprintf(buf, TEXT("%f\0"), arc_.radius());
	//int len = sprintf(buf, TEXT("R=%f\0"), arc_.radius());
	dim_text(buf);
}
void Radius_Dimension::recal_text_positon()
{
  show_change(true);
  Point head = this->head();
  Point pos = (head+tail_)/2;
  text_position(pos);
}

void Radius_Dimension::recal_text_rotation()
{
  show_change(true);
  Point head = this->head();
  Normal nor;
  nor.set_data(tail_, head);
  double nor_radian(0);
  normal2d_2_radian(nor, nor_radian);
  //angle_2_normal2d(nor_radian, nor);
  int nor_quadrant(0);
  radian_2_quadrand_re(nor_radian, nor_quadrant);
  switch(nor_quadrant)
  {
  case 2:
  case 3:
    nor_radian += pi;
    break;
  }
  std_radian(nor_radian);
  text_rotation(nor_radian);
}

//void  Radius_Dimension::center(const Point& pt)
//{
//  center_ = pt;
//  recal_tail();
//}	
//Point Radius_Dimension::center()const
//{
//  return center_;
//}						
void  Radius_Dimension::tail  (const Point& pt)
{
  show_change(true);
  tail_ = pt;
  //recal_head();
  //recal_text_positon();
  //recal_text_rotation();
}
Point Radius_Dimension::tail  ()const
{
  return tail_;
}				
//void  Radius_Dimension::head  (const Point& pt)
//{
//  set_head(pt);
////  Float r = center_.distanceto(pt);
////  Normal nor;
////  nor.set_data(center_,tail_);
////  nor.set_unit();
////  head_ =  center_.polarTo(r, nor);
//}	
//Point Radius_Dimension::head  ()const
//{
//  return head_;
//  //Point head;
//  //Normal nor;
//  //nor.set_data(center_,tail_);
//  //nor.set_unit();
//  //return center_.polarTo(r_, nor);
//  //head = center_.polarTo(r_, nor);
//  //return head_;
//}

Point Radius_Dimension::head()const
{
	Point s = arc_.start();
	Point p = arc_.path();
	Point e = arc_.end();
	if(s==p || p==e){
		return s;
	}


	Point c = arc_.center();
	Float r = arc_.radius();
	Normal nor;
	nor.set_data(c,tail_);
	nor.set_unit();
	return c.polarTo(r,nor);
}

//void Radius_Dimension::set_head(const Point& pt)
//{
//  head_ = pt;
//  recal_tail();
//  //recal_text_positon();
//  //recal_text_rotation();
//  //recal_head();
//
//  //  Float r = center_.distanceto(pt);
//  //  Normal nor;
//  //  nor.set_data(center_,tail_);
//  //  nor.set_unit();
//  //  head_ =  center_.polarTo(r, nor);
//}
//void Radius_Dimension::set_tail(const Point& pt)
//{
//  tail_ = pt;
//  recal_head();
//  //recal_text_positon();
//  //recal_text_rotation();
//  //recal_head();
//
//  //  Float r = center_.distanceto(pt);
//  //  Normal nor;
//  //  nor.set_data(center_,tail_);
//  //  nor.set_unit();
//  //  head_ =  center_.polarTo(r, nor);
//}
//
//void Radius_Dimension::recal_head()
//{
//  if(center_ == tail_){
//    return;
//  }
//
//  Float r = center_.distanceto(head_);
//  Normal nor;
//  nor.set_data(center_, tail_);
//  nor.set_unit();
//  //if(!nor.is_zero_normal())
//  head_ = center_.polarTo(r, nor);
//  
//  recal_text_positon();
//  recal_text_rotation();
//}						
//void Radius_Dimension::recal_tail()
//{
//  if(center_ == head_){
//    return;
//  }
//
//  Float r = center_.distanceto(tail_);
//  Normal nor;
//  nor.set_data(center_, head_);
//  nor.set_unit();
//  //if(!nor.is_zero_normal())
//  tail_ = center_.polarTo(r, nor);
//  
//  recal_text_positon();
//  recal_text_rotation();
//}						

//void  Radius_Dimension::setdata(const Point& center,
//                                const Point& tail,
//                                const Point& head)
//{
//  center_ = center ;
//  tail_   = tail   ;
//  set_head(head)   ;
//}

void Radius_Dimension::setctrl(const std::vector<Point>& pts)
{
  show_change(true);
  if(pts.size() < pt_count()){
    return;
  }
  arc_.set(pts[0],pts[1],pts[2]);
  tail_ = pts[3];
  if(pts[2]!=pts[3]){
    recal_text();
  }

//  if(pts.size() != pt_count){
//    return;
//  }
//  RArc arc;
//  arc.setdata(pts[0],pts[1],pts[2]);
//  center_ = arc.center();
//  head_   = arc.get_middle_pt();
//  tail_   = pts[3];
//  setdata(arc.center(),arc.get_start_pt(),arc.get_end_pt(),arc.get_middle_pt());
}
void Radius_Dimension::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(arc_.start());
  pts.push_back(arc_.path());
  pts.push_back(arc_.end());
  pts.push_back(tail_);


//  RArc arc;
//  arc.set
//
//  pts.push_back(vertex_);
//  pts.push_back(start_ );
//  pts.push_back(end_   );
//  pts.push_back(dim_   );
}
int  Radius_Dimension::pt_count()const
{
  return 4;
}

void Radius_Dimension::setdrag(const std::vector<Point>& pts, int index)
{
  show_change(true);
  if(pts.size() < 1){
    return;
  }
  tail_=pts[0];
  recal_text();
}
void Radius_Dimension::getdrag(std::vector<Point>& pts)const
{
  pts.push_back(tail_);
}

//namespace
}
