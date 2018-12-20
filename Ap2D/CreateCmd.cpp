
#include "StdAfx.h"
#include "CreateCmd.h"

//11ÀàÊµÌå
#include "Line_Arrow.h"
#include "RArc.h"
#include "Circle.h"
#include "Angle_Dimension.h"
#include "Cloud_Line.h"
#include "Cut_Section.h"
#include "Lead_Dimension_Block.h"
#include "Ln_Dim_Block.h"
#include "Radius_Dimension.h"
#include "Rectentity.h"
#include "Text_Dimension.h"
#include "Mgr_Dxfs.h"



namespace dlhml
{

CreateCmd::CreateCmd(Scene& scene, Entity* org)
:Create_Command(scene, org)
{
}

Create_Entity* CreateCmd::cloneme()
{
  //Entity * myorg = org_->clone();
  dlhml::CreateCmd * cs = new dlhml::CreateCmd(scene_, org_);
  cs->mode(mode_);
	cs->set_steel(steel_);
  cs->db_color=db_color;
  cs->mouse_screen_ = mouse_screen_;
  cs->mouse_move_   = mouse_move_  ;
  cs->mouse_snap_   = mouse_snap_  ;
  cs->steel_        = steel_       ;
  //cs->paint_snap_.ondraw();
	cs->blue_frame(blue_frame());
  return cs;
}
static void deal_ent(Line_Arrow* e)
{
/*
	int pos_s = ap2d::Model::instance()->block_db().is_select(e->start());
	int pos_e = ap2d::Model::instance()->block_db().is_select(e->end());
	if(pos_s != -1){
		ap2d::Model::instance()->block_db().blks_[pos_s].ids_.push_back(e->entity_id());
		ap2d::Model::instance()->block_db().blks_[pos_s].ents_.push_back(e);
	}
	if(pos_e != -1){
		ap2d::Model::instance()->block_db().blks_[pos_e].ids_.push_back(e->entity_id());
		ap2d::Model::instance()->block_db().blks_[pos_e].ents_.push_back(e);
	}
*/
}
static void deal_ent(RArc* e)
{
}
static void deal_ent(Circle* e)
{
}
static void deal_ent(Angle_Dimension* e)
{
}
static void deal_ent(Cloud_Line* e)
{
}
static void deal_ent(Cut_Section* e)
{
}
static void deal_ent(Lead_Dimension_Block* e)
{
}
static void deal_ent(Ln_Dim_Block* e)
{
}
static void deal_ent(Radius_Dimension* e)
{
}
static void deal_ent(Rectentity* e)
{
}
static void deal_ent(Text_Dimension* e)
{
}
static void add_block(Entity* entity)
{
	if(entity->isa(MY_RUNTIME_CLASS(Line_Arrow))){
		deal_ent((Line_Arrow*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(RArc))){
		deal_ent((RArc*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Circle))){
		deal_ent((Circle*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Angle_Dimension))){
		deal_ent((Angle_Dimension*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Cloud_Line))){
		deal_ent((Cloud_Line*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Cut_Section))){
		deal_ent((Cut_Section*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block))){
		deal_ent((Lead_Dimension_Block*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
		deal_ent((Ln_Dim_Block*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Radius_Dimension))){
		deal_ent((Radius_Dimension*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Rectentity))){
		deal_ent((Rectentity*)entity);
	}else if(entity->isa(MY_RUNTIME_CLASS(Text_Dimension))){
		deal_ent((Text_Dimension*)entity);
	}

}
void CreateCmd::insert_to_db_p(Entity* entity)
{
	int cmd_status = get_steel();
	entity->layer_name(LAYER_AP_DIM);

	add_block(entity);

}

void CreateCmd::remove_from_db_p(Entity* entity)
{
	
}


}//namespace

