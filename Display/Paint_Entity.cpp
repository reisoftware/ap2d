// Paint_Entity.cpp: implementation of the Paint_Entity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Paint_Entity.h"
#include "../object/Global.h"

#include "Point.h"
#include "Line.h"
#include "Rectentity.h"
#include "Scene_d.h"
#include "Painter.h"
#include "Line_Type.h"
#include "Database.h"
#include "Select_Pen.h"
#include "Text.h"
#include "Cloud_Line.h"
#include "Select_Font.h"
#include "Text_Style.h"
#include "Circle.h"
#include "RArc.h"
#include "Create_Entity.h"

#include "Three_Pt_Dimension.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Lead_Dimension_Block.h"
#include "Text_Dimension.h"
#include "Tool_Arithmetic.h"
#include "Paint_Entity_Tools.h"
#include "Ln_Dim.h"
//#include "Line_Dim.h"
#include "Angle_Dimension.h"
#include "Radius_Dimension.h"
#include "Cut_Section.h"


#include "Normal.h"
#include <cassert>
#include "getrace.h"

//#define NO_TRANSFORM


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace dlhml{

DWORD WINAPI MyThreadProc(LPVOID lpParameter)
{
	return 0;
}

HANDLE Paint_Entity::thread_ = 0;
Paint_Entity::Paint_Entity(Scene& scene,Painter& painter)
:scene_(scene)
,painter_(painter)
MCT_INIT2("Paint_Entity")
{
	line_style_ = 0;
/*
	if(!thread_){
		thread_ = CreateThread(NULL,  // no security attributes 
			0,                // use default stack size 
			(LPTHREAD_START_ROUTINE) MyThreadProc, 
			(LPVOID)&scene_, // param to thread func 
			CREATE_SUSPENDED, // creation flag 
			0);       // thread identifier 
		assert(thread_);
		BOOL b = SetThreadPriority(thread_,THREAD_PRIORITY_BELOW_NORMAL);
		assert(b);
		DWORD err = ResumeThread(thread_);
		assert(err != -1);
	}
*/
}

Paint_Entity::~Paint_Entity()
{

}
void Paint_Entity::close()
{
	delete this;
}
void Paint_Entity::rect_select_entity(std::list<Entity*>& ents,
                                      const Rect& rect)
{
  Rect itrc;
  Float xmin=rect.xmin();
  Float xmax=rect.xmax();
  Float ymin=rect.ymin();
  Float ymax=rect.ymax();

  int i=0;
  entity_iterator iter;
  iter=scene_.database()->entity_begin();
  for(; iter != scene_.database()->entity_end(); ++iter){
    if(  !(*iter)->isa(MY_RUNTIME_CLASS(Ln_Dim_Block        )) 
      && !(*iter)->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block)) ){
      itrc=(*iter)->box2d();
      if(itrc.xmax() < xmin){
        continue;
      }
      if(itrc.xmin() > xmax){
        continue;
      }
      if(itrc.ymax() < ymin){
        continue;
      }
      if(itrc.ymin() > ymax){
        continue;
      }
      //		if(++i>50000)
      //			continue;
    }
    ents.push_back(*iter);
  }
}

//BET
//liming 09.08.07
//void Paint_Entity::rect_select_entity(std::list<Entity*>& ents,const Rect& rect)
//{
//  int i=0;
//  entity_iterator iter;
//  iter=scene_.database()->entity_begin();
//  for(; iter != scene_.database()->entity_end(); ++iter){
//    if((*iter)->box2d().xmax() < rect.xmin())
//      continue;
//    if((*iter)->box2d().xmin() > rect.xmax())
//      continue;
//    if((*iter)->box2d().ymax() < rect.ymin())
//      continue;
//    if((*iter)->box2d().ymin() > rect.ymax())
//      continue;
//    //if(++i>50000)
//    //	continue;
//    ents.push_back(*iter);
//  }
//}
//TER

void Paint_Entity::draw_coord()
{
	Point org(20,scene_.screen_cy()-20);
	scene_.screen_to_world_point(org);
	//Point org(0,0);
	
	Point st,ed;
	Line line;
	line.line_style("dot");
	line.color_index(1);
	Float len = 100 * scene_.screen_to_world().value(0,0);
	
  Text text;
	text.color_index(1);
  text.align_point(Text::right_top);
  text.dxf_height(len/8);
	
	st.setdata(org.x-len/10, org.y);
	ed.setdata(org.x+len, org.y);
	line.setdata(st,ed);
	draw_line(line);
	text.setdata(ed,"X");
	draw_text(text);
	
	st.setdata(org.x, org.y-len/10);
	ed.setdata(org.x, org.y+len);
	line.setdata(st,ed);
	draw_line(line);
	text.setdata(ed,"Y");
	draw_text(text);
}

void Paint_Entity::draw_entity_list(std::list<Entity*>& ents)
{
  std::list<Entity*>::iterator iter;
  for(iter=ents.begin();iter!=ents.end();++iter){
    (*iter)->draw(*this);
  }
}

void Paint_Entity::draw_entity_list(std::list<Entity*>& ents, int max_count)
{
  assert(max_count>=1);
  int ents_size = ents.size();
  assert(ents.size() >= max_count*2);
  int interval_dis = ents_size / max_count;
  assert(interval_dis >= 2);
  int i=0;
  std::list<Entity*>::iterator iter;
  for(iter=ents.begin();iter!=ents.end();++iter){
    ////超过max_draw_count个元素，间隔着画
    ++i;
    assert(interval_dis);
    if(i%interval_dis){
      continue;
    }
    (*iter)->draw(*this);
  }
}

void Paint_Entity::draw_database()
{
  entity_iterator iter;
  iter=scene_.database()->entity_begin();
  for(; iter != scene_.database()->entity_end(); ++iter){
    (*iter)->draw(*this);
  }
}

void Paint_Entity::draw_entity(std::list<Entity*>& ents)
{
  int max_count = scene_.max_draw_count();
  if(max_count<=0 || ents.size() < max_count*2){
    draw_entity_list(ents);
  }else{
    draw_entity_list(ents, max_count);
  }
}

// void Paint_Entity::draw_entity(std::list<Entity*>& ents)
// {
//   int ents_size = ents.size();
//   int interval_dis = ents_size / scene_.max_draw_count() + 1;
//   int i=0;
//   std::list<Entity*>::iterator iter;
//   for(iter=ents.begin();iter!=ents.end();++iter){
//     ////超过max_draw_count个元素，间隔着画
//     ++i;
//     assert(interval_dis);
//     if(i%interval_dis){
//       continue;
//     }
//     (*iter)->draw(*this);
//   }
// }

void Paint_Entity::draw_all_entity() 
{ 
  Rect rc = scene_.client_rect();
  Matrix mat = scene_.screen_to_world();
  rc.transformby(mat);
  painter_.set_memory_dc(scene_.background_color(),mat);
  

#ifndef USE_IMAGE 
  std::list<Entity*> ents;
  rect_select_entity(ents,rc);
  draw_entity(ents);
#else 
  draw_database();
#endif 

	draw_coord();
	painter_.display_memory(); 
} 


//BET
//2010.12.29
// void Paint_Entity::draw_all_entity() 
// { 
//   Rect rc = scene_.client_rect();
//   Matrix mat = scene_.screen_to_world();
//   rc.transformby(mat);
//   painter_.set_memory_dc(scene_.background_color(),mat);
//   
// 
// #ifndef USE_IMAGE 
//   //std::string old_layer;
//   //TRACE_OUT("Paint_Entity::draw_all_entity()  USE_IMAGE\n");
//   std::list<Entity*> ents;
//   rect_select_entity(ents,rc);
// //   int ents_size = ents.size();
// //   int interval_dis = ents_size / scene_.max_draw_count() + 1;
// //   int i=0;
// //   std::list<Entity*>::iterator iter;
// //   for(iter=ents.begin();iter!=ents.end();++iter){
// //     ////超过max_draw_count个元素，间隔着画
// //     ++i;
// //     assert(interval_dis);
// //     if(i%interval_dis){
// //       continue;
// //     }
// //     (*iter)->draw(*this);
// //   }
// #else 
// //   entity_iterator iter;
// //   iter=scene_.database()->entity_begin();
// //   for(; iter != scene_.database()->entity_end(); ++iter)
// //     (*iter)->draw(*this);
// #endif 
// 
// //#ifdef _DEBUG
// //  Line gln;
// //  gln.setdata(Point(0,0),Point(1000,1000));
// //  gln.color_index(5);
// //  gln.line_style("dot");
// //  gln.xor_draw(*this);
// //#endif
// 
// 	////
// 	draw_coord();
//  
// 	painter_.display_memory(); 
//  
// } 
//TER

//BET
//liming 09.08.07
//void Paint_Entity::draw_all_entity()
//{
//  Rect rc = scene_.client_rect();
//  Matrix mat = scene_.screen_to_world();
//  rc.transformby(mat);
//  painter_.set_memory_dc(scene_.background_color(),mat);
//#ifndef USE_IMAGE
//  //std::string old_layer;
//  std::vector<Entity*> ents;
//  rect_select_entity(ents,rc);
//  std::vector<Entity*>::iterator iter;
//  for(iter=ents.begin();iter!=ents.end();++iter){
//    //old_layer=(*iter)->line_style();
//    //(*iter)->line_style("Continuous");
//    (*iter)->draw(*this);
//    //(*iter)->line_style(old_layer.c_str());
//  }
//#else
//  entity_iterator iter;
//  iter=scene_.database()->entity_begin();
//  for(; iter != scene_.database()->entity_end(); ++iter)
//    (*iter)->draw(*this);
//#endif
//  
//  //#ifdef _DEBUG
//  //  Line gln;
//  //  gln.setdata(Point(0,0),Point(1000,1000));
//  //  gln.color_index(5);
//  //  gln.line_style("dot");
//  //  gln.xor_draw(*this);
//  //#endif
//  
//  Point st,ed;
//  Text text;
//  Line line;
//  line.line_style("dot");
//  line.color(RGB(255,0,0));
//  Float len = 100 * scene_.screen_to_world().value(0,0);
//  st.setdata(-len/10,0);
//  ed.setdata(len,0);
//  line.setdata(st,ed);
//  draw_line(line);
//  text.setdata(ed,"X");
//  text.align_point(Text::right_top);
//  text.height(len/5);
//  draw_text(text);
//  st.setdata(0,-len/10);
//  ed.setdata(0,len);
//  line.setdata(st,ed);
//  draw_line(line);
//  text.setdata(ed,"Y");
//  draw_text(text);
//  
//  painter_.display_memory();
//  
//}
//TER

Point Paint_Entity::world_to_screen(const Point& pt)
{
	Point p(pt);
	scene_.world_to_screen_point(p);
	return p;
}


void Paint_Entity::draw_rect(const Rect& rect, bool xor)
{
  Point st,ed;
  Line ln;
  ln.color_index(rect.color_index ());
  ln.selected(rect.selected());
  
  st.setdata(rect.xmin(),rect.ymin());
  ed.setdata(rect.xmin(),rect.ymax());
  ln.setdata(st,ed);
  draw_line(ln,xor);
  
  st.setdata(rect.xmax(),rect.ymax());
  ln.setdata(st,ed);
  draw_line(ln,xor);
  
  ed.setdata(rect.xmax(),rect.ymin());
  ln.setdata(st,ed);
  draw_line(ln,xor);
  
  st.setdata(rect.xmin(),rect.ymin());
  ln.setdata(st,ed);
  draw_line(ln,xor);
}
void Paint_Entity::draw_rect(const Rect& rect)
{
  draw_rect(rect,false);
// 	Point st,ed;
// 	Line ln;
//   ln.color_index(rect.color_index ());
//   ln.selected   (rect.selected    ());
// 
// 	st.setdata(rect.xmin(),rect.ymin());
// 	ed.setdata(rect.xmin(),rect.ymax());
//   ln.setdata(st,ed);
//   draw_line(ln);
// 
// 	st.setdata(rect.xmax(),rect.ymax());
//   ln.setdata(st,ed);
//   draw_line(ln);
// 
// 	ed.setdata(rect.xmax(),rect.ymin());
//   ln.setdata(st,ed);
//   draw_line(ln);
// 
// 	st.setdata(rect.xmin(),rect.ymin());
//   ln.setdata(st,ed);
//   draw_line(ln);
}
void Paint_Entity::xor_draw_rect(const Rect& rect)
{
  draw_rect(rect,true);
// 	Point st,ed;
// 	Line ln;
//   ln.color_index(rect.color_index ());
//   ln.selected   (rect.selected    ());
// 
// 	st.setdata(rect.xmin(),rect.ymin());
// 	ed.setdata(rect.xmin(),rect.ymax());
//   ln.setdata(st,ed);
//   xor_draw_line(ln);
// 
// 	st.setdata(rect.xmax(),rect.ymax());
//   ln.setdata(st,ed);
//   xor_draw_line(ln);
// 
// 	ed.setdata(rect.xmax(),rect.ymin());
//   ln.setdata(st,ed);
//   xor_draw_line(ln);
// 
// 	st.setdata(rect.xmin(),rect.ymin());
//   ln.setdata(st,ed);
//   xor_draw_line(ln);
// // 	Point st,ed;
// // 	Line line;
// // 	//line.color(RGB(255,0,0));
// //   line.color_index(3);
// // 
// // 	select_linestyle(line);
// // 	Select_Pen pen(painter_,line,line_style_);
// // 
// // 	st.setdata(rect.xmin(),rect.ymin());
// // 	ed.setdata(rect.xmin(),rect.ymax());
// // 	painter_.xor_line(world_to_screen(st),world_to_screen(ed));
// // 
// // 	st.setdata(rect.xmax(),rect.ymax());
// // 	painter_.xor_line(world_to_screen(st),world_to_screen(ed));
// // 
// // 	ed.setdata(rect.xmax(),rect.ymin());
// // 	painter_.xor_line(world_to_screen(st),world_to_screen(ed));
// // 
// // 	st.setdata(rect.xmin(),rect.ymin());
// // 	painter_.xor_line(world_to_screen(st),world_to_screen(ed));
}
void Paint_Entity::select_linestyle(const Entity& ent)
{
	if(line_style_ != NULL){
		if(strcmp(line_style_->name(),ent.line_style().c_str())==0)
			return;
	}
	if(line_style_!= NULL)
		line_style_ = 0;
	scene_.database()->get_linetype(line_style_,ent.line_style());
}

static bool is_solid(const Line& ln)
{
	return (!strcmp(ln.line_style().c_str(),"Continuous"));
}

void Paint_Entity::paint_line(const Line& line, 
															bool xor, 
															const Point& st, 
															const Point& ed)
{
//   if(st.distanceto2d(ed)<1000){
//     //TRACE_OUT("st[%f,%f], ed[%f,%f]\n", st.x, st.y, ed.x, ed.y);
//     return;
//   }
	
	if(line.selected() && !is_solid(line)){
		Line solid = line;
    solid.line_style(dlhml::lt_continue());

		select_linestyle(solid);
		Select_Pen solid_pen(painter_,solid,line_style_);
		if(xor){
			painter_.xor_line(st,ed);
		}
		else{
			painter_.line(st,ed);
		}

		Line cente = line;
		cente.selected(false);
		cente.color_index(0);

		select_linestyle(cente);
		Select_Pen center_pen(painter_,cente,line_style_);
		if(xor){
			painter_.xor_line(st,ed);
		}
		else{
			painter_.line(st,ed);
		}

	}
	else{
		select_linestyle(line);
		Select_Pen pen(painter_,line,line_style_);
		if(xor){
			painter_.xor_line(st,ed);
		}
		else{
			painter_.line(st,ed);
		}
	}
}

void Paint_Entity::xor_draw_line(const Line& line)
{
	Point lspt = world_to_screen(line.start());
	Point lept = world_to_screen(line.end());

	paint_line(line, true, lspt, lept);

}

//	if(line.selected() && !is_solid(line)){
//		Line solid = line;
//		solid.line_style("Continuous");
//
//		select_linestyle(solid);
//		Select_Pen solid_pen(painter_,solid,line_style_);
//		painter_.xor_line(lspt,lept);
//
//		Line cente = line;
//		cente.selected(false);
//		cente.color_index(0);
//
//		select_linestyle(cente);
//		Select_Pen center_pen(painter_,cente,line_style_);
//		painter_.line(lspt,lept);
//
//	}
//	else{
//		select_linestyle(line);
//		Select_Pen pen(painter_,line,line_style_);
//		painter_.xor_line(lspt,lept);
//	}

void Paint_Entity::draw_line(const Line& line)
{
	Point lspt = line.start();
	Point lept = line.end();
#ifndef NO_TRANSFORM
	lspt.transformby2d(scene_.world_to_screen());
	lept.transformby2d(scene_.world_to_screen());
#endif

	paint_line(line, false, lspt, lept);
}

//	if(line.selected() && !is_solid(line)){
//		Line solid = line;
//		solid.line_style("Continuous");
//
//		select_linestyle(solid);
//		Select_Pen solid_pen(painter_,solid,line_style_);
//		painter_.line(lspt,lept);
//
//		Line cente = line;
//		cente.selected(false);
//		cente.color_index(0);
//
//		select_linestyle(cente);
//		Select_Pen center_pen(painter_,cente,line_style_);
//		painter_.line(lspt,lept);
//
//	}
//	else{
//		select_linestyle(line);
//		Select_Pen pen(painter_,line,line_style_);
//		painter_.line(lspt,lept);
//	}

void Paint_Entity::draw_line(const Line& line, bool xor)
{
  if(xor){
    xor_draw_line(line);
  }
  else{
    draw_line(line);
  }
}
void Paint_Entity::draw_arc(const RArc& arc)
{
	if(arc.selected() && strcmp(arc.line_style().c_str(),"Continuous")!=0){
		RArc solid = arc;
		solid.line_style("Continuous");
		paint_arc(solid);

		RArc cente = arc;
		cente.selected(false);
		paint_arc(cente);
	}
	else{
		paint_arc(arc);
	}
}

bool Paint_Entity::output_arc(const RArc& arc)
{
  TRACE_OUT("\n**************************** draw arc ****************************\n");
  TRACE_OUT("arc_.s == %f, %f, %f\n", arc.start().x, arc.start().y, arc.start().z);
  TRACE_OUT("arc_.p == %f, %f, %f\n", arc.path().x, arc.path().y, arc.path().z);
  TRACE_OUT("arc_.e == %f, %f, %f\n", arc.end().x, arc.end().y, arc.end().z);
  TRACE_OUT("arc_.c == %f, %f, %f\n", arc.center().x, arc.center().y, arc.center().z);
  TRACE_OUT("arc_.r == %f\n", arc.radius());
  TRACE_OUT("arc_.sdeg == %f\n", arc.start_degree2d());
  TRACE_OUT("arc_.edeg == %f\n", arc.end_degree2d());
  TRACE_OUT("arc_.srad == %f\n", arc.start_radian2d());
  TRACE_OUT("arc_.erad == %f\n", arc.end_radian2d());
  TRACE_OUT("arc_.color == %d\n", arc.color_index());
  TRACE_OUT("arc_.box.min == %f, %f, %f\n", arc.box2d().xmin(), arc.box2d().ymin());
  TRACE_OUT("arc_.box.max == %f, %f, %f\n", arc.box2d().xmax(), arc.box2d().ymax());
  Line cs(arc.center(), arc.start());
  Line cp(arc.center(), arc.path());
  Line ce(arc.center(), arc.end());
  draw_line(cs);
  draw_line(cp);
  draw_line(ce);
  Rect boxrc = arc.box2d();
  draw_rect(boxrc);
  return true;
}

void Paint_Entity::paint_arc(const RArc& arc)
{
  Line ln;
  ln.color_index(arc.color_index());
  ln.line_style(arc.line_style());
  ln.setdata(arc.start(), arc.end());
  if(ln.length() < 1){
    draw_line(ln, false);
    return;
  }
  if(ln.is_in_line(arc.path())){
    draw_line(ln, false);
    return;
  }
  
	Point cen = arc.center();
	Point ptr = cen;
	ptr.x += arc.radius();
#ifndef NO_TRANSFORM
	cen = world_to_screen(cen);
	ptr = world_to_screen(ptr);
#endif
	Float r = ptr.x-cen.x;


	Float sweep;
	if(arc.end_degree2d() < arc.start_degree2d())
		sweep = arc.end_degree2d()+360-arc.start_degree2d();
	else
		sweep = arc.end_degree2d()-arc.start_degree2d();
	
	select_linestyle(arc);
	Select_Pen pen(painter_,arc,line_style_);
	painter_.angle_arc(cen.x,cen.y,r,arc.start_degree2d(),sweep);
//   assert(output_arc(arc));
}

void Paint_Entity::xor_draw_arc(const RArc& arc)
{
	if(arc.selected() && strcmp(arc.line_style().c_str(),"Continuous")!=0){
		RArc solid = arc;
		solid.line_style("Continuous");
		xor_paint_arc(solid);

		RArc cente = arc;
		cente.selected(false);
		xor_paint_arc(cente);
	}
	else{
		xor_paint_arc(arc);
	}
}
void Paint_Entity::xor_paint_arc(const RArc& arc)
{
  Line ln;
  Point pt1, pt2, pt3;
  pt1 = arc.start();
  pt2 = arc.path();
  pt3 = arc.end();
  //arc.getdata(pt1, pt2, pt3);
  if(pt1==pt2){
    return;
  }
  if(pt2==pt3){
    ln.setdata(pt1, pt2);
    ln.color_index(arc.color_index());
    xor_draw_line(ln);
    return;
  }
  if(pt1.distanceto2d(pt3)<1){
    ln.setdata(pt1, pt3);
    ln.color_index(arc.color_index());
    xor_draw_line(ln);
    return;
  }

	Point lt(arc.center().x-arc.radius(),arc.center().y-arc.radius());
	Point rb(arc.center().x+arc.radius(),arc.center().y+arc.radius());
	Point st,ed;
  st = arc.start2d();
  ed = arc.end2d();
	//arc.get_end_point(st,ed);

	select_linestyle(arc);
	Select_Pen pen(painter_,arc,line_style_);

	painter_.xor_arc(world_to_screen(lt),world_to_screen(rb),
		world_to_screen(st),world_to_screen(ed));
//   TRACE_OUT("xor---------------\n");
//   TRACE_OUT("arc_.s == %f,%f,%f\n", arc.start().x, arc.start().y, arc.start().z);
//   TRACE_OUT("arc_.p == %f,%f,%f\n", arc.path().x, arc.path().y, arc.path().z);
//   TRACE_OUT("arc_.e == %f,%f,%f\n", arc.end().x, arc.end().y, arc.end().z);
//   TRACE_OUT("arc_.c == %f,%f,%f\n", arc.center().x, arc.center().y, arc.center().z);
//   TRACE_OUT("arc_.sdeg == %f\n", arc.start_degree2d());
//   TRACE_OUT("arc_.edeg == %f\n", arc.end_degree2d());
}

////circle
void Paint_Entity::draw_circle(const Circle& circle)
{
	if(circle.selected() && strcmp(circle.line_style().c_str(),"Continuous")!=0){
		Circle solid = circle;
		solid.line_style("Continuous");
		paint_circle(solid);

		Circle cente = circle;
		cente.selected(false);
		paint_circle(cente);
	}
	else{
		paint_circle(circle);
	}
}
void Paint_Entity::paint_circle(const Circle& circle)
{
	Point lr,rb;
	Float r = circle.radius();
	lr.setdata(circle.center().x-r,circle.center().y-r);
	rb.setdata(circle.center().x+r,circle.center().y+r);
#ifndef NO_TRANSFORM
	lr = world_to_screen(lr);
	rb = world_to_screen(rb);
#endif

	select_linestyle(circle);
	Select_Pen pen(painter_,circle,line_style_);

	painter_.ellipse(lr.x,lr.y,rb.x,rb.y);
}

void Paint_Entity::xor_draw_circle(const Circle& circle)
{
	if(circle.selected() && strcmp(circle.line_style().c_str(),"Continuous")!=0){
		Circle solid = circle;
		solid.line_style("Continuous");
		xor_paint_circle(solid);

		Circle cente = circle;
		cente.selected(false);
		xor_paint_circle(cente);
	}
	else{
		xor_paint_circle(circle);
	}
}
void Paint_Entity::xor_paint_circle(const Circle& circle)
{
	Point lr,rb;
	Float r = circle.radius();
	lr.setdata(circle.center().x-r,circle.center().y-r);
	rb.setdata(circle.center().x+r,circle.center().y+r);
	lr = world_to_screen(lr);
	rb = world_to_screen(rb);

	select_linestyle(circle);
	Select_Pen pen(painter_,circle,line_style_);

	painter_.xor_ellipse(lr.x,lr.y,rb.x,rb.y);
}



///////
void Paint_Entity::draw_rectentity(const Rectentity& rect)
{
	Line line[4];
	rect.get_line(line);
	for(int i=0;i<4;++i){
		line[i].color(rect.color());
		line[i].line_style(rect.line_style());
		draw_line(line[i]);
	}
}
void Paint_Entity::draw_solid_circle(const Circle& circle)
{
	Point lr,rb;
	Float r = circle.radius();
	lr.setdata(circle.center().x-r,circle.center().y-r);
	rb.setdata(circle.center().x+r,circle.center().y+r);
	lr = world_to_screen(lr);
	rb = world_to_screen(rb);

	select_linestyle(circle);
	Select_Pen pen(painter_,circle,line_style_);

	painter_.ellipse(lr.x,lr.y,rb.x,rb.y,true);

  Line c(circle.center(), circle.center());
  c.selected(true);
  draw_line(c);

}


void Paint_Entity::draw_text(const Text& text)
{
	Point pos;
	text.left_top_point(pos);
#ifndef NO_TRANSFORM
	scene_.world_to_screen_point(pos);
#endif

	Matrix m = scene_.world_to_screen();
	Float h = text.gdi_height()*m.value(0,0);
  
  if(h<1){
    return;
    h = 1;
  }

  bool sel = text.selected();
  if(!sel){
    ////用线代替
    if(h <= 3){
      Line ln1 = text.center_line();
      ln1.color(text.color());
  //     if(sel){
  //       ln1.color_index(7);
  //     }
      draw_line(ln1);
      return;
    }
    if(h <= 6){
      Line ln1 = text.center_line();
      ln1.color(text.color());
  //     if(sel){
  //       ln1.color_index(7);
  //     }
      ln1.selected(true);
      draw_line(ln1);
      return;
    }
  }

  Text t(text);
  t.gdi_height(h);
  
  if(sel){
    //t.color(text.color() ^ RGB(255,255,255));
    t.color(RGB(0,0,0));
  }

	Text_Style ts = text.style_val();
	Select_Font font(painter_,t,&ts);
		
  painter_.textout(pos, text.text().c_str(), text.color(), sel);

  ////test
//   Line ln1 = text.dxf_base_line();
//   ln1.color(text.color());
//   draw_line(ln1);
  
}
void Paint_Entity::xor_draw_text(const Text& text)
{
	Point pos;
	text.left_top_point(pos);
	scene_.world_to_screen_point(pos);

	Matrix m = scene_.world_to_screen();
	Float h = text.gdi_height()*m.value(0,0);

	Text t(text);
	t.gdi_height(h);

	Text_Style* ts = &(t.style_val());
	//scene_.database()->get_textstyle(ts,text.style_name());
	Select_Font font(painter_,t,ts);

  if(text.selected()){
//		painter_.graystring(pos,text.text(),RGB(0,0,0));
//		painter_.xor_textout(pos,text.text());
//		painter_.graystring(pos,text.text(),text.color());
    COLORREF old_color = painter_.set_text_color(scene_.background_color());
		painter_.xor_textout(pos,text.text().c_str());
    painter_.set_text_color(old_color);
		painter_.graystring(pos,text.text().c_str(),scene_.background_color());
  }
  else{
		painter_.xor_textout(pos,text.text().c_str());
  }
}
//BET 2009.08.14
//liming
//void Paint_Entity::draw_text(const Text& text)
//{
//	Point pos;
//	text.left_top_point(pos);
//#ifndef NO_TRANSFORM
//	scene_.world_to_screen_point(pos);
//#endif
//
//	Matrix m = scene_.world_to_screen();
//	Float height = text.height()*m.value(0,0);
//	if(height<1)
//		height =1;
//
//	Text t(text);
//	t.height(height);
//
//	Text_Style* ts = NULL;
//	scene_.database()->get_textstyle(ts,text.style_name());
//	Select_Font font(painter_,t,ts);
//
//  if(text.selected()){
//    COLORREF old_color = painter_.set_text_color(scene_.background_color());
//		painter_.textout(pos,text.text());
//    painter_.set_text_color(old_color);
//		painter_.graystring(pos,text.text(),text.color());
//  }
//  else{
//		painter_.textout(pos,text.text());
//  }
////#ifdef _DEBUG
////	draw_rect(text.box2d());
////#endif
//
//}
//void Paint_Entity::xor_draw_text(const Text& text)
//{
//	Point pos;
//	text.left_top_point(pos);
//	scene_.world_to_screen_point(pos);
//
//	Matrix m = scene_.world_to_screen();
//	Float height = text.height()*m.value(0,0);
//
//	Text t(text);
//	t.height(height);
//
//	Text_Style* ts = &(t.style_val());
//	//scene_.database()->get_textstyle(ts,text.style_name());
//	Select_Font font(painter_,t,ts);
//
//  if(text.selected()){
////		painter_.graystring(pos,text.text(),RGB(0,0,0));
////		painter_.xor_textout(pos,text.text());
////		painter_.graystring(pos,text.text(),text.color());
//    COLORREF old_color = painter_.set_text_color(scene_.background_color());
//		painter_.xor_textout(pos,text.text());
//    painter_.set_text_color(old_color);
//		painter_.graystring(pos,text.text(),scene_.background_color());
//  }
//  else{
//		painter_.xor_textout(pos,text.text());
//  }
//}
//TER
void Paint_Entity::xor_draw_rectentity(const Rectentity& rect)
{
	Line line[4];
	rect.get_line(line);
	for(int i=0;i<4;++i){
		line[i].color(rect.color());
		line[i].line_style(rect.line_style());
		xor_draw_line(line[i]);
	}
}
void Paint_Entity::xor_draw_solid_circle(const Circle& circle)
{
	Point lr,rb;
	Float r = circle.radius();
	lr.setdata(circle.center().x-r,circle.center().y-r);
	rb.setdata(circle.center().x+r,circle.center().y+r);
	lr = world_to_screen(lr);
	rb = world_to_screen(rb);

	select_linestyle(circle);
	Select_Pen pen(painter_,circle,line_style_);

	painter_.xor_ellipse(lr.x,lr.y,rb.x,rb.y,true);
}

//cloud line
void Paint_Entity::draw_cloud_line(const Cloud_Line& cloud)
{
	cloud_line_paint(cloud, false);
}
void Paint_Entity::xor_draw_cloud_line(const Cloud_Line& cloud)
{
	cloud_line_paint(cloud, true);
}
void Paint_Entity::cloud_line_paint(const Cloud_Line& cloud, bool xor)
{
  bool sel = cloud.selected();
	std::vector<Entity*>  lns;
  cloud.get_lines(lns);
  ////当没有ok之前，外部设置open（true）了。
  if(!cloud.open() && lns.size()==2){
    xor ? lns[0]->xor_draw(*this) : lns[0]->draw(*this);
		dlhml::destory(lns);
    return;
  }
  int i=0;
  for(i=0; i<lns.size(); i++){
    if(!lns[i]){
      continue;
    }
    lns[i]->line_style(cloud.line_style());
  }
  for(i=0; i<lns.size(); i++){
    if(!lns[i]){
      continue;
    }
    xor ? lns[i]->xor_draw(*this) : lns[i]->draw(*this);
  }
  destory(lns);
	return;


  //  bool sel = cloud.selected();
  //	if(cloud.mode() == LINE_OPEN || cloud.mode() == LINE_CLOSED)	{
  //		Line ln;
  //		ln.selected(sel);
  //    ln.color(cloud.color());
  //		std::vector<Line>  lns;
  //		std::vector<Point> pts;
  //		cloud.getdata(pts);
  //		int i=0; 
  //		int pts_size = pts.size();
  //		int for_limit= cloud.mode() == LINE_OPEN ? pts_size-1 : pts_size;
  //		for(; i<for_limit; i++){
  //			ln.setdata(pts[(i)%pts_size], pts[(i+1)%pts_size]);
  //			xor ? xor_draw_line(ln) : draw_line(ln);
  //		}
  //	}
  //	return;

  Matrix mat;
  mat.set_z_rotation_radian(-pi/2);
  Normal nor;
  RArc arc;
  arc.color(cloud.color());
  Point st,ed,pt,c;
  std::vector<Point> pts;
  cloud.getdata(pts);
  for(std::vector<Point>::iterator it=pts.begin();it!=pts.end()-1;++it){
    st = *it;
    ed = *(it+1);
    pt = ed-st;
    pt.transformby(mat);
    nor.set_data(pt.x,pt.y,0);
    pt = (st+ed)/2;
    c = pt.polarTo(st.distanceto(ed)/2,nor);
    Float r = c.distanceto(st);
    nor.set_data(c,ed);
    Float stang = nor.angle_x_axis_two_pi()*180/pi;
    nor.set_data(c,st);
    Float edang = nor.angle_x_axis_two_pi()*180/pi;
    //arc.setdata(c,r,stang,edang);
    arc.selected(sel);
    draw_arc(arc);
  }
}

  //void Paint_Entity::draw_dimension_text(Text& text,const Dimension& dim)
  //{
  ////  bool sel = dim.selected();
  ////  std::vector<Entity*> es;
  ////  dim.get_dim_show(es);
  ////  select(es,sel);
  ////  draw(es,*this,false);
  ////  destory(es);
  //}
  //void Paint_Entity::xor_draw_dimension_text(Text& text,const Dimension& dim)
  //{
  ////  bool sel = dim.selected();
  ////  std::vector<Entity*> es;
  ////  dim.get_dim_show(es);
  ////  select(es,sel);
  ////  draw(es,*this,true);
  ////  destory(es);
  //}

  //void Paint_Entity::draw_dimension_text(Text& text,const Dimension& dim)
  //{
  //	if(strcmp("",text.text())==0)
  //		return;
  //	draw_text(text);
  //	std::vector<Line*> textlines;
  //	Line textl1,textl2,textl3,textl4,textl5,textl6;
  //	textlines.push_back(&textl1);
  //	textlines.push_back(&textl2);
  //	textlines.push_back(&textl3);
  //	textlines.push_back(&textl4);
  //	textlines.push_back(&textl5);
  //	textlines.push_back(&textl6);
  //	int num = dim.get_text_line_show(text,textlines);
  //	//设置高亮显示
  //	bool sel = dim.selected();
  //	for(int i=0;i<num;++i){
  //		textlines[i]->selected(sel);
  //		draw_line(*textlines[i]);
  //	}
  //	RArc arcleft,arcright;
  //	std::vector<RArc*> arcs;
  //	arcs.push_back(&arcleft);
  //	arcs.push_back(&arcright);
  //	num = dim.get_text_arc_show(text,arcs);
  //	for(i=0;i<num;++i){
  //		arcs[i]->selected(sel);
  //		draw_arc(*arcs[i]);
  //	}
  //	Circle cir;
  //	std::vector<Circle*> cirs;
  //	cirs.push_back(&cir);
  //	num = dim.get_text_circle_show(text,cirs);
  //	for(i=0;i<num;++i){
  //		cirs[i]->selected(sel);
  //		draw_circle(*cirs[i]);
  //	}
  //}
  //void Paint_Entity::xor_draw_dimension_text(Text& text,const Dimension& dim)
  //{
  //	if(strcmp("",text.text())==0)
  //		return;
  //	xor_draw_text(text);
  //	std::vector<Line*> textlines;
  //	Line textl1,textl2,textl3,textl4,textl5,textl6;
  //	textlines.push_back(&textl1);
  //	textlines.push_back(&textl2);
  //	textlines.push_back(&textl3);
  //	textlines.push_back(&textl4);
  //	textlines.push_back(&textl5);
  //	textlines.push_back(&textl6);
  //	int num = dim.get_text_line_show(text,textlines);
  //	for(int i=0;i<num;++i)
  //		xor_draw_line(*textlines[i]);
  //	RArc arcleft,arcright;
  //	std::vector<RArc*> arcs;
  //	arcs.push_back(&arcleft);
  //	arcs.push_back(&arcright);
  //	num = dim.get_text_arc_show(text,arcs);
  //	for(i=0;i<num;++i)
  //		xor_draw_arc(*arcs[i]);
  //	Circle cir;
  //	std::vector<Circle*> cirs;
  //	cirs.push_back(&cir);
  //	num = dim.get_text_circle_show(text,cirs);
  //	for(i=0;i<num;++i)
  //		xor_draw_circle(*cirs[i]);
  //}

  //bet 2009.07.06
  //void Paint_Entity::draw_text_dim(const Text_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //  std::vector<Entity*> es;
  //  dim.get_dim_show(es);
  //  select(es,sel);
  //  draw(es,*this,false);
  //  destory(es);
  //}
  //void Paint_Entity::xor_draw_text_dim(const Text_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //  std::vector<Entity*> es;
  //  dim.get_dim_show(es);
  //  select(es,sel);
  //  draw(es,*this,true);
  //  destory(es);
  // }
  //ter 2009.07.06

  //void Paint_Entity::draw_text_dim(const Text_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //	//text
  //	Text text;
  //	dim.get_text_show(text);
  //	draw_dimension_text(text,dim);
  //#ifdef _DEBUG
  //	draw_rect(dim.box2d());
  //#endif
  //
  //}
  //void Paint_Entity::xor_draw_text_dim(const Text_Dimension& dim)
  //{
  //	bool sel = dim.selected();
  //	//text
  //	Text text;
  //	dim.get_text_show(text);
  ////	text.selected(sel);
  //	xor_draw_dimension_text(text,dim);
  //	
  //}

  //bet 2009.07.06
  //void Paint_Entity::draw_lead_dim(const Lead_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //  std::vector<Entity*> es;
  //  dim.get_dim_show(es);
  //  select(es,sel);
  //  draw(es,*this,false);
  //  destory(es);
  //}
  //
  //void Paint_Entity::xor_draw_lead_dim(const Lead_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //  std::vector<Entity*> es;
  //  dim.get_dim_show(es);
  //  select(es,sel);
  //  draw(es,*this,true);
  //  destory(es);
  //}
  //ter 2009.07.06


  //void Paint_Entity::draw_lead_dim(const Lead_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //	//dim line
  //	std::vector<Line*> dimlines;
  //	Line diml;
  //	dim.get_line_show(diml);
  //  diml.selected(sel);
  //	draw_line(diml);
  //	//text
  //	Text text;
  //	dim.get_text_show(text);
  //	draw_dimension_text(text,dim);
  //
  //#ifdef _DEBUG
  //	draw_rect(dim.box2d());
  //#endif
  //
  //}

  //void Paint_Entity::xor_draw_lead_dim(const Lead_Dimension& dim)
  //{
  //	bool sel = dim.selected();
  //	//dim line
  //	std::vector<Line*> dimlines;
  //	Line diml;
  //  dim.get_line_show(diml);
  //	xor_draw_line(diml);
  //	//text
  //	Text text;
  //	dim.get_text_show(text);
  ////	text.selected(sel);
  //	xor_draw_dimension_text(text,dim);
  //}

  //void Paint_Entity::draw_lead_dim(const Lead_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //	//dim line
  //	std::vector<Line*> dimlines;
  //	Line diml;
  //	dimlines.push_back(&diml);
  //	dim.get_line_show(dimlines);
  //	for(int i=0;i<dimlines.size();i++)
  //		dimlines[i]->selected(sel);
  //	draw_line(diml);
  //	//text
  //	Text text;
  //	dim.get_text_show(text);
  //	draw_dimension_text(text,dim);
  //
  //#ifdef _DEBUG
  //	draw_rect(dim.box2d());
  //#endif
  //
  //}
  //
  //void Paint_Entity::xor_draw_lead_dim(const Lead_Dimension& dim)
  //{
  //	bool sel = dim.selected();
  //	//dim line
  //	std::vector<Line*> dimlines;
  //	Line diml;
  //	dimlines.push_back(&diml);
  //	dim.get_line_show(dimlines);
  //	for(int i=0;i<dimlines.size();i++)
  //		dimlines[i]->selected(sel);
  //	xor_draw_line(diml);
  //	//text
  //	Text text;
  //	dim.get_text_show(text);
  ////	text.selected(sel);
  //	xor_draw_dimension_text(text,dim);
  //}

  //bet 2009.07.06
  //void Paint_Entity::draw_three_pt_dim(const Three_Pt_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //  //dim line
  //  std::vector<Line*> dimlines;
  //  Line startl,endl,diml;
  //  startl.selected(sel);
  //  endl.selected(sel);
  //  diml.selected(sel);
  //  dimlines.push_back(&startl);
  //  dimlines.push_back(&endl);
  //  dimlines.push_back(&diml);
  //  dim.get_dim_lines_show(dimlines);
  //  draw_line(startl);
  //  draw_line(endl);
  //  draw_line(diml);
  //  //text
  //  Text text;
  //  dim.get_text_show(text);
  //  draw_dimension_text(text,dim);
  //  //arrow
  //  Line a1,a2,a3,a4;
  //  a1.selected(sel);
  //  a2.selected(sel);
  //  a3.selected(sel);
  //  a4.selected(sel);
  //  dimlines.clear();
  //  dimlines.push_back(&a1);
  //  dimlines.push_back(&a2);
  //  dimlines.push_back(&a3);
  //  dimlines.push_back(&a4);
  //  int i=0;
  //  int num = dim.get_arrow_line_show(diml,dimlines);
  //  for(i=0;i<num;++i)
  //    draw_line(*dimlines[i]);
  //  Circle cir1,cir2;
  //  std::vector<Circle*> cirs;
  //  cirs.push_back(&cir1);
  //  cirs.push_back(&cir2);
  //  num = dim.get_arrow_circle_show(diml,cirs);
  //  for(i=0;i<num;++i)
  //    draw_solid_circle(*cirs[i]);
  //  
  //#ifdef _DEBUG
  //  draw_rect(dim.box2d());
  //#endif
  //}
  //
  //void Paint_Entity::xor_draw_three_pt_dim(const Three_Pt_Dimension& dim)
  //{
  //  bool sel = dim.selected();
  //  //dim line
  //  std::vector<Line*> dimlines;
  //  Line startl,endl,diml;
  //  startl.selected(sel);
  //  endl.selected(sel);
  //  diml.selected(sel);
  //  dimlines.push_back(&startl);
  //  dimlines.push_back(&endl);
  //  dimlines.push_back(&diml);
  //  dim.get_dim_lines_show(dimlines);
  //  xor_draw_line(startl);
  //  xor_draw_line(endl);
  //  xor_draw_line(diml);
  //  //text
  //  Text text;
  //  dim.get_text_show(text);
  //  xor_draw_dimension_text(text,dim);
  //  //arrow
  //  Line a1,a2,a3,a4;
  //  a1.selected(sel);
  //  a2.selected(sel);
  //  a3.selected(sel);
  //  a4.selected(sel);
  //  dimlines.clear();
  //  dimlines.push_back(&a1);
  //  dimlines.push_back(&a2);
  //  dimlines.push_back(&a3);
  //  dimlines.push_back(&a4);
  //  int i=0;
  //  int num = dim.get_arrow_line_show(diml,dimlines);
  //  for(i=0;i<num;++i)
  //    xor_draw_line(*dimlines[i]);
  //  Circle cir1,cir2;
  //  std::vector<Circle*> cirs;
  //  cirs.push_back(&cir1);
  //  cirs.push_back(&cir2);
  //  num = dim.get_arrow_circle_show(diml,cirs);
  //  for(i=0;i<num;++i)
  //    xor_draw_solid_circle(*cirs[i]);
  //}
  //ter 2009.07.06

//void Paint_Entity::draw_ln_din_block(const Ln_Dim_Block& block)
//{
//  Ln_Dim * dim = NULL;
//	std::vector<Ln_Dim*>::const_iterator iter;
//  for(iter=list_.begin();iter!=list_.end();++iter){
//    dim = *iter;
//    if(!dim){
//      continue;
//    }
//		dim->draw(out);
//#ifdef _DEBUG
//    Line oex, sex, eex, odm, edm;
//    dim->get_o_lines(oex,odm);
//    dim->get_s_lines(sex,eex,edm);
//#endif
//  }
//}

//bet 2009.07.06
//void Paint_Entity::draw_ln_dim(const Ln_Dim& dim)
//{
//  //Ln_Dim& dim = const_cast<Ln_Dim&>(dim_c);
//  bool sel = dim.selected();
//  std::vector<Entity*> es;
//  dim.get_dim_show(es);
//  select(es,sel);
//  draw(es,*this,false);
//  destory(es);
//
////#ifdef _DEBUG
////  Point txtpt = dim.text_position();
////  Line oexln, odmln;
////  dim.get_o_lines(oexln,odmln);
////
////  Line ln;
////  ln.setdata(txtpt, odmln.middle());
////  draw_line(ln);
////#endif
//
//
//
////  int i=0;
////  for(i=0; i<es.size(); i++){
////    es[i]->draw(*this);
////  }
//
////  bool sel = dim.selected();
////	//dim line
////	std::vector<Line*> dimlines;
////	Line startl,endl,diml,diml2;
////  //
////  startl.selected(sel);
////  endl.selected(sel);
////  diml.selected(sel);
////  diml2.selected(sel);
////  //
////	dimlines.push_back(&startl);
////	dimlines.push_back(&endl);
////	dimlines.push_back(&diml);
////	dimlines.push_back(&diml2);
////	dim.get_dim_lines_show(dimlines);
////	if(dim.show0()){
////		draw_line(startl);
////		draw_line(endl);
////	}
////	draw_line(diml);
////	draw_line(diml2);
////	//text
////	Text text;
////	dim.get_text_show(text);
////	if(dim.show0()){
////		draw_dimension_text(text,dim);
////	}
////	dim.get_text2_show(text);
////	draw_dimension_text(text,dim);
////	if(strcmp("",dim.dim_text3())!=0){
////		dim.get_text3_show(text);
////		draw_dimension_text(text,dim);
////	}
////	//arrow
////	int i=0;
////	int num = dim.get_o_arrow_line_show(dimlines);
////	if(dim.show0()){
////		for(i=0;i<num;++i)
////			draw_line(*dimlines[i]);
////	}
////	num = dim.get_e_arrow_line_show(dimlines);
////	for(i=0;i<num;++i)
////		draw_line(*dimlines[i]);
////	Circle cir;
////	std::vector<Circle*> cirs;
////	cirs.push_back(&cir);
////	num = dim.get_o_arrow_circle_show(cirs);
////	if(dim.show0()){
////		for(i=0;i<num;++i)
////			draw_solid_circle(*cirs[i]);
////	}
////	num = dim.get_e_arrow_circle_show(cirs);
////	for(i=0;i<num;++i)
////		draw_solid_circle(*cirs[i]);
//
//  
////  ////裁决start/end show
////  bool show0 = dim.start() == dim.end();
//////  if(dim.start() == dim.end()){
//////    dim.start_show(true);
//////    dim.end_show(false);
//////  }else{
//////    dim.start_show(false);
//////    dim.end_show(true);
//////  }
////
////  bool sel = dim.selected();
////  //dim line
////  std::vector<Line*> dimlines;
////  Line startl,endl,diml,diml2;
////  //
////  startl.selected(sel);
////  endl.selected(sel);
////  diml.selected(sel);
////  diml2.selected(sel);
////  //
////  dimlines.push_back(&startl);
////  dimlines.push_back(&endl);
////  dimlines.push_back(&diml);
////  dimlines.push_back(&diml2);
////  dim.get_dim_lines_show(dimlines);
//////  if(dim.start_show()){
////  if(show0){
////    draw_line(startl);
////    draw_line(endl);
////  }else{
////  ///////////////////
//////  if(dim.end_show()){
////    draw_line(diml);
////    draw_line(diml2);
////  }
////  //text
////  Text text;
//////  dim.get_text_show(text);
//////  if(dim.start_show()){
////  if(show0){
////    dim.get_text_show(text);
////    draw_dimension_text(text,dim);
////  }else{
////  dim.get_text2_show(text);
////  ///////////////////
////  //if(dim.end_show()){
////    draw_dimension_text(text,dim);
////  }
////  if(strcmp("",dim.dim_text3())!=0){
////    dim.get_text3_show(text);
////    draw_dimension_text(text,dim);
////  }
////  //arrow
////  int i=0;
////  int num = dim.get_start_arrow_line_show(dimlines);
//////  if(dim.start_show()){
////  if(show0){
////    for(i=0;i<num;++i)
////      draw_line(*dimlines[i]);
////  }else{
////    num = dim.get_end_arrow_line_show(dimlines);
////  ///////////////////
//////  if(dim.end_show()){
////    for(i=0;i<num;++i)
////      draw_line(*dimlines[i]);
////  }
////  Circle cir;
////  std::vector<Circle*> cirs;
////  cirs.push_back(&cir);
////  num = dim.get_start_arrow_circle_show(cirs);
//////  if(dim.start_show()){
////  if(show0){
////    for(i=0;i<num;++i)
////      draw_solid_circle(*cirs[i]);
////  }else{
////    num = dim.get_end_arrow_circle_show(cirs);
////    ///////////////////
////    //if(dim.end_show()){
////    for(i=0;i<num;++i)
////      draw_solid_circle(*cirs[i]);
////  }
//////#ifdef _DEBUG
//////  draw_rect(dim.box2d());
//////#endif
////  
//}
//void Paint_Entity::xor_draw_ln_dim(const Ln_Dim& dim)
//{
//  //Ln_Dim& dim = const_cast<Ln_Dim&>(dim_c);
//  bool sel = dim.selected();
//  std::vector<Entity*> es;
//  dim.get_dim_show(es);
//  select(es,sel);
//  draw(es,*this,true);
//  destory(es);
//
//  
////  bool sel = dim.selected();
////	//dim line
////	std::vector<Line*> dimlines;
////	Line startl,endl,diml,diml2;
////  //
////  startl.selected(sel);
////  endl.selected(sel);
////  diml.selected(sel);
////  diml2.selected(sel);
////  //
////	dimlines.push_back(&startl);
////	dimlines.push_back(&endl);
////	dimlines.push_back(&diml);
////	dimlines.push_back(&diml2);
////	dim.get_dim_lines_show(dimlines);
////	if(dim.show0()){
////		xor_draw_line(startl);
////		xor_draw_line(endl);
////	}
////	xor_draw_line(diml);
////	xor_draw_line(diml2);
////	//text
////	Text text;
////	dim.get_text_show(text);
////	if(dim.show0()){
////		xor_draw_dimension_text(text,dim);
////	}
////	dim.get_text2_show(text);
////	xor_draw_dimension_text(text,dim);
////	if(strcmp("",dim.dim_text3())!=0){
////		dim.get_text3_show(text);
////		xor_draw_dimension_text(text,dim);
////	}
////	//arrow
////	int i=0;
////	int num = dim.get_o_arrow_line_show(dimlines);
////	if(dim.show0()){
////		for(i=0;i<num;++i)
////			xor_draw_line(*dimlines[i]);
////	}
////	num = dim.get_e_arrow_line_show(dimlines);
////	for(i=0;i<num;++i)
////		xor_draw_line(*dimlines[i]);
////	Circle cir;
////	std::vector<Circle*> cirs;
////	cirs.push_back(&cir);
////	num = dim.get_o_arrow_circle_show(cirs);
////	if(dim.show0()){
////		for(i=0;i<num;++i)
////			xor_draw_solid_circle(*cirs[i]);
////	}
////	num = dim.get_e_arrow_circle_show(cirs);
////	for(i=0;i<num;++i)
////		xor_draw_solid_circle(*cirs[i]);
//}
//void Paint_Entity::ln_dim_paint(const Ln_Dim& dim, bool xor)
//{}

//void Paint_Entity::draw_line_dim(const Line_Dim& dim)
//{
//  ////裁决start/end show
//  bool show0 = dim.start() == dim.end();
////  if(dim.start() == dim.end()){
////    dim.start_show(true);
////    dim.end_show(false);
////  }else{
////    dim.start_show(false);
////    dim.end_show(true);
////  }
//
//  bool sel = dim.selected();
//  //dim line
//  std::vector<Line*> dimlines;
//  Line startl,endl,diml,diml2;
//  //
//  startl.selected(sel);
//  endl.selected(sel);
//  diml.selected(sel);
//  diml2.selected(sel);
//  //
//  dimlines.push_back(&startl);
//  dimlines.push_back(&endl);
//  dimlines.push_back(&diml);
//  dimlines.push_back(&diml2);
//  dim.get_dim_lines_show(dimlines);
////  if(dim.start_show()){
//  if(show0){
//    draw_line(startl);
//    draw_line(endl);
//  }else{
//  ///////////////////
////  if(dim.end_show()){
//    draw_line(diml);
//    draw_line(diml2);
//  }
//  //text
//  Text text;
////  dim.get_text_show(text);
////  if(dim.start_show()){
//  if(show0){
//    dim.get_text_show(text);
//    draw_dimension_text(text,dim);
//  }else{
//  dim.get_text2_show(text);
//  ///////////////////
//  //if(dim.end_show()){
//    draw_dimension_text(text,dim);
//  }
//  if(strcmp("",dim.dim_text3())!=0){
//    dim.get_text3_show(text);
//    draw_dimension_text(text,dim);
//  }
//  //arrow
//  int i=0;
//  int num = dim.get_start_arrow_line_show(dimlines);
////  if(dim.start_show()){
//  if(show0){
//    for(i=0;i<num;++i)
//      draw_line(*dimlines[i]);
//  }else{
//    num = dim.get_end_arrow_line_show(dimlines);
//  ///////////////////
////  if(dim.end_show()){
//    for(i=0;i<num;++i)
//      draw_line(*dimlines[i]);
//  }
//  Circle cir;
//  std::vector<Circle*> cirs;
//  cirs.push_back(&cir);
//  num = dim.get_start_arrow_circle_show(cirs);
////  if(dim.start_show()){
//  if(show0){
//    for(i=0;i<num;++i)
//      draw_solid_circle(*cirs[i]);
//  }else{
//    num = dim.get_end_arrow_circle_show(cirs);
//    ///////////////////
//    //if(dim.end_show()){
//    for(i=0;i<num;++i)
//      draw_solid_circle(*cirs[i]);
//  }
//#ifdef _DEBUG
//  draw_rect(dim.box2d());
//#endif
//  
//}
//void Paint_Entity::xor_draw_line_dim(const Line_Dim& dim)
//{
//  bool sel = dim.selected();
//	//dim line
//	std::vector<Line*> dimlines;
//	Line startl,endl,diml,diml2;
//  //
//  startl.selected(sel);
//  endl.selected(sel);
//  diml.selected(sel);
//  diml2.selected(sel);
//  //
//	dimlines.push_back(&startl);
//	dimlines.push_back(&endl);
//	dimlines.push_back(&diml);
//	dimlines.push_back(&diml2);
//	dim.get_dim_lines_show(dimlines);
//	if(dim.show0()){
//		xor_draw_line(startl);
//		xor_draw_line(endl);
//	}
//	xor_draw_line(diml);
//	xor_draw_line(diml2);
//	//text
//	Text text;
//	dim.get_text_show(text);
//	if(dim.show0()){
//		xor_draw_dimension_text(text,dim);
//	}
//	dim.get_text2_show(text);
//	xor_draw_dimension_text(text,dim);
//	if(strcmp("",dim.dim_text3())!=0){
//		dim.get_text3_show(text);
//		xor_draw_dimension_text(text,dim);
//	}
//	//arrow
//	int i=0;
//	int num = dim.get_start_arrow_line_show(dimlines);
//	if(dim.show0()){
//		for(i=0;i<num;++i)
//			xor_draw_line(*dimlines[i]);
//	}
//	num = dim.get_end_arrow_line_show(dimlines);
//	for(i=0;i<num;++i)
//		xor_draw_line(*dimlines[i]);
//	Circle cir;
//	std::vector<Circle*> cirs;
//	cirs.push_back(&cir);
//	num = dim.get_start_arrow_circle_show(cirs);
//	if(dim.show0()){
//		for(i=0;i<num;++i)
//			xor_draw_solid_circle(*cirs[i]);
//	}
//	num = dim.get_end_arrow_circle_show(cirs);
//	for(i=0;i<num;++i)
//		xor_draw_solid_circle(*cirs[i]);
//}


//ter 2009.07.06
//void Paint_Entity::draw_angle_dim(const Angle_Dimension& dim)
//{
//  bool sel = dim.selected();
//  std::vector<Entity*> es;
//  dim.get_dim_show(es);
//  select(es,sel);
//  draw(es,*this,false);
//  destory(es);
//}
//void Paint_Entity::xor_draw_angle_dim(const Angle_Dimension& dim)
//{
//  bool sel = dim.selected();
//  std::vector<Entity*> es;
//  dim.get_dim_show(es);
//  select(es,sel);
//  draw(es,*this,true);
//  destory(es);
//}
//bet 2009.07.06

//void Paint_Entity::draw_angle_dim(const Angle_Dimension& dim)
//{
//  //dim line
//  Line startl,endl,extendl;
//  RArc diml;
//  dim.get_dim_lines_show(startl,endl,extendl,diml);
//  startl  .selected(dim.selected());
//  endl    .selected(dim.selected());
//  extendl .selected(dim.selected());
//  diml    .selected(dim.selected());
//  draw_line(startl);
//  draw_line(endl);
//  draw_line(extendl);
//  draw_arc(diml);
//  //text
//  Text text;
//  dim.get_text_show(text);
//  draw_dimension_text(text,dim);
//  //arrow
//  std::vector<Line*> dimlines;
//  dimlines.push_back(&startl);
//  dimlines.push_back(&endl);
//  int i=0;
//  int num = dim.get_start_arrow_line_show(dimlines);
//  for(i=0;i<num;++i)
//    draw_line(*dimlines[i]);
//  num = dim.get_end_arrow_line_show(dimlines);
//  for(i=0;i<num;++i){
//    dimlines[i]->selected(dim.selected());
//    draw_line(*dimlines[i]);
//  }
//  Circle cir;
//  std::vector<Circle*> cirs;
//  cirs.push_back(&cir);
//  num = dim.get_start_arrow_circle_show(cirs);
//  for(i=0;i<num;++i)
//    draw_solid_circle(*cirs[i]);
//  num = dim.get_end_arrow_circle_show(cirs);
//  for(i=0;i<num;++i)
//    draw_solid_circle(*cirs[i]);
//#ifdef _DEBUG
//  draw_rect(dim.box2d());
//#endif
//}
//void Paint_Entity::xor_draw_angle_dim(const Angle_Dimension& dim)
//{
//  //dim line
//  Line startl,endl,extendl;
//  RArc diml;
//  dim.get_dim_lines_show(startl,endl,extendl,diml);
//  startl  .selected(dim.selected());
//  endl    .selected(dim.selected());
//  extendl .selected(dim.selected());
//  diml    .selected(dim.selected());
//
//  if(dim.start() != dim.end()){
//    xor_draw_line(startl);
//  }
//  xor_draw_line(endl);
//  xor_draw_line(extendl);
//  xor_draw_arc(diml);
//  //text
//  Text text;
//  dim.get_text_show(text);
//  xor_draw_dimension_text(text,dim);
//  //arrow
//  std::vector<Line*> dimlines;
//  dimlines.push_back(&startl);
//  dimlines.push_back(&endl);
//  int i=0;
//  int num = dim.get_start_arrow_line_show(dimlines);
//  for(i=0;i<num;++i)
//    xor_draw_line(*dimlines[i]);
//  num = dim.get_end_arrow_line_show(dimlines);
//  for(i=0;i<num;++i){
//    dimlines[i]->selected(dim.selected());
//    xor_draw_line(*dimlines[i]);
//  }
//  Circle cir;
//  std::vector<Circle*> cirs;
//  cirs.push_back(&cir);
//  num = dim.get_start_arrow_circle_show(cirs);
//  for(i=0;i<num;++i)
//    xor_draw_solid_circle(*cirs[i]);
//  num = dim.get_end_arrow_circle_show(cirs);
//  for(i=0;i<num;++i)
//    xor_draw_solid_circle(*cirs[i]);
//}

//bet 2009.07.06
//void Paint_Entity::draw_radius_dim(const Radius_Dimension& dim)
//{
//  bool sel = dim.selected();
//  std::vector<Entity*> es;
//  dim.get_dim_show(es);
//  select(es,sel);
//  draw(es,*this,false);
//  destory(es);
//}
//void Paint_Entity::xor_draw_radius_dim(const Radius_Dimension& dim)
//{
//  bool sel = dim.selected();
//  std::vector<Entity*> es;
//  dim.get_dim_show(es);
//  select(es,sel);
//  draw(es,*this,true);
//  destory(es);
//}
//ter 2009.07.06

//void Paint_Entity::draw_radius_dim(const Radius_Dimension& dim)
//{
//  bool sel = dim.selected();
//  //dim line
//  Line startl,endl;
//  //
//  startl.selected(sel);
//  endl.selected(sel);
//  //
//  dim.get_line_show(startl);
//  draw_line(startl);
//  //text
//  Text text;
//  dim.get_text_show(text);
//  draw_dimension_text(text,dim);
//  //arrow
//  std::vector<Line*> dimlines;
//  dimlines.push_back(&startl);
//  dimlines.push_back(&endl);
//  int i=0;
//  int num = dim.get_arrow_line_show(dimlines);
//  for(i=0;i<num;++i)
//    draw_line(*dimlines[i]);
//#ifdef _DEBUG
//  draw_rect(dim.box2d());
//#endif
//}
//void Paint_Entity::xor_draw_radius_dim(const Radius_Dimension& dim)
//{
//  bool sel = dim.selected();
//  RArc arc=dim.arc();
//  arc.selected(sel);
//  xor_draw_arc(arc);
//
//  //dim line
//  Line startl,endl;
//  startl.selected(sel);
//  //
//  endl.selected(sel);
//  dim.get_line_show(startl);
//  //
//  xor_draw_line(startl);
//  //text
//  Text text;
//  dim.get_text_show(text);
//  xor_draw_dimension_text(text,dim);
//  //arrow
//  std::vector<Line*> dimlines;
//  dimlines.push_back(&startl);
//  dimlines.push_back(&endl);
//  int i=0;
//  int num = dim.get_arrow_line_show(dimlines);
//  for(i=0;i<num;++i)
//    xor_draw_line(*dimlines[i]);
//}

void Paint_Entity::draw_cut_section(const Cut_Section& cut)
{
 // bool sel = dim.selected();
	Line line[8];
	Text text[2];
	cut.get_denote_show(line,text);
	int i=0;
	for(;i<8;++i){
	//	line[i]->selected(sel);
		draw_line(line[i]);
	}
	for(i=0;i<2;++i)
		draw_text(text[i]);

}
void Paint_Entity::xor_draw_cut_section(const Cut_Section& cut)
{
	Line line[8];
	Text text[2];
	cut.get_denote_show(line,text);
	int i=0;
	for(;i<8;++i)
		xor_draw_line(line[i]);
	for(i=0;i<2;++i)
		xor_draw_text(text[i]);
}


}//namespace
