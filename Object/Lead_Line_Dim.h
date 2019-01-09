// Lead_Line_Dim.h: interface for the Lead_Line_Dim class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEAD_LINE_DIM_H__80E0673D_A652_43D0_93CE_A1E3DC3C9576__INCLUDED_)
#define AFX_LEAD_LINE_DIM_H__80E0673D_A652_43D0_93CE_A1E3DC3C9576__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dimension.h"


namespace dlhml{
class Line;

class OBJECT_API Lead_Line_Dim : public Dimension  
{
	MY_DECLARE_DYNCREATE(Lead_Line_Dim)
public:
	Lead_Line_Dim();
	Lead_Line_Dim(const Lead_Line_Dim& rhs);
	Lead_Line_Dim& operator=(const Lead_Line_Dim& rhs);
	virtual ~Lead_Line_Dim();

public:
	void  start_pt_rect(const Rect& rc)	{start_pt_rect_=rc;}
	Rect  start_pt_rect() const					{return start_pt_rect_;}

public:
	void	setdata(const Point& st,const Point& ed);

	void  start(const Point& st);
	Point start()const;
  void  end(const Point& ed);
  Point end()const;

public:
	void lead(bool b){lead_ = b;}
	bool lead() const{return lead_;}


public:
	bool get_line(Line& line) const;

public:
  virtual void get_line(std::vector<Entity*>& es)const;
  virtual void get_show(std::vector<Entity*>& es)const;

  void get_line_show(Line& ln)const;
	int  get_start_arrow_line_show  (std::vector<Line   *>& lines   ) const;
	int  get_start_arrow_circle_show(std::vector<Circle *>& circles ) const;

	void get_str_sub(char *name);
	void set_from_str_sub(char *name);

public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;

public:
	bool start_in_rect() const;
	//8.14
	Rect get_txt_rect();
	Point get_range_pt();

	Color color_fact(){return color_fact_;}
	void color_fact(Color color){color_fact_=color;}

	bool visit(Visitor& v);

	//09.6.22
	void dim_sign(LPCTSTR dim_sign);
	LPCTSTR dim_sign() const;

private:
	Point start_;
	Rect start_pt_rect_;
	Color color_fact_;
	//09.8.26
  LPTSTR	dim_sign_;
	bool lead_;

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

	//Rect calc_box2d() const;

	bool snap_endpointme(Point& pt,const Rect& rect) const;
	bool snap_middle_pointme(Point& pt,const Rect& rect) const;
	bool snap_nearest_pointme(Point& pt,const Rect& rect) const;
	//bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;
};


}
#endif // !defined(AFX_LEAD_LINE_DIM_H__80E0673D_A652_43D0_93CE_A1E3DC3C9576__INCLUDED_)
