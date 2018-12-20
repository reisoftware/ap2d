
#include "StdAfx.h"
#include "intersect.h"
#include "calculate.h"
#include <vector>
#include "Point.h"
#include "LLine.h"
#include "RLine.h"
#include "SLine.h"
#include "Circle.h"
#include "Arc.h"
#include "Plane.h"

namespace geo{

int intersect2d(const LLine& ln1, const LLine& ln2, Point& pt)
{
  LLine lh1 = project(ln1);
	LLine lh2 = project(ln2);
	bool flag = intersect(lh1,lh2,pt);
	if(!flag)
		return 0;
	else
		return 1;
}

int intersect2d(const RLine& ray, const LLine& ln, Point& pt)
{
  RLine rh = project(ray);
	LLine rlh = make_line(rh);
	LLine lh = project(ln);
	Point ph;
	int flag = intersect2d(rlh,lh,ph);
	if(flag == 0)
		return 0;
	else if(relation(ph,rh)){
		pt = ph;
		return 1;
	}
	else
		return 0;
}

int intersect2d(const RLine& ray1, const RLine& ray2, Point& pt)
{
  RLine rh1 = project(ray1);
	RLine rh2 = project(ray2);
	LLine rlh1 = make_line(rh1);
	LLine rlh2 = make_line(rh2);
	Point ph;
	int flag = intersect2d(rlh1,rlh2,ph);
	if(flag == 0)
		return 0;
	else if(relation(ph,rh1) && relation(ph,rh2)){
		pt = ph;
		return 1;
	}
	else
		return 0;
}
int intersect2d(const SLine& sl, const LLine& ln, Point& pt)
{
  SLine sh = project(sl);
	LLine slh = make_line(sh);
	LLine lh = project(ln);
	Point ph;
	int flag = intersect2d(slh,lh,ph);
	if(flag == 0)
		return 0;
	else if(relation(ph,sh)){
		pt = ph;
		return 1;
	}
	else
		return 0;
}

int intersect2d(const SLine& sl, const RLine& ray, Point& pt)
{
  SLine sh = project(sl);
	LLine slh = make_line(sh);
	RLine rh = project(ray);
	LLine rlh = make_line(rh);
	Point ph;
	int flag = intersect2d(slh,rlh,ph);
	if(flag == 0)
		return 0;
	else if(relation(ph,sh) && relation(ph,rh)){
		pt = ph;
		return 1;
	}
	else
		return 0;
}
int intersect2d(const SLine& sl1, const SLine& sl2, Point& pt)
{
  SLine sh1 = project(sl1);
	LLine slh1 = make_line(sh1);
	SLine sh2 = project(sl2);
	LLine slh2 = make_line(sh2);
	Point ph;
	int flag = intersect2d(slh1,slh2,ph);
	if(flag == 0)
		return 0;
	else if(relation(ph,sh1) && relation(ph,sh2)){
		pt = ph;
		return 1;
	}
	else
		return 0;
}

////Circle
int intersect2d(const Circle& lhs, const LLine & rhs, Point& pt1, Point& pt2)
{
	Plane pla = make_plane(lhs.center,make_point(lhs.nor));
	LLine lh = project(rhs);
	LLine lx = resume_line(lh,pla);
	Point cross1,cross2;
	int num = intersect(lx,lhs,cross1,cross2);
	if(num == 0)
		return 0;
	else if(num == 2){
		pt1 = project(cross1);
		pt2 = project(cross2);
		return 2;
	}
	else
		pt1 = project(cross1);
		return 1;
}

int intersect2d(const Circle& lhs, const RLine & rhs, Point& pt1, Point& pt2)
{
	LLine ln = make_line(rhs);
	RLine rh = project(rhs);
	Point p1,p2;
	int flag = intersect2d(lhs,ln,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){
		if(relation(p1,rh))
			i++;
		if(relation(p2,rh))
			j++;
		if(i + j == 1)
			pt1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			pt1 = p1;pt2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		if(relation(p1,rh)){
			pt1 = p1;i++;}
		return i;
	}
	else
		return 0;
}

int intersect2d(const Circle& lhs, const SLine & rhs, Point& pt1, Point& pt2)
{
	LLine ln = make_line(rhs);
	SLine sh = project(rhs);
	Point p1,p2;
	int flag = intersect2d(lhs,ln,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){
		if(relation(p1,sh))
			i++;
		if(relation(p2,sh))
			j++;
		if(i + j == 1)
			pt1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			pt1 = p1;pt2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		if(relation(p1,sh)){
			pt1 = p1;i++;}
		return i;
	}
	else
		return 0;
}

int intersect2d(const Circle& lhs,const Circle& rhs,Point& pt1,Point& pt2)
{
	return 0;
}
////Arc
int intersect2d(const Arc& lhs, const LLine & rhs, Point& pt1, Point& pt2)
{
	Circle c;
	resume_circle(lhs,c);
	Point p1,p2;
	int flag = intersect2d(c,rhs,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){
		Point px1 = resume_point(p1,c);
		Point px2 = resume_point(p2,c);
		if(relation(px1,lhs))
			i++;
		if(relation(px2,lhs))
			j++;
		if(i + j == 1)
			pt1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			pt1 = p1;pt2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		Point px1 = resume_point(p1,c);
		if(relation(px1,lhs)){
			pt1 = p1;i++;}
		return i;
	}
	else
		return 0;
}

int intersect2d(const Arc& lhs, const RLine & rhs, Point& pt1, Point& pt2)
{
	LLine ln = make_line(rhs);
	RLine rh = project(rhs);
	Point p1,p2;
	int flag = intersect2d(lhs,ln,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){
		if(relation(p1,rh))
			i++;
		if(relation(p2,rh))
			j++;
		if(i + j == 1)
			pt1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			pt1 = p1;pt2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		if(relation(p1,rh)){
			pt1 = p1;i++;}
		return i;
	}
	else
		return 0;
}

int intersect2d(const Arc& lhs, const SLine & rhs, Point& pt1, Point& pt2)
{
	LLine ln = make_line(rhs);
	SLine sh = project(rhs);
	Point p1,p2;
	int flag = intersect2d(lhs,ln,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){ 
		if(relation(p1,sh))
			i++;
		if(relation(p2,sh))
			j++;
		if(i + j == 1)
			pt1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			pt1 = p1;pt2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		if(relation(p1,sh)){
			pt1 = p1;i++;}
		return i;
	}
	else
		return 0;
}

int intersect2d(const Arc& lhs, const Circle& rhs, Point& pt1, Point& pt2)
{
	return 0;
}
int intersect2d(const Arc& lhs, const Arc   & rhs, Point& pt1, Point& pt2)
{
	return 0;
}

void intersect2d(const LLine& ln, const Box& box, std::set<Point>& pts)
{
	SLine sls[4];
	make_line(box,sls);
	int i;
	for(i = 0; i < 4;i++){
		Point pt;
		int n = intersect2d(sls[i],ln,pt);
		if(n)
			pts.insert(pt);
	}
}
void intersect2d(const RLine& rl, const Box& box, std::set<Point>& pts)
{
	SLine sls[4];
	make_line(box,sls);
	int i;
	for(i = 0; i < 4;i++){
		Point pt;
		int n = intersect2d(sls[i],rl,pt);
		if(n)
			pts.insert(pt);
	}
}
void intersect2d(const SLine& sl, const Box& box, std::set<Point>& pts)
{
	SLine sls[4];
	make_line(box,sls);
	int i;
	for(i = 0; i < 4;i++){
		Point pt;
		int n = intersect2d(sls[i],sl,pt);
		if(n)
			pts.insert(pt);
	}
}
void intersect2d(const Circle& c, const Box& box, std::set<Point>& pts)
{
	SLine sls[4];
	make_line(box,sls);
	int i;
	for(i = 0; i < 4;i++){
		Point pt1,pt2;
		int n = intersect2d(c,sls[i],pt1,pt2);
		if(n == 1)
			pts.insert(pt1);
		if(n == 2){
			pts.insert(pt1);
			pts.insert(pt2);
		}
	}
}
void intersect2d(const Arc& arc, const Box& box, std::set<Point>& pts)
{
	SLine sls[4];
	make_line(box,sls);
	int i;
	for(i = 0; i < 4;i++){
		Point pt1,pt2;
		int n = intersect2d(arc,sls[i],pt1,pt2);
		if(n == 1)
			pts.insert(pt1);
		if(n == 2){
			pts.insert(pt1);
			pts.insert(pt2);
		}
	}
}
void intersect2d(const Box& box1, const Box& box2, std::set<Point>& pts)
{
	SLine sls1[4],sls2[4];
	make_line(box1,sls1);
	make_line(box2,sls2);
	int i,j;
	for(i = 0; i < 4;i++){
		for(j = 0; j < 4;j++){
			Point pt;
			int n = intersect2d(sls1[i],sls2[j],pt);
			if(n)
				pts.insert(pt);
		}
	}
}



}//namespace
