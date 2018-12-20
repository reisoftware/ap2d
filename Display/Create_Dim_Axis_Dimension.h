// Create_Dim_Axis_Dimension.h: interface for the Create_Dim_Axis_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREATE_DIM_AXIS_DIMENSION_H__05DF1126_3601_48BF_B232_30F3CA0B7849__INCLUDED_)
#define AFX_CREATE_DIM_AXIS_DIMENSION_H__05DF1126_3601_48BF_B232_30F3CA0B7849__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Create_Entity.h"

namespace dlhml{
class DISPLAY_API Create_Dim_Axis_Dimension : public Create_Entity  
{
public:
	Create_Dim_Axis_Dimension(Scene& scene);
	virtual ~Create_Dim_Axis_Dimension();
	void close(){delete this;}
private:
	void mouse_move_p(UINT nFlags, const Point& pt);
	void left_button_down_p(UINT nFlags, const Point& pt);
	void right_button_up_p(UINT nFlags, const Point& pt);

	void xor_draw_p(Draw_Entity& paint);
	void add_dim();

	
private:
	MCT_DEF
};
}

#endif // !defined(AFX_CREATE_DIM_AXIS_DIMENSION_H__05DF1126_3601_48BF_B232_30F3CA0B7849__INCLUDED_)
