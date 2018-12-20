// Entity_Snap.h: interface for the Entity_Snap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_ENTITY_SNAP_H__73EDCA9A_6440_4807_AB09_BFA697C8BC72__INCLUDED_
#define AFX_ENTITY_SNAP_H__73EDCA9A_6440_4807_AB09_BFA697C8BC72__INCLUDED_

#include "export.h"
#include "../afc/counter.h"

namespace dlhml{
class Point;
class Rect;
class Line;
class Line_Arrow;
class Circle;
class RArc;
class Text;
class Cloud_Line;
class Text_Dimension;
class Lead_Dimension;
class Lead_Dimension_MT;
class Three_Pt_Dimension;
class Ln_Dim;
class Angle_Dimension;
class Radius_Dimension;
class Lead_Dimension_Info;
class Text_Dimension_Info;
class Ln_Dim_PlateSide;
class Ln_Dim_Direct;
class Lead_Name;
//
//class Line_Dim;

class OBJECT_API Entity_Snap
{
public:
	Entity_Snap();
	virtual ~Entity_Snap();

	virtual bool intersect(Point& pt,const Rect& rect,const Line& line) const = 0;
  virtual bool intersect(Point& pt,const Rect& rect,const Line_Arrow& la) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Circle& circle) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const RArc& arc) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Text& text) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Cloud_Line& cloud) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Text_Dimension& dim) const = 0;
	virtual bool intersect(Point& Pt,const Rect& rect,const Lead_Dimension& dim) const = 0;
	virtual bool intersect(Point& Pt,const Rect& rect,const Lead_Dimension_MT& dim) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Three_Pt_Dimension& dim) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Ln_Dim& dim) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Angle_Dimension& dim) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Radius_Dimension& dim) const = 0;

	virtual bool intersect(Point& pt,const Rect& rect,const Lead_Dimension_Info& dim) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Lead_Name& dim) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Text_Dimension_Info& dim) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Ln_Dim_PlateSide& dim) const = 0;
	virtual bool intersect(Point& pt,const Rect& rect,const Ln_Dim_Direct& dim) const = 0;
  //
//	virtual bool intersect(Point& pt,const Rect& rect,const Line_Dim& lndim) const = 0;
private:
	MCT_DEF
};
}
#endif // !defined(AFX_ENTITY_SNAP_H__73EDCA9A_6440_4807_AB09_BFA697C8BC72__INCLUDED_)
