// Scene.cpp: implementation of the Scene class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Scene_d.h"
#include "Point.h"
#include "Database.h"
#include "Create_Entity.h"
#include "Idle_Command.h"
#include "Matrix_d.h"
#include "Paint_Entity.h"
#include "Entity.h"
#include "Scene_Wnd.h"
#include "myalgorithm.h"
#include "Painter_Windows.h"
#include "Create_Text.h"
//#include "Entity_Move.h"
//#include "Create_Circle.h"
//#include "Create_Arc.h"
#include "Line.h"

//#include "Create_Break.h"
//#include "Create_Copy.h"
//#include "Create_Delete.h"
//#include "Create_Extend.h"
//#include "Create_Mirror.h"
//#include "Create_Rotate.h"
//#include "Create_Scale.h"
//#include "Create_Trim.h"
//#include "Create_Cloud_Line.h"
#include "Create_Text.h"
#include "Create_Dim_Lead_Dimension.h"
#include "Create_Dim_Text_Dimension.h"
#include "Create_Dim_Axis_Dimension.h"

#include "Create_Command.h"

//#include "Edit_Line.h"
//#include "Edit_Circle.h"
//#include "Edit_Arc.h"

//#include "Edit_Dim_Three_Pt.h"
//#include "Edit_Dim_Three_Pt_Block.h"
//#include "Edit_Dim_Angle.h"
//#include "Edit_Dim_Four_Pt.h"
//#include "Edit_Dim_Lead.h"
//#include "Edit_Dim_Radius.h"
//#include "Edit_Dim_Text.h"
#include "Edit_Rectentity.h"
#include "Edit_Cut_Section.h"
#include "Create_Rect.h"
//#include "Create_Block.h"
//#include "Edit_Dim_Four_Pt_Block.h"
//#include "Edit_Dim_Lead_Block.h"

#include "Edit_Rectentity.h"
//#include "Edit_Cloud_Line.h"
#include "Create_Rect.h"


#include "Edit_Entity_Property.h"

#include "Command_Line.h"
#include <cassert>
#include "Command_Line_In.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


namespace dlhml{
Scene::Scene()
{
	database_.reset(Database::create_me());
	Entity::set_database(database_.get());
	command_line_.reset(new Command_Line_In());
	edit_entity_.reset(new Edit_Entity_Property(*this));
	//idle_command(NULL);
  //cmd_list_.set_idle(idle);
  cmd_list_.set_idle(new Idle_Command(*this));
}

void Scene::set_idle(Idle_Command* idle)
{
  cmd_list_.set_idle(idle);
}

Idle_Command* Scene::get_idle()
{
  return cmd_list_.get_idle();
}

Scene::~Scene()
{
}
Point Scene::get_current_center(const Point& screen_center) const
{
	return paper_.get_current_center(screen_center);
}
void Scene::undo()
{
  get_idle()->ok();
	cmd_list_.undo();
}
void Scene::redo()
{
  get_idle()->ok();
	cmd_list_.redo();
}
bool Scene::can_undo()
{
	return cmd_list_.can_undo();
}
bool Scene::can_redo()
{
	return cmd_list_.can_redo();
}
void Scene::attach_command(Create_Entity* cmd)
{
	if(cmd){
		cmd_list_.add_cmd(cmd);
	}
}
//void Scene::idle_command(Create_Entity* ce) 
//{
//  if(ce){
//    cmd_list_.add_cmd(ce);
//  }
//  cmd_list_.add_cmd(NULL);
//} 
void Scene::idle_command() 
{
  cmd_list_.add_cmd(NULL);
} 
void Scene::create_entity(Create_Entity* ce) 
{
	attach_command(ce);
} 

void Scene::make_block()
{
//  cmd_list_.current()->add_group();
  cmd_list_.current()->make_block();


//  Line*symbol = Line::create_me();
//  symbol->setdata(Point(0,0),Point(100,100));
//  cmd_list_.current()->insert(symbol, 100);
}
void Scene::split_block()
{
  cmd_list_.current()->split_block();
}
void Scene::set_focus()
{
  cmd_list_.current()->set_focus();
}

//void Scene::create_line() 
//{
//  Line ln;
//  cmd_list_.add_cmd(new Create_Command(*this, &ln));
//} 
//void Scene::create_rectentity()
//{
//	cmd_list_.add_cmd(new Create_Rect(*this));
//}
void Scene::edit_rectentity(Entity& rectentity)
{
//	cmd_list_.add_cmd(new Edit_Rectentity(*this,*((Rectentity*)(&rectentity))));
} 
//  void Scene::create_circle() 
//  {  
//    cmd_list_.add_cmd(new Create_Circle(*this));
//  } 
//  void Scene::create_arc()
//  {
//	  cmd_list_.add_cmd(new Create_Arc(*this));
//  }
  void Scene::edit_text(Entity& text)
  {
  }
//  void Scene::create_cloud_line()
//  {
//	  cmd_list_.add_cmd(new Create_Cloud_Line(*this));
//  }
void Scene::create_copy()
{
  cmd_list_.current()->copy_cad();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Copy(*this));
}
void Scene::entity_move()
{
  cmd_list_.current()->move_cad();
//  cmd_list_.current()->vmove_line();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Move(*this));
}
void Scene::create_rotate()
{
  cmd_list_.current()->rotate_cad();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Rotate(*this));
}
void Scene::create_scale()
{
  cmd_list_.current()->scale_cad();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Scale(*this));
}
void Scene::create_mirror()
{
  cmd_list_.current()->mirror_cad();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Mirror(*this));
}
void Scene::vmove_line()
{
  cmd_list_.current()->vmove_line();
}
void Scene::offset_cad()
{
  cmd_list_.current()->offset_cad();
}
void Scene::strech_cad()
{
  cmd_list_.current()->strech_cad();
}
void Scene::add_group()
{
  cmd_list_.current()->add_group();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Mirror(*this));
}
void Scene::copy_joint_cad()
{
  cmd_list_.current()->copy_joint_cad();
}
void Scene::create_break()
{
  cmd_list_.current()->break_cad();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Break(*this));
}
void Scene::create_delete()
{
  cmd_list_.current()->del();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Delete(*this));
}
void Scene::create_extend()
{
  cmd_list_.current()->extend_cad();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Extend(*this));
}
void Scene::create_trim()
{
  cmd_list_.current()->trim_cad();
//	get_idle()->clear_xor();
//	cmd_list_.add_cmd(new Entity_Trim(*this));
}
void Scene::add_dim_cad()
{
  cmd_list_.current()->add_dim_cad();
}
void Scene::del_dim_cad()
{
  cmd_list_.current()->del_dim_cad();
}
void Scene::re0_dim_cad()
{
  cmd_list_.current()->re0_dim_cad();
}
void Scene::layout_dim_base_cad()
{
  cmd_list_.current()->layout_dim_base_cad();
}
void Scene::layout_dim_line_cad()
{
  cmd_list_.current()->layout_dim_line_cad();
}
void Scene::move_dim_line_cad()
{
  cmd_list_.current()->move_dim_line_cad();
}



void Scene::create_text(LPCTSTR cont,int height, int color_id)
{
	get_idle()->clear_xor();
	cmd_list_.add_cmd(new Create_Text(*this,cont, height, color_id));
}
void Scene::create_Dim_Lead_Dimension()
{
	cmd_list_.add_cmd(new Create_Dim_Lead_Dimension(*this));
}
void Scene::create_Dim_Text_Dimension()
{
	cmd_list_.add_cmd(new Create_Dim_Text_Dimension(*this));
}
void Scene::create_Dim_Axis_Dimension()
{
	cmd_list_.add_cmd(new Create_Dim_Axis_Dimension(*this));
}


Painter* Scene::get_painter() const
{
	return painter_.get();
}
void Scene::mouse_move(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->mouse_move(nFlags,pt);
}
void Scene::left_button_down(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->left_button_down(nFlags,pt);
}
void Scene::left_button_up(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->left_button_up(nFlags,pt);
}
void Scene::left_button_dblclk(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->left_button_dblclk(nFlags,pt);
}
void Scene::right_button_down(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->right_button_down(nFlags,pt);
}
void Scene::right_button_up(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->right_button_up(nFlags,pt);
}
void Scene::right_button_dblclk(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->right_button_dblclk(nFlags,pt);
}
void Scene::middle_button_down(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->middle_button_down(nFlags,pt);
}
void Scene::middle_button_up(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->middle_button_up(nFlags,pt);
}
void Scene::middle_button_dblclk(UINT nFlags, const Point& pt)
{
	cmd_list_.current()->middle_button_dblclk(nFlags,pt);
}
void Scene::mouse_wheel(UINT nFlags, short zDelta, const Point& pt)
{
	cmd_list_.current()->mouse_wheel(nFlags,zDelta,pt);
}
void Scene::key_down(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	cmd_list_.current()->key_down(nFlags,nRepCnt,nFlags);
}

void Scene::screen_to_world_point(Point& pt) const
{
	pt.transformby(screen_to_world());
}
void Scene::world_to_screen_point(Point& pt) const
{
	pt.transformby(world_to_screen());
}
void Scene::screen_to_world_rect(Rect& rect) const
{
	rect.transformby(screen_to_world());
}
void Scene::world_to_screen_rect(Rect& rect) const
{
	rect.transformby(world_to_screen());
}


void Scene::draw_scene()
{
	paint_->draw_all_entity();
	cmd_list_.current()->set_first_draw();
}
void Scene::invalidate()
{
	draw_scene();
//	window_->invalidate();
}
void Scene::invalidate_rect(RECT rc)
{
	window_->invalidate_rect(rc);
}
Rect Scene::client_rect()
{
	return window_->client_rect();
}
void Scene::attach_window(Scene_Wnd* window)
{
	window_.reset(window);
	painter_.reset(window_->get_painter());
	paint_.reset(new Paint_Entity(*this,*painter_.get()));
}
Scene_Wnd* Scene::get_window() const
{
	return window_.get();
}
void Scene::attach_edit_entity(Edit_Entity* edit)
{
	edit_entity_.reset(edit);
}
void Scene::attach_edit_entity_dlg(Edit_Entity* edit)
{
	edit_entity_dlg_.reset(edit);
}
void Scene::attach_command_line(Command_Line* command)
{
	command_line_.reset(command);
}
void Scene::set_vistor(Visitor* edit_dlg)
{
  edit_ent_dlg_ = edit_dlg;
}
Visitor* Scene::get_vistor()
{
  return edit_ent_dlg_;
}

void Scene::info_to_command_line(LPCTSTR info,bool update)
{
	assert(command_line_.get());
	command_line_->show_command(info,update);
}
bool Scene::get_command_line_point(Point& pt) const
{
	Float val1,val2;
	if(!command_line_->get_two_value(val1,val2))
		return false;
	pt.setdata(val1,val2);
	return true;
}
bool Scene::get_command_line_length(Float& len) const
{
	return command_line_->get_one_value(len);
}
int Scene::get_commmand_line_string(LPTSTR str) const
{
	return command_line_->get_string(str);
}
void Scene::coord_info_to_status(LPCTSTR info)
{
	assert(command_line_.get());
	command_line_->show_coord(info);
}

Create_Entity* Scene::current_cmd()
{
  return cmd_list_.current();
}
void Scene::selected_all(bool sel)
{
  database()->selected_all(sel);
}

void Scene::ok()
{
  cmd_list_.current()->ok();
}
void Scene::confirm()
{
  cmd_list_.current()->confirm();
}
void Scene::cancel()
{
  cmd_list_.current()->cancel();
}
void Scene::del()
{
  cmd_list_.current()->del();
}

void Scene::insert(Entity * symbol)
{
  cmd_list_.current()->insert(symbol);
}
void Scene::insert(const Point& pt, Entity * symbol)
{
  cmd_list_.current()->insert(pt,symbol);
}
void Scene::insert(Entity * symbol, int select_count)
{
  cmd_list_.current()->insert(symbol, select_count);
}
void Scene::insert(Entity * xor_it, const std::vector<Float>& dis, Entity * symbol, int side)
{
  cmd_list_.current()->insert(xor_it,dis,symbol,side);
}
//void Scene::insert(double w, double h)
//{
//  cmd_list_.current()->insert(w,h);
//}
//void Scene::insert(double w, double h, const Point& pt)
//{
//  cmd_list_.current()->insert(w,h,pt);
//}

void Scene::slope_line()
{
  cmd_list_.current()->slope_line();
}

//  void Scene::edit_dim_three_pt(Entity& threept)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Three_Pt(*this,*((Three_Pt_Dimension*)(&threept))));
//  }
//  void Scene::edit_dim_three_pt_block(Entity& threeptblock)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Three_Pt_Block(*this,
//		  *((Three_Pt_Dimension_Block*)(&threeptblock))));
//  }
//  void Scene::edit_dim_angle(Entity& angle)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Angle(*this,*((Angle_Dimension*)(&angle))));
//  }
//  void Scene::edit_dim_four_pt(Entity& fourpt)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Four_Pt(*this,*((Four_Pt_Dimension*)(&fourpt))));
//  }
//  void Scene::edit_dim_four_pt_block(Entity& fourptblock)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Four_Pt_Block(*this,
//		  *((Four_Pt_Dimension_Block*)(&fourptblock))));
//  }
//  void Scene::edit_dim_lead(Entity& lead)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Lead(*this,*((Lead_Dimension*)(&lead))));
//  }
//  void Scene::edit_dim_lead_block(Entity& leadblock)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Lead_Block(*this,*((Lead_Dimension_Block*)(&leadblock))));
//  }
//  void Scene::edit_dim_radius(Entity& radius)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Radius(*this,*((Radius_Dimension*)(&radius))));
//  }
//  void Scene::edit_dim_text(Entity& text)
//  {
//	  cmd_list_.add_cmd(new Edit_Dim_Text(*this,*((Text_Dimension*)(&text))));
//  }
  void Scene::edit_cut_section(Entity& cut_section)
  {
	  cmd_list_.add_cmd(new Edit_Cut_Section(*this,*((Cut_Section*)(&cut_section))));
  }



//namespace
}
