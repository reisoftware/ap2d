// Entity_Snap_Implement.cpp: implementation of the Entity_Snap_Implement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Entity_Snap_Implement.h"
#include "Global.h"
#include "Entity_Calculate.h"
#include "Line.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Cloud_Line.h"
#include "intersect.h"
//#include "RArc.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
//line
template<> 
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,
                                            const Line& line) const
{
	Entity_Calculate calc;
	Point p;
	if(!calc.line_insect_line_segment(p,t_,line))
		return false;
	if(p.envelop(rect)){
		pt = p;
		return true;
	}
	return false;
}
template<> 
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,
                                            const Circle& circle) const
{
//	Entity_Calculate calc;
	Point p1,p2;
//f(!calc.line_insect_circle(p1,p2,t_,circle))
	if(!intersect2d_c_s(circle,t_,p1,p2))
		return false;
	if(p1.envelop(rect)){
		pt = p1;
		return true;
	}
	if(p2.envelop(rect)){
		pt = p2;
		return true;
	}
	return false;
}
template<> 
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,
                                            const RArc& arc) const
{
	//Entity_Calculate calc;
	Point p1,p2;
  if(!intersect2d_a_s(arc, t_, p1, p2))
	//if(!calc.line_insect_arc(p1,p2,t_,arc))
		return false;
	if(p1.envelop(rect)){
		pt = p1;
		return true;
	}
	if(p2.envelop(rect)){
		pt = p2;
		return true;
	}
	return false;
}

//bet line
/*
template<> 
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Line>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	Line line;
	dim.get_line(line);
	Entity_Calculate calc;
	Point p;
	if(!calc.line_insect_line_segment(p,t_,line))
		return false;
	if(p.envelop(rect)){
		pt = p;
		return true;
	}
	return false;
}
template<>
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Line>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& cl) const
{
  bool myre = false;
	Entity_Calculate calc;
  Point mypt;
  std::vector<Entity*> lns;
  Line* ln = NULL;
  cl.get_lines(lns);
  int i=0;
  for(; i<lns.size(); i++){
    ln = (Line*)(lns[i]);
    if( calc.line_insect_line(mypt, t_, *ln) && mypt.envelop(rect) ){
      pt = mypt;
      myre = true;
    }
  }
  destory(lns);
  return myre;

  
//  Line ln;
//	int i=0; //bet for cloud
//	int pts_size = cl.pts_.size();
//	int for_limit= mode() == LINE_OPEN ? cl.pts_size-1 : cl.pts_size;
//	for(; i<for_limit; i++){
//		ln.setdata(cl.pts_[(i)%pts_size], cl.pts_[(i+1)%pts_size]);
//    calc.line_insect_line(mypt, ln, t_);
//    if(mypt.envelop(rect)){
//      pt = mypt;
//      return true;
//    }
//	}
//	return false;
}
*/
//ter line


//circle
template<> 
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,
                                            const Line& line) const
{
	//Entity_Calculate calc;
	Point p1,p2;
//f(!calc.line_insect_circle(p1,p2,line,t_))
	if(!intersect2d_c_s(t_, line, p1, p2))
		return false;
	if(p1.envelop(rect)){
		pt = p1;
		return true;
	}
	if(p2.envelop(rect)){
		pt = p2;
		return true;
	}
	return false;
}
template<> 
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,
                                            const Circle& circle) const
{
	Entity_Calculate calc;
	Point p1,p2;
	if(!calc.circle_insect_circle(p1,p2,t_,circle))
		return false;
	if(p1.envelop(rect)){
		pt = p1;
		return true;
	}
	if(p2.envelop(rect)){
		pt = p2;
		return true;
	}
	return false;
}
template<> 
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,
                                            const RArc& arc) const
{
	Entity_Calculate calc;
	Point p1,p2;
	if(!calc.circle_insect_arc(p1,p2,t_,arc))
		return false;
	if(p1.envelop(rect)){
		pt = p1;
		return true;
	}
	if(p2.envelop(rect)){
		pt = p2;
		return true;
	}
	return false;
}

//ter circle and text
/*
template<> 
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Circle>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}

//text
template<> 
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Line& line) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Circle& circle) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const RArc& arc) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Text>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}
*/
//ter circle and text

//arc
template<> 
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,
                                            const Line& line) const
{
//	Entity_Calculate calc;
	Point p1,p2;
  if(!intersect2d_a_s(t_, line, p1, p2))
//	if(!calc.line_insect_arc(p1,p2,line,t_))
		return false;
	if(p1.envelop(rect)){
		pt = p1;
		return true;
	}
	if(p2.envelop(rect)){
		pt = p2;
		return true;
	}
	return false;
}
template<> 
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,
                                            const Circle& circle) const
{
	Entity_Calculate calc;
	Point p1,p2;
	if(!calc.circle_insect_arc(p1,p2,circle,t_))
		return false;
	if(p1.envelop(rect)){
		pt = p1;
		return true;
	}
	if(p2.envelop(rect)){
		pt = p2;
		return true;
	}
	return false;
}
template<> 
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,
                                            const RArc& arc) const
{
	Entity_Calculate calc;
	Point p1,p2;
	if(!calc.arc_insect_arc(p1,p2,t_,arc))
		return false;
	if(p1.envelop(rect)){
		pt = p1;
		return true;
	}
	if(p2.envelop(rect)){
		pt = p2;
		return true;
	}
	return false;
}
//bet arc and the other
/*
template<> 
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<RArc>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}

//Three_Pt_Dimension
template<> 
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Line& line) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Circle& circle) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const RArc& arc) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Three_Pt_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}

//Ln_Dim
template<> 
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Line& line) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Circle& circle) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const RArc& arc) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Ln_Dim>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}

//Text_Dimension
template<> 
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Line& line) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Circle& circle) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const RArc& arc) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Text_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}

//Lead_Dimension
template<> 
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Line& line) const
{
//	Line line;
//	dim.get_line(line);
//	Entity_Calculate calc;
//	Point p;
//	if(!calc.line_insect_line_segment(p,t_,line))
//		return false;
//	if(p.envelop(rect)){
//		pt = p;
//		return true;
//	}
//	return false;
	return false;
}
template<> 
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Circle& circle) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const RArc& arc) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Lead_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}

//Angle_Dimension
template<> 
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Line& line) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Circle& circle) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const RArc& arc) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Angle_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}

//Radius_Dimension
template<> 
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Line& line) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Circle& circle) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const RArc& arc) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Radius_Dimension>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& dim) const
{
	return false;
}

//Cloud_Line
template<> 
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Line& line) const
{
  bool myre = false;
	Entity_Calculate calc;
  Point mypt;
  std::vector<Entity*> lns;
  Line* ln = NULL;
  t_.get_lines(lns);
  int i=0;
  for(; i<lns.size(); i++){
    ln = (Line*)(lns[i]);
    if( calc.line_insect_line(mypt, line, *ln) && mypt.envelop(rect) ){
      pt = mypt;
      myre = true;
    }
  }
  destory(lns);
  return myre;
}
template<> 
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Circle& circle) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const RArc& arc) const
{
	return false;
}
template<> 
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Text& text) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Three_Pt_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Ln_Dim& dim) const
{
	return false;
}
//template<>
//bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
template<>
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Text_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Lead_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Angle_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Radius_Dimension& dim) const
{
	return false;
}
template<>
bool Entity_Snap_Implement<Cloud_Line>::intersect(Point& pt,
																						const Rect& rect,const Cloud_Line& cl) const
{
  bool myre = false;
	Entity_Calculate calc;
  Point mypt;
  std::vector<Entity*> lns_1, lns_2;
  Line* ln_1=NULL;
  Line* ln_2=NULL;
  t_.get_lines(lns_1);
  cl.get_lines(lns_2);

  int i=0, k=0;
  for(; i<lns_1.size(); i++){
    ln_1 = (Line*)(lns_1[i]);
    for(; k<lns_1.size(); k++){
      ln_2 = (Line*)(lns_2[k]);
      if( calc.line_insect_line(mypt, *ln_1, *ln_2) && mypt.envelop(rect) ){
        pt = mypt;
        myre = true;
      }
    }
  }
  destory(lns_1);
  destory(lns_2);
  return myre;
}

//Line_Dim
//template<> 
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Line& line) const
//{
//	return false;
//}
//template<> 
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Circle& circle) const
//{
//	return false;
//}
//template<> 
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const RArc& arc) const
//{
//	return false;
//}
//template<> 
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Text& text) const
//{
//	return false;
//}
//template<>
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Three_Pt_Dimension& dim) const
//{
//	return false;
//}
//template<>
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Ln_Dim& dim) const
//{
//	return false;
//}
//template<>
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Line_Dim& dim) const
//{
//	return false;
//}
//template<>
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Text_Dimension& dim) const
//{
//	return false;
//}
//template<>
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Lead_Dimension& dim) const
//{
//	return false;
//}
//template<>
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Angle_Dimension& dim) const
//{
//	return false;
//}
//template<>
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Radius_Dimension& dim) const
//{
//	return false;
//}
//template<>
//bool Entity_Snap_Implement<Line_Dim>::intersect(Point& pt,
//																						const Rect& rect,const Cloud_Line& dim) const
//{
//	return false;
//}

*/
//ter arc and the other

}
