// Create_Dim_Text_Dimension.cpp: implementation of the Create_Dim_Text_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Create_Dim_Text_Dimension.h"

#include "Scene_d.h"
#include "Line.h"
#include "Circle.h"
#include "Paint_Entity.h"
#include "Painter.h"
#include "myalgorithm.h"
#include "Text_Dimension.h"

#include "Block.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Create_Dim_Text_Dimension::Create_Dim_Text_Dimension(Scene& scene)
:Create_Entity(scene)
MCT_INIT2("Create_Dim_Text_Dimension")
{
  create_text_=true;
	pText_dim_ = NULL;
	group_ents_ = NULL;;
}

Create_Dim_Text_Dimension::~Create_Dim_Text_Dimension()
{

}

void Create_Dim_Text_Dimension::mouse_move_p(UINT nFlags, const Point& pt)
{
	switch(step_)
	{
	case 0:
		xor_draw();
		begin_ = pt;
		xor_draw();
		break;
	default:
		break;
	}
}
void Create_Dim_Text_Dimension::left_button_down_p(UINT nFlags, const Point& pt)
{
	++step_;
	Snap* sanp = NULL;
	switch(step_)
	{
	case 1:
		begin_ = pt;
		//判断是否在块内
//		scene_.database()->select_block(p_block_,begin_);
		sanp = scene_.get_snap_flag();		
//		if(!sanp->anypoint()){
			if(!scene_.database()->select_group(group_ents_,begin_))
				step_ =0;
//		}
		if(step_ !=0)
			scene_.info_to_command_line("input text: ",true);
		break;
	default:
		break;
	}
}
void Create_Dim_Text_Dimension::right_button_up_p(UINT nFlags, const Point& pt)
{
//	scene_.idle_command(this);
	scene_.idle_command();
	scene_.create_Dim_Text_Dimension();
}

void Create_Dim_Text_Dimension::xor_draw_p(Draw_Entity& paint)
{
	Text_Dimension dim;
	char ch_temp[100];
	const char* ch = dim_txt_.c_str();
	strcpy(ch_temp,ch);   
	dim.dim_text(ch);
	dim.text_position(begin_);
	dim.xor_draw(paint);
}
void Create_Dim_Text_Dimension::add_txt(char* txt)
{
	pText_dim_ = Text_Dimension::create_me();
	pText_dim_->dim_text(txt);
	pText_dim_->dim_style_name("DimText");
	pText_dim_->text_position(begin_);
	Entity_ID id;
	//添加手动标注和加实体方法
	pText_dim_->layer_name("l_manual_dim");

	insert_to_db(pText_dim_);

/*
	pText_dim_->post2db(*scene_.database(),id);
	//添加到块
	if(group_ents_)
		group_ents_->push_back_id(id);
*/
}
void Create_Dim_Text_Dimension::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(step_)
	{
	case 1:
		if(vk_.esc()){
			scene_.info_to_command_line("exit dim",true);
			//scene_.idle_command(this);
			scene_.idle_command();
		}
		if(vk_.enter()){
			char ch[100];
			if(get_commmand_line_string(ch)){
			scene_.info_to_command_line("",true);
			dim_txt_ = ch;
			if(strcmp(ch,"")==0){
				scene_.info_to_command_line("please input txt:",true);
				scene_.info_to_command_line("",true);
			}
			else
				add_txt(ch);
				//scene_.idle_command(this);
				scene_.idle_command();
				scene_.invalidate();
				cmd_start();
			}
		}
		break;
	default:
		break;
	}
}
bool Create_Dim_Text_Dimension::execute_p()
{
	Entity_ID id;
	if(pText_dim_ != NULL)
		pText_dim_->post2db(*scene_.database(),id);
	scene_.invalidate();
	return true;
}
bool Create_Dim_Text_Dimension::unexecute_p()
{
	if(pText_dim_ != NULL)
		scene_.database()->remove_entity(pText_dim_->entity_id());
	scene_.invalidate();
	return true;
}
void Create_Dim_Text_Dimension::cmd_start()
{
	scene_.attach_command(new Create_Dim_Text_Dimension(scene_));
}
//
}
