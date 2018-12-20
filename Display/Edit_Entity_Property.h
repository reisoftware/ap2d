// Edit_Entity_Property.h: interface for the Edit_Entity_Property class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_EDIT_ENTITY_PROPERTY_H__1A873CD6_B918_4FE3_B180_B0957FC92267__INCLUDED_
#define AFX_EDIT_ENTITY_PROPERTY_H__1A873CD6_B918_4FE3_B180_B0957FC92267__INCLUDED_


#include "Edit_Entity.h"

namespace dlhml{
class Scene;
class Edit_Entity_Property : public Edit_Entity  
{
public:
	Edit_Entity_Property(Scene& scene);
	virtual ~Edit_Entity_Property();

	void close();

	void edit_line(Line& line) const;
	void edit_rectentity(Rectentity& rect) const;
	void edit_circle(Circle& circle) const;
	void edit_arc(RArc& arc) const;
	void edit_text(Text& text) const;
	void edit_cloud_line(Cloud_Line& clout) const;

//	void edit_text_dim(Text_Dimension& dim) const;
//
//	void edit_lead_dim(Lead_Dimension& dim) const;
//	void edit_lead_dim_block(Lead_Dimension_Block& block) const;
//	void edit_three_pt_dim(Three_Pt_Dimension& dim) const;
//	void edit_three_pt_dim_block(Three_Pt_Dimension_Block& block) const;
//	void edit_four_pt_dim(Four_Pt_Dimension& dim) const;
//	void edit_four_pt_dim_block(Four_Pt_Dimension_Block& block) const;
//  
//	void edit_angle_dim(Angle_Dimension& dim) const;
//	void edit_radius_dim(Radius_Dimension& dim) const;
	void edit_cut_section(Cut_Section& cut) const;

private:
	Scene& scene_;

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_EDIT_ENTITY_PROPERTY_H__1A873CD6_B918_4FE3_B180_B0957FC92267__INCLUDED_)
