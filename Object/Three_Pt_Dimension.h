// Three_Pt_Dimension.h: interface for the Three_Pt_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_THREE_PT_DIMENSION_H__2B8B2A33_8C91_4B04_B9B3_38B84402B587__INCLUDED_
#define AFX_THREE_PT_DIMENSION_H__2B8B2A33_8C91_4B04_B9B3_38B84402B587__INCLUDED_


#include "Dimension.h"
#include <vector>

namespace dlhml{
class Line;
class Circle;
class OBJECT_API Three_Pt_Dimension : public Dimension
{
	MY_DECLARE_DYNCREATE(Three_Pt_Dimension)
public:
	Three_Pt_Dimension();
	Three_Pt_Dimension(const Three_Pt_Dimension& rhs);
	Three_Pt_Dimension& operator=(const Three_Pt_Dimension& rhs);
	virtual ~Three_Pt_Dimension();

	void  setdata(const Point& st,const Point& ed,const Point& dim);

  //angle
  void  extend_radian (Float a);					
  Float extend_radian ()const	 ;					
  void  dimline_radian(Float a);					
  Float dimline_radian()const	 ;
  void  dimline_degree(Float a);
  Float dimline_degree()const	 ;					
 
	void  start_dim_to(const Point& st);			
  Point start_dim_to()const			  ;     
  void  end_dim_to  (const Point& ed);				
  Point end_dim_to  ()const				;       
  void  dimension_pt(const Point& dimpt);	
  Point dimension_pt()const			     ;  

	bool get_lines(Line& start_extendline,Line& end_extendline,Line& dimline) const;

	bool get_dim_lines_show(std::vector<Line*>& lines) const;
	int  get_arrow_line_show(const Line& dim,std::vector<Line*>& lines) const;
	int  get_arrow_circle_show(const Line& dim,std::vector<Circle*>& circles) const;


	bool visit(Visitor& v);

public:
  virtual void get_line(std::vector<Entity*>& es)const{}
  virtual void get_show(std::vector<Entity*>& es)const{}
  

private:
	Float extend_angle_;
	Point start_;
	Point end_;
	Point dimpt_;

private:
	void loadme(File& in);
	void saveme(const File& out) const;

	void edit_propertyme(const Edit_Entity& edit);

	//void drawme(Draw_Entity& out) const;
	//void xor_drawme(Draw_Entity& out) const;

	errorinfo postme2db(Database& db,Entity_ID& id);

	void transformbyme(const Matrix& mat);
	void drag_startme(const Matrix& mat);
	void drag_endme(const Matrix& mat);

	Entity* cloneme() const;

	void closeme();

	bool intersectme(const Rect& rect) const;
	bool envelopme(const Rect& rect) const;

	Rect calc_box2d() const;

	bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_THREE_PT_DIMENSION_H__2B8B2A33_8C91_4B04_B9B3_38B84402B587__INCLUDED_)
