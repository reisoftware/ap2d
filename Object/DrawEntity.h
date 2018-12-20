
#ifndef _DRAW_ENTITY_H_DLHML_
#define _DRAW_ENTITY_H_DLHML_

#include "export.h"

namespace dlhml{
class Line;
class Rectentity;
class Circle;
class RArc;
class Text;
class Cloud_Line;
class Text_Dimension;
class Lead_Dimension;
class Three_Pt_Dimension;
class Ln_Dim;
class Angle_Dimension;
class Radius_Dimension;
class Cut_Section;

class Rect;

//
//class Line_Dim;


class OBJECT_API Draw_Entity
{
public:
	Draw_Entity()MCT_INIT1("Draw_Entity"){}
	virtual ~Draw_Entity(){};

	virtual void draw_line(const Line& line) = 0;
	virtual void draw_rectentity(const Rectentity& rect) = 0;
	virtual void draw_circle(const Circle& circle) = 0;
	virtual void draw_arc(const RArc& arc) = 0;
	virtual void draw_text(const Text& text) = 0;

	virtual void draw_cloud_line(const Cloud_Line& cloud) = 0;
	virtual void draw_cut_section(const Cut_Section& cut) = 0;
//	virtual void draw_text_dim(const Text_Dimension& dim) = 0;
//	virtual void draw_lead_dim(const Lead_Dimension& dim) = 0;
//	virtual void draw_three_pt_dim(const Three_Pt_Dimension& dim) = 0;
//	virtual void draw_ln_dim(const Ln_Dim& dim) = 0;
//	virtual void draw_angle_dim(const Angle_Dimension& dim) = 0;
//	virtual void draw_radius_dim(const Radius_Dimension& dim) = 0;



	virtual void xor_draw_line(const Line& line) = 0;
	virtual void xor_draw_rectentity(const Rectentity& rect) = 0;
	virtual void xor_draw_circle(const Circle& circle) = 0;
	virtual void xor_draw_arc(const RArc& arc) = 0;
	virtual void xor_draw_text(const Text& text) = 0;

	virtual void xor_draw_cloud_line(const Cloud_Line& cloud) = 0;
	virtual void xor_draw_cut_section(const Cut_Section& cut) = 0;
//	virtual void xor_draw_text_dim(const Text_Dimension& dim) = 0;
//	virtual void xor_draw_lead_dim(const Lead_Dimension& dim) = 0;
//	virtual void xor_draw_three_pt_dim(const Three_Pt_Dimension& dim) = 0;
//	virtual void xor_draw_ln_dim(const Ln_Dim& dim) = 0;
//	virtual void xor_draw_angle_dim(const Angle_Dimension& dim) = 0;
//	virtual void xor_draw_radius_dim(const Radius_Dimension& dim) = 0;


	virtual void xor_draw_rect(const Rect& rect) = 0;

  //
//	virtual void     draw_line_dim(const Line_Dim& lndim) = 0;
//	virtual void xor_draw_line_dim(const Line_Dim& lndim) = 0;

private:
	MCT_DEF
};
}
#endif //_DRAW_ENTITY_H_DLHML_
