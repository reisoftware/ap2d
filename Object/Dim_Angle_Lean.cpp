
#include "stdafx.h"
#include "Dim_Angle_Lean.h"

#include "Database.h"
#include "DrawEntity.h"
#include "Edit_Entity.h"
#include "Visitor.h"
#include "Entity_Snap.h"

#include "Entity_Calculate.h"
#include "Global.h"

#include "Normal.h"
#include <cassert>
#include "getrace.h"


namespace dlhml{

MY_IMPLEMENT_DYNCREATE(Dim_Angle_Lean,Dimension)

Dim_Angle_Lean::Dim_Angle_Lean()
:Dimension()
MCT_INIT2("Dim_Angle_Lean")
{
}

Dim_Angle_Lean::Dim_Angle_Lean(const Line& ln)
:Dimension()
MCT_INIT2("Dim_Angle_Lean")
{
  setdata(ln);
}

Dim_Angle_Lean::Dim_Angle_Lean(const Point& st,const Point& ed)
:Dimension()
MCT_INIT2("Dim_Angle_Lean")
{
  setdata(st,ed);
}
Dim_Angle_Lean::Dim_Angle_Lean(const Dim_Angle_Lean& rhs)
:Dimension(rhs)
MCT_INIT2("Dim_Angle_Lean")
{
  ln_=rhs.ln_;
}
Dim_Angle_Lean& Dim_Angle_Lean::operator=(const Dim_Angle_Lean& rhs)
{
  Entity::operator=(rhs);
  if(this==&rhs){
    return *this;
  }
  ln_=rhs.ln_;
  return *this;
}

Dim_Angle_Lean::~Dim_Angle_Lean()
{

}

void Dim_Angle_Lean::getdata(Line & ln)const
{
  ln=ln_;
}
void Dim_Angle_Lean::setdata(const Line& ln)
{
  show_change(true);
  ln_=ln;
}

void Dim_Angle_Lean::setdata(const Point& st,const Point& ed)
{
  show_change(true);
  ln_.setdata(st,ed);
}

bool Dim_Angle_Lean::visit(Visitor& v)
{
  show_change(true);
	return v.visit_Dim_Angle_Lean(*this);
}

void Dim_Angle_Lean::loadme(File& in)
{
  ln_.load(in);
}
void Dim_Angle_Lean::saveme(const File& out) const
{
  ln_.save(out);
}
void Dim_Angle_Lean::get_strme(char *out)
{
	ln_.get_str(out);

}

void Dim_Angle_Lean::set_from_strme(char *in)
{
	ln_.set_from_str(in);

}

void Dim_Angle_Lean::edit_propertyme(const Edit_Entity& edit)
{
	edit.edit_Dim_Angle_Lean(*this);
}


//void Dim_Angle_Lean::drawme(Draw_Entity& out) const
//{
//  //NOOK
////	out.draw_line(*this);
//}
//void Dim_Angle_Lean::xor_drawme(Draw_Entity& out) const
//{
//  //NOOK
////	out.xor_draw_line(*this);
//}


errorinfo Dim_Angle_Lean::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Dim_Angle_Lean::transformbyme(const Matrix& mat)
{
//	REITRACE;
  show_change(true);
  ln_.transformby(mat);
}
void Dim_Angle_Lean::drag_startme(const Matrix& mat)
{
  show_change(true);
  Point pt;
  pt = ln_.start();
	pt.transformby(mat);
  ln_.start(pt);
}
void Dim_Angle_Lean::drag_endme(const Matrix& mat)
{
  show_change(true);
  Point pt;
  pt = ln_.end();
	pt.transformby(mat);
  ln_.end();
}
Entity* Dim_Angle_Lean::cloneme() const
{
	return new Dim_Angle_Lean(*this);
}

void Dim_Angle_Lean::closeme()
{
	delete this;
}

//void intersectme(const Entity& e , std::vector<Point>& pts)const
//{
//}

bool Dim_Angle_Lean::intersectme(const Rect& rect) const
{
  return ln_.intersect(rect);
// 	Entity_Calculate calc;
// 	return calc.linesegment_insect_rect(ln_,rect);
}
bool Dim_Angle_Lean::envelopme(const Rect& rect) const
{
	return ln_.envelop(rect);
}

Rect Dim_Angle_Lean::calc_box2d() const
{
  return ln_.box2d();
}

bool Dim_Angle_Lean::snap_endpointme(Point& pt,const Rect& rect) const
{
  return ln_.snap_endpoint(pt,rect);
//   Point st = ln_.start();
//   Point ed = ln_.end  ();
//   if(st.envelop(rect)){
//     pt = st;
//     return true;
//   }
//   if(ed.envelop(rect)){
//     pt = ed;
//     return true;
//   }
//   return false;
}
bool Dim_Angle_Lean::snap_middle_pointme(Point& pt,const Rect& rect) const
{
  return ln_.snap_middle_point(pt,rect);
//   Point middle = ln_.middle();
//   if(middle.envelop(rect)){
//     pt = middle;
//     return true;
//   }
//   return false;
}
bool Dim_Angle_Lean::snap_nearest_pointme(Point& pt,const Rect& rect) const
{
  return ln_.snap_nearest_point(pt,rect);
//   Entity_Calculate calc;
//   Point o;
//   o.x = (rect.xmax()+rect.xmin())/2.0;
//   o.y = (rect.ymax()+rect.ymin())/2.0;
//   if(!calc.line_perpendicular(pt,ln_,o))
//     return false;
//   if(!pt.envelop(rect))
//     return false;
//   return true;
}
bool Dim_Angle_Lean::snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const
{
  return ln_.snap_perpendicular_point(pt,rect,o);
//   Entity_Calculate calc;
//   Point out;
//   calc.line_perpendicular(out,ln_,o);
//   if(out.envelop(rect)){
//     pt = out;
//     return true;
//   }
//   return false;
}
//bool Dim_Angle_Lean::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//////Entity 统一实现
//  return false;
////	Entity_Snap_Implement<Line> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Dim_Angle_Lean::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,ln_);
}



void Dim_Angle_Lean::setctrl(const std::vector<Point>& pts)
{
  show_change(true);
  assert(pts.size()>=2);
  start(pts[0]);
  end  (pts[1]);
}
void Dim_Angle_Lean::getctrl(std::vector<Point>& pts) const
{
  pts.push_back(start());
  pts.push_back(end  ());
}
int Dim_Angle_Lean::pt_count()const
{
  return 2;
}
void Dim_Angle_Lean::setdrag(const std::vector<Point>& pts, int index)
{
  show_change(true);
  ln_.setdrag(pts,index);
//  if(pts.size()<3){
//    return;
//  }
//  switch(index)
//  {
//  case 0:
//    st_ += pts[0]-middle();
//    ed_ += pts[0]-middle();
//    break;
//  case 1:
//    start(pts[1]);
//    break;
//  case 2:
//    end  (pts[2]);
//    break;
//  }
}
void Dim_Angle_Lean::getdrag(std::vector<Point>& pts)const
{
  ln_.getdrag(pts);
//  pts.push_back(middle());
//  pts.push_back(start ());
//  pts.push_back(end   ());
}
void Dim_Angle_Lean::setstrech(const std::vector<Point>& pts)
{
  show_change(true);
  setctrl(pts);
}
void Dim_Angle_Lean::getstrech(std::vector<Point>& pts) const
{
  getctrl(pts);
}


//1)if nor.z    ==0, return length()
//2)if nor.len2d==0, return ed.z - st.z
//3)ln.len2d / nor.len2d == ln.z / nor.z
Float Dim_Angle_Lean::length_p(const Normal& nor)const
{
  return ln_.length(nor);
}

Point Dim_Angle_Lean::polarTo_p(Float len, bool orderway)const
{
  return ln_.polarTo(len,orderway);
}

void Dim_Angle_Lean::extend(const Line& ln)
{
  show_change(true);
  Entity_Calculate calc;
  Point pt;
  if(!calc.line_insect_line(pt, ln_, ln)){
    return ;
  }
  if(ln_.is_in_segline(pt)){
    return ;
  }
  Point st = ln_.start();
  Point ed = ln_.end  ();
  Float dis1 = st.distanceto2d(pt);
  Float dis2 = ed.distanceto2d(pt);
  if(LessThen(dis1,dis2)){
    st = pt;
  }
  else{
    ed = pt;
  }
  ln_.setdata(st,ed);

  return ;
}
void Dim_Angle_Lean::trim(const Line& ln)
{
  show_change(true);
  ln_.trim(ln);
}
void Dim_Angle_Lean::split(const Line& ln, std::vector<Entity*>& os)const
{
  Point ins_pt;
  Dim_Angle_Lean * ln1=NULL;
  Dim_Angle_Lean * ln2=NULL;
  Entity_Calculate calc;
  if(!calc.line_insect_line_segment(ins_pt, ln, ln_)){
    ln1 = (Dim_Angle_Lean*)(this->clone());
    os.push_back(ln1);
  }else{
    ln1 = (Dim_Angle_Lean*)(this->clone());
    ln2 = (Dim_Angle_Lean*)(this->clone());
    ln1->start(ins_pt);
    ln2->end  (ins_pt);
    os.push_back(ln1);
    os.push_back(ln2);
  }
  //ln_.split(ln,os);
}

void Dim_Angle_Lean::get_line(std::vector<Entity*>& es)const
{
  Line * ln = Line::create_me();
  *ln = ln_;
  //int aaa = color_index();
  //int aaaa= dim_style_val_.line_color();
  //dim_style_val_.line_color(color_index());
  ln->color_index(dim_style_val_.line_color());
  ln->line_style(line_style());
  es.push_back(ln);
}
void Dim_Angle_Lean::get_show(std::vector<Entity*>& es)const
{
  get_line(es);
  dim_style_val_.get_arrow(ln_,es);
}

void Dim_Angle_Lean::save_luame(std::ofstream &out,int tab_num)
{
	ln_.save_lua(out,"ln_",tab_num);
}
void Dim_Angle_Lean::open_luame(lua_State *l) 
{
	TRACE_OUT("Dim_Angle_Lean open in open_luame()\n");
	ln_.open_lua(l,"ln_");
	txt_change(true);
}


}//namespace

