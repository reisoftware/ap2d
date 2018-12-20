// Block.h: interface for the Block class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_BLOCK_H__EB0555E1_6D88_478B_BE55_96593B4CE112__INCLUDED_
#define AFX_BLOCK_H__EB0555E1_6D88_478B_BE55_96593B4CE112__INCLUDED_

#include <vector>
#include "Entity.h"
#include "Point.h"

namespace dlhml{
class Entity_ID;
class Database;
class OBJECT_API Block : public Entity
{
	MY_DECLARE_DYNCREATE(Block)
public:
	Block();
	Block(const Block& rhs);
	Block& operator=(const Block& rhs);
	virtual ~Block();

	virtual Float length()const;

	void push_back(Entity* ent);
	void push_back_id(const Entity_ID& id);
  virtual Point focus()   const{return focus_;}
  virtual void  focus(Point pt){focus_ = pt  ;}
  virtual void get_show(std::vector<Entity*>& lns)const;

//public:
//  virtual void moveto(const Point& pt);
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;

protected:
  virtual void get_ptr_p(std::vector<Entity*>& ptrs);
  void			color_index(int index);


public:
	Entity* front();
	Entity* back();
	bool erase(Entity* ent);
	bool remove(Entity* ent);

	Entity* next(const Entity* pos);
	int size() const;

	bool pt_in(const Point& pt) const;

	bool visit(Visitor& v);

	virtual void selected(bool select);
	virtual bool selected()const			;

//protected:
//  virtual void moveto_p(const Point& pt);


private:
  Point focus_;

private:
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;

	
	void get_strme(char *out){;}
	void set_from_strme(char *in){;}

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

	bool snap_endpointme(Point& pt,const Rect& rect) const;
	bool snap_center_pointme(Point& pt,const Rect& rect) const;
	bool snap_middle_pointme(Point& pt,const Rect& rect) const;
	bool snap_nearest_pointme(Point& pt,const Rect& rect) const;
	bool snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const;
	bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

private:
#pragma warning(push)
	#pragma warning(disable:4251)
	std::vector<Entity*> list_;
#pragma warning(pop)

	Database* private_db_;

	//mutable Entity* selected_;

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_BLOCK_H__EB0555E1_6D88_478B_BE55_96593B4CE112__INCLUDED_)
