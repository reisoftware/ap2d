// Entity_Calculate.h: interface for the Entity_Calculate class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_ENTITY_CALCULATE_H__2F571835_FD72_46B0_919D_5FF380DFD385__INCLUDED_
#define AFX_ENTITY_CALCULATE_H__2F571835_FD72_46B0_919D_5FF380DFD385__INCLUDED_

#include "export.h"
#include <vector>
#include "Line.h"

namespace dlhml{

enum DEGREE_POS {AXIS_0  =  0, QD_1, 
                 AXIS_90 = 90, QD_2, 
                 AXIS_180=180, QD_3, 
                 AXIS_270=270, QD_4};

class Point;
class Line;
class Circle;
class RArc;
class Rect;
class Entity;
class OBJECT_API Entity_Calculate  
{
public:
	Entity_Calculate();
	~Entity_Calculate();


	//line
	//二维平面函数
	//与x轴的角度
	bool middle_perpendicular_line(Line& line,const Point& st,const Point& ed);
	Float line_angle_to_x_axis(const Line& line) const;
	bool line_tan(Float &a,const Line& line) const;
	Float line_B(const Line& line) const;
	bool parallel(const Line& lhs,const Line& rhs) const;
	bool point_in_linesegment(const Point &q,const Line& line) const;
  bool radian_Arc(Float& radian_max,Float& radian_min,
    Float Arc[],Float CC[]) const;
  int radian_intersec(Float IntersecRadian[],Float m_intersec[],Float CC[]) const;
	bool line_parallel(Line& dest,const Line& src,const Point& o) const;
	bool line_perpendicular(Point& out,const Line& line,const Point& o) const;
	//计算过已知点与已知线的垂足
	bool point_perpendicular(Float p[2],Float p1[2],Float p2[2],Float pt[2]) const;

//	void get_ents_rect(Rect& rect,const std::vector<Entity*>& ents);
	bool linesegment_insect_rect(const Line& lines,const Rect& rect);
  bool rect_insect_beeline(const Rect& rc, const Line& ln);


	bool line_insect_line_segment(Point& ptIn,const Line& lhs,const Line& line) const;
	bool line_insect_line(Point& ptIn,const Line& lhs,const Line& line) const;
	//bool line_insect_circle(Point& pt1,Point& pt2,const Line& line,const Circle& circle) const;
  //bool line_insect_arc(Point& pt1,Point& pt2,const Line& line,const RArc& arc) const;


	//circle
	bool circle_insect_circle(Point& pt1,Point& pt2,const Circle& lhs,const Circle& rhs) const;
	bool circle_insect_arc(Point& pt1,Point& pt2,const Circle& circle,const RArc& arc) const;
	bool intersect_cir2arc(Float& pt1_x,Float& pt1_y,Float& pt2_x,Float& pt2_y,
		Float center_x,Float center_y,Float rad,
		Float arcst_x,Float arcst_y,Float arced_x,
		Float arced_y,Float arc_x,Float arc_y) const;

	//arc
	bool arc_insect_arc(Point& pt1,Point& pt2,const RArc& lhs,const RArc& rhs) const;
	bool intersect_arc2arc(Float& pt1_x,Float& pt1_y,Float& pt2_x,Float& pt2_y,
								   Float arcst1_x,Float arcst1_y,
								   Float arced1_x,Float arced1_y,
								   Float arc1_x,Float arc1_y,
								   Float arcst2_x,Float arcst2_y,
								   Float arced2_x,Float arced2_y,
								   Float arc2_x,Float arc2_y) const;

	bool intersect_cir2cir(Float& pt1_x,
                        Float& pt1_y,
                        Float& pt2_x,
                        Float& pt2_y,
		                    Float center1_x,
                        Float center1_y,
                        Float rad_1,
		                    Float center2_x,
                        Float center2_y,
                        Float rad_2) const;
  //base 
//	int intersect_line2circle(Float& destpt1_x, 
//                            Float& destpt1_y, 
//								            Float& destpt2_x, 
//                            Float& destpt2_y, 
//								            Float linest_x,   
//                            Float linest_y, 
//								            Float lineed_x,   
//                            Float lineed_y, 
//								            Float center_x,   
//                            Float center_y, 
//								            Float rad) const;
//	int intersect_line2arc( Float& pt1_x,
//                          Float& pt1_y,
//                          Float& pt2_x,
//                          Float& pt2_y,
//									        Float lst_x,
//                          Float lst_y, 
//									        Float led_x,
//                          Float led_y, 
//									        Float arcst_x,
//                          Float arcst_y, 
//									        Float arced_x,
//                          Float arced_y, 
//									        Float arc_x,
//                          Float arc_y) const;


private:
	MCT_DEF
};

bool area_by_side(const std::vector<Point>& pts, int index, Float& myarea);

inline bool is_in(const Point& pt, const Point polygon[], int nCount);
inline bool is_in(const Point& pt, const std::vector<Point>& polygon);



DEGREE_POS degree_pos(Float deg); 

////是否正多边形（无扭曲，即任意不相邻的两条边均无交点）
//inline bool is_polygon(const std::vector<Point  >& polygon);
inline bool is_polygon(const std::vector<Line*>& polygon);




inline bool is_in(const Point& pt, const std::vector<Point>& polygon)
{
  return is_in(pt,polygon.begin(),polygon.size());
}
inline bool is_in(const Point& pt, const Point polygon[], int nCount)
{
  if(nCount < 2) return false;
  ////若点恰好在边线上，则直接认定点在多边形内。
  int i=0;
  Line border;
  for(i=0; i< nCount; i++){
    border.setdata(polygon[i], polygon[(i+1)%nCount]);
    if(border.is_in_segline(pt)){
      return true;
    }
  }
  
  if(nCount < 2) return false;
  int nCross = 0; 
  for(i = 0; i < nCount; i++){ 
    Point p1 = polygon[i]; 
    Point p2 = polygon[(i+1) % nCount]; 
    //// 求解 y=p.y 与 p1p2 的交点 
    if (EquFloat(p1.y,p2.y) ) //// p1p2 与 y=p0.y平行 
      continue; 
    if (LessThen(pt.y, min(p1.y, p2.y)) ) //// 交点在p1p2延长线上 
      continue; 
    if (MoreEqu( pt.y, max(p1.y, p2.y)) ) //// 交点在p1p2延长线上 
      continue; 
    //// 求交点的 X 坐标 
    double x =	(double)(pt.y-p1.y) * 
      (double)(p2.x-p1.x) / 
      (double)(p2.y-p1.y) + p1.x; 
    if (MoreThen(x, pt.x) ) 
      nCross++; //// 只统计单边交点 
  } 
  //// 单边交点为偶数，点在多边形之外 --- 
  return (bool)(nCross % 2 == 1); 
}

////是否正多边形（无扭曲，即任意不相邻的两条边均无交点）
//inline bool is_polygon(const std::vector<Point  >& polygon);
inline bool is_polygon(const std::vector<Line*>& polygon)
{
  Entity_Calculate calc;
  Point inspt;
  bool isins=false;
  int i=0, k=0;
  for(i=0; i<polygon.size(); i++){
    for(k=0; k<polygon.size(); k++){
      if(k==i || k==i-1 || k==i+1){
        continue;
      }
      if(!polygon[i] || !polygon[k]){
        continue;
      }
      isins = calc.line_insect_line(inspt,*polygon[i],*polygon[k]);
      if(isins){
        if(polygon[i]->is_in_segline(inspt) || polygon[k]->is_in_segline(inspt)){
          return false;
        }
      }
    }
  }
  return true;
}



}//namespace
#endif // !defined(AFX_ENTITY_CALCULATE_H__2F571835_FD72_46B0_919D_5FF380DFD385__INCLUDED_)
