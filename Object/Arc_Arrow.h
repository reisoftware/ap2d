
#ifndef _TIAN_OBJCET_ARC_ARROW_H_
#define _TIAN_OBJCET_ARC_ARROW_H_

#include "Dimension.h"
#include "RArc.h"

namespace dlhml{
class OBJECT_API Arc_Arrow : public Dimension
{
	MY_DECLARE_DYNCREATE(Arc_Arrow)
public:
	Arc_Arrow();
	Arc_Arrow(const RArc& ac);
	virtual ~Arc_Arrow();

public:
  void set(const Point& pt1, const Point& pt2, const Point& pt3);
  void set(const Point& c, const Point& s, const Point& e, const Point& p);
  void set_radian2d(const Point& c, Float r, Float srad, Float erad);
  void set_degree2d(const Point& c, Float r, Float sdeg, Float edeg);
  
public:
  void center(const Point& c);
  void radius(Float r);
  void start(const Point& pt);
  void path(const Point& pt);
  void end(const Point& pt);

public:
  RArc get()const;
  
public:
  Point center()const; ////圆心
  Float radius()const; ////半径
  
public:
  Float radian()const;  ////张开角度
  Float degree()const;  ////张开角度
  
public:
  Float start_radian2d()const;
  Float start_degree2d()const;
  
public:
  Float end_radian2d()const;
  Float end_degree2d()const;
  
public:
  Float middle_radian2d()const;
  Float middle_degree2d()const;
  
public:
  Point middle()const;
  Point start()const;
  Point path()const;
  Point end()const;
  
public:
  Point middle2d()const;
  Point start2d()const;
  Point path2d()const;
  Point end2d()const;

// public:
//   void  set_start_pt(const Point& pt);
//   void  set_path_pt(const Point& pt);
//   void  set_end_pt(const Point& pt);
//   void  getdata(RArc& ac)const;
//   void  getdata(Point& pt1,Point& pt2,Point& pt3)const;
// 	void  get_end_point(Point& st,Point& ed) const;
//   Point get_middle_pt()const;
//   Point get_start_pt()const;
//   Point get_path_pt()const;
//   Point get_end_pt()const;
// public:
// 	bool setdata(const Point& start,const Point& path,const Point& end);
// 	void setdata(const Point& c,const Point& st,const Point& ed,const Point& path);
// 	void setdata(const Point& c,Float r,Float st_degree,Float ed_degree);
// 	void  center(const Point& c)		    ;
// 	Point center() const								{return arc_.center();}
// 	void  radius(Float r) 							;
// 	Float radius() const								{return arc_.radius();}
// 	void  start_degree2d(Float a)			    ;
// 	Float start_degree2d() const					{return arc_.start_degree2d();}
// 	void  end_degree2d(Float a)				    ;
// 	Float end_degree2d() const						{return arc_.end_degree2d();}
// 	void  start_radian2d(Float a)			    ;
// 	Float start_radian2d() const					{return arc_.start_radian2d();}
// 	void  end_radian2d(Float a)				    ;
// 	Float end_radian2d() const						{return arc_.end_radian2d();}

public:
  bool visit(Visitor& v);

private:
  RArc arc_;

private:
	void open_luame(lua_State *l) ;
	void save_luame(std::ofstream &out,int tab_num);

	
	void get_strme(char *out);
	void set_from_strme(char *in);

	void loadme(File& in);
	void saveme(const File& out) const;
	void edit_propertyme(const Edit_Entity& edit);
	//void drawme(Draw_Entity& out) const;
	//void xor_drawme(Draw_Entity& out) const;
	void transformbyme(const Matrix& mat);
	void drag_startme(const Matrix& mat);
	void drag_endme(const Matrix& mat);
	void closeme();
	bool intersectme(const Rect& rect) const;
	bool envelopme(const Rect& rect) const;
	Rect calc_box2d() const;
  Entity* cloneme() const;
  errorinfo postme2db(Database& db,Entity_ID& id);

	bool snap_endpointme(Point& pt,const Rect& rect) const;
	bool snap_center_pointme(Point& pt,const Rect& rect) const;
  bool snap_nearest_pointme(Point& pt,const Rect& rect)const;
  bool snap_middle_pointme(Point& pt,const Rect& rect)const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

public:
  ////得到其构成的基本线条（LINE/ARC/CIRCLE）
  virtual void get_line(std::vector<Entity*>& es)const;
  virtual void get_show(std::vector<Entity*>& es)const;
  
public:
  //virtual void intersectme(const Entity& e , std::vector<Point>& pts)const;
  
protected:
  virtual Float	length_p()const;
  virtual Float	length_p(const Normal& nor) const;
  virtual Point polarTo_p(Float len, bool orderway=true)const;
public:
  virtual Point focus()   const{return middle();}
public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;


	
private:
	MCT_DEF
};
}
#endif//FILE

