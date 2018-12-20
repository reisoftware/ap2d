#include "StdAfx.h"
#include "calculate.h" 
#include "Point.h"
#include "Normal.h"
#include "global.h"
#include "Plane.h"

#include "LLine.h"
#include "SLine.h"
#include "RLine.h"
#include "Circle.h"
#include "Arc.h"
#include "GETRACE.h"
#define LIMIT		0.05

namespace geo{
const Plane xoy(0,0,1,0);		////xoy平面
const Point O(0,0,0);		////原点坐标
const Point ox(1,0,0);		////x轴的单位向量
const Point oy(0,1,0);		////y轴的单位向量
const Point oz(0,0,1);		////z轴的单位向量

Point project(const Point &pt)
//空间点在xoy平面上的投影
{
	Point ph(pt.x,pt.y,0);
	return ph;
}

Point operator * (const Point &vec1,const Point &vec2)
//重载两个三维矢量的矢量积
{
	Point vec_mul;
	vec_mul.x = (vec1.y) * (vec2.z) - (vec2.y) * (vec1.z);
	vec_mul.y = (vec2.x) * (vec1.z) - (vec1.x) * (vec2.z);
	vec_mul.z = (vec1.x) * (vec2.y) - (vec2.x) * (vec1.y);
	return vec_mul;
}

//两个三维矢量的三维点积，对应坐标相乘之和
Float multiply(const Point &vec1,const Point &vec2)
{
	Float num = (vec1.x) * (vec2.x) + (vec1.y) * (vec2.y) + (vec1.z) * (vec2.z);
	return num;
}

////重载两条线段完全相等（即完全重合，
////起点与起点为同一点，终点与终点为同一点
////或者起点与终点为同一点，终点与起点为同一点）
bool operator == (const LLine &ln1,const LLine &ln2)
{
	bool flag1 = (ln1.pt1 == ln2.pt1) && (ln1.pt2 == ln2.pt2);
	bool flag2 = (ln1.pt1 == ln2.pt2) && (ln1.pt2 == ln2.pt1);
	return flag1 || flag2;
}

////重载数右乘向量，与向量各个坐标相乘
Point operator * (const Point &vec_o,Float d)  //重载数乘三维向量
{
	Point vec_n;
	vec_n.x = (vec_o.x) * (d);
	vec_n.y = (vec_o.y) * (d);
	vec_n.z = (vec_o.z) * (d);
	return vec_n;
}

////重载数左乘向量，与向量各个坐标相乘
Point operator * (Float d,const Point &vec_o)  //重载数乘三维向量
{
	Point vec_n;
	vec_n.x = (vec_o.x) * (d);
	vec_n.y = (vec_o.y) * (d);
	vec_n.z = (vec_o.z) * (d);
	return vec_n;
}

//三维向量的模，即从原点到该向量点的长度
Float mos(const Point &vec)
{
	if(vec == O)
		return 0;
	return sqrt(multiply(vec,vec));
}

Point get_nor(const Plane &pla)  //取出平面的法向量
{
	Point nor;
	nor.x = pla.a;
	nor.y = pla.b;
	nor.z = pla.c;
	return nor;
}

Point normalize(const Point &vec)  //三维向量单位化
{
	if(vec == O)
		return vec;
	Float m = mos(vec);
	return vec * (1/m);
}

Float angle(const Point &vec1,const Point &vec2)  //两个向量的夹角
{
	Float angle = acos( multiply(vec1,vec2) / (mos(vec1) * mos(vec2)) );
	return angle;
}

//给出一个法向量，返回一个平面，d是平面的第四个坐标
Plane make_plane(const Point &nor,Float d)
{
	Plane pla;
	pla.a = nor.x;
	pla.b = nor.y;
	pla.c = nor.z;
	pla.d = d;
	return pla;
}

Plane make_plane(const Point &p1,const Point &p2,const Point &p3)
//利用三个点确定决定的平面
{
	Point po1 = p2 - p1;
	Point po2 = p3 - p2;
	Point nor = po1 * po2;
	Float d = -multiply(nor,p2);
	return make_plane(nor,d);
}

Plane make_plane(const Point &pt,const Point &nor)
//通过平面的法向量和其上一点求平面
{
	Plane pla(nor.x,nor.y,nor.z,-multiply(pt,nor));
	return pla;
}

Plane make_plane(const LLine &ln1,const LLine &ln2)
//求两条共面直线确定的平面
{
	if( !relation(ln1,ln2))
		return make_plane(ln1.pt1,ln1.pt2,ln2.pt1);
	else{
		Point nor1 = ln1.pt2 - ln1.pt1;
		Point nor2 = ln2.pt2 - ln2.pt1;
		Point nor = nor1 * nor2;
		return make_plane(ln1.pt1,nor);
	}
}

SLine create_sline(const Point &pt1,const Point &pt2)
//两点做线段
{
	SLine sl;
	sl.pt1 = pt1;
	sl.pt2 = pt2;
	return sl;
}

LLine create_line(const Point &pt1,const Point &pt2)
//两点做直线
{
	LLine ln;
	ln.pt1 = pt1;
	ln.pt2 = pt2;
	return ln;
}

LLine make_line(const Point &pt,const Point &vec)
//已知直线的方向向量和其上一点，求直线
{
	LLine ln;
	ln.pt1 = pt;
	ln.pt2 = pt +  normalize(vec) * 10;
	return ln;
}

Float distance(const Point &p1,const Point &p2)  //空间两点之间的距离
{
	return mos(p1 - p2);
}

Float distance2d(const Point &pt1,const Point &pt2)
//二维空间内两点之间的距离
{
	Point ph1 = project(pt1);
	Point ph2 = project(pt2);
	return mos(ph1 - ph2);
}

LLine project(const LLine &ln)
//直线在xoy平面上的投影
{
	LLine lh;
	lh.pt1 = project(ln.pt1);
	lh.pt2 = project(ln.pt2);
	return lh;
}

RLine project(const RLine &rl)
//射线在xoy平面上的投影
{
	RLine rh;
	rh.pt1 = project(rl.pt1);
	rh.pt2 = project(rl.pt2);
	return rh;
}

SLine project(const SLine &sl)
//线段在xoy平面上的投影
{
	SLine sh;
	sh.pt1 = project(sl.pt1);
	sh.pt2 = project(sl.pt2);
	return sh;
}

LLine make_line(const RLine &rl)
//射线做直线
{
	LLine ln;
	ln.pt1 = rl.pt1;
	ln.pt2 = rl.pt2;
	return ln;
}

LLine make_line(const SLine &sl)
//线段做直线
{
	LLine ln;
	ln.pt1 = sl.pt1;
	ln.pt2 = sl.pt2;
	return ln;
}

bool relation(const Point &pt,const RLine &ray)
//判断点在射线上，在射线上返回真，否则返回假
{
	if(pt == ray.pt1)
		return true;
	else
		return normalize(pt - ray.pt1) == normalize(ray.pt2 - ray.pt1);
}

bool relation(const Point &pt,const SLine &sl)
//判断点在线段上，在线段上返回真，否则返回假
{
	if(pt == sl.pt1 || pt == sl.pt2)
		return true;
	else{
		Point vec1 = normalize(sl.pt1 - pt);
		Point vec2 = normalize(sl.pt2 - pt);
		return vec1 == (vec2 * (-1));
	}
}

bool operator > (const Point &p1,const Point &p2)
//直线上对点排序，重载点p1 > p2
{
	if (more_than(p1.x,p2.x))
		return true;
	else if (less_than(p1.x,p2.x))
		 return false;
	else if (more_than(p1.y,p2.y))
		 return true;
	else if (less_than(p1.y,p2.y))
		 return false;
	else if (more_than(p1.z,p2.z))
		return true;
	else
		return false;
}

bool operator < (const Point &p1,const Point &p2)
//直线上对点排序，重载点p1 < p2
{
	if (less_than(p1.x,p2.x))
		return true;
	else if (more_than(p1.x,p2.x))
		return false;
	else if (less_than(p1.y,p2.y))
		return true;
	else if (more_than(p1.y,p2.y))
		return false;
	else if (less_than(p1.z,p2.z))
		return true;
	else
		return false;
}

Float distance(const Point &p,const LLine &ln)  //点到空间直线的距离
{
	Point direction_vector = ln.pt2 - ln.pt1;
	Point p_p1 = ln.pt1 - p;
	Point vector_mul = p_p1 * direction_vector;
	Float dis = mos(vector_mul) / mos(direction_vector); 
	return dis;
}

Float distance2d(const Point &p,const LLine &ln)
//二维空间内点到直线的距离
{
	Point ph = project(p);
	LLine lnh = project(ln);
	return distance(ph,lnh);
}

Float distance(const Point &p,const Plane &pla)  //点到平面的距离
{
	Point nor = get_nor(pla);
	Float dis = fabs(multiply(p,nor) + pla.d) / mos(nor);
	return dis;
}

Point project(const Point &p,const LLine &ln)
//计算点在空间直线上的投影坐标
{
	Float h = distance(p,ln);
	if(equ(h,0))
		return p;
	else{
		Point vecl = ln.pt2 - ln.pt1;
		Point vechs = p - ln.pt1;
		if(equ(multiply(vecl,vechs),0))
			return ln.pt1;
		else{
			Point veche = p - ln.pt2;
			if(equ(multiply(vecl,veche),0))
				return ln.pt2;
			else{
				Float pp1 =  mos(vechs);
				Float dis = sqrt(pp1 * pp1 - h * h);
				Point vec =  normalize(vecl);
				Point p1 = ln.pt1 + vec * dis;
				Point p2 = ln.pt1 - vec * dis;
				Point vec1 = p1 - p;
				return ( equ(multiply(vecl,vec1),0)) ? p1 : p2;
			}
		}
	}
}

Point project2d(const Point &pt,const LLine &ln)
//二维空间内求点到直线的投影
{
	Point pth = project(pt);
	LLine lnh = project(ln);
	return project(pth,lnh);
}

////下面函数专用：两条共面直线斜交时求交点pt
////sign是两条直线在当前坐标下是否分离
static void intersect(const LLine &ln1,const LLine &ln2,int sign,Point &pt)
{
	Float dis1 = distance(ln1.pt1,ln2);
	Float dis2 = distance(ln1.pt2,ln2);
	if(!sign){
		if(equ(dis1,0))
			pt = ln1.pt1;
		else if(equ(dis2,0))
			pt = ln1.pt2;
		else if(equ(distance(ln2.pt1,ln1),0))
			pt = ln2.pt1;
		else
			pt = ln2.pt2;
	}
	else{
		Float num = (sign == -1) ? (dis1 - dis2) : (dis1 + dis2);
		Float d = distance(ln1.pt1,ln1.pt2);
		Float dis = dis1 * d / num;
		Point pp = normalize(ln1.pt2 - ln1.pt1) * dis;
		pt = pp + ln1.pt1;
	} 
}

//空间两条直线的交点,无交点返回假，有交点则写入参数3
bool intersect(const LLine &ln1,const LLine &ln2,Point &pt)
{
	int flag = relation(ln1,ln2);
	if(flag < 1 || flag > 2)
		return 0;
	else if(flag == 2){
		int sign = dline_leave(make_sline(ln1),make_sline(ln2));
		intersect(ln1,ln2,sign,pt);
		return 1;
	}
	else if(flag == 1){
		pt = project(ln1.pt1,ln2);
		return 1;
	}
	return 0;
}

//判断两个三维向量的关系，平行返回0，垂直返回1，其它返回2
int relation(const Point &vec1,const Point &vec2)  
{
	Point vec1_normalize = normalize(vec1);
	Point vec2_normalize = normalize(vec2);
	Point reverse = vec2_normalize * (-1);
	bool vec1_vec2 = (vec1_normalize == vec2_normalize);
	bool vec1_rev = (vec1_normalize == reverse);
	if( vec1 == vec2 || vec1_vec2 || vec1_rev )
		return 0;
	else
		return (equ(multiply(vec1,vec2),0)) ? 1 : 2;
}

//判断空间三点关系，有重合或共线返回假，构成三角形则返回真
bool relation(const Point &p1,const Point &p2,const Point &p3)
{
	if(p1 == p2 || p2 == p3 || p1 == p3)
	  return false;
	else{
		Point vec1 = p2 - p1;
		Point vec2 = p2 - p3;
		return (relation(vec1,vec2)) ? true : false;
	}
}

//计算点在任意平面上的投影坐标
Point project(const Point &pt,const Plane &pla)
{
	double h = distance(pt,pla);	
	if(equ(h,0))
		return pt;
	else{
		Point vec = get_nor(pla);
		Point nor = normalize(vec);
		Point pt1 = pt + nor * h;
		Point pt2 = pt - nor * h;
		double num = multiply(pt1,vec) + pla.d;
		return (equ(num,0)) ? pt1 : pt2;
	}
}

//判断两个平面的位置关系，重合返回-1，平行返回0，垂直返回1，其它返回2
int relation(const Plane &pla1,const Plane &pla2)
{
	Point nor1 = get_nor(pla1);
	Point nor2 = get_nor(pla2);
	Point norh = project(nor1,pla1);
	double num1 = distance(norh,pla2);
	double num2 = multiply(nor1,nor2);
	if( !relation(nor1,nor2) )
		return equ(num1,0) ? -1 : 0;
	else
		return equ(num2,0) ? 1 : 2;
}

//直线和平面的位置关系，直线在平面上返回-1，直线平行于平面返回0
//直线垂直平面返回1，其它返回2
int relation(const LLine &ln,const Plane &pla)  
{
	Point nor = get_nor(pla);
	Point vec = ln.pt2 - ln.pt1;
	Float num1 = multiply(ln.pt1,nor) + pla.d;
	Float num2 = multiply(ln.pt2,nor) + pla.d;
	bool flag = equ(num1,0);
	if(flag && equ(num2,0))
		return -1;
	else if( !flag && equ(multiply(nor,vec),0))
		return 0;
	else
		return relation(nor,vec) ? 2 : 1;
}

//求空间直线和平面的交点，没有交点则返回假，有交点则写入参数3
bool intersect(const LLine &ln,const Plane &pla,Point &pt)
{
	int flag = relation(ln,pla);
	if(flag < 1)
		return false;
	Point ph1 = project(ln.pt1,pla);
	if(flag == 1){
		pt = ph1;
		return true;
	}
	Point ph2 = project(ln.pt2,pla);
	LLine lnh(ph1,ph2);
	return intersect(ln,lnh,pt);
}

//在两个平面外求一点，仅下面求交线函数调用
static Point get_separate_pt(const Plane &pla1,const Plane &pla2,const Point &nor1)
{
	Point pt = nor1,pt1,pt2;
	pt1 = nor1 * 2;
	pt2 = nor1 * 3;
	if(equ(distance(pt,pla1),0))
		return equ(distance(pt1,pla2),0) ? pt2 : pt1;
	else if(equ(distance(pt,pla2),0))
		return equ(distance(pt1,pla1),0) ? pt2 : pt1;
	else
		return pt;
}

/*
bool intersect(const Plane &pla1,const Plane &pla2,LLine &ln)
//求两个平面的交线，两平面平行或重合时返回假
{
	if(relation(pla1,pla2) < 1)
		return false;
	Point nor1 = get_nor(pla1);
	Point nor2 = get_nor(pla2);
	Point vec = nor1 * nor2;
	Point pt = get_separate_pt(pla1,pla2,nor1);
	Point ph1 = project(pt,pla1);
	Point ph2 = project(pt,pla2);
	Point nor = (pt - ph1) * (pt - ph2);
	Point vec1 = nor * nor1;
	Point vec2 = nor * nor2;
	LLine ln1 = make_line(ph1,vec1);
	LLine ln2 = make_line(ph2,vec2);
	Point cross;
	intersect(ln1,ln2,cross);
	ln = make_line(cross,vec);
	return true;
}*/

//求空间任意两个平面的交线，两平面平行或重合时返回假
bool intersect(const Plane &pla1,const Plane &pla2,LLine &line)
{
	if(relation(pla1,pla2) < 1)
		return false;
	else{
		Point vec = get_nor(pla1) * get_nor(pla2);
		bool cs1 = equ(vec.x,0);
		bool cs2 = equ(vec.y,0);
		bool cs3 = equ(vec.z,0);
		Float a1 = pla1.a, b1 = pla1.b, c1 = pla1.c, d1 = pla1.d;
		Float a2 = pla2.a, b2 = pla2.b, c2 = pla2.c, d2 = pla2.d;
		Float x0, y0, z0;
		Point pt;
		if( (cs1 && !(cs2 || cs3)) || (!cs2 && cs1 && cs3) ){
			x0 = (c1*d2 - c2*d1) / (a1*c2 - a2*c1);
			z0 = (a2*d1 - a1*d2) / (a1*c2 - a2*c1);
			pt.set(x0,0,z0);
		}
		else if( (cs2 && !(cs1 || cs3)) || (cs3 && !(cs1 || cs2)) || (!cs1 && cs2 && cs3) ){
			y0 = (c1*d2 - c2*d1) / (b1*c2 - b2*c1);
			z0 = (b2*d1 - b1*d2) / (b1*c2 - b2*c1);
			pt.set(0,y0,z0);
		}
		else if( (!cs3 && cs1 && cs2) || !(cs1 || c2 || cs3) ){
			x0 = (b1*d2 - b2*d1) / (a1*b2 - a2*b1);
			y0 = (a2*d1 - a1*d2) / (a1*b2 - a2*b1);
			pt.set(x0,y0,0);
		}
		line = make_line(pt,vec);
		return true;
	}
}

//判断空间两条直线是否重合,重合返回真，否则为假
bool superposition(const LLine &ln1,const LLine &ln2)
{
	Float d1 = distance(ln2.pt1,ln1);
	Float d2 = distance(ln2.pt2,ln1);
	return equ(d1,0) && equ(d2,0);
}

//判断二维空间两条直线是否重合,重合返回真，否则为假
bool superposition2d(const LLine &ln1,const LLine &ln2)
{
	LLine lnh1 = project(ln1);
	LLine lnh2 = project(ln2);
	return superposition(lnh1,lnh2);
}

//判断空间两条直线是否平行,平行返回真，否则为假
bool parallel(const LLine &ln1,const LLine &ln2)
{
	Point vec1 = ln1.pt2 - ln1.pt1;
	Point vec2 = ln2.pt2 - ln2.pt1;
	int parallel = relation(vec1,vec2);
	bool superposit = superposition(ln1,ln2);
	return !superposit && !parallel;
}

//判断空间两条线段是否平行,平行返回真，否则为假
bool parallel(const SLine &sl1,const SLine &sl2)
{
	Point vec1 = sl1.pt2 - sl1.pt1;
	Point vec2 = sl2.pt2 - sl2.pt1;
	int parallel = relation(vec1,vec2);
	bool superposit = superposition(make_line(sl1),make_line(sl2));
	return !superposit && !parallel;
}

//判断空间两条直线是否相交,相交返回真，否则为假
bool intersection(const LLine &ln1,const LLine &ln2)
{
	bool superposit = superposition(ln1,ln2);
	bool para = parallel(ln1,ln2);
	if(superposit || para)
		return false;
	else{
		bool jug1 = relation(ln1.pt1,ln1.pt2,ln2.pt1);
		bool jug2 = relation(ln1.pt1,ln1.pt2,ln2.pt2);
		if(!jug1 || !jug2)
			return true;
		else{
			Plane pla1 = make_plane(ln1.pt1,ln1.pt2,ln2.pt1);
			Plane pla2 = make_plane(ln1.pt1,ln1.pt2,ln2.pt2);
			Point nor1 = get_nor(pla1);
			Point nor2 = get_nor(pla2);
			int nor = relation(nor1,nor2);
			return (nor) ? false : true;
		}
	}
}

//空间两条直线的位置关系
//重合返回-1，平行返回0，相交时垂直返回1，斜交返回2
//异面返回3
int relation(const LLine &ln1,const LLine &ln2)
{
	Point vec1 = ln1.pt2 - ln1.pt1;
	Point vec2 = ln2.pt2 - ln2.pt1;
	Float num_vec = multiply(vec1,vec2);
	bool superposit = superposition(ln1,ln2);
	bool intersect = intersection(ln1,ln2);
	bool parall = parallel(ln1,ln2);
	if(superposit)
		return -1;
	else if(parall)
		return 0;
	else if(intersect)
		return (equ(num_vec,0)) ? 1 : 2;
	else
		return 3;
}

//直线ln上一点在xoy面上的投影是ph,恢复ph在ln上的点
Point resume_point(const Point &ph,const LLine &ln)
{
	bool flag_x = equ(ln.pt1.x,ln.pt2.x);
	bool flag_y = equ(ln.pt1.y,ln.pt2.y);
	if(flag_x && flag_y)
		return ln.pt1;
	Point pt = ph;
	Float num = ln.pt2.z - ln.pt1.z;
	Float z1 = (ph.x - ln.pt1.x) * num / (ln.pt2.x - ln.pt1.x) + ln.pt1.z;
	Float z2 = (ph.y - ln.pt1.y) * num / (ln.pt2.y - ln.pt1.y) + ln.pt1.z;
	pt.z = (flag_x) ? z2 : z1;
	return pt;
}

//平面pla上一点在xoy面上的投影是ph,恢复ph在pla上的点
Point resume_point(const Point &ph,const Plane &pla)
{
	if(equ(distance(ph,pla),0))
		return ph;
	Float z = (pla.a * ph.x + pla.b * ph.y + pla.d) / (-pla.c);
	Point pt(ph.x,ph.y,z);
	return pt;
}

//Lh为pla上直线在xoy平面上的投影，恢复Lh在pla上的直线
LLine resume_line(const LLine &lh,const Plane &pla)
{
	LLine ln;
	ln.pt1 = resume_point(lh.pt1,pla);
	ln.pt2 = resume_point(lh.pt2,pla);
	return ln;
}

SLine make_sline(const LLine &ln)  //直线做线段
{
	SLine sl;
	sl.pt1 = ln.pt1;
	sl.pt2 = ln.pt2;
	return sl;
}

//共面线段的相交关系
//无穿透相交返回0，在同一侧返回-1，其它返回1
int dline_leave(const SLine &sl1,const SLine &sl2)
{
	LLine ln1 = make_line(sl1);
	LLine ln2 = make_line(sl2);
	Float dis1 = distance(sl1.pt1,ln2);
	Float dis2 = distance(sl1.pt2,ln2);
	Float dis3 = distance(sl2.pt1,ln1);
	Float dis4 = distance(sl2.pt2,ln1);
	bool flag1 = equ(dis1,0) || equ(dis2,0);
	bool flag2 = equ(dis3,0) || equ(dis4,0);
	if(flag1 || flag2)
		return 0;
	else{
		Point ph1 = project(sl1.pt1,ln2);
		Point ph2 = project(sl1.pt2,ln2);
		Point vec1 = normalize(ph1 - sl1.pt1);
		Point vec2 = normalize(ph2 - sl1.pt2);
		return (vec1 == vec2) ? -1 : 1;
	}
}

Point make_point(const Normal &nor) //Normal 转Point
{
	Point pt;
	pt.set(nor.x,nor.y,nor.z);
	return pt;
}

//空间共面的直线和圆的交点，返回交点个数
//有两个交点时交点写入cross1和cross2，有一个交点时交点写入cross1
int intersect(const LLine &ln,const Circle &c,Point &cross1,Point &cross2)
{
	Float d = distance(c.center,ln);
	Point ch = project(c.center,ln);
	Point vec = normalize(ln.pt2 - ln.pt1);
	if(more_than(c.radius,d)){
		Float h = sqrt(pow(c.radius,2) - d * d);
		cross1 = ch + vec * h;
		cross2 = ch - vec * h;
		return 2;
	}
	else if(equ(d,c.radius)){
		cross1 = ch;
		return 1;
	}
	else
		return 0;
}

Normal make_nor(const Point &pt) //点转换Normal
{
	Normal nor;
	nor.set(pt.x,pt.y,pt.z);
	return nor;
}

void resume_circle(const Arc &arc,Circle &c)  //恢复圆弧对应的圆
{
	Plane pla = make_plane(arc.start,arc.end,arc.path);
	Point nor = get_nor(pla);
	c.nor = make_nor(nor);
	Point mid1 = (arc.start + arc.path) * 0.5;
	Point mid2 = (arc.end + arc.path) * 0.5;
	Point vec1 = (arc.path - arc.start) * nor;
	Point vec2 = (arc.path - arc.end) * nor;
	LLine ln1 = make_line(mid1,vec1);
	LLine ln2 = make_line(mid2,vec2);
	Point pt;
	intersect(ln1,ln2,pt);
	c.center = pt;
	c.radius = distance(c.center,arc.start);
}

//判断点在圆弧上，不在圆弧上返回假，否则返回真
bool relation(const Point &pt,const Arc &arc)
{
	Plane pla = make_plane(arc.start,arc.end,arc.path);
	if(!equ(distance(pt,pla),0))
		return false;
	Circle c;
	resume_circle(arc,c);
	if(relation(pt,c))
		return false;
	if(pt == arc.start || pt == arc.end)
		return true;
	SLine sl1 = create_sline(arc.start,arc.end);
	SLine sl2 = create_sline(pt,arc.path);
	Point cross;
	return !intersect(sl1,sl2,cross);
}

//求圆所在的平面
Plane make_plane(const Circle &c)
{
	Point nor = make_point(c.nor);
	return make_plane(c.center,nor);
}

//点和圆的位置关系,点不在圆所在的平面上返回-2
//点在圆上返回0，在圆外返回1，在园内返回-1
int relation(const Point &pt,const Circle &c)
{
	Plane pla = make_plane(c);
	Float dis1 = distance(pt,pla);
	if(!equ(dis1,0))
		return -2;
	Float dis2 = distance(pt,c.center);
	if(equ(dis2,c.radius))
		return 0;
	else
		return more_than(dis2,c.radius) ? 1 : -1;
}

//求三角形的外接圆
Circle make_circle(const Point &pt1,const Point &pt2,const Point &pt3)
{
	Arc arc(pt1,pt2,pt3);
	Circle c;
	resume_circle(arc,c);
	return c;
}

//空间共面的直线和圆弧的交点，返回交点个数
//有两个交点时交点写入cross1和cross2，有一个交点时交点写入cross1
int intersect(const LLine &ln,const Arc &arc,Point &cross1,Point &cross2)
{
	Circle c;
	resume_circle(arc,c);
	Point p1,p2;
	int n = intersect(ln,c,p1,p2);
	int i = 0,j = 0;
	if(n == 2){
		if(relation(p1,arc))
			i++;
		if(relation(p2,arc))
			j++;
		if(i + j == 1)
			cross1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			cross1 = p1;
			cross2 = p2;
		}
		return i + j;
	}
	else if(n == 1){
		if(relation(p1,arc)){
			cross1 = p1;
			i++;
		}
		return i;
	}
	else
		return 0;
}

/////共面的线段和直线的交点，交点写入参数pt，无交点返回假
bool intersect(const SLine &sl,const LLine &ln,Point &pt)
{
	LLine lnx = make_line(sl);
	Point px;
	bool flag = intersect(lnx,ln,px);
	if(!flag)
		return false;
	else if(relation(px,sl)){
		pt = px;
		return true;
	}
	else
		return false;
}

////共面的两线段的交点，交点写入参数pt，无交点返回假
bool intersect(const SLine& sl1, const SLine& sl2, Point& pt)
{
	LLine slh1 = make_line(sl1);
	LLine slh2 = make_line(sl2);
	Point ph;
	bool flag = intersect(slh1,slh2,ph);
	if(!flag)
		return false;
	else if(relation(ph,sl1) && relation(ph,sl2)){
		pt = ph;
		return true;
	}
	else
		return false;
}

////共面的线段和圆弧的交点，返回交点个数
//有两个交点时交点写入cross1和cross2，有一个交点时交点写入cross1
int intersect(const SLine &sl,const Arc &arc,Point &cross1,Point &cross2)
{
	LLine ln = make_line(sl);
	Point p1,p2;
	int flag = intersect(ln,arc,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){ 
		if(relation(p1,sl))
			i++;
		if(relation(p2,sl))
			j++;
		if(i + j == 1)
			cross1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			cross1 = p1;cross2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		if(relation(p1,sl)){
			cross1 = p1;
			i++;
		}
		return i;
	}
	else
		return 0;
}

////共面的线段和圆的交点，返回交点个数
//有两个交点时交点写入cross1和cross2，有一个交点时交点写入cross1
int intersect(const SLine &sl,const Circle &c,Point &cross1,Point &cross2)
{
	LLine ln = make_line(sl);
	Point p1,p2;
	int flag = intersect(ln,c,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){ 
		if(relation(p1,sl))
			i++;
		if(relation(p2,sl))
			j++;
		if(i + j == 1)
			cross1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			cross1 = p1;cross2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		if(relation(p1,sl)){
			cross1 = p1;
			i++;
		}
		return i;
	}
	else
		return 0;
}

//判断两个圆是否共面，不共面返回假
bool is_conplane(const Circle &c1,const Circle &c2)
{
	Plane pla1 = make_plane(c1);
	Plane pla2 = make_plane(c2);
	Point nor1 = normalize(get_nor(pla1));
	Point nor2 = normalize(get_nor(pla2));
	bool flag = (nor1 == nor2) || (nor1 == (nor2 * (-1)));
	if(!flag)
		return false;
	Float dis = distance(c1.center,pla2);
	return equ(dis,0);
}

//两个圆的位置关系,不共面时返回-1
//完全相离返回0，外切返回1，内切不重合返回2，完全内包含返回3
//完全重合返回4，一般相交返回5
int relation(const Circle &c1,const Circle &c2)
{
	bool flag = is_conplane(c1,c2);
	if(!flag)
		return -1;
	Float dis = distance(c1.center,c2.center);
	Float dsum = c1.radius + c2.radius;
	Float dif = fabs(c1.radius - c2.radius);
	if(more_than(dis,dsum))
		return 0;
	else if(equ(dis,dsum))
		return 1;
	else if(equ(dis,dif) && !(c1.center == c2.center))
		return 2;
	else if( less_than(dis,dif) )
		return 3;
	else
		return (c1.center == c2.center) && equ(c1.radius,c2.radius) ? 4 : 5;
}

//判断圆c1是否在共面的圆c2里面
bool dcircle_in(const Circle &c1,const Circle &c2)
{
	int flag = relation(c1,c2);
	if(flag == 2 || flag == 3)
		return less_than(c1.radius,c2.radius);
	return false;
}

//圆c投影在xoy平面上，ph为投影椭圆上一点，恢复ph在圆c上的点
Point resume_point(const Point &ph,const Circle &c)
{
	Plane pla = make_plane(c.center,make_point(c.nor));
	return resume_point(ph,pla);
}

//角度转换弧度
Float convert_degree(const Float &degree)
{
  return degree * geo::pi() / 180.0;
}

//弧度转换角度
Float convert_radian(const Float &radian)
{
	return radian*180.0 / geo::pi();
}

//二维空间内点pl和方向vec决定直线L,求pl到pt在L上的投影的距离
//方向vec决定距离的负号
Float dis2d(const Point &pl,const Point &pt,const Normal &vec)
{
	Point direction = make_point(vec);
	Point plh = project(pl);
	Point pth = project(pt);
	Point vech = project(direction);
	LLine lnh = make_line(plh,vech);
	Point phh = project(pth,lnh);
	Float dis = distance(plh,phh);
	return (normalize(vech) == normalize(phh - plh)) ? dis : (-dis);
}

//二维空间内点pt在直线ln上的投影和方向vec决定直线L
//求投影点到pt在L上的投影的距离，方向vec决定距离的负号
Float dis2d(const Point &pt,const LLine &ln,const Normal &vec)
{
	Point pth = project(pt);
	LLine lnh = project(ln);
	Point direction = make_point(vec);
	Point vech = project(direction);
	Point phh = project(pth,lnh);
	LLine newh = make_line(phh,vech);
	Point pthh = project(pth,newh);
	Float dis = distance(phh,pthh);
	return (normalize(vech) == normalize(pthh - phh)) ? dis : (-dis);
}

//二维空间内求过点pt且平行于直线ln的直线
LLine offset2d(const Point &pt,const LLine &ln)
{
	Point pth = project(pt);
	LLine lnh = project(ln);
	Point vech = lnh.pt2 - lnh.pt1;
	return make_line(pth,vech);
}

//二维空间内求直线lnsourse沿pt方向平移dis距离后的直线
LLine offset2d(const LLine &lnsourse,const Point &pt,Float dis)
{
	Point pth = project(pt);
	LLine lnh = project(lnsourse);
	Point pthh = project(pth,lnh);
	if(pth == pthh)
		return lnh;
	else{
		Point vech = normalize(pth - pthh);
		Point pxh = pthh + vech*dis;
		Point vecl = lnh.pt2 - lnh.pt1;
		return make_line(pxh,vecl);
	}
}

//二维空间内求任意垂直于ln的直线
LLine erect2d(const LLine &ln)
{
	LLine lnh = project(ln);
	Point vec = lnh.pt2 - lnh.pt1;
	Point vech;
	vech.set(-vec.y,vec.x,0);
	return make_line(lnh.pt1,vech);
}

//二维空间内求过点垂直于ln的直线
LLine erect2d(const Point &pt,const LLine &ln)
{
	Point pth = project(pt);
	LLine lnh = project(ln);
	Point vec = lnh.pt2 - lnh.pt1;
	Point vech;
	vech.set(-vec.y,vec.x,0);
	return make_line(pth,vech);
}

//二维空间内求点center到pt的方向与x轴正向的逆时针角
Float get_angle2d(const Point &pt,const Point &center)
{
	Point vec;
	vec.set(pt.x - center.x,pt.y - center.y,0);
	Float ang = angle(vec,ox);
	if(more_equ(vec.y,0))
		return ang;
	else
		return 2 * geo::pi() - ang;
}

//二维空间内求圆弧的中分角
Float bisector_radian2d(const Arc &arc)
{
	Circle c;
	resume_circle(arc,c);
	Float ang_start = get_angle2d(arc.start,c.center);
	Float ang_end = get_angle2d(arc.end,c.center);
	Float ang = (ang_start + ang_end) / 2;
	if(more_equ(ang_start,ang_end))
		return ang + geo::pi();
	else
		return ang;
}

//求圆弧上两点之间的弧中点，参数4是该弧对应的圆
Point middle_point(const Arc &arc,const Point &p1,const Point &p2,const Circle &c)
{
	Point middle = (p1 + p2) * 0.5;
	Point vecl = p1 - p2;
	Point vecn = make_point(c.nor) * vecl;
	Point vec = normalize(vecn);
	Point pt1 = c.center + vec * c.radius;
	Point pt2 = c.center - vec * c.radius;
	SLine sl1 = create_sline(p1,p2),sl2;
	bool flag1 = p1 == arc.start && p2 == arc.end;
	bool flag2 = p1 == arc.end && p2 == arc.start;
	if(flag1 || flag2)
		return (relation(pt1,arc)) ? pt1 : pt2;
	else if(p1 == arc.start && p2 != arc.end)
		sl2 = create_sline(pt1,arc.end);
	else
		sl2 = create_sline(pt1,arc.start);
	Point cross;
	return (intersect(sl1,sl2,cross)) ? pt1 : pt2;
}

//求圆弧的弧中点
Point bisector_point2d(const Arc &arc)
{
	Circle c;
	resume_circle(arc,c);
	return middle_point(arc,arc.start,arc.end,c);
}

//求圆弧的弧中线
LLine bisector_line2d(const Arc &arc)
{
	Circle c;
	resume_circle(arc,c);
	Point mid = middle_point(arc,arc.start,arc.end,c);
	return create_line(c.center,mid);
}

//二维空间内过点pt做x轴正向成angle角度的直线，在直线上平移pt一个单位
Point polarto2d(const Point &pt,Float angle)
{
	Point px;
	px.set(pt.x + cos(angle),pt.y + sin(angle),0);
	return px;
}

//二维空间内过点pt做x轴正向成angle角度的直线
LLine make_line(const Point &pt,Float angle)
{
	Point pth = project(pt);
	Point pxh = polarto2d(pt,angle);
	return create_line(pth,pxh);
}

//二维空间内求弧度数对应的方向
Normal convert2d(Float angle)
{
	Normal vec;
	vec.set(cos(angle),sin(angle),0);
	return vec;
}

//二维空间内过ptbase做平行于lnbase的直线L，求pt在L上的投影
Point project2d(const Point &pt,const LLine &lnbase,const Point &ptbase)
{
	LLine lnh = offset2d(ptbase,lnbase);
	Point pth = project(pt);
	return project(pth,lnh);
}

//二维空间内求方向direction关于x轴的逆时针角
Float radian2d(const Normal &direction)
{
	Point vec = make_point(direction);
	return get_angle2d(vec,O);
}

//二维空间内求两点所确定的方向关于x轴的逆时针角
Float radian2d(const Point &ptend,const Point &ptstart)
{
	Point vec = ptend - ptstart;
	return get_angle2d(vec,O);
}

Float radian2d(const LLine &ln)
//二维空间内求直线所对应的关于x轴的逆时针角
{
	Point vec = ln.pt2 - ln.pt1;
	return get_angle2d(vec,O);
}

Float stdradian(Float radian)
//化一般弧度为[0,2*PI)之间的弧度
{
	Float result = radian;
	Float pai2 = 2 * geo::pi();
	while(less_than(result,0))
		result += pai2;
	while(more_equ(result,pai2))
		result -= pai2;
	return result;
}

Float stdangle(Float angle)
//化一般角度为[0,360)之间的角度
{
	Float result = angle;
	while(less_than(result,0))
		result += 360;
	while(more_equ(result,360))
		result -= 360;
	return result;
}

//根据不同的情况返回弧度数所在的象限
//当开关on_off为真时，x正轴包括在第一象限，y正轴包括在第二象限，以此类推；
//当开关on_off为假时，x正轴包括在第四象限，y正轴包括在第一象限，以此类推；
int quadrant(Float radian,const bool &on_off)
{
	Float result = stdradian(radian);
	Float pai = geo::pi() / 2;
	int n = result / pai;
	if(on_off)
		return n+1;
	else{
		if(equ(result,0))
			return 4;
		else if(equ(result,pai))
			return 1;
		else if(equ(result,2 * pai))
			return 2;
		else if(equ(result,3 * pai))
			return 3;
		else
			return n + 1;
	}
}
//点和平面的位置关系
//点在平面上返回0，平面垂直于xoy面时返回-2，点在平面上方返回1，在下方返回-1
int relation(const Point& pt,const Plane& pla)
{
	Float dis = distance(pt,pla);
	if(equ(dis,0))
		return 0;
	if(equ(pla.c,0))
		return -2;
	Float zh = -(pla.d + pla.a * pt.x + pla.b * pt.y) / pla.c;
	return less_than(zh,pt.z) ? 1 : -1;
}

////////求多边形最小面积的外接矩形////////////////////

////直线和多边形的穿透关系,不穿透返回真，穿透返回假
////直线只经过某边界时视为不穿透
static bool penetrate_relation(const LLine& ln,const std::vector<Point>& pts)
{
	int i,j;
	bool flag = 1;
	Point vec_normalize,ph;
	for(i = 0;i < pts.size();i++){
		if(!equ(distance(pts[i],ln),0)){
			ph = project(pts[i],ln);
			vec_normalize = normalize(pts[i] - ph);
			break;
		}
	}
	for(j = i+1;j < pts.size();j++){
		if(!equ(distance(pts[j],ln),0)){
			Point ph_temp = project(pts[j],ln);
			Point vec_normalize_temp = normalize(pts[j] - ph_temp);
			if(vec_normalize != vec_normalize_temp){
				flag = 0;
				break;
			}
		}
	}
	return flag;
}
////标记每个多边形顶点是凸点还是凹点
////真表示凸点，假表示凹点
static void get_flags(const std::vector<Point>& pts,std::vector<bool>& flags)
{
	if(pts.size() <2)
		return;
	int i,j;
	LLine ln;
	for(i = 0;i < pts.size()-1;i++){
		j = i;
		ln = create_line(pts[i],pts[++j]);
		flags.push_back(penetrate_relation(ln,pts));
	}
	ln = create_line(pts[pts.size()-1],pts[0]);
	flags.push_back(penetrate_relation(ln,pts));
}

static void get_chimb(const std::vector<Point>& pts,std::vector<Point>& chimb)
////取多边形的凸包，即挑出每个凸点，顺序不变
{
  if(pts.empty()){
    return;
  }
	std::vector<bool> flags;
	get_flags(pts,flags);
  if(flags.empty()){
    return;
  }
	if(flags[0] || flags[flags.size()-1])
		chimb.push_back(pts[0]);
	int i, n = pts.size();
	for(i = 1;i < n;i++){
		if(flags[i-1] || flags[i])
			chimb.push_back(pts[i]);
	}
}

static Float get_area(const LLine& ln,const std::vector<Point>& pts)
////得到凸多边形以ln为基边的外接矩形面积
{
	std::set<Point> pro_pts;
	Float max_high = 0,high;
	int i, n = pts.size();
	for(i = 0;i < n;i++){
		pro_pts.insert(project(pts[i],ln));
		high = distance(pts[i],ln);
		if(more_than(high,max_high))
			max_high = high;
	}
	Float len = distance(*(pro_pts.begin()),*(--pro_pts.end()));
	return max_high * len;
}

Float get_min_area(const std::vector<Point>& pts)
////得到多边形的最小外接矩形面积
{
	if(pts.size() <1)
		return -1;
	std::vector<Point> chimb;
	get_chimb(pts,chimb);
	int n = chimb.size();
	if(n < 3)
		return -1;
	int i,j;
	LLine ln = create_line(chimb[0],chimb[n-1]);
	Float min_area = get_area(ln,chimb);
	Float area;
	for(i = 0;i < n-1;i++){
		j = i;
		ln = create_line(chimb[i],chimb[++j]);
		area = get_area(ln,chimb);
		if(less_than(area,min_area))
			min_area = area;
	}
	return min_area;
}

///// to zhong /////
////把pt点沿着垂直于ln的方向平移dis距离
////sign_pt是平移方向，sign_pt在直线左侧则向左移动，否则向右移动
Point get_pt(const LLine &ln,const Point & pt,const Point & sign_pt,Float dis)
{
	Point ph = project(sign_pt,ln);
	Point vec = sign_pt - ph;
	return pt + normalize(vec) * dis;
}

static bool get_line(const LLine &ln1,const LLine &ln2,
										Float dis,LLine& ln) ////下面distance函数专用
{
	Point px;
	Float dis1 = distance(ln1.pt1,ln2);
	Float dis2 = distance(ln1.pt2,ln2);
	bool flag = more_than(dis1,0);
	Point ph1 = project(ln1.pt1,ln2);
	Point ph2 = project(ln1.pt2,ln2);
	Point normal1 = normalize(ln1.pt1 - ph1);
	Point normal2 = normalize(ln1.pt2 - ph2);
	if(flag && more_than(dis2,0)){
		if(normal1 != normal2)
			return false;////直线ln1不在直线ln2的一侧，无法确定延长线
		else
			px = ph1 + normal1 * dis;
	}
	else
		px = flag ? (ph1 + normal1 * dis) : (ph2 + normal2 * dis);
	ln = make_line(px,ln2.pt2 - ln2.pt1);
	return true;
}

static bool get_cross(const LLine &ln1,const LLine &ln2,
											Float dis,Point& cross) ////下面distance函数专用
{
	Float dis1 = distance(ln1.pt1,ln2);
	Float dis2 = distance(ln1.pt2,ln2);
	bool flag = more_than(dis1,0);
	Point ph1 = project(ln1.pt1,ln2);
	Point ph2 = project(ln1.pt2,ln2);
	Point normal1 = normalize(ln1.pt1 - ph1);
	Point normal2 = normalize(ln1.pt2 - ph2);
	if(flag && more_than(dis2,0)){
		if(normal1 != normal2)
			return false;////直线ln1不在直线ln2的一侧，无法确定延长线
		else
			cross = ph1 + normal1 * dis;
	}
	else
		cross = flag ? (ph1 + normal1 * dis) : (ph2 + normal2 * dis);
	return true;
}

Float distance(const LLine &ln1,const LLine &ln2,Float dis,Point &cross)
{
	int flag = relation(ln1,ln2);
	switch(flag){
		case -1 : return 0;
		case 1 : {
			bool sign = get_cross(ln1,ln2,dis,cross);
			if(!sign)
				return -1;
			return dis;
		}
		case 2 : {
			Point pt;
			intersect(ln1,ln2,pt);
			LLine ln;
			bool sign = get_line(ln1,ln2,dis,ln);
			if(!sign)
				return -1;
			intersect(ln1,ln,cross);
			return distance(pt,cross);
		}
		default : return -1;
	}
}
///// to zhong /////

//求三角形所在平面的法向量
Point get_nor(const Point& pt1,const Point& pt2,const Point& pt3)
{
	Point vec1 = pt1 - pt2;
	Point vec2 = pt1 - pt3;
	return normalize(vec1 * vec2);
}

bool less_arc(const Arc &arc)  //判断圆弧是否是略弧（圆心角小于180度）
{
	Circle c;
	resume_circle(arc,c);
	LLine ln1 = create_line(arc.start,arc.end);
	LLine ln2 = create_line(arc.path,c.center);
	Point cross;
	return intersect(make_sline(ln1),make_sline(ln2),cross);
}

Float get_angle(const Arc &arc)  //求圆弧的圆心角
{
	Circle c;
	resume_circle(arc,c);
	Point vec1 = arc.start - c.center;
	Point vec2 = arc.end - c.center;
	double num = multiply(vec1,vec2) / (mos(vec1) * mos(vec2));
	if(num == -1)
		return pi();
	else if(less_arc(arc))
		return acos(num);
	else
		return 2*pi() - acos(num);
}

////求经过略弧两个断点切线的交点
Point get_pt(const Arc &arc)
{
	assert(less_arc(arc));
	Circle c;
	resume_circle(arc,c);
	Point normal = make_point(c.nor);
	Point vec1 = normal * (c.center - arc.start);
	Point vec2 = normal * (c.center - arc.end);
	LLine ln1 = make_line(arc.start,vec1);
	LLine ln2 = make_line(arc.end,vec2);
	Point pt;
	intersect(ln1,ln2,pt);
	return pt;
}

//求圆弧半径
Float get_radius(const Arc &arc)
{
	Circle c;
	resume_circle(arc,c);
	return c.radius;
}

////求圆弧上以弧始点为起点的旋转方向
////c是圆弧对应的圆
Point rotate_direction(const Arc &arc,const Circle &c)
{
	Point mid = middle_point(arc,arc.start,arc.end,c);
	LLine ln = make_line(c.center,arc.start);
	Point ph = project(mid,ln);
	return normalize(mid - ph);
}

////圆弧上任意一点到圆弧开始点的同时针角（弧度制）
////center是圆弧对应圆的圆心
Float get_angle(const Arc &arc,const Point &center,
								const Point &rotate_vec,const Point &pt)
{
	if(pt == arc.start)
		return 0;
	Point vec1 = arc.start - center;
	Point vec2 = pt - center;
	if(normalize(vec1) == normalize(vec2 * (-1)))
		return pi();
	LLine ln = make_line(center,arc.start);
	Point ph = project(pt,ln);
	Point vec = normalize(pt - ph);
	Float ang = angle(vec1,vec2);
	return (vec == rotate_vec) ? ang : (2*pi() - ang);
}

////圆上任意一点到圆上基点的同时针角（弧度制）
Float get_angle(const Circle &c,const Point &base,const Point &pt)
{
	LLine ln = make_line(c.center,base);
	Point ph = project(pt,ln);
	if(pt == ph)
		return (pt == base) ? 0 : pi();
	Point vech1 = normalize(pt - ph);
	Point normal = make_point(c.nor);
	Point vecl = base - c.center;
	Point vech2 = normalize(normal * vecl);
	Float ang = angle(vecl, pt - c.center);
	return (vech1 == vech2) ? ang : (2*pi() - ang);
}

static void deal_sort(std::vector<Point> &pts,std::vector<Float> &angs,
									 std::vector<Point> &result)  ////下面sort函数专用
{
	int i,sign;
	Point temp_pt;
	Float temp_ang;
	while(pts.size()){
		temp_ang = angs[0];
		sign = 0;
		for(i = 1; i < angs.size(); i++){
			if(less_than(angs[i],temp_ang)){
				temp_ang = angs[i];
				sign = i;
			}
		}
		result.push_back(pts[sign]);
		pts.erase(&pts[sign]);
		angs.erase(&angs[sign]);
	}
}

////对圆弧上的点集排序(点集中不能有重复点)(距离圆弧start点)
bool sort(const Arc &arc,const std::vector<Point> &pts,std::vector<Point> &result)
{
	int i,n = pts.size();
	if(n < 2)
		return false;
	Circle c;
	resume_circle(arc,c);
	Point rotate_vec = rotate_direction(arc,c);
	std::vector<Float> angs;
	for(i = 0; i < n; i++)
		angs.push_back(get_angle(arc,c.center,rotate_vec,pts[i]));
	std::vector<Point> temp = pts;
	deal_sort(temp,angs,result);
	return true;
}

////对圆上的点集排序(点集中不能有重复点)
bool sort(const Circle &c,const std::vector<Point> &pts,std::vector<Point> &result)
{
	int i,n = pts.size();
	if(n < 3)
		return false;
	result.push_back(pts[0]);
	std::vector<Float> angs;
	for(i = 1; i < n; i++)
		angs.push_back(get_angle(c,pts[0],pts[i]));
	std::vector<Point> temp_pt = pts;
	temp_pt.erase(&temp_pt[0]);
	deal_sort(temp_pt,angs,result);
	return true;
}

///////////////////////merge_arc///////////////////////////
////两个浮点数相等，返回真表示相等
static bool length_equ(Float num1,Float num2)
{
	return fabs(num1 - num2) <= LIMIT;
}

////把线数组sort_lns中下标在j到k之间的线加到线数组new_lns中
static void add_line(const std::vector<LLine> &sort_lns,int j,int k,
										 std::vector<LLine> &new_lns)
{
	int i;
	for(i = j; i <= k;i++)
		new_lns.push_back(sort_lns[i]);
}

////得到线数组sort_lns中每条线的长度
static void get_lens(const std::vector<LLine> &sort_lns,std::vector<Float> &lens)
{
	int i;
	for(i = 0; i < sort_lns.size(); i++){
		Float dis = distance(sort_lns[i].pt1,sort_lns[i].pt2);
		lens.push_back(dis);
	}
}

static void add_line(const std::vector<LLine> &sort_lns,int n1,int n2,
										 std::vector<LLine> &new_lns,int s,int e)
////下标[n1,n2]包含[s,e],把下标在[n1,s),(e,n2]的直线放入新的直线数组中
{
	int i;
	for(i = n1; i < s; i++)
		new_lns.push_back(sort_lns[i]);
	for(i = e+1; i <= n2; i++)
		new_lns.push_back(sort_lns[i]);
}

////判断点是否在圆上，不在圆上返回假
static bool is_on_circle(const Point &pt,const Circle &c)
{
	Float dis = distance(pt,c.center);
	return fabs(dis - c.radius) <= LIMIT;
}

////判断线数组sort_lns中下标在i到e之间的线是否有合成弧的线
////如果有，则返回真，此时n2是能合成弧的末线段下标，所以n2 <= e
////若没有，则n2是无效值，返回假
static bool is_merge_arc(const std::vector<LLine> &sort_lns,
												 int i,int e,int &n2)
{
	if(i + 1 >= e)
		return false;
	Circle c = make_circle(sort_lns[i].pt1,sort_lns[i].pt2,sort_lns[i+1].pt2);
	int j,count = 0;
	for(j = i+2;j <= e; ++j){
		if(is_on_circle(sort_lns[j].pt2,c))
			count++;
		else
			break;
	}
	if(count){
		n2 = i + count + 1;
		return true;
	}
	return false;
}

////判断线数组sort_lns中下标在s到e之间的线是否有合成弧的线
////如果有，则返回真，此时n1，n2是位于s，e之间能合成弧的始末线段下标
////所以有n1 >= s, n2 <= e
////若没有，则n1，n2是无效值，返回假
static bool is_merge_arc(const std::vector<LLine> &sort_lns,
												 int s,int e,int &n1,int &n2)
{
	int i;
	for(i = s; i < e; i++){
		bool flag = is_merge_arc(sort_lns,i,e,n2);
		if(flag){
			n1 = i;
			return true;
		}
	}
	return false;
}

////该函数添加线数组sort_lns中下标位于s,e之间能合成的弧到new_arcs中
////把期间其它不能合成弧的线加到线数组new_lns中
////lens是线数组sort_lns中每一条线段的长度数组
////若等长且共圆的能合成弧的线段长度大于长度range，则这些线段不合成弧，依旧加到线数组new_lns中，此时flag = -1
////若等长且共圆的能合成弧的线段长度小于长度range，则这些线段合成弧，合成的弧加到new_arcs中，此时flag = 1
static void add_arc_line(const std::vector<LLine> &sort_lns,std::vector<LLine> &new_lns,
												 std::vector<Arc> &new_arcs,const std::vector<Float> &lens,
												 int s,int e,int &flag,Float range)
{
	int n1, n2;
	bool sign = is_merge_arc(sort_lns,s,e,n1,n2);
	if(!sign)
		add_line(sort_lns,s,e,new_lns);
	else if(more_equ(lens[n1],range)){
		flag = -1;
		add_line(sort_lns,s,e,new_lns);
	}
	else{
		flag = 1;
		add_line(sort_lns,s,e,new_lns,n1,n2);
		Arc arc(sort_lns[n1].pt1,sort_lns[n1].pt2,sort_lns[n2].pt2);
		new_arcs.push_back(arc);
	}
}

////在长度数组lens中寻找下标从s开始连续等长的线段
////e是连续等长的最后一根线段下标，n是数组lens的长度
////若连续等长的线段个数大于等于2则返回真，否则返回假
static bool find_equ_length(const std::vector<Float> &lens,int s,int n,int &e)
{
	int i, count = 0;
	for(i = s+1; i < n; i++){
		if(length_equ(lens[s],lens[i]))
			++count;
		else
			break;
	}
	if(count > 1){
		e = s + count;
		return true;
	}
	return false;
}

////把线数组sort_lns中可以合成弧的线段合成弧添加到new_arcs中
////其它的线添加到new_lns中，range是合成弧的极限长度
////若合成了一条弧则返回1，有合成弧的线段但长度大于range，则返回-1，否则返回0
static int merge_arc(const std::vector<LLine> &sort_lns,std::vector<LLine> &new_lns,
											std::vector<Arc> &new_arcs,Float range)
{
	int s,e,n = sort_lns.size(),flag = 0;
	std::vector<Float> lens;
	bool sign;
	get_lens(sort_lns,lens);
	for(s = 0; s < n; s++){
		sign = find_equ_length(lens,s,n,e);
		if(sign){
			add_arc_line(sort_lns,new_lns,new_arcs,lens,s,e,flag,range);
			s = e;
		}
		else
			new_lns.push_back(sort_lns[s]);
	}
	if(new_arcs.size())
		return 1;
	return flag;
}

////在线数组temp_lns中寻找第一条长度大于range的线，若长度都小于range则返回假
static bool get_first_line(std::vector<LLine> &temp_lns,
													 Float range,LLine &ln)
{
	int i,flag = 0;
	Float dis;
	for(i = 0; i < temp_lns.size(); i++){
		dis = distance(temp_lns[i].pt1,temp_lns[i].pt2);
		if(less_than(range,dis)){
			flag = 1;
			ln = temp_lns[i];
			temp_lns.erase(&temp_lns[i]);
			break;
		}
	}
	return flag == 1;
}

////如果直线temp_ln的第一个端点与temp_lns的第i条线的某端点相连
////则设temp_ln的另一个端点是temp_lns的第i条线的另一个端点
////然后从temp_lns中删除第i条线，添加temp_ln到sort_lns数组，返回真
////若temp_lns的第i条线不与temp_ln的第一个端点相连，则返回假
static bool link_point(std::vector<LLine> &temp_lns,LLine &temp_ln,
											int i,std::vector<LLine> &sort_lns)
{
	if(temp_ln.pt1 == temp_lns[i].pt1 || temp_ln.pt1 == temp_lns[i].pt2){
		if(temp_ln.pt1 == temp_lns[i].pt1)
			temp_ln.pt2 = temp_lns[i].pt2;
		else
			temp_ln.pt2 = temp_lns[i].pt1;
		sort_lns.push_back(temp_ln);
		temp_lns.erase(&temp_lns[i]);
		return true;
	}
	return false;
}

////在线数组temp_lns中寻找是否有与temp_ln相连接的线
////如有则把temp_ln的第一个端点设为连接的端点，另一个端点设为与之连接的线的另一个端点
////然后添加temp_ln到sort_lns中，然后设temp_ln的第一个端点为它的第二个端点
////如果在线数组temp_lns中找不到与temp_ln连接的线则返回假
static bool link_point(std::vector<LLine> &temp_lns,LLine &temp_ln,
											std::vector<LLine> &sort_lns)
{
	int i,sign = 0;
	bool flag;
	for(i = 0; i < temp_lns.size(); i++){
		flag = link_point(temp_lns,temp_ln,i,sort_lns);
		if(flag){
			sign = 1;
			break;
		}
	}
	if(sign){
		temp_ln.pt1 = temp_ln.pt2;
		return true;
	}
	return false;
}

////对线数组lns按照首尾相连的顺序进行排序，排序后的线添加到sort_lns中
////sort_lns中前一条线的第二个端点必须连接后一条线的第一个端点
////sort_lns中的第一条线的长度必须大于range
////lns中如果所有的线的长度都小于等于range，或者sort_lns中的线不能构成环则返回假
static bool sort_line(const std::vector<LLine> &lns,Float range,
											std::vector<LLine> &sort_lns)
{
	std::vector<LLine> temp_lns = lns;
	LLine ln,temp_ln;
	bool flag = get_first_line(temp_lns,range,ln);
	if(!flag)
		return false;
	sort_lns.push_back(ln);
	temp_ln.pt1 = ln.pt2;
	while(temp_lns.size()){
		bool flag = link_point(temp_lns,temp_ln,sort_lns);
		if(!flag)
			return false;
	}
	return true;
}

////去掉线数组lns中重合的线，去重之后的线添加进news中
static void remove_repeat(const std::vector<LLine> &lns,std::vector<LLine> &news)
{
	int i;
	std::vector<LLine> temp_lns = lns;
	LLine temp;
	while(temp_lns.size()){
		temp = temp_lns[0];
		news.push_back(temp);
		temp_lns.erase(&temp_lns[0]);
		for(i = 0; i < temp_lns.size(); i++)
			if(temp == temp_lns[i]){
				temp_lns.erase(&temp_lns[i]);
				break;
			}
	}
}

////判断线ln1与线ln2是否共线，如果共线则合并成一条线写入ln1
////不共线则返回假
static bool is_conline(LLine &ln1,LLine &ln2)
{
	if(!superposition(ln1,ln2))
		return false;
	ln1.pt2 = ln2.pt2;
	return true;
}

////线数组sort_lns是一个排序后的数组（首尾相连的环），把其内共线的线合并
static void remove_conline(std::vector<LLine> sort_lns)
{
	if(sort_lns.size() < 2)
		return;
	int sign = 1;
	while(sign){
		int i, n = sort_lns.size();
		for(i = 0; i < n-1; i++){
			if(is_conline(sort_lns[i],sort_lns[i+1])){
				sort_lns.erase(&sort_lns[i+1]);
				break;
			}
		}
		if(sort_lns.size() == n)
			sign = 0;
	}
	if(sort_lns.size() < 2)
		return;
	if(is_conline(sort_lns[sort_lns.size()-1],sort_lns[0]))
		sort_lns.erase(&sort_lns[0]);
}

////合成弧主函数，返回合成的弧个数
int merge_arc(const std::vector<LLine> &lns,Float range,
							 std::vector<LLine> &new_lns,std::vector<Arc> &new_arcs)
{
	int n = lns.size();
	if(n <= 3){
		add_line(lns,0,n-1,new_lns);
		return 0;
	}
	else{
		std::vector<LLine> sort_lns,news;
		remove_repeat(lns,news);
		bool flag = sort_line(news,range,sort_lns);
		if(!flag){
			new_lns = news;
			return 0;
		}
		remove_conline(sort_lns);
		return merge_arc(sort_lns,new_lns,new_arcs,range);
	}
}

////在线数组lncs寻找是否有某一条线的某个端点是temp
////如果存在这样的线，则改变temp的值为该线的另一个端点，返回真，若找不到则返回假
static bool is_having_link(std::vector<LLine> &lncs,Point &temp,int n)
{
	int i = 0;
	for(; i < n; i++){
		if(temp == lncs[i].pt1 || temp == lncs[i].pt2){
			if(temp == lncs[i].pt1)
				temp = lncs[i].pt2;
			else
				temp = lncs[i].pt1;
			lncs.erase(&lncs[i]);
			return true;
		}
	}
	return false;
}

////在一个链中寻找最两端的某个端点并写入start，若链构成环则返回假
static bool get_first_point(const std::vector<LLine> &lns,Point &start)
{
	if(lns.size() < 3)
		return false;
	std::vector<LLine> lncs = lns;
	Point temp = lncs[0].pt1, temp_st = lncs[0].pt2;
	lncs.erase(&lncs[0]);
	while (lncs.size()) {
		int n = lncs.size();
		bool flag = is_having_link(lncs,temp,n);
		if(temp == temp_st)
			return false;
		if(!flag || lncs.size() == 0){
			start = temp;
			return true;
		}
	}
	return false;
}

////在一个链中寻找两端某端点所在在线，并记下该线在数组中的位置于j
////st是该端点是该线的第一个点还是第二个点
static bool get_first_line(const std::vector<LLine> &lns,int &j,int &st)
{
	Point start;
	bool flag = get_first_point(lns,start);
	if(!flag)
		return false;
	int i, n = lns.size();
	for(i = 0;i < n;i++){
		if(start == lns[i].pt1 || start == lns[i].pt2){
			j = i;
			if(start == lns[i].pt1)
				st = 1;
			else
				st = 2;
			return true;
		}
	}
	return false;
}

////把链lncs中连接的各个顺序点写入点数组sort_pts
////temp是该链的某个端点，n是链长
static void add_point(std::vector<LLine> &lncs,Point &temp,
											std::vector<Point> &sort_pts,int n)
{
	int i;
	for(i = 0; i < n; i++)
		if(temp == lncs[i].pt1 || temp == lncs[i].pt2){
			sort_pts.push_back(temp);
			if(temp == lncs[i].pt1)
				temp = lncs[i].pt2;
			else
				temp = lncs[i].pt1;
			lncs.erase(&lncs[i]);
			break;
		}
}

////把链lncs中连接的各个顺序点写入点数组sort_pts
////temp是该链的某个端点，若链中有多余的孤立无连接的线则返回假
static bool get_sort_pts(std::vector<LLine> &lncs,Point &temp,
												 std::vector<Point> &sort_pts)
{
	while (lncs.size()){
		int n = lncs.size();
		add_point(lncs,temp,sort_pts,n);
		if(lncs.size() && lncs.size() == n)
			return false;
	}
	return true;
}

////把链lns中连接的各个顺序点写入点数组sort_pts
////若链中有多余的孤立无连接的线则返回假
static bool get_sort_pts(const std::vector<LLine> &lns,std::vector<Point> &sort_pts)
{
	int st,j;
	bool flag = get_first_line(lns,j,st);
	if(!flag)
		return false;
	std::vector<LLine> lncs = lns;
	Point start = (st == 1) ? lncs[j].pt1 : lncs[j].pt2;
	sort_pts.push_back(start);
	Point temp = (st == 1) ? lncs[j].pt2 : lncs[j].pt1;
	lncs.erase(&lncs[j]);
	bool sign = get_sort_pts(lncs,temp,sort_pts);
	if(!sign)
		return false;
	sort_pts.push_back(temp);
	return true;
}

////把有序链中有共线三点的中间点去掉，即不能有共线的线存在
static void remove_conline(std::vector<Point> &sort_pts)
{
	if(sort_pts.size() < 3)
		return;
	int sign = 1;
	while(sign){
		int i,n = sort_pts.size();
		if(n < 3)
			break;
		for(i = 0;i < n-2; i++){
			bool flag = relation(sort_pts[i],sort_pts[i+1],sort_pts[i+2]);
			if(!flag){
				sort_pts.erase(&sort_pts[i+1]);
				break;
			}
		}
		if(sort_pts.size() == n)
			sign = 0;
	}
}

////有序链中以i开始的点能否与其后的点合成弧
////如果能则把能合成弧的最后一个点的下标写入e，并返回真
static bool is_merge_arc(const std::vector<Point> &sort_pts,int i,int n,int &e)
{
	if((i+2) >= (n-1)){
		e = i + 1;
		return false;
	}
	Circle c = make_circle(sort_pts[i],sort_pts[i+1],sort_pts[i+2]);
	int j, count = 0;
	for(j = i+3;j < n; ++j){
		if(is_on_circle(sort_pts[j],c))
			++count;
		else
			break;
	}
	e = count ? (i + count + 2) : (i + 1);
	return count > 0;
}

////有序链sort_pts中能合成弧的点合成弧写入new_arcs
////不能合成的线写入new_lns，如果合成的弧个数是1则返回真，否则返回假
static bool merge_arc(std::vector<LLine> &new_lns,std::vector<Arc> &new_arcs,
							 const std::vector<Point> &sort_pts)
{
	if(sort_pts.size() < 4)
		return false;
	int i, n = sort_pts.size();
	for(i = 0; i < n; ++i){
		int e;
		bool flag = is_merge_arc(sort_pts,i,n,e);
		if(flag){
			Arc arc(sort_pts[i],sort_pts[i+1],sort_pts[e]);
			new_arcs.push_back(arc);
		}
		else if(e == n)
			break;
		else{
			LLine ln(sort_pts[i],sort_pts[e]);
			new_lns.push_back(ln);
		}
		i = e - 1;
	}
	return new_arcs.size() == 1;
}

////单链合成弧主函数，当且仅当合成一条弧时返回真
bool merge_arc(const std::vector<LLine> &lns,std::vector<LLine> &new_lns,
							 std::vector<Arc> &new_arcs)
{
	if(lns.size() < 3)
		return false;
	std::vector<Point> sort_pts;
	bool flag = get_sort_pts(lns,sort_pts);
	if(!flag)
		return false;
	remove_conline(sort_pts);
	if(sort_pts.size() < 4)
		return false;
	return merge_arc(new_lns,new_arcs,sort_pts);
}

////该函数记下线数组中每条线的长度和长度状态
////每个长度写入长度数组lens，每个状态规定：长度大于range，状态为1，否则为0
static void get_judge_data(const std::vector<SLine> &sls,Float range,
										 std::vector<int> &flags,std::vector<Float> &lens)
{
	int i, n = sls.size();
	for(i = 0; i < n; i++){
		Float len = distance(sls[i].pt1,sls[i].pt2);
		if(less_equ(len,range))
			flags.push_back(0);
		else
			flags.push_back(1);
		lens.push_back(len);
	}
}

////该函数根据线数组的长度和状态考虑是否合成圆
////有一条线的长度大于极限长度或者有两条线的长度不一样长则视为不能合成圆，返回假
static bool is_consider_merge(const std::vector<int> &flags,
															const std::vector<Float> &lens)
{
	int i,n = lens.size();
	Float len = lens[0];
	for(i = 0; i < n; i++){
		if((flags[i] == 1) || (!length_equ(lens[i],len)))
			return false;
	}
	return true;
}

////判断两条线段是否共线，不共线返回假
bool is_conline(const SLine &sl1,const SLine &sl2)
{
	LLine ln(sl2.pt1,sl2.pt2);
	Float dis1 = distance(sl1.pt1,ln);
	Float dis2 = distance(sl1.pt2,ln);
	return equ(dis1,0) && equ(dis2,0);
}

////合并两条首尾相连且共线的线段为一条线段，参数1保存合并的线段
static bool merge_conline(SLine &sl1,const SLine &sl2)
{
	if(!is_conline(sl1,sl2))
		return false;
	bool flag1 = (sl1.pt1 == sl2.pt1) || (sl1.pt1 == sl2.pt2);
	bool flag2 = (sl1.pt2 == sl2.pt1) || (sl1.pt2 == sl2.pt2);
	if(flag1 || flag2){
		SLine sl;
		if(sl1.pt1 == sl2.pt1)
			sl.set(sl1.pt2,sl2.pt2);
		if(sl1.pt1 == sl2.pt2)
			sl.set(sl1.pt2,sl2.pt1);
		if(sl1.pt2 == sl2.pt1)
			sl.set(sl1.pt1,sl2.pt2);
		if(sl1.pt2 == sl2.pt2)
			sl.set(sl1.pt1,sl2.pt1);
		sl1 = sl;
		return true;
	}
	return false;
}

////该函数判断有序相连的线数组中是否有共线的线段
////如果有则合并，并且删除原来的线段，返回1，否则返回0
static int is_having_conline(std::vector<SLine> &sls)
{
	int i, n = sls.size();
	for(i = 0; i < n-1; i++){
		bool flag = merge_conline(sls[i],sls[i+1]);
		if(flag){
			sls.erase(&sls[i+1]);
			break;
		}
	}
	return (sls.size() == n) ? 0 : 1;
}

////合并线段数组中共线相连的线段
static void merge_conline(std::vector<SLine> &sls)
{
	int sign = 1;
	while(sign){
		sign = is_having_conline(sls);
	}
	if(sls.size() < 2)
		return;
	if(merge_conline(sls[sls.size()-1],sls[0]))
		sls.erase(&sls[0]);
}

////把线段数组合并成一个圆，不符合合并条件返回假
static bool merge_circle(const std::vector<SLine> &scs,Circle &c)
{
	c = make_circle(scs[0].pt1,scs[0].pt2,scs[2].pt1);
	int i, n = scs.size();
	for(i = 1; i < n; i++){
		bool flag1 = is_on_circle(scs[i].pt1,c);
		bool flag2 = is_on_circle(scs[i].pt2,c);
		if(!(flag1 && flag2))
			return false;
	}
	return true;
}

////合并圆主函数
////把线段数组合并成一个圆，不符合合并条件返回假
bool merge_circle(const std::vector<SLine> &sls,
									Float range,Circle &c)
{
	std::vector<SLine> scs = sls;
	merge_conline(scs);
	std::vector<int> flags;
	std::vector<Float> lens;
	get_judge_data(scs,range,flags,lens);
	bool flag = is_consider_merge(flags,lens);
	if(!flag || scs.size() < 2)
		return false;
	return merge_circle(scs,c);
}
///////////////////////merge_arc///////////////////////////

///////////////////////dis_parallel to zhong///////////////////////////
////在线数组lns中寻找与ln平行且距离最小的线lx
////函数返回最小距离，若没有平行的线则返回0
static Float find_line(const LLine &ln,const std::vector<LLine> &lns,LLine &lx)
{
	int i, j, n = lns.size();
	Float min_dis = 0;
	for(i = 0; i < n; ++i)
		if(!relation(ln,lns[i])){
			min_dis = distance(ln.pt1,lns[i]);
			lx = lns[i];
			break;
		}
	if(equ(min_dis,0))
		return 0;
	for(j = i+1; j < n; ++j){
		if(!relation(ln,lns[j])){
			Float dis = distance(ln.pt1,lns[j]);
			if(less_than(dis,min_dis)){
				min_dis = dis;
				lx = lns[j];
			}
		}
	}
	return min_dis;
}

////在线数组中寻找与线ln最近的一条平行线，返回它们的最短距离
////并求一点mid_off，它是ln的中点沿垂直于平行
Float dis_parallel(const LLine &ln,const std::vector<LLine> &lns,
									 Float dis,Point &mid_off)
{
	LLine lx;
	Float len = find_line(ln,lns,lx);
	if(equ(len,0))
		return -1;
	Point mid = (ln.pt1 + ln.pt2) * 0.5;
	Point ph = project(mid,lx);
	mid_off = mid + normalize(mid - ph) * dis;
	return len;
}
///////////////////////dis_parallel to zhong///////////////////////////

///////////////////////求任意多边形面积///////////////////////////
////对线数组按首尾连接的顺序排序写入sort_lns
static void sort_line(const std::vector<LLine> &lns,std::vector<LLine> &sort_lns)
{
	assert(lns.size() > 2);
	std::vector<LLine> temp_lns = lns;
	LLine temp_ln, ln = temp_lns[0];
	sort_lns.push_back(ln);
	temp_lns.erase(&temp_lns[0]);
	temp_ln.pt1 = ln.pt2;
	while(temp_lns.size())
		link_point(temp_lns,temp_ln,sort_lns);
}

////对一条线按端点1到端点2的顺序积分
static Float get_area(const LLine &ln)
{
	if(equ(ln.pt1.x,ln.pt2.x))
		return 0;
	Float k = (ln.pt2.y - ln.pt1.y) / (ln.pt2.x - ln.pt1.x);
	Float b = ln.pt1.y - k * ln.pt1.x;
	Float f2 = 0.5 * k * pow(ln.pt2.x,2) + b * ln.pt2.x;
	Float f1 = 0.5 * k * pow(ln.pt1.x,2) + b * ln.pt1.x;
	return f2 - f1;
}

////求多边形的面积
Float get_area(const std::vector<Point> &pts)
{
	int i, n = pts.size();
	LLine ln;
	Float sum_area = 0, area;
	for(i = 0; i < n-1; i++){
		ln.set(pts[i],pts[i + 1]);
		area = get_area(ln);
		sum_area += area;
	}
	ln.set(pts[n - 1],pts[0]);
	area = get_area(ln);
	sum_area += area;
	return less_than(sum_area,0.0) ? (-sum_area) : sum_area;
}
///////////////////////求任意多边形面积///////////////////////////

////判断线段数组中是否有与线段sl平行的线段，n是数组长度，存在平行则返回真
static bool is_have_parallel(const SLine &sl,const std::vector<SLine>& refer,int n)
{
	int i, flag = 0;
	bool sign;
	for(i = 0; i < n; i++){
		sign = parallel(sl,refer[i]);
		if(sign){
			flag = 1;
			break;
		}
	}
	return flag == 1;
}

////在src中找出与refer平行的线，放入result中。
void find_parallel(const std::vector<SLine>& src,
                   const std::vector<SLine>& refer,
                   std::vector<SLine>& result)
{
  int i, ns = src.size(), nr = refer.size();
	bool flag;
	for(i = 0; i < ns; i++){
		flag = is_have_parallel(src[i],refer,nr);
		if(flag)
			result.push_back(src[i]);
	}
}

////在src中找出与refer平行的线，放入paral中，其它的放入other中
////src，refer，paral，other中都存的是线段的下标，实际线段在all中
void find_parallel(const std::vector<SLine>& all, 
                   const std::vector<int>& src,
                   const std::vector<int>& refer,
                   std::vector<int>& paral,
                   std::vector<int>& other)
{
	int i, ns = src.size(), nr = refer.size();
	std::vector<SLine> refer_lns;
	for(i = 0; i < nr; i++)
		refer_lns.push_back(all[refer[i]]);
	bool flag;
	for(i = 0; i < ns; i++){
		flag = is_have_parallel(all[src[i]],refer_lns,nr);
		if(flag)
			paral.push_back(src[i]);
		else
			other.push_back(src[i]);
	}
}

//求pt2_pt1决定的角度（与x轴正向的夹角），返回标准角度
Float get_degree(const Point &pt1,const Point &pt2)
{
	Float num = get_angle2d(pt2,pt1);
	Float ang = convert_radian(num);
	return stdangle(ang);
}
//求一个向量决定的角度（与x轴正向的夹角），返回标准角度
Float get_degree(const Point &vec)
{
	return get_degree(O,vec);
}

////求方向pt0_pt1与方向pt0_pt2的夹角，返回标准角度
Float get_degree(const Point &pt0,const Point &pt1,const Point &pt2)
{
	Float num1 = get_degree(pt0,pt1);
	Float num2 = get_degree(pt0,pt2);
	return stdangle(num2 - num1);
}

////在线段数组中找到端点是temp的线段，并把temp的值改为该线段的另一个端点
////然后把temp放入点数组中，若找不到这样的线段则返回假
static bool link_point(std::vector<SLine> &scs,Point &temp,
											 std::vector<Point> &pts)
{
	int i, n = scs.size();
	for(i = 0; i < n; i++)
		if(temp == scs[i].pt1 || temp == scs[i].pt2){
			if(temp == scs[i].pt1)
				temp = scs[i].pt2;
			else
				temp = scs[i].pt1;
			pts.push_back(temp);
			scs.erase(&scs[i]);
			return true;
		}
	return false;
}
////取出多边形的有序顶点
bool get_points(const std::vector<SLine> &sls,std::vector<Point> &pts)
{
	if(sls.size()<1)
		return false;
	std::vector<SLine> scs = sls;
	Point temp = scs[0].pt1, start = scs[0].pt2;
	pts.push_back(temp);
	scs.erase(&scs[0]);
	while(temp != start){
		bool flag = link_point(scs,temp,pts);
		if(!flag)
			return false;
	}
	return true;
}
//判断多边形是否是凸的
bool is_protruding(const std::vector<SLine> &sls)
{
	std::vector<Point> pts;
	bool sign = get_points(sls,pts);
	if(!sign)
		return false;
	std::vector<bool> flags;
	get_flags(pts,flags);
	int i, n = flags.size(), flag = 1;
	for(i = 0; i < n; i++){
		if(!flags[i]){
			flag = 0;
			break;
		}
	}
	return flag == 1;
}


///////////////////////rect problem///////////////////////////
////取出矩形的四条边放进线段数组中
void make_line(const Box& box,std::vector<SLine> &sls)
{
	SLine sl;
	Point pt1,pt2;
	pt1.set(box.max_.x,box.max_.y,0.0);
	pt2.set(box.min_.x,box.max_.y,0.0);
	sl.set(pt1,pt2);
	sls.push_back(sl);
	pt1 = pt2;
	pt2.set(box.min_.x,box.min_.y,0.0);
	sl.set(pt1,pt2);
	sls.push_back(sl);
	pt1 = pt2;
	pt2.set(box.max_.x,box.min_.y,0.0);
	sl.set(pt1,pt2);
	sls.push_back(sl);
	pt1 = pt2;
	pt2.set(box.max_.x,box.max_.y,0.0);
	sl.set(pt1,pt2);
	sls.push_back(sl);
}

////取出矩形的四条边放进线段数组中
void make_line(const Box& box,SLine sls[])
{
	sls[0].pt1.set(box.max_.x,box.max_.y,0.0);
	sls[0].pt2.set(box.min_.x,box.max_.y,0.0);
	sls[1].pt1 = sls[0].pt2;
	sls[1].pt2.set(box.min_.x,box.min_.y,0.0);
	sls[2].pt1 = sls[1].pt2;
	sls[2].pt2.set(box.max_.x,box.min_.y,0.0);
	sls[3].pt1 = sls[2].pt2;
	sls[3].pt2.set(box.max_.x,box.max_.y,0.0);
}

////把线段sl的两个端点和它与线段数组的所有交点放入set集合中
////之所以用set而不用vector：对同一条线段上的点需要对其排序，而且不能有重合点
static int intersect(const std::vector<SLine> &sls,
										 const SLine &sl,std::set<Point> &cros)
{
	cros.insert(sl.pt1);
	cros.insert(sl.pt2);
	Point pt;
	bool flag;
	int i, n = sls.size();
	for(i = 0; i < n; i++){
		flag = intersect(sl,sls[i],pt);
		if(flag)
			cros.insert(pt);
	}
	return cros.size();
}

////set集合pts上的点是位于同一条线段上的点
////用它的第j个点和第j+1个点做一条线段，求该线段的中点
static Point get_mid_pt(const std::set<Point> &pts,int j)
{
	std::set<geo::Point>::const_iterator it = pts.begin();
	int count = 0;
	while(count != j){
		it++;
		count++;
	}
	std::set<geo::Point>::const_iterator temp1 = it,temp2 = ++it;
	return (*temp1 + *temp2) * 0.5;
}

////线段和多边形的关系，在内返回1，在外返回0，相交返回-1
////只是端点相交不视为相交，完全穿透才视为相交
int relation(const SLine &sl,const std::vector<SLine> &sls,
						 const std::vector<Point> &pts)
{
	TRACE_OUT("geo::relation :start!\n"); 
	std::set<Point> cros;
	int n = intersect(sls,sl,cros), i, in_n = 0, out_n = 0;
	Point mid;
	for(i = 0;i < n-1; i++){
		mid = get_mid_pt(cros,i);
		if(isin(mid,pts)){
			in_n++;
		}else{
			out_n++;
		}
	}
	TRACE_OUT("geo::relation :ok!\n"); 
	if(in_n == (n - 1))
		return 1;
	else
		return (out_n == (n - 1)) ? 0 : -1;
}

////判断矩形是否在多边形内
bool is_in(const Box &box,const std::vector<SLine> &sls)
{
	std::vector<Point> pts;
	bool sign = get_points(sls,pts);
	if(!sign)
		return false;
	std::vector<SLine> box_sls;
	make_line(box,box_sls);
	int i;
	for(i = 0; i < 4; ++i){
		if(relation(box_sls[i],sls,pts) != 1){
			return false;
		}
	}
	return true;
}

////取出矩形的四个顶点放进点数组中
static void get_vertexs(const Box &box,Point vertex[])
{
	vertex[0] = box.max_;
	vertex[1].set(box.min_.x,box.max_.y,0.0);
	vertex[2] = box.min_;
	vertex[3].set(box.max_.x,box.min_.y,0.0);
}

//判断点是否在矩形内，在矩形边缘上视为在里面
static bool is_in(const Point &pt,const Box &box)
{
	bool flag_x1 = more_equ(pt.x,box.max_.x) && less_equ(pt.x,box.min_.x);
	bool flag_x2 = more_equ(pt.x,box.min_.x) && less_equ(pt.x,box.max_.x);
	bool flag_y1 = more_equ(pt.y,box.max_.y) && less_equ(pt.y,box.min_.y);
	bool flag_y2 = more_equ(pt.y,box.min_.y) && less_equ(pt.y,box.max_.y);
	return (flag_x1 || flag_x2) && (flag_y1 || flag_y2);
}

////判断点数组是否和矩形有关（只要有一个点在矩形内就是有关的）,有关返回真
static bool is_in(const Point vertex[],const Box &box)
{
	int i;
	bool flag;
	for(i = 0; i < 4; ++i){
		flag = is_in(vertex[i],box);
		if(flag)
			return true;
	}
	return false;
}

////判断两个矩形是否是相交的，只有互相不包含且完全分离才视为不相交，相交返回真
static bool is_cross(const Box &box1,const Box &box2)
{
	Point vertex1[4],vertex2[4];
	get_vertexs(box1,vertex1);
	get_vertexs(box2,vertex2);
	bool flag1 = is_in(vertex1,box2);
	bool flag2 = is_in(vertex2,box1);
	return flag1 || flag2;
}

////判断矩形与矩形数组是否相交，相交则返回真
bool is_cross(const Box &box,const std::vector<Box> &boxs)
{
	int i, n = boxs.size();
	bool flag;
	for(i = 0; i < n; i++){
		flag = is_cross(box,boxs[i]);
		if(flag)
			return true;
	}
	return false;
}

////寻找包围点集合的最小包围盒
static void get_rect(const std::set<Point> &vertexs,Box &box)
{
	std::set<Point>::const_iterator it = vertexs.begin();
	Point pt = *it;
	box.max_ = box.min_ = pt;
	it++;
	for (;it != vertexs.end();++it){
		pt = *it;
		if(less_than(pt.x,box.max_.x))
			box.max_.x = pt.x;
		if(more_than(pt.x,box.min_.x))
			box.min_.x = pt.x;
		if(less_than(pt.y,box.min_.y))
			box.min_.y = pt.y;
		if(more_than(pt.y,box.max_.y))
			box.max_.y = pt.y;
	}
}

////寻找包围线段数组的最小包围盒
void get_rect(const std::vector<SLine> &sls,Box &box)
{
	int i,n = sls.size();
	std::set<Point> vertexs;
	for(i = 0; i < n; i++){
		vertexs.insert(sls[i].pt1);
		vertexs.insert(sls[i].pt2);
	}
	get_rect(vertexs,box);
}
///////////////////////rect problem///////////////////////////


///////////////////////find_loops///////////////////////////
struct Line_Branch{
	SLine sl; ////原线段
	bool single_branch;////线与其它线的连接是单分支还是多分支
	////只有且仅有两条线段的端点与原线段的两个端点分别相连接时该线段才视为单分支
	////true是单分支，false是多分支，独立的线视为多分支,多分支线不处理
};

////判断线段sl是单分支还是多分支，单分支返回真，否则返回假
////点集合pts是sl与线段数组intersect_lns的交点集合
static bool get_single_branch(const SLine &sl,const std::vector<Point> &pts,
															const std::vector<SLine> &intersect_lns)
{
	if(pts.size() != 2)
		return false;
	bool flag1 = (sl.pt1 == pts[0]) || (sl.pt1 == pts[1]);
	bool flag2 = (sl.pt2 == pts[0]) || (sl.pt2 == pts[1]);
	bool flag3 = (pts[0] == intersect_lns[0].pt1) || (pts[0] == intersect_lns[0].pt2);
	bool flag4 = (pts[1] == intersect_lns[1].pt1) || (pts[1] == intersect_lns[1].pt2);
	return flag1 && flag2 && flag3 && flag4;
}

////判断线段sl1与sl2是否是端点相连的，是则把相连的端点写入pt，返回真
static bool is_link(const SLine &sl1,const SLine &sl2,Point &pt)
{
	bool flag1 = (sl1.pt1 == sl2.pt1) || (sl1.pt1 == sl2.pt2);
	bool flag2 = (sl1.pt2 == sl2.pt1) || (sl1.pt2 == sl2.pt2);
	if(flag1){
		pt = (sl1.pt1 == sl2.pt1) ? sl2.pt1 : sl2.pt2;
		return true;
	}
	if(flag2){
		pt = (sl1.pt2 == sl2.pt1) ? sl2.pt1 : sl2.pt2;
		return true;
	}
	return false;
}

////判断两条线段的连接方式，重合返回-1，共线且首尾相连接返回0
////不共线但首尾相连接返回1，其它返回-2
static int link_mode(const SLine &sl1,const SLine &sl2,Point &pt)
{
	if(sl1 == sl2)
		return -1;
	bool flag = is_link(sl1,sl2,pt);
	if(is_conline(sl1,sl2))
		return flag ? 0 : -2;
	return flag ? 1 : -2;
}


static Line_Branch get_line_branch(const SLine &sl,int n,
																	 const std::vector<SLine> &sls)
{
	std::vector<Point> pts;
	std::vector<SLine> intersect_lns;
	int i;
	for(i = 0; i < n; i++){
		Point pt;
		int flag = link_mode(sl,sls[i],pt);
		if(flag >= 0){
			intersect_lns.push_back(sls[i]);
			pts.push_back(pt);
		}
	}
	Line_Branch ln_bch;
	ln_bch.sl = sl;
	ln_bch.single_branch = get_single_branch(sl,pts,intersect_lns);
	return ln_bch;
}

////在线数组scs中找出只有单分支的线，存入线段数组aim_sls
static void get_aim_sls(const std::vector<SLine> &scs,std::vector<SLine> &aim_sls)
{
	int i, n = scs.size();
	for(i = 0; i < n; i++){
		Line_Branch ln_bch = get_line_branch(scs[i],n,scs);
		if(ln_bch.single_branch)
			aim_sls.push_back(scs[i]);
	}
}

////在线数组中寻找一条端点等于temp的线段，然后把temp的值改为该线段的另一个端点
////存此线段到loop中，然后从原来的线段数组中把该线段删除，返回真
////若找不到这样的线段则返回假
static bool link_point(std::vector<SLine> &aim_sls,Point &temp,Loop &loop)
{
	int i, n = aim_sls.size();
	for(i = 0; i < n; i++)
		if(temp == aim_sls[i].pt1 || temp == aim_sls[i].pt2){
			if(temp == aim_sls[i].pt1)
				temp = aim_sls[i].pt2;
			else
				temp = aim_sls[i].pt1;
			loop.push_back(aim_sls[i]);
			aim_sls.erase(&aim_sls[i]);
			return true;
		}
	return false;
}

////在线段数组中寻找一条环存入loop，若找到的线段链不是环则返回假
static bool find_loop(std::vector<SLine> &aim_sls,Loop &loop)
{
	Point temp = aim_sls[0].pt1, start = aim_sls[0].pt2;
	loop.push_back(aim_sls[0]);
	aim_sls.erase(&aim_sls[0]);
	while(temp != start){
		bool flag = link_point(aim_sls,temp,loop);
		if(!flag)
			return false;
	}
	return true;
}

////寻找环主函数
////在线段数组slns中找出所有的环存入环数组lps
bool find_loops(const std::vector<SLine> &slns,Loops &lps)
{
	std::vector<SLine> scs = slns, aim_sls;
	get_aim_sls(scs,aim_sls);
	while(aim_sls.size()){
		Loop loop;
		bool flag = find_loop(aim_sls,loop);
		if(flag)
			lps.push_back(loop);
	}
	return lps.size() > 0;
}
///////////////////////find_loops///////////////////////////

////根据一中心点，半径和始末角度得到一个弧
void arc2d(Arc& arc, const Point& c, Float r, Float srad, Float erad)
{
	Float s = stdradian(srad);
	Float e = stdradian(erad);
	Float num = (s + e) * 0.5;
	Float m = more_than(s,e) ? stdradian(num + pi()) : num;
	arc.start.set(c.x + r * cos(s),c.y + r * sin(s),c.z);
	arc.path.set(c.x + r * cos(m),c.y + r * sin(m),c.z);
	arc.end.set(c.x + r * cos(e),c.y + r * sin(e),c.z);
}

////根据一中心点c和弧上一点p,以及弧中心与弧始末点的连线上任意一点s，e求该弧
void arc2d(Arc& arc, const Point& c, const Point& s, const Point& e, const Point& p)
{
  Float r = distance(c,p);
	arc.start = c + normalize(s - c) * r;
	arc.end = c + normalize(e - c) * r;
	arc.path = p;
	arc.center_ = c;
}

////平移弧使其圆心变成c点
void set_arc_center(Arc& arc, const Point& c)
{
	Circle cir;
	resume_circle(arc,cir);
	Arc temp;
	temp.start = c + (arc.start - cir.center);
	temp.path = c + (arc.path - cir.center);
	temp.end = c + (arc.end - cir.center);
	arc = temp;
}

////放缩弧使其半径变成r长
void set_arc_radius(Arc& arc, Float r)
{
	Circle c;
	resume_circle(arc,c);
	Arc temp;
	temp.start = c.center + normalize(arc.start - c.center) * r;
	temp.path = c.center + normalize(arc.path - c.center) * r;
	temp.end = c.center + normalize(arc.end - c.center) * r;
	arc = temp;
}

////求点center到点arc_pt决定的向量与x轴正方向的逆时针角
static Float get_rad(const Point &arc_pt,const Point &center)
{
	Point vec = project(arc_pt - center);
	Float rad = angle(vec,ox);
	return less_than(vec.y,0) ? (2 * pi() - rad) : rad;
}

////求弧起始点的逆时针弧度（始终保持弧是逆时针的，若不是逆时针则求弧终点的逆时针角）
Float arc2d_srad(const Arc& arc)
{
  Circle c;
	resume_circle(arc,c);
	bool flag = is_ccw2d(arc);
	if(flag)
		return get_rad(arc.start,c.center);
	else
		return get_rad(arc.end,c.center);
}

////求弧终点的逆时针弧度（始终保持弧是逆时针的，若不是逆时针则求弧起始点的逆时针角）
Float arc2d_erad(const Arc& arc)
{
  Circle c;
	resume_circle(arc,c);
	bool flag = is_ccw2d(arc);
	if(flag)
		return get_rad(arc.end,c.center);
	else
		return get_rad(arc.start,c.center);
}

////判断二维弧的三个点是否异常（共线或者有两点重合等），异常返回假
bool is_arc2d(const Arc& arc)
{
  Point start = project(arc.start);
	Point mid = project(arc.path);
	Point end = project(arc.end);
	return relation(start,mid,end);
}

////判断空间弧的三个点是否异常（共线或者有两点重合等）
bool is_arc(const Arc& arc)
{
  return relation(arc.start,arc.path,arc.end);
}

////求弧的中点
Point arc_middle_pt(const Arc& arc)
{
  Circle c;
	resume_circle(arc,c);
	return middle_point(arc,arc.start,arc.end,c);
}

////求弧的中点的弧度
Float arc_middle_rad(const Arc& arc)
{
  Float rad_s = arc2d_srad(arc);
	Float rad_e = arc2d_erad(arc);
	return (rad_e + rad_s) * 0.5;
}

////判断一个弧是不是逆时针顺序，不是则返回假
bool is_ccw2d(const Arc& arc)
{
	Circle c;
	resume_circle(arc,c);
	Float rad_s = get_rad(arc.start,c.center);
	Float rad_p = get_rad(arc.path,c.center);
	Float rad_e = get_rad(arc.end,c.center);
	bool flag1 = more_than(rad_p,rad_s) && more_than(rad_e,rad_p);
	bool flag2 = more_than(rad_p,rad_s) && more_than(rad_s,rad_e);
	bool flag3 = more_than(rad_e,rad_p) && more_than(rad_s,rad_e);
	return flag1 || flag2 || flag3;
}

///////////////////////get_arc_box///////////////////////////
////求弧在三个坐标轴方向上的最大点和最小点，把这六个点存入点数组
////c是弧对应的圆
static void get_pts(const Arc& arc,const Circle &c,std::vector<Point> &pts,
										const Point &vec_x,const Point &vec_y,const Point &vec_z)
{
	Point pt;
	if(vec_x != O){
		pt = c.center + vec_x * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
		pt = c.center - vec_x * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
	}
	if(vec_y != O){
		pt = c.center + vec_y * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
		pt = c.center - vec_y * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
	}
	if(vec_z != O){
		pt = c.center + vec_z * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
		pt = c.center - vec_z * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
	}
}

////求弧在三个坐标轴方向上的最大点和最小点，把这六个点存入点数组
////c是弧对应的圆
static void get_pts(const Arc& arc,const Circle &c,std::vector<Point> &pts)
{
	pts.push_back(arc.start);
	pts.push_back(arc.end);
	Point normal = make_point(c.nor);
	Point vec_x = normalize((normal * ox) * normal);
	Point vec_y = normalize((normal * oy) * normal);
	Point vec_z = normalize((normal * oz) * normal);
	get_pts(arc,c,pts,vec_x,vec_y,vec_z);
}

////根据点pt的坐标，比较盒子最大点和最小点的坐标，然后重置盒子坐标
////若盒子最大点x的坐标小于点pt的x的坐标，则把盒子最大点x的坐标设为pt的x的坐标，其它类似
void get_box(const Point &pt,Box &box)
{
	if(more_than(pt.x,box.max_.x))
		box.max_.x = pt.x;
	if(more_than(pt.y,box.max_.y))
		box.max_.y = pt.y;
	if(more_than(pt.z,box.max_.z))
		box.max_.z = pt.z;
	if(less_than(pt.x,box.min_.x))
		box.min_.x = pt.x;
	if(less_than(pt.y,box.min_.y))
		box.min_.y = pt.y;
	if(less_than(pt.z,box.min_.z))
		box.min_.z = pt.z;
}

//求包围空间圆弧的标准长方体，若圆弧平行于某坐标面则长方体退化为长方形
Box get_arc_box(const Arc& arc)
{
	Circle c;
	resume_circle(arc,c);
	std::vector<Point> pts;
	get_pts(arc,c,pts);
	int i,n = pts.size();
	Box box;
	box.max_ = box.min_ = pts[0];
	for(i = 1; i < n; i++)
		get_box(pts[i],box);
	return box;
}
///////////////////////get_arc_box///////////////////////////


///////////////////////put box///////////////////////////
#define BOX_DIS_LEFT					2.0	//左右对齐时盒子与外边框的左间距或右间距
#define BOX_DIS_UP						2.0	//上下对齐时盒子与外边框的上间距或下间距
#define BOX_DIS_EQU_LEFT			2.0	//等距对齐时盒子之间的左右等间距
#define BOX_DIS_EQU_UP				2.0	//等距对齐时盒子之间的上下等间距

////将盒子标准化，使其最大点为右上角的点，最小点为左下角的点
////此函数只适用于盒子目前的两个点是左上和右下的情形
static Rect_Box standard_box_main_catercorner(const Rect_Box &box_s)
{
	Rect_Box box_n;
	if(more_than(box_s.max_.x,box_s.min_.x)){
		box_n.max_.set(box_s.max_.x,box_s.min_.y,box_s.min_.z);
		box_n.min_.set(box_s.min_.x,box_s.max_.y,box_s.max_.z);
	}
	else{
		box_n.max_.set(box_s.min_.x,box_s.max_.y,box_s.max_.z);
		box_n.min_.set(box_s.max_.x,box_s.min_.y,box_s.min_.z);
	}
	return box_n;
}

////将盒子标准化，使其最大点为右上角的点，最小点为左下角的点
static Rect_Box standard_box(const Rect_Box &box_s)
{
	Float slope = (box_s.max_.y - box_s.min_.y) / (box_s.max_.x - box_s.min_.x);
	if(more_than(slope,0)){
		if(more_than(box_s.max_.x,box_s.min_.x))
			return box_s;
		else{
			Rect_Box box_n;
			box_n.max_ = box_s.min_;
			box_n.min_ = box_s.max_;
			return box_n;
		}
	}
	return standard_box_main_catercorner(box_s);
}

typedef void (*ALIGNMENT) (const Rect_Box &base_box,Rect_Box &move_box);
////该函数是模板函数，把盒子数组中的盒子按照第一个盒子对齐
static void alignment(ALIGNMENT alignment_function,std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	if(n < 2)
		return;
	Rect_Box standardbox = standard_box(boxs[0]);
	for(int i = 1;i < n;i++)
		alignment_function(standardbox,boxs[i]);
}

////左对齐，把盒子的左边坐标移到left_x位置，保持盒子上下坐标不变，只改变x值
static void left_alignment(const Float &left_x,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_x = standardbox.max_.x - standardbox.min_.x;
	standardbox.min_.x = left_x;
	standardbox.max_.x = standardbox.min_.x + len_x;
	box = standardbox;
}
////以第一个参数为基准左对齐第二个盒子，即两个盒子左边的坐标相同
////保持盒子上下坐标不变，只改变x值
////基准盒子参数必须是标准化的
void left_alignment(const Rect_Box &base_box,Rect_Box &move_box)
{
	left_alignment(base_box.min_.x,move_box);
}
////无外框，以第一个为基准左对齐
void left_alignment(std::vector<Rect_Box> &boxs)
{
	alignment(left_alignment,boxs);
}
////有外框，以外框为基准左对齐
void left_alignment(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
}

////右对齐,把盒子的右边坐标移到right_x位置，保持盒子上下坐标不变，只改变x值
static void right_alignment(const Float &right_x,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_x = standardbox.max_.x - standardbox.min_.x;
	standardbox.max_.x = right_x;
	standardbox.min_.x = standardbox.max_.x - len_x;
	box = standardbox;
}
////以第一个参数为基准右对齐第二个盒子
////保持盒子上下坐标不变，只改变x值
////基准盒子参数必须是标准化的
void right_alignment(const Rect_Box &base_box,Rect_Box &move_box)
{
	right_alignment(base_box.max_.x,move_box);
}
////无外框，以第一个为基准右对齐
void right_alignment(std::vector<Rect_Box> &boxs)
{
	alignment(right_alignment,boxs);
}
////有外框，以外框为基准右对齐
void right_alignment(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
}

////上对齐,把盒子的上边坐标移到up_y位置，保持盒子左右坐标不变，只改变y值
static void up_alignment(const Float &up_y,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_y = standardbox.max_.y - standardbox.min_.y;
	standardbox.max_.y = up_y;
	standardbox.min_.y = standardbox.max_.y - len_y;
	box = standardbox;
}
////以第一个参数为基准上对齐第二个盒子
////保持盒子左右坐标不变，只改变y值
////基准盒子参数必须是标准化的
void up_alignment(const Rect_Box &base_box,Rect_Box &move_box)
{
	up_alignment(base_box.max_.y,move_box);
}
////无外框，以第一个为基准上对齐
void up_alignment(std::vector<Rect_Box> &boxs)
{
	alignment(up_alignment,boxs);
}
////有外框，以外框为基准上对齐
void up_alignment(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
}

////下对齐,把盒子的下边坐标移到down_y位置，保持盒子左右坐标不变，只改变y值
static void down_alignment(const Float &down_y,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_y = standardbox.max_.y - standardbox.min_.y;
	standardbox.min_.y = down_y;
	standardbox.max_.y = standardbox.min_.y + len_y;
	box = standardbox;
}
////以第一个参数为基准下对齐第二个盒子
////保持盒子左右坐标不变，只改变y值
////基准盒子参数必须是标准化的
void down_alignment(const Rect_Box &base_box,Rect_Box &move_box)
{
	down_alignment(base_box.min_.y,move_box);
}
////无外框，以第一个为基准下对齐
void down_alignment(std::vector<Rect_Box> &boxs)
{
	alignment(down_alignment,boxs);
}
////有外框，以外框为基准下对齐
void down_alignment(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
}

////左右中间对齐：使盒子左右移到，保持上下坐标y不变
////把盒子中心点的x坐标移到middle_x位置
static void middle_alignment_left(const Float &middle_x,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_x = (standardbox.max_.x - standardbox.min_.x) / 2;
	standardbox.max_.x = middle_x + len_x;
	standardbox.min_.x = middle_x - len_x;
	box = standardbox;
}

////把盒子数组按第一个盒子左右中间对齐
////即每个盒子中心点的x坐标都是第一个盒子中心点的x坐标，保持y坐标不变
void middle_alignment_left(std::vector<Rect_Box> &boxs)
{
	int i,n = boxs.size();
	if(n < 2)
		return ;
	Float mid_x = (boxs[0].max_.x + boxs[0].min_.x) / 2;
	for(i = 1; i < n; i++)
		middle_alignment_left(mid_x,boxs[i]);
}

////把盒子数组按外框左右中间对齐
////即每个盒子中心点的x坐标都是外框中心点的x坐标，保持y坐标不变
void middle_alignment_left(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
	Float mid_x = (out_frame.max_.x + out_frame.min_.x) / 2;
	int i,n = boxs.size();
	for(i = 0; i < n; i++)
		middle_alignment_left(mid_x,boxs[i]);
}

////上下中间对齐：使盒子上下移到，保持上下坐标x不变
////把盒子中心点的y坐标移到middle_y位置
static void middle_alignment_up(const Float &middle_y,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_y = (standardbox.max_.y - standardbox.min_.y) / 2;
	standardbox.max_.y = middle_y + len_y;
	standardbox.min_.y = middle_y - len_y;
	box = standardbox;
}

////把盒子数组按第一个盒子上下中间对齐
////即每个盒子中心点的y坐标都是第一个盒子中心点的y坐标，保持x坐标不变
void middle_alignment_up(std::vector<Rect_Box> &boxs)
{
	int i,n = boxs.size();
	if(n < 2)
		return ;
	Float mid_y = (boxs[0].max_.y + boxs[0].min_.y) / 2;
	for(i = 1; i < n; i++)
		middle_alignment_up(mid_y,boxs[i]);
}

////把盒子数组按外框上下中间对齐
////即每个盒子中心点的y坐标都是外框中心点的y坐标，保持x坐标不变
void middle_alignment_up(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
	Float mid_y = (out_frame.max_.y + out_frame.min_.y) / 2;
	int i,n = boxs.size();
	for(i = 0; i < n; i++)
		middle_alignment_up(mid_y,boxs[i]);
}

////把盒子数组中每个盒子都标准化，n是盒子数组长度
static void standard_box(std::vector<Rect_Box> &boxs,int n)
{
	int i;
	for(i = 0; i < n; i++){
		Rect_Box temp = standard_box(boxs[i]);
		boxs[i] = temp;
	}
}

////上下等距对齐
////无外框情形，以最两端的盒子为基准上下等距移动中间的盒子
////保持每个盒子的x坐标不变
void equ_dis_alignment_up(std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	if(n < 3)
		return;
	standard_box(boxs,n);
	Float len = (boxs[0].min_.y - boxs[n-1].max_.y) / (n - 1);
	for(int i = 1; i < n-1; i++){
		Float middle_line_y = boxs[0].min_.y - i * len;
		Float half_len = (boxs[i].max_.y - boxs[i].min_.y) / 2;
		boxs[i].max_.y = middle_line_y + half_len;
		boxs[i].min_.y = middle_line_y - half_len;
	}
}

////求每两个盒子需要的上下等间距equ_len_y
////lens是每个盒子在y方向上的长度数组，n是盒子数组的长度
////out_frame是外框盒子
static bool get_equal_length_y(const std::vector<Float> &lens,int n,
																const Rect_Box &out_frame,Float &equ_len_y)
{
	Float sum_len = out_frame.max_.y - out_frame.min_.y;
	Float add_len = 0;
	for(int i = 0;i < n; i++)
		add_len += lens[i];
	equ_len_y = (sum_len - add_len) / (n + 1);
	return more_than(equ_len_y,0);
}

////得到第j个盒子距离外框上边的移到长度
static Float get_move_y(const std::vector<Float> &lens,int j,Float equ_len_y)
{
	Float sum_len = 0;
	int i;
	for(i = 0; i < j; i++)
		sum_len += lens[i];
	return sum_len + (j + 1) * equ_len_y;
}

////根据盒子数组求它在y方向上的长度数组，n是盒子数组的长度
static void get_len_y(const std::vector<Rect_Box> &boxs,
											std::vector<Float> &lens,int n)
{
	int i;
	for(i = 0; i < n; i++)
		lens.push_back(boxs[i].max_.y - boxs[i].min_.y);
}

////有外框情形，以外框顶端和底端为基准等距移动盒子
////与外框上下边也等距，返回假则表现盒子长度在y方向溢出
bool equ_dis_alignment_up(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	standard_box(boxs,n);
	Rect_Box standard_out = standard_box(out_frame);
	std::vector<Float> lens;
	get_len_y(boxs,lens,n);
	Float equ_len_y;
	bool flag = get_equal_length_y(lens,n,standard_out,equ_len_y);
	for(int i = 0; i < n; i++){
		Float len_y = get_move_y(lens,i,equ_len_y);
		boxs[i].max_.y = standard_out.max_.y - len_y;
		boxs[i].min_.y = boxs[i].max_.y - lens[i];
	}
	return flag;
}

////左右等距对齐
////无外框情形，以最两端的盒子为基准左右等距移动中间的盒子
////保持每个盒子的y坐标不变
void equ_dis_alignment_left(std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	if(n < 3)
		return;
	standard_box(boxs,n);
	Float len = (boxs[0].min_.x - boxs[n-1].max_.x) / (n - 1);
	for(int i = 1; i < n-1; i++){
		Float middle_line_x = boxs[0].min_.x - i * len;
		Float half_len = (boxs[i].max_.x - boxs[i].min_.x) / 2;
		boxs[i].max_.x = middle_line_x + half_len;
		boxs[i].min_.x = middle_line_x - half_len;
	}
}

////求每两个盒子需要的上下等间距equ_len_x
////lens是每个盒子在x方向上的长度数组，n是盒子数组的长度
////out_frame是外框盒子
static bool get_equal_length_x(const std::vector<Float> &lens,int n,
																const Rect_Box &out_frame,Float &equ_len_x)
{
	Float sum_len = out_frame.max_.x - out_frame.min_.x;
	Float add_len = 0;
	for(int i = 0;i < n; i++)
		add_len += lens[i];
	equ_len_x = (sum_len - add_len) / (n + 1);
	return more_than(equ_len_x,0);
}

////得到第j个盒子距离外框左边的移到长度
static Float get_move_x(const std::vector<Float> &lens,int j,Float equ_len_x)
{
	Float sum_len = 0;
	int i;
	for(i = 0; i < j; i++)
		sum_len += lens[i];
	return sum_len + (j + 1) * equ_len_x;
}

////根据盒子数组求它在x方向上的长度数组，n是盒子数组的长度
static void get_len_x(const std::vector<Rect_Box> &boxs,
											std::vector<Float> &lens,int n)
{
	int i;
	for(i = 0; i < n; i++)
		lens.push_back(boxs[i].max_.x - boxs[i].min_.x);
}
////有外框情形，以外框左端和右端为基准等距移动盒子
////与外框左右边也等距，返回假则表现盒子长度在x方向溢出
bool equ_dis_alignment_left(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	standard_box(boxs,n);
	Rect_Box standard_out = standard_box(out_frame);
	std::vector<Float> lens;
	get_len_x(boxs,lens,n);
	Float equ_len_x;
	bool flag = get_equal_length_x(lens,n,standard_out,equ_len_x);
	for(int i = 0; i < n; i++){
		Float len_x = get_move_x(lens,i,equ_len_x);
		boxs[i].min_.x = standard_out.min_.x + len_x;
		boxs[i].max_.x = boxs[i].min_.x + lens[i];
	}
	return flag;
}

}
