// Lead_Line_Dim.cpp: implementation of the Lead_Line_Dim class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lead_Line_Dim.h"
#include "Lead_Dimension_MT.h"
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
//#include "..\DrawDll\reitrace.h"

#include "geo2d.h"
#include "getrace.h"
#include "encode.h"
#include <cassert>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Lead_Line_Dim,Dimension)
Lead_Line_Dim::Lead_Line_Dim()
MCT_INIT1("Lead_Line_Dim")
{
	align_point(Text::center_center);
	dim_sign_ = NULL;
	dim_text("TXT");
	dim_style_val_.txt_frame(Dimension_Style::Baseline);
}

Lead_Line_Dim::Lead_Line_Dim(const Lead_Line_Dim& rhs)
:Dimension(rhs)
MCT_INIT2("Lead_Line_Dim")
{
	//dim_content_ = NULL;
	dim_sign_ = NULL;
	start_ = rhs.start_;
	//end_ = rhs.end_;
	start_pt_rect_ = rhs.start_pt_rect_;
	//string_copy(dim_content_,rhs.dim_content_);
	string_copy(dim_sign_,rhs.dim_sign_);
}
Lead_Line_Dim& Lead_Line_Dim::operator=(const Lead_Line_Dim& rhs)
{
	Dimension::operator =(rhs);
	if(this == &rhs)
		return *this;
	//dim_content_ = NULL;
	dim_sign_ = NULL;
	start_ = rhs.start_;
	//end_ = rhs.end_;
	start_pt_rect_ = rhs.start_pt_rect_;
	//string_copy(dim_content_,rhs.dim_content_);
	string_copy(dim_sign_,rhs.dim_sign_);
	return *this;
}
Lead_Line_Dim::~Lead_Line_Dim()
{
	//string_delete(dim_content_);
	string_delete(dim_sign_);

}

void Lead_Line_Dim::setdata(const Point& st,const Point& ed)
{
  show_change(true);
	start_ = st;
  text_position(ed);
}

void  Lead_Line_Dim::start(const Point& st)
{
  show_change(true);
  start_=st;
}
Point Lead_Line_Dim::start()const
{
  return start_;
}


void Lead_Line_Dim::end(const Point& ed)				
{
  txt_change(true);
  show_change(true);
  text_position(ed);
}

Point Lead_Line_Dim::end()const
{
  return text_position();
}


bool Lead_Line_Dim::visit(Visitor& v)
{
  show_change(true);
	return v.Visit_Lead_Line_Dim(*this);
}
void Lead_Line_Dim::loadme(File& in)
{
	load_me(in);
	start_.load(in);
	//end_.load(in);
	start_pt_rect_.load(in);
	color_fact_.load(in);
	in >> dim_sign_;
}
void Lead_Line_Dim::saveme(const File& out) const
{
	save_me(out);
	start_.save(out);
	//end_.save(out);
	start_pt_rect_.save(out);
	color_fact_.save(out);
	out << dim_sign_;
}
void Lead_Line_Dim::save_luame(std::ofstream &out,int tab_num)
{
	Dimension::save_luame(out,tab_num);
	start_.save_lua(out,"start_",tab_num);

	start_pt_rect_.save_lua(out,"start_pt_rect_",tab_num);
	color_fact_.save_lua(out,"color_fact_",tab_num);

	if(dim_sign_)
		lua::string_save(out,"dim_sign_",dim_sign_,tab_num);
	else
		lua::string_save(out,"dim_sign_"," ",tab_num);
	lua::bool_save(out,"lead_",lead_,tab_num);

}
void Lead_Line_Dim::open_luame(lua_State *l)  
{
	TRACE_OUT("Lead_Line_Dim::open_luame() start\n");
	Dimension::open_luame(l);
	start_.open_lua(l,"start_");
	start_pt_rect_.open_lua(l,"start_pt_rect_");
	color_fact_.open_lua(l,"color_fact_");
	std::string temp;
	get_value(string,l,temp,"dim_sign_");
	string_copy(dim_sign_,temp.c_str());
	
	txt_change(true);
	TRACE_OUT("Lead_Line_Dim::open_luame() end\n");

}
void Lead_Line_Dim::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","LEAD_DIM");
	get_str_ent();
	get_str_dim();
	////////////////////////////////////////////////////////////
	start_.get_str_sub("start_");
	start_pt_rect_.get_str_sub("start_pt_rect_");
	rei_add_str(NULL,"dim_sign_",dim_sign_);
	rei_get_encode(out);
}

void Lead_Line_Dim::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	set_from_str_dim();
	////////////////////////////////////////////////////////////
	start_.set_from_str_sub("start_");
	start_pt_rect_.set_from_str_sub("start_pt_rect_");
	dim_sign_ = rei_get("dim_sign_");
	rei_quit();
}

void Lead_Line_Dim::get_str_sub(char *name)
{
	char s[MAX_REDIS_STR];
	get_str_ent_sub(name);
	get_str_dim_sub(name);
	////////////////////////////////////////////////////////////
	sprintf(s,"%s.start_",name);
	start_.get_str_sub(s);
	sprintf(s,"%s.start_pt_rect_",name);
	start_pt_rect_.get_str_sub(s);
	sprintf(s,"%s.dim_sign_",name);
	rei_add_str(NULL,s,dim_sign_);
	sprintf(s,"%s.dim_sign_",name);

}
void Lead_Line_Dim::set_from_str_sub(char *name)
{
	char s[MAX_REDIS_STR];
	set_from_str_ent_sub(name);
	set_from_str_dim_sub(name);
	////////////////////////////////////////////////////////////
	sprintf(s,"%s.start_",name);
	start_.set_from_str_sub(s);
	sprintf(s,"%s.start_pt_rect_",name);
	start_pt_rect_.set_from_str_sub(s);
	sprintf(s,"%s.dim_sign_",name);
	dim_sign_ = rei_get(s);

}

//void Lead_Line_Dim::dim_content(LPCTSTR dim_content)
//{
// txt_change(true);
// string_copy(dim_content_,dim_content);
//}
//LPCTSTR Lead_Line_Dim::dim_content() const
//{
//	return dim_content_;
//}
void Lead_Line_Dim::dim_sign(LPCTSTR dim_sign)
{
 txt_change(true);
 string_copy(dim_sign_,dim_sign);
}
LPCTSTR Lead_Line_Dim::dim_sign() const
{
	return dim_sign_;
}
void Lead_Line_Dim::edit_propertyme(const Edit_Entity& edit)
{
  show_change(true);
}


errorinfo Lead_Line_Dim::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Lead_Line_Dim::transformbyme(const Matrix& mat)
{
	show_change(true);
	Dimension::transformbyme(mat);
	start_.transformby(mat);

	start_pt_rect_.transformby(mat);
}
void Lead_Line_Dim::drag_startme(const Matrix& mat)
{
	show_change(true);
	start_.transformby(mat);
	start_pt_rect_.transformby(mat);
}
void Lead_Line_Dim::drag_endme(const Matrix& mat)
{
	show_change(true);
	text_position_.transformby(mat);
}

Entity* Lead_Line_Dim::cloneme() const
{
	return new Lead_Line_Dim(*this);
}
bool Lead_Line_Dim::start_in_rect() const
{
	Rect zero;
	if(zero == start_pt_rect_)
		return false;
	if(start_.envelop(start_pt_rect_))
		return true;
	return false;
}
void Lead_Line_Dim::closeme()
{
	delete this;
}
bool Lead_Line_Dim::get_line(Line& line) const
{
	//Point ed;
	Text txt;
	get_text_show(txt);
	Dimension_Style::Txt_Frame ts = dim_style_val_.txt_frame();
	////圆型外框
	if(ts == Dimension_Style::Baseline)
	{  
		std::vector<Point> pts;
		txt.real_box_pt(pts);
		assert(pts.size()>=4);
		line.setdata(start_,txt.position());
		return true;
	}

	//line.setdata(start_,ed);
	return true;
}

void Lead_Line_Dim::get_line(std::vector<Entity*>& es)const
{
	//斜线
	Line * ln_lean = Line::create_me();
	ln_lean->color_index(dim_style_val_.line_color());

	if(start_.x > text_position_.x)
	{
		Point pt_end(text_position_.x+text_max_len_,text_position_.y,text_position_.z);
		ln_lean->setdata(start_,pt_end);
	}
	else
	{
		ln_lean->setdata(start_,text_position_);
	}
	es.push_back(ln_lean);

	//横线
	Line * ln_level = Line::create_me();
	ln_level->color_index(dim_style_val_.line_color());

	if(start_.x > text_position_.x)
	{
		Point pt_st(text_position_.x+text_max_len_,text_position_.y,text_position_.z);
		Point pt_end(pt_st.x-text_max_len_,pt_st.y,pt_st.z);
		ln_level->setdata(pt_st,pt_end);
	}
	else
	{
		Point pt_end(text_position_.x+text_max_len_,text_position_.y,text_position_.z);
		ln_level->setdata(text_position_,pt_end);
	}
	es.push_back(ln_level);


}

void Lead_Line_Dim::get_show(std::vector<Entity*>& es)const
{
	//文字
	Text * text = Text::create_me();
	text->set_database(static_current_db_);
	text->rotation(text_rotation_);
	text->setdata(text_position_,dim_text_);
	//text->width_factor(0.1);
	text->color_index(dim_style_val_.text_color());
	dim_style_val_.get_text(*text);

	txt_record(*text);	  
	text->align_point(Text::left_bottom);
	es.push_back(text);

	text_max_len_ = text->box2d().width();
	//直线
	get_line(es);
}



  
void Lead_Line_Dim::get_line_show(Line& ln)const
{
	get_line(ln);
	ln.line_style(line_style());
	ln.color_index(dim_style_val_.line_color());
}


bool Lead_Line_Dim::intersectme(const Rect& rect) const
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
bool Lead_Line_Dim::envelopme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
	return start_.envelop(rect) && text_position().envelop(rect)
		&& text.envelop(rect);
}

Rect Lead_Line_Dim::get_txt_rect()
{
	Rect rect;
	Text text;
	get_text_show(text);
	std::vector<Entity*> ents;
	ents.push_back(&text);

	dlhml::box2d(rect, ents);
//	Entity_Calculate calc;
//	calc.get_ents_rect(rect,ents);
	return rect;

}
bool Lead_Line_Dim::snap_endpointme(Point& pt,const Rect& rect) const
{
	Line line;
	get_line(line);
	return line.snap_endpoint(pt,rect);
}
bool Lead_Line_Dim::snap_middle_pointme(Point& pt,const Rect& rect) const
{
	Line line;
	get_line(line);
	return line.snap_middle_point(pt,rect);
}
bool Lead_Line_Dim::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
	Line line;
	get_line(line);
	return line.snap_nearest_point(pt,rect);
}

bool Lead_Line_Dim::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}
Point Lead_Line_Dim::get_range_pt() 
{
	Rect lead_rect = get_txt_rect();
	std::vector<float> x_maxs,x_mins,y_maxs,y_mins;
	x_maxs.push_back(lead_rect.xmax());
	x_mins.push_back(lead_rect.xmin());
	y_maxs.push_back(lead_rect.ymax());
	y_mins.push_back(lead_rect.ymin());
	
	Rect re_range;
	std::vector<float>::iterator iter_max_x = std::max_element(x_maxs.begin(),x_maxs.end());
	std::vector<float>::iterator iter_min_x = std::min_element(x_mins.begin(),x_mins.end());
	std::vector<float>::iterator iter_max_y = std::max_element(y_maxs.begin(),y_maxs.end());
	std::vector<float>::iterator iter_min_y = std::min_element(y_mins.begin(),y_mins.end());
	re_range.xmax(*iter_max_x);
	re_range.xmin(*iter_min_x);
	re_range.ymax(*iter_max_y);
	re_range.ymin(*iter_min_y);
	Point rect_center,pt_lead_start,pt_lead_end;
	pt_lead_start = start_;
	pt_lead_end = text_position();
	rect_center.setdata((re_range.xmax()+re_range.xmin())/2.0f,(re_range.ymax()+re_range.ymin())/2.0f);
	Point end_pt;
	if(pt_lead_start.x>rect_center.x){
		if(pt_lead_start.y>rect_center.y){
			end_pt.setdata(re_range.xmax(),re_range.ymax());
		}else{
			end_pt.setdata(re_range.xmax(),re_range.ymin());
		}
	}else{
		if(pt_lead_start.y>rect_center.y){
			end_pt.setdata(re_range.xmin(),re_range.ymax());
		}else{
			end_pt.setdata(re_range.xmin(),re_range.ymin());
		}
	}
	return end_pt;
}
//09.6.22
void Lead_Line_Dim::setctrl(const std::vector<Point>& pts)
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
void Lead_Line_Dim::getctrl(std::vector<Point>& pts) const
{
	if(lead_){
	  pts.push_back(start_);
	}
	pts.push_back(text_position());
}
int  Lead_Line_Dim::pt_count()const
{
  return lead_ ? 2 : 1;
}
void Lead_Line_Dim::setdrag(const std::vector<Point>& pts, int index)
{
	assert(pts.size() > index);
  show_change(true);
	switch(index){
		case 0:
			text_position(pts[index]);
			break;
		case 1:
			start_ = pts[index];
			break;
	}
}
void Lead_Line_Dim::getdrag(std::vector<Point>& pts) const
{
	pts.push_back(text_position());
	if(lead_){
		pts.push_back(start_);
	}
}


}
