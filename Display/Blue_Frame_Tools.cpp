

#include "StdAfx.h"
#include "Blue_Frame_Tools.h"

#include "Scene_d.h"
#include "Group_Ents.h"
#include "Point.h"
#include "Circle.h"
#include "Cloud_Line.h"
#include "Create_Entity.h"
#include "Database.h"
#include "Dimension_Style.h"
#include "Line.h"
#include "Line_Type.h"
#include "myalgorithm.h"
#include "Normal.h"
#include "Paint_Entity.h"
#include "Paint_Entity_Tools.h"
#include "Painter.h"
#include "Point.h"
#include "RArc.h"
#include "Scene_d.h"
#include "Select_Font.h"
#include "Select_Pen.h"
#include "Text.h"
#include "Text_Style.h"

namespace dlhml{

Blue_Frame_Tools::Blue_Frame_Tools(Scene& scene, Group_Ents* blue)
:Paint_Entity_Tools(scene)
,blue_(blue)
MCT_INIT2("Blue_Frame_Tools")
{
}

Blue_Frame_Tools::~Blue_Frame_Tools()
{
}

dlhml::Group_Ents * Blue_Frame_Tools::select_blue_frame(const dlhml::Point& pt) const
{
  dlhml::Group_Ents * blue_frame = NULL;
  if(!scene_.database()->select_group(blue_frame, pt)){
    blue_frame = NULL;
  }
  return blue_frame;
}

bool Blue_Frame_Tools::is_pt_in_blue_frame(const Point& pt, 
                                           const Group_Ents* blue_frame) const
{
  return blue_frame->isin(pt);
}

void Blue_Frame_Tools::reset_show_4pt_start()const
{
	if(!blue_){ 
	  return;
	}
	Ln_Dim_Block * block = NULL;

	int i=0;
	for(i=0; i<blue_->entity_count(); ++i){
    const Entity* ent_it = (*blue_)[i];
    if(!ent_it){
      continue;
    }
		if(ent_it->myclass()==LINE_DIM_BLOCK){
		  block = (Ln_Dim_Block*)ent_it;
      if(block->mode()==PILEUP_DIM){
        block->show0(true);
      }
    }
  }

  for(i=0; i<blue_->entity_count(); ++i){
    const Entity* ent_it = (*blue_)[i];
    if(!ent_it){
      continue;
    }
		if(ent_it->myclass()==LINE_DIM_BLOCK){
		  block = (Ln_Dim_Block*)ent_it;
      //  如果它是显示的，隐藏后面所有重合0点，否则，不处理。
      if(block->mode()==PILEUP_DIM){
        if(block->show0()){
          hide_4pt_start_by_superposion(block);
        }
      }
		}
	}
}
//void Blue_Frame_Tools::reset_show_4pt_start()const
//{
//	if(!blue_){ 
//	  return;
//	}
//	Ln_Dim_Block * block = NULL;
//  EntityIDArray::const_iterator begin = blue_->begin();
//  EntityIDArray::const_iterator end = blue_->end();
//  EntityIDArray::const_iterator it = begin;
//  for(it = begin; it != end; it++){
//    Entity* ent_it;
//    scene_.database()->entity_from_id(ent_it, *it);
//    if(!ent_it){
//      continue;
//    }
//		if(ent_it->myclass()==LINE_DIM_BLOCK){
//		  block = (Ln_Dim_Block*)ent_it;
//      if(block->mode()==PILEUP_DIM){
//        block->show0(true);
//      }
//    }
//  }
//  for(it = begin; it != end; it++){
//    Entity* ent_it;
//    scene_.database()->entity_from_id(ent_it, *it);
//    if(!ent_it){
//      continue;
//    }
//		if(ent_it->myclass()==LINE_DIM_BLOCK){
//		  block = (Ln_Dim_Block*)ent_it;
//      //  如果它是显示的，隐藏后面所有重合0点，否则，不处理。
//      if(block->mode()==PILEUP_DIM){
//        if(block->show0()){
//          hide_4pt_start_by_superposion(block);
//        }
//      }
//		}
//	}
//}

void Blue_Frame_Tools::hide_4pt_start_by_superposion(Ln_Dim_Block* block)const
{
	if(!blue_||!block){ 
	  return;
	}
	Ln_Dim_Block * other = NULL;
  
	int i=0;
	for(i=0; i<blue_->entity_count(); ++i)
  {
    const Entity* ent_it = (*blue_)[i];
    if(!ent_it){
      continue;
    }
		if(ent_it->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
		  other = (Ln_Dim_Block*)ent_it;
      //  不改变自身
      if(other == block){
        continue;
      }
			//  如果和当前标注0点引出线直线重合,隐藏它的0点.
			if(is_0_position(other, block)){
			  other->show0(false);
			}
		}
	}

}

//void Blue_Frame_Tools::hide_4pt_start_by_superposion(Ln_Dim_Block* block)const
//{
//	if(!blue_||!block){ 
//	  return;
//	}
//	Ln_Dim_Block * other = NULL;
//  EntityIDArray::const_iterator it = blue_->begin();
//  EntityIDArray::const_iterator end = blue_->end();
//  
//
//	for(; it != end; it++)
//  {
//    Entity* ent_it;
//    scene_.database()->entity_from_id(ent_it, *it);
//    if(!ent_it){
//      continue;
//    }
//		if(ent_it->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
//		  other = (Ln_Dim_Block*)ent_it;
//      //  不改变自身
//      if(other == block){
//        continue;
//      }
//			//  如果和当前标注0点引出线直线重合,隐藏它的0点.
//			if(is_0_position(other, block)){
//			  other->show0(false);
//			}
//		}
//	}
//
//}

//namespace
}