// Line.h: interface for the Line class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_LINE_H__E85DCD39_5EE2_4532_863D_9945D04DEA4B__INCLUDED_
#define AFX_LINE_H__E85DCD39_5EE2_4532_863D_9945D04DEA4B__INCLUDED_

#include "Entity.h"
#include "Point.h"

#include "Text.h"

namespace dlhml{

	
	
class OBJECT_API Line : public Entity
{
	MY_DECLARE_DYNCREATE(Line)
public:
	Line();
	Line(const Point& st,const Point& ed);
	Line(const Line& rhs);
	Line& operator=(const Line& rhs);
	virtual ~Line();

public:
  virtual void intersectme(const Entity& e , std::vector<Point>& pts)const;
  virtual void intersectme(const Line  & ln, std::vector<Point>& pts)const;
  virtual void intersectme(const RArc  & ac, std::vector<Point>& pts)const;
  virtual void intersectme(const Circle& cr, std::vector<Point>& pts)const;
  //virtual bool intersectme(const Cloud_Line& cl, std::vector<Point>& pts)const;

public:
  virtual bool is_ortho(){return true;}
public:
  virtual void extend(const Line& ln);
  virtual void trim  (const Line& ln);
  virtual void split (const Line& ln , std::vector<Entity*>& os)const;
	virtual void split (int num, Float dis, std::vector<Entity*>& os)const;

//   virtual void lua_load(iLua_File &fin);
// 	virtual void lua_save(oLua_File &fout)const;
public:
	Float	length_to_nor(const Normal& nor) const;
	Float	length_by_way(const Normal& nor) const;

public:
  Point middle()const;
  Line  reverse()const;

	void	setdata(const Point& st,const Point & ed);
	void	setdata(const Point& st,const Normal& ed);

	void	start(const Point& pt) {st_ = pt;}
	Point	start() const {return st_;}
	void	end(const Point& pt)  {ed_ = pt;}
	Point	end() const {return ed_;}
	Float distanceto(const Point& pt) const;
	Float distanceto2d(const Point& pt) const;

	int get_start_arrow_line_show(std::vector<Line*>& lines) const;
	int get_end_arrow_line_show(std::vector<Line*>& lines) const;
	void arrow_pos(int pos);
	int arrow_pos() const	{return arrow_pos_;}
	void arrow_size(float size){arrowsize_ = size;}
	float arrow_size(){return arrowsize_;}

	bool visit(Visitor& v);

  bool is_in_line(Point pt)const;
  bool is_in_rayline(Point pt)const;
  bool is_in_segline(Point pt)const;

  Point perpendicular(const Point& pt);

  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;
  virtual void setstrech(const std::vector<Point>& pts);
  virtual void getstrech(std::vector<Point>& pts) const;

public:
  virtual void set2d();

protected:
  virtual Point focus()const{return middle();}
//public:
//  virtual void moveto(const Point& pt);
  //virtual Point focus()   const{return middle();}
  //virtual void  focus(Point pt){}

protected:
	virtual Float	length_p()const{return st_.distanceto(ed_);}
	virtual Float	length_p(const Normal& nor) const;
  virtual Point polarTo_p(Float len, bool orderway=true)const;

private:
	Point st_;
	Point ed_;

private:
  int arrow_pos_;
	float arrowsize_;
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
	bool snap_middle_pointme(Point& pt,const Rect& rect) const;
	bool snap_nearest_pointme(Point& pt,const Rect& rect) const;
	bool snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const;
	//bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

	//
	void create_arrow(Normal nor,Point arrow_pos,std::vector<Line*>& lines)const;
private:
	MCT_DEF
};
}
#endif//FILE


