// Paper_Space.cpp: implementation of the Paper_Space class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Paper_Space.h"
#include "Point.h"
#include <TCHAR.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Paper_Space::Paper_Space()
:dim_flags_(5)
MCT_INIT2("Paper_Space")
{
  ortho_ = false;
  background_color_ = RGB(0,0,0);
  entity_color_ = RGB(255,255,255);
  line_style_ = 0;
  string_copy(line_style_,"Continuous");
  layer_ = 0;
  string_copy(layer_,"Layer0");
  
  Float scale = 0.9765625;
  Matrix mat;
  //Æ½ÒÆ
  mat.set_move(-20,-500,0); 
  screen_to_world_ *= mat;
  //BET
  //world_to_screen_=screen_to_world_;
  //world_to_screen_.inverse();
  //TER

#ifndef USE_IMAGE
	//·­×ªyÖá
	mat.set_x_rotation_radian(pi);
	screen_to_world_ *= mat;
  //BET
  //world_to_screen_=screen_to_world_;
  //world_to_screen_.inverse();
  //TER
#endif
	//±ÈÀý
	mat.set_scale(scale,scale,scale);
	screen_to_world_ *= mat;
  //BET
  //world_to_screen_=screen_to_world_;
  //world_to_screen_.inverse();
  //TER
}
Paper_Space::Paper_Space(const Paper_Space& rhs)
MCT_INIT1("Paper_Space")
{
	ortho_ = rhs.ortho_;
	background_color_ = rhs.background_color_;
	entity_color_ = rhs.entity_color_;
	line_style_=0;
	string_copy(line_style_,rhs.line_style_);
	layer_ = 0;
	string_copy(layer_,rhs.layer_);
	screen_to_world_ = rhs.screen_to_world_;
  //BET
 // world_to_screen_=screen_to_world_;
  //world_to_screen_.inverse();
  //TER
	snap_ = rhs.snap_;

  dim_flags_ = rhs.dim_flags_;  
}
Paper_Space& Paper_Space::operator=(const Paper_Space& rhs)
{
	if(this == &rhs)
		return *this;
	ortho_ = rhs.ortho_;
	background_color_ = rhs.background_color_;
	entity_color_ = rhs.entity_color_;
	string_copy(line_style_,rhs.line_style_);
	string_copy(layer_,rhs.layer_);
	screen_to_world_ = rhs.screen_to_world_;
  //BET
  //world_to_screen_=screen_to_world_;
  //world_to_screen_.inverse();
  //TER
	snap_ = rhs.snap_;

//	add_to_dim_list_ = rhs.add_to_dim_list_;
//	erase_from_dim_list_ = rhs.erase_from_dim_list;
  dim_flags_ = rhs.dim_flags_;  
	return *this;
}
Paper_Space::~Paper_Space()
{
	string_delete(line_style_);
	string_delete(layer_);
}
bool Paper_Space::string_copy(LPTSTR& dest,LPCTSTR src)
{
	if(dest == src)
		return true;
	if(NULL != dest)
		delete [] dest;
	dest = 0;
	if(!src)
		return true;
	int length = lstrlen(src);
	dest = new TCHAR[length+1];
	_tcscpy(dest,src);
	dest[length] = '\0';
	return true;
}

void Paper_Space::string_delete(LPTSTR& str)
{
	delete [] str;
	str = NULL;
}

void Paper_Space::set_move(Float dx,Float dy,Float dz)
{
	Matrix mat;
	mat.set_move(dx,dy,dz);
	screen_to_world_ *= mat;
  //BET
  //world_to_screen_=screen_to_world_;
  //world_to_screen_.inverse();
  //TER
}
void Paper_Space::set_scale(Float sx,Float sy,Float sz)
{
	Matrix mat;
	mat.set_scale(sx,sy,sz);
	screen_to_world_ *= mat;
  //BET
  //world_to_screen_=screen_to_world_;
  //world_to_screen_.inverse();
  //TER
}
Matrix Paper_Space::screen_to_world() const
{
	return screen_to_world_;
}
Matrix Paper_Space::world_to_screen() const
{
	Matrix mat(screen_to_world_);
	mat.inverse();
	return mat;
  //BET
  //return world_to_screen_;
  //TER
}
Point Paper_Space::get_current_center(const Point& screen_center) const
{
	Point pt(screen_center);
	pt.transformby(screen_to_world_);
	return pt;
}
Float Paper_Space::get_current_scale() const
{
	return screen_to_world_.value(0,0);
}
}
