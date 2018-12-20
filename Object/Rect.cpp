// Rect.cpp: implementation of the Rect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rect.h"
#include "File.h"
#include "Point.h"
#include "Matrix_d.h"
#include "Lua_Tab.h"
#include "encode.h"
//#include "..\DrawDll\reitrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#pragma warning (disable : 4244)

namespace dlhml{

Rect::Rect()
:xmin_(0.0)
,ymin_(0.0)
,xmax_(0.0)
,ymax_(0.0)
,seled_(false)
MCT_INIT2("Rect")
{
}
Rect::Rect(const Rect& rhs)
:xmin_(rhs.xmin_)
,ymin_(rhs.ymin_)
,xmax_(rhs.xmax_)
,ymax_(rhs.ymax_)
MCT_INIT2("Rect")
{
}

Rect::Rect(const RECT& rect)
:seled_(false)
MCT_INIT2("Rect")
{
	xmin_ = rect.left; 
	ymin_ = rect.top;
	xmax_ = rect.right;
	ymax_ = rect.bottom;
}
Rect& Rect::operator=(const RECT& rect)
{
	xmin_ = rect.left; 
	ymin_ = rect.top;
	xmax_ = rect.right;
	ymax_ = rect.bottom;
  //seled_= false;
	return *this;
}

void Rect::update()
{
  if(xmin_ > xmax_){
    std::swap(xmin_, xmax_);
  }
  if(ymin_ > ymax_){
    std::swap(ymin_, ymax_);
  }
}

void Rect::load(File& in)
{
	in >> xmin_ >> ymin_ >> xmax_ >> ymax_ >> seled_;
}
void Rect::save(const File& out) const
{
	out << xmin_ << ymin_ << xmax_ << ymax_ << seled_;
}
void Rect::save_lua(std::ofstream &out,char *name,int tab_num)
{
	lua::begin_table(out,name,tab_num);

	lua::double_save(out,"xmin_",xmin_,tab_num+1);
	lua::double_save(out,"ymin_",ymin_,tab_num+1);
	lua::double_save(out,"xmax_",xmax_,tab_num+1);
	lua::double_save(out,"ymax_",ymax_,tab_num+1);
	lua::bool_save(out,"seled_",seled_,tab_num+1);

	lua::end_table(out,tab_num);

}
void Rect::open_lua(lua_State *l,char *name)
{
	Lua_Tab t(l,name);
	get_value(number,l,xmin_,"xmin_");
	get_value(number,l,ymin_,"ymin_");
	get_value(number,l,xmax_,"xmax_");
	get_value(number,l,ymax_,"ymax_");
	get_value(number,l,seled_,"seled_");
}

void Rect::get_str_sub(char *name)
{
	char s[MAX_REDIS_STR];
	sprintf(s,"%s.xmin_",name);
	rei_add_float(NULL,s,xmin_);

	sprintf(s,"%s.ymin_",name);
	rei_add_float(NULL,s,ymin_);

	sprintf(s,"%s.xmax_",name);
	rei_add_float(NULL,s,xmax_);

	sprintf(s,"%s.ymax_",name);
	rei_add_float(NULL,s,ymax_);

	sprintf(s,"%s.seled_",name);
	rei_add_int(NULL,s,seled_);

	
}
void Rect::set_from_str_sub(char *name)
{
	char s[MAX_REDIS_STR];
	sprintf(s,"%s.xmin_",name);
	xmin_ = atof(rei_get(s));

	sprintf(s,"%s.ymin_",name);
	ymin_ = atof(rei_get(s));

	sprintf(s,"%s.xmax_",name);
	xmax_ = atof(rei_get(s));

	sprintf(s,"%s.ymin_",name);
	ymin_ = atof(rei_get(s));

	sprintf(s,"%s.ymax_",name);
	ymax_ = atof(rei_get(s));

	sprintf(s,"%s.seled_",name);
	seled_ = atoi(rei_get(s));

}
void Rect::transformby(const Matrix& mat)
{
//	REITRACE;
	Point pt1(xmin_,ymin_,0.0);
	Point pt2(xmax_,ymax_,0.0);
	pt1.transformby(mat);
	pt2.transformby(mat);
	setdata(pt1,pt2);
}
/*
矩形各由两点(左下/右上)决定，使用逻辑坐标系   
  矩形   A   (x1,y1),(x2,y2);     
  矩形   B   (x3,y3),(x4,y4);   
    
  设   m=   (x1>x4)|(x2<x3)   
        n=   (y2<y3)|(y1>y4)   
    
  if(m|n)   
  {   
  //不相交   
  }   
  else   
  {   
  //相交   
  }   
*/
bool Rect::intersect(const Rect& rect) const
{
	bool m = (xmin()>rect.xmax())|(xmax()<rect.xmin());
	bool n = (ymax()<rect.ymin())|(ymin()>rect.ymax());
	if(m|n)
		return false;
	else
		return true;
}
bool Rect::envelop(const Rect& rc) const
{
	return xmin_>rc.xmin_ && xmax_<rc.xmax_ && ymin_>rc.ymin_ && ymax_<rc.ymax_;
}
void Rect::setdata(const Point& st,const Point& ed)
{
	xmin_ = min(st.x,ed.x);
	xmax_ = max(st.x,ed.x);
	ymin_ = min(st.y,ed.y);
	ymax_ = max(st.y,ed.y);
}

Rect Rect::operator * (Float f) const
{
	Rect rc = *this;
	return rc*=f;
}
Rect& Rect::operator *= (Float f) 
{
	Float xmid = (xmin()+xmax())/2;
	Float ymid = (ymin()+ymax())/2;
	
	Float xdis = fabs(xmax()-xmid);
	Float ydis = fabs(ymax()-ymid);
	
	xmin_ = (xmid - xdis * f);
	ymin_ = (ymid - ydis * f);
	xmax_ = (xmid + xdis * f);
	ymax_ = (ymid + ydis * f);
	
	return *this;
}



}//namespace
