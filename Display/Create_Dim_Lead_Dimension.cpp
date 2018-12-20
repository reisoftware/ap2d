// Create_Dim_Lead_Dimension.cpp: implementation of the Create_Dim_Lead_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Create_Dim_Lead_Dimension.h"

#include "Scene_d.h"
#include "Line.h"
#include "Paint_Entity.h"
#include "Painter_Windows.h"

#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Block.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Create_Dim_Lead_Dimension::Create_Dim_Lead_Dimension(Scene& scene)
:Create_Entity(scene)
MCT_INIT2("Create_Dim_Lead_Dimension")
{
  create_text_=true;
	pLead_dim_ = NULL;
	group_ents_ = NULL;;
}
Create_Dim_Lead_Dimension::~Create_Dim_Lead_Dimension()
{
}
void Create_Dim_Lead_Dimension::mouse_move_p(UINT nFlags, const Point& pt)
{
	switch(step_)
	{
	case 0:
		begin_ = pt;
		get_snap_point(begin_);
		break;
	case 1:
		xor_draw();
		end_ = pt;
		get_ortho_point(begin_,end_);
		get_snap_point(end_);
		xor_draw();
		break;
	default:
		break;
	}
}
void Create_Dim_Lead_Dimension::left_button_down_p(UINT nFlags, const Point& pt)
{
	++step_;
	Snap* sanp = NULL;
	switch(step_)
	{
	case 1:
		begin_ = pt;
		get_snap_point(begin_);
		//判断是否在块内
		sanp = scene_.get_snap_flag();		
//		if(!sanp->anypoint()){
//			if(!scene_.database()->select_group(group_ents_,begin_))
//				step_ =0;
//		}
		end_ = begin_;
		break;
	case 2:
		end_ = pt;
		get_ortho_point(begin_,end_);
		get_snap_point(end_);
		scene_.info_to_command_line("input text: ",true);
		break;
	default:
		break;
	}
}
void Create_Dim_Lead_Dimension::right_button_up_p(UINT nFlags, const Point& pt)
{
	scene_.info_to_command_line("exit dim.",true);
	//scene_.idle_command(this);
	scene_.idle_command();
	scene_.create_Dim_Lead_Dimension();
}
void Create_Dim_Lead_Dimension::xor_draw_p(Draw_Entity& paint)
{
	Lead_Dimension dim;
	dim.start(begin_);
	dim.text_position(end_);
	dim.text_position(end_);

	char ch_temp[100];
	const char* ch = dim_txt_.c_str();
	strcpy(ch_temp,ch);   
	dim.dim_text(ch);
	dim.color(scene_.entity_color());
	dim.xor_draw(paint);
}
void Create_Dim_Lead_Dimension::add_dim(char* txt)
{
//	Lead_Dimension*	pDim = Lead_Dimension::create_me();
	pLead_dim_ = Lead_Dimension::create_me();
	pLead_dim_->start(begin_);
	pLead_dim_->text_position(end_);
  pLead_dim_->dim_style_val().text_pos(Dimension_Style::CENTER);
	pLead_dim_->dim_text(txt);
	pLead_dim_->color(scene_.entity_color());
	pLead_dim_->dim_style_name("DimLeadText");
	//添加手动标注和加实体方法
	pLead_dim_->layer_name("l_manual_dim");
	
  pLead_dim_->text_position(end_);
  pLead_dim_->align_point(Text::center_center);
	insert_to_db(pLead_dim_);
/*
	Entity_ID id;
	pLead_dim_->post2db(*scene_.database(),id);

	//添加到块
	if(group_ents_)
		group_ents_->push_back_id(id);
*/
}
void Create_Dim_Lead_Dimension::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(step_)
	{
	case 0:
		if(vk_.esc()){
			scene_.info_to_command_line("exit dim",true);
			//scene_.idle_command(this);
			scene_.idle_command();
		}
		break;
	case 2:
		if(vk_.esc()){
			xor_draw();
			scene_.info_to_command_line("exit dim",true);
			//scene_.idle_command(this);
			scene_.idle_command();
		}
		if(vk_.enter()){
			char ch[100];
			if(get_commmand_line_string(ch/*dim_txt_*/)){
			scene_.info_to_command_line("",true);
			dim_txt_ = ch;
			if(strcmp(ch,"")==0){
				scene_.info_to_command_line("please input txt:",true);
				scene_.info_to_command_line("",true);
			}
			else
				add_dim(ch);
				//scene_.idle_command(this);
				scene_.idle_command();
				scene_.invalidate();
				cmd_start();//新的命令开始
			}
		}
		break;
	default:
		break;
	}
}
bool Create_Dim_Lead_Dimension::execute_p()
{
	Entity_ID id;
	if(pLead_dim_ != NULL)
		pLead_dim_->post2db(*scene_.database(),id);
	scene_.invalidate();
	return true;
}
bool Create_Dim_Lead_Dimension::unexecute_p()
{
	if(pLead_dim_ != NULL)
		scene_.database()->remove_entity(pLead_dim_->entity_id());
	scene_.invalidate();
	return true;
}
void Create_Dim_Lead_Dimension::cmd_start()
{
	scene_.attach_command(new Create_Dim_Lead_Dimension(scene_));
}

}