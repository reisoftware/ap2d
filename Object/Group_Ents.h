#if !defined _GROUP_ENTS_H_
#define _GROUP_ENTS_H_


#include "Entity.h"

namespace dlhml{

class Entity_ID;
class Database;
class Paint_Entity;

#pragma warning (disable : 4251)
#pragma warning (disable : 4786)


class OBJECT_API Group_Ents : public Entity
{
	MY_DECLARE_DYNCREATE(Group_Ents)
public:
	Group_Ents();
	Group_Ents(const Group_Ents& rhs);
	~Group_Ents();

	Group_Ents& operator=(const Group_Ents& rhs);
	bool operator==(const Group_Ents& rhs);

public:
	void set_db(Database* db){db_=db;}

public:
	int	 entity_count()const;
	void push_back(Entity * e);
	void push_back(const Entity_ID& id);
	void push_back(const std::vector<Entity*>& es);
	void erase(const Entity * e);
	void clear();
	
	void setat(int i, Entity * e);
	Entity * getat(int i)const;
	Entity * operator[] (int i);
	const Entity * operator[] (int i) const;
	//int ids_count();
	//void push_back(const Entity_ID& id);
	//void push_back(const EntityIDArray& ids);

	void update_box2d();

public:
  //EntityIDArray::const_iterator begin()const{return ids_.begin();}
  //EntityIDArray::const_iterator end()const{return ids_.end();}
	//EntityIDArray::iterator begin(){return ids_.begin();}
	//EntityIDArray::iterator end(){return ids_.end();}
	
	//void delete_ids();
	
public:
	bool isin(const Point& pt)const;
	bool isin(const Entity* e)const;

public:

	//void add_selected(Paint_Entity & paint,std::vector<Entity*>& ents);
	//void show_ids(Paint_Entity & paint);


	//int id(){return id_;}
	//void id(int id){id_=id;}

public:
	virtual void selected(bool select);

private:
	Database* db_;

	//int id_;									////未知功能属性
	//EntityIDArray ids_;				////所属兰框的实体ID
	std::vector<Entity*> ents_;	////所属兰框的实体指针

	void get_strme(char *out){;}
	void set_from_strme(char *in){;}

private:
	void tramsfromby_content(const Matrix& mat);
	Rect box2d_content() const;

public:
  virtual Point focus()const;

  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;
  //virtual void setstrech(const std::vector<Point>& pts);
  //virtual void getstrech(std::vector<Point>& pts) const;

private:
	void get_lines(std::vector<Entity*>& lns)const;

private:
	//Float left_, right_, top_, bottom_;
	Point lt_;
	Point rb_;

private:
	bool visit(Visitor& v){return false;}

private:
	void loadme(File& in);
	void saveme(const File& out) const;

	void edit_propertyme(const Edit_Entity& edit);

	void drawme(Draw_Entity& out) const;
	void xor_drawme(Draw_Entity& out) const;

	errorinfo postme2db(Database& db,Entity_ID& id);

	void transformbyme(const Matrix& mat);
	void drag_startme(const Matrix& mat);
	void drag_endme(const Matrix& mat);

	Entity* cloneme() const;		////克隆自身时，其关联的ents_都会克隆

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
	MCT_DEF
};

}
#endif