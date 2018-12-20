// Edit_Cut_Section.cpp: implementation of the Edit_Cut_Section class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Edit_Cut_Section.h"
#include "Scene_d.h"

#include "Painter.h"
#include "Paint_Entity.h"
#include "Rect.h"
#include "Database.h"
#include "Cut_Section.h"

#include "TPlaneGeometry.h"
#include "Paint_Entity_Tools.h"
#include "TSolidGeometry.h"
#include <cassert>
#include "Group_Ents.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Edit_Cut_Section::Edit_Cut_Section(Scene& scene,Cut_Section& cut)
:Create_Entity(scene)
,cut_section_(cut)
MCT_INIT2("Edit_Cut_Section")
{
	drag_start_ = false;
	drag_end_ = false;
	del_ = false;
	paint_selected();

//	cut_section_.selected(true);
//	scene_.invalidate();


}

Edit_Cut_Section::~Edit_Cut_Section()
{
//	cut_section_.selected(false);
//	scene_.invalidate();

}
void Edit_Cut_Section::close()
{
	delete this;
}
void Edit_Cut_Section::mouse_move_p(UINT nFlags, const Point& pt)
{
	switch(step_)
	{
	case 1:
		xor_draw();
		cur_ = pt;
		xor_draw();
		break;
	default:
		break;
	}
}
void Edit_Cut_Section::left_button_down_p(UINT nFlags, const Point& pt)
{
	Rect st,ed,mid;
	++step_;
	switch(step_)
	{
	case 1:
		begin_ = end_ = pt;
		cur_ = pt;
		get_rect(cut_section_.start(),st);
		get_rect(cut_section_.end(),ed);
		if(pt.envelop(st)){
			drag_start_ = true;
			moved_pt_ = cut_section_.start();
		}else if(pt.envelop(ed)){
			drag_end_ = true;
			moved_pt_ = cut_section_.end();
		}else{
			step_ = 0;
		}
		break;
	case 2:	
		cur_ = end_ = pt;
		xor_draw();
		drag_cut_section();
		scene_.idle_command();
		//scene_.idle_command(this);
		break;
	default:
		break;
	}
}
void Edit_Cut_Section::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(vk_.del()){
//		delete_txt_in_cut_section();
		delete_cut_sign();
		del_ = true;
		scene_.invalidate();
		//scene_.idle_command(this);
		scene_.idle_command();
	}

}
void Edit_Cut_Section::delete_cut_sign()
{
	Line * li = cut_section_.get_line_in_section();
	Text * txt = cut_section_.get_text_in_section();
	//先把组中该实体给删除掉
	scene_.database()->erase_ent_in_group(li);
	scene_.database()->erase_ent_in_group(txt);
	scene_.database()->erase_ent_in_group(&cut_section_);

	scene_.database()->remove_entity(li->entity_id());
	scene_.database()->remove_entity(txt->entity_id());
	scene_.database()->remove_entity(cut_section_.entity_id());
}
void Edit_Cut_Section::delete_txt_in_cut_section()
{
	LPCTSTR name = cut_section_.denote_text().c_str();
	int name_length = strlen(name);
	char* name_a = new char[name_length+1];
	char* temp = new char[name_length+1];
	strcpy(name_a,name);
	strcpy(temp,name);
	name_a[name_length] = '\0';
	temp[name_length] = '\0';
	strcat(name_a,"-");
	strcat(name_a,temp);
	LPCTSTR name_all = name_a;
	//循环数据库，去掉字符串=name_all的剖面名称
	delete_text(name_all);


	delete []temp;
	delete []name_a;
}
void Edit_Cut_Section::delete_text(LPCTSTR content)
{
	EntityIDArray ids;
	dlhml::entity_iterator iter = scene_.database()->entity_begin();
	for(; iter!=scene_.database()->entity_end();++iter){
		dlhml::Entity* ent = *iter;
		if(ent->isa(MY_RUNTIME_CLASS(Text))){
				Text *txt = (Text *)(ent);
				if(strcmp(txt->text().c_str(),content)==0){
					ids.push_back(txt->entity_id());
				}					
		}
	}
	for(int i=0;i<ids.size();i++)
		scene_.database()->remove_entity(ids[i]);
	scene_.invalidate();
	

}
void Edit_Cut_Section::right_button_up_p(UINT nFlags, const Point& pt)
{
	//scene_.idle_command(this);
	scene_.idle_command();
}
void Edit_Cut_Section::left_button_dblclk_p(UINT nFlags, const Point& pt)
{
	Edit_Entity* edit = scene_.get_edit_entity_dlg();
	assert(edit);
	edit->edit_cut_section(cut_section_);
	scene_.invalidate();
}
void Edit_Cut_Section::xor_draw_p(Draw_Entity& paint)
{
	Cut_Section cut_section(cut_section_);
	Rect rc;
/*
	//先擦掉
	get_rect(cut_section.start(),rc);
	paint.xor_draw_rect(rc);
	get_rect(cut_section.end(),rc);
	paint.xor_draw_rect(rc);
	//先擦掉

*/
	Point ptTemp = get_pedal_pt_to_line(cur_,cut_section_.start(),cut_section_.end());
	if(drag_start_){
		cut_section.start(ptTemp);
	}else if(drag_end_){
		cut_section.end(ptTemp);
	}else{}
//	Rect rc;
	get_rect(cut_section.start(),rc);
	paint.xor_draw_rect(rc);
	get_rect(cut_section.end(),rc);
	paint.xor_draw_rect(rc);
	paint.xor_draw_cut_section(cut_section);
}
void Edit_Cut_Section::paint_selected()
{
	Painter* painter = scene_.get_painter();
	Paint_Entity paint(scene_,*painter);
	Rect rc;
	get_rect(cut_section_.start(),rc);
	paint.xor_draw_rect(rc);
	get_rect(cut_section_.end(),rc);
	paint.xor_draw_rect(rc);
}
void Edit_Cut_Section::get_rect(const Point& pt,Rect& rc)
{
	Float len = pick_rect_edge_length() * scene_.screen_to_world().value(0,0);
	rc.xmin(pt.x-len);
	rc.xmax(pt.x+len);
	rc.ymin(pt.y-len);
	rc.ymax(pt.y+len);
}
void Edit_Cut_Section::drag_cut_section()
{
	Painter* painter = scene_.get_painter();
	Paint_Entity paint(scene_,*painter);
	paint.xor_draw_cut_section(cut_section_);

	Point ptTemp = get_pedal_pt_to_line(cur_,cut_section_.start(),cut_section_.end());
	if(drag_start_){
		cut_section_.start(ptTemp);
	}else if(drag_end_){
		cut_section_.end(ptTemp);
	}else{}
	paint.draw_cut_section(cut_section_);
}
bool Edit_Cut_Section::execute_p()
{
	if(del_){
		delete_execute_p();
	}else{
		end_ = moved_pt_;
		if(drag_start_){
			begin_ = moved_pt_ = cut_section_.start();
		}else if(drag_end_){
			begin_ = moved_pt_ = cut_section_.end();
		}else{}
		drag_cut_section();
	}
	scene_.invalidate();
	return true;
}
void Edit_Cut_Section::delete_unexecute_p()
{
		Line * li = cut_section_.get_line_in_section();
		Text * txt = cut_section_.get_text_in_section();
		Entity_ID id_l,id_txt;
		li->post2db(*scene_.database(),id_l);
		txt->post2db(*scene_.database(),id_txt);
		Group_Ents *group_ent = NULL,*txt_group = NULL,*cut_group = NULL;
		scene_.database()->select_group(group_ent,li->start());
		if(group_ent != NULL)
			group_ent->push_back(id_l);
		scene_.database()->select_group(txt_group,txt->position());
		if(txt_group != NULL)
			txt_group->push_back(id_txt);

		cut_section_.post2db(*scene_.database(),id_new_);
		scene_.database()->select_group(cut_group,cut_section_.start());
		if(cut_group != NULL)
			cut_group->push_back(id_new_);
}
void Edit_Cut_Section::delete_execute_p()
{
		Line * li = cut_section_.get_line_in_section();
		Text * txt = cut_section_.get_text_in_section();
		scene_.database()->remove_entity(li->entity_id());
		scene_.database()->remove_entity(txt->entity_id());
		scene_.database()->remove_entity(id_new_);
}
bool Edit_Cut_Section::unexecute_p()
{
	if(del_){
		delete_unexecute_p();
	}else{
		end_ = moved_pt_;
		if(drag_start_)
			begin_ = moved_pt_ = cut_section_.start();
		else if(drag_end_)
			begin_ = moved_pt_ = cut_section_.end();
		else{}
		drag_cut_section();
	}
	scene_.invalidate();

	return true;
}
Point Edit_Cut_Section::get_pedal_pt_to_line(const Point& ptCur,const Point& ptStart,const Point& ptEnd)
{
	TIAN_GA_BETTER::TLine line(Paint_Entity_Tools::GetPt3D(ptStart),Paint_Entity_Tools::GetPt3D(ptEnd));
	CPt3D_Pri pt3d = TIAN_GA_BETTER::TSolidGeometry::PtPedal(Paint_Entity_Tools::GetPt3D(ptCur),line);
	Point ptTemp = Paint_Entity_Tools::GetPoint(pt3d);
	return ptTemp;
}
void Edit_Cut_Section::mouse_wheel_p(UINT nFlags, short zDelta, const Point& pt)
{
	paint_selected();
}

}
