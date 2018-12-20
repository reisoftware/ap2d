// Dimension.cpp: implementation of the Dimension class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dimension.h"

#include <cassert>

#include "Database.h"
#include "File.h"

#include "Dimension_Style.h"

#include "Matrix_d.h"
#include "Normal.h"

#include "global.h"

#include "Text.h"
#include "Line.h"
#include "Circle.h"
#include "RArc.h"
#include "Entity_Calculate.h"
#include "encode.h"

//#include "..\DrawDll\reitrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_RUNTIME(Dimension,Entity)
Object* Dimension::createob()
{return 0;}

void Dimension::init()
{
	dim_style_name_ = "Standard";
	dim_text_ = "Standard";
	text_rotation_ = 0;

  set_dim_style(dim_style_name_);
  align_point_ = get_text_align();

}
Dimension::Dimension()
MCT_INIT1("Dimension")
{
	init();
  txt_change(true);
  show_change(true);
}
Dimension::Dimension(const Dimension& rhs)
:Entity(rhs)
MCT_INIT2("Dimension")
{
	init();
	dim_style_name_ = rhs.dim_style_name_;
	dim_text_ = rhs.dim_text_;

	text_rotation_ = rhs.text_rotation_;
	text_position_ = rhs.text_position_;
	align_point_ = rhs.align_point_;

	dim_style_val_  = rhs.dim_style_val_  ;
	text_style_val_ = rhs.text_style_val_ ;

  //align_point(Text::center_bottom);

  ////clone时，不复制show_record_
  //show_record_ = rhs.show_record_;
  //show_change_ = rhs.show_change_;
  show_change_ = true;

  //txt_change_=rhs.txt_change_;
  //txt_record_=rhs.txt_record_;
  txt_change_=true;
  txt_record_=rhs.txt_record_;
  
}
Dimension& Dimension::operator=(const Dimension& rhs)
{
	Entity::operator=(rhs);
	if(this == &rhs)
		return *this;
	dim_style_name_ = rhs.dim_style_name_;
	dim_text_ = rhs.dim_text_;


	text_rotation_ = rhs.text_rotation_;
	text_position_ = rhs.text_position_;
	align_point_ = rhs.align_point_;
  //
	dim_style_val_  = rhs.dim_style_val_  ;
	text_style_val_ = rhs.text_style_val_ ;

  ////clone时，不复制show_record_
  //show_record_ = rhs.show_record_;
  //show_change_ = rhs.show_change_;
  show_change_ = true;

  //txt_change_=rhs.txt_change_;
  //txt_record_=rhs.txt_record_;
  txt_change_=true;
  txt_record_=rhs.txt_record_;

  return *this;
}
Dimension::~Dimension()
{
  destory(show_record_);
}
void Dimension::load_me(File& in)
{
	in  >> dim_style_name_ 
      >> dim_text_ 
      >> text_rotation_;
	text_position_.load(in);
	int TextAlignFlag;
	in >> TextAlignFlag;
	align_point_ = (Text::AlignPt)TextAlignFlag;

  txt_change(true);
  show_change(true);
}
void Dimension::save_me(const File& out) const
{
	out << dim_style_name_ 
      << dim_text_ 
      << text_rotation_;
	text_position_.save(out);
	int TextAlignFlag = align_point_;
	out << TextAlignFlag;

}
void Dimension::save_luame(std::ofstream &out,int tab_num)
{
	lua::string_save(out,"dim_style_name_",dim_style_name_,tab_num);
	lua::string_save(out,"dim_text_",dim_text_,tab_num);
	lua::double_save(out,"text_rotation_",text_rotation_,tab_num);
	int align = align_point_;
	lua::int_save(out,"TextAlignFlag",align,tab_num);

	text_position_.save_lua(out,"text_position_",tab_num);
	dim_style_val_.save_lua(out,"dim_style_val_",tab_num);
}

void Dimension::open_luame(lua_State *l)
{
  std::string temp;
  get_value(string, l, temp, "dim_style_name_");

  dim_style_name_ = temp;

  get_value(string, l, temp, "dim_text_");
   dim_text_ = temp;
 get_value(number, l, text_rotation_, "text_rotation_");
  int align = 0;
  get_value(number, l, align, "TextAlignFlag");
  align_point_ = (Text::AlignPt)align;
  
  text_position_.open_lua(l, "text_position_");
 	dim_style_val_.open_lua(l,"dim_style_val_");
 
}
void Dimension::get_str_dim()
{
	//DIM//////////////////////////////////////////////////////////
	rei_add_str(NULL,"dim_style_name_",dim_style_name_.c_str());
	rei_add_str(NULL,"dim_text_",dim_text_.c_str());

	rei_add_float(NULL,"text_rotation_",text_rotation_);
	rei_add_int(NULL,"align_point_",align_point_);

	//DIM STYLE//////////////////////////////////////////////////////////
	rei_add_str(NULL,"dim_style_val_.name_",dim_style_val_.name().c_str());
	rei_add_str(NULL,"dim_style_val_.text_style_",dim_style_val_.text_style_name().c_str());
	rei_add_float(NULL,"dim_style_val_.text_precision_",dim_style_val_.text_precision());
	rei_add_int(NULL,"dim_style_val_.decimal_place_",dim_style_val_.decimal_place());
	rei_add_int(NULL,"dim_style_val_.decimal_addends_",dim_style_val_.decimal_addends());
	rei_add_float(NULL,"dim_style_val_.extendstartoff_",dim_style_val_.extend_start_off());
	rei_add_float(NULL,"dim_style_val_.extendendoff_",dim_style_val_.extend_end_off());
	rei_add_float(NULL,"dim_style_val_.start_dim_length_",dim_style_val_.start_dim_length());
	rei_add_float(NULL,"dim_style_val_.end_dim_length_",dim_style_val_.end_dim_length());
	rei_add_int(NULL,"dim_style_val_.arrowstyle_",dim_style_val_.arrow_style());
	rei_add_float(NULL,"dim_style_val_.arrowsize_",dim_style_val_.arrow_size());
	rei_add_int(NULL,"dim_style_val_.arrow_num_",dim_style_val_.arrow_num());
	rei_add_int(NULL,"dim_style_val_.tf_",dim_style_val_.txt_frame());
	rei_add_int(NULL,"dim_style_val_.tp_",dim_style_val_.text_pos());
	rei_add_float(NULL,"dim_style_val_.text_hight_",dim_style_val_.text_height());
	rei_add_int(NULL,"dim_style_val_.text_frame_color_",dim_style_val_.text_frame_color());
	rei_add_int(NULL,"dim_style_val_.text_color_",dim_style_val_.text_color());
	rei_add_int(NULL,"dim_style_val_.line_color_",dim_style_val_.line_color());
	

}
void Dimension::set_from_str_dim()
{
	//DIM//////////////////////////////////////////////////////////
	dim_style_name_ = rei_get("dim_style_name_");
	dim_text_ = rei_get("dim_text_");
	text_rotation_ = atof(rei_get("text_rotation_"));
	int align_point = atoi(rei_get("align_point_"));
	align_point_ = (Text::AlignPt)align_point;
	//DIM STYLE//////////////////////////////////////////////////////////
	dim_style_val_.name(rei_get("dim_style_val_.name_"));
	dim_style_val_.text_style_name(rei_get("dim_style_val_.text_style_name"));
	dim_style_val_.text_precision(atof(rei_get("dim_style_val_.text_precision_")));
	dim_style_val_.decimal_place(atoi(rei_get("dim_style_val_.decimal_place_")));
	dim_style_val_.decimal_addends(rei_get("dim_style_val_.decimal_addends_"));
	dim_style_val_.extend_start_off(atof(rei_get("dim_style_val_.extendstartoff_")));
	dim_style_val_.extend_end_off(atof(rei_get("dim_style_val_.extendendoff_")));
	dim_style_val_.start_dim_length(atof(rei_get("dim_style_val_.start_dim_length_")));
	dim_style_val_.end_dim_length(atof(rei_get("dim_style_val_.end_dim_length_")));
	dim_style_val_.arrow_style((Dimension_Style::Arrow)(atoi(rei_get("dim_style_val_.arrowstyle_"))));
	dim_style_val_.arrow_size(atoi(rei_get("dim_style_val_.arrowsize_")));
	dim_style_val_.arrow_num(atoi(rei_get("dim_style_val_.arrow_num_")));
	dim_style_val_.txt_frame((Dimension_Style::Txt_Frame)atoi(rei_get("dim_style_val_.tf_")));

	dim_style_val_.text_pos((Dimension_Style::TextPos)atoi(rei_get("dim_style_val_.tp_")));
	dim_style_val_.text_height(atof(rei_get("dim_style_val_.text_hight_")));
	dim_style_val_.text_frame_color(atoi(rei_get("dim_style_val_.text_frame_color_")));
	dim_style_val_.text_color(atoi(rei_get("dim_style_val_.text_color_")));
	dim_style_val_.line_color(atoi(rei_get("dim_style_val_.line_color_")));	
}

void Dimension::get_str_dim_sub(char *name)
{
	char s[MAX_REDIS_STR];
	//DIM//////////////////////////////////////////////////////////
	sprintf(s,"%s.dim_style_name_",name);
	rei_add_str(NULL,"dim_style_name_",dim_style_name_.c_str());
	sprintf(s,"%s.dim_text_",name);
	rei_add_str(NULL,"dim_text_",dim_text_.c_str());
	sprintf(s,"%s.text_rotation_",name);
	rei_add_float(NULL,"text_rotation_",text_rotation_);
	sprintf(s,"%s.align_point_",name);
	rei_add_int(NULL,"align_point_",align_point_);

	//DIM STYLE//////////////////////////////////////////////////////////
	sprintf(s,"%s.dim_style_val_.name_",name);
	rei_add_str(NULL,"dim_style_val_.name_",dim_style_val_.name().c_str());
	sprintf(s,"%s.dim_style_val_.text_style_",name);
	rei_add_str(NULL,"dim_style_val_.text_style_",dim_style_val_.text_style_name().c_str());
	sprintf(s,"%s.dim_style_val_.text_precision_",name);
	rei_add_float(NULL,"dim_style_val_.text_precision_",dim_style_val_.text_precision());
	sprintf(s,"%s.dim_style_val_.decimal_place_",name);
	rei_add_int(NULL,"dim_style_val_.decimal_place_",dim_style_val_.decimal_place());
	sprintf(s,"%s.dim_style_val_.decimal_addends_",name);
	rei_add_int(NULL,"dim_style_val_.decimal_addends_",dim_style_val_.decimal_addends());
	sprintf(s,"%s.dim_style_val_.extendstartoff_",name);
	rei_add_float(NULL,"dim_style_val_.extendstartoff_",dim_style_val_.extend_start_off());
	sprintf(s,"%s.dim_style_val_.extendendoff_",name);
	rei_add_float(NULL,"dim_style_val_.extendendoff_",dim_style_val_.extend_end_off());
	sprintf(s,"%s.dim_style_val_.start_dim_length_",name);
	rei_add_float(NULL,"dim_style_val_.start_dim_length_",dim_style_val_.start_dim_length());
	sprintf(s,"%s.dim_style_val_.end_dim_length_",name);
	rei_add_float(NULL,"dim_style_val_.end_dim_length_",dim_style_val_.end_dim_length());
	sprintf(s,"%s.dim_style_val_.arrowstyle_",name);
	rei_add_int(NULL,"dim_style_val_.arrowstyle_",dim_style_val_.arrow_style());
	sprintf(s,"%s.dim_style_val_.arrowsize_",name);
	rei_add_float(NULL,"dim_style_val_.arrowsize_",dim_style_val_.arrow_size());
	sprintf(s,"%s.dim_style_val_.arrow_num_",name);
	rei_add_int(NULL,"dim_style_val_.arrow_num_",dim_style_val_.arrow_num());
	sprintf(s,"%s.dim_style_val_.tf_",name);
	rei_add_int(NULL,"dim_style_val_.tf_",dim_style_val_.txt_frame());
	sprintf(s,"%s.dim_style_val_.tp_",name);
	rei_add_int(NULL,"dim_style_val_.tp_",dim_style_val_.text_pos());
	sprintf(s,"%s.dim_style_val_.text_hight_",name);
	rei_add_float(NULL,"dim_style_val_.text_hight_",dim_style_val_.text_height());
	sprintf(s,"%s.dim_style_val_.text_frame_color_",name);
	rei_add_int(NULL,"dim_style_val_.text_frame_color_",dim_style_val_.text_frame_color());
	sprintf(s,"%s.dim_style_val_.text_color_",name);
	rei_add_int(NULL,"dim_style_val_.text_color_",dim_style_val_.text_color());
	sprintf(s,"%s.dim_style_val_.line_color_",name);
	rei_add_int(NULL,"dim_style_val_.line_color_",dim_style_val_.line_color());
	

}
void Dimension::set_from_str_dim_sub(char *name)
{
	char s[MAX_REDIS_STR];
	//DIM//////////////////////////////////////////////////////////
	sprintf(s,"%s.dim_style_name_",name);
	dim_style_name_ = rei_get("dim_style_name_");
	sprintf(s,"%s.dim_text_",name);
	dim_text_ = rei_get("dim_text_");
	sprintf(s,"%s.text_rotation_",name);
	text_rotation_ = atof(rei_get("text_rotation_"));
	sprintf(s,"%s.align_point_",name);
	int align_point = atoi(rei_get("align_point_"));
	align_point_ = (Text::AlignPt)align_point;
	//DIM STYLE//////////////////////////////////////////////////////////
	sprintf(s,"%s.dim_style_val_.name_",name);
	dim_style_val_.name(rei_get("dim_style_val_.name_"));
	sprintf(s,"%s.dim_style_val_.text_style_name",name);
	dim_style_val_.text_style_name(rei_get("dim_style_val_.text_style_name"));
	sprintf(s,"%s.dim_style_val_.text_precision_",name);
	dim_style_val_.text_precision(atof(rei_get("dim_style_val_.text_precision_")));
	sprintf(s,"%s.dim_style_val_.decimal_place_",name);
	dim_style_val_.decimal_place(atoi(rei_get("dim_style_val_.decimal_place_")));
	sprintf(s,"%s.dim_style_val_.decimal_addends_",name);
	dim_style_val_.decimal_addends(rei_get("dim_style_val_.decimal_addends_"));
	sprintf(s,"%s.dim_style_val_.extendstartoff_",name);
	dim_style_val_.extend_start_off(atof(rei_get("dim_style_val_.extendstartoff_")));
	sprintf(s,"%s.dim_style_val_.extendendoff_",name);
	dim_style_val_.extend_end_off(atof(rei_get("dim_style_val_.extendendoff_")));
	sprintf(s,"%s.dim_style_val_.start_dim_length_",name);
	dim_style_val_.start_dim_length(atof(rei_get("dim_style_val_.start_dim_length_")));
	sprintf(s,"%s.dim_style_val_.end_dim_length_",name);
	dim_style_val_.end_dim_length(atof(rei_get("dim_style_val_.end_dim_length_")));
	sprintf(s,"%s.dim_style_val_.arrowstyle_",name);
	dim_style_val_.arrow_style((Dimension_Style::Arrow)(atoi(rei_get("dim_style_val_.arrowstyle_"))));
	sprintf(s,"%s.dim_style_val_.arrowsize_",name);
	dim_style_val_.arrow_size(atoi(rei_get("dim_style_val_.arrowsize_")));
	sprintf(s,"%s.dim_style_val_.arrow_num_",name);
	dim_style_val_.arrow_num(atoi(rei_get("dim_style_val_.arrow_num_")));
	sprintf(s,"%s.dim_style_val_.tf_",name);
	dim_style_val_.txt_frame((Dimension_Style::Txt_Frame)atoi(rei_get("dim_style_val_.tf_")));

	sprintf(s,"%s.dim_style_val_.tp_",name);
	dim_style_val_.text_pos((Dimension_Style::TextPos)atoi(rei_get("dim_style_val_.tp_")));
	sprintf(s,"%s.dim_style_val_.text_hight_",name);
	dim_style_val_.text_height(atof(rei_get("dim_style_val_.text_hight_")));
	sprintf(s,"%s.dim_style_val_.text_frame_color_",name);
	dim_style_val_.text_frame_color(atoi(rei_get("dim_style_val_.text_frame_color_")));
	sprintf(s,"%s.dim_style_val_.text_color_",name);
	dim_style_val_.text_color(atoi(rei_get("dim_style_val_.text_color_")));
	sprintf(s,"%s.dim_style_val_.line_color_",name);
	dim_style_val_.line_color(atoi(rei_get("dim_style_val_.line_color_")));	
}
void Dimension::dim_text(std::string text)			
{
  txt_change(true);
  show_change(true);
  dim_text_ = text;
}
void Dimension::text_position(const Point& pos)
{
  txt_change(true);
  show_change(true);
  text_position_ = pos;
}
void Dimension::text_rotation(Float rot)			
{
  txt_change(true);
  show_change(true);
  text_rotation_ = rot;
} 
void Dimension::text_normal(const Normal& nor)
{
  txt_change(true);
  show_change(true);
	text_rotation_ = nor.angle_x_axis_two_pi();
}
void Dimension::align_point(Text::AlignPt align)
{
  txt_change(true);
  show_change(true);
  align_point_ = align;
  switch(align)
  {
  case Text::  left_bottom:
  case Text::center_bottom:
  case Text:: right_bottom:
    dim_style_val_.text_pos(Dimension_Style::UP);
    break;
  case Text::  left_center:
  case Text::center_center:
  case Text:: right_center:
    dim_style_val_.text_pos(Dimension_Style::CENTER);
    break;
  case Text::  left_top:
  case Text::center_top:
  case Text:: right_top:
    dim_style_val_.text_pos(Dimension_Style::DOWN);
    break;
  }
}

void Dimension::dim_style_name(std::string style_name)
{
  txt_change(true);
  show_change(true);
  dim_style_name_ = style_name;
  set_dim_style(dim_style_name_);
}
void Dimension::dim_style_val(Dimension_Style style_val)
{
  txt_change(true);
  show_change(true);
  dim_style_val_ = style_val;
}
void Dimension::set_dim_style(const Dimension_Style& style)
{
  dim_style_val_ = style;
  show_change(true);
  txt_change(true);
}
void Dimension::set_dim_style(std::string style_name)
{
  dim_style_name_ = style_name;
  assert(static_current_db_);
  Dimension_Style* ds=0;
  static_current_db_->get_dimensionstyle(ds,style_name);
  assert(ds);
  dim_style_val_ = *ds;
  show_change(true);
  txt_change(true);
}

void Dimension::txt_change(bool b)const
{
  Dimension * the = const_cast<Dimension*>(this);
  the->txt_change_=b;
  the->show_change(true);
}

void Dimension::txt_record(const Text& txt)const
{
  Dimension * the = const_cast<Dimension*>(this);
  the->txt_record_=txt;
  txt_change(false);
}


  ////内部创建内存，需外部释放
void Dimension::get_text_show(Text& text) const
{
  if(txt_change_){
	  text.set_database(static_current_db_);
    //align_point_ = get_text_align();
	  text.align_point(get_text_align());
	  text.rotation(text_rotation_);
	  text.setdata(text_position_,dim_text_);
	  text.color_index(dim_style_val_.text_color());

    dim_style_val_.get_text(text);

    txt_record(text);
  }
  else{
    text=txt_record_;
  }
  

}
  ////内部创建内存，需外部释放
void Dimension::get_text_frame_show(Text& text, std::vector<Entity*>& es) const
{
  get_text_show(text);
	dim_style_val_.get_text_frame(text, es);

//#ifdef _DEBUG
////  Point pts[4];
////  text.real_box_point(pts);
//  const std::vector<Point>& pts = text.real_box_point();
//  Line * ln = NULL;
//  ln=Line::create_me();
//  ln->setdata(pts[0],pts[1]);
//  es.push_back(ln);
//  ln=Line::create_me();
//  ln->setdata(pts[1],pts[2]);
//  es.push_back(ln);
//  ln=Line::create_me();
//  ln->setdata(pts[2],pts[3]);
//  es.push_back(ln);
//  ln=Line::create_me();
//  ln->setdata(pts[3],pts[0]);
//  es.push_back(ln);
//#endif


//	return true;
}
  ////内部创建内存，需外部释放
int  Dimension::get_text_line_show(const Text& text,std::vector<Line*>& lines) const
{

	const Dimension_Style* ds=&dim_style_val_;
	ds->get_text_line(text,lines);
	for(int i=0;i<lines.size();++i){
		lines[i]->line_style(line_style());
		//lines[i]->color_index(dim_style_val_.text_frame_color());
	}
	//return num;
  return 0;
}
  ////内部创建内存，需外部释放
int  Dimension::get_text_circle_show(const Text& text,std::vector<Circle*>& circles) const
{
	const Dimension_Style* ds=&dim_style_val_;
	ds->get_text_circle(text,circles);
	for(int i=0;i<circles.size();++i){
		circles[i]->line_style(line_style());
		//circles[i]->color_index(dim_style_val_.text_frame_color());
	}
	//return num;
  return 0;
} 
  ////内部创建内存，需外部释放
int  Dimension::get_text_arc_show(const Text& text,std::vector<RArc*>& arcs) const
{
	const Dimension_Style* ds=&dim_style_val_;
	ds->get_text_arc(text,arcs);
	for(int i=0;i<arcs.size();++i){
		arcs[i]->line_style(line_style());
		//arcs[i]->color_index(dim_style_val_.text_frame_color());
	}
	//return num;
  return 0;
}
Text::AlignPt Dimension::get_text_align()const
{
  switch(dim_style_val_.text_pos())
  {
  case Dimension_Style::UP:
    return Text::center_bottom;
    break;
  case Dimension_Style::CENTER:
    return Text::center_center;
    break;
  case Dimension_Style::DOWN:
    return Text::center_top;
    break;
  }
  return Text::center_center;
}
Text::AlignPt Dimension::align_point()const
{
  return get_text_align();
}

void Dimension::get_dim_style(Dimension_Style& style)const
{
  style = dim_style_val_;
}
void Dimension::get_dim_style(std::string& style_name)const
{
  style_name = dim_style_name_;
}

void	Dimension::color_index(int index)
{
  txt_change(true);
  show_change(true);
  Entity::color_index(index);
  dim_style_val_.line_color(index);
}
int	Dimension::color_index() const		
{
  return Entity::color_index();
}



void Dimension::transformbyme(const Matrix& mat)
{
//	REITRACE;
  txt_change(true);
  show_change(true);
	////TEXT
  ////rota
  dlhml::transformby2d_radian(mat, text_rotation_);
  ////height
  Float hei = dim_style_val_.text_height();
  dlhml::transformby2d_distance(mat, hei);
  dim_style_val_.text_height(hei);
  ////position
  text_position_.transformby(mat);
//	REITRACE;
}

//BET 2009.09.10
//************************************************************************
//                   matrix's type                                      
//************************************************************************
//void Dimension::transformbyme(const Matrix& mat)
//{
//	REITRACE;
//  txt_change(true);
//  show_change(true);
//  ////TEXT
//  ////rota
//
//	REITRACE;
//  if(mat.mat_type()==ZRAOTA_MAT){
////		ReiTrace::out("text_rotation=",text_rotation_);
//    text_rotation_ += mat.rota_radian();
//	REITRACE;
////		ReiTrace::out("text_rotation=",text_rotation_);
//    std_radian(text_rotation_);
//	REITRACE;
//
//  }
//	REITRACE;
//
//  ////height
//  Float hei = dim_style_val_.text_height();
//  hei *= mat.value(0,0);
//  dim_style_val_.text_height(hei);
//	REITRACE;
//  ////position
//  text_position_.transformby(mat);
//	REITRACE;
//}
//TER

void Dimension::intersectme(const Entity& e , std::vector<Point>& pts)const
{
  if(&e == this){
    return;
  }
  std::vector<Entity*> es;
  get_line(es);
  int i=0;
  for(i=0;i<es.size();i++){
    es[i]->intersect(e, pts);
  }
  destory(es);
}
void Dimension::intersectme(const Line  & ln, std::vector<Point>& pts)const
{
//Entity::intersectme(ln,pts);
  std::vector<Entity*> es;
  get_line(es);
  int i=0;
  for(i=0;i<es.size();i++){
    es[i]->intersect(ln, pts);
  }
  destory(es);
}
void Dimension::intersectme(const RArc  & ac, std::vector<Point>& pts)const
{
//Entity::intersectme(ac,pts);
  std::vector<Entity*> es;
  get_line(es);
  int i=0;
  for(i=0;i<es.size();i++){
    es[i]->intersect(ac, pts);
  }
  destory(es);
}
void Dimension::intersectme(const Circle& cr, std::vector<Point>& pts)const
{
//Entity::intersectme(cr,pts);
  std::vector<Entity*> es;
  get_line(es);
  int i=0;
  for(i=0;i<es.size();i++){
    es[i]->intersect(cr, pts);
  }
  destory(es);
}

bool Dimension::intersectme(const Rect& rect) const
{
	std::vector<Entity*> es;
	get_show(es);

	bool myresult = false;
  int i=0;
  for(i=0;i<es.size();i++){
    if(es[i]->intersect(rect)){
			myresult = true;
			break;
		}
  }
	dlhml::destory(es);
	return myresult;
}
bool Dimension::envelopme(const Rect& rect) const
{
	std::vector<Entity*> es;
	get_show(es);

	bool myresult = true;
  int i=0;
  for(i=0;i<es.size();i++){
    if(!es[i]->envelop(rect)){
			myresult = false;
			break;
		}
  }
	dlhml::destory(es);
	return myresult;
}


////lINE/ARC/CIRCLE不再单独实现
////DIMESION及其子类在Dimesion类实现,其子类不再单独实现
//bool Dimension::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
//  //SNAP 2009.07.02
//  if(&ent == this){
//    return false;
//  }
//  std::vector<Point> pts;
//  std::vector<Entity*> es;
//  this->get_line(es);
//  int i=0;
//  for(i=0;i<es.size();i++){
//    if(!es[i]){
//      continue;
//    }
//    es[i]->intersect(ent,pts);
//  }
//  dlhml::destory(es);
//  for(i=0;i<pts.size();i++){
//    if(pts[i].envelop(rect)){
//      pt = pts[i];
//      return true;
//    }
//  }
//  return false;
//}

void Dimension::drawme(Draw_Entity& out) const
{
  std::vector<Entity*>& es = get_show_record();
  //get_show(es);
  select(es,seled_);
  dlhml::draw(es,out,false);
  //destory(es);
}
void Dimension::xor_drawme(Draw_Entity& out) const
{
  std::vector<Entity*> es;
  get_show(es);
  select(es,seled_);
  dlhml::draw(es,out,true);
  dlhml::destory(es);
}
//void Dimension::drawme(Draw_Entity& out) const
//{
//  std::vector<Entity*> es;
//  get_show(es);
//  select(es,seled_);
//  dlhml::draw(es,out,false);
//  destory(es);
//}
//void Dimension::xor_drawme(Draw_Entity& out) const
//{
//  std::vector<Entity*> es;
//  get_show(es);
//  select(es,seled_);
//  dlhml::draw(es,out,true);
//  destory(es);
//}

void Dimension::show_change(bool b)const
{
  Dimension * the = const_cast<Dimension*>(this);
  the->show_change_=b;
  the->box_change(true);
}

void Dimension::show_record()const
{
  if(show_change_){
    Dimension * the = const_cast<Dimension*>(this);
    destory(the->show_record_);
    get_show(the->show_record_);
    show_change(false);
  }
}
std::vector<Entity*>& Dimension::get_show_record()const
{
  Dimension * the = const_cast<Dimension*>(this);
  the->show_record();
  return the->show_record_;
}


Rect Dimension::calc_box2d() const
{
  Rect box;

	dlhml::box2d(box, get_show_record());
//  Entity_Calculate calc;
//  calc.get_ents_rect(box,get_show_record());
  return box;
}


//namespace
}
