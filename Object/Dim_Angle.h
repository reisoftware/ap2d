// Dim_Angle.h: interface for the Dim_Angle class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_LEAD_DIMENSION_ANGLE_H__15805EB8_6296_44DB_ACF2_4D8C565856C7__INCLUDED_
#define AFX_LEAD_DIMENSION_ANGLE_H__15805EB8_6296_44DB_ACF2_4D8C565856C7__INCLUDED_


#include "Entity.h"
#include <vector>

#include "Dimension.h"

namespace dlhml{

class OBJECT_API Dim_Angle : public Dimension
{
	MY_DECLARE_DYNCREATE(Dim_Angle)
public:
	Dim_Angle();
	Dim_Angle(const Dim_Angle& rhs);
	Dim_Angle& operator=(const Dim_Angle& rhs);
	virtual ~Dim_Angle();
	void clear();

//**构建类时需要重载的函数************************************************************************************
private:
	void get_line(std::vector<Entity*>& es)const;
	void get_show(std::vector<Entity*>& es)const;
	void loadme(File& in);
	void saveme(const File& out) const;
	void edit_propertyme(const Edit_Entity& edit);
	errorinfo postme2db(Database& db,Entity_ID& id);
	void drag_startme(const Matrix& mat);
	void drag_endme(const Matrix& mat);
	Entity* cloneme() const;
	void closeme();
	bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;
	bool visit(Visitor& v);
//**构建类时需要重载的函数************************************************************************************

private:
	Point ver_;
	Point side1_;
	Point side2_;
	Point pos_;

	std::string side1_txt_;
	std::string side2_txt_;


private:
	void init(const Dim_Angle& rhs);
	void set_prop_line(Line *ln)const;
	void set_prop_text(Text *txt)const;
	std::string get_lean_value(double base,double len_one,double len_two)const;
	void move_to(std::vector<Entity*>& es,Point side2,Point ver)const;

	bool get_angle_align(const Point &ver,const Point &side1,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const ;
	void deal_one(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const;
	void deal_two(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const;
	void deal_three(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const;
	void deal_four(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const;

	void deal_ver_x_axis(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const;
	void deal_ver_y_axis(const Point &ver,const Point &side2,dlhml::Text::AlignPt &align1,dlhml::Text::AlignPt &align2,double & angle1,double & angle2)const;

	void get_texts(std::string &txt1,std::string &txt2,double side1_len,double side2_len)const;
private:

private:
	//虚函数
	int  pt_count()const;
	void setctrl(const std::vector<Point>& pts);
	void getctrl(std::vector<Point>& pts) const;
	void getdrag(std::vector<Point>& pts)const;
	void setdrag(const std::vector<Point>& pts, int index);
	void transformbyme(const Matrix& mat);



};
}
#endif // !defined(AFX_LEAD_DIMENSION_BLOCK_H__15805EB8_6296_44DB_ACF2_4D8C565856C7__INCLUDED_)
