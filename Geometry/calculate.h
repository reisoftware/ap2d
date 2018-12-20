#ifndef _GEOMETRY_CALCULATE_H_
#define _GEOMETRY_CALCULATE_H_
#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <assert.h>
#include "Point.h"
#include "box.h"
#include "export.h"
#include "Float.h"

namespace geo{

	class Normal;

	class Plane;

	class LLine;
	class SLine;
	class RLine;
	class Circle;
	class Arc;

GEOAPI Point project(const Point &pt);
GEOAPI Point operator * (const Point &p1,const Point &p2);
GEOAPI Float multiply(const Point &p1,const Point &p2);
GEOAPI Point operator * (const Point &pt,Float d);
GEOAPI Point operator * (Float d,const Point &pt);
GEOAPI Float mos(const Point &p);
GEOAPI Point get_nor(const Plane &pla);
GEOAPI Point normalize(const Point &pt);
GEOAPI Float angle(const Point &p1,const Point &p2);
GEOAPI Plane make_plane(const Point &pt,Float d);
GEOAPI Plane make_plane(const Point &p1,const Point &p2,const Point &p3);
GEOAPI Plane make_plane(const Point &pt,const Point &nor);
GEOAPI Plane make_plane(const LLine &ln1,const LLine &ln2);
GEOAPI Plane make_plane(const Circle &c);
GEOAPI SLine create_sline(const Point &pt1,const Point &pt2);
GEOAPI LLine make_line(const Point &pt,const Point &vec);
GEOAPI Float distance(const Point &p1,const Point &p2);
GEOAPI LLine project(const LLine &ln);
GEOAPI RLine project(const RLine &rl);
GEOAPI SLine project(const SLine &sl);
GEOAPI LLine make_line(const RLine &rl);
GEOAPI LLine make_line(const SLine &sl);
GEOAPI bool relation(const Point &pt,const RLine &ray);
GEOAPI bool relation(const Point &pt,const SLine &sl);
GEOAPI bool operator > (const Point &p1,const Point &p2);
GEOAPI bool operator < (const Point &p1,const Point &p2);
GEOAPI Float distance(const Point &p,const LLine &ln);
GEOAPI Float distance(const Point &p,const Plane &pla);
GEOAPI Point project(const Point &p,const LLine &ln);
GEOAPI Point project(const Point &p,const Plane &pla);
GEOAPI bool intersect(const LLine &ln1,const LLine &ln2,Point &pt);
GEOAPI bool intersect(const LLine &ln,const Plane &pla,Point &pt);
GEOAPI bool intersect(const Plane &pla1,const Plane &pla2,LLine &ln);
GEOAPI int intersect(const LLine &ln,const Arc &arc,Point &cross1,Point &cross2);
GEOAPI bool intersect(const SLine &sl,const LLine &ln,Point &pt);
GEOAPI bool intersect(const SLine& sl1, const SLine& sl2, Point& pt);
GEOAPI int intersect(const SLine &sl,const Arc &arc,Point &cross1,Point &cross2);
GEOAPI int intersect(const SLine &sl,const Circle &c,Point &cross1,Point &cross2);
GEOAPI int relation(const Point &p1,const Point &p2);
GEOAPI bool relation(const Point &p1,const Point &p2,const Point &p3);
GEOAPI int relation(const Plane &pla1,const Plane &pla2);
GEOAPI int relation(const LLine &ln,const Plane &pla);
GEOAPI int relation(const Point& pt,const Plane& pla);
GEOAPI bool superposition(const LLine &ln1,const LLine &ln2);
GEOAPI bool parallel(const LLine &ln1,const LLine &ln2);
GEOAPI bool parallel(const SLine &sl1,const SLine &sl2);
GEOAPI bool intersection(const LLine &ln1,const LLine &ln2);
GEOAPI int relation(const LLine &ln1,const LLine &ln2);
GEOAPI Point resume_point(const Point &ph,const LLine &ln);
GEOAPI Point resume_point(const Point &ph,const Plane &pla);
GEOAPI LLine resume_line(const LLine &lh,const Plane &pla);
GEOAPI int dline_leave(const SLine &sl1,const SLine &sl2);
GEOAPI SLine make_sline(const LLine &ln);
GEOAPI Point make_point(const Normal &nor);
GEOAPI int intersect(const LLine &ln,const Circle &c,Point &cross1,Point &cross2);
GEOAPI void resume_circle(const Arc &arc,Circle &c);
GEOAPI bool relation(const Point &pt,const Arc &arc);
GEOAPI int relation(const Point &pt,const Circle &c);
GEOAPI int relation(const Circle &c1,const Circle &c2);
GEOAPI bool is_conplane(const Circle &c1,const Circle &c2);
GEOAPI bool dcircle_in(const Circle &c1,const Circle &c2);
GEOAPI Circle make_circle(const Point &pt1,const Point &pt2,const Point &pt3);
GEOAPI Point resume_point(const Point &ph,const Circle &c);
GEOAPI Normal make_nor(const Point &pt);
GEOAPI Point middle_point(const Arc &arc,const Point &p1,const Point &p2,const Circle &c);
GEOAPI bool superposition2d(const LLine &ln1,const LLine &ln2);
GEOAPI Point project2d(const Point &pt,const LLine &ln);
GEOAPI Float distance2d(const Point &p,const LLine &ln);
GEOAPI Float distance2d(const Point &pt1,const Point &pt2);
GEOAPI Float convert_degree(const Float &degree);
GEOAPI Float convert_radian(const Float &radian);
GEOAPI Float dis2d(const Point &pl,const Point &pt,const Normal &vec);
GEOAPI Float dis2d(const Point &pt,const LLine &ln,const Normal &vec);
GEOAPI LLine offset2d(const Point &pt,const LLine &ln);
GEOAPI LLine offset2d(const LLine &lnsourse,const Point &pt,Float dis);
GEOAPI LLine erect2d(const LLine &ln);
GEOAPI LLine erect2d(const LLine &ln);
GEOAPI LLine erect2d(const Point &pt,const LLine &ln);
GEOAPI Float get_angle2d(const Point &pt,const Point &center);
GEOAPI Float bisector_radian2d(const Arc &arc);
GEOAPI Point bisector_point2d(const Arc &arc);
GEOAPI LLine bisector_line2d(const Arc &arc);
GEOAPI Point polarto2d(const Point &pt,Float angle);
GEOAPI Normal convert2d(Float angle);
GEOAPI Point project2d(const Point &pt,const LLine &lnbase,const Point &ptbase);
GEOAPI Float radian2d(const Normal &direction);
GEOAPI Float radian2d(const Point &ptend,const Point &ptstart);
GEOAPI Float radian2d(const LLine &ln);
GEOAPI Float stdradian(Float radian);
GEOAPI Float stdangle(Float angle);
GEOAPI int quadrant(Float radian,const bool &on_off);
GEOAPI LLine make_line(const Point &pt,Float angle);
GEOAPI void make_line(const Box& box,std::vector<SLine> &sls);
GEOAPI void make_line(const Box& box,SLine sls[]);
GEOAPI Float get_min_area(const std::vector<Point>& pts);
GEOAPI Point get_pt(const LLine &ln,const Point & pt,const Point & sign_pt,Float dis);
GEOAPI bool get_points(const std::vector<SLine> &sls,std::vector<Point> &pts);
GEOAPI Point any_point(const Plane &pla,const Point &pt);
GEOAPI Float distance(const LLine &ln1,const LLine &ln2,Float dis,Point &cross);
GEOAPI Float ray_angle(const Point& st,const Point& ed);
GEOAPI Point get_nor(const Point& pt1,const Point& pt2,const Point& pt3);
GEOAPI Point get_pt(const Arc &arc);
GEOAPI Float get_radius(const Arc &arc);
GEOAPI bool less_arc(const Arc &arc);  //判断略弧
GEOAPI Float get_angle(const Arc &arc);  //求圆弧的圆心角
GEOAPI Float get_angle(const Circle &c,const Point &base,const Point &pt);
GEOAPI bool sort(const Circle &c,const std::vector<Point> &pts,std::vector<Point> &result);
GEOAPI bool sort(const Arc &arc,const std::vector<Point> &pts,std::vector<Point> &result);

/*把短线小于range的并且个数连续短线大于等于3的线，合成弧，剩余的线放到new_lns,弧放到new_arcs中*/
GEOAPI int merge_arc(const std::vector<LLine> &lns,Float range,std::vector<LLine> &new_lns,std::vector<Arc> &new_arcs);
GEOAPI bool merge_arc(const std::vector<LLine> &lns,std::vector<LLine> &new_lns,std::vector<Arc> &new_arcs);
GEOAPI bool merge_circle(const std::vector<SLine> &lns,Float range,Circle &c);
/*求在lns中与ln平行的线，返回它们之间距离最小值,并且求，ln的中点，和其有最小值的的平行线中点连线上逆向的距离=dis的点*/
GEOAPI Float dis_parallel(const LLine &ln,const std::vector<LLine> &lns,Float dis,Point &mid_off);
/*hoop是一个环，查找lns中有没有线能够产生一个更大的hoop，有的话把hoop生成*/
GEOAPI Float get_area(const std::vector<Point> &pts);
GEOAPI void find_parallel(const std::vector<SLine>& src,const std::vector<SLine>& refer,std::vector<SLine>& result);
GEOAPI void find_parallel(const std::vector<SLine>& all, 
                          const std::vector<int>& src,
                          const std::vector<int>& refer,
                          std::vector<int>& paral,
                          std::vector<int>& other);

GEOAPI Float get_degree(const Point &pt1,const Point &pt2);
GEOAPI Float get_degree(const Point &pt);
GEOAPI Float get_degree(const Point &pt0,const Point &pt1,const Point &pt2);
GEOAPI bool is_protruding(const std::vector<SLine> &sls);
GEOAPI bool is_in(const Box &rc,const std::vector<SLine> &sls);
GEOAPI bool is_cross(const Box &box,const std::vector<Box> &rcs);
GEOAPI void get_rect(const std::vector<SLine> &sls,Box &box);

GEOAPI typedef std::vector<SLine> Loop;
GEOAPI typedef std::vector<Loop> Loops;
GEOAPI bool find_loops(const std::vector<SLine> &slns,Loops &lps);


GEOAPI void arc2d(Arc& arc, const Point& c, Float r, Float srad, Float erad);
GEOAPI void arc2d(Arc& arc, const Point& c, const Point& s, const Point& e, const Point& p);

GEOAPI void set_arc_center(Arc& arc, const Point& c);
GEOAPI void set_arc_radius(Arc& arc, Float r);

GEOAPI Float arc2d_srad(const Arc& arc);
GEOAPI Float arc2d_erad(const Arc& arc);
GEOAPI void get_box(const Point &pt,Box &box);
GEOAPI Box get_arc_box(const Arc& arc);
GEOAPI bool is_arc2d(const Arc& arc);
GEOAPI bool is_arc(const Arc& arc);
GEOAPI bool is_ccw2d(const Arc& arc);
GEOAPI Point arc_middle_pt(const Arc& arc);
GEOAPI Float arc_middle_rad(const Arc& arc);
GEOAPI bool equ_dis_alignment_left(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs);
GEOAPI bool equ_dis_alignment_up(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs);
GEOAPI void left_alignment(const Rect_Box &base_box,Rect_Box &move_box);
GEOAPI void left_alignment(std::vector<Rect_Box> &boxs);
GEOAPI void right_alignment(const Rect_Box &base_box,Rect_Box &move_box);
GEOAPI void right_alignment(std::vector<Rect_Box> &boxs);
GEOAPI void up_alignment(const Rect_Box &base_box,Rect_Box &move_box);
GEOAPI void up_alignment(std::vector<Rect_Box> &boxs);
GEOAPI void down_alignment(const Rect_Box &base_box,Rect_Box &move_box);
GEOAPI void down_alignment(std::vector<Rect_Box> &boxs);
GEOAPI void middle_alignment_left(std::vector<Rect_Box> &boxs);
GEOAPI void middle_alignment_left(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs);
GEOAPI void middle_alignment_up(std::vector<Rect_Box> &boxs);
GEOAPI void middle_alignment_up(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs);

}
#endif
