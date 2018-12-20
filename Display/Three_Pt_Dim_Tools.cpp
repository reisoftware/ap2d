
#include "StdAfx.h"
#include "Three_Pt_Dim_Tools.h"

#include "Scene_d.h"
#include "Three_Pt_Dimension.h"
#include "Three_Pt_Dimension_Block.h"

namespace better{

Three_Pt_Dim_Tools::Three_Pt_Dim_Tools(const Scene& scene)
:scene_(scene)
,dim_  (NULL)
MCT_INIT2("Three_Pt_Dim_Tools")
{
}

Three_Pt_Dim_Tools::Three_Pt_Dim_Tools(const Scene& scene, 
                                       Three_Pt_Dimension * dim)
:scene_(scene)
,dim_(dim)
MCT_INIT2("Three_Pt_Dim_Tools")
{
}

//Three_Pt_Dim_Tools::Three_Pt_Dim_Tools(const Scene& scene, 
//                                       Three_Pt_Dimension_Block * dim_block)
//: scene_(scene)
//, dim_  (NULL)
//, dim_block_(dim_block)
//{
//}

Three_Pt_Dim_Tools::~Three_Pt_Dim_Tools()
{
}

void Three_Pt_Dim_Tools::set_dim_ptr(Three_Pt_Dimension * dim)
{
  dim_ = dim;
}

//void Three_Pt_Dim_Tools::set_dim_block_ptr(Three_Pt_Dimension_Block * dim_block)
//{
//  dim_block_ = dim_block;
//}

//void Three_Pt_Dim_Tools::insert_to_db()
//{
//}
//
//void Three_Pt_Dim_Tools::remove_from_db()
//{
//}

//namespace
}