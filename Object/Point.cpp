// Point.cpp: implementation of the Point class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Point.h"
#include "File.h"
#include "Rect.h"
#include "Normal.h"
#include "Matrix_d.h"
#include "iolua.h"
#include "Lua_Tab.h"
#include "encode.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4800)
#pragma warning (disable : 4244)

namespace dlhml{
Point::Point(const Point& rhs)
:x(rhs.x)
,y(rhs.y)
,z(rhs.z)
,seled_(rhs.seled_)
MCT_INIT2("Point")
{
}

Point& Point::operator=(const Point& pt){
	x = pt.x;
	y = pt.y;
	z = pt.z;
  seled_=pt.seled_;
	return *this;
}
Point::Point(const POINT& pt)
:x(pt.x)
,y(pt.y)
,z(0)
,seled_(false)
MCT_INIT2("Point")
{
}

Point& Point::operator=(const POINT& pt){
  x = pt.x;
  y = pt.y;
  z = 0;
  seled_=false;
  return *this;
}

void Point::setdata(Float x,Float y,Float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::load(File& in)
{
	in >> x >> y >> z;
}
void Point::save(const File& out) const
{
	out << x << y << z;
}

// void Point::lua_load(iLua_File &fin)
// {
// }
// 
// void Point::lua_save(oLua_File &fout)const
// {
// 	fout.save_value("x", x);
// 	fout.save_value("y", y);
// 	fout.save_value("z", z);
// }
void Point::save_lua(std::ofstream &out,char *name,int tab_num)
{
	lua::begin_table(out,name,tab_num);

	lua::double_save(out,"x",x,tab_num+1);
	lua::double_save(out,"y",y,tab_num+1);
	lua::double_save(out,"z",z,tab_num+1);

	lua::end_table(out,tab_num);

}
void Point::open_lua(lua_State *l,char *name)
{
	Lua_Tab lua(l,name);
	get_value(number,l,x,"x");
	get_value(number,l,y,"y");
	get_value(number,l,z,"z");

}
void Point::get_str()
{
	rei_add_float(NULL,"x",x);
	rei_add_float(NULL,"y",y);
	rei_add_float(NULL,"z",z);

}
void Point::set_from_str()
{
	x = atof(rei_get("x"));
	y = atof(rei_get("y"));
	z = atof(rei_get("z"));
}

void Point::get_str_sub(char *name)
{
	char s1[MAX_REDIS_STR];
	char s2[MAX_REDIS_STR];
	char s3[MAX_REDIS_STR];
	sprintf(s1,"%s.x",name);
	sprintf(s2,"%s.y",name);
	sprintf(s3,"%s.z",name);

	rei_add_float(NULL,s1,x);
	rei_add_float(NULL,s2,y);
	rei_add_float(NULL,s3,z);
	
}
void Point::set_from_str_sub(char *name)
{
	char s1[MAX_REDIS_STR];
	char s2[MAX_REDIS_STR];
	char s3[MAX_REDIS_STR];
	sprintf(s1,"%s.x",name);
	sprintf(s2,"%s.y",name);
	sprintf(s3,"%s.z",name);
	x = atof(rei_get(s1));
	y = atof(rei_get(s2));
	z = atof(rei_get(s3));
}

void Point::transformby(const Matrix& mat)
{
	Float m_x,m_y,m_z;
	m_x=mat.value(0,0)*x+mat.value(1,0)*y+mat.value(2,0)*z+mat.value(3,0);
	m_y=mat.value(0,1)*x+mat.value(1,1)*y+mat.value(2,1)*z+mat.value(3,1);
	m_z=mat.value(0,2)*x+mat.value(1,2)*y+mat.value(2,2)*z+mat.value(3,2);
	x=m_x;
	y=m_y;
	z=m_z;
}
void Point::transformby2d(const Matrix& mat)
{
	Float m_x,m_y;
	m_x=mat.value(0,0)*x+mat.value(1,0)*y+mat.value(2,0)*z+mat.value(3,0);
	m_y=mat.value(0,1)*x+mat.value(1,1)*y+mat.value(2,1)*z+mat.value(3,1);
	x=m_x;
	y=m_y;
}
bool Point::envelop(const Rect& rect) const
{
	return !(x>rect.xmax()) && !(x<rect.xmin()) && !(y>rect.ymax()) && !(y<rect.ymin());
	return ::PtInRect(&(RECT)rect,*this);
}
Point Point::polarTo(Float len, const Normal& normal) const
{
	if(EquFloat(len,0))
		return *this;
	if(normal.is_zero_normal())
		return *this;
	Normal nor = normal;
	nor.set_unit();
	return Point(x+len*nor.x(),y+len*nor.y(),z+len*nor.z());
}

Point Point::operator + (const Normal& nor)const{
	return Point(x+nor.x(),y+nor.y(),z+nor.z());
}
Point& Point::operator+=(const Normal& rhs){
	x+=rhs.x();y+=rhs.y();z+=rhs.z();return *this;
}
Point Point::operator - (const Normal& rhs) const{
	return Point(x-rhs.x(),y-rhs.y(),z-rhs.z());
}
Point& Point::operator-=(const Normal& rhs){
	x-=rhs.x();y-=rhs.y();z-=rhs.z();return *this;
}

void Point::setdata(const Normal& nor)
{
  setdata(nor.x(), nor.y(), nor.z());
}


//namespace
}
