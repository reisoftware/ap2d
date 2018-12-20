
#ifndef _TIAN_OBJCET_ARC_H_
#define _TIAN_OBJCET_ARC_H_

#include "Entity.h"
#include "Point.h"
#include "../geometry/Arc.h"

namespace dlhml{
class OBJECT_API RArc : public Entity
{
	MY_DECLARE_DYNCREATE(RArc)
public:
	RArc();
  virtual ~RArc();

public:
  void set(const geo::Arc& o);
  void set(const Point& pt1, const Point& pt2, const Point& pt3);
  void set(const Point& c, const Point& s, const Point& e, const Point& p);
  void set_radian2d(const Point& c, Float r, Float srad, Float erad);
  void set_degree2d(const Point& c, Float r, Float sdeg, Float edeg);

public:
  void center(const Point& pt);
  void radius(Float r);
  void start(const Point& pt);
  void path(const Point& pt);
  void end(const Point& pt);

public:
  geo::Arc get()const;

public:
  Point center()const; ////圆心
  Float radius()const; ////半径
  
public:
  Float radian()const;  ////张开角度
  Float degree()const;  ////张开角度
  
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

	void get_str_sub();
	void set_from_str_sub();

  // public:
// 	Point start()const{return get_start_pt();}
// 	Point end()const{return get_end_pt();}
// public:
//   void  set_start_pt(const Point& pt);
//   void  set_path_pt(const Point& pt);
//   void  set_end_pt(const Point& pt);
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
// 	void  center(const Point& c);
// 	Point center() const;
// 	void  radius(Float r);
// 	Float radius() const;
// 	void  start_degree(Float a);
// 	Float start_degree() const;
// 	void  end_degree(Float a);
// 	Float end_degree() const;
// 	void  start_radian(Float a);
// 	Float start_radian() const;
// 	void  end_radian(Float a);
// 	Float end_radian() const;


// private:
// 	Float		radius_;
// 	Float		start_degree_;   //degree
// 	Float		end_degree_;
// 	Point		center_;
// private:
//   Point pt1_;
//   Point pt2_;
//   Point pt3_;

private:
  geo::Arc arc_;

private:
	void loadme(File& in);
	void saveme(const File& out) const;

	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);

	void edit_propertyme(const Edit_Entity& edit);

	void drawme(Draw_Entity& out) const;
	void xor_drawme(Draw_Entity& out) const;

	errorinfo postme2db(Database& db,Entity_ID& id);

	void transformbyme(const Matrix& mat);
	void drag_startme(const Matrix& mat);
	void drag_endme(const Matrix& mat);

	Entity* cloneme() const;

	void closeme();

	bool intersectme(const Rect& rect) const;
	bool envelopme(const Rect& rect) const;

	Rect calc_box2d() const;

	bool snap_endpointme(Point& pt,const Rect& rect) const;
	bool snap_center_pointme(Point& pt,const Rect& rect) const;
  bool snap_nearest_pointme(Point& pt,const Rect& rect)const;
  bool snap_middle_pointme(Point& pt,const Rect& rect)const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

public:
  virtual void intersectme(const Entity& e , std::vector<Point>& pts)const;
  virtual void intersectme(const Line  & ln, std::vector<Point>& pts)const;
  virtual void intersectme(const RArc  & ac, std::vector<Point>& pts)const;
  virtual void intersectme(const Circle& cr, std::vector<Point>& pts)const;
  
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
  
  // 	virtual void lua_load(iLua_File &fin);
  // 	virtual void lua_save(oLua_File &fout)const;
public:
  bool visit(Visitor& v);
  

// private:
//   void init_pt();
//   void init_other();
//   void init_other(const Point& pt1,const Point& pt2,const Point& pt3);
//   void set_3_pt(const Point& pt1,const Point& pt2,const Point& pt3);
// 	bool is_sort(double asin1, double asin2, double asin3)const;

// private:
//   bool is_in(Float degree)const;

	
private:
	MCT_DEF
};
}
#endif//FILE

