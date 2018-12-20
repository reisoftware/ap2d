// Paint_Entity.h: interface for the Paint_Entity class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_PAINT_ENTITY_H__37EF3BEA_B603_4224_A21E_E6F4112CF07A__INCLUDED_
#define AFX_PAINT_ENTITY_H__37EF3BEA_B603_4224_A21E_E6F4112CF07A__INCLUDED_

#include "display_export.h"
#include "DrawEntity.h"
#include <vector>
#include <list>

namespace dlhml{
class Scene;
class Painter;
class Line_Type;
class Entity;
class Point;

class Rect;
class Text;
class Dimension;
class Cut_Section;
class DISPLAY_API Paint_Entity : public Draw_Entity
{
	static HANDLE thread_;
public:
	Paint_Entity(Scene& scene,Painter& painter);
	~Paint_Entity();
	void close();

public:
  void draw_all_entity(); 
private:
	void rect_select_entity(std::list<Entity*>& ents,const Rect& rect);
  void draw_entity(std::list<Entity*>& ents);
  void draw_entity_list(std::list<Entity*>& ents);
  void draw_entity_list(std::list<Entity*>& ents, int max_count);
  void draw_database();

private:
	void paint_arc(const RArc& arc);
	void xor_paint_arc(const RArc& arc);
public:
	void draw_arc(const RArc& arc);
	void xor_draw_arc(const RArc& arc);

private:
	void paint_circle(const Circle& circle);
	void xor_paint_circle(const Circle& circle);
public:
	void draw_circle(const Circle& circle);
	void xor_draw_circle(const Circle& circle);


public:
	void xor_draw_cloud_line(const Cloud_Line& cloud);
	void draw_cloud_line(const Cloud_Line& cloud);
	void cloud_line_paint(const Cloud_Line& cloud, bool xor = true);

private:
  void paint_line(const Line& line, bool xor, const Point& st, const Point& ed);
public:
	void draw_line(const Line& line);
	void xor_draw_line(const Line& line);
  void draw_line(const Line& line, bool xor);

public:
	void draw_rectentity(const Rectentity& rect);
	void draw_text(const Text& text);

  void draw_rect(const Rect& rect, bool xor);
	void draw_rect(const Rect& rect);
  void xor_draw_rect(const Rect& rect);

	void xor_draw_rectentity(const Rectentity& rect);
	void xor_draw_text(const Text& text);

  
//	void draw_ln_dim(const Ln_Dim& dim);
//	void xor_draw_ln_dim(const Ln_Dim& dim);
//  void ln_dim_paint(const Ln_Dim& dim, bool xor=true);

//  void draw_ln_din_block(const Ln_Dim_Block& block);
//	void draw_text_dim(const Text_Dimension& dim);
//	void draw_lead_dim(const Lead_Dimension& dim);
//	void draw_three_pt_dim(const Three_Pt_Dimension& dim);
//	void draw_angle_dim(const Angle_Dimension& dim);
//	void draw_radius_dim(const Radius_Dimension& dim);
  void draw_cut_section(const Cut_Section& cut);
//
//	void xor_draw_text_dim(const Text_Dimension& dim);
//	void xor_draw_lead_dim(const Lead_Dimension& dim);
//	void xor_draw_three_pt_dim(const Three_Pt_Dimension& dim);
//	void xor_draw_angle_dim(const Angle_Dimension& dim);
//	void xor_draw_radius_dim(const Radius_Dimension& dim);
	void xor_draw_cut_section(const Cut_Section& cut);

//	void draw_line_dim(const Line_Dim& dim);
//	void xor_draw_line_dim(const Line_Dim& dim);

private:
  bool output_arc(const RArc& arc);

private:
	void draw_coord();

private:
	Scene& scene_;
	Painter& painter_;

	Point world_to_screen(const Point& pt);
	
	Line_Type* line_style_;
	void select_linestyle(const Entity& ent);

private:
	void draw_solid_circle(const Circle& circle);
	void xor_draw_solid_circle(const Circle& circle);
	//void draw_dimension_text(Text& text,const Dimension& dim);
	//void xor_draw_dimension_text(Text& text,const Dimension& dim);

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_PAINT_ENTITY_H__37EF3BEA_B603_4224_A21E_E6F4112CF07A__INCLUDED_)
