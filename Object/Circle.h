// Circle.h: interface for the Circle class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_CIRCLE_H__AA83AB73_3393_41FF_B729_46B16D929B5C__INCLUDED_
#define AFX_CIRCLE_H__AA83AB73_3393_41FF_B729_46B16D929B5C__INCLUDED_

#include "Entity.h"
#include "Point.h"

namespace dlhml{
class OBJECT_API Circle : public Entity
{
	MY_DECLARE_DYNCREATE(Circle)
public:
	Circle();
	Circle(const Circle& rhs);
	Circle(const Point& c,Float r);
	Circle& operator=(const Circle& rhs);
  bool operator==(const Circle& r)const;
	virtual ~Circle();
  //virtual set_draw_center(bool& draw_c, Point& c)const{draw_c=true;c=center_;}

public:
  virtual void intersectme(const Entity& e , std::vector<Point>& pts)const;
  virtual void intersectme(const Line  & ln, std::vector<Point>& pts)const;
  virtual void intersectme(const RArc  & ac, std::vector<Point>& pts)const;
  virtual void intersectme(const Circle& cr, std::vector<Point>& pts)const;
  //virtual bool intersectme(const Cloud_Line& cl, std::vector<Point>& pts)const;
	
  
public:
  virtual Float length()const;

public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;

  void setdata(const Point& center,Float r){
		center_ = center;
		radius_ = r;
	}
	void center(const Point& center) { center_ = center;}
	Point center() const  {return center_;}
	void radius(Float r)   {radius_ = r;}
	Float radius() const  {return radius_;}
  void radius(const Point& pt);

	bool visit(Visitor& v);
protected:
  virtual Point focus()const{return center_;}

private:
	Float		radius_;
	Point		center_;

private:
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;

	
	void get_strme(char *out);
	void set_from_strme(char *in);

	void loadme(File& in);
	void saveme(const File& out) const;

//	void lua_load(iLua_File &fin);
//	void lua_save(oLua_File &fout)const;
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

	bool snap_center_pointme(Point& pt,const Rect& rect) const;
	bool snap_nearest_pointme(Point& pt,const Rect& rect) const;
	//bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_CIRCLE_H__AA83AB73_3393_41FF_B729_46B16D929B5C__INCLUDED_)
