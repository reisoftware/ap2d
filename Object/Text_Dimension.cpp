// Text_Dimension.cpp: implementation of the Text_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Text_Dimension.h"

#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Visitor.h"

#include "Text.h"
#include "Line.h"
#include "File.h"

#include "Matrix_d.h"
#include "Entity_Snap_Implement.h"
#include "Entity_Calculate.h"
#include "Global.h"

#include "getrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Text_Dimension,Dimension)
Text_Dimension::Text_Dimension()
MCT_INIT1("Text_Dimension")
{
	//dim_content_ = NULL;
	dim_text("TXT");
	dim_style_val_.txt_frame(Dimension_Style::ArrowEdge);
}
Text_Dimension::Text_Dimension(const Text_Dimension& rhs)
:Dimension(rhs)
MCT_INIT2("Text_Dimension")
{
//	dim_content_ = NULL;
//	string_copy(dim_content_,rhs.dim_content_);
	dim_sign_ = rhs.dim_sign_;
}
Text_Dimension& Text_Dimension::operator=(const Text_Dimension& rhs)
{
	Dimension::operator =(rhs);
//	dim_content_ = NULL;
	dim_sign_ = rhs.dim_sign_;
	return *this;
}
Text_Dimension::~Text_Dimension()
{

}
bool Text_Dimension::visit(Visitor& v)
{
  show_change(true);
	return v.Visit_Text_Dimension(*this);
}
void Text_Dimension::loadme(File& in)
{
	load_me(in);
	color_fact_.load(in);
	in>>dim_sign_;
}
void Text_Dimension::saveme(const File& out) const
{
	save_me(out);
	color_fact_.save(out);
	out<<dim_sign_;
}
void Text_Dimension::save_luame(std::ofstream &out,int tab_num)
{
	Dimension::save_luame(out,tab_num);
	lua::string_save(out,"dim_sign_",dim_sign_,tab_num);
	color_fact_.save_lua(out,"color_fact_",tab_num);

}
void Text_Dimension::open_luame(lua_State *l)  
{
	TRACE_OUT("Text_Dimension open in open_luame()\n");
	Dimension::open_luame(l);
	std::string temp;
	get_value(number,l,temp,"dim_sign_");
	(dim_sign_ =temp.c_str());
	txt_change(true);

}

//void Text_Dimension::dim_content(std::string dim_content)
//{
// txt_change(true);
// string_copy(dim_content_,dim_content);
//}
//std::string Text_Dimension::dim_content() const
//{
//	return dim_content_;
//}
void Text_Dimension::dim_sign(std::string dim_sign)
{
 txt_change(true);
 dim_sign_ = dim_sign;
}
std::string Text_Dimension::dim_sign() const
{
	return dim_sign_;
}

void Text_Dimension::edit_propertyme(const Edit_Entity& edit)
{
  show_change(true);
//	edit.edit_text_dim(*this);
}

//void Text_Dimension::drawme(Draw_Entity& out) const
//{
//	//out.draw_text_dim(*this);
//
//  std::vector<Entity*> es;
//  get_show(es);
//  select(es,seled_);
//  dlhml::draw(es,out,false);
//  destory(es);
//}
//void Text_Dimension::xor_drawme(Draw_Entity& out) const
//{
//	//out.xor_draw_text_dim(*this);
//
//  std::vector<Entity*> es;
//  get_show(es);
//  select(es,seled_);
//  dlhml::draw(es,out,true);
//  destory(es);
//}

errorinfo Text_Dimension::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Text_Dimension::transformbyme(const Matrix& mat)
{
//	REITRACE;
  show_change(true);
  Dimension::transformbyme(mat);
//  ////TEXT
//  ////rota
//  if(mat.mat_type()==RAOTA_MAT){
//    text_rotation_ += mat.rota_radian();
//    std_radian(text_rotation_);
//  }
//  ////height
//  Float hei = dim_style_val_.text_height();
//  hei *= mat.value(0,0);
//  dim_style_val_.text_height(hei);
//	text_position_.transformby(mat);
}
void Text_Dimension::drag_startme(const Matrix& mat)
{
  show_change(true);
}
void Text_Dimension::drag_endme(const Matrix& mat)
{
  show_change(true);
}

Entity* Text_Dimension::cloneme() const
{
	return new Text_Dimension(*this);
}

void Text_Dimension::closeme()
{
	delete this;
}

bool Text_Dimension::intersectme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
	return text.intersect(rect);
}
bool Text_Dimension::envelopme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
	return text.envelop(rect);
}

Rect Text_Dimension::calc_box2d() const
{
	Rect box2d_;
	Text text;
	get_text_show(text);
	std::vector<Entity*> ents;
	ents.push_back(&text);

	dlhml::box2d(box2d_, ents);
//	Entity_Calculate calc;
//	calc.get_ents_rect(box2d_,ents);
	return box2d_;
}

//bool Text_Dimension::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////	Entity_Snap_Implement<Text_Dimension> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Text_Dimension::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}
//09.6.22
void Text_Dimension::setctrl(const std::vector<Point>& pts)
{
  show_change(true);
  if(pts.size() != 1){
    return;
  }
	text_position_ = pts[0];
}
void Text_Dimension::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(text_position_);
}
int  Text_Dimension::pt_count()const
{
  return 1;
}
void Text_Dimension::setdrag(const std::vector<Point>& pts, int index)
{
  if(pts.empty()){
    return;
  }
  text_position(pts[0]);
}
void Text_Dimension::getdrag(std::vector<Point>& pts)const
{
  pts.push_back(text_position_);
}

void Text_Dimension::get_show(std::vector<Entity*>& es)const
{
  //TEXT AND ITS FRAME
  Text * txt = Text::create_me();
  get_text_frame_show(*txt, es);
  es.push_back(txt);
}


}//namespace
