// Dimension_Style.cpp: implementation of the Dimension_Style class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dimension_Style.h"

#include <cassert>
#include <TCHAR.H>

#include "Point.h"
#include "Normal.h"
#include "Matrix_d.h"

#include "Text.h"
#include "Line.h"
#include "RArc.h"
#include "Circle.h"

#include "Global.h"
#include "Entity_Calculate.h"
#include "Lua_Tab.h"

#include "getrace.h"

#include "../afc/format.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
void Dimension_Style::init()
{
	text_style_ = "Standard";
//   rounding_type_ = ROUNDING_BE_DIVIDED_BY_1;
//   text_precision_ = 2;
//   text_fill_   = false;
	//text_precision_ = 2;
  text_precision_ = 0.01;
  decimal_place_ = 2;
  decimal_addends_= false;
	//引出线数据
	extendstartoff_ = 0.5;
	extendendoff_ = 3.0;
	//四点标注，标注线长度
	start_dim_length_ = 8.0;
	end_dim_length_ = 8.0;
	//箭头数据
	arrowstyle_ = NO;
	arrowsize_ = 2.0;
  arrow_num_ = ARROW_NULL;
	//文字数据
	tf_ = Only;
	tp_ = UP;
	text_hight_ = 25;
	
	text_frame_color_ = 1;
	text_color_ = 1;
	line_color_ = 1;
	text_hight_ = 25;

}
Dimension_Style::Dimension_Style()
MCT_INIT1("Dimension_Style")
{
	init();
}
Dimension_Style::Dimension_Style(const Dimension_Style& rhs)
MCT_INIT1("Dimension_Style")
{
	init();
	name_ = rhs.name_;
	text_style_ = rhs.text_style_;
//   rounding_type_ = rhs.rounding_type_;
//   text_precision_ = rhs.text_precision_;
//   text_fill_   = rhs.text_fill_  ;
  text_precision_ = rhs.text_precision_;
  decimal_place_ = rhs.decimal_place_;
  decimal_addends_= rhs.decimal_addends_;

	extendstartoff_ = rhs.extendstartoff_;
	extendendoff_ = rhs.extendendoff_;
	start_dim_length_ = rhs.start_dim_length_;
	end_dim_length_ = rhs.end_dim_length_;
	arrowstyle_ = rhs.arrowstyle_;
	arrowsize_ = rhs.arrowsize_;
	tf_ = rhs.tf_;
	tp_ = rhs.tp_;
	
	text_frame_color_ = rhs.text_frame_color_;
	text_color_ = rhs.text_color_;
	line_color_ = rhs.line_color_;
	text_hight_ = rhs.text_hight_;

  arrow_num_ = rhs.arrow_num_;
}
Dimension_Style& Dimension_Style::operator=(const Dimension_Style& rhs)
{
	if(this == &rhs)
		return *this;
	name_ = rhs.name_;
	text_style_ = rhs.text_style_;
//   rounding_type_ = rhs.rounding_type_;
//   text_precision_ = rhs.text_precision_;
//   text_fill_   = rhs.text_fill_  ;
  text_precision_ = rhs.text_precision_;
  decimal_place_ = rhs.decimal_place_;
  decimal_addends_= rhs.decimal_addends_;

  extendstartoff_ = rhs.extendstartoff_;
	extendendoff_ = rhs.extendendoff_;
	start_dim_length_ = rhs.start_dim_length_;
	end_dim_length_ = rhs.end_dim_length_;
	arrowstyle_ = rhs.arrowstyle_;
	arrowsize_ = rhs.arrowsize_;
	tf_ = rhs.tf_;
	tp_ = rhs.tp_;

	text_frame_color_ = rhs.text_frame_color_;
	text_color_ = rhs.text_color_;
	line_color_ = rhs.line_color_;
	text_hight_ = rhs.text_hight_;

  arrow_num_ = rhs.arrow_num_;

  return *this;
}
bool Dimension_Style::operator== (const Dimension_Style& rhs)
{
	//不判断名是否相等
	//name_ == rhs.name_&&
	if(
		text_style_==rhs.text_style_&&
// 		rounding_type_==rhs.rounding_type_&&
//     text_precision_==rhs.text_precision_&&
//     text_fill_==rhs.text_fill_&&
  text_precision_ == rhs.text_precision_ &&
  decimal_place_ == rhs.decimal_place_ &&
  decimal_addends_== rhs.decimal_addends_ &&

		extendstartoff_==rhs.extendstartoff_&&
		extendendoff_==rhs.extendendoff_&&
		start_dim_length_==rhs.start_dim_length_&&
		end_dim_length_==rhs.end_dim_length_&&
		arrowstyle_==rhs.arrowstyle_&&
		tf_==rhs.tf_&&
		tp_==rhs.tp_&&
		text_hight_==rhs.text_hight_)
		return true;
	return false;

}
Dimension_Style::~Dimension_Style()
{
}

Dimension_Style* Dimension_Style::create_me()
{
	return new Dimension_Style;
}
bool Dimension_Style::close()
{
	
	delete this;
	return true;
}

// void Dimension_Style::lua_load(iLua_File &fin)
// {
// 
// }
// 
// void Dimension_Style::lua_save(oLua_File &fout)const
// {
// 	fout.save_value("name_", name_);
// 	fout.save_value("text_style_", text_style_);
// 	fout.save_value("rounding_type_", rounding_type_);
// 	fout.save_value("text_precision_", text_precision_);
// 
// 	fout.save_value("text_fill_", text_fill_);
// 	fout.save_value("extendstartoff_", extendstartoff_);
// 	fout.save_value("extendendoff_", extendendoff_);
// 	fout.save_value("start_dim_length_", start_dim_length_);
// 	fout.save_value("end_dim_length_", end_dim_length_);
// 	fout.save_value("arrowstyle_", (int)arrowstyle_);
// 	fout.save_value("arrowsize_", arrowsize_);
// 	fout.save_value("arrow_num_", arrow_num_);
// 	fout.save_value("tf_", (int)tf_);
// 	fout.save_value("tp_", (int)tp_);
// 	fout.save_value("text_hight_", text_hight_);
// 	fout.save_value("text_frame_color_", text_frame_color_);
// 	fout.save_value("text_color_", text_color_);
// 	fout.save_value("line_color_", line_color_);
// }
void Dimension_Style::save_lua(std::ofstream &out,char *name,int tab_num)
{
	int pos = tab_num+1;
	lua::begin_table(out,name,tab_num);
	lua::lpstr_save(out,"kind","Dimension_Style",pos);
	
	lua::string_save(out,"name_",name_,pos);
	lua::string_save(out,"text_style_",text_style_,pos);
// 	lua::int_save(out,"rounding_type_",rounding_type_,pos);
// 	lua::int_save(out,"text_precision_",text_precision_,pos);
// 	lua::bool_save(out,"text_fill_",text_fill_,pos);
  lua::double_save(out, "text_precision_", text_precision_, pos);
  lua::int_save(out, "decimal_place_", decimal_place_, pos);
  lua::bool_save(out, "decimal_addends_", decimal_addends_, pos);

	lua::double_save(out,"extendstartoff_",extendstartoff_,pos);
	lua::double_save(out,"extendendoff_",extendendoff_,pos);
	lua::double_save(out,"start_dim_length_",start_dim_length_,pos);
	lua::double_save(out,"end_dim_length_",end_dim_length_,pos);
	lua::int_save(out,"arrowstyle_",arrowstyle_,pos);
	lua::double_save(out,"arrowsize_",arrowsize_,pos);
	lua::int_save(out,"arrow_num_",arrow_num_,pos);
	lua::int_save(out,"tf_",tf_,pos);
	lua::int_save(out,"tp_",tp_,pos);
	lua::double_save(out,"text_hight_",text_hight_,pos);
	lua::int_save(out,"text_frame_color_",text_frame_color_,pos);
	lua::int_save(out,"text_color_",text_color_,pos);
	lua::int_save(out,"line_color_",line_color_,pos);

	lua::end_table(out,tab_num);

}


static dlhml::Dimension_Style::Arrow get_arrow_kind(int kind)
{
	if(kind == 10)
		return Dimension_Style::NO;
	else if(kind == 11)
		return Dimension_Style::LEAD;
	else if(kind == 12)
		return Dimension_Style::COMMON;
	else if(kind == 13)
		return Dimension_Style::CIRCLE;
	else
		return Dimension_Style::NO;

}
static dlhml::Dimension_Style::Txt_Frame get_frame_kind(int kind)
{
	if(kind == 1)
		return Dimension_Style::Only;
	else if(kind == 2)
		return Dimension_Style::Baseline;
	else if(kind == 3)
		return Dimension_Style::ArcEdge;
	else if(kind == 4)
		return Dimension_Style::ArrowEdge;
	else if(kind == 5)
		return Dimension_Style::RectEdge;
	else if(kind == 6)
		return Dimension_Style::CircleEdge;
	else
		return Dimension_Style::Only;

}
static dlhml::Dimension_Style::TextPos get_txtpos_kind(int kind)
{
	if(kind == 20)
		return Dimension_Style::UP;
	else if(kind == 21)
		return Dimension_Style::CENTER;
	else if(kind == 22)
		return Dimension_Style::DOWN;

		return Dimension_Style::UP;

}
void Dimension_Style::open_lua(lua_State *l,char *name)
{

	Lua_Tab t(l,name);
	std::string temp;
	get_value(string,l,temp,"kind");
	get_value(string,l,temp,"name_");
	name_ = temp.c_str();
	get_value(string,l,temp,"text_style_");
	text_style_ = temp.c_str();

// 	get_value(number,l,rounding_type_,"rounding_type_");
// 	get_value(number,l,text_precision_,"text_precision_");
// 	get_value(number,l,text_fill_,"text_fill_");
  get_value(number, l, text_precision_, "text_precision_");
  get_value(number, l, decimal_place_, "decimal_place_");
  get_value(number, l, decimal_addends_, "decimal_addends_");

	get_value(number,l,extendstartoff_,"extendstartoff_");
	get_value(number,l,extendendoff_,"extendendoff_");
	get_value(number,l,start_dim_length_,"start_dim_length_");
	get_value(number,l,end_dim_length_,"end_dim_length_");

	int kind;
	get_value(number,l,kind,"arrowstyle_");
	arrowstyle_ = get_arrow_kind(kind);
	get_value(number,l,arrowsize_,"arrowsize_");
	get_value(number,l,arrow_num_,"arrow_num_");

	get_value(number,l,kind,"tf_");
	tf_ = get_frame_kind(kind);
	get_value(number,l,kind,"tp_");
	tp_ = get_txtpos_kind(kind);
	get_value(number,l,text_hight_,"text_hight_");
	get_value(number,l,text_frame_color_,"text_frame_color_");
	get_value(number,l,text_color_,"text_color_");
	get_value(number,l,line_color_,"line_color_");



}

void Dimension_Style::text_precision(double d)
{
  text_precision_ = d;
}
double Dimension_Style::text_precision()const
{
  return text_precision_;
}
void Dimension_Style::decimal_place(int n)
{
  decimal_place_ = n;
}
int Dimension_Style::decimal_place()const
{
  return decimal_place_;
}
void Dimension_Style::decimal_addends(bool b)
{
  decimal_addends_ = b;
}
bool Dimension_Style::decimal_addends()const
{
  return decimal_addends_;
}


Point Dimension_Style::get_extend_base(const Point& basept,const Point& dimpt) const
{
	Normal nor;
	nor.set_data(basept,dimpt);
	Point pt(basept);
	return pt.polarTo(extendstartoff_,nor);
}
Point Dimension_Style::get_extend_end(const Point& basept,const Point& dimpt) const
{
	Normal nor;
	nor.set_data(basept,dimpt);
	Point pt(dimpt);
	return pt.polarTo(extendendoff_,nor);
}
Point Dimension_Style::get_start_dim_length(const Point& real_dimpt,const Normal& nor) const
{
	return real_dimpt.polarTo(start_dim_length_,nor);
}
Point Dimension_Style::get_end_dim_length(const Point& real_dimpt,const Normal& nor) const
{
	return real_dimpt.polarTo(end_dim_length_,nor);
}
Point Dimension_Style::get_dim_length(const Point& real_dimpt,const Normal& nor,const Text& text) const
{
	SIZE sz;
	text.horizontal_size(sz);
	return real_dimpt.polarTo(start_dim_length_+sz.cx,nor);
}
bool Dimension_Style::numeric_char(TCHAR ch) const
{
	return !IsCharAlpha(ch) && IsCharAlphaNumeric(ch);
}
bool Dimension_Style::numeric_str(std::string str) const
{
	int i=0;
	int num = strlen(str.c_str());
	for(;i<num;i++)
	{
		if(str[i] == '.')
			continue;
		if(!numeric_char(str[i]))
			break;
	}
	return i == num;
}
std::string Dimension_Style::get_rounding_text(std::string str)const
{
  std::string::size_type dot_pos = str.find('.');
  if(dot_pos == std::string::npos){
    return str;
  }
  double d = atof(str.c_str());
  str = afc::format(d, text_precision_, decimal_place_, decimal_addends_);
  return str;
} 

// std::string Dimension_Style::get_rounding_text(std::string str)const
// {
//   std::string::size_type dot_pos = str.find('.');
//   if(dot_pos == std::string::npos){
//     return str;
//   }
//   
//   int bit_for = text_precision_;
//   switch(rounding_type_)
//   {
//   case ROUNDING_BE_DIVIDED_BY_1:
//     bit_for = text_precision;
//     break;
//   case ROUNDING_BE_DIVIDED_BY_2:
//     bit_for = text_precision-1;
//     break;
//   case ROUNDING_BE_DIVIDED_BY_3:
//     bit_for = text_precision-2;
//     break;
//   default:
//     return str;
//   }
//   double num = atof(str.c_str());
//   int i=0;
//   for(i=0;i<bit_for;i++){
//     num*=10;
//   }
//   num*=rounding_type_;
//   num+=0.5;
//   int i_num = (int)(num);
//   num = (double)i_num/rounding_type_;
//   for(i=0;i<bit_for;i++){
//     num/=10;
//   }
//   
//   char buf_rounding[32];
//   sprintf(buf_rounding,"%d\0",text_precision_);
//   std::string rounding_str = buf_rounding;
//   rounding_str = "%." + rounding_str + "f\0";
//   
//   char buf_num[32];
//   sprintf(buf_num,rounding_str.c_str(),num);
//   str = buf_num;
//   
//   if(!text_fill_){
//     dot_pos = str.find('.');
//     if(dot_pos == std::string::npos){
//       return str;
//     }
//     std::string::size_type it = str.length()-1;
//     for(it=str.length()-1; it>=dot_pos; it--){
//       if(str[it]=='0' || str[it]=='.'){
//         str.erase(it);
//       }else{
//         break;
//       }
//     }
//   }
//   return str;
// } 


void Dimension_Style::get_text(Text& text) const
{
  std::string str = text.text();
  if(numeric_str(str.c_str())){
    str=get_rounding_text(str);
    text.text(str.c_str());
  }

////四舍五入
//   if(numeric_str(text.text())){
//     char ch[10];
//     strcpy(ch,"%.");
//     char pc[3];
//     sprintf(pc,"%d",text_precision_);
//     strcat(ch,pc);
//     strcat(ch,"f");
//     char s[20];
//     if(UEquFloat(0,atof(text.text()))){
//       sprintf(s,ch,atof(text.text()));
//       text.text(s);
//     }else{
//       text.text("0");
//     }
//   }

  text.style_name(text_style_);
  text.dxf_height(text_hight_);
  text.color_index(text_color_);

  if(tp_ == UP){
    text.align_point(Text::center_bottom);
  }
  else if(tp_ == CENTER){
    text.align_point(Text::center_center);
    //text.position(pt.polarTo(text_hight_/2,nor));
  }
  else{
    text.align_point(Text::center_top);
    //text.position(pt.polarTo(text_hight_,nor));
  }
}
void Dimension_Style::get_text_frame(Text& text, std::vector<Entity*>& es) const
{
  get_text(text);

  //TEXT FRAME
  int i=0;
  //LINE
  std::vector<Line*> lns;
  get_text_line(text,lns);
  for(i=0;i<lns.size();i++){
    lns[i]->color_index(text_frame_color_);
    es.push_back(static_cast<Entity*>(lns[i]));
  }
  //CIRCLE
  std::vector<Circle*> cirs;
  get_text_circle(text,cirs);
  for(i=0;i<cirs.size();i++){
    cirs[i]->color_index(text_frame_color_);
    es.push_back(static_cast<Entity*>(cirs[i]));
  }
  //ARC
  std::vector<RArc*> arcs;
  get_text_arc(text,arcs);
  for(i=0;i<arcs.size();i++){
    arcs[i]->color_index(text_frame_color_);
    es.push_back(static_cast<Entity*>(arcs[i]));
  }
}

// void Dimension_Style::get_text(Text& text) const
// {
//   if(numeric_str(text.text())){
//     char ch[10];
//     strcpy(ch,"%.");
//     char pc[3];
//     sprintf(pc,"%d",text_precision_);
//     strcat(ch,pc);
//     strcat(ch,"f");
//     char s[20];
//     if(UEquFloat(0,atof(text.text()))){
//       sprintf(s,ch,atof(text.text()));
//       text.text(s);
//     }else{
//       text.text("0");
//     }
//   }
//   text.style_name(text_style_);
//   text.height(text_hight_);
//   text.color_index(text_color_);
//   if(tp_ == UP){
//     return;
//   }
//   Normal nor;
//   nor.set_x_axis_angle(text.rotation()-pi/2);
//   Point pt;
//   text.left_top_point(pt);
//   if(tp_ == CENTER){
//     text.position(pt.polarTo(text_hight_/2,nor));
//     return ;
//   }
//   text.position(pt.polarTo(text_hight_,nor));
// }
// void Dimension_Style::get_text_frame(Text& text, std::vector<Entity*>& es) const
// {
// //bet
// //lm
// //	if(numeric_str(text.text())){
// //		char ch[10];
// //		strcpy(ch,"%.");
// //		char pc[3];
// //		sprintf(pc,"%d",text_precision_);
// //		strcat(ch,pc);
// //		strcat(ch,"f");
// //		char s[20];
// //		if(UEquFloat(0,atof(text.text()))){
// //			sprintf(s,ch,atof(text.text()));
// //			text.text(s);
// //		}else{
// //			text.text("0");
// //		}
// //	}
// //	text.style_name(text_style_);
// //	text.height(text_hight_);
// //  text.color_index(text_color_);
// //  if(tp_ == UP){
// //		return;
// //  }
// //	Normal nor;
// //	nor.set_x_axis_angle(text.rotation()-pi/2);
// //	Point pt;
// //	text.left_top_point(pt);
// //	if(tp_ == CENTER){
// //		text.position(pt.polarTo(text_hight_/2,nor));
// //		return ;
// //	}
// //	text.position(pt.polarTo(text_hight_,nor));
// //ter
// 
// 	if(numeric_str(text.text())){
// 		char ch[10];
// 		strcpy(ch,"%.");
// 		char pc[3];
// 		sprintf(pc,"%d",text_precision_);
// 		strcat(ch,pc);
// 		strcat(ch,"f");
// 		char s[20];
// 		if(UEquFloat(0,atof(text.text()))){
// 			sprintf(s,ch,atof(text.text()));
// 			text.text(s);
// 		}else{
// 			text.text("0");
// 		}
// 	}
// 	text.style_name(text_style_);
// 	text.height(text_hight_);
//   text.color_index(text_color_);
// 
// //	Normal nor;
// //  radian_2_normal2d(text.rotation()-pi/2,nor);
// //  nor.set_unit();
// //  Point pt = text.position();
// 
// 
//   if(tp_ == UP){
//     text.align_point(Text::center_bottom);
//   }
//   else if(tp_ == CENTER){
//     text.align_point(Text::center_center);
// 		//text.position(pt.polarTo(text_hight_/2,nor));
// 	}
//   else{
//     text.align_point(Text::center_top);
// 	  //text.position(pt.polarTo(text_hight_,nor));
//   }
// 
//   //TEXT FRAME
//   int i=0;
//   //LINE
//   std::vector<Line*> lns;
//   get_text_line(text,lns);
//   for(i=0;i<lns.size();i++){
//     es.push_back(static_cast<Entity*>(lns[i]));
//   }
//   //CIRCLE
//   std::vector<Circle*> cirs;
//   get_text_circle(text,cirs);
//   for(i=0;i<cirs.size();i++){
//     es.push_back(static_cast<Entity*>(cirs[i]));
//   }
//   //ARC
//   std::vector<RArc*> arcs;
//   get_text_arc(text,arcs);
//   for(i=0;i<arcs.size();i++){
//     es.push_back(static_cast<Entity*>(arcs[i]));
//   }
// 
// }
void Dimension_Style::text_pos(TextPos pos)
{
  tp_=pos;
}


//void Dimension_Style::get_text_frame(std::vector<Entity*>& es)
//{
//  Text txt;
//  get_text(txt);
//  std::vector<Line*> lns;
//  get_text_line(txt,lns);
//  int i=0;
//  for(i=0;i<lns.size();i++){
//    es.push_back(static_cast<Entity*>(lns[i]));
//  }
//}
void Dimension_Style::get_text_line(const Text& text,std::vector<Line*>& lines) const
{
  Line * ln =   NULL;
	//Point pt[4];
  //text.real_box_point(pt);
  //const std::vector<Point>& pt = text.real_box_point();
	std::vector<Point> pt;
	text.real_box_pt(pt);
	assert(pt.size()>=4);
	if(tf_ == Only){
		//return 0;
	}else if(tf_ == Baseline){
    ln = Line::create_me();		
    ln->color_index(text_frame_color_);
    ln->setdata(pt[0],pt[3]);									      //bottom line
    lines.push_back(ln);
		//return 1;
	}else if(tf_ == ArcEdge){
    ln = Line::create_me();		
    ln->color_index(text_frame_color_);
    ln->setdata(pt[1],pt[2]);									//top line
    lines.push_back(ln);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[0],pt[3]);									//bottom line
    lines.push_back(ln);
		//return 2;
	}else if(tf_ == ArrowEdge){
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[1],pt[2]);									//top line
    lines.push_back(ln);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[0],pt[3]);									//bottom line
    lines.push_back(ln);
		Float len = pt[0].distanceto(pt[1])/2;
		Normal nor;
		nor.set_x_axis_angle(text.rotation()+pi/2);
		Point t = pt[0].polarTo(len,nor);
		nor.set_x_axis_angle(text.rotation()+pi);
		t = t.polarTo(len,nor);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[0],t);									//left bottom line
    lines.push_back(ln);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
    ln->setdata(pt[1],t);									//left top line
    lines.push_back(ln);
		nor.set_x_axis_angle(text.rotation()+pi/2);
		t = pt[3].polarTo(len,nor);
		nor.set_x_axis_angle(text.rotation());
		t = t.polarTo(len,nor);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[3],t);									//right bottom line
    lines.push_back(ln);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[2],t);									//right top line
    lines.push_back(ln);
		//return 6;
	}else if(tf_ == RectEdge){
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[1],pt[2]);									//top line
    lines.push_back(ln);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[0],pt[3]);									//bottom line
    lines.push_back(ln);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[0],pt[1]);									//left line
    lines.push_back(ln);
    ln = Line::create_me();
    ln->color_index(text_frame_color_);
		ln->setdata(pt[2],pt[3]);		          //right line
    lines.push_back(ln);
		//return 4;
	}else if(tf_ == CircleEdge){
		//return 0;
	}else{
		//return -1;
	}
}
void Dimension_Style::get_text_circle(const Text& text,std::vector<Circle*>& circles) const
{
  Circle * circle = NULL;

	if(tf_ == CircleEdge){
//		Point pt[4];
//		text.real_box_point(pt);
    //const std::vector<Point>& pt = text.real_box_point();
		std::vector<Point> pt;
		text.real_box_pt(pt);
		assert(pt.size()>=4);
		Entity_Calculate calc;
		Point center;
		calc.line_insect_line(center,Line(pt[0],pt[2]),Line(pt[1],pt[3]));
    
    circle = Circle::create_me();
    circle->color_index(text_frame_color_);
		circle->setdata(center,pt[0].distanceto(pt[2])/2);

    //circle->center(text.position());

    circles.push_back(circle);
		//return 1;
	}else{
		//return 0;
	}
}
void Dimension_Style::get_text_arc(const Text& text,std::vector<RArc*>& arcs) const
{
  RArc * arc = NULL;

	if(tf_ == ArcEdge){
//		Point pt[4];
//		text.real_box_point(pt);
    //const std::vector<Point>& pt = text.real_box_point();
		std::vector<Point> pt;
		text.real_box_pt(pt);
		assert(pt.size()>=4);
		Float radius = pt[0].distanceto(pt[1])/2;
		Point center = pt[0]+pt[1];
		center /= 2;
		Normal nor;
		nor.set_data(center,pt[1]);
		Float stang = nor.angle_x_axis_two_pi()*180/pi;
		nor.set_data(center,pt[0]);
		Float edang = nor.angle_x_axis_two_pi()*180/pi;

    arc = RArc::create_me();
    arc->color_index(text_frame_color_);
		arc->set_degree2d(center,radius,stang,edang);
    arcs.push_back(arc);

		center = pt[2]+pt[3];
		center /= 2;
		nor.set_data(center,pt[3]);
		stang = nor.angle_x_axis_two_pi()*180/pi;
		nor.set_data(center,pt[2]);
		edang = nor.angle_x_axis_two_pi()*180/pi;

    arc = RArc::create_me();
    arc->color_index(text_frame_color_);
		arc->set_degree2d(center,radius,stang,edang);
    arcs.push_back(arc);
		//return 2;
	}else{
		//return 0;
	}
}

////根据arc、arrow_num_画箭头
////内部调用get_arrow(点、向量)
void Dimension_Style::get_arrow(const RArc& arc, ARROW_NUM an, std::vector<Entity*>& es)const
{
  Point  pt;
  Normal nor;
  ////起始端/两端
  if(an == ARROW_START ||an == ARROW_DOUBLE){
    pt = arc.start();
    nor.set_data(arc.center(), pt);
    nor.rota_z(-90);
    get_arrow(pt,nor,es);
  }
  ////终止端/两端
  if(an == ARROW_END   ||an == ARROW_DOUBLE){
    pt = arc.end();
    nor.set_data(arc.center(), pt);
    nor.rota_z(+90);
    get_arrow(pt,nor,es);
  }
  ////无箭头
}
void Dimension_Style::get_arrow(const RArc& arc, std::vector<Entity*>& es)const
{
  get_arrow(arc, arrow_num_, es);
}

////根据ln、arrow_num_画箭头
////内部调用get_arrow(点、向量)
void Dimension_Style::get_arrow(const Line& ln, ARROW_NUM an, std::vector<Entity*>& es)const
{
  Point  pt;
  Normal nor;
  ////起始端/两端
  if(an == ARROW_START ||an == ARROW_DOUBLE){
    pt = ln.start();
    nor.set_data(ln.reverse());
    get_arrow(pt,nor,es);
  }
  ////终止端/两端
  if(an == ARROW_END   ||an == ARROW_DOUBLE){
    pt = ln.end();
    nor.set_data(ln);
    get_arrow(pt,nor,es);
  }
  ////无箭头
}
void Dimension_Style::get_arrow(const Line& ln, std::vector<Entity*>& es)const
{
  get_arrow(ln, arrow_num_, es);
}

////根据点、向量画箭头
////向量指向标注点
void Dimension_Style::get_arrow(const Point & pt , 
                                const Normal& nor,
                                std::vector<Entity*>& es)const
{
  std::vector<Line*> lns;
  get_arrow_line(pt,nor,lns);
  int i=0;
  for(i=0;i<lns.size();++i){
    lns[i]->color_index(line_color_);
  }
	dlhml::push_back<Line>(lns,es);
  std::vector<Circle*> crs;
  get_arrow_circle(pt,crs);
  for(i=0;i<crs.size();++i){
    crs[i]->color_index(line_color_);
  }
	dlhml::push_back<Circle>(crs,es);
}

//nor point to dim			向量指向标注点
void Dimension_Style::get_arrow_line(const Point& real_dimpt,
                                    const Normal& nor,
                                    std::vector<Line*>& lines) const
{
  Line * ln = NULL;

	if(arrowstyle_ == LEAD){
		Normal n;
		n.set_x_axis_angle(nor.angle_x_axis_two_pi()+pi/4);
		Point pt1 = real_dimpt.polarTo(arrowsize_,n);
		n.set_x_axis_angle(nor.angle_x_axis_two_pi()+pi/4+pi);
		Point pt2 = real_dimpt.polarTo(arrowsize_,n);
		
    ln = Line::create_me();
    ln->setdata(pt1,pt2);
    ln->color_index(line_color_);
    lines.push_back(ln);
		
    //return 1;
	}else if(arrowstyle_ == COMMON){
    Float dis_10 = sqrt(10);
    Point pt1, pt2;
    pt1.x = -arrowsize_*3/dis_10;
    pt1.y = -arrowsize_*1/dis_10;
    pt2.x = -arrowsize_*3/dis_10;
    pt2.y = +arrowsize_*1/dis_10;
    Float rota_radian=0;
    normal2d_2_radian(nor,rota_radian);
    Matrix rota_mat;
    rota_mat.set_z_rotation_radian(rota_radian);
    pt1.transformby(rota_mat);
    pt2.transformby(rota_mat);
    Matrix move_mat;
    move_mat.set_move(real_dimpt);
    pt1.transformby(move_mat);
    pt2.transformby(move_mat);

// 		Normal n;
// 		n.set_x_axis_angle(nor.angle_x_axis_two_pi()+3*pi/4);
// 		Point pt1 = real_dimpt.polarTo(arrowsize_,n);

    ln = Line::create_me();
		ln->setdata(real_dimpt,pt1);
    ln->color_index(line_color_);
    lines.push_back(ln);
		
//     n.set_x_axis_angle(nor.angle_x_axis_two_pi()-3*pi/4);
// 		Point pt2 = real_dimpt.polarTo(arrowsize_,n);

    ln = Line::create_me();
    ln->setdata(real_dimpt,pt2);
    ln->color_index(line_color_);
    lines.push_back(ln);
		
    //return 2;
	}else if(arrowstyle_ == CIRCLE){
		//return 0;
	}else{
		//return -1;
	}
}
//void Dimension_Style::get_two_arrow_line(const Point& real_dimpt,
//                                        const Normal& nor,
//                                        std::vector<Line*>& lines) const
//{
//  Line * ln = NULL;
//
//	Normal n;
//	n.set_x_axis_angle(nor.angle_x_axis_two_pi()+3*pi/4);
//	Point pt1 = real_dimpt.polarTo(arrowsize_,n);
//
//  ln = Line::create_me();
//	ln->setdata(real_dimpt,pt1);
//  ln->color_index(line_color_);
//  lines.push_back(ln);
//
//	n.set_x_axis_angle(nor.angle_x_axis_two_pi()-3*pi/4);
//	Point pt2 = real_dimpt.polarTo(arrowsize_,n);
//
//  ln = Line::create_me();
//	ln->setdata(real_dimpt,pt2);
//  ln->color_index(line_color_);
//  lines.push_back(ln);
//
//	//return 2;
//}

void Dimension_Style::get_arrow_circle(const Point& real_dimpt,
                                       std::vector<Circle*>& circles) const
{
  Circle * circle = NULL;
	if(arrowstyle_ == CIRCLE){
    circle = Circle::create_me();
		circle->setdata(real_dimpt,arrowsize_/2);
    circle->color_index(line_color_);
    circles.push_back(circle);
		//return 1;
	}else{
		//return 0;
	}
}

void Dimension_Style::line_color(int color)         
{
  line_color_ = color;
//  TRACE_OUT("line_color_:%d",color);
}



}
