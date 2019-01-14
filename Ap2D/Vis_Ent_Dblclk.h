// Vis_Ent_Dblclk.h: interface for the Vis_Ent_Dblclk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIS_ENT_DBLCLK_H__06B662FF_DDAE_4B66_B2A2_D2FFD8B397DE__INCLUDED_)
#define AFX_VIS_ENT_DBLCLK_H__06B662FF_DDAE_4B66_B2A2_D2FFD8B397DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Visitor.h"
#include "Mgr_Dxfs.h"




class Vis_Ent_Dblclk  : public dlhml::Visitor 
{
public:
	Vis_Ent_Dblclk();
	virtual ~Vis_Ent_Dblclk();

	bool visit_line(dlhml::Line& line);
	bool visit_line_arrow(dlhml::Line_Arrow& la);
	bool Visit_Circle(dlhml::Circle& circle);
	bool Visit_RArc(dlhml::RArc& arc);
  bool Visit_Arc_Arrow(dlhml::Arc_Arrow& aa);
	bool Visit_Text(dlhml::Text& text);
	bool Visit_Cloud_Line(dlhml::Cloud_Line& cloud);

	bool Visit_Angle_Dimension(dlhml::Angle_Dimension& dim);
	bool Visit_Ln_Dim(dlhml::Ln_Dim& dim) ;
	bool Visit_Ln_Dim_Block(dlhml::Ln_Dim_Block& dim);
	bool Visit_Radius_Dimension(dlhml::Radius_Dimension& dim);

	bool Visit_Lead_Dimension(dlhml::Lead_Dimension& lead_dim);
	bool Visit_Text_Dimension(dlhml::Text_Dimension& text_dim);
	
	bool Visit_Lead_Dimension_Block(dlhml::Lead_Dimension_Block& lead_dim_block);

	bool visit_Lead_Dimension_Info(dlhml::Lead_Dimension_Info& lead_dim_info);
	bool Visit_Lead_Line_Dim(dlhml::Lead_Line_Dim& lead_dim_info);



	bool Visit_Text_Dimension_Info(dlhml::Text_Dimension_Info& dim) ;
	bool Visit_Ln_Dim_PlateSide(dlhml::Ln_Dim_PlateSide& dim) ;
	bool Visit_Ln_Dim_Direct(dlhml::Ln_Dim_Direct& dim);

	bool Visit_Dim_Angle(dlhml::Dim_Angle& dim);

private:
	void show_dlg();
	
};

#endif // !defined(AFX_VIS_ENT_DBLCLK_H__06B662FF_DDAE_4B66_B2A2_D2FFD8B397DE__INCLUDED_)
