// Normal.h: interface for the Normal class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_NORMAL_H__22841A58_7ED0_453A_9C28_B71CD92CC4A1__INCLUDED_
#define AFX_NORMAL_H__22841A58_7ED0_453A_9C28_B71CD92CC4A1__INCLUDED_
/*
* n = { A, B, C }
*/
//					   y//
//							//
//							//
//							//
//							//
//							//
//							//
//							///////////////////
//					   //				x
//					  //
//					 //
//					//z
//
//

#include "export.h"
#include "../afc/counter.h"

namespace dlhml{
class File;
class Line;
class Point;
class OBJECT_API Normal  
{
public:
  Normal():x_(0),y_(0),z_(0)MCT_INIT2("Normal"){}
  explicit Normal(const Point& pt);
  explicit Normal(const Line & ln);
  Normal(const Point& st, const Point& ed);
  Normal(Float xx,Float yy,Float zz):x_(xx),y_(yy),z_(zz)MCT_INIT2("Normal"){}
  ~Normal(){}
  
  //serialize
  void load(File& in);
  void save(const File& out) const;
  
  void set_x_axis_angle(Float radians){
    x_ = cos(radians);
    y_ = sin(radians);
    z_ = 0.0;
  }
  void set_data(Float xx,Float yy,Float zz){
    x_ = xx;
    y_ = yy;
    z_ = zz;
  }
  void set_data(const Point& pt);
  void set_data(const Line & ln);
  void set_data(const Point& st,const Point& ed);
  void set_unit(){
    Float dist = distance_to_zero();
    x_ /= dist;
    y_ /= dist;
    z_ /= dist;
  }
  //反向
  void set_reverse(){
    x_ = -x_;
    y_ = -y_;
    z_ = -z_;
  }
  Float dis_by_way(const Point& pt) const;
  Line  line()const;
  void rota_z(double degree);
  
public:
  bool   operator==(const Normal& rhs) const;
  bool   operator!=(const Normal& rhs) const;
  Normal operator* (const Normal& rhs) const;
  
public:
  bool is_zero_normal() const{
    return (EquFloat(x_,0.0) && EquFloat(y_,0.0) && EquFloat(z_,0.0));
  }
  bool is_x_axis_normal() const{
    return (EquFloat(y_,0.0) && EquFloat(z_,0.0) && UEquFloat(x_,0.0));
  }
  bool is_y_axis_normal() const{
    return (EquFloat(x_,0.0) && EquFloat(z_,0.0) && UEquFloat(y_,0.0));
  }
  bool is_z_axis_normal() const{
    return (EquFloat(y_,0.0) && EquFloat(x_,0.0) && UEquFloat(z_,0.0));
  }
  Float x() const{return x_;}
  Float y() const{return y_;}
  Float z() const{return z_;}
  void  x(Float f){x_=f;}
  void  y(Float f){y_=f;}
  void  z(Float f){z_=f;}
  //方向余弦
  Float angle_x_axis() const{
    return acos(x_ / distance_to_zero());
  }
  Float angle_y_axis() const{
    return acos(y_ / distance_to_zero());
  }
  Float angle_z_axis() const{
    return acos(z_ / distance_to_zero());
  }
  Float distance_to_zero() const{
    return sqrt(x_*x_ + y_*y_ + z_*z_);
  }
  
  Float angle_x_axis_two_pi() const;
  
  
private:
  Float x_;
  Float y_;
  Float z_;
  
private:
	MCT_DEF
};

inline void normal2d_2_radian(const Normal& nor, double& radian)
{
  if(nor.is_zero_normal()){
    radian=0;
    return;
  }
  double x_pow = pow(nor.x(),2);
  double y_pow = pow(nor.y(),2);
  double dis   = sqrt(x_pow+y_pow);
  double sin_n = nor.y()/dis;
  radian = asin(sin_n);
  if(LessThen(nor.x(),0)){
    radian = pi-radian;
  }
  std_radian(radian);
  //  return radian;
}

inline void normal2d_2_degree(const Normal& nor, double& degree)
{
  double rad(0); 
  normal2d_2_radian(nor,rad);
  degree = radian_2_degree(rad);
}

inline void radian_2_normal2d(double radian, Normal& nor)
{
  //  Normal nor;
  nor.set_data(0,0,0);
  std_radian(radian);
  double sin_n = sin(radian);
  double cos_n = cos(radian);
  nor.set_data(cos_n, sin_n, 0);
  nor.set_unit();
  //  return nor;
}

inline void degree_2_normal2d(double degree, Normal& nor)
{
  double rad = degree_2_radian(degree);
  radian_2_normal2d(rad,nor);
}


//namespace
}

#endif // !defined(AFX_NORMAL_H__22841A58_7ED0_453A_9C28_B71CD92CC4A1__INCLUDED_)
