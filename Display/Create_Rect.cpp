// Create_Rect.cpp: implementation of the Create_Rect class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Create_Rect.h"
/*
#include "Scene_d.h"
#include "Paint_Entity.h"
#include "Painter.h"
#include "myalgorithm.h"
#include "Normal.h"
#include "Database.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Create_Rect::Create_Rect(Scene& scene)
:Create_Entity(scene)
{
	prect_ = NULL;
	scene_.info_to_command_line("start point of rectangle : ",true);
}

Create_Rect::~Create_Rect()
{
}
void Create_Rect::close()
{
	delete this;
}
void Create_Rect::mouse_move_p(UINT nFlags, const Point& pt)
{
	switch(step_)
	{
	case 1:
		xor_draw();
		end_ = cur_ = pt;
		xor_draw();
		break;
	default:
		break;
	}
}
void Create_Rect::left_button_down_p(UINT nFlags, const Point& pt)
{
	switch(++step_)
	{
	case 1:
		begin_ = end_ = cur_ = pt;
		//判断是否在块内
		scene_.database()->select_group(group_ents_,begin_);
		scene_.info_to_command_line("end point of rectangle : ",true);
		break;
	case 2:
		end_ = cur_ = pt;
		addrect();
		scene_.idle_command();
		break;
	default:
		break;
	}
}
void Create_Rect::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(step_)
	{
	case 0:
		if(vk_.esc()){
			scene_.info_to_command_line("exit rectangle",true);
			scene_.idle_command();
		}
		if(vk_.enter()){
			if(get_command_line_point(begin_)){
				step_ = 1;
				scene_.info_to_command_line("",true);
				scene_.info_to_command_line("end point: ",true);
			}
		}
		break;
	case 1:
		if(vk_.esc()){
			xor_draw();
			scene_.info_to_command_line("exit rectangle",true);
			scene_.idle_command();
		}
		if(vk_.enter()){
			if(get_command_line_point(end_)){
				addrect();
				scene_.idle_command();
			}	
			scene_.info_to_command_line("",true);
	}
		break;
	default:
		break;
	}
}
void Create_Rect::xor_draw_p(Draw_Entity& paint)
{
	Rectentity recty;
	recty.color(scene_.entity_color());
	Rect rect;
	rect.setdata(begin_,cur_);
	recty.rect(rect);
	paint.xor_draw_rectentity(recty);
}
void Create_Rect::addrect() 
{ 
  Painter* painter = scene_.get_painter();
  Paint_Entity paint(scene_,*painter);
  xor_draw();
  
  prect_ = Rectentity::create_me();
  prect_->color(scene_.entity_color());
  Rect rect;
  rect.setdata(begin_,end_);
  prect_->rect(rect);
  
  prect_->layer_name(layer_manual_dim);
  prect_->post2db(*scene_.database(),id_);
  
  paint.xor_draw_rectentity(*prect_);
  paint.draw_rectentity(*prect_);
  //添加到块
  if(group_ents_)
    group_ents_->push_back_id(id_);
} 
bool Create_Rect::execute_p()
{	
	prect_->post2db(*scene_.database(),id_);
	scene_.invalidate();
	return true;
}
bool Create_Rect::unexecute_p()
{
	Entity* ent =0;
	scene_.database()->entity_from_id(ent,id_);
	prect_= (Rectentity *) ent;
	scene_.database()->remove_entity(id_);
	scene_.invalidate();
	return true;
}
}
*/

