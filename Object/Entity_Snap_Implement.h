// Entity_Snap_Implement.h: interface for the Entity_Snap_Implement class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_ENTITY_SNAP_IMPLEMENT_H__34E63A5A_5350_4C12_8172_87C4FF234D29__INCLUDED_
#define AFX_ENTITY_SNAP_IMPLEMENT_H__34E63A5A_5350_4C12_8172_87C4FF234D29__INCLUDED_

#include "Entity_Snap.h"

namespace dlhml{
template<typename T> 
class Entity_Snap_Implement : public Entity_Snap
{
public:
	explicit Entity_Snap_Implement(const T& t):t_(t){}
	~Entity_Snap_Implement(){}

	bool intersect(Point& pt,const Rect& rect,const Line  & line  ) const;
	bool intersect(Point& pt,const Rect& rect,const RArc  & arc   ) const;
	bool intersect(Point& pt,const Rect& rect,const Circle& circle) const;
//	bool intersect(Point& pt,const Rect& rect,const Text& text) const;
//	bool intersect(Point& pt,const Rect& rect,const Cloud_Line& cloud) const;
//	bool intersect(Point& pt,const Rect& rect,const Text_Dimension& dim) const;
//	bool intersect(Point& Pt,const Rect& rect,const Lead_Dimension& dim) const;
//	bool intersect(Point& pt,const Rect& rect,const Three_Pt_Dimension& dim) const;
//	bool intersect(Point& pt,const Rect& rect,const Ln_Dim& dim) const;
//	bool intersect(Point& pt,const Rect& rect,const Angle_Dimension& dim) const;
//	bool intersect(Point& pt,const Rect& rect,const Radius_Dimension& dim) const;
  //
	//bool intersect(Point& pt,const Rect& rect,const Line_Dim& dim) const;
private:
	const T& t_;
private:
	MCT_DEF
};
}
#endif // !defined(AFX_ENTITY_SNAP_IMPLEMENT_H__34E63A5A_5350_4C12_8172_87C4FF234D29__INCLUDED_)
