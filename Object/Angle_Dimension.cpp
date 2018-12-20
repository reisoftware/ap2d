// Angle_Dimension.cpp: implementation of the Angle_Dimension class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Angle_Dimension.h"

#include "Global.h"

#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Entity_Snap_Implement.h"
#include "Normal.h"
#include "Dimension_Style.h"
#include "Line.h"
#include "RArc.h"
#include "Entity_Calculate.h"
#include "Matrix_d.h"
#include "Circle.h"
#include <cassert>
#include "Visitor.h"

#include "Global.h"
#include "getrace.h"
#include "encode.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Angle_Dimension,Dimension)
Angle_Dimension::Angle_Dimension()
MCT_INIT1("Angle_Dimension")
{
  dim_style_val_.arrow_num(ARROW_DOUBLE);
}
Angle_Dimension::~Angle_Dimension()
{
}
bool Angle_Dimension::visit(Visitor& v)
{
	return v.Visit_Angle_Dimension(*this);
}
void Angle_Dimension::loadme(File& in)  
{ 
  show_change(true);
  load_me(in);
	vertex_.load(in);
	start_ .load(in);
	end_   .load(in);
	dim_   .load(in);
} 
void Angle_Dimension::saveme(const File& out) const
{
	save_me(out);
	vertex_.save(out);
	start_ .save(out);
	end_   .save(out);
	dim_   .save(out);
}
void Angle_Dimension::save_luame(std::ofstream &out,int tab_num)
{
	Dimension::save_luame(out,tab_num);
	vertex_.save_lua(out,"vertex_",tab_num);
	start_.save_lua(out,"start_",tab_num);
	end_.save_lua(out,"end_",tab_num);
	dim_.save_lua(out,"dim_",tab_num);

}
void Angle_Dimension::open_luame(lua_State *l)  
{
	TRACE_OUT("Angle_Dimension open in open_luame()\n");
  Dimension::open_luame(l);
  vertex_.open_lua(l,"vertex_");
  start_.open_lua(l,"start_");
  end_.open_lua(l,"end_");
  dim_.open_lua(l,"dim_");

	txt_change(true);

}
void Angle_Dimension::get_strme(char *out)
{
	rei_quit();

	rei_add_str(NULL,"kind","ANGLE_DIM");

	get_str_ent();
	get_str_dim();

	////////////////////////////////////////////////////////////
	rei_add_float(NULL,"vertex_.x",vertex_.x);
	rei_add_float(NULL,"vertex_.y",vertex_.y);
	rei_add_float(NULL,"vertex_.z",vertex_.z);

	rei_add_float(NULL,"start_.x",start_.x);
	rei_add_float(NULL,"start_.y",start_.y);
	rei_add_float(NULL,"start_.z",start_.z);

	rei_add_float(NULL,"end_.x",end_.x);
	rei_add_float(NULL,"end_.y",end_.y);
	rei_add_float(NULL,"end_.z",end_.z);

	rei_add_float(NULL,"dim_.x",dim_.x);
	rei_add_float(NULL,"dim_.y",dim_.y);
	rei_add_float(NULL,"dim_.z",dim_.z);

	rei_get_encode(out);
}

void Angle_Dimension::set_from_strme(char *in)
{
	rei_init(in);


	set_from_str_ent();
	set_from_str_dim();


	////////////////////////////////////////////////////////////
	
	vertex_.x = atof(rei_get("vertex_.x"));
	vertex_.y = atof(rei_get("vertex_.y"));
	vertex_.z = atof(rei_get("vertex_.z"));
	
	start_.x = atof(rei_get("start_.x"));
	start_.y = atof(rei_get("start_.y"));
	start_.z = atof(rei_get("start_.z"));
	
	end_.x = atof(rei_get("end_.x"));
	end_.y = atof(rei_get("end_.y"));
	end_.z = atof(rei_get("end_.z"));
	
	dim_.x = atof(rei_get("dim_.x"));
	dim_.y = atof(rei_get("dim_.y"));
	dim_.z = atof(rei_get("dim_.z"));



	rei_quit();
}
void Angle_Dimension::edit_propertyme(const Edit_Entity& edit)
{
  show_change(true);
//	edit.edit_angle_dim(*this);
}

//void Angle_Dimension::drawme(Draw_Entity& out) const
//{
//	out.draw_angle_dim(*this);
//}
//void Angle_Dimension::xor_drawme(Draw_Entity& out) const
//{
////  if(start_==end_){
////    Line ln(start_,end_);
////    ln.xor_draw(out);
////  }
////  else{
//    Dimension::xor_drawme(out);
////  }
//}

errorinfo Angle_Dimension::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Angle_Dimension::transformbyme(const Matrix& mat)
{
  show_change(true);
  Dimension::transformbyme(mat);
	//text_position_.transformby(mat);
	vertex_.transformby(mat);
	start_ .transformby(mat);
	end_   .transformby(mat);
	dim_   .transformby(mat);
}
void Angle_Dimension::drag_startme(const Matrix& mat)
{
  show_change(true);
}
void Angle_Dimension::drag_endme(const Matrix& mat)
{
  show_change(true);
}

Entity* Angle_Dimension::cloneme() const
{
	return new Angle_Dimension(*this);
}

void Angle_Dimension::closeme()
{
	delete this;
}

void Angle_Dimension::get_line(std::vector<Entity*>& es)const
{
  Line * stln = Line::create_me();
  if(start_==end_){
    stln->setdata(vertex_,start_);
    stln->color_index(dim_style_val_.line_color());
    stln->line_style(line_style());
    es.push_back(stln);
    return;
  }
  //LINES
  Line * edln = Line::create_me();
  Line * exln = Line::create_me();
  RArc * dim_arc = RArc::create_me();
  get_dim_lines_show(*stln,*edln,*exln,*dim_arc);
  es.push_back(stln);
  es.push_back(edln);
  es.push_back(exln);
  es.push_back(dim_arc);
}

void Angle_Dimension::get_show(std::vector<Entity*>& es)const
{
  Line stln,edln,exln;
  RArc dim_arc;
  get_dim_lines_show(stln,edln,exln,dim_arc);
  //LINES
  get_line(es);
//  Line * stln = Line::create_me();
//  Line * edln = Line::create_me();
//  Line * exln = Line::create_me();
//  RArc * dim_arc = RArc::create_me();
//  get_dim_lines_show(*stln,*edln,*exln,*dim_arc);
//  es.push_back(stln);
//  es.push_back(edln);
//  es.push_back(exln);
//  es.push_back(dim_arc);
  //TEXT AND ITS FRAME
  Text * txt = Text::create_me();
  get_text_frame_show(*txt, es);
  es.push_back(txt);
  //ARROW
  dim_style_val_.get_arrow(dim_arc,es);
//  std::vector<Line*> slns;
//  get_start_arrow_line_show(slns);
//  push(slns,es);
//  std::vector<Line*> elns;
//  get_end_arrow_line_show(elns);
//  push(elns,es);
//  std::vector<Circle*> scrs;
//  get_start_arrow_circle_show(scrs);
//  push(scrs,es);
//  std::vector<Circle*> ecrs;
//  get_end_arrow_circle_show(ecrs);
//  push(ecrs,es);
}


void Angle_Dimension::get_dim_lines_show(Line& st,Line& ed,Line& extendline,RArc& dim) const
{
  get_lines(st,ed,extendline,dim);
  st  .line_style(line_style());
  ed  .line_style(line_style());
  dim .line_style(line_style());
  extendline.line_style(line_style());
  st  .color_index(dim_style_val_.line_color());
  ed  .color_index(dim_style_val_.line_color());
  dim .color_index(dim_style_val_.line_color());
  extendline.color_index(dim_style_val_.line_color());
  //return true;
}
int Angle_Dimension::get_start_arrow_line_show(std::vector<Line*>& lines) const
{
  Line start,end,extendline;
  RArc dim;
  get_lines(start,end,extendline,dim);
  const Dimension_Style* ds=&dim_style_val_;
  Point st1,ed1;
  st1 = dim.start();
  ed1 = dim.end();
  //dim.get_end_point(st1,ed1);

  Point pt = st1-vertex_;
  Matrix mat;
  mat.set_z_rotation_radian(-pi/2);
  pt.transformby(mat);
  Normal nor;
  nor.set_data(pt.x,pt.y,0);

  ds->get_arrow_line(st1,nor,lines);
  for(int i=0;i<lines.size();++i){
    lines[i]->line_style(line_style());
    lines[i]->color_index(dim_style_val_.line_color());
  }
  //return num;
  return 0;
}
int Angle_Dimension::get_end_arrow_line_show(std::vector<Line*>& lines) const
{
  Line start,end,extendline;
  RArc dim;
  get_lines(start,end,extendline,dim);
  const Dimension_Style* ds=&dim_style_val_;
  Point st1,ed1;
  st1 = dim.start();
  ed1 = dim.end();
  //dim.get_end_point(st1,ed1);
  Point pt = ed1-vertex_;
  Matrix mat;
  mat.set_z_rotation_radian(+pi/2);
  pt.transformby(mat);
  Normal nor;
  nor.set_data(pt.x,pt.y,0);

  ds->get_arrow_line(ed1,nor,lines);
  for(int i=0;i<lines.size();++i){
    lines[i]->line_style(line_style());
    lines[i]->color_index(dim_style_val_.line_color());
  }
  //return num;
  return 0;
}
int Angle_Dimension::get_start_arrow_circle_show(std::vector<Circle*>& circles) const
{
  Line start,end,extendline;
  RArc dim;
  get_lines(start,end,extendline,dim);
  const Dimension_Style* ds=&dim_style_val_;
  Point st1,ed1;
  st1 = dim.start();
  ed1 = dim.end();
  //dim.get_end_point(st1,ed1);
  ds->get_arrow_circle(st1,circles);
  for(int i=0;i<circles.size();++i){
    circles[i]->line_style(line_style());
    circles[i]->color_index(dim_style_val_.line_color());
  }
  //return num;
  return 0;
}
int Angle_Dimension::get_end_arrow_circle_show(std::vector<Circle*>& circles) const
{
  Line start,end,extendline;
  RArc dim;
  get_lines(start,end,extendline,dim);
  const Dimension_Style* ds=&dim_style_val_;
  Point st1,ed1;
  st1 = dim.start();
  ed1 = dim.end();
  //dim.get_end_point(st1,ed1);
  ds->get_arrow_circle(ed1,circles);
  for(int i=0;i<circles.size();++i){
    circles[i]->line_style(line_style());
    circles[i]->color_index(dim_style_val_.line_color());
  }
  //return num;
  return 0;
}
/*
*/
bool Angle_Dimension::get_lines(Line& st,Line& ed,Line& entendline,RArc& dim) const
{
  RArc arc;
  arc.set(vertex_,start_,end_,dim_);
  st.setdata(arc.center(), arc.start() );
  ed.setdata(arc.center(), arc.end()   );
  dim.set(vertex_,start_,end_,dim_);
  //entendline.setdata(arc.center(), arc.middle());
  //entendline.setdata(arc.start(), arc.end());
  return true;
}

/*
bool Angle_Dimension::get_lines(Line& st,Line& ed,Line& entendline,RArc& dim) const
{
  Point c;
  if(start_==end_ || start_==dim_ || end_==dim_){
    c=vertex_;
  }else{
    dim.set(start_, dim_, end_);
    //dim.setdata(start_, dim_, end_);
    c = dim.center();
  }
  st.setdata(c, start_ );
  ed.setdata(c, end_   );
  entendline.setdata(c, vertex_);
	return true;
}
*/

/*
bool Angle_Dimension::get_lines(Line& st,Line& ed,Line& entendline,RArc& dim) const
{
  st.setdata(vertex_, start_ );
  ed.setdata(vertex_, end_   );
  dim.set(vertex_,start_,end_,dim_);
  //entendline.setdata(vertex_);
	return true;
}
*/


bool Angle_Dimension::intersectme(const Rect& rect) const
{
  Line start,end,extendline;
  RArc dim;
  get_lines(start,end,extendline,dim);
  Entity_Calculate calc;
  if(calc.linesegment_insect_rect(start,rect))
    return true;
  if(calc.linesegment_insect_rect(end,rect))
    return true;
  if(dim.intersect(rect))
    return true;
  Text text;
  get_text_show(text);
  if(text.intersect(rect))
    return true;
  return false;
}
bool Angle_Dimension::envelopme(const Rect& rect) const
{ 
  Line start,end,extendline;
  RArc dim;
  get_lines(start,end,extendline,dim);
  Text text;
  get_text_show(text);
  return vertex_.envelop(rect) && start.end().envelop(rect) 
    && end.end().envelop(rect) && text_position_.envelop(rect)
    && text.envelop(rect) && dim.envelop(rect);
  return false;
}

Rect Angle_Dimension::calc_box2d() const
{
  Rect box2d_;
  Line start,end,extendline;
  RArc dim;
  get_lines(start,end,extendline,dim);
  std::vector<Entity*> ents;
  ents.push_back(&start);
  ents.push_back(&end);
  ents.push_back(&dim);
  Text text;
  get_text_show(text);
  ents.push_back(&text);
	dlhml::box2d(box2d_, ents);
  //Entity_Calculate calc;
  //calc.get_ents_rect(box2d_,ents);
  return box2d_;
}

//bool Angle_Dimension::snap_intersect_pointme(Point& pt,
//                                             const Entity& ent,
//                                             const Rect& rect) const
//{
//  //NOOK SNAP
//  return false;
////	Entity_Snap_Implement<Angle_Dimension> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Angle_Dimension::snap_intersect_pointme(Point& pt,
                                             const Entity_Snap& snap,
                                             const Rect& rect) const
{
  //NOOK SNAP
  //return false;
	return snap.intersect(pt,rect,*this);
}
 
Point Angle_Dimension::center()const
{               
  RArc arc;
  arc.set(start_,dim_,end_); 
  //arc.setdata(start_,dim_,end_); 
  return arc.center();
}

void Angle_Dimension::setdata(const Point& v,const Point& st,const Point& ed,const Point& dim)
{
  show_change(true);
  vertex_ = v ;
	start_ = st ;
	end_  = ed  ;
	dim_ = dim  ;
  dim_text_recal();
}

void Angle_Dimension::center(const Point& pt)
{
  show_change(true);
  Point  c = center();
  Normal nor;
  nor.set_data(c, pt);
  Point  new_srt = start();
  Point  new_end = end  ();
  Point  new_dim = dim  ();
  new_srt+=nor;
  new_end+=nor;
  new_dim+=nor;
  setdata(vertex(), new_srt, new_end, new_dim);
  Point  new_text_pos = text_position();
  new_text_pos+=nor;
  text_position(new_text_pos);
}

void Angle_Dimension::dim_text_recal()
{
  show_change(true);
//	if(is_dim_0(){
//	    return;
//	}
	dim_text_content();
	dim_text_position();
	dim_text_rotation();
	dim_text_alignpt();
}
void Angle_Dimension::dim_text_content()
{
  show_change(true);
  RArc arc;
  arc.set(start_,dim_,end_);
  //arc.setdata(start_,dim_,end_);
  Float an = arc.end_degree2d()-arc.start_degree2d();
  std_degree(an);

	int    du= int(an);
	int    fe= int((an-du)*60);
	TCHAR buf[MAXSIZE_DIM_TEXT];
	int len = sprintf(buf, TEXT("%dÅK%d\'\0"), du, fe);
	dim_text(buf);
}
void Angle_Dimension::dim_text_position()
{
  show_change(true);
	text_position(dim_);
}
void Angle_Dimension::dim_text_rotation()
{
  show_change(true);
  RArc arc;
  arc.set(start_, dim_, end_);
  //arc.setdata(start_, dim_, end_);
  Point c   = arc.center();
  Point mid = arc.middle();
  Normal nor;
  nor.set_data(c,mid);
  Float mid_degree=0;
  normal2d_2_degree(nor,mid_degree);
  mid_degree+=90;
  if(MoreEqu(mid_degree,90)&&LessThen(mid_degree,270)){
    mid_degree+=180;
  }
  //  DEGREE_POS dp = degree_pos(mid_degree);
  //  switch(dp)
  //  {
  //  case QD_2:
  //  case QD_3:
  //  case AXIS_180:
  //  case AXIS_270:
  //    mid_degree+=180;
  //    break;
  //  }
  std_degree(mid_degree);
  Float mid_radian = degree_2_radian(mid_degree);
  text_rotation(mid_radian);

//	RArc ar = ArcFromDim(&dim);
//	TArc tarc = LArc2Tarc(ar);
//	double dAngleMid = TPG::MidArc(tarc);
//	double dTxtRota = TPG::Radian(
//		dAngleMid+T_PI/2);
//	if(TPG::RadianToQuadrantRe(dTxtRota) 
//		== 2) 
//	{
//		dTxtRota += TIAN_GA_BETTER::PI_R;
//	}
//	else if(TPG::RadianToQuadrantRe(dTxtRota) 
//		== 3)
//	{
//		dTxtRota -= TIAN_GA_BETTER::PI_R;
//	}
//	dTxtRota = TPG::Radian(dTxtRota);
//	dim.text_rotation(dTxtRota);
}
void Angle_Dimension::dim_text_alignpt()
{
  show_change(true);
  align_point(get_text_align());
	//align_point(Text::center_bottom);
}

void Angle_Dimension::setctrl(const std::vector<Point>& pts)
{
  show_change(true);
  if(pts.size() != 4){
    return;
  }
  Point pt0 = pts[0];
  Point pt1 = pts[1];
  Point pt2 = pts[2];
  Point pt3 = pts[3];
  /*
  RArc arc;
  arc.set(pts[0],pts[1],pts[2],pts[3]);
  setdata(arc.center(),arc.start(),arc.end(),arc.middle());
  */
  setdata(pts[0],pts[1],pts[2],pts[3]);
  if(pt2!=pt3){
	RArc arc;
	arc.set(pts[0],pts[1],pts[2],pts[3]);
	dim_ = arc.middle();
	setdata(arc.center(),arc.start(),arc.end(),arc.middle());
  }
}
void Angle_Dimension::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(vertex_);
  pts.push_back(start_ );
  pts.push_back(end_   );
  pts.push_back(dim_   );
}
int  Angle_Dimension::pt_count()const
{
  return 4;
}
void Angle_Dimension::setdrag(const std::vector<Point>& pts, int index)
{
  show_change(true);
  if(pts.empty()){
    return;
  }
  //RArc arc;
  //arc.set(start_,dim_,end_);
  //arc.setdata(start_,dim_,end_);
  //arc.center(pts[0]);
  //start_=arc.start();
  //dim_  =arc.middle();
  //end_  =arc.end();
  //text_position(dim_);
  Point nor;
  switch(index)
  {
  case 0:
	  nor = pts[index] - vertex_;
	  vertex_ += nor;
	  start_ += nor;
	  end_ += nor;
	  dim_ += nor;
	  text_position_ += nor;
	  break;
  case 1:
	  nor = pts[index] - dim_;
	  dim_ += nor;
	  RArc arc;
	  arc.set(vertex_,start_,end_,dim_);
	  dim_ = arc.middle();
	  text_position_ = dim_;
	  break;
  }
}
void Angle_Dimension::getdrag(std::vector<Point>& pts)const
{
  //RArc arc;
  //arc.set(start_,dim_,end_);
  //arc.setdata(start_,dim_,end_);
  //pts.push_back(arc.center());
  pts.push_back(vertex_);
  pts.push_back(dim_);
}

//namespace
}
