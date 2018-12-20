#ifndef _LINE_H_
#define _LINE_H_
#include "pt3d.h"
#include "segment.h"
class CPlane;
class AFX_EXT_CLASS Line:public Segment{
  CPt3D start_;
  CPt3D end_;
public:
  Line();
  Line(CPt3D start,CPt3D end);
		
  int do_it(Visitor_Segment& v);
  void release();

  CPt3D mid();
  void Serialize(CArchive& ar);

  CPt3D get_start() const { return start_;}
  CPt3D get_end() const { return end_;}
  void set_start(const CPt3D& pt) { start_ = pt;}
  void set_end(const CPt3D& pt) { end_ = pt;}
  Line parallel(const CPlane& plane,double dis) const;
  CPt3D intersect(const Line& line) const;
  CPt3D perpendculiar(CPt3D pt) const;
};
#endif
