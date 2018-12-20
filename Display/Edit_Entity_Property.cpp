// Edit_Entity_Property.cpp: implementation of the Edit_Entity_Property class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Edit_Entity_Property.h"

#include "Scene_d.h"
#include "Line.h"
#include "Circle.h"
#include "RArc.h"
#include "Text.h"
#include "Cloud_Line.h"

#include "Angle_Dimension.h"
#include "Ln_Dim.h"
#include "Ln_Dim_Block.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Lead_Dimension_Block.h"
#include "Radius_Dimension.h"
#include "Text_Dimension.h"
#include "Three_Pt_Dimension.h"
#include "Three_Pt_Dimension_Block.h"

#include "Cut_Section.h"
#include "Rectentity.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Edit_Entity_Property::Edit_Entity_Property(Scene& scene)
:scene_(scene)
MCT_INIT2("Edit_Entity_Property")
{

}

Edit_Entity_Property::~Edit_Entity_Property()
{

}
void Edit_Entity_Property::close()
{
	delete this;
}
void Edit_Entity_Property::edit_line(Line& line) const
{
//	scene_.edit_line(line);
}
void Edit_Entity_Property::edit_rectentity(Rectentity& rect) const
{
	scene_.edit_rectentity(rect);
}
void Edit_Entity_Property::edit_circle(Circle& circle) const
{
//	scene_.edit_circle(circle);
}
void Edit_Entity_Property::edit_arc(RArc& arc) const
{
//	scene_.edit_arc(arc);
}
void Edit_Entity_Property::edit_text(Text& text) const
{
	scene_.edit_text(text);
}
void Edit_Entity_Property::edit_cloud_line(Cloud_Line& clout) const
{
//	scene_.edit_cloud_line(clout);
}
//void Edit_Entity_Property::edit_text_dim(Text_Dimension& dim) const
//{
//	scene_.edit_dim_text(dim);
//}
//void Edit_Entity_Property::edit_lead_dim(Lead_Dimension& dim) const
//{
//	scene_.edit_dim_lead(dim);
//}
//void Edit_Entity_Property::edit_three_pt_dim(Three_Pt_Dimension& dim) const
//{
//	scene_.edit_dim_three_pt(dim);
//}
//void Edit_Entity_Property::edit_three_pt_dim_block(Three_Pt_Dimension_Block& block) const
//{
//	scene_.edit_dim_three_pt_block(block);
//}
//void Edit_Entity_Property::edit_four_pt_dim(Ln_Dim& dim) const
//{
//	scene_.edit_dim_four_pt(dim);
//}
//void Edit_Entity_Property::edit_four_pt_dim_block(Ln_Dim_Block& block) const
//{
//	scene_.edit_dim_four_pt_block(block);
//}
//void Edit_Entity_Property::edit_angle_dim(Angle_Dimension& dim) const
//{
//	scene_.edit_dim_angle(dim);
//}
//void Edit_Entity_Property::edit_radius_dim(Radius_Dimension& dim) const
//{
//	scene_.edit_dim_radius(dim);
//}
void Edit_Entity_Property::edit_cut_section(Cut_Section& cut) const
{
	scene_.edit_cut_section(cut);
}
//void Edit_Entity_Property::edit_lead_dim_block(Lead_Dimension_Block& block) const
//{
//	scene_.edit_dim_lead_block(block);
//}



}
