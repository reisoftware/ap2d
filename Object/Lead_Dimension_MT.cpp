// Lead_Dimension_MT.cpp: implementation of the Lead_Dimension_MT class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
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
MY_IMPLEMENT_DYNCREATE(Lead_Dimension_MT,Dimension)
Lead_Dimension_MT::Lead_Dimension_MT()
MCT_INIT1("Lead_Dimension_MT")
{
  //dim_style_val_.arrow_num(ARROW_END);
  align_point(Text::center_center);
	//dim_content_ = NULL;
	dim_sign_ = NULL;
	dim_text("TXT");
	dim_style_val_.txt_frame(Dimension_Style::ArcEdge);
	lead_ = true;
}

Lead_Dimension_MT::Lead_Dimension_MT(const Lead_Dimension_MT& rhs)
:Dimension(rhs)
MCT_INIT2("Lead_Dimension_MT")
{
	//dim_content_ = NULL;
	dim_sign_ = NULL;
	start_ = rhs.start_;
	//end_ = rhs.end_;
	start_pt_rect_ = rhs.start_pt_rect_;
	//string_copy(dim_content_,rhs.dim_content_);
	string_copy(dim_sign_,rhs.dim_sign_);
	lead_ = rhs.lead_;
}
Lead_Dimension_MT& Lead_Dimension_MT::operator=(const Lead_Dimension_MT& rhs)
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
	lead_ = rhs.lead_;
	return *this;
}
Lead_Dimension_MT::~Lead_Dimension_MT()
{
	//string_delete(dim_content_);
	string_delete(dim_sign_);

}

void Lead_Dimension_MT::setdata(const Point& st,const Point& ed)
{
  show_change(true);
	start_ = st;
  text_position(ed);
}

void  Lead_Dimension_MT::start(const Point& st)
{
  show_change(true);
  start_=st;
}
Point Lead_Dimension_MT::start()const
{
  return start_;
}


void Lead_Dimension_MT::end(const Point& ed)				
{
  txt_change(true);
  show_change(true);
  text_position(ed);
}

Point Lead_Dimension_MT::end()const
{
  return text_position();
}


bool Lead_Dimension_MT::visit(Visitor& v)
{
  show_change(true);
	return v.Visit_Lead_Dimension_MT(*this);
}
void Lead_Dimension_MT::loadme(File& in)
{
	load_me(in);
	start_.load(in);
	//end_.load(in);
	start_pt_rect_.load(in);
	color_fact_.load(in);
	in >> dim_sign_;
	in >> lead_;
}
void Lead_Dimension_MT::saveme(const File& out) const
{
	save_me(out);
	start_.save(out);
	//end_.save(out);
	start_pt_rect_.save(out);
	color_fact_.save(out);
	out << dim_sign_;
	out << lead_;
}
void Lead_Dimension_MT::save_luame(std::ofstream &out,int tab_num)
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
void Lead_Dimension_MT::open_luame(lua_State *l)  
{
	TRACE_OUT("Lead_Dimension_MT::open_luame() start\n");
	Dimension::open_luame(l);
	start_.open_lua(l,"start_");
	start_pt_rect_.open_lua(l,"start_pt_rect_");
	color_fact_.open_lua(l,"color_fact_");
	std::string temp;
	get_value(string,l,temp,"dim_sign_");
	string_copy(dim_sign_,temp.c_str());
	
	get_value(number,l,lead_,"lead_");
	txt_change(true);
	TRACE_OUT("Lead_Dimension_MT::open_luame() end\n");

}
void Lead_Dimension_MT::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","LEAD_DIM");
	get_str_ent();
	get_str_dim();
	////////////////////////////////////////////////////////////
	start_.get_str_sub("start_");
	start_pt_rect_.get_str_sub("start_pt_rect_");
	rei_add_str(NULL,"dim_sign_",dim_sign_);
	rei_add_int(NULL,"lead_",lead_);
	rei_get_encode(out);
}

void Lead_Dimension_MT::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	set_from_str_dim();
	////////////////////////////////////////////////////////////
	start_.set_from_str_sub("start_");
	start_pt_rect_.set_from_str_sub("start_pt_rect_");
	dim_sign_ = rei_get("dim_sign_");
	lead_ = atoi(rei_get("lead_"));
	rei_quit();
}

void Lead_Dimension_MT::get_str_sub(char *name)
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
	rei_add_int(NULL,s,lead_);

}
void Lead_Dimension_MT::set_from_str_sub(char *name)
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
	sprintf(s,"%s.lead_",name);
	lead_ = atoi(rei_get(s));

}

//void Lead_Dimension_MT::dim_content(LPCTSTR dim_content)
//{
// txt_change(true);
// string_copy(dim_content_,dim_content);
//}
//LPCTSTR Lead_Dimension_MT::dim_content() const
//{
//	return dim_content_;
//}
void Lead_Dimension_MT::dim_sign(LPCTSTR dim_sign)
{
 txt_change(true);
 string_copy(dim_sign_,dim_sign);
}
LPCTSTR Lead_Dimension_MT::dim_sign() const
{
	return dim_sign_;
}
void Lead_Dimension_MT::edit_propertyme(const Edit_Entity& edit)
{
  show_change(true);
//	edit.edit_lead_dim(*this);
}

//void Lead_Dimension_MT::drawme(Draw_Entity& out) const
//{
//	out.draw_lead_dim(*this);
//}
//
//void Lead_Dimension_MT::xor_drawme(Draw_Entity& out) const
//{
//	out.xor_draw_lead_dim(*this);
//}

errorinfo Lead_Dimension_MT::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Lead_Dimension_MT::transformbyme(const Matrix& mat)
{
//	REITRACE;
  show_change(true);
//	REITRACE;
  Dimension::transformbyme(mat);
//	REITRACE;
	//text_position_.transformby(mat);
	start_.transformby(mat);
//	REITRACE;

	start_pt_rect_.transformby(mat);
	//	REITRACE;
}
void Lead_Dimension_MT::drag_startme(const Matrix& mat)
{
  show_change(true);
	start_.transformby(mat);
	start_pt_rect_.transformby(mat);
}
void Lead_Dimension_MT::drag_endme(const Matrix& mat)
{
  show_change(true);
	text_position_.transformby(mat);
	//end_.transformby(mat);
}

Entity* Lead_Dimension_MT::cloneme() const
{
	return new Lead_Dimension_MT(*this);
}
bool Lead_Dimension_MT::start_in_rect() const
{
	Rect zero;
	if(zero == start_pt_rect_)
		return false;
	if(start_.envelop(start_pt_rect_))
		return true;
	return false;
}
void Lead_Dimension_MT::closeme()
{
	delete this;
}
bool Lead_Dimension_MT::get_line(Line& line) const
{
  //Point ed;
  Text txt;
  get_text_show(txt);
  Dimension_Style::Txt_Frame ts = dim_style_val_.txt_frame();
  ////圆型外框
  if(ts == Dimension_Style::CircleEdge){
    Point c = txt.center();
    std::vector<Circle*> crs;
    dim_style_val_.get_text_circle(txt,crs);
    if(crs.empty()){
      line.setdata(start_,c);
      return true;
    }
    Circle cr = *(crs.front());
    //c = cr.center();
    c = text_position();
    Normal nor;
    nor.set_data(c,start_);
    Point ed = c.polarTo(cr.radius(),nor);
    line.setdata(start_,ed);
    destory(crs);
    return true;
  }
  ////其他形状外框
  else{
//    Point pts[4];
//    txt.real_box_point(pts);
    //const std::vector<Point>& pts = txt.real_box_point();
		std::vector<Point> pts;
		txt.real_box_pt(pts);
		assert(pts.size()>=4);
    ////若st点在框内，则不画
//    if(dlhml::is_in(start_, pts)){
//      line.setdata(start_,start_);
//      return true;
//    }
    ////否则，选择最近的点连接
    int min_dis_id = geo2d::min_dis(pts, start_);

//    int min_dis_id=0;
//
//    Float min_dis=start_.distanceto2d(pts[0]);
//    Float dis=0;
//    int i=0;
//    for(i=1;i<4;i++){
//      dis = start_.distanceto2d(pts[i]);
//      if(LessThen(dis,min_dis)){
//        min_dis = dis;
//        min_dis_id = i;
//      }
//    }
//
    line.setdata(start_,pts[min_dis_id]);
    //line.setdata(start_,txt.position());
	  return true;
    //ed = pts[min_dis_id];
  }

	//line.setdata(start_,ed);
	return true;
}

void Lead_Dimension_MT::get_line(std::vector<Entity*>& es)const
{
  //LINE
  Line * ln = Line::create_me();
  get_line_show(*ln);
  es.push_back(ln);
}

void Lead_Dimension_MT::get_show(std::vector<Entity*>& es)const
{
	////不显示牵引线
	if(lead_){
		get_line(es);
		//LINE
		//ARROW
		Line ln;
		get_line_show(ln);
		dim_style_val_.get_arrow(ln,es);
	}

  //TEXT AND ITS FRAME
  Text * txt = Text::create_me();
  get_text_frame_show(*txt, es); 
  es.push_back(txt);
}
//  Line * ln = Line::create_me();
//  get_line_show(*ln);
//  es.push_back(ln);
//   std::vector<Line*> slns;
//   get_start_arrow_line_show(slns);
//   push(slns,es);
//   std::vector<Circle*> scrs;
//   get_start_arrow_circle_show(scrs);
//   push(scrs,es);

  
void Lead_Dimension_MT::get_line_show(Line& ln)const
{
	get_line(ln);
	ln.line_style(line_style());
	//ln.color_index(dim_style_val_.text_frame_color());
	ln.color_index(dim_style_val_.line_color());
}
//bool Lead_Dimension_MT::get_line_show(std::vector<Line*>& lines) const
//{
//	get_line(*lines[0]);
//	lines[0]->line_style(line_style());
//	lines[0]->color(color());
//	return true;
//}

int Lead_Dimension_MT::get_start_arrow_line_show(std::vector<Line*>& lines) const
{
  Line start;
  get_line(start);
  const Dimension_Style* ds=&dim_style_val_;

  Normal nor;
  nor.set_data(text_position(),start_);

  ds->get_arrow_line(start_,nor,lines);
  for(int i=0;i<lines.size();++i){
    lines[i]->line_style(line_style());
    lines[i]->color_index(dim_style_val_.text_frame_color());
  }
  //return num;
  return 0;
}
int Lead_Dimension_MT::get_start_arrow_circle_show(std::vector<Circle*>& circles) const
{
  Line start;
  get_line(start);
  const Dimension_Style* ds=&dim_style_val_;

  ds->get_arrow_circle(start_,circles);
  for(int i=0;i<circles.size();++i){
    circles[i]->line_style(line_style());
    circles[i]->color_index(dim_style_val_.text_frame_color());
  }
  //return num;
  return 0;
}



bool Lead_Dimension_MT::intersectme(const Rect& rect) const
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
bool Lead_Dimension_MT::envelopme(const Rect& rect) const
{
	Text text;
	get_text_show(text);
	return start_.envelop(rect) && text_position().envelop(rect)
		&& text.envelop(rect);
}

//Rect Lead_Dimension_MT::calc_box2d() const
//{
//	Rect box2d_;
//	Line line;
//	get_line(line);
//	Text text;
//	get_text_show(text);
//	std::vector<Entity*> ents;
//	ents.push_back(&line);
//	ents.push_back(&text);
//
//	dlhml::box2d(box2d_, ents);
////	Entity_Calculate calc;
////	calc.get_ents_rect(box2d_,ents);
//	return box2d_;
//}
Rect Lead_Dimension_MT::get_txt_rect()
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

bool Lead_Dimension_MT::snap_endpointme(Point& pt,const Rect& rect) const
{
	Line line;
	get_line(line);
	return line.snap_endpoint(pt,rect);
}
bool Lead_Dimension_MT::snap_middle_pointme(Point& pt,const Rect& rect) const
{
	Line line;
	get_line(line);
	return line.snap_middle_point(pt,rect);
}
bool Lead_Dimension_MT::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
	Line line;
	get_line(line);
	return line.snap_nearest_point(pt,rect);
}
//bool Lead_Dimension_MT::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////	Entity_Snap_Implement<Lead_Dimension_MT> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Lead_Dimension_MT::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}
Point Lead_Dimension_MT::get_range_pt() 
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


  //pts.push_back(end_ );
//		if(pts.size() != 2){
//			return;
//		}
//		//end_ = pts[1];
//09.6.22
void Lead_Dimension_MT::setctrl(const std::vector<Point>& pts)
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
void Lead_Dimension_MT::getctrl(std::vector<Point>& pts) const
{
	if(lead_){
	  pts.push_back(start_);
	}
	pts.push_back(text_position());
}
int  Lead_Dimension_MT::pt_count()const
{
  return lead_ ? 2 : 1;
}
void Lead_Dimension_MT::setdrag(const std::vector<Point>& pts, int index)
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
void Lead_Dimension_MT::getdrag(std::vector<Point>& pts) const
{
	pts.push_back(text_position());
	if(lead_){
		pts.push_back(start_);
	}
}


}
