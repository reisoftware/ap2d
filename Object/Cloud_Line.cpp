// Cloud_Line.cpp: implementation of the Cloud_Line class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cloud_Line.h"
#include "Global.h"
#include "File.h"
#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Database.h"
#include "Entity_Snap_Implement.h"
#include "Line.h"
#include "RArc.h"
#include "Entity_Calculate.h"
#include "calculate.h"
#include "Visitor.h"
#include "Line.h"
#include "Entity_Calculate.h"
#include "Normal.h"
#include "Matrix_d.h"
#include "Lua_Tab.h"

#include "encode.h"

#include <algorithm>
#include <cassert>
#include "getrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Cloud_Line,Entity)
Cloud_Line::Cloud_Line()
//:mode_(ARC_CLOSED)
:open_(false)
,line_(false)
,rect_(false)
,salience_(5)
MCT_INIT2("Cloud_Line")
{

}
Cloud_Line::Cloud_Line(const Cloud_Line& rhs)
:Entity(rhs)
,salience_(5)
MCT_INIT2("Cloud_Line")
{
	pts_ = rhs.pts_;
//	mode_= rhs.mode_;
	open_= rhs.open_;
	line_= rhs.line_;
  rect_= rhs.rect_;
}
Cloud_Line& Cloud_Line::operator=(const Cloud_Line& rhs)
{
	Entity::operator =(rhs);
	if(this == &rhs)
		return *this;
	pts_ = rhs.pts_;
//	mode_= rhs.mode_;
	open_= rhs.open_;
	line_= rhs.line_;
  rect_= rhs.rect_;
	return *this;
}
Cloud_Line::~Cloud_Line()
{

}
bool Cloud_Line::visit(Visitor& v)
{
  box_change(true);
	return v.Visit_Cloud_Line(*this);
}
void Cloud_Line::loadme(File& in)
{
	int count =0;
	in >> count ;
	for(int i=0;i<count;i++){
		Point pt;
		pt.load(in);
		pts_.push_back(pt);
	}
	//in >> mode_;
  in >> open_;
  in >> line_;
  in >> rect_;
}
void Cloud_Line::saveme(const File& out) const
{
	int count =pts_.size();
	out << count ;
	for(std::vector<Point>::const_iterator it=pts_.begin();it!=pts_.end();++it)
		it->save(out);
//	out << mode_;
  out << open_;
  out << line_;
  out << rect_;
}
void Cloud_Line::save_luame(std::ofstream &out,int tab_num)
{
	lua::bool_save(out,"open_",open_,tab_num);
	lua::bool_save(out,"line_",line_,tab_num);
	lua::bool_save(out,"rect_",rect_,tab_num);
	std::vector<Point>::iterator iter = pts_.begin();
	lua::begin_table(out,"pts_",tab_num);
	for(;iter!=pts_.end();++iter){
		iter->save_lua(out,NULL,tab_num+1);
	}
	lua::val_save(out,"}",tab_num);


}
void Cloud_Line::open_luame(lua_State *l) 
{
	TRACE_OUT("Cloud_Line::open_luame()\n");
  get_value(number,l,open_,"open_");
  get_value(number,l,line_,"line_");
	get_value(number,l,rect_,"rect_");

	Lua_Tab luatab(l,"pts_");
	int index = lua_gettop(l);
	lua_pushnil(l);
	std::string kind;
	Point pt;
	while(lua_next(l,index) != 0){
		get_value(number,l,pt.x,"x");
		get_value(number,l,pt.y,"y");
		get_value(number,l,pt.z,"z");
		pts_.push_back(pt);
		lua_pop(l,1);
	}
	color_= RGB(255,0,0);

}

void Cloud_Line::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","CLOUD_LINE");
	get_str_ent();
	//////////////////////////
	rei_add_int(NULL,"open_",open_);
	rei_add_int(NULL,"line_",line_);
	rei_add_int(NULL,"rect_",rect_);

	int count = pts_.size();
	rei_add_int(NULL,"pts_num",count);
	char field_name[MAX_REDIS_STR];
	char field_name1[MAX_REDIS_STR];
	char field_name2[MAX_REDIS_STR];
	for (int i = 0; i < count; i++){
			sprintf(field_name,"pts%d",i);
			strcpy(field_name1,field_name);
			strcpy(field_name2,field_name);
			strcat(field_name,".x");
			rei_add_float(NULL,field_name,pts_[i].x);
			strcat(field_name1,".y");
			rei_add_float(NULL,field_name1,pts_[i].y);
			strcat(field_name2,".z");
			rei_add_float(NULL,field_name2,pts_[i].z);
	}
	rei_get_encode(out);
}

void Cloud_Line::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	////////////////////////////////////////////////////////////
	open_ = atoi(rei_get("open_"));
	line_ = atoi(rei_get("line_"));
	rect_ = atoi(rei_get("rect_"));
	
	int count = atoi(rei_get("pts_num"));
	pts_.clear();
	char field_name[MAX_REDIS_STR];
	char field_name1[MAX_REDIS_STR];
	char field_name2[MAX_REDIS_STR];
	for( int i = 0; i < count; i++){
		sprintf(field_name,"pts%d",i);
		strcpy(field_name1,field_name);
		strcpy(field_name2,field_name);
		strcat(field_name,".x");
		strcat(field_name1,".y");
		strcat(field_name2,".z");
		Point pt;
		pt.x = atof(rei_get(field_name));
		pt.y = atof(rei_get(field_name1));
		pt.z = atof(rei_get(field_name2));
		pts_.push_back(pt);
	}

	rei_quit();
}
void Cloud_Line::edit_propertyme(const Edit_Entity& edit)
{
	edit.edit_cloud_line(*this);
}

void Cloud_Line::drawme(Draw_Entity& out) const
{
	out.draw_cloud_line(*this);
}
void Cloud_Line::xor_drawme(Draw_Entity& out) const
{
	out.xor_draw_cloud_line(*this);
}

errorinfo Cloud_Line::postme2db(Database& db,Entity_ID& id)
{
	return db.entity_push_back(this,id);
}

void Cloud_Line::transformbyme(const Matrix& mat)
{
  Normal nor1, nor2;
  Normal oldnor, newnor;
  if(pts_.size() >= 3){
    nor1.set_data(getat(0), getat(1));
    nor2.set_data(getat(0), getat(2));
    nor1.set_unit();
    nor2.set_unit();
    oldnor = nor1 * nor2;
  }

	for(std::vector<Point>::iterator it=pts_.begin();it!=pts_.end();++it)
		it->transformby(mat);

  if(pts_.size() >= 3){
    nor1.set_data(getat(0), getat(1));
    nor2.set_data(getat(0), getat(2));
    nor1.set_unit();
    nor2.set_unit();
    newnor = nor1 * nor2;

    oldnor.set_unit();
    newnor.set_unit();
    if(oldnor != newnor){
      std::reverse(pts_.begin(),pts_.end());
    }
  }
}

//BET 2009.09.10
//***********************************************************
//********with the salience point.***************************
//void Cloud_Line::transformbyme(const Matrix& mat)
//{
//  Point oldpath, newpath;
//  if(pts_.size() >= 2){
//    oldpath = get_path_pt(getat(0), getat(1));
//  }
//  
//  for(std::vector<Point>::iterator it=pts_.begin();it!=pts_.end();++it)
//    it->transformby(mat);
//  
//  if(pts_.size() >= 2){
//    newpath = get_path_pt(getat(0), getat(1));
//  }
//  if(oldpath != newpath){
//    std::reverse(pts_.begin(),pts_.end());
//  }
//}
//TER

//BET 2009.09.10
//***********************************************************
//********with the matrix's type.****************************
//void Cloud_Line::transformbyme(const Matrix& mat)
//{
//	for(std::vector<Point>::iterator it=pts_.begin();it!=pts_.end();++it)
//		it->transformby(mat);
//
//  if(mat.mat_type()==MIRROR_MAT){
//    std::reverse(pts_.begin(),pts_.end());
//  }
//  rect_ = false;
//  else if(mat.mat_type()==ZRAOTA_MAT){
//    rect_ = false;
//  }
//}
//TER

void Cloud_Line::drag_startme(const Matrix& mat)
{
}
void Cloud_Line::drag_endme(const Matrix& mat)
{
}

Entity* Cloud_Line::cloneme() const
{
	return new Cloud_Line(*this);
}

void Cloud_Line::closeme()
{
	delete this;
}

bool Cloud_Line::intersectme(const Rect& rect) const
{
	bool theresult = false;

	Entity_Calculate calc;
  std::vector<Entity*> es;
  get_lines(es);
  int i=0;
  for(i=0;i<es.size();i++){
    if(es[i]==NULL){
      continue;
    }
    if(es[i]->intersect(rect)){
      theresult = true;
			break;
    }
  }
  destory(es);

	return theresult;
}

// bool Cloud_Line::intersectme(const Rect& rect) const
// {
// 	
// 	
// 	bool theresult = false;
// 	
// 	Entity_Calculate calc;
//   if(line_){
// 		Line line;
// 		for(std::vector<Point>::const_iterator it=pts_.begin();it!=pts_.end();++it){
// 			std::vector<Point>::const_iterator iter = it+1;
// 			if(iter==pts_.end())
// 				iter=pts_.begin();
// 			line.setdata(*it,*iter);
// 			if(calc.linesegment_insect_rect(line,rect)){
// 				theresult = true;
// 				break;
// 			}
// 		}
//   }
//   else{
//     std::vector<Entity*> es;
//     get_lines(es);
//     int i=0;
//     for(i=0;i<es.size();i++){
//       if(es[i]==NULL){
//         continue;
//       }
//       if(es[i]->intersect(rect)){
//         theresult = true;
// 				break;
//       }
//     }
//     destory(es);
//   }
// 	
// 	return theresult;
// }

bool Cloud_Line::envelopme(const Rect& rect) const
{
	bool theresult = true;
	
	Entity_Calculate calc;
  std::vector<Entity*> es;
  get_lines(es);
	if(es.empty()){
		theresult = false;
	}
  int i=0;
  for(i=0;i<es.size();i++){
    if(es[i]==NULL){
      continue;
    }
    if(!es[i]->envelop(rect)){
      theresult = false;
			break;
    }
  }
  destory(es);
	
	return theresult;
}

// bool Cloud_Line::envelopme(const Rect& rect) const
// {
// 	assert(pts_.size() >= 2 && "Cloud_Line::envelopme(rc)");
// 	for(std::vector<Point>::const_iterator it=pts_.begin();it!=pts_.end();++it){
// 		if(!it->envelop(rect))
// 			return false;
// 	}
// 	return true;
// }

Rect Cloud_Line::calc_box2d() const
{
  Rect box2d_;
  box2d_.set_reverse_minmax();
  
  for(std::vector<Point>::const_iterator it=pts_.begin();it!=pts_.end();++it){
    box2d_.xmin(min(box2d_.xmin(),it->x));
    box2d_.ymin(min(box2d_.ymin(),it->y));
    box2d_.xmax(max(box2d_.xmax(),it->x));
    box2d_.ymax(max(box2d_.ymax(),it->y));
  }
  return box2d_;
}

bool Cloud_Line::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
//NOOK SNAP 2009.07.02
////Entity 统一实现
  return false;
//	Entity_Snap_Implement<Cloud_Line> imp(*this);
//	return ent.snap_intersect_point_imp(pt,imp,rect);
}
bool Cloud_Line::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
  bool myre = false;

  std::vector<Entity*> lns;
  get_lines(lns);
  Line * ln = NULL;
  int i=0;
  for(i=0; i<lns.size(); i++){
    ln = (Line*)lns[i];
    if(snap.intersect(pt,rect,*ln)){
      myre = true;
      break;
    }
  }
  destory(lns);
  return myre;
}

bool Cloud_Line::snap_endpointme(Point& pt,const Rect& rect)const
{
  int i=0;
  for(; i<pts_.size(); i++){
    if(pts_[i].envelop(rect)){
      pt = pts_[i];
      return true;
    }
  }
  return false;
}
bool Cloud_Line::snap_middle_pointme(Point& pt,const Rect& rect)const
{
  bool myre = false;

  std::vector<Entity*> lns;
  get_lines(lns);
  Line * ln = NULL;
  Point midpt;
  int i=0;
  for(i=0; i<lns.size(); i++){
    ln = (Line*)lns[i];
    midpt = ln->middle();
    if(midpt.envelop(rect)){
      pt = midpt;
      myre = true;
			break;
    }
  }
  destory(lns);
  return myre;

  
//  Line ln;
//  Point midpt;
//  int i=0; 
//  int pts_size = pts_.size();
//  int for_limit= mode() == LINE_OPEN ? pts_size-1 : pts_size;
//  for(; i<for_limit; i++){
//    ln.setdata(pts_[(i)%pts_size], pts_[(i+1)%pts_size]);
//    midpt = ln.middle();
//    if(midpt.envelop(rect)){
//      pt = midpt;
//      return true;
//    }
//  }
//  return false;
}

bool Cloud_Line::snap_nearest_pointme(Point& pt,const Rect& rect)const
{
  Point o;
  o.x = (rect.xmax()+rect.xmin())/2.0;
  o.y = (rect.ymax()+rect.ymin())/2.0;
  bool myre = false;

  std::vector<Entity*> lns;
  get_lines(lns);
  Line * ln = NULL;
  Point mypt;
  int i=0;
  for(i=0; i<lns.size(); i++){
    ln = (Line*)lns[i];
    mypt = ln->perpendicular(o);
    if(mypt.envelop(rect)){
      pt = mypt;
      myre = true;
			break;
    }
  }
  destory(lns);
  return myre;

  
//  Point o;
//  o.x = (rect.xmax()+rect.xmin())/2.0;
//  o.y = (rect.ymax()+rect.ymin())/2.0;
//  
//  Line ln;
//  Point mypt;
//  int i=0; 
//  int pts_size = pts_.size();
//  int for_limit= mode() == LINE_OPEN ? pts_size-1 : pts_size;
//  for(; i<for_limit; i++){
//    ln.setdata(pts_[(i)%pts_size], pts_[(i+1)%pts_size]);
//    mypt = ln.perpendicular(o);
//    if(mypt.envelop(rect)){
//      pt = mypt;
//      return true;
//    }
//  }
//  return false;
}

void Cloud_Line::setat(int i, const Point& pt)
{
  box_change(true);
  dlhml::setat(pts_, i, pt);
}

const Point& Cloud_Line::getat(int i)const
{
  return dlhml::getat(pts_,i);
}

////获得实际显示时的基本图形实体（线弧圆）
void Cloud_Line::get_show(std::vector<Entity*>& es)const
{
  get_lines(es);
}
void Cloud_Line::get_lines(std::vector<Entity*>& lns)const
{
	if(pts_.empty()){
		return;
	}
	assert(!pts_.empty() && "Cloud_Line::get_lines(es)");

  Entity* ent = NULL;
  int i=0; 
  int pts_size = pts_.size();
  int for_limit= open_ ? pts_size-1 : pts_size;   //  OPEN / CLOSED
  for(; i<for_limit; i++){
    if(line_){                                  //  LINE / ARC
      Line * ln = Line::create_me();
      ent = ln;
      ln->setdata(getat(i), getat(i+1));
    }
    else{
      RArc * arc= RArc::create_me();
      ent = arc;
      Point pt1 = getat(i);
      Point pt3 = getat(i+1);
      //BET
      Point pt2 = get_path_pt(pt1, pt3);
//      Line  lnm(pt1, pt3);
//      Point  ptm = lnm.middle();
//      Normal nor(lnm);
//      nor.rota_z(90);
//      Point pt2 = ptm.polarTo(lnm.length()*salience_/10, nor);
      //TER
      arc->set(pt1, pt2, pt3);
    }
    ent->selected(seled_);
    ent->color(color());
    lns.push_back(ent);
  }
}

Point Cloud_Line::get_path_pt(const Point& st, const Point& ed)const
{
  Line  lnm(st, ed);
  Point  ptm = lnm.middle();
  Normal nor(lnm);
  nor.rota_z(90);
  Point pt2 = ptm.polarTo(lnm.length()*salience_/10, nor);
  return pt2;
}

Float Cloud_Line::length_p()const
{
  std::vector<Entity*> lns;
  get_lines(lns);
  Float len=0;
  int i=0;
  for(; i<lns.size(); i++){
    len += lns[i]->length();
  }
  destory(lns);
  return len;
}
Float Cloud_Line::length_p(const Normal& nor)const
{
  std::vector<Entity*> lns;
  get_lines(lns);
  Float len=0;
  int i=0;
  for(; i<lns.size(); i++){
    len += lns[i]->length(nor);
  }
  destory(lns);
  return len;
}

Float Cloud_Line::area_min_rect_p()const
{
  if(line_ && !open_){
    return dlhml::area_min_rect(pts_);
  }else{
    return -1;
  }
}

Float Cloud_Line::area_min_rect_p(const Normal& nor)const
{ 
  if(line_ && !open_){
    if(EquFloat(nor.z(),0)){
      return dlhml::area_min_rect(pts_);
    }
    Normal nor2d = nor;
    nor2d.z(0);
    Point nor_ed;
    nor_ed.setdata(nor2d);
    Float nor2d_len = nor_ed.distanceto2d(Point());
    nor_ed.setdata(nor);
    Float nor_len = nor_ed.distanceto(Point());
  
    if(EquFloat(nor2d_len,0)){
      return 0;
    }
    Float area2d = dlhml::area_min_rect(pts_);
    return nor_len*area2d/nor2d_len;

    //return dlhml::area(pts_);
  }else{
    return -1;
  }
//    if(mode_ == LINE_CLOSED){
//      if(EquFloat(nor.z(),0)){
//        return dlhml::area(pts_);
//      }
//      Normal nor2d = nor;
//      nor2d.z(0);
//      Point nor_ed;
//      nor_ed.setdata(nor2d);
//      Float nor2d_len = nor_ed.distanceto2d(Point());
//      nor_ed.setdata(nor);
//      Float nor_len = nor_ed.distanceto(Point());
//    
//      if(EquFloat(nor2d_len,0)){
//        return 0;
//      }
//      Float area2d = dlhml::area(pts_);
//      return nor_len*area2d/nor2d_len;
//
//      //return dlhml::area(pts_);
//    }else{
//      return -1;
//    }
}

Point Cloud_Line::focus()const
{
  if(pts_.empty()){
    return Point(0,0,0);
  }
  Rect box = box2d();
  double x = ( box.xmin()+box.xmax() )/2;
  double y = ( box.ymin()+box.ymax() )/2;
  return Point(x,y);
}

Float Cloud_Line::x_length()const
{
  Rect box = box2d();
  return box.xmax() - box.xmin();
}
Float Cloud_Line::y_length()const
{
  Rect box = box2d();
  return box.ymax() - box.ymin();
}
void Cloud_Line::rect_plate(Float xlen, Float ylen)
{
  rect_=true;
  Point f = focus();
  pts_.resize(4);

  xlen/=2;
  ylen/=2;

  pts_[0].x=f.x-xlen;
  pts_[0].y=f.y+ylen;

  pts_[1].x=f.x-xlen;
  pts_[1].y=f.y-ylen;

  pts_[2].x=f.x+xlen;
  pts_[2].y=f.y-ylen;
  
  pts_[3].x=f.x+xlen;
  pts_[3].y=f.y+ylen;
}

void Cloud_Line::rect(bool b)
{
  box_change(true);
  rect_=b;
  if(rect_){
    reset_rect();
  }
}
// void Cloud_Line::setrect()
// {
//   rect_=true;
//   reset_rect();
// }

void Cloud_Line::getdrag(std::vector<Point>& pts)const
{
  pts=pts_;
//   if(rect_ && line_){
//     std::vector<Entity*> es;
//     get_lines(es);
//     if(es.size()==4){
//       int i=0;
//       for(i=0;i<es.size();i++){
//         if(!es[i]){
//           continue;
//         }
//         Line * ln = static_cast<Line*>(es[i]);
//         pts.push_back(ln->middle());
//       }
//     }
//     destory(es);
//   }
}
void Cloud_Line::setdrag(const std::vector<Point>& pts, int index)
{
  box_change(true);
  pts_=pts;
//   if(!rect_){
//     pts_=pts;
//     return;
//   }
//   if(pts.size()!=8 || pts_.size()!=4){
//     return;
//   }
//   if(0<=index&&index<4){
//     reset_rect(index,pts[index]);
//   }
//   else if(index<8){
//     reset_rect_by_side(index,pts[index]);
//   }
}
void Cloud_Line::setstrech(const std::vector<Point>& pts)
{
  box_change(true);
  setdrag(pts);
}
void Cloud_Line::getstrech(std::vector<Point>& pts) const
{
  getdrag(pts);
}

void Cloud_Line::getctrl(std::vector<Point>& pts)const
{
  if(rect_){
    if(pts_.size()!=4){
      return;
    }
    pts.push_back(pts_[0]);
    pts.push_back(pts_[2]);
  }
  else{
    pts=pts_;
  }
}
////if this is rect, pts.size()==2.
void Cloud_Line::setctrl(const std::vector<Point>& pts)
{
  box_change(true);
  if(rect_){
    if(pts.size()!=2){
      return;
    }
    if(pts_.size()!=4){
      pts_.resize(4);
    }
    pts_[0]=pts[0];
    pts_[1].x=pts[0].x;
    pts_[1].y=pts[1].y;
    pts_[2]=pts[1];
    pts_[3].x=pts[1].x;
    pts_[3].y=pts[0].y;
  }
  else{
    pts_=pts;
  }
}

////if this is rect, pts.size()==4.
void Cloud_Line::setdata(const std::vector<Point>& pts)
{
  box_change(true);
  pts_=pts;
//     if(rect_){
//       if(pts_.size()!=4 || pts.size()!=4){
//         return;
//       }
//       int i=0;
//       for(i=0; i<4; i++){
//         if(pts_[i]!=pts[i]){
//           break;
//         }
//       }
//       reset_rect(i,pts[i]);
//     }else{
//       pts_=pts;
//     }
}
void Cloud_Line::reset_rect_by_side(int index, const Point& pt)
{
  box_change(true);
  switch(index)
  {
  case 4:
    pts_[0].x=pt.x;
    pts_[1].x=pt.x;
    break;
  case 5:
    pts_[1].y=pt.y;
    pts_[2].y=pt.y;
    break;
  case 6:
    pts_[2].x=pt.x;
    pts_[3].x=pt.x;
    break;
  case 7:
    pts_[3].y=pt.y;
    pts_[0].y=pt.y;
    break;
  }
}
void Cloud_Line::reset_rect(int index, const Point& pt)
{
  box_change(true);
  switch(index)
  {
  case 0:
    pts_[0]=pt;
    pts_[3].y=pt.y;
    pts_[1].x=pt.x;
    break;
  case 1:
    pts_[1]=pt;
    pts_[2].y=pt.y;
    pts_[0].x=pt.x;
    break;
  case 2:
    pts_[2]=pt;
    pts_[1].y=pt.y;
    pts_[3].x=pt.x;
    break;
  case 3:
    pts_[3]=pt;
    pts_[0].y=pt.y;
    pts_[2].x=pt.x;
    break;
  }
}
void Cloud_Line::reset_rect()
{
  box_change(true);
  if(rect_){
    Rect box = box2d();
    pts_.resize(4);

    pts_[0].x=box.xmin();
    pts_[0].y=box.ymax();

    pts_[1].x=box.xmin();
    pts_[1].y=box.ymin();

    pts_[2].x=box.xmax();
    pts_[2].y=box.ymin();
  
    pts_[3].x=box.xmax();
    pts_[3].y=box.ymax();
  }
}
int Cloud_Line::pt_count()const
{
  if(rect_){
    return 2;
  }
  else{
    return MAX_PT_COUNT;
  }
}


void Cloud_Line::intersectme(const Entity& e , std::vector<Point>& pts)const
{
  std::vector<Entity*> lns;
  get_show(lns);
  int i=0;  
  for(i=0; i<lns.size(); i++){
    lns[i]->intersect(e, pts);
  }
	dlhml::destory(lns);
}
void Cloud_Line::intersectme(const Line & ln, std::vector<Point>& pts)const
{
  std::vector<Entity*> lns;
  get_show(lns);
  int i=0;  
  for(i=0; i<lns.size(); i++){
    lns[i]->intersect(ln, pts);
  }
  dlhml::destory(lns);
}
void Cloud_Line::intersectme(const RArc & ac, std::vector<Point>& pts)const
{
  std::vector<Entity*> lns;
  get_show(lns);
  int i=0;  
  for(i=0; i<lns.size(); i++){
    lns[i]->intersect(ac, pts);
  }
  dlhml::destory(lns);
}
void Cloud_Line::intersectme(const Circle & cr, std::vector<Point>& pts)const
{
  std::vector<Entity*> lns;
  get_show(lns);
  int i=0;  
  for(i=0; i<lns.size(); i++){
    lns[i]->intersect(cr, pts);
  }
  dlhml::destory(lns);
}
//bool Cloud_Line::intersectme(const Cloud_Line& cl, std::vector<Point>& pts)const
//{
//  bool myre=false;
//  std::vector<Entity*> lns;
//  get_lines(lns);
//  int i=0;
//  for(i=0; i<lns.size(); i++){
//    if(lns[i]->intersect(cl, pts)){
//      myre=true;
//    }
//  }
//  destory(lns);
//  return myre;
//}



}//namespace
