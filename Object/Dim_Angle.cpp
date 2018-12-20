// Dim_Angle.cpp: implementation of the Dim_Angle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dim_Angle.h"
#include "Visitor.h"
#include "Database.h"
#include "Line.h"
#include "Text.h"
#include "Normal.h"
#include "format.h"
#include "Matrix_d.h"

#include "../Geometry/Float.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{

Point ver_t_;
Point side1_t_;
Point side2_t_;


MY_IMPLEMENT_DYNCREATE(Dim_Angle,Dimension)
Dim_Angle::Dim_Angle()
{	
	dim_text_ = "100";

}
void Dim_Angle::init(const Dim_Angle& rhs)
{
	ver_ = rhs.ver_;
	side1_ = rhs.side1_;
	side2_ = rhs.side2_;
	pos_ = rhs.pos_;
	side1_txt_ = rhs.side1_txt_;
	side2_txt_ = rhs.side2_txt_;
}

Dim_Angle::Dim_Angle(const Dim_Angle& rhs)
:Dimension(rhs)
{
	init(rhs);
}

Dim_Angle& Dim_Angle::operator=(const Dim_Angle& rhs)
{
	Entity::operator =(rhs);
	if(this == &rhs){
		return *this;
	}
	init(rhs);
	return *this;
}

Dim_Angle::~Dim_Angle()
{
	clear();
}


void Dim_Angle::clear()
{
}
//**构建类时需要重载的函数************************************************************************************
bool Dim_Angle::visit(Visitor& v)
{
  show_change(true);
	return v.Visit_Dim_Angle(*this);
}
void Dim_Angle::loadme(File& in)
{
}
void Dim_Angle::saveme(const File& out) const
{
}
void Dim_Angle::edit_propertyme(const Edit_Entity& edit)
{
	show_change(true);
//	edit.edit_dim_angle(*this);
}
errorinfo Dim_Angle::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}
void Dim_Angle::drag_startme(const Matrix& mat)
{
  show_change(true);
}
void Dim_Angle::drag_endme(const Matrix& mat)
{
  show_change(true);
}
Entity* Dim_Angle::cloneme() const
{
	return new Dim_Angle(*this);
}
void Dim_Angle::closeme()
{
	delete this;
}
bool Dim_Angle::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
{
	return false;
}
bool Dim_Angle::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return false;
}
std::string Dim_Angle::get_lean_value(double base,double len_one,double len_two)const 
{
	std::string str;
	double len = (base *len_two)/len_one;
	str = afc::format(len,0,0,false);

	return str;
}
void Dim_Angle::get_texts(std::string &txt1,std::string &txt2,double side1_len,double side2_len)const
{
	double base_len = 100;
	txt2 = get_lean_value(base_len,side1_len,side2_len);
	double t2 = atof(txt2.c_str());
	if(t2>100){
		txt2 = "100";
		txt1 = get_lean_value(base_len,side2_len,side1_len);
	}else{
		txt1 = "100";
	}
	
	
}
void Dim_Angle::get_line(std::vector<Entity*>& es)const
{
	Line line ;
	line.setdata(this->ver_,side1_);
	//限制长度
	Normal nor_to;
	nor_to.set_data(ver_,side2_);
	float len = dim_style_val_.text_height()*5;
	Point side2_cal = ver_.polarTo(len,nor_to);
	dlhml::Point perp_pt = line.perpendicular(side2_cal);
	//临时值
	ver_t_ = ver_;
	side1_t_ = perp_pt;
	side2_t_ = side2_cal;

	//第一条直角边
	dlhml::Line *line_perp = dlhml::Line::create_me();
	line_perp->setdata(side2_cal,perp_pt);
	set_prop_line(line_perp);
	es.push_back(line_perp);
	//第一条边的文字	
	dlhml::Text *t_first = dlhml::Text::create_me();
	dlhml::Point mid_first = line_perp->middle();
	t_first->position(mid_first);
	dlhml::Text::AlignPt t_side1_align,t_side2_align;
	double side1_angle=0,side2_angle=0;	
	get_angle_align(ver_,perp_pt,side2_cal,t_side1_align,t_side2_align,side1_angle,side2_angle);
	

	set_prop_text(t_first);
	t_first->rotation(side1_angle);
	t_first->align_point(t_side1_align);
	es.push_back(t_first);
	//第二条边	
	dlhml::Line *line_first = dlhml::Line::create_me();
	line_first->setdata(ver_,perp_pt);
	set_prop_line(line_first);
	es.push_back(line_first);
	//第二条边的文字	
	dlhml::Text *t_second = dlhml::Text::create_me();
	dlhml::Point mid_second = line_first->middle();
	t_second->position(mid_second);	
	
	//处理两个文字
	std::string txt1="100",txt2;
	get_texts(txt1,txt2,line_perp->length(),line_first->length());
	t_first->text(txt1);
	t_second->text(txt2);

	t_second->rotation(side2_angle);
	t_second->align_point(t_side2_align);
	set_prop_text(t_second);
	es.push_back(t_second);
	//斜边
	dlhml::Line *line_lean = dlhml::Line::create_me();
	line_lean->setdata(side2_cal,ver_);
	set_prop_line(line_lean);
	es.push_back(line_lean);
	if(step_>2){
		move_to(es,side2_cal,ver_);
	}
}
void Dim_Angle::move_to(std::vector<Entity*>& es,Point side2,Point ver)const
{
	Line line(side2,ver);
	dlhml::Point pos_perp = line.perpendicular(pos_);

	
	Normal move_nor;
	move_nor.set_data(ver,pos_perp);	
	Matrix mat;
	mat.set_move(move_nor);
	for(int i=0;i<es.size();i++)
	{
		es[i]->transformby(mat);
	}

}
void Dim_Angle::get_show(std::vector<Entity*>& es)const
{
	get_line(es);
	
}
//**构建类时需要重载的函数************************************************************************************
void Dim_Angle::set_prop_line(Line *ln)const
{
    ln->color_index(dim_style_val_.line_color());
    ln->line_style(line_style());
}
void Dim_Angle::set_prop_text(Text *txt)const
{
	txt->color_index(dim_style_val_.text_color());
	txt->dxf_height(dim_style_val_.text_height());

}

int Dim_Angle::pt_count()const
{
  return 4;
}
void Dim_Angle::setctrl(const std::vector<Point>& pts)
{
	show_change(true);
	int s = pts.size() ;
	if(pts.size() != 4){
		return;
	}
	ver_ = pts[0];
	side1_ = pts[1];
	side2_ = pts[2];
	pos_ = pts[3];



}
void Dim_Angle::getctrl(std::vector<Point>& pts) const
{
  show_change(true);
	pts.push_back(ver_);
	pts.push_back(side1_);
	pts.push_back(side2_);
	pts.push_back(pos_);
}

void Dim_Angle::setdrag(const std::vector<Point>& pts, int index)
{
  show_change(true);
  if(pts.empty()){
    return;
  }
  
}
void Dim_Angle::getdrag(std::vector<Point>& pts)const
{
	show_change(true);
	pts.push_back(ver_);
	pts.push_back(side1_);
	pts.push_back(side2_);
	pts.push_back(pos_);
}
void Dim_Angle::transformbyme(const Matrix& mat)
{
	show_change(true);
	this->ver_.transformby(mat);
	side1_ .transformby(mat);
	side2_   .transformby(mat);
	pos_   .transformby(mat);
}
void Dim_Angle::deal_one(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const
{
    dlhml::Normal nor;    

	if(side2.x >0){
		//第二条在第四象限
		align1 = dlhml::Text::center_top;
		align2 = dlhml::Text::center_bottom;
		nor.set_data(side1_t_,side2_t_);
		normal2d_2_radian(nor,angle1);

		nor.set_data(side1_t_,ver_t_);
		normal2d_2_radian(nor,angle2);

	}else{
		//第二条在第二象限
		align1 = dlhml::Text::center_top;
		align2 = dlhml::Text::center_top;
		nor.set_data(side2_t_,side1_t_);
		normal2d_2_radian(nor,angle1);

		nor.set_data(side1_t_,ver_t_);
		normal2d_2_radian(nor,angle2);

	
	}
}
void Dim_Angle::deal_two(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const
{
  dlhml::Normal nor;    

	if(side2.x > 0){
		//第二条在第一象限
		align1 = dlhml::Text::center_top;
		align2 = dlhml::Text::center_top;
	
		nor.set_data(side1_t_,side2_t_);
		normal2d_2_radian(nor,angle1);

		nor.set_data(ver_t_,side1_t_);
		normal2d_2_radian(nor,angle2);

	}else{
		//第二条在第三象限
		align1 = dlhml::Text::center_top;
		align2 = dlhml::Text::center_bottom;
		
		nor.set_data(side2_t_,side1_t_);
		normal2d_2_radian(nor,angle1);

		nor.set_data(ver_t_,side1_t_);
		normal2d_2_radian(nor,angle2);

	
	}
}
void Dim_Angle::deal_three(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const
{
  dlhml::Normal nor;    

	if(side2.x >0){
		//第二条在第四象限
		align1 = dlhml::Text::center_bottom;
		align2 = dlhml::Text::center_bottom;
		nor.set_data(side1_t_,side2_t_);
		normal2d_2_radian(nor,angle1);

		nor.set_data(ver_t_,side1_t_);
		normal2d_2_radian(nor,angle2);

	}else{
		//第二条在第二象限
		align1 = dlhml::Text::center_bottom;
		align2 = dlhml::Text::center_top;
		nor.set_data(side2_t_,side1_t_);
		normal2d_2_radian(nor,angle1);

		nor.set_data(ver_t_,side1_t_);
		normal2d_2_radian(nor,angle2);

	
	}
}
void Dim_Angle::deal_four(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const
{
  dlhml::Normal nor;    

	if(side2.x >0){
		//第二条在第一象限
		align1 = dlhml::Text::center_bottom;
		align2 = dlhml::Text::center_top;
		nor.set_data(side1_t_,side2_t_);
		normal2d_2_radian(nor,angle1);

		nor.set_data(side1_t_,ver_t_);
		normal2d_2_radian(nor,angle2);

	}else{
		//第二条在第三象限
		align1 = dlhml::Text::center_bottom;
		align2 = dlhml::Text::center_bottom;
		nor.set_data(side2_t_,side1_t_);
		normal2d_2_radian(nor,angle1);

		nor.set_data(side1_t_,ver_t_);
		normal2d_2_radian(nor,angle2);


	
	}
}
void Dim_Angle::deal_ver_x_axis(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const
{
  dlhml::Normal nor;    

	if(ver.x >0){
		//ver在x轴正方向
		if(side2.y>0)
		{
			//第二条在第一象限
			align1 = dlhml::Text::center_bottom;
			align2 = dlhml::Text::center_top;
			nor.set_data(side1_t_,side2_t_);
			normal2d_2_radian(nor,angle1);

			nor.set_data(side1_t_,ver_t_);
			normal2d_2_radian(nor,angle2);
		}else{
			//第二条在第四象限
			align1 = dlhml::Text::center_bottom;
			align2 = dlhml::Text::center_bottom;
			nor.set_data(side2_t_,side1_t_);
			normal2d_2_radian(nor,angle1);

			nor.set_data(side1_t_,ver_t_);
			normal2d_2_radian(nor,angle2);
		}

	}else{
		//ver在x轴负方向
		if(side2.y>0)
		{
			//第二条在第四象限
			align1 = dlhml::Text::center_top;
			align2 = dlhml::Text::center_top;
			nor.set_data(side1_t_,side2_t_);
			normal2d_2_radian(nor,angle1);

			nor.set_data(ver_t_,side1_t_);
			normal2d_2_radian(nor,angle2);
		}else{
			//第二条在第三象限
			align1 = dlhml::Text::center_top;
			align2 = dlhml::Text::center_bottom;
			nor.set_data(side2_t_,side1_t_);
			normal2d_2_radian(nor,angle1);

			nor.set_data(ver_t_,side1_t_);
			normal2d_2_radian(nor,angle2);
		}

	
	} 

}
void Dim_Angle::deal_ver_y_axis(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const
{
   dlhml::Normal nor;    

	if(ver.y >0){
		//ver在y轴正方向
		if(side2.x>0)
		{
			//第二条在第一象限
			align1 = dlhml::Text::center_top;
			align2 = dlhml::Text::center_bottom;
			nor.set_data(side1_t_,side2_t_);
			normal2d_2_radian(nor,angle1);

			nor.set_data(side1_t_,ver_t_);
			normal2d_2_radian(nor,angle2);
		}else{
			//第二条在第二象限
			align1 = dlhml::Text::center_top;
			align2 = dlhml::Text::center_top;
			nor.set_data(side2_t_,side1_t_);
			normal2d_2_radian(nor,angle1);

			nor.set_data(side1_t_,ver_t_);
			normal2d_2_radian(nor,angle2);
		}

	}else{
		//ver在y轴负方向
		if(side2.x>0)
		{
			//第二条在第四象限
			align1 = dlhml::Text::center_bottom;
			align2 = dlhml::Text::center_bottom;
			nor.set_data(side1_t_,side2_t_);
			normal2d_2_radian(nor,angle1);

			nor.set_data(ver_t_,side1_t_);
			normal2d_2_radian(nor,angle2);
		}else{
			//第二条在第三象限
			align1 = dlhml::Text::center_bottom;
			align2 = dlhml::Text::center_bottom;
			nor.set_data(side2_t_,side1_t_);
			normal2d_2_radian(nor,angle1);

			nor.set_data(side1_t_,ver_t_);
			normal2d_2_radian(nor,angle2);
		}

	
	} 

}
bool Dim_Angle::get_angle_align(const Point &ver,const Point &side1,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const 
{
	//把side1设为圆心
	Point ver_t(ver.x-side1.x,ver.y-side1.y,0),side2_t(side2.x-side1.x,side2.y-side1.y,0);	

	if(geo::equ(ver_t.x,0)){
		deal_ver_y_axis(ver_t,side2_t,align1,align2,angle1,angle2);
	}
	else if(geo::equ(ver_t.y,0)){
		deal_ver_x_axis(ver_t,side2_t,align1,align2,angle1,angle2);
	}
	else if((ver_t.x >0)  && (ver_t.y >0) ){
		deal_one(ver_t,side2_t,align1,align2,angle1,angle2);
	}
	else if((ver_t.x <0)  && (ver_t.y >0) )
	{
		deal_two(ver_t,side2_t,align1,align2,angle1,angle2);
	}
	else if((ver_t.x <0)  && (ver_t.y <0) )
	{
		deal_three(ver_t,side2_t,align1,align2,angle1,angle2);
	}
	else if((ver_t.x >0)  && (ver_t.y <0) )
	{
		deal_four(ver_t,side2_t,align1,align2,angle1,angle2);
	}

	return true;
}



}//namespace




