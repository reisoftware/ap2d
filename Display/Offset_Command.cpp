
#include "StdAfx.h"
#include "Offset_Command.h"
#include "../object/Global.h"

#include "Entity_Calculate.h"

#include "Matrix_d.h"
#include "Normal.h"

#include "Entity.h"
#include "Line_Arrow.h"
#include "Cloud_Line.h"
#include "Arc_Arrow.h"
#include "Circle.h"

namespace dlhml
{

bool Offset_Command::cad_cammand(const Line& ln)
{
  bool return_val=true;

  if(!xor_ || xor_->empty() || !new_){
    return false;
  }
  std::vector<Entity*>& x = *xor_;
  std::vector<Entity*>& n = *new_;
  copy(x, n);

  Entity * front_e = new_->front();
  if(!front_e){
    return false;
  }
  if(front_e->isa(MY_RUNTIME_CLASS(Line_Arrow))){
    Matrix mat;
    mat.set_move(ln);
    matcal<Entity>(n, mat);
  }
  else if(front_e->isa(MY_RUNTIME_CLASS(Cloud_Line))){
    ////移动线
    Cloud_Line* cl = static_cast<Cloud_Line*>(front_e);
    std::vector<Entity*> es;
    cl->get_lines(es);
    Line* cl_ln=NULL;
    Point drag_pt;
    Point way_pt=ln.end();
    Float dis=ln.length();
    Point mat_pt;
    int i=0;
    std::vector<Point> old_pts;
    cl->getdata(old_pts);
    bool way_in_polygon = dlhml::is_in(way_pt,old_pts); 
    for(i=0;i<es.size();i++){
      if(!es[i]){
        continue;
      }
      cl_ln = static_cast<Line*>(es[i]);
      drag_pt = cl_ln->middle();
      Point test_pt = output_pt(*cl_ln,way_pt,0.1);
      bool mat_in_polygon = dlhml::is_in(test_pt,old_pts);
      ////拉动到多边形的内外，其他边应与第一个边保持一致。
      if(way_in_polygon==mat_in_polygon){
        mat_pt = output_pt(*cl_ln,way_pt,+dis);
      }else{
        mat_pt = output_pt(*cl_ln,way_pt,-dis);
      }
      Matrix mat;
      mat.set_move(drag_pt,mat_pt);
      cl_ln->transformby(mat);
    }
    ////求交点
    std::vector<Point> pts;
    Entity_Calculate calc;
    Line* preln;
    Point inspt;
    int es_size = es.size();
    for(i=es_size;i<es_size*2;i++){
      if(!getat(es,i) || !getat(es,i-1)){
        continue;
      }
      cl_ln = static_cast<Line*>(getat(es,i));
      preln = static_cast<Line*>(getat(es,i-1));
      if(calc.line_insect_line(inspt,*cl_ln,*preln)){
        pts.push_back(inspt);
      }
    }
//     ////如果不是多边形（扭曲），则不操作失败
//     std::vector<Line*> lns;
//     push(es,lns);
//     if(!is_polygon(lns)){
//       cl->setdata(pts);
//       return_val = false;
//     }
//     //////
    cl->setdata(pts);
    destory(es);
  }
  else if(front_e->isa(MY_RUNTIME_CLASS(Arc_Arrow))){
    Arc_Arrow * aa = static_cast<Arc_Arrow*>(front_e);
    Point cen = aa->center();
    if(cen==ln.end()){
      return false;
    }
    Float r   = cen.distanceto2d(ln.end());
    aa->radius(r);
  }
  else if(front_e->isa(MY_RUNTIME_CLASS(Circle))){
    Circle * cr = static_cast<Circle*>(front_e);
    Point cen = cr->center();
    if(cen==ln.end()){
      return false;
    }
    Float r   = cen.distanceto2d(ln.end());
    cr->radius(r);
  }

  return return_val;
}

Point Offset_Command::key_cammand(const Point& begin, const Point& end)
{
  if(!xor_ || xor_->empty()){
    return end;
  }
  std::vector<Entity*>& x = *xor_;
  Entity * front_e = xor_->front();
  if(!front_e){
    return end;
  }

  double dis = 0;
  if(front_e->isa(MY_RUNTIME_CLASS(Line_Arrow))){
    Line_Arrow * e = static_cast<Line_Arrow*>(front_e);
    Line ln;
    e->getdata(ln);
    dis = ln.distanceto2d(end);
  }
  else if(front_e->isa(MY_RUNTIME_CLASS(Cloud_Line))){
    Cloud_Line * cl = static_cast<Cloud_Line*>(front_e);
    std::vector<Point> pts;
    cl->getdata(pts);
    if(pts.size()<2){
      return end;
    }
    Line ln(pts[0],pts[1]);
    dis = ln.distanceto2d(end);
  }
  else if(front_e->isa(MY_RUNTIME_CLASS(Arc_Arrow))){
    Arc_Arrow * e = static_cast<Arc_Arrow*>(front_e);
    RArc ac;
    ac = e->get();
    Point cen = ac.center();
    if(cen==begin){
      return end;
    }
    Line  rln(begin,cen);
    Point ins = rln.perpendicular(end);
    dis = begin.distanceto2d(ins);
  }
  else if(front_e->isa(MY_RUNTIME_CLASS(Circle))){
    Circle * e = static_cast<Circle*>(front_e);
    Point cen = e->center();
    if(cen==begin){
      return end;
    }
    Line  rln(begin,cen);
    Point ins = rln.perpendicular(end);
    dis = begin.distanceto2d(ins);
  }

  return key_cammand(begin, end, dis);
}
Point Offset_Command::key_cammand(const Point& begin, const Point& way, double val)
{
  if(!xor_ || xor_->empty()){
    return way;
  }
  std::vector<Entity*>& x = *xor_;
  Entity * e = xor_->front();
  if(!e){
    return way;
  }

  Normal nor;
  if(e->isa(MY_RUNTIME_CLASS(Line_Arrow))){
    Line_Arrow * la = static_cast<Line_Arrow*>(e);
    Line dat_ln;
    la->getdata(dat_ln);
    
    nor.set_data(dat_ln);
    nor.rota_z(90);
    Point ext = begin.polarTo(val, nor);
    Line ext_ln(begin,ext);
    Point dicular = ext_ln.perpendicular(way); // 垂足
    nor.set_data(begin,dicular);
  }
  else if(e->isa(MY_RUNTIME_CLASS(Cloud_Line))){
    Cloud_Line * cl = static_cast<Cloud_Line*>(e);
    std::vector<Point> pts;
    cl->getdata(pts);
    if(pts.size()<2){
      return way;
    }
    Line cl_ln(pts[0],pts[1]);
    nor.set_data(cl_ln);
    nor.rota_z(90);
    Point ext = begin.polarTo(val, nor);
    Line ext_ln(begin,ext);
    Point dicular = ext_ln.perpendicular(way); //// 垂足
    nor.set_data(begin,dicular);
  }
  else if(e->isa(MY_RUNTIME_CLASS(Arc_Arrow))){
    Arc_Arrow * aa = static_cast<Arc_Arrow*>(e);
    RArc ac;
    ac = aa->get();
    Point cen = ac.center();
    if(cen==begin){
      nor.set_data(begin,way);
    }
    else{
      Line  rln(begin,cen);
      Point ins = rln.perpendicular(way);
      nor.set_data(begin,ins);
    }
  }
  else if(e->isa(MY_RUNTIME_CLASS(Circle))){
    Circle * cr = static_cast<Circle*>(e);
    Point cen = cr->center();
    if(cen==begin){
      nor.set_data(begin,way);
    }
    else{
      Line  rln(begin,cen);
      Point ins = rln.perpendicular(way);
      nor.set_data(begin,ins);
    }
  }

  return begin.polarTo(val, nor);
}


Point Offset_Command::output_pt(const Line& ln, const Point& way)
{
  Float dis = ln.distanceto2d(way);
  return output_pt(ln,way,dis);
}

Point Offset_Command::output_pt(const Line& ln, const Point& way, double dis)
{
  Point mid = ln.middle();
  Normal nor;
  nor.set_data(ln);
  nor.rota_z(90);
  Point ext = mid.polarTo(dis, nor);
  Line ext_ln(mid,ext);
  Point dicular = ext_ln.perpendicular(way); //// 垂足
  nor.set_data(mid,dicular);
  return mid.polarTo(dis, nor);
}

}//namespace
