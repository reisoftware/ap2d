// Visitor.h: interface for the Visitor class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_VISITOR_H__F961AEAD_0C8A_4270_B2FA_4AE9B1CA1CFF__INCLUDED_
#define AFX_VISITOR_H__F961AEAD_0C8A_4270_B2FA_4AE9B1CA1CFF__INCLUDED_

#include "counter.h"

namespace dlhml{
class Line;
class Line_Arrow;
class Circle;
class RArc;
class Arc_Arrow;
class Text;
class Rectentity;
class Cloud_Line;
class Cut_Section;
class Angle_Dimension;
class Ln_Dim;
class Lead_Dimension;
class Lead_Dimension_MT;
class Radius_Dimension;
class Text_Dimension;
class Three_Pt_Dimension;
class Block;
class Ln_Dim_Block;
class Three_Pt_Dimension_Block;
class Lead_Dimension_Block;
class Lead_Dimension_Info;
class Lead_Name;
class Text_Dimension_Info;
class Ln_Dim_PlateSide;
class Ln_Dim_Direct;

class Dim_Angle;
class Dim_Angle_Lean;
class Lead_Line_Dim;

class Group;
class Visitor  
{
public:
	Visitor()MCT_INIT1("Vistor"){}
	virtual ~Visitor(){}

	virtual bool visit_line(Line& ent) {return false;}
  virtual bool visit_line_arrow(Line_Arrow& ent) {return false;}
	virtual bool Visit_Circle(Circle& ent) {return false;}
	virtual bool Visit_RArc(RArc& ent) {return false;}
  virtual bool Visit_Arc_Arrow(Arc_Arrow& ent) {return false;}
	virtual bool Visit_Text(Text& ent) {return false;}
	virtual bool Visit_Rectentity(Rectentity& ent) {return false;}
	virtual bool Visit_Cloud_Line(Cloud_Line& ent) {return false;}
	virtual bool Visit_Cut_Section(Cut_Section& ent) {return false;}
	virtual bool Visit_Angle_Dimension(Angle_Dimension& dim) {return false;}
	virtual bool Visit_Ln_Dim(Ln_Dim& dim) {return false;}
	virtual bool Visit_Lead_Dimension(Lead_Dimension& dim) {return false;}
	virtual bool Visit_Lead_Line_Dim(Lead_Line_Dim& dim) {return false;}
	virtual bool Visit_Lead_Dimension_MT(Lead_Dimension_MT& dim) {return false;}
	virtual bool Visit_Radius_Dimension(Radius_Dimension& dim) {return false;}
	virtual bool Visit_Text_Dimension(Text_Dimension& dim) {return false;}
	virtual bool Visit_Three_Pt_Dimension(Three_Pt_Dimension& dim) {return false;}
	virtual bool Visit_Block(Block& block) {return false;}
	virtual bool Visit_Ln_Dim_Block(Ln_Dim_Block& dim) {return false;}
	virtual bool Visit_Three_Pt_Dimension_Block(Three_Pt_Dimension_Block& dim) {return false;}
	virtual bool Visit_Lead_Dimension_Block(Lead_Dimension_Block& dim) {return false;}
	//
	virtual bool Visit_Group(Group& group) {return false;}
	virtual bool visit_block(Block& block) {return false;}

	virtual bool visit_Lead_Name(Lead_Name& dim) {return false;}

	virtual bool visit_Lead_Dimension_Info(Lead_Dimension_Info& dim) {return false;}

	virtual bool Visit_Text_Dimension_Info(Text_Dimension_Info& dim) {return false;}
	virtual bool Visit_Ln_Dim_PlateSide(Ln_Dim_PlateSide& dim) {return false;}
	virtual bool Visit_Ln_Dim_Direct(Ln_Dim_Direct& dim) {return false;}
	//09.06.08
  //virtual bool visit_line_dim(Line_Dim& lndim) {return false;}
	virtual bool Visit_Dim_Angle(Dim_Angle& dim) {return false;}
	
  virtual bool visit_Dim_Angle_Lean(Dim_Angle_Lean& ent) {return false;}
private:
	MCT_DEF
};
}
#endif // !defined(AFX_VISITOR_H__F961AEAD_0C8A_4270_B2FA_4AE9B1CA1CFF__INCLUDED_)
