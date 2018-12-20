// Cut_Section.cpp: implementation of the Cut_Section class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cut_Section.h"
#include <algorithm>
#include <functional>

#include "File.h"
#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Line.h"
#include "Entity_Calculate.h"
#include "Normal.h"
#include "Block.h"
#include "Text.h"
#include "Matrix_d.h"
#include "Visitor.h"
#include <cassert>
#include "getrace.h"

#include "Global.h"
#include "encode.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Cut_Section,Entity)
Cut_Section::Cut_Section()
MCT_INIT1("Cut_Section")
{

	text_style_ = "Standard";
	text_height_ = 0;
	sel_part_ =0;
	
	dis_in_=0;
	dis_out_=0;
	txt_color_=1;

	group_ent_ = NULL;
}

Cut_Section::Cut_Section(const Cut_Section& rhs)
:Entity(rhs)
MCT_INIT2("Cut_Section")
{
	denote_text_ = rhs.denote_text_;
	text_style_ = rhs.text_style_;

	text_height_ = rhs.text_height_;
	start_ = rhs.start_;
	end_ = rhs.end_;
	three_ = rhs.three_;	
	
	id_blk_cut_in_ = rhs.id_blk_cut_in();	

	section_pos_ = rhs.section_pos_;	
	rect_left_ = rhs.rect_left_;	
	rect_right_ = rhs.rect_right_;	
	dis_in_ = rhs.dis_in_;	
	dis_out_ = rhs.dis_out_;	
	txt_color_ = rhs.txt_color_;	

	Entity* ent=0;
	if(Error::OK == Entity::static_current_db_->entity_from_id(ent,rhs.detail_)){
		Entity* e = ent->clone();
		e->post2db(*Entity::static_current_db_,detail_);
	}
}
Cut_Section& Cut_Section::operator=(const Cut_Section& rhs)
{
	Entity::operator =(rhs);
	if(this == &rhs)
		return *this;
	denote_text_ = rhs.denote_text_;
	text_style_ = rhs.text_style_;
	text_height_ = rhs.text_height_;
	start_ = rhs.start_;
	end_ = rhs.end_;
	three_ = rhs.three_;	

	id_blk_cut_in_ = rhs.id_blk_cut_in();	

	section_pos_ = rhs.section_pos_;	
	rect_left_ = rhs.rect_left_;	
	rect_right_ = rhs.rect_right_;	
	dis_in_ = rhs.dis_in_;	
	dis_out_ = rhs.dis_out_;	
	txt_color_ = rhs.txt_color_;	

	Entity* ent=0;
	if(Error::OK == Entity::static_current_db_->entity_from_id(ent,rhs.detail_)){
		Entity* e = ent->clone();
		e->post2db(*Entity::static_current_db_,detail_);
	}
	return *this;
}
Cut_Section::~Cut_Section()
{
/*
	Entity* ent=0;
	if(Error::OK == Entity::static_current_db_->entity_from_id(ent,detail_)){
		Block* b = (Block*)ent;
		Entity* e = b->back();
		b->erase(e);
	}
*/
}
bool Cut_Section::visit(Visitor& v)
{
	return v.Visit_Cut_Section(*this);
}
void Cut_Section::loadme(File& in)
{
	in >> denote_text_;
	in >> text_style_;
	in >> text_height_;
	start_.load(in);
	end_.load(in);
	three_.load(in);
	id_blk_cut_in_.load(in);
	section_pos_.load(in);
	rect_left_.load(in);
	rect_right_.load(in);
	in >> dis_in_;
	in >> dis_out_;
	in >> txt_color_;

	//读取块
	int num = 0;
	in >> num;
	for(int i=0; i<num; ++i){
		char* classname = NULL;
		in >> classname;
		Runtime_Class* pR = NULL;
		pR = Runtime_Class::load(classname);
		delete [] classname;
		Object* pO = NULL;
		pO = pR->createob();
		Entity* pEnt = static_cast<Entity*>(pO);
		pEnt->load(in);
		section_ents_.push_back(pEnt);
	}

}
void Cut_Section::saveme(const File& out) const
{
	out << denote_text_;
	out << text_style_;
	out << text_height_;
	start_.save(out);
	end_.save(out);
	three_.save(out);

	id_blk_cut_in_.save(out);

	section_pos_.save(out);
	rect_left_.save(out);
	rect_right_.save(out);
	out << dis_in_;
	out << dis_out_;
	out << txt_color_;


	//保存块
	out << section_ents_.size();
	std::vector<Entity*>::const_iterator iter;
	for(iter=section_ents_.begin();iter!=section_ents_.end();++iter){
		Runtime_Class* pR = (*iter)->GetRuntimeClass();
		out << pR->classname;
		(*iter)->save(out);
	}

}
void Cut_Section::save_luame(std::ofstream &out,int tab_num)
{
	lua::string_save(out,"denote_text_",denote_text_,tab_num);
	lua::string_save(out,"text_style_",text_style_,tab_num);
	lua::float_save(out,"text_height_",text_height_,tab_num);
	start_.save_lua(out,"start_",tab_num);
	end_.save_lua(out,"end_",tab_num);
	three_.save_lua(out,"three_",tab_num);
//	id_blk_cut_in_.save_lua(out,"id_blk_cut_in_",tab_num);
	section_pos_.save_lua(out,"section_pos_",tab_num);
	rect_left_.save_lua(out,"rect_left_",tab_num);
	rect_right_.save_lua(out,"rect_right_",tab_num);

	lua::float_save(out,"dis_in_",dis_in_,tab_num);
	lua::float_save(out,"dis_out_",dis_out_,tab_num);
	lua::int_save(out,"txt_color_",txt_color_,tab_num);
}

void Cut_Section::open_luame(lua_State *l)
{
	TRACE_OUT("Cut_Section::open_luame() start \n");
	std::string temp;
  get_value(string,l,temp,"denote_text_");

	denote_text_ = temp;

  get_value(string,l,temp,"text_style_");
	
	text_style_ = temp;

	get_value(number,l,text_height_,"text_height_");
 
	start_.open_lua(l,"start_");
	end_.open_lua(l,"end_");
	three_.open_lua(l,"three_");
//	id_blk_cut_in_.open_lua(l,"id_blk_cut_in_");
	section_pos_.open_lua(l,"section_pos_");
	rect_left_.open_lua(l,"rect_left_");
	rect_right_.open_lua(l,"rect_right_");
	
	get_value(number,l,dis_in_,"dis_in_");
	get_value(number,l,dis_out_,"dis_out_");
	get_value(number,l,txt_color_,"txt_color_");


	TRACE_OUT("Cut_Section::open_luame() end \n");
}

void Cut_Section::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","CUT_SECTION");
	get_str_ent();
	//////////////////////////
	rei_add_str(NULL,"denote_text_","denote_text_");
	rei_add_str(NULL,"text_style_","text_style_");
	rei_add_float(NULL,"text_height_",text_height_);

	rei_add_float(NULL,"start_.x",start_.x);
	rei_add_float(NULL,"start_.y",start_.y);
	rei_add_float(NULL,"start_.z",start_.z);

	rei_add_float(NULL,"end_.x",end_.x);
	rei_add_float(NULL,"end_.y",end_.y);
	rei_add_float(NULL,"end_.z",end_.z);

	rei_add_float(NULL,"three_.x",three_.x);
	rei_add_float(NULL,"three_.y",three_.y);
	rei_add_float(NULL,"three_.z",three_.z);

	rei_add_float(NULL,"section_pos_.x",section_pos_.x);
	rei_add_float(NULL,"section_pos_.y",section_pos_.y);
	rei_add_float(NULL,"section_pos_.z",section_pos_.z);

	rei_add_float(NULL,"rect_left_.x",rect_left_.x);
	rei_add_float(NULL,"rect_left_.y",rect_left_.y);
	rei_add_float(NULL,"rect_left_.z",rect_left_.z);

	rei_add_float(NULL,"rect_right_.x",rect_right_.x);
	rei_add_float(NULL,"rect_right_.y",rect_right_.y);
	rei_add_float(NULL,"rect_right_.z",rect_right_.z);

	rei_add_float(NULL,"dis_in_",dis_in_);
	rei_add_float(NULL,"dis_out_",dis_out_);
	rei_add_int(NULL,"txt_color_",txt_color_);
	rei_get_encode(out);
}

void Cut_Section::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	////////////////////////////////////////////////////////////	
	denote_text_ = rei_get("denote_text_");
	text_style_ = rei_get("text_style_");
	text_height_ = atof(rei_get("text_height_"));

	start_.x = atof(rei_get("start_.x"));
	start_.y = atof(rei_get("start_.y"));
	start_.z = atof(rei_get("start_.z"));

	end_.x = atof(rei_get("end_.x"));
	end_.y = atof(rei_get("end_.y"));
	end_.z = atof(rei_get("end_.z"));

	three_.x = atof(rei_get("three_.x"));
	three_.y = atof(rei_get("three_.y"));
	three_.z = atof(rei_get("three_.z"));

	section_pos_.x = atof(rei_get("section_pos_.x"));
	section_pos_.y = atof(rei_get("section_pos_.y"));
	section_pos_.z = atof(rei_get("section_pos_.z"));

	rect_left_.x = atof(rei_get("rect_left_.x"));
	rect_left_.y = atof(rei_get("rect_left_.y"));
	rect_left_.z = atof(rei_get("rect_left_.z"));

	rect_right_.x = atof(rei_get("rect_right_.x"));
	rect_right_.y = atof(rei_get("rect_right_.y"));
	rect_right_.z = atof(rei_get("rect_right_.z"));

	dis_in_ = atof(rei_get("dis_in_"));
	dis_out_ = atof(rei_get("dis_out_"));
	txt_color_ = atoi(rei_get("txt_color_"));
	rei_quit();


}
void Cut_Section::edit_propertyme(const Edit_Entity& edit)
{
	edit.edit_cut_section(*this);
}
void Cut_Section::get_denote_show(Line (&line)[8],Text (&text)[2]) const
{
	Normal tostart,toend,tothree;
	Line l;
	l.setdata(start_,end_);
	Entity_Calculate calc;
	Point pp;
	calc.line_perpendicular(pp,l,three_);
	tothree.set_data(pp,three_);
	tostart.set_data(end_,start_);
	toend.set_data(start_,end_);

//	Float len = text_height_+4/text_height_+8/text_height_;
	Float len = text_height_;

	line[0].setdata(start_,start_.polarTo(len,toend));
	Point three = start_.polarTo(len,tothree);
	line[1].setdata(start_,three);
	Float arrow_len=text_height_/4;
	Normal nor = tothree;
	nor.set_reverse();
	Float ang = nor.angle_x_axis_two_pi();
	ang -= pi/6;
	Normal n;
	n.set_x_axis_angle(ang);
	line[2].setdata(three,three.polarTo(arrow_len,n));
	ang += pi/3;
	n.set_x_axis_angle(ang);
	line[3].setdata(three,three.polarTo(arrow_len,n));
	line[4].setdata(end_,end_.polarTo(len,tostart));
	three = end_.polarTo(len,tothree);
	line[5].setdata(end_,three);
	line[6].setdata(three,three.polarTo(arrow_len,n));
	ang -= pi/3;
	n.set_x_axis_angle(ang);
	line[7].setdata(three,three.polarTo(arrow_len,n));
	int i=0;
	for(;i<8;++i){
		line[i].color(color());
		line[i].line_style(line_style());
	}
	Point textpos = start_.polarTo(len-8/text_height_,tothree);

	textpos.setdata(textpos.x,textpos.y-len);
	
	text[0].set_database(static_current_db_);
	text[0].style_name(text_style_);
//	text[0].height(text_height_);

	if(EquFloat(start_.x,end_.x) ||EquFloat(start_.y,end_.y) ){
		textpos = textpos.polarTo(text_height_/4,toend);
		text[0].align_point(Text::center_center);
		text[0].rotation(0.0);

	}else{
		text[0].align_point(Text::left_bottom);
		text[0].rotation(toend.angle_x_axis_two_pi());

	}
	text[0].dxf_height(text_height_);

	text[0].setdata(textpos,denote_text_);
//	text[0].color(color());
	text[0].color_index(txt_color_);
	textpos = end_.polarTo(len-8/text_height_,tothree);

	textpos.setdata(textpos.x,textpos.y+len);

	text[1].set_database(static_current_db_);
	text[1].style_name(text_style_);
//	text[1].height(text_height_);

	
	if(EquFloat(start_.x,end_.x) ||EquFloat(start_.y,end_.y) ){
		textpos = textpos.polarTo(text_height_/4,tostart);
		text[1].align_point(Text::center_center);
		text[1].rotation(0.0);

	}else{
		text[1].align_point(Text::right_bottom);
		text[1].rotation(toend.angle_x_axis_two_pi());

	}

	text[1].dxf_height(text_height_);
	text[1].setdata(textpos,denote_text_);
//	text[1].color(color());
	text[1].color_index(txt_color_);
}
void Cut_Section::drawme(Draw_Entity& out) const
{
	out.draw_cut_section(*this);
	std::vector<Entity*>::const_iterator iter;
	for(iter=section_ents_.begin();iter!=section_ents_.end();++iter)
		(*iter)->draw(out);
}
void Cut_Section::xor_drawme(Draw_Entity& out) const
{
	out.xor_draw_cut_section(*this);
}
errorinfo Cut_Section::postme2db(Database& db,Entity_ID& id)
{
	private_db_ = &db;
	return db.entity_push_back(this,id);
}
void Cut_Section::transformbyme(const Matrix& mat)
{
//	REITRACE;
	if(sel_part_ ==1){
		text_height_ *= mat.value(0,0);
		start_.transformby(mat);
		end_.transformby(mat);
		three_.transformby(mat);
		
		rect_left_.transformby(mat);
		rect_right_.transformby(mat);
	}else{
		std::vector<Entity*>::iterator iter;
		for(iter=section_ents_.begin();iter!=section_ents_.end();++iter)
			(*iter)->transformby(mat);		
	}
}
Entity* Cut_Section::cloneme() const
{
	return new Cut_Section(*this);
}
void Cut_Section::closeme()
{
	delete this;
}
bool Cut_Section::intersectme(const Rect& rect) const
{
	Line line[8];
	Text text[2];
	get_denote_show(line,text);
	Entity_Calculate calc;
	int i=0;
	for(;i<8;++i){
		if(calc.linesegment_insect_rect(line[i],rect))
			return true;
	}
	for(i=0;i<2;++i){
		if(text[i].intersect(rect))
			return true;
	}
	std::vector<Entity*>::const_iterator iter;
	for(iter=section_ents_.begin();iter!=section_ents_.end();++iter){
		Rect temp1 = (*iter)->box2d();
		if(temp1.xmax() < rect.xmin())
			continue;
		if(temp1.xmin() > rect.xmax())
			continue;
		if(temp1.ymax() < rect.ymin())
			continue;
		if(temp1.ymin() > rect.ymax())
			continue;
		if((*iter)->intersect(rect)){
			selected_ = (*iter);
			return true;
		}
	}
	return false;
}
bool Cut_Section::envelopme(const Rect& rect) const
{
	std::vector<Entity*>::const_iterator iter;
	for(iter=section_ents_.begin();iter!=section_ents_.end();++iter){
		if(!(*iter)->envelop(rect))
			return false;
	}
	return start_.envelop(rect) && end_.envelop(rect) && three_.envelop(rect);
}
Rect Cut_Section::calc_box2d() const
{
	Rect box2d_;
	std::vector<Entity*> ents;
	Line line[8];
	Text text[2];
	get_denote_show(line,text);
	int i=0;
	for(;i<8;++i)
		ents.push_back(&line[i]);
	for(i=0;i<2;++i)
		ents.push_back(&text[i]);
	
	dlhml::box2d(box2d_, ents);
//	Entity_Calculate calc;
//	calc.get_ents_rect(box2d_,ents);

	//剖面实体
	Rect box;
	box.set_reverse_minmax();
	std::vector<Entity*>::const_iterator iter;
	for(iter=section_ents_.begin();iter!=section_ents_.end();++iter){
		Rect temp = (*iter)->box2d();
		box.xmin(min(box2d_.xmin(),temp.xmin()));
		box.ymin(min(box2d_.ymin(),temp.ymin()));
		box.xmax(max(box2d_.xmax(),temp.xmax()));
		box.ymax(max(box2d_.ymax(),temp.ymax()));
	}
	Rect box_all;
	box_all.xmin(min(box2d_.xmin(),box.xmin()));
	box_all.ymin(min(box2d_.ymin(),box.ymin()));
	box_all.xmax(max(box2d_.xmax(),box.xmax()));
	box_all.ymax(max(box2d_.ymax(),box.ymax()));
	return box_all;
}
bool Cut_Section::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
	return false;
}
bool Cut_Section::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return false;
}
void Cut_Section::drag_startme(const Matrix& mat)
{
}
void Cut_Section::drag_endme(const Matrix& mat)
{
}

void Cut_Section::push_back(Entity* ent)
{
	section_ents_.push_back(ent);
}
void Cut_Section::delete_section()
{
}
int Cut_Section::selected(Entity*ent)
{
	return 0;
}
//09.6.22
void Cut_Section::setctrl(const std::vector<Point>& pts)
{
  if(pts.size() != 1){
    return;
  }
	start_ = pts[0];
	end_ = pts[1];
	three_ = pts[2];
	rect_left_ = pts[3];
	rect_right_ = pts[4];
}
void Cut_Section::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(start_);
  pts.push_back(end_);
  pts.push_back(three_);
  pts.push_back(rect_left_);
  pts.push_back(rect_right_);
}
int  Cut_Section::pt_count() const
{
  return 5;
}
void Cut_Section::setdrag(const std::vector<Point>& pts, int index)
{
  if(pts.empty()){
    return;
  }
	start_ = pts[0];
	end_ = pts[1];
}
void Cut_Section::getdrag(std::vector<Point>& pts)const
{
  pts.push_back(start_);
  pts.push_back(end_);
}


}
