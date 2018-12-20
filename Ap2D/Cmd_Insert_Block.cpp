// Cmd_Insert_Block.cpp: implementation of the Cmd_Insert_Block class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Cmd_Insert_Block.h"

#include "Dlg_Block_Manage.h"
#include "DB_View.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cmd_Insert_Block::Cmd_Insert_Block(dlhml::Scene& scene):Create_Entity(scene)
{
		Dlg_Block_Manage dlg;
		if(dlg.DoModal() == IDOK){
			dlg.get_ents(ents_);
			
		}

}

Cmd_Insert_Block::~Cmd_Insert_Block()
{

}

dlhml::Point Cmd_Insert_Block::get_center()
{		
	dlhml::Point center;
	dlhml::EntityIDArray ent_ids;
	for(int i=0;i<ents_.size();i++){
		ent_ids.push_back(ents_[i]->entity_id());
	}
	dlhml::Rect rect;
	DB_View::instance()->cur_view()->scene()->database()->group_entity_rect(rect,ent_ids);
	center.x = (rect.xmax()+rect.xmin())/2.0;
	center.y = (rect.ymax()+rect.ymin())/2.0;
	return center;
}
void Cmd_Insert_Block::move(dlhml::Matrix move)
{
	for(int i=0;i<ents_.size();i++){
		ents_[i]->transformby(move);
	}

	
}

void Cmd_Insert_Block::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
{
	++step_;
	dlhml::Point center = get_center();
	dlhml::Matrix move_mat;
	switch(step_)
	{
	case 1:
		begin_ = end_ = pt;
		move_mat.set_move(center,begin_);
	
		move(move_mat);

		step_=0;

		break;
	default:
		break;
	}

	DB_View::instance()->cur_view()->scene()->invalidate();
}