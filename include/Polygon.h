#ifndef _POLYGON_H_
#define _POLYGON_H_
#include "pt4d.h"
#include <vector>
#include "geptr.h"

class Segment;
class Line;
class CArc;
class CGeNorm;
class CPlane;
class CGeAxis;
namespace apcad{
  class Transform_Base;
  class AFX_EXT_CLASS Polygon{
    std::vector<Pt4D> pts_;
		
  public:
    static BOOL line_frame;
    explicit Polygon(const std::vector<Pt4D>& pts);
    explicit Polygon(std::vector<Line>& lines);
    Polygon();
    ~Polygon();
    void get_pts(std::vector<CPt3D>& pts) const;
    std::vector<Pt4D> get_pts() const;
    void push_back(Pt4D pt);
    void push_back(const CPt3D& pt);
    unsigned int size() const;
    const Pt4D& operator[](unsigned int index) const;
    Pt4D& operator[](unsigned int index);
    void erase(unsigned int index);
    void clear();
		
    void insert(int index,const Pt4D& pt);
  public:
    Polygon operator -(const Polygon& polygon) const;
  public:	
    int draw_line_frame() const;
    int pick(const CPt3D& pt) const;
    void draw_boundary(CPlane& plane,vector<CPt3D>& sect_pts) const;
  public:
    void offset(int index,const CPt3D& pt);
    void move_to(double len,const CGeNorm& normal);
    void transform(Transform_Base& transform_base);
    void reverse();

    CGeNorm get_normal() const;
    CGeAxis get_axis() const;
  public:
    CPt3D perpendicular(const CPt3D& pt) const;
    bool intersect(const Polygon& rhs,Line& line) const;
    int intersect(const Line& line,CPt3D& pt) const;
  public:
    std::vector< GEXY::CPtr<Segment> > get_segments() const;
  public:
    void Serialize(CArchive& ar);
  };
  void draw_arrow_line(const CPt3D& start,const CPt3D& end,const CGeNorm& norm);
}
#endif
