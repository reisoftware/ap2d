// Mgr_Entity.h: interface for the Mgr_Entity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_ENTITY_H__C7E3E310_248E_41DC_AA03_4D26981F7798__INCLUDED_)
#define AFX_MGR_ENTITY_H__C7E3E310_248E_41DC_AA03_4D26981F7798__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line_Arrow.h"
#include "Circle.h"
#include "Arc_Arrow.h"
#include "Cloud_Line.h"
#include "Lead_Dimension.h"
#include "Ln_Dim.h"
#include "Angle_Dimension.h"
#include "Radius_Dimension.h"
#include "Mgr_Dxfs.h"
#include "Global.h"
#include "Lead_Dimension_Info.h"
#include "Text_Dimension.h"
#include "Text_Dimension_Info.h"


class Mgr_Entity  
{
public:
	Mgr_Entity();
	virtual ~Mgr_Entity();

};

void init_line_arrow(dlhml::Line_Arrow &seed);
void init_circle(dlhml::Circle &seed);
void init_arc_arrow(dlhml::Arc_Arrow &seed);
void init_cloud_line(dlhml::Cloud_Line &seed);
void init_dim_lead(dlhml::Lead_Dimension &seed);
void init_ln_dim(dlhml::Ln_Dim &seed);
void init_angle_dim(dlhml::Angle_Dimension &seed);
void init_radius_dim(dlhml::Radius_Dimension &seed);

void init_dim_text(dlhml::Text_Dimension &seed);

void set_brush_prop(Entitys &ents,Brush_Prop &brush_prop);

void init_dim_lead_info(dlhml::Lead_Dimension_Info &seed);
void init_dim_text_info(dlhml::Text_Dimension_Info &seed);

void extend_line();

#endif // !defined(AFX_MGR_ENTITY_H__C7E3E310_248E_41DC_AA03_4D26981F7798__INCLUDED_)
