// Line.cpp: implementation of the Line class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Line.h"
#include "Global.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Entity_Snap_Implement.h"
#include "Entity_Calculate.h"
#include "Edit_Entity.h"
#include "Visitor.h"

#include "Normal.h"
#include <cassert>

#include "Cloud_Line.h"
#include "Entity_Calculate.h"
#include "intersect.h"
#include "getrace.h"
#include "encode.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Line,Entity)
Line::Line()
MCT_INIT1("Line")
{
//	myclass_ = 'L';
	arrow_pos_ = NULL;
//	string_copy(arrow_pos_,"Standard");
	arrow_pos_ = 0;
	arrowsize_ = 8;

}
Line::Line(const Point& st,const Point& ed)
:st_(st)
,ed_(ed)
MCT_INIT2("Line")

{

}
Line::Line(const Line& rhs)
:Entity(rhs)
,st_(rhs.st_)
,ed_(rhs.ed_)
MCT_INIT2("Line")
{
//	string_copy(arrow_pos_,rhs.arrow_pos_);
	arrow_pos_ = rhs.arrow_pos_;
	arrowsize_ = rhs.arrowsize_;
}
Line& Line::operator=(const Line& rhs)
{
	Entity::operator=(rhs);
	if(this == &rhs)
		return *this;
	st_ = rhs.st_;
	ed_ = rhs.ed_;
//	myclass_ = rhs.myclass_;
//	string_copy(dim_style_,rhs.dim_style_);
//	string_copy(arrow_pos_,rhs.arrow_pos_);
	arrow_pos_ = rhs.arrow_pos_;
	arrowsize_ = rhs.arrowsize_;
	return *this;
}
Line::~Line()
{

}

void Line::setdata(const Point& st,const Point& ed)
{
  box_change(true);
	st_ = st;
	ed_ = ed;
//  int sum=0;
//  for(int i=0;i<1000000;++i){
//    sum+=i;
//  }
}

void Line::setdata(const Point& st,const Normal& nor)
{
  box_change(true);
  Point ed = st.polarTo(1, nor);
  st_ = st;
  ed_ = ed;
}


bool Line::visit(Visitor& v)
{
  box_change(true);
	return v.visit_line(*this);
}
void Line::loadme(File& in)
{
	st_.load(in);
	ed_.load(in);
//	in>>arrow_pos_;
//	in>>arrowsize_; 
}
void Line::saveme(const File& out) const
{
	st_.save(out);
	ed_.save(out);
// 	out << arrow_pos_ <<  arrowsize_; 
}
void Line::save_luame(std::ofstream &out,int tab_num)
{
	st_.save_lua(out,"st_",tab_num);
	ed_.save_lua(out,"ed_",tab_num);
}
void Line::open_luame(lua_State *l)  
{
	TRACE_OUT("Line open in open_luame()\n");
	st_.open_lua(l,"st_");
	ed_.open_lua(l,"ed_");

}

void Line::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","LINE");

	get_str_ent();

	rei_add_float(NULL,"st_.x",st_.x);
	rei_add_float(NULL,"st_.y",st_.y);
	rei_add_float(NULL,"st_.z",st_.z);

	rei_add_float(NULL,"ed_.x",ed_.x);
	rei_add_float(NULL,"ed_.y",ed_.y);
	rei_add_float(NULL,"ed_.z",ed_.z);
	rei_get_encode(out);
}

void Line::set_from_strme(char *in)
{
	rei_init(in);

	set_from_str_ent();
	
	st_.x = atof(rei_get("st_.x"));
	st_.y = atof(rei_get("st_.y"));
	st_.z = atof(rei_get("st_.z"));

	ed_.x = atof(rei_get("ed_.x"));
	ed_.y = atof(rei_get("ed_.y"));
	ed_.z = atof(rei_get("ed_.z"));

	rei_quit();



}




// void Line::lua_load(iLua_File &fin)
// {
// 
// }
// 
// void Line::lua_save(oLua_File &fout)const
// {
// 	Entity::lua_save(fout);
// 	fout.save_value("st_", &st_);
// 	fout.save_value("ed_", &ed_);
// }

void Line::edit_propertyme(const Edit_Entity& edit)
{
	edit.edit_line(*this);
}

void Line::drawme(Draw_Entity& out) const
{
	out.draw_line(*this);
}
void Line::xor_drawme(Draw_Entity& out) const
{
	out.xor_draw_line(*this);
}

errorinfo Line::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}

void Line::transformbyme(const Matrix& mat)
{
	st_.transformby(mat);
	ed_.transformby(mat);
}
void Line::drag_startme(const Matrix& mat)
{
	st_.transformby(mat);
}
void Line::drag_endme(const Matrix& mat)
{
	ed_.transformby(mat);
}
Entity* Line::cloneme() const
{
	return new Line(*this);
}

void Line::closeme()
{
	delete this;
}

bool Line::intersectme(const Rect& rect) const
{
	Entity_Calculate calc;
	return calc.linesegment_insect_rect(*this,rect);
}
bool Line::envelopme(const Rect& rect) const
{
	return st_.envelop(rect) && ed_.envelop(rect);
}

Rect Line::calc_box2d() const
{
  Rect box2d_;
  box2d_.xmax(max(st_.x,ed_.x));
  box2d_.xmin(min(st_.x,ed_.x));
  box2d_.ymax(max(st_.y,ed_.y));
  box2d_.ymin(min(st_.y,ed_.y));
  return box2d_;
}

bool Line::snap_endpointme(Point& pt,const Rect& rect) const
{
  if(st_.envelop(rect)){
    pt = st_;
    return true;
  }
  if(ed_.envelop(rect)){
    pt = ed_;
    return true;
  }
  return false;
}
bool Line::snap_middle_pointme(Point& pt,const Rect& rect) const
{
  Point middle = st_ + ed_;
  middle /= 2.0;
  if(middle.envelop(rect)){
    pt = middle;
    return true;
  }
  return false;
}
Float Line::distanceto(const Point& pt) const
{
  Entity_Calculate calc;
  Point p;
  calc.line_perpendicular(p,*this,pt);
  return p.distanceto(pt);
}
Float Line::distanceto2d(const Point& pt) const
{
  Point pt2d, st2d, ed2d;
  pt2d.set2d(pt );
  st2d.set2d(st_);
  ed2d.set2d(ed_);
  Line ln2d(st2d,ed2d);
  return ln2d.distanceto(pt2d);
}
bool Line::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
  Entity_Calculate calc;
  Point o;
  o.x = (rect.xmax()+rect.xmin())/2.0;
  o.y = (rect.ymax()+rect.ymin())/2.0;
  if(!calc.line_perpendicular(pt,*this,o))
    return false;
  if(!pt.envelop(rect))
    return false;
  return true;
}
bool Line::snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const
{
  Entity_Calculate calc;
  Point out;
  calc.line_perpendicular(out,*this,o);
  if(out.envelop(rect)){
    pt = out;
    return true;
  }
  return false;
}
//bool Line::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////	Entity_Snap_Implement<Line> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Line::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}
int Line::get_start_arrow_line_show(std::vector<Line*>& lines) const
{
	Normal nor;
	nor.set_data(ed_,st_);
	create_arrow(nor,st_,lines);
	return lines.size();
}
int Line::get_end_arrow_line_show(std::vector<Line*>& lines) const
{
  Normal nor;
  nor.set_data(st_,ed_);
  create_arrow(nor,ed_,lines);
  return lines.size();
}
void Line::create_arrow(Normal nor,Point arrow_pos,std::vector<Line*>& lines)const
{
  
  Line *arrow_l_1 = Line::create_me();
  Line *arrow_l_2 = Line::create_me();
  Normal n;
  n.set_x_axis_angle(nor.angle_x_axis_two_pi()+3.5*pi/4);
  Point pt1 = arrow_pos.polarTo(arrowsize_,n);
  arrow_l_1->setdata(arrow_pos,pt1);
  n.set_x_axis_angle(nor.angle_x_axis_two_pi()-3.5*pi/4);
  Point pt2 = arrow_pos.polarTo(arrowsize_,n);
  arrow_l_2->setdata(arrow_pos,pt2);
  
  //设置属性
  arrow_l_1->line_style(linestyle_);
  arrow_l_2->line_style(linestyle_);
  arrow_l_1->color(color_.rgb());
  arrow_l_2->color(color_.rgb());
  
  lines.push_back(arrow_l_1);
  lines.push_back(arrow_l_2);
}
void Line::arrow_pos(int pos)
{
  box_change(true);
	arrow_pos_ = pos;
}

bool Line::is_in_line(Point pt)const
{
  if(is_in_rayline(pt)){
    return true;
  }
  Line reverse_ln;
  reverse_ln.setdata(ed_,st_);
  if(reverse_ln.is_in_rayline(pt)){
    return true;
  }
  return false;
}
 
bool Line::is_in_rayline(Point pt)const
{
  if(pt == st_){
    return true;
  }
  Normal nor_ln, nor_pt;
  nor_ln.set_data(st_,ed_);
  nor_pt.set_data(st_,pt );
  nor_ln.set_unit();
  nor_pt.set_unit();
  if(nor_pt == nor_ln){
    return true;
  }
  return false;
}
 
bool Line::is_in_segline(Point pt)const
{
  if(!is_in_rayline(pt)){
    return false;
  }
  Line reverse_ln;
  reverse_ln.setdata(ed_,st_);
  if(!reverse_ln.is_in_rayline(pt)){
    return false;
  }
  return true;
}

Point Line::perpendicular(const Point& pt)
{
  Point result_pt;
  Entity_Calculate cal;
  cal.line_perpendicular(result_pt, *this, pt);
  return result_pt;
}

void Line::setctrl(const std::vector<Point>& pts)
{
  box_change(true);
  assert(pts.size()>=2);
  start(pts[0]);
  end  (pts[1]);
}
void Line::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(start());
  pts.push_back(end  ());
}
int Line::pt_count()const
{
  return 2;
}
void Line::setdrag(const std::vector<Point>& pts, int index)
{
  if(pts.size()<3){
    return;
  }
  box_change(true);
  Point nor = pts[0]-middle();
  switch(index)
  {
  case 0:
    st_ += nor;
    ed_ += nor;
    break;
  case 1:
    start(pts[1]);
    break;
  case 2:
    end  (pts[2]);
    break;
  }
}
void Line::getdrag(std::vector<Point>& pts)const
{
  pts.push_back(middle());
  pts.push_back(start ());
  pts.push_back(end   ());
}

void Line::setstrech(const std::vector<Point>& pts)
{
  box_change(true);
  setctrl(pts);
}
void Line::getstrech(std::vector<Point>& pts) const
{
  getctrl(pts);
}


Point Line::middle()const
{
  Point pt;
  pt.x = (st_.x+ed_.x)/2;
  pt.y = (st_.y+ed_.y)/2;
  pt.z = (st_.z+ed_.z)/2;
  return pt;
}


//1)if nor.z    ==0, return length()
//2)if nor.len2d==0, return ed.z - st.z
//3)ln.len2d / nor.len2d == ln.z / nor.z
Float Line::length_p(const Normal& nor)const
{
  Normal nor2d = nor;
  nor2d.z(0);
  Float ln_len2d = length_to_nor(nor2d);

  Point nor2d_st;
  Point nor2d_ed;
  nor2d_ed.setdata(nor2d);
  Float nor_len2d = nor2d_st.distanceto2d(nor2d_ed);
  Float nor_z     = nor.z();
  Float ln_lenz   = ln_len2d*nor_z/nor_len2d;

  Line temp = *this;
  Point st = temp.start();
  Point ed = temp.end();
  st.z = 0;
  ed.z = ln_lenz;
  temp.start(st);
  temp.end(ed);
  
  Float len = temp.length();
  return len;
}
//线投影在normal上的长度，有符号
Float	Line::length_by_way(const Normal& nor) const
{
  Line  nor_ln = nor.line();
  Point nor_st = nor_ln.perpendicular(start());
  Point nor_ed = nor_ln.perpendicular(end  ());
  Float len = nor_st.distanceto(nor_ed);

  Normal nor1(nor);
  Normal nor2(nor_st,nor_ed);
  nor1.set_unit();
  nor2.set_unit();
  return nor1 == nor2 ? len : -len ;
}
//线投影在normal上的长度，无符号
Float Line::length_to_nor(const Normal& nor)const
{
  return fabs(length_by_way(nor));
}

Point Line::polarTo_p(Float len, bool orderway)const
{
  if(orderway){
    Normal nor(*this);
    return st_.polarTo(len,nor);
  }
  else{
    Normal nor(ed_,st_);
    return ed_.polarTo(len,nor);
  }
}

void Line::intersectme(const Entity& e , std::vector<Point>& pts)const
{
  if(&e == this){
    return;
  }
  e.intersect(*this, pts);
}
void Line::intersectme(const Line & ln, std::vector<Point>& pts)const
{
  if(&ln == this){
    return;
  }
  Entity_Calculate calc;
  Point pt;
  bool myre = calc.line_insect_line(pt, *this, ln);
  if(myre){
    pts.push_back(pt);
  }
  //return myre;
}
void Line::intersectme(const RArc & ac, std::vector<Point>& pts)const
{
//  Entity_Calculate calc;
  Point pt1, pt2;
//   bool myre = calc.line_insect_arc(pt1, pt2, *this, ac);
//   if(myre){
//     pts.push_back(pt1);
//     pts.push_back(pt2);
//   }
  //return myre;
  int xpt_count = intersect2d_a_l(ac, *this, pt1, pt2);
  dlhml::push_xpt(xpt_count, pt1, pt2, pts);
}
void Line::intersectme(const Circle & cr, std::vector<Point>& pts)const
{
//  Entity_Calculate calc;
  Point pt1, pt2;
//bool myre = calc.line_insect_circle(pt1, pt2, *this, cr);
//   if(myre){
//     pts.push_back(pt1);
//     pts.push_back(pt2);
//   }
  //return myre;
  int xpt_count = intersect2d_c_l(cr, *this, pt1, pt2);
  push_xpt(xpt_count, pt1, pt2, pts);
}
//bool Line::intersectme(const Cloud_Line& cl, std::vector<Point>& pts)const
//{
//  Entity_Calculate calc;
//  Point pt;
//  bool myre=false;
//  std::vector<Entity*> lns;
//  cl.get_lines(lns);
//  int i=0;
//  for(i=0; i<lns.size(); i++){
//    if(lns[i]->intersect(*this, pts)){
//      myre=true;
//    }
//  }
//  destory(lns);
//  return myre;
//}

void Line::extend(const Line& ln)
{
  box_change(true);
  Entity_Calculate calc;
  Point pt;
  if(!calc.line_insect_line(pt, *this, ln)){
    return ;
  }
  if(this->is_in_segline(pt)){
    return ;
  }
  Float dis1 = st_.distanceto2d(pt);
  Float dis2 = ed_.distanceto2d(pt);
  if(LessThen(dis1,dis2)){
    st_ = pt;
  }
  else{
    ed_ = pt;
  }

  return ;
}
void Line::trim(const Line& ln)
{
  box_change(true);
  Entity_Calculate calc;
  Point pt;
  if(!calc.line_insect_line_segment(pt, *this, ln)){
    return ;
  }
//  if(!this->is_in_segline(pt)){
//    return ;
//  }
  Float ln_degree = 0;
  Float st_degree = 0;
  Float ed_degree = 0;
  normal2d_2_degree(Normal(ln), ln_degree);
  normal2d_2_degree(Normal(ln.end(),st_), st_degree);
  normal2d_2_degree(Normal(ln.end(),ed_), ed_degree);
  if(LessThen(st_degree-ln_degree, 180) && MoreThen(st_degree-ln_degree, 0) || 
     LessThen(st_degree-ln_degree, -180)){
    st_ = pt;
  }
  else{
    ed_ = pt;
  }

  return ;
}


static int get_break_pt(const Line& the, const Line& src, Point& pt1, Point& pt2)
{
	////命令线长度是0
	if(dlhml::EquFloat(the.length() ,0)){
		return 0;
	}
	////命令线在源线上
	if(src.is_in_segline(the.start()) && src.is_in_segline(the.end())){
		Float dis1 = src.start().distanceto2d(the.start());
		Float dis2 = src.start().distanceto2d(the.end());
		if(dlhml::LessThen(dis1,dis2)){
			pt1 = the.start();
			pt2 = the.end();
		}else{
			pt1 = the.end();
			pt2 = the.start();
		}
		return 2;
	}
	////命令线起点在源线上
	if(src.is_in_segline(the.start()) && !src.is_in_segline(the.end())){
		pt1 = the.start();
		return 1;
	}
	////命令线终点在源线上
	if(src.is_in_segline(the.end()) && !src.is_in_segline(the.start())){
		pt1 = the.end();
		return 1;
	}
	////命令线终点与源线相交
	Point ins_pt;
	Entity_Calculate calc;
  if(calc.line_insect_line_segment(ins_pt, src, the)){
		pt1 = ins_pt;
		return 1;
	}
	////命令线终点与源线相离
	return 0;
}

void Line::split(const Line& ln, std::vector<Entity*>& os)const
{
	Point pt1, pt2;
  Line * ln1=NULL;
  Line * ln2=NULL;
	int pos = get_break_pt(ln, *this, pt1, pt2);
	if(pos == 2){
		ln1 = static_cast<Line*>(this->clone());
		ln2 = static_cast<Line*>(this->clone());
		ln1->end(pt1);
		ln2->start(pt2);
		os.push_back(ln1);
		os.push_back(ln2);
		return;
	}
	if(pos == 1){
		ln1 = static_cast<Line*>(this->clone());
		ln2 = static_cast<Line*>(this->clone());
		ln1->end(pt1);
		ln2->start(pt1);
		os.push_back(ln1);
		os.push_back(ln2);
		return;
	}
	if(pos == 0){
		ln1 = static_cast<Line*>(this->clone());
		os.push_back(ln1);
		return;
	}
}

////								 数量		断开距离
void Line::split(int num, Float dis, std::vector<Entity*>& os)const
{
	//如果只要1段或者断开距离*(数量-1) >= 线的长度， 无法打断
	if(num<=1 || dlhml::LessEqu(this->length(), dis*(num-1))){
		Line * ln = static_cast<Line*>(this->clone());
		os.push_back(ln);
		return;
	}
	Float sum_dis = dis * (num-1);
	Float sum_len = this->length() - sum_dis;
	Float the_len = sum_len / num;
	int i=0;
	for(; i<num; ++i){
		Normal nor(st_, ed_);
		Line * ln = static_cast<Line*>(this->clone());
		Float st_len = (the_len+dis) * i;
		Float ed_len = st_len + the_len;
		Point st = st_.polarTo(st_len, nor);
		Point ed = st_.polarTo(ed_len, nor);
		ln->setdata(st, ed);
		os.push_back(ln);
	}
}
// void Line::split(const Line& ln, std::vector<Entity*>& os)const
// {
//   Point ins_pt;
//   Line * ln1=NULL;
//   Line * ln2=NULL;
//   Entity_Calculate calc;
//   if(!calc.line_insect_line_segment(ins_pt, ln, *this)){
// 		ln1 = (Line*)(this->clone());
// 		os.push_back(ln1);
//   }
// 	else{
// 		ln1 = (Line*)(this->clone());
// 		ln2 = (Line*)(this->clone());
// 		ln1->start(ins_pt);
// 		ln2->end  (ins_pt);
// 		os.push_back(ln1);
// 		os.push_back(ln2);
//   }
// }

void Line::set2d()
{
  box_change(true);
  st_.z=0;
  ed_.z=0;
}

Line Line::reverse()const
{
  Point s=st_;
  Point e=ed_;
  std::swap(s,e);
  return Line(s,e);
}



}//namespace

