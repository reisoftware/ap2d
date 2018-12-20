// Point.h: interface for the Point class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_POINT_H__42B9E6A3_89C7_43FB_9E66_AB2C573FAFA8__INCLUDED_
#define AFX_POINT_H__42B9E6A3_89C7_43FB_9E66_AB2C573FAFA8__INCLUDED_

#include "export.h"
#include <fstream>
#include "../afc/iolua.h"
#include "../afc/counter.h"

// class iLua_File;
// class oLua_File;
namespace dlhml{
class File;
class Matrix;
class Rect;
class Normal;
class OBJECT_API Point  
{
public:
  Point():x(0),y(0),z(0),seled_(false)MCT_INIT2("Point"){}
  Point(Float xx,Float yy,Float zz=0.0):x(xx),y(yy),z(zz),seled_(false)MCT_INIT2("Point"){}

  Point(const Point& rhs);
  Point& Point::operator=(const Point& pt);

  explicit Point(const POINT& pt);
  Point& Point::operator=(const POINT& pt);

  operator POINT() const{
    POINT pt;
    pt.x = static_cast<long>(x);
    pt.y = static_cast<long>(y);
    return pt;
  }
  
  ~Point(){}
  
public:
  bool operator==(const Point& rhs) const{
    return equal(rhs);
  }
  bool operator!=(const Point& rhs) const{
    return !equal(rhs);
  }
  bool equal(const Point& rhs) const{
    return EquFloat(x,rhs.x) && EquFloat(y,rhs.y) && EquFloat(z,rhs.z);
  }
  
public:
  //serialize
  void load(File& in);
  void save(const File& out) const;

	void get_str_sub(char *name);
	void set_from_str_sub(char *name);
 
	void get_str();
	void set_from_str();
// 	void lua_load(iLua_File &fin);
// 	void lua_save(oLua_File &fout)const;

	void save_lua(std::ofstream &out,char *name,int tab_num);
  void open_lua(lua_State *l,char *name) ;
	

  void transformby(const Matrix& mat);
  void transformby2d(const Matrix& mat);
  bool envelop(const Rect& rect) const;
  
  void setdata(Float x, Float y, Float z = 0.0);
  
public:
  Float distanceto(const Point& pt) const{
    Float dis = 0.0;
    Float powerx = (x-pt.x)*(x-pt.x);
    Float powery = (y-pt.y)*(y-pt.y);
    Float powerz = (z-pt.z)*(z-pt.z);
    dis = sqrt(powerx+powery+powerz);
    return dis;
  }
  Float distanceto2d(const Point& pt) const{
    Float dis = 0.0;
    Float powerx = (x-pt.x)*(x-pt.x);
    Float powery = (y-pt.y)*(y-pt.y);
    dis = sqrt(powerx+powery);
    return dis;
  }
  
  void polarTo(const Point &ptBase, float disX, float disY, float disZ=0.0){
    x = ptBase.x + disX;
    y = ptBase.y + disY;
    z = ptBase.z + disZ;
  }
  Point polarTo(Float len, const Normal& normal) const;
  
  Point operator * (Float val) const{
    return Point(x*val,y*val,z*val);
  }
  friend Point operator * (Float val,const Point& rhs){
    return Point(rhs.x*val,rhs.y*val,rhs.z*val);
  }
  Point& operator*=(Float val){
    x*=val;y*=val;z*=val;return *this;
  }
  Point operator / (Float val) const{
    return Point(x/val,y/val,z/val);
  }
  Point& operator/=(Float val){
    x/=val;y/=val;z/=val;return *this;
  }
  
  Point operator + (const Point& pt)const{
    return Point(x+pt.x,y+pt.y,z+pt.z);
  }
  Point& operator+=(const Point& rhs){
    x+=rhs.x;y+=rhs.y;z+=rhs.z;return *this;
  }
  Point operator - (const Point& rhs) const{
    return Point(x-rhs.x,y-rhs.y,z-rhs.z);
  }
  Point& operator-=(const Point& rhs){
    x-=rhs.x;y-=rhs.y;z-=rhs.z;return *this;
  }
  
  Point operator + (const Normal& nor)const;
  Point& operator+=(const Normal& rhs);
  Point operator - (const Normal& rhs)const;
  Point& operator-=(const Normal& rhs);
  
  Float x;
  Float y;
  Float z;
  
public:
  void set2d(const Point& rhs){x=rhs.x;y=rhs.y;z=0;}
  void setdata(const Normal& nor);
  
public:
  void selected(bool s){seled_  = s  ;}
  bool selected()const {return seled_;}
  
private:
  bool seled_;
	
private:
	MCT_DEF
};


inline Float h_radian(const Point& st, const Point& ed);
inline Float v_radian(const Point& st, const Point& ed);

inline Float h_radian(const Point& st, const Point& ed)
{
if(LessEqu(st.x,ed.x)){
  return 0;
}else{
  return pi;
}
}
inline Float v_radian(const Point& st, const Point& ed)
{
if(LessEqu(st.y,ed.y)){
  return pi/2;
}else{
  return pi*3/2;
}
}

}
#endif // !defined(AFX_POINT_H__42B9E6A3_89C7_43FB_9E66_AB2C573FAFA8__INCLUDED_)
