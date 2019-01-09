// Lead_Dimension_Info.cpp: implementation of the Lead_Dimension_Info class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lead_Dimension_Info.h"
#include "Global.h"
#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Entity_Snap_Implement.h"
#include "Line.h"
#include "Circle.h"
#include "Normal.h"
#include "Entity_Calculate.h"
#include "Text.h"
#include "File.h"
#include "Visitor.h"
#include <algorithm>
#include <functional>

#include "encode.h"
#include <cassert>
#include <iostream>

#include "Replace_String.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Lead_Dimension_Info,Dimension)
Lead_Dimension_Info::Lead_Dimension_Info()
MCT_INIT1("Lead_Dimension_Info")
{
	//dim_style_val_.arrow_num(ARROW_END);
	align_point(Text::center_center);
	//dim_content_ = NULL;
	dim_text("TXT");
	dim_style_val_.txt_frame(Dimension_Style::ArcEdge);
	lead_ = true;
	text_max_len_ = 0;

	names_.push_back("name1");
	names_.push_back("name2");
	names_.push_back("name3");
}

Lead_Dimension_Info::Lead_Dimension_Info(const Lead_Dimension_Info& rhs)
:Dimension(rhs)
MCT_INIT2("Lead_Dimension_Info")
{
	start_ = rhs.start_;
	lead_ = rhs.lead_;
	names_ = rhs.names_;

	rep_db_ = rhs.rep_db_;

}
Lead_Dimension_Info& Lead_Dimension_Info::operator=(const Lead_Dimension_Info& rhs)
{
	Dimension::operator =(rhs);
	if(this == &rhs)
		return *this;
	start_ = rhs.start_;
	lead_ = rhs.lead_;
	names_ = rhs.names_;

	rep_db_ = rhs.rep_db_;

	return *this;
}
Lead_Dimension_Info::~Lead_Dimension_Info()
{
	//string_delete(dim_sign_);

}

void Lead_Dimension_Info::setdata(const Point& st,const Point& ed)
{
	show_change(true);
	start_ = st;
	text_position(ed);
}

void  Lead_Dimension_Info::start(const Point& st)
{
  show_change(true);
  start_=st;
}
Point Lead_Dimension_Info::start()const
{
  return start_;
}


void Lead_Dimension_Info::end(const Point& ed)				
{
  txt_change(true);
  show_change(true);
  text_position(ed);
}

Point Lead_Dimension_Info::end()const
{
  return text_position();
}


bool Lead_Dimension_Info::visit(Visitor& v)
{
  show_change(true);
	return v.visit_Lead_Dimension_Info(*this);
}
void Lead_Dimension_Info::loadme(File& in)
{
	load_me(in);
	start_.load(in);
	in >> lead_;
}
void Lead_Dimension_Info::saveme(const File& out) const
{
	save_me(out);
	start_.save(out);
	out << lead_;
}
void Lead_Dimension_Info::save_luame(std::ofstream &out,int tab_num)
{
	Dimension::save_luame(out,tab_num);
	start_.save_lua(out,"start_",tab_num);
	lua::bool_save(out,"lead_",lead_,tab_num);
	lua::save(out,"names_",names_,tab_num);

}
void Lead_Dimension_Info::open_luame(lua_State *l)  
{
	Dimension::open_luame(l);
	start_.open_lua(l,"start_");
	std::string temp;	
	get_value(number,l,lead_,"lead_");

	names_.clear();
	lua::open(l,"names_",names_);

	txt_change(true);

}
void Lead_Dimension_Info::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","LEAD_DIM");
	get_str_ent();
	get_str_dim();
	////////////////////////////////////////////////////////////
	start_.get_str_sub("start_");
	rei_add_int(NULL,"lead_",lead_);
	rei_get_encode(out);
}

void Lead_Dimension_Info::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	set_from_str_dim();
	////////////////////////////////////////////////////////////
	start_.set_from_str_sub("start_");
	lead_ = atoi(rei_get("lead_"));
	rei_quit();
}

void Lead_Dimension_Info::get_str_sub(char *name)
{
	char s[MAX_REDIS_STR];
	get_str_ent_sub(name);
	get_str_dim_sub(name);
	////////////////////////////////////////////////////////////
	sprintf(s,"%s.start_",name);
	start_.get_str_sub(s);
	sprintf(s,"%s.lead_",name);
	rei_add_int(NULL,s,lead_);

}
void Lead_Dimension_Info::set_from_str_sub(char *name)
{
	char s[MAX_REDIS_STR];
	set_from_str_ent_sub(name);
	set_from_str_dim_sub(name);
	////////////////////////////////////////////////////////////
	sprintf(s,"%s.start_",name);
	start_.set_from_str_sub(s);
	sprintf(s,"%s.lead_",name);
	lead_ = atoi(rei_get(s));

}


Entity* Lead_Dimension_Info::cloneme() const
{
	return new Lead_Dimension_Info(*this);
}
void Lead_Dimension_Info::closeme()
{
	delete this;
} 
double Lead_Dimension_Info::get_txt_max_width(std::vector<Entity*>& es)const
{

	double width = 0;
	int max_len = 0;
	for(int i=0;i<names_.size();i++){
		int len = strlen(names_[i].c_str());
		int short_len = check_null_replace(names_[i]);
		len = len - short_len;
		max_len = max(len,max_len);
	}
	//由于字宽的问题进行乘以固定比例
	float max_len_t = max_len - 4.5;//考虑字宽的问题
	//float max_len_t = max_len;
	width = max_len_t*dim_style_val_.text_height();
	return width;
}
void Lead_Dimension_Info::get_line(std::vector<Entity*>& es)const
{  
	Line * ln = Line::create_me();
		//添加两个牵引线，符合tekla显示方式，
	Line * ln_level = Line::create_me();

	if(start_.x > text_position_.x)
	{
		//float width = get_txt_max_width(es);
		float width = text_max_len_;
		//此处是绘制横线的位置，处理时最关键的地方
		double txt_pos_offset = width*0.45;
		if(text_max_len_ > 850)
		{
			txt_pos_offset = 0;
		}
		else
		{
			txt_pos_offset = width*0.45;
		}
		Point txt_pos = Point(text_position_.x+txt_pos_offset,text_position_.y);
		ln->setdata(start_,txt_pos);
		ln->color_index(dim_style_val_.line_color());
		es.push_back(ln);



		double left_dis = width-txt_pos_offset/2;
	//	ln_level->setdata(text_position_,Point(text_position_.x-left_dis,text_position_.y));
		ln_level->setdata(txt_pos,Point(text_position_.x-left_dis,text_position_.y));
	}
	else
	{
		ln->setdata(start_,text_position_);
		ln->color_index(dim_style_val_.line_color());
		es.push_back(ln);

		//添加两个牵引线，符合tekla显示方式，

		//float width = get_txt_max_width(es);
		float width = text_max_len_;
		//此处是绘制横线的位置，处理时最关键的地方
		ln_level->setdata(text_position_,Point(text_position_.x+width,text_position_.y));
	
	}
	
	ln_level->color_index(dim_style_val_.line_color());
	es.push_back(ln_level);
}






//**基类处理回调函数**********************************************************************************************
  


bool Lead_Dimension_Info::intersectme(const Rect& rect) const
{
	Line line;
	line.setdata(start_,text_position_);
	Entity_Calculate calc;
	if(calc.linesegment_insect_rect(line,rect))
		return true;
	Text text;
	get_text_show(text);
	if(text.intersect(rect))
		return true;
	return false;
}
bool Lead_Dimension_Info::envelopme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
	return start_.envelop(rect) && text_position().envelop(rect)
		&& text.envelop(rect);
}



bool Lead_Dimension_Info::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}


//09.6.22
void Lead_Dimension_Info::setctrl(const std::vector<Point>& pts)
{
	show_change(true);
	assert(pts.size() >= 1);
	start_ = pts[0];
	if(lead_){
		assert(pts.size() >= 2);
		text_position(pts[1]); 
	}
	else{
		assert(pts.size() >= 1);
		text_position(pts[0]); 
	}
}
void Lead_Dimension_Info::getctrl(std::vector<Point>& pts) const
{
	if(lead_){
	  pts.push_back(start_);
	}
	pts.push_back(text_position());
}
int  Lead_Dimension_Info::pt_count()const
{
  return lead_ ? 2 : 1;
}

void Lead_Dimension_Info::edit_propertyme(const Edit_Entity& edit)
{
  show_change(true);
//	edit.edit_lead_dim(*this);
}

errorinfo Lead_Dimension_Info::postme2db(Database& db,Entity_ID& id)
{
	show_change(true);
	return db.entity_push_back(this,id);
}

void Lead_Dimension_Info::transformbyme(const Matrix& mat)
{
	show_change(true);
//	Dimension::transformbyme(mat);

	start_.transformby(mat);
	//基类里有text_position_的转换，此处不需要转换
	text_position_.transformby(mat);
}
void Lead_Dimension_Info::drag_startme(const Matrix& mat)
{
	show_change(true);
//	Dimension::transformbyme(mat);
	start_.transformby(mat);
	text_position_.transformby(mat);
}
void Lead_Dimension_Info::drag_endme(const Matrix& mat)
{
	show_change(true);
//	Dimension::transformbyme(mat);
	start_.transformby(mat);
	text_position_.transformby(mat);
}
//**基类处理回调函数**********************************************************************************************

void Lead_Dimension_Info::rep_text(Text *t,std::vector<Entity*>& es)const 
{
	double max_len = 0;
	for(int i=0;i<rep_db_.size();i++){
	
		Replace_String rep;
		max_len = rep.rep_text(rep_db_[i].rep_str_,t,rep_db_[i].style_,rep_db_[i].sign_,rep_db_[i].postfix_,es);
	
		//怎么记录此时是不是最长的呢。
		//此时很麻烦，如果当时此行是最长的，替换完成后变短了，总体长度就要变短，但是它是不是最长的，就不应该影响具体长度变化。	
		//row_lens_.push_back(const_cast<double>(max_len));
	//	row_lens_.push_back(max_len);
	
		if(text_max_len_ <= max_len)
		{
			text_max_len_ = max_len;
		}
		

	}

}

int Lead_Dimension_Info::check_null_replace(std::string name)const 
{
	//查找串中有无需要替代成空串的串，有的话返回替换串的长度，用于处理牵引线的长度
	for(int i=0;i<rep_db_.size();i++){
		int pos = name.find(rep_db_[i].rep_str_);
		if(pos != -1){
			if(strcmp(rep_db_[i].sign_.c_str(),"")==0 )
				return rep_db_[i].rep_str_.length();
			else 
				return 0;
		}
	}
	return 0;
}


void Lead_Dimension_Info::get_show(std::vector<Entity*>& es)const
{
//	std::string sss = rep_str_;

	

	//防止拖动时全是乱线添加判断
//	if(!seled_)
		draw_names(es);
		
	if(lead_){
		get_line(es);
	}
}





void Lead_Dimension_Info::draw_names(std::vector<Entity*>& es)const
{
	//作用是在基准线上移距离，因为导出dxf会出现文字最低端和牵引线是重合的
	double up_dis = 5;

	Point pos = text_position_;
	if(start_.x > text_position_.x)
		pos.setdata(pos.x - get_txt_max_width(es),pos.y + up_dis);
	else
		pos.setdata(pos.x,pos.y + up_dis);

	std::vector<std::string> ns;
	for(int i=names_.size()-1;i>=0;i--)
	{
		ns.push_back(names_[i]);
			
	}


	int j=0;
	//每行之间的间隔
	double row_dis = dim_style_val_.text_height()/2.0;
	for(i=0;i<ns.size();i++)
	{
		Text * text = Text::create_me();
		text->set_database(static_current_db_);
		text->rotation(text_rotation_);
		text->setdata(pos,ns[i]);
		//text->width_factor(0.1);
		text->color_index(dim_style_val_.text_color());
		dim_style_val_.get_text(*text);

		txt_record(*text);	  
		text->align_point(Text::left_bottom);
		es.push_back(text);

		j++;
		pos.y = text_position_.y + j*dim_style_val_.text_height()+row_dis*j  + up_dis;


		//创建完成后马上进行替换
		rep_text(text,es);
		
//		row_lens_.push_back(text->box2d().width());

		if(text_max_len_ <= text->box2d().width())
		{
			text_max_len_ = text->box2d().width();
		}
	}

}


void Lead_Dimension_Info::setdrag(const std::vector<Point>& pts, int index)
{
	assert(pts.size() > index);
	int count = pts.size();
	show_change(true);
	switch(index){
		case 0:
		//	start_ = pts[index];
			text_position(pts[index]);
		//	text_position(start_);
			break;
		case 1:
			start_ = pts[index];
			break;
	}
}
void Lead_Dimension_Info::getdrag(std::vector<Point>& pts) const
{
	//拖动处理
	pts.push_back(text_position());
	if(lead_){
		pts.push_back(start_);
	}
}




}
