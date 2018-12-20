#ifndef _HBEAM_CUT_H_
#define _HBEAM_CUT_H_
class CGePlate;
class CMember;
class CPlane;
#include "pt3d.h"
class AFX_EXT_CLASS HBeam_Cut{
public:
  enum Edge{start = 0,end,nil};
  enum BK{one = 0,two,three};
private:
  Edge edge_;
  double d1_;
  double d2_;
  double a_;
  double b_;
  double ra_;
  double rb_;
  double h1_;
  double h2_;
  BK up_bk_;
  BK bottom_bk_;

  CPt3D polar_to(const CPt3D& start,const CPt3D& end,double len) const;

public:
  HBeam_Cut();
  void set_d(double d1,double d2);
  void set_edge(Edge edge);
  void set_a(double a) { a_ = a;}
  void set_b(double b) { b_ = b;}
  void set_ra(double ra) { ra_ = ra;}
  void set_rb(double rb) { rb_ = rb;}
  void set_h1(double h1) { h1_ = h1;}
  void set_h2(double h2) { h2_ = h2;}
  void set_up_bk(BK bk) { up_bk_ = bk;}

  BK get_up_bk() const { return up_bk_;}
  BK get_bottom_bk() const {return bottom_bk_;}

  double get_a() const {return a_;}
  double get_b() const {return b_;}
  double get_ra() const {return ra_;}
  double get_rb() const {return rb_;}
  double get_h1() const { return h1_;}
  double get_h2() const { return h2_;}
  double get_d1() const { return d1_;}
  double get_d2() const { return d2_;}
  Edge get_edge() const { return edge_;}

  void set_bottom_bk(BK bk) { bottom_bk_ = bk;}
  BOOL is_null() const;

  void init(CMember& member,CPlane& plane);
  BOOL edit();

  void Serialize(CArchive& ar);

  void save();
  void load();
};
#endif
