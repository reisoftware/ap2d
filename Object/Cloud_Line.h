// Cloud_Line.h: interface for the Cloud_Line class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_CLOUD_LINE_H__AE9FFD70_F9C4_4CBD_B3A8_DEACF02D396E__INCLUDED_
#define AFX_CLOUD_LINE_H__AE9FFD70_F9C4_4CBD_B3A8_DEACF02D396E__INCLUDED_

#pragma warning (disable : 4251)

#include "Entity.h"
#include "Point.h"
#include <vector>
#include <vector>
#include "Line.h"

namespace dlhml{

//enum CLOUD_MODE {ARC_CLOSED, LINE_OPEN, LINE_CLOSED};
//const int ARC_OPEN   = 100;
const int ARC_CLOSED = 100;
const int LINE_OPEN  = 102;
const int LINE_CLOSED= 103;
const int RECT_CLOSED= 110;

const int MAX_PT_COUNT = 100;

class OBJECT_API Cloud_Line : public Entity
{
	MY_DECLARE_DYNCREATE(Cloud_Line)
public:
	Cloud_Line();
	Cloud_Line(const Cloud_Line& rhs);
	Cloud_Line& operator=(const Cloud_Line& rhs);
	virtual ~Cloud_Line();
public:
	bool visit(Visitor& v);

public:
  Float x_length()const;
  Float y_length()const;
  void  rect_plate(Float xlen, Float ylen);
protected:
	virtual Float length_p()const;
  virtual Float length_p(const Normal& nor)const;
  virtual Float area_min_rect_p()const;
  virtual Float area_min_rect_p(const Normal& nor)const;


public:
	void setdata(const std::vector<Point>& pts);
	void getdata(std::vector<Point>& pts) const{pts=pts_;}
public:
  virtual Point focus()const;
  virtual int  pt_count()const;
protected:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;
  virtual void setstrech(const std::vector<Point>& pts);
  virtual void getstrech(std::vector<Point>& pts) const;

protected:
  virtual void intersectme(const Entity& e , std::vector<Point>& pts)const;
  virtual void intersectme(const Line  & ln, std::vector<Point>& pts)const;
  virtual void intersectme(const RArc  & ac, std::vector<Point>& pts)const;
  virtual void intersectme(const Circle& cr, std::vector<Point>& pts)const;

public:
	void open(bool b){open_ = b   ;box_change(true);}
	bool open()const {return open_;}
	void line(bool b){line_ = b   ;box_change(true);}
	bool line()const {return line_;}
  bool rect(){return rect_;}
  void rect(bool b);

public:
  void get_show(std::vector<Entity*>& lns)const;
	void get_lines(std::vector<Entity*>& lns)const;

public:
  void salience(int sal){salience_=sal   ;}
  int  salience()const  {return salience_;}

private:
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;

	
	void get_strme(char *out);
	void set_from_strme(char *in);

	void loadme(File& in);
	void saveme(const File& out) const;

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

	bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

  bool snap_endpointme(Point& pt,const Rect& rect)const;
  bool snap_middle_pointme(Point& pt,const Rect& rect)const;
  bool snap_nearest_pointme(Point& pt,const Rect& rect)const;

	std::vector<Point> pts_;
  int salience_;          ////»¡ÏßÍ¹Æð(5:Í¹Æð°ë¾¶)

private:
  void         setat(int i,const Point& pt);
  const Point& getat(int i)const;

  Point get_path_pt(const Point& st, const Point& ed)const;

private:
  void reset_rect_by_side(int index, const Point& pt);
  void reset_rect(int index, const Point& pt);
  void reset_rect();

private:
	bool open_;   //OPEN/CLOSED
  bool line_;   //LINE/ARC
  bool rect_;   //std plate

private:
	MCT_DEF
};
}
#endif // !defined(AFX_CLOUD_LINE_H__AE9FFD70_F9C4_4CBD_B3A8_DEACF02D396E__INCLUDED_)
