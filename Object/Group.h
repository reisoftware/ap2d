
#if !defined _GROUP_H_
#define _GROUP_H_


#include "Entity.h"
#include <vector>

namespace dlhml{

class Entity_ID;
class Database;

class OBJECT_API Group  : public Entity
{
	MY_DECLARE_DYNCREATE(Group)
public:
	Group();
	virtual ~Group();


	Group(const Group& rhs);
	Group& operator=(const Group& rhs);
	void push_back_id(const Entity_ID& id);
	bool pt_in(const Point& pt) const;

	EntityIDArray::iterator begin();
	EntityIDArray::iterator end();
	bool remove(Entity_ID id);

	void transformby_ent_selected();

	bool visit(Visitor& v);
private:
	Database* private_db_;
	EntityIDArray ids_;
	mutable Entity* selected_;

private:
	void loadme(File& in);
	void saveme(const File& out) const;
	
	void get_strme(char *out){;}
	void set_from_strme(char *in){;}

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
	MCT_DEF
};

}

#endif