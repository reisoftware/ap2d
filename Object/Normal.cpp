// Normal.cpp: implementation of the Normal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Normal.h"
#include "File.h"
#include "Line.h"
#include "Entity_Calculate.h"
//#include "Point.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{

////
Normal::Normal(const Point& pt)
MCT_INIT1("Normal")
{
  set_data(pt);
}
Normal::Normal(const Line & ln)
MCT_INIT1("Normal")
{
  set_data(ln);
}
Normal::Normal(const Point& st, const Point& ed)
MCT_INIT1("Normal")
{
  set_data(st,ed);
}

////
void Normal::load(File& in)
{
	in >> x_ >> y_ >> z_;
}
void Normal::save(const File& out) const
{
	out << x_ << y_ << z_;
}
Float Normal::angle_x_axis_two_pi() const
{
	Float r = angle_x_axis();
	if(!(x_>0) && y_<0)
		r += 2*(pi-r);
	if(x_>0 && y_<0)
		r = 2*pi-r;
	return r;
}

////setdata
void Normal::set_data(const Point& pt)
{
  set_data(Point(0,0,0), pt);
}
void Normal::set_data(const Line& ln)
{
  set_data(ln.start(), ln.end());
}
void Normal::set_data(const Point& st,const Point& ed)
{
	x_ = ed.x-st.x;
	y_ = ed.y-st.y;
	z_ = ed.z-st.z;
}

////operator
bool Normal::operator==(const Normal& rhs) const
{
  return (EquFloat(x_,rhs.x_) && EquFloat(y_,rhs.y_) && EquFloat(z_,rhs.z_));
}
bool Normal::operator!=(const Normal& rhs) const
{
  return !(*this==rhs);
}
Normal Normal::operator * (const Normal& rhs) const
{
  Normal nor;
  nor.x_ = this->y_ * rhs  .z_ - rhs  .y_  * this->z_;
  nor.y_ = rhs  .x_ * this->z_ - this->x_  * rhs  .z_;
  nor.z_ = this->x_ * rhs  .y_ - rhs  .x_  * this->y_;
  return nor;
}


Float Normal::dis_by_way(const Point& pt)const
{
//  Point st;
//  Point ed = st.polarTo(1, *this);
  Line ln = line();

	Entity_Calculate calc;
	Point po;
	calc.line_perpendicular(po,ln,pt);
  Float dis = po.distanceto(Point(0,0,0));
  Normal nor_me(*this);
  Normal nor_po(po);
  nor_me.set_unit();
  nor_po.set_unit();
  return nor_me==nor_po ? dis : -dis ;
}

void Normal::rota_z(double degree)
{
  Normal nor = *this;
	double a = degree_2_radian(degree);
	
	nor.x_ = x_ * cos(a) - y_ * sin(a);
	nor.y_ = x_ * sin(a) + y_ * cos(a);
	nor.z_ = z_;

	*this = nor;
}

Line Normal::line()const
{
  Line ln;
  Point st;
  Point ed = st.polarTo(1,*this);
  ln.setdata(st,ed);
  return ln;
}


}//namespace
