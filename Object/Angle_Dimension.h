// Angle_Dimension.h: interface for the Angle_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_ANGLE_DIMENSION_H__C864DE35_556A_48B9_A817_F6042157F0C0__INCLUDED_
#define AFX_ANGLE_DIMENSION_H__C864DE35_556A_48B9_A817_F6042157F0C0__INCLUDED_

#include "Dimension.h"
#include "RArc.h"

namespace dlhml{

class Entity;

class OBJECT_API Angle_Dimension : public Dimension
{
	MY_DECLARE_DYNCREATE(Angle_Dimension)
public:
  //virtual MY_CLASS myclass()const{return ANGLE_DIM;}
public:
	Angle_Dimension();
//	Angle_Dimension(const Angle_Dimension& rhs);
//	Angle_Dimension& operator=(const Angle_Dimension& rhs);
	virtual ~Angle_Dimension();

	void setdata(const Point& v,const Point& st,const Point& ed,const Point& dim);
	void  vertex(const Point& pt){vertex_ =pt;}
	void  start (const Point& pt){start_  =pt;}
	void  dim   (const Point& pt){dim_    =pt;}
	void  end   (const Point& pt){end_    =pt;}
  void  center(const Point& pt);
	Point vertex()const	{return vertex_ ;}
	Point start ()const	{return start_  ;}
	Point dim   ()const	{return dim_    ;}
	Point end   ()const	{return end_    ;}
  Point center()const;

	void dim_text_recal();
	void dim_text_content();
	void dim_text_position();
	void dim_text_rotation();
	void dim_text_alignpt();

public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;

public:
	bool get_lines(Line& st,Line& ed,Line& entendline,RArc& dim) const;

//SHOW
public:
  virtual void get_line(std::vector<Entity*>& es)const;
  virtual void get_show(std::vector<Entity*>& es)const;
  
protected:
	void get_dim_lines_show(Line& st,Line& ed,Line& extendline,RArc& dim) const;
	int  get_start_arrow_line_show  (std::vector<Line   *>& lines   ) const;
	int  get_end_arrow_line_show    (std::vector<Line   *>& lines   ) const;
	int  get_start_arrow_circle_show(std::vector<Circle *>& circles ) const;
	int  get_end_arrow_circle_show  (std::vector<Circle *>& circles ) const;


public:
	bool visit(Visitor& v);

private:
	Point vertex_;
	Point start_;
	Point end_;
	Point dim_;

private:
	void loadme(File& in);
	void saveme(const File& out) const;

	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);

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

private:
	MCT_DEF
};
}
#endif // !defined(AFX_ANGLE_DIMENSION_H__C864DE35_556A_48B9_A817_F6042157F0C0__INCLUDED_)
