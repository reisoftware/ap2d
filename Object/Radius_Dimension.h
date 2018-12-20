// Radius_Dimension.h: interface for the Radius_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_RADIUS_DIMENSION_H__7A6E1CAA_2DBA_467A_A4E5_60E7927BAFD6__INCLUDED_
#define AFX_RADIUS_DIMENSION_H__7A6E1CAA_2DBA_467A_A4E5_60E7927BAFD6__INCLUDED_


#include "Dimension.h"
#include "RArc.h"

namespace dlhml{
class OBJECT_API Radius_Dimension : public Dimension
{
	MY_DECLARE_DYNCREATE(Radius_Dimension)
public:
	Radius_Dimension();
	//Radius_Dimension(const Radius_Dimension& rhs);
	//Radius_Dimension& operator=(const Radius_Dimension& rhs);
	virtual ~Radius_Dimension();

//	void  setdata(const Point& center,const Point& tail,const Point& head);
  void arc(const RArc& a){arc_ = a;};
  RArc arc()const{return arc_;}
//	void  center (const Point& pt);	
//	Point center ()const;						
	void  tail   (const Point& pt);	
	Point tail   ()const;						
//	void  head   (const Point& pt);	
//	Point head   ()const;						

	bool get_line(Line& line) const;


public:
  virtual void get_line(std::vector<Entity*>& es)const;
  virtual void get_show(std::vector<Entity*>& es)const;
public:
	void get_line_show(Line& line) const;
	int  get_arrow_line_show  (std::vector<Line  *>& lines  ) const;
	int  get_arrow_circle_show(std::vector<Circle*>& circles) const;

protected:

public:
  bool visit(Visitor& v);
  
public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;

private:
  RArc arc_;
	//Point center_;
	Point tail_;
	//Point head_;
  //Float r_;

private:
//  void set_head(const Point& pt);
//  void set_tail(const Point& pt);
//  void recal_head();
//  void recal_tail();

public:
  Point head()const;

private:
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);

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

	//bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

  void recal_text();
  void recal_text_content();
  void recal_text_positon();
  void recal_text_rotation();

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_RADIUS_DIMENSION_H__7A6E1CAA_2DBA_467A_A4E5_60E7927BAFD6__INCLUDED_)
