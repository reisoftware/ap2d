
#ifndef _EDIT_ENTITY_H_DLHML_
#define _EDIT_ENTITY_H_DLHML_

#include "export.h"
#include "../afc/counter.h"

namespace dlhml{
class Line;
class Line_Arrow;
class Rectentity;
class Circle;
class RArc;
class Text;
class Cloud_Line;
class Text_Dimension;
class Lead_Dimension;
class Lead_Dimension_Block;
class Three_Pt_Dimension;
class Three_Pt_Dimension_Block;
class Ln_Dim;
class Ln_Dim_Block;
class Angle_Dimension;
class Radius_Dimension;
class Cut_Section;
class Dim_Angle;
class Dim_Angle_Lean;
class OBJECT_API Edit_Entity
{
public:
  Edit_Entity():okcancel_(false)MCT_INIT2("Edit_Entity"){}
	virtual ~Edit_Entity(){}

	virtual void close() = 0;

	virtual void edit_line(Line& line) const = 0;
  virtual void edit_line_arrow(Line_Arrow& line) const{}
	virtual void edit_rectentity(Rectentity& rect) const = 0;
	virtual void edit_circle(Circle& circle) const = 0;
	virtual void edit_arc(RArc& arc) const = 0;
	virtual void edit_text(Text& text) const = 0;
	virtual void edit_cloud_line(Cloud_Line& clout) const = 0;
  //	virtual void edit_text_dim(Text_Dimension& dim) const = 0;
  //	virtual void edit_lead_dim(Lead_Dimension& dim) const = 0;
  //	virtual void edit_three_pt_dim(Three_Pt_Dimension& dim) const = 0;
  //	virtual void edit_three_pt_dim_block(Three_Pt_Dimension_Block& block) const = 0;
  //	virtual void edit_four_pt_dim(Ln_Dim& dim) const = 0;
  //	virtual void edit_four_pt_dim_block(Ln_Dim_Block& block) const = 0;
  //	virtual void edit_angle_dim(Angle_Dimension& dim) const = 0;
  //	virtual void edit_radius_dim(Radius_Dimension& dim) const = 0;
	virtual void edit_cut_section(Cut_Section& cut) const = 0;
  //	virtual void edit_lead_dim_block(Lead_Dimension_Block& block) const = 0;
  virtual void edit_Dim_Angle_Lean(Dim_Angle_Lean& dim) const{}

public:
  void okcancel(bool ok){okcancel_ = ok;}
  bool okcancel()const{return okcancel_;}
protected:
  mutable bool okcancel_;

private:
	MCT_DEF
};
}

#endif //_EDIT_ENTITY_H_DLHML_
