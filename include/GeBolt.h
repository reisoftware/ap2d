#ifndef _GEBOLT_H_
#define _GEBOLT_H_
#include "pt3d.h"
class Jnt_Axis;
namespace apcad{
  class Polygon;
  class Transform_Base;
}
class CPlane;
class CGeAxis;
const int MAX_VERTEX = 8;
class AFX_EXT_CLASS CGeBolt  
{
private:
	
  CPt3D start_;
  CPt3D end_;
  double dia_;
  double hole_dia_;
  CString type_;//8T,4T,10TµÈ
  int jnt_index_;
	
public:
  CGeBolt();
  ~CGeBolt();

  int get_jnt_index() const { return jnt_index_;}
  void set_jnt_index(int index) { jnt_index_ = index;}
  void set_start(CPt3D pt) { start_ = pt;}
  void set_hole(double hole_d) { hole_dia_ = hole_d;}
  void set_diameter(double d) { dia_ = d;}
  void set_type(CString type) { type_ = type;}
  void set_pt(const CPt3D& pt,const CGeNorm& norm);
	 
  double get_diameter() const { return dia_;}
  CPt3D get_cen() const;
  double get_len() const;
  CString get_type() const { return type_;}
  double get_hole() const { return hole_dia_;}
  void Serialize(CArchive &ar);
  void draw_2d_c(CPlane& plane,CGeAxis* axis);
  void draw_2d_r(CPlane& plane,CGeAxis* axis);
  void draw_2d_cross(CPlane& plane,CGeAxis* axis);
  void draw_center(CPlane& plane,vector<CPt3D>& pts);
  apcad::Polygon get_polygon(const CGeAxis& axis) const;

  void transform(apcad::Transform_Base& transform_base);
		
  void l2g(Jnt_Axis* axis);
  void g2l(Jnt_Axis* axis);
};

typedef vector<CGeBolt> CGeBoltVector;
#endif
