#ifndef _TIAN_OBJECT_LINE_ARROW_H_
#define _TIAN_OBJECT_LINE_ARROW_H_

#include "Dimension.h"
#include "Line.h"

namespace dlhml{

	
	
class OBJECT_API Line_Arrow : public Dimension
{
	MY_DECLARE_DYNCREATE(Line_Arrow)

public:
	Line_Arrow();
  Line_Arrow(const Line & ln);
	Line_Arrow(const Point& st,const Point& ed);
  Line_Arrow(const Line_Arrow& rhs);
  Line_Arrow& operator=(const Line_Arrow& rhs);
	virtual ~Line_Arrow();

public:
  bool visit(Visitor& v);

public:
  void	setdata(const Line & ln);
  void  getdata(Line & ln) const;
  void	setdata(const Point& st,const Point & ed);
  void	start(const Point& pt)    {ln_.start(pt);}
  void	end  (const Point& pt)    {ln_.end  (pt);}
  Point	start()const              {return ln_.start();}
  Point	end  ()const              {return ln_.end  ();}

public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;
  virtual void setstrech(const std::vector<Point>& pts);
  virtual void getstrech(std::vector<Point>& pts) const;

public:
  virtual bool is_ortho(){return true;}
public:
  virtual void extend(const Line& ln);
  virtual void trim  (const Line& ln);
  virtual void split (const Line& ln , std::vector<Entity*>& os)const;

public:
  virtual void get_line(std::vector<Entity*>& es)const;
  virtual void get_show(std::vector<Entity*>& es)const;

protected:
  virtual Point focus()const{return ln_.middle();}

protected:
	virtual Float	length_p()const{return ln_.length();}
	virtual Float	length_p(const Normal& nor) const;
  virtual Point polarTo_p(Float len, bool orderway=true)const;

protected:
  //virtual void intersectme(const Entity& e , std::vector<Point>& pts)const;
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l) ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);


private:
	virtual void loadme(File& in);
	virtual void saveme(const File& out) const;
	virtual void edit_propertyme(const Edit_Entity& edit);
	//virtual void drawme(Draw_Entity& out) const;
	//virtual void xor_drawme(Draw_Entity& out) const;
	virtual void transformbyme(const Matrix& mat);
  virtual void drag_startme(const Matrix& mat);
  virtual void drag_endme(const Matrix& mat);
	virtual void closeme();
	virtual bool intersectme(const Rect& rect) const;
	virtual bool envelopme(const Rect& rect) const;
	virtual Rect calc_box2d() const;
  virtual Entity* cloneme() const;
  virtual errorinfo postme2db(Database& db,Entity_ID& id);

private:
	virtual bool snap_endpointme(Point& pt,const Rect& rect) const;
	virtual bool snap_middle_pointme(Point& pt,const Rect& rect) const;
	virtual bool snap_nearest_pointme(Point& pt,const Rect& rect) const;
	virtual bool snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const;
//virtual bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	virtual bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

private:
  Line ln_;
private:
	MCT_DEF
};

}//namespace

#endif//FILE
 
