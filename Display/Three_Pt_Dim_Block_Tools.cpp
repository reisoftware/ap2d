
#include "StdAfx.h"
#include "Three_Pt_Dim_Block_Tools.h"

#include "Scene_d.h"
#include "Three_Pt_Dimension.h"
#include "Three_Pt_Dimension_Block.h"

namespace better{

Three_Pt_Dim_Block_Tools::Three_Pt_Dim_Block_Tools(const Scene& scene)
:scene_(scene)
,dim_block_(NULL)
MCT_INIT2("Three_Pt_Dim_Block_Tools")
{
}

//Three_Pt_Dim_Block_Tools::Three_Pt_Dim_Block_Tools(const Scene& scene, 
//                                                   Three_Pt_Dimension * dim)
//: scene_(scene)
////, dim_  (dim)
//, dim_block_(NULL)
//{
//}

Three_Pt_Dim_Block_Tools::Three_Pt_Dim_Block_Tools(const Scene& scene, 
                                                   Three_Pt_Dimension_Block * dim_block)
:scene_(scene)
,dim_block_(dim_block)
MCT_INIT2("Three_Pt_Dim_Block_Tools")
{
}

Three_Pt_Dim_Block_Tools::~Three_Pt_Dim_Block_Tools()
{
}

//void Three_Pt_Dim_Block_Tools::set_dim_ptr(Three_Pt_Dimension * dim)
//{
//  dim_ = dim;
//}

void Three_Pt_Dim_Block_Tools::set_dim_block_ptr(Three_Pt_Dimension_Block * dim_block)
{
  dim_block_ = dim_block;
}

//void Three_Pt_Dim_Block_Tools::insert_to_db()
//{
//  if(!dim_block_){
//    return;
//  }
//  
//}
//
//void Three_Pt_Dim_Block_Tools::remove_from_db()
//{
//  if(!dim_block_){
//    return;
//  }
//}

//namespace
}