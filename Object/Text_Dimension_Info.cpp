// Text_Dimension_Info.cpp: implementation of the Text_Dimension_Info class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Text_Dimension_Info.h"

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
#include "Replace_String_Center.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Text_Dimension_Info,Dimension)
Text_Dimension_Info::Text_Dimension_Info()
MCT_INIT1("Text_Dimension_Info")
{
	//dim_content_ = NULL;
	dim_text("TXT");
	dim_style_val_.txt_frame(Dimension_Style::ArrowEdge);

	names_.push_back("name1");
	names_.push_back("name2");

}
Text_Dimension_Info::Text_Dimension_Info(const Text_Dimension_Info& rhs)
:Dimension(rhs)
MCT_INIT2("Text_Dimension_Info")
{
//	dim_content_ = NULL;
//	string_copy(dim_content_,rhs.dim_content_);
	dim_sign_ = rhs.dim_sign_;
	names_ = rhs.names_;

	rep_db_ = rhs.rep_db_;
}
Text_Dimension_Info& Text_Dimension_Info::operator=(const Text_Dimension_Info& rhs)
{
	Dimension::operator =(rhs);
//	dim_content_ = NULL;
	dim_sign_ = rhs.dim_sign_;
	names_ = rhs.names_;

	rep_db_ = rhs.rep_db_;

	return *this;
}
Text_Dimension_Info::~Text_Dimension_Info()
{

}
bool Text_Dimension_Info::visit(Visitor& v)
{
  show_change(true);
	return v.Visit_Text_Dimension_Info(*this);
}
void Text_Dimension_Info::loadme(File& in)
{
	load_me(in);
	color_fact_.load(in);
	in>>dim_sign_;
}
void Text_Dimension_Info::saveme(const File& out) const
{
	save_me(out);
	color_fact_.save(out);
	out<<dim_sign_;
}
void Text_Dimension_Info::save_luame(std::ofstream &out,int tab_num)
{
	Dimension::save_luame(out,tab_num);
	lua::string_save(out,"dim_sign_",dim_sign_,tab_num);
	color_fact_.save_lua(out,"color_fact_",tab_num);

	lua::save(out,"names_",names_,tab_num);

}
void Text_Dimension_Info::open_luame(lua_State *l)  
{
	TRACE_OUT("Text_Dimension_Info open in open_luame()\n");
	Dimension::open_luame(l);
	std::string temp;
	get_value(number,l,temp,"dim_sign_");
	(dim_sign_ =temp.c_str());
	txt_change(true);

}

void Text_Dimension_Info::dim_sign(std::string dim_sign)
{
 txt_change(true);
 dim_sign_ = dim_sign;
}
std::string Text_Dimension_Info::dim_sign() const
{
	return dim_sign_;
}

void Text_Dimension_Info::edit_propertyme(const Edit_Entity& edit)
{
  show_change(true);
//	edit.edit_text_dim(*this);
}


errorinfo Text_Dimension_Info::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Text_Dimension_Info::transformbyme(const Matrix& mat)
{
//	REITRACE;
  show_change(true);
  Dimension::transformbyme(mat);
  Float hei = dim_style_val_.text_height();
  hei *= mat.value(0,0);
  dim_style_val_.text_height(hei);
	text_position_.transformby(mat);
}
void Text_Dimension_Info::drag_startme(const Matrix& mat)
{
  show_change(true);
	text_position_.transformby(mat);
}
void Text_Dimension_Info::drag_endme(const Matrix& mat)
{
  show_change(true);
	text_position_.transformby(mat);
}

Entity* Text_Dimension_Info::cloneme() const
{
	return new Text_Dimension_Info(*this);
}

void Text_Dimension_Info::closeme()
{
	delete this;
}

bool Text_Dimension_Info::intersectme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
	return text.intersect(rect);
}
bool Text_Dimension_Info::envelopme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
	return text.envelop(rect);
}

Rect Text_Dimension_Info::calc_box2d() const
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

//bool Text_Dimension_Info::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////	Entity_Snap_Implement<Text_Dimension_Info> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Text_Dimension_Info::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}
//09.6.22
void Text_Dimension_Info::setctrl(const std::vector<Point>& pts)
{
  show_change(true);
  if(pts.size() != 1){
    return;
  }
	text_position_ = pts[0];
}
void Text_Dimension_Info::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(text_position_);
}
int  Text_Dimension_Info::pt_count()const
{
  return 1;
}
void Text_Dimension_Info::setdrag(const std::vector<Point>& pts, int index)
{
  if(pts.empty()){
    return;
  }
  text_position(pts[0]);
}
void Text_Dimension_Info::getdrag(std::vector<Point>& pts)const
{
  pts.push_back(text_position_);
}

void Text_Dimension_Info::draw_names(std::vector<Entity*>& es)const
{

	Point pos = text_position_;
	int j=1;
	for(int i=0;i<names_.size();i++)
	{
	  Text * text = Text::create_me();
	  
	  text->set_database(static_current_db_);
    //align_point_ = get_text_align();
	
	  //text->align_point(get_text_align());
	 
	 
	  
	  text->rotation(text_rotation_);
	  text->setdata(pos,names_[i]);
	  text->color_index(dim_style_val_.text_color());

		dim_style_val_.get_text(*text);

		txt_record(*text);	  

		Normal nor;
		radian_2_normal2d(text_rotation_+dlhml::pi/2, nor);
		double dis = j*dim_style_val_.text_height()+8.0;
		pos = text_position_.polarTo(dis, nor);
	
		//测试全部改成左底对齐
	  text->align_point(dlhml::Text::left_bottom);

	  //UGLY angle rotate 
/*		pos.y = text_position_.y - j*dim_style_val_.text_height()-5.0;
		if(EquFloat(text_rotation_,3.1415926/2.0)){
			pos.x = text_position_.x - (j*dim_style_val_.text_height()+5.0);
		}else if(EquFloat(text_rotation_,0)){
		
		}else{
			pos.x = text_position_.x - (j*dim_style_val_.text_height()+5.0)/2;
		}
	*/	
		j++;
		es.push_back(text);


  		//创建完成后马上进行替换
		rep_text(text,es);


	}
}

//**基类处理回调函数**********************************************************************************************

void Text_Dimension_Info::rep_text(Text *t,std::vector<Entity*>& es)const 
{
	for(int i=0;i<rep_db_.size();i++){
	
		Replace_String_Center rep;
		rep.rep_text(rep_db_[i].rep_str_,t,rep_db_[i].style_,rep_db_[i].sign_,rep_db_[i].postfix_,es);
	}
}

void Text_Dimension_Info::get_show(std::vector<Entity*>& es)const
{
  //TEXT AND ITS FRAME
  //Text * txt = Text::create_me();
  //get_text_frame_show(*txt, es);
  //es.push_back(txt);

	draw_names(es);

}


}//namespace
