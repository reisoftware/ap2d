
#include "stdafx.h"
#include "Text.h"
#include "DrawEntity.h"
#include "Entity_Snap_Implement.h"
#include "File.h"
#include "Database.h"
#include "Text_Style.h"
#include "Matrix_d.h"
#include "Line.h"
#include "Edit_Entity.h"
#include <cassert>
#include "Visitor.h"
#include "Point.h"
#include "Entity_Calculate.h"

#include "Global.h"

#include "fstream"
#include "getrace.h"
#include "encode.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Text,Entity)
void Text::init()
{
//  myclass_="Text";

	align_point_ = center_center;
	width_factor_ = 0.0;
	dxf_height_ = 20;
	rotation_radian_ = 0;

  real_box_change(true);
  std_sz_change(true);
  std_cx_record_=-1;
  std_cy_record_=-1;
}
Text::Text()
MCT_INIT1("Text")
{
	init();
	//string_copy(style_name_,"Standard");
  style_name("Standard");
  //std_size();
}
Text::Text(const Point& _pos,std::string _content)
MCT_INIT1("Text")
{
	init();
	postion_ = _pos;
	style_name("Standard");
	content_ = _content;

  //std_size();
}
Text::Text(const Point& _pos,std::string _content,std::string _font)
MCT_INIT1("Text")
{
	init();
	postion_ = _pos;
	style_name("Standard");
	content_ = _content;
	font_ = _font;

  //std_size();
}
Text::Text(const Text& rhs)
:Entity(rhs)
MCT_INIT2("Text")
{
	init();
	align_point_ = rhs.align_point_;

	content_ = rhs.content_;
	font_ = rhs.font_;
	style_name_ = rhs.style_name_;

	width_factor_ = rhs.width_factor_;
	dxf_height_ = rhs.dxf_height_;
	rotation_radian_ = rhs.rotation_radian_;
	postion_ = rhs.postion_;

  style_val_ = rhs.style_val_;
  //std_size_  = rhs.std_size_;

  std_sz_change_=rhs.std_sz_change_;
  std_cx_record_=rhs.std_cx_record_;
  std_cy_record_=rhs.std_cy_record_;
  
  real_es_changed_ = rhs.real_es_changed_;
	real_box_record_ = rhs.real_box_record_;
  //std_size();
}
Text& Text::operator=(const Text& rhs)
{
	Entity::operator =(rhs);
	if(this == &rhs)
		return *this;
	align_point_ = rhs.align_point_;

	content_ = rhs.content_;
	font_ = rhs.font_;
	style_name_ = rhs.style_name_;

	width_factor_ = rhs.width_factor_;
	dxf_height_ = rhs.dxf_height_;
	rotation_radian_ = rhs.rotation_radian_;
	postion_ = rhs.postion_;

  style_val_ = rhs.style_val_;
  //std_size_  = rhs.std_size_;

  std_sz_change_=rhs.std_sz_change_;
  std_cx_record_=rhs.std_cx_record_;
  std_cy_record_=rhs.std_cy_record_;

  real_es_changed_ = rhs.real_es_changed_;
	real_box_record_ = rhs.real_box_record_;
  //std_size();
	return *this;
}
Text::~Text()
{
}
bool Text::visit(Visitor& v)
{
	return v.Visit_Text(*this);
}

void Text::loadme(File& in)
{
	int TextAlignFlag;
	in >> TextAlignFlag;
	align_point_ = (AlignPt)TextAlignFlag;
	in >>content_
     >>font_
     >>style_name_
     >>width_factor_
     >>dxf_height_
     >>rotation_radian_;
	postion_  .load(in);
  //style_val_.load(in);
  style_name(style_name_);

  std_sz_change(true);
  real_box_change(true);
  //std_size();
}
void Text::saveme(const File& out) const
{
	int TextAlignFlag = align_point_;
	out << TextAlignFlag;
	out <<content_
      <<font_
      <<style_name_
      <<width_factor_
      <<dxf_height_
      <<rotation_radian_;
	postion_  .save(out);
  //style_val_.save(out);
}
static Text::AlignPt get_align_kind(int v)
{
	if(v == 1)
		return Text::AlignPt::left_top;
	else if(v == 2)
		return Text::AlignPt::left_center;
	else if(v == 3)
		return Text::AlignPt::left_bottom;
	else if(v == 4)
		return Text::AlignPt::center_top;
	else if(v == 5)
		return Text::AlignPt::center_center;
	else if(v == 6)
		return Text::AlignPt::center_bottom;
	else if(v == 7)
		return Text::AlignPt::right_top;
	else if(v == 8)
		return Text::AlignPt::right_center;
	else if(v == 9)
		return Text::AlignPt::right_bottom;
	else
		return Text::AlignPt::center_center;
}
void Text::save_luame(std::ofstream &out,int tab_num)
{
	int TextAlignFlag = align_point_;
	lua::int_save(out,"align_point_",align_point_,tab_num);

	if(strcmp(content_.c_str(),"[")!=-1  || strcmp(content_.c_str(),"]")!=-1 )
		lua::string_save(out,"content_",content_,tab_num);
	else
		lua::string_save(out,"content_",content_,tab_num);

	lua::string_save(out,"font_",font_,tab_num);
	lua::string_save(out,"style_name_",style_name_,tab_num);
	lua::float_save(out,"width_factor_",width_factor_,tab_num);
	lua::float_save(out,"dxf_height_",dxf_height_,tab_num);
	lua::float_save(out,"rotation_radian_",rotation_radian_,tab_num);
	postion_.save_lua(out,"postion_",tab_num);

	
}

void Text::get_strme(char *out)
{
	rei_quit();

	rei_add_str(NULL,"kind","TEXT");

	get_str_ent();

	////////////////////////////////////////////////////////////

	rei_add_int(NULL,"align_point_",align_point_);
	rei_add_str(NULL,"content_",content_.c_str());
	rei_add_str(NULL,"font_",font_.c_str());
	rei_add_str(NULL,"style_name_",style_name_.c_str());

	rei_add_float(NULL,"width_factor_",width_factor_);
	rei_add_float(NULL,"dxf_height_",dxf_height_);
	rei_add_float(NULL,"rotation_radian_",rotation_radian_);

	
	rei_add_float(NULL,"postion_.x",postion_.x);
	rei_add_float(NULL,"postion_.y",postion_.y);
	rei_add_float(NULL,"postion_.z",postion_.z);

	rei_get_encode(out);
}

void Text::set_from_strme(char *in)
{
	rei_init(in);


	set_from_str_ent();

	////////////////////////////////////////////////////////////
	int align = atoi(rei_get("align_point_"));
	align_point_ = get_align_kind(align);
	content_ = rei_get("content_");
	font_ = rei_get("font_");
	style_name_ = rei_get("style_name_");
	width_factor_ = atof(rei_get("width_factor_"));
	dxf_height_ = atof(rei_get("dxf_height_"));
	rotation_radian_ = atof(rei_get("rotation_radian_"));
	
	postion_.x = atof(rei_get("postion_.x"));
	postion_.y = atof(rei_get("postion_.y"));
	postion_.z = atof(rei_get("postion_.z"));

	rei_quit();

//	color_ = 1;


}



void Text::open_luame(lua_State *l) 
{
	TRACE_OUT("Text open in open_luame()\n");
	int align;
	get_value(number,l,align,"align_point_");
	align_point_ = get_align_kind(align);

	std::string temp;
	get_value(string,l,temp,"content_");
	content_ = temp;
	get_value(string,l,temp,"font_");
	font_ = temp;
	get_value(string,l,temp,"style_name_");
	
	get_value(number,l,width_factor_,"width_factor_");
	get_value(number,l,dxf_height_,"dxf_height_");
	get_value(number,l,rotation_radian_,"rotation_radian_");

	postion_.open_lua(l,"postion_");

}


// void Text::lua_load(iLua_File &fin)
// {
// }
// 
// void Text::lua_save(oLua_File &fout)const
// {
// }

void Text::style_val(const Text_Style& s)
{
  style_val_ = s;
  //std_size();
  std_sz_change(true);
  real_box_change(true);
}
void Text::text(std::string cont)		      
{
  content_ = cont;
  //std_size();
  std_sz_change(true);
  real_box_change(true);
}
void Text::font(std::string name)		      
{
  font_ = name;
  //std_size();
  std_sz_change(true);
  real_box_change(true);
}
void Text::dxf_height(Float h)			        
{
  dxf_height_ = h;
  std_sz_change(true);
  real_box_change(true);
}
void Text::gdi_height(Float h)	           
{
  dxf_height(h/gdi_scale());
}


void Text::edit_propertyme(const Edit_Entity& edit)
{
	edit.edit_text(*this);
}

void Text::drawme(Draw_Entity& out) const
{
  //std::ofstream("D:/text_drawme");
	out.draw_text(*this);
}
void Text::xor_drawme(Draw_Entity& out) const
{
	out.xor_draw_text(*this);
}

errorinfo Text::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}

void Text::transformbyme(const Matrix& mat)
{
  std_sz_change(true);
  dlhml::transformby2d_radian(mat, rotation_radian_);
  dlhml::transformby2d_distance(mat, dxf_height_);
  postion_.transformby(mat);
}

//BET 2009.09.10
//************************************************************************
//          matrix's type                                                                        
//************************************************************************
//void Text::transformbyme(const Matrix& mat)
//{
//  std_sz_change(true);
//  dlhml::transformby2d(mat, rotation_radian_);
//  height_ *= mat.value(0,0);
//  postion_.transformby(mat);
//}
//TER

//BET 2009.09.10
//void Text::transformbyme(const Matrix& mat)
//{
//  std_sz_change(true);
//  dlhml::transformby2d(mat, rotation_radian_);
//  height_ *= mat.value(0,0);
//  postion_.transformby(mat);
//}
//TER


//BET 2009.09.10
//void Text::transformbyme(const Matrix& mat)
//{
//	REITRACE;
//  std_sz_change(true);
//  if(mat.mat_type()==ZRAOTA_MAT){
//    rotation_radian_ += mat.rota_radian();
//    std_radian(rotation_radian_);
//  }
//
////else if(mat.mat_type()==SCALE_MAT){
////  	height_ *= mat.value(0,0);
////    //height_ *= mat.scale_times();
////  }else if(mat.mat_type()==MOVE_MAT){
////  }
//  height_ *= mat.value(0,0);
//  postion_.transformby(mat);
//}
//TER

void Text::drag_startme(const Matrix& mat)
{
}
void Text::drag_endme(const Matrix& mat)
{
}

Entity* Text::cloneme() const
{
	return new Text(*this);
}

void Text::closeme()
{
	delete this;
}

void Text::setdata(const Point& pos,std::string cont)
{
  std_sz_change(true);
  //real_box_change(true);

  postion_ = pos;
  content_ = cont;

  //std_size();
}
void Text::setdata(const Point& pos,std::string cont,std::string name)
{
  std_sz_change(true);
  //real_box_change(true);

  postion_ = pos;
  content_ = cont;
  font_ = name;

  //std_size();
}
void Text::align_point(AlignPt pt)			
{
  std_sz_change(true);
  align_point_ = pt;
}
void Text::style_name(std::string s)			      
{
  style_name_ = s;

  assert(static_current_db_);
  Text_Style* ts;
  static_current_db_->get_textstyle(ts,style_name_);
  assert(ts);
  //style_val_=*ts;
  style_val(*ts);
}
void Text::width_factor(Float wf)			
{
  width_factor_ = wf;
}
void Text::position(const Point& pos)	
{
  postion_ = pos;
  real_box_change(true);
}
void Text::rotation(Float r)		        
{
  rotation_radian(r);
  real_box_change(true);
}
void Text::rotation_radian(Float r)    
{
  rotation_radian_ = r;
  real_box_change(true);
}
void Text::rotation_degree(Float r)    
{
  rotation_radian_ = dlhml::degree_2_radian(r);
  real_box_change(true);
}

std::string Text::text() const				        
{
  return content_;
}
std::string Text::font() const				        
{
  return font_;
}
Point Text::position() const						
{
  return postion_;
}
Float Text::rotation() const		        
{
  return rotation_radian();
}
Float Text::rotation_radian() const	    
{
  return rotation_radian_;
}
Float Text::rotation_degree() const	    
{
  Float deg = dlhml::radian_2_degree(rotation_radian_);
  return deg;
}
Text::AlignPt Text::align_point() const					
{
  return align_point_;
}

std::string Text::style_name()const				  
{
  return style_name_;
}
Text_Style Text::style_val ()const
{
  return style_val_;
}

Float Text::dxf_height() const			        
{
  return dxf_height_;
}
Float Text::gdi_height()const
{
  return text_height_dxf_2_gdi(dxf_height());
}

Float Text::width_factor() const				
{
  return width_factor_;
}


bool Text::intersectme(const Rect& rect) const
{
//  if( !(*content_)){
//    return postion_.envelop(rect);
//  }

  ////文本中心点在矩形内
  Point txt_cpt = center();
  if(txt_cpt.envelop(rect)){
    return true;
  }

//	Point pt[4];
//	real_box_point(pt);
  //const std::vector<Point>& pt = real_box_point();
	std::vector<Point> pt;
	real_box_pt(pt);
	assert(pt.size()>=4);


  ////真实包围框4条边与矩形相交
  Line line;
	line.setdata(pt[0],pt[1]);
	if(line.intersect(rect))
		return true;
	line.setdata(pt[1],pt[2]);
	if(line.intersect(rect))
		return true;
	line.setdata(pt[2],pt[3]);
	if(line.intersect(rect))
		return true;
	line.setdata(pt[3],pt[0]);
	if(line.intersect(rect))
		return true;


  Point selpt;
//  selpt.setdata(rect.xmin(),rect.ymin());
//  if(is_in(selpt, pt, 4)){
//    return true;
//  }
//  selpt.setdata(rect.xmin(),rect.ymax());
//  if(is_in(selpt, pt, 4)){
//    return true;
//  }
//  selpt.setdata(rect.xmax(),rect.ymax());
//  if(is_in(selpt, pt, 4)){
//    return true;
//  }
//  selpt.setdata(rect.xmax(),rect.ymin());
//  if(is_in(selpt, pt, 4)){
//    return true;
//  }


  ////矩形中心点在真实包围框内
  selpt.setdata((rect.xmin()+rect.xmax())/2,(rect.ymin()+rect.ymax())/2);
  if(is_in(selpt, pt)){
    return true;
  }
//  if(is_in(selpt, pt, 4)){
//    return true;
//  }

  ////整个文本包围盒选中
//  Rect box_rc=calc_box2d();
//  if(selpt.envelop(box_rc)){
//    return true;
//  }

	return false;
}
bool Text::envelopme(const Rect& rect) const
{
	return box2d().envelop(rect);
}

Rect Text::calc_box2d() const
{
	Rect box2d_;
//	Point pt[4];
//	real_box_point(pt);
//  const std::vector<Point>& pt = real_box_point();
	std::vector<Point> pt;
	real_box_pt(pt);
	int aaa = pt.size();
	assert(pt.size()>=4);
	box2d_.set_reverse_minmax();

	for(int i=0; i<4; ++i){
		box2d_.xmin(min(box2d_.xmin(),pt[i].x));
		box2d_.ymin(min(box2d_.ymin(),pt[i].y));
		box2d_.xmax(max(box2d_.xmax(),pt[i].x));
		box2d_.ymax(max(box2d_.ymax(),pt[i].y));
	}
	return box2d_;
}
HFONT	Text::get_font() const
{
	return style_val_.get_font(*this);
}
//BET 2009.08.12
//liming
//HFONT	Text::get_font() const
//{
//  assert(static_current_db_);
//  assert(style_);
//  Text_Style* ts=0;
//  static_current_db_->get_textstyle(ts,style_name_);
//  assert(ts);
//  return ts->get_font(*this);
//}
//TER
//better 2009.02.08
//void Text::a_word_size(SIZE& sz) const
//{
//	HFONT hFont = get_font();
//	HDC hDC = ::GetDC(NULL);
//	HFONT hOld = (HFONT)::SelectObject(hDC,hFont);
//	::GetTextExtentPoint32(hDC,content_,1,&sz);
//	::SelectObject(hDC,hOld);
//	::ReleaseDC(NULL,hDC);
//	::DeleteObject(hFont);
//}
//
  
//void Text::std_size_change(bool b)
//{
//  box_change(true);
//  std_size_change_=b;
//}
//
//void Text::std_size()const
//{
//
//  Text * this_obj = const_cast<Text*>(this);
//  this_obj->std_cx_=sz.cx;
//  this_obj->std_cy_=sz.cy;
//  this_obj->std_size_change(false);
//}

void Text::std_sz_change(bool b)const
{
  Text * the = const_cast<Text*>(this);
  the->std_sz_change_=b;
  the->real_es_changed_=true;
}
void Text::std_sz_record(Float cx, Float cy)const
{
  Text * the = const_cast<Text*>(this);
  the->std_cx_record_=cx;
  the->std_cy_record_=cy;
  std_sz_change(false);
}

void Text::horizontal_size(SIZE& sz) const
{
  if(std_sz_change_){
    if( strcmp(content_.c_str(),"")==0){
      sz.cx = 0;
      sz.cy = dlhml::text_height_dxf_2_gdi(dxf_height_);
    }else{
      //SIZE sz;
      HFONT hFont = get_font();
      HDC hDC = ::GetDC(NULL);
      HFONT hOld = (HFONT)::SelectObject(hDC,hFont);
      ::GetTextExtentPoint32(hDC,content_.c_str(),strlen(content_.c_str()),&sz);
      ::SelectObject(hDC,hOld);
      ::ReleaseDC(NULL,hDC);
      ::DeleteObject(hFont);
    }
    if(sz.cy<1){
      sz.cy = 1;
    }
    std_sz_record(sz.cx,sz.cy);
  }
  else{
    sz.cx=std_cx_record_;
    sz.cy=std_cy_record_;
  }
}
//BET 2009.08.12
//liming
//void Text::horizontal_size(SIZE& sz) const
//{
////  sz.cx=50;
////  sz.cy=20;
////  return;
//
//  HFONT hFont = get_font();
//  HDC hDC = ::GetDC(NULL);
//  HFONT hOld = (HFONT)::SelectObject(hDC,hFont);
//  ::GetTextExtentPoint32(hDC,content_,lstrlen(content_),&sz);
//  ::SelectObject(hDC,hOld);
//  ::ReleaseDC(NULL,hDC);
//  ::DeleteObject(hFont);
////  int sum=0;
////  for(int i=0;i<10000;i++){
////    sum+=i;
////  }
//}
//TER
void Text::horizontal_rect(Rect& rect) const
{
  SIZE size;
  horizontal_size(size);
  
  Point l_pos = postion_;
  
  switch(align_point_)
  {
  case left_top:
    rect.xmin(l_pos.x);
    rect.xmax(l_pos.x + size.cx);
    rect.ymin(l_pos.y - size.cy);
    rect.ymax(l_pos.y);
    break;
  case left_center:
    rect.xmin(l_pos.x);
    rect.xmax(l_pos.x + size.cx);
    rect.ymin(l_pos.y - size.cy/2.0);
    rect.ymax(l_pos.y + size.cy/2.0);
    break;
  case left_bottom:
    rect.xmin(l_pos.x);
    rect.xmax(l_pos.x + size.cx);
    rect.ymin(l_pos.y);
    rect.ymax(l_pos.y + size.cy);
    break;
  case center_top:
    rect.xmin(l_pos.x - size.cx/2.0);
    rect.xmax(l_pos.x + size.cx/2.0);
    rect.ymin(l_pos.y - size.cy);
    rect.ymax(l_pos.y);
    break;
  case center_center:
    rect.xmin(l_pos.x - size.cx/2.0);
    rect.xmax(l_pos.x + size.cx/2.0);
    rect.ymin(l_pos.y - size.cy/2.0);
    rect.ymax(l_pos.y + size.cy/2.0);
    break;
  case center_bottom:
    rect.xmin(l_pos.x - size.cx/2.0);
    rect.xmax(l_pos.x + size.cx/2.0);
    rect.ymin(l_pos.y);
    rect.ymax(l_pos.y + size.cy);
    break;
  case right_top:
    rect.xmin(l_pos.x - size.cx);
    rect.xmax(l_pos.x);
    rect.ymin(l_pos.y - size.cy);
    rect.ymax(l_pos.y);
    break;
  case right_center:
    rect.xmin(l_pos.x - size.cx);
    rect.xmax(l_pos.x);
    rect.ymin(l_pos.y - size.cy/2.0);
    rect.ymax(l_pos.y + size.cy/2.0);
    break;
  case right_bottom:
    rect.xmin(l_pos.x - size.cx);
    rect.xmax(l_pos.x);
    rect.ymin(l_pos.y);
    rect.ymax(l_pos.y + size.cy);
    break;
  default:
    break;
  }
  
  //<better 2009.02.08
  //  SIZE aws; // a word size
  //  a_word_size(aws);
  //  rect.xmin(rect.xmin() - aws.cx);
  //  rect.xmax(rect.xmax() + aws.cx);
  //>better 2009.02.08
}
//<liming 2009.02.08
//void Text::horizontal_rect(Rect& rect) const
//{
//	SIZE size;
//	horizontal_size(size);
//	Point l_pos = postion_;
//
//	switch(align_point_)
//	{
//	case left_top:
//		rect.xmin(l_pos.x);
//		rect.xmax(l_pos.x + size.cx);
//		rect.ymin(l_pos.y - size.cy);
//		rect.ymax(l_pos.y);
//		break;
//	case left_center:
//		rect.xmin(l_pos.x);
//		rect.xmax(l_pos.x + size.cx);
//		rect.ymin(l_pos.y - size.cy/2.0);
//		rect.ymax(l_pos.y + size.cy/2.0);
//		break;
//	case left_bottom:
//		rect.xmin(l_pos.x);
//		rect.xmax(l_pos.x + size.cx);
//		rect.ymin(l_pos.y);
//		rect.ymax(l_pos.y + size.cy);
//		break;
//	case center_top:
//		rect.xmin(l_pos.x - size.cx/2.0);
//		rect.xmax(l_pos.x + size.cx/2.0);
//		rect.ymin(l_pos.y - size.cy);
//		rect.ymax(l_pos.y);
//		break;
//	case center_center:
//		rect.xmin(l_pos.x - size.cx/2.0);
//		rect.xmax(l_pos.x + size.cx/2.0);
//		rect.ymin(l_pos.y - size.cy/2.0);
//		rect.ymax(l_pos.y + size.cy/2.0);
//		break;
//	case center_bottom:
//		rect.xmin(l_pos.x - size.cx/2.0);
//		rect.xmax(l_pos.x + size.cx/2.0);
//		rect.ymin(l_pos.y);
//		rect.ymax(l_pos.y + size.cy);
//		break;
//	case right_top:
//		rect.xmin(l_pos.x - size.cx);
//		rect.xmax(l_pos.x);
//		rect.ymin(l_pos.y - size.cy);
//		rect.ymax(l_pos.y);
//		break;
//	case right_center:
//		rect.xmin(l_pos.x - size.cx);
//		rect.xmax(l_pos.x);
//		rect.ymin(l_pos.y - size.cy/2.0);
//		rect.ymax(l_pos.y + size.cy/2.0);
//		break;
//	case right_bottom:
//		rect.xmin(l_pos.x - size.cx);
//		rect.xmax(l_pos.x);
//		rect.ymin(l_pos.y);
//		rect.ymax(l_pos.y + size.cy);
//		break;
//	default:
//		break;
//	}
//}
//>liming 2009.02.08
void Text::real_box_change(bool b)const
{
  Text * the = const_cast<Text*>(this);
  the->box_change(true);
  the->real_es_changed_=b;
}

// static void extend_height(std::vector<Point>& pts)
// {
//   Float oh = pts[1].y - pts[0].y;
//   Float eh = oh / 6;    ////上下各扩展1/6
//   pts[0].y -= eh;
//   pts[1].y += eh;
//   pts[2].y += eh;
//   pts[3].y -= eh;
// }

////输入txt
// void Text::extend_box(const Rect& rc, Rect& txt, Rect& box)const
// {
//   txt = box = rc;
//   Float txt_ymax = rc.ymax();
//   Float txt_ymin = rc.ymin();
//   Float box_ymax = rc.ymax();
//   Float box_ymin = rc.ymin();
//   Float oh = txt_ymax - txt_ymin;
//   Float eh = oh / 6;    ////上下各扩展1/6
// 
//   switch(align_point_){
//   case left_top:
//   case center_top:
//   case right_top:
//     txt_ymax -= eh*1;
//     txt_ymin -= eh*1;
//     box_ymax += eh*0;
//     box_ymin -= eh*2;
//     break;
//   case left_center:
//   case center_center:
//   case right_center:
//     txt_ymax -= eh*0;
//     txt_ymin -= eh*0;
//     box_ymax += eh*1;
//     box_ymin -= eh*1;
//     break;
//   case left_bottom:
//   case center_bottom:
//   case right_bottom:
//     txt_ymax += eh*1;
//     txt_ymin += eh*1;
//     box_ymax += eh*2;
//     box_ymin -= eh*0;
//     break;
//   }
//   txt.ymax(txt_ymax);
//   txt.ymin(txt_ymin);
//   box.ymax(box_ymax);
//   box.ymin(box_ymin);
// }

void Text::real_4pt(std::vector<Point>& pts) const//, bool extend_h
{
  //Point (&pt)[4]
  if(real_es_changed_){
    Text * the = const_cast<Text*>(this);
    std::vector<Point>& pt = the->real_box_record_;
    pt.resize(4);
    int bbb = pt.size();
//    if( !(*content_)){
//      pt[0]=postion_;
//      pt[1]=postion_;
//      pt[2]=postion_;
//      pt[3]=postion_;
//    }
//    
    Rect rect;
    horizontal_rect(rect);
//     Rect txt_rc, box_rc;
//     extend_box(rect, txt_rc, box_rc);
//     rect = extend_h ? box_rc : txt_rc;

    pt[0].setdata(rect.xmin(),rect.ymin());//LB     [1]┏──────┓[2]
    pt[1].setdata(rect.xmin(),rect.ymax());//LT        │            │
    pt[2].setdata(rect.xmax(),rect.ymax());//RT        │            │
    pt[3].setdata(rect.xmax(),rect.ymin());//RB     [0]┗──────┛[3]
    
    
    Matrix move,rmove,rotation;
    move.set_move(-postion_.x,-postion_.y,0);
    rotation.set_z_rotation_radian(rotation_radian_);
    rmove.set_move(postion_.x,postion_.y,0);
    for(int i=0; i<4; ++i){
      pt[i].transformby(move);
      pt[i].transformby(rotation);
      pt[i].transformby(rmove);
    }
    the->real_box_change(false);
  }
  pts = real_box_record_;
}

Line Text::dxf_base_line()const
{
  std::vector<Point> pts;
  real_box_pt(pts);
  assert(pts.size() >= 4);
  Float dis01 = pts[0].distanceto2d(pts[1]);
//   Float offdis = (1-dxf_height()/gdi_height())/2 * dis01;
  Float offdis = (gdi_height()-dxf_height())/2;
  Normal nor01;////[0]--->[1]
  nor01.set_data(pts[0], pts[1]);
  nor01.set_unit();
  Point s = pts[0].polarTo(offdis, nor01);
  Point e = pts[3].polarTo(offdis, nor01);

  ////缩短一个字节的(1-dxf/gdi)
  int count = strlen(content_.c_str());
  Float dis03 = pts[0].distanceto2d(pts[3]);
  Float singlew = dis03/count;
  Float cutdis = ( singlew-singlew*dxf_height()/gdi_height() )/2;
  Normal nor03;
  nor03.set_data(pts[0], pts[3]);
  nor03.set_unit();
  s = s.polarTo(cutdis, nor03);
  Normal nor30;
  nor30.set_data(pts[3], pts[0]);
  nor30.set_unit();
  e = e.polarTo(cutdis, nor30);

  Line ln(s, e);
  return ln;
}

Line Text::dxf_bottom_line()const
{
  std::vector<Point> pts;
  real_box_pt(pts);
  assert(pts.size() >= 4);
  Float dis01 = pts[0].distanceto2d(pts[1]);
//   Float offdis = (1-dxf_height()/gdi_height())/2 * dis01;
  Float offdis = (gdi_height()-dxf_height())/2;
  Normal nor01;////[0]--->[1]
  nor01.set_data(pts[0], pts[1]);
  nor01.set_unit();
  Point s = pts[0];//.polarTo(offdis, nor01);
  Point e = pts[3];//.polarTo(offdis, nor01);

  ////缩短一个字节的(1-dxf/gdi)
  int count = strlen(content_.c_str());
  Float dis03 = pts[0].distanceto2d(pts[3]);
  Float singlew = dis03/count;
  Float cutdis = ( singlew-singlew*dxf_height()/gdi_height() )/2;
  Normal nor03;
  nor03.set_data(pts[0], pts[3]);
  nor03.set_unit();
  s = s.polarTo(cutdis, nor03);
  Normal nor30;
  nor30.set_data(pts[3], pts[0]);
  nor30.set_unit();
  e = e.polarTo(cutdis, nor30);

  Line ln(s, e);
  return ln;
}

Line Text::center_line()const
{
  std::vector<Point> pts;
  real_box_pt(pts);
  assert(pts.size() >= 4);
  Point s = (pts[0]+pts[1])/2;
  Point e = (pts[2]+pts[3])/2;
  Line ln(s, e);
  return ln;
}


void Text::real_box_pt(std::vector<Point>& pts) const
{
  real_box_change(true);
  real_4pt(pts); //, true
}

// void Text::real_txt_pt(std::vector<Point>& pts) const
// {
//   real_box_change(true);
//   real_4pt(pts);//, false
// }

//BET 2009.08.12
//liming
//void Text::real_box_point(Point (&pt)[4]) const
//{
//  if(!content_ || !(*content_)){
//    pt[0]=postion_;
//    pt[1]=postion_;
//    pt[2]=postion_;
//    pt[3]=postion_;
//  }
//  
//  Rect rect;
//  horizontal_rect(rect);
//  pt[0].setdata(rect.xmin(),rect.ymin());
//  pt[1].setdata(rect.xmin(),rect.ymax());
//  pt[2].setdata(rect.xmax(),rect.ymax());
//  pt[3].setdata(rect.xmax(),rect.ymin());
//  
//  Matrix move,rmove,rotation;
//  move.set_move(-postion_.x,-postion_.y,0);
//  rotation.set_z_rotation(rotation_radian_);
//  rmove.set_move(postion_.x,postion_.y,0);
//  for(int i=0; i<4; ++i){
//    pt[i].transformby(move);
//    pt[i].transformby(rotation);
//    pt[i].transformby(rmove);
//  }
//}
//TER
void Text::left_top_point(Point& lt) const
{
	std::vector<Point> pt;
	real_box_pt(pt);
	assert(pt.size()>=4);
	lt = pt[1];
}
bool Text::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
//NOOK SNAP 2009.07.02
////Entity 统一实现
  return false;
//	Entity_Snap_Implement<Text> imp(*this);
//	return ent.snap_intersect_point_imp(pt,imp,rect);
}
bool Text::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}

void Text::setctrl(const std::vector<Point>& pts)
{
  real_box_change(true);

  if(pts.size()<1){
    return;
  }
  position(pts.front());
}
void Text::getctrl(std::vector<Point>& pts)const
{
  pts.push_back(position());
}
int Text::pt_count()const
{
  return 1;
}

Point Text::center()const
{
//	Point ptBox[4];
//	real_box_point(ptBox);
//  const std::vector<Point>& ptBox = real_box_point();
	std::vector<Point> ptBox;
	real_box_pt(ptBox);
	assert(ptBox.size()>=4);
  return (ptBox[0]+ptBox[2])/2;
}

// void Text::set_crurent_db()
// {
//   set_database(static_current_db_);
// }

static void gdi_rect(std::string str, Float h, Rect& rc)
{
  Text txt;
  txt.gdi_height(h);
  txt.text(str.c_str());
  txt.horizontal_rect(rc);
} 

static Float seemly_height(const Rect& txtrc, const Rect rc)
{
  Float h = rc.height();
  Float w = rc.width();
  Float txth = txtrc.height();
  Float txtw = txtrc.width();
  if(LessThen(txtw, w)){
    return txth;
  }else{
    return txth * w / txtw;
  }
}

Float seemly_gdi_height(const Rect& rc, std::string row)
{
  Rect txtrc;
  gdi_rect(row, rc.height(), txtrc);
  return seemly_height(txtrc, rc);
}


Float seemly_gdi_height(const Rect& rc, const std::vector<std::string>& rows)
{
  Rect txtrc, maxrc;
  Float thew = 0;
  Float maxw = 0;
  Float h = rc.height();
  Float w = rc.width();
  int count = rows.size();
  int i=0;
  for(i=0; i<count; ++i){
    gdi_rect(rows[i], h/count, txtrc);
    thew = txtrc.width();
    if(maxw < thew){
      maxw = thew;
      maxrc = txtrc;
    }
  }
  return seemly_height(maxrc, rc);
}


}//namespace
