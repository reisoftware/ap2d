
#ifndef _GEOMETRY_FLOAT_H_
#define _GEOMETRY_FLOAT_H_

#include "export.h"

namespace geo{


//const double PI = 3.14159265358979;
const double FMIN = 0.0001;


typedef double Float;

inline Float pi(){return 3.14159265358979;} 
inline Float pi2(){return pi()*2;}
inline Float pi_half(){return pi()/2;}
inline Float circ(){return 360.0;}
inline Float circ_half(){return 180.0;}

inline bool less_than(const Float& l, const Float& r)
{
  return r - l > FMIN;
}
inline bool more_than(const Float& l, const Float& r)
{
  return less_than( r ,  l);
}
inline bool less_equ(const Float& l, const Float& r)
{
  return !more_than( l , r );
}
inline bool more_equ(const Float& l, const Float& r)
{
  return !less_than( l , r );
}
inline bool equ(Float l, Float r)
{
  return less_equ( l , r ) && more_equ( l , r );
}



//class GEOAPI Float
//{
//public:
//  Float():f_(0){}
//  Float(double f):f_(f){}
//  operator double(){return f_;}
//  operator double()const{return f_;}
//
//private:
//  double f_;
//
//private:
//  friend inline bool operator < (const Float& l, const Float& r);
//  friend inline bool operator > (const Float& l, const Float& r);
//  friend inline bool operator <=(const Float& l, const Float& r);
//  friend inline bool operator >=(const Float& l, const Float& r);
//  friend inline bool operator ==(Float l, Float r);
//  friend inline bool operator !=(const Float& l, const Float& r);
//  
//  friend inline Float operator + (const Float& l, const Float& r);
//  friend inline Float operator - (const Float& l, const Float& r);
//  friend inline Float operator * (const Float& l, const Float& r);
//  friend inline Float operator / (const Float& l, const Float& r);
//  friend inline Float& operator +=(Float& l, const Float& r);
//  friend inline Float& operator -=(Float& l, const Float& r);
//  friend inline Float& operator *=(Float& l, const Float& r);
//  friend inline Float& operator /=(Float& l, const Float& r);
//  
//};

//inline bool operator < (const Float& l, const Float& r)
//{
//  return r.f_ - l.f_ > FMIN;
//}
//inline bool operator > (const Float& l, const Float& r)
//{
//  return r < l;
//}
//inline bool operator <=(const Float& l, const Float& r)
//{
//  return !( l > r );
//}
//inline bool operator >=(const Float& l, const Float& r)
//{
//  return !( l < r );
//}
//inline bool operator ==(Float l, Float r)
//{
//  return ( l <= r ) && ( l >= r );
//}
//inline bool operator !=(const Float& l, const Float& r)
//{
//  return !( l == r );
//}
//inline Float operator + (const Float& l, const Float& r)
//{
//  return l.f_ + r.f_;
//}
//inline Float operator - (const Float& l, const Float& r)
//{
//  return l.f_ - r.f_;
//}
//inline Float operator * (const Float& l, const Float& r)
//{
//  return l.f_ * r.f_;
//}
//inline Float operator / (const Float& l, const Float& r)
//{
//  return l.f_ / r.f_;
//}
//inline Float& operator +=(Float& l, const Float& r)
//{
//  l.f_ += r.f_;
//  return l;
//}
//inline Float& operator -=(Float& l, const Float& r)
//{
//  l.f_ -= r.f_;
//  return l;
//}
//inline Float& operator *=(Float& l, const Float& r)
//{
//  l.f_ *= r.f_;
//  return l;
//}
//inline Float& operator /=(Float& l, const Float& r)
//{
//  l.f_ /= r.f_;
//  return l;
//}

}//namespace

#endif//FILE

