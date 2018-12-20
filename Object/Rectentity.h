// Rectentity.h: interface for the Rectentity class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_RECTENTITY_H__F526165E_89C2_449E_B59F_EB027A4DAA4B__INCLUDED_
#define AFX_RECTENTITY_H__F526165E_89C2_449E_B59F_EB027A4DAA4B__INCLUDED_

#include "Entity.h"
#include "Rect.h"

namespace dlhml{
class Line;
class OBJECT_API Rectentity : public Entity
{
	MY_DECLARE_DYNCREATE(Rectentity)
public:
	Rectentity();
	Rectentity(const Rectentity& rhs);
	Rectentity& operator=(const Rectentity& rhs);
	virtual ~Rectentity();

	void rect(const Rect& rc)				{rect_=rc;}
	Rect rect() const								{return rect_;}

	void get_point(Point (&pt)[4]) const;
	void get_line(Line (&line)[4]) const;

	bool visit(Visitor& v);

private:
	Rect rect_;

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

	Entity* cloneme() const;

	void closeme();

	bool intersectme(const Rect& rect) const;
	bool envelopme(const Rect& rect) const;

	Rect calc_box2d() const;

	bool snap_endpointme(Point& pt,const Rect& rect) const;
	bool snap_middle_pointme(Point& pt,const Rect& rect) const;
	bool snap_nearest_pointme(Point& pt,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_RECTENTITY_H__F526165E_89C2_449E_B59F_EB027A4DAA4B__INCLUDED_)
