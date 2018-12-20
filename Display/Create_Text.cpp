// reate_Text.cpp: implementation of the Create_Text class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Create_Text.h"

#include "Scene_d.h"
#include "Text.h"
#include "Paint_Entity.h"

#include "Painter.h"
#include "myalgorithm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Create_Text::Create_Text(Scene& scene,LPCTSTR cont,int height, int color_id)
:Create_Entity(scene)
,cont_(cont)
,hei_(height)
,cid_(color_id)
MCT_INIT2("Create_Text")
{
  create_text_=true;
  text_=NULL;
	cont_ = cont;
//	text.text(cont);
//	text.color(scene_.entity_color());

	text_ = Text::create_me();
	text_->setdata(end_,cont_.c_str());
  text_->dxf_height(hei_);
	text_->color_index(color_id);
//	text_->color(scene_.entity_color());
//	text_->color(3);
  xor_draw();
}

Create_Text::~Create_Text()
{

}
void Create_Text::close()
{
	delete this;
}

void Create_Text::on_draw()
{
  xor_draw();
}
void Create_Text::xor_draw()
{
  Paint_Entity paint=get_paint();
	text_->set_database(scene_.database());
	text_->setdata(end_,cont_.c_str());
	paint.xor_draw_text(*text_);
}

void Create_Text::mouse_move_p(UINT nFlags, const Point& pt)
{
  xor_draw();
	end_ = pt;
  xor_draw();
}
void Create_Text::left_button_down_p(UINT nFlags, const Point& pt)
{
	end_ = pt;
	//判断是否在块内
	scene_.database()->select_group(group_ents_,end_);
	addtext();
	scene_.idle_command();
}
void Create_Text::right_button_up_p(UINT nFlags, const Point& pt)
{
	end_ = pt;
	addtext();
	scene_.idle_command();
}
void Create_Text::addtext()
{
	Entity_ID id;
	text_->post2db(*scene_.database(),id);

/*
	//test*************
	text_->re_calc_box2d();
	Rect rect = text_->box2d();
	Point pt1,pt2,pt3,pt4;
	pt1.setdata(rect.xmin(),rect.ymax());
	pt2.setdata(rect.xmax(),rect.ymin());
	pt3.setdata(rect.xmax(),rect.ymax());
	pt4.setdata(rect.xmin(),rect.ymax());
	Line *l = Line::create_me();
	l->setdata(pt1,pt2);
	Line *r = Line::create_me();
	r->setdata(pt3,pt4);
	l->post2db(*scene_.database(),id);
	r->post2db(*scene_.database(),id);
	//test*************
*/

	Painter* painter = scene_.get_painter();
	Paint_Entity paint(scene_,*painter);
	paint.xor_draw_text(*text_);
	paint.draw_text(*text_);
	//添加到块
	if(group_ents_)
		group_ents_->push_back(id);
}

void Create_Text::key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(vk_.enter()){
    char buf[512];
    int buf_end =  get_commmand_line_string(buf);
    buf[buf_end]= '\0';
    cont_ = buf;
	  text_->setdata(end_,cont_.c_str());
    //scene_.invalidate();
    command_line_output("");
  }
}

}
