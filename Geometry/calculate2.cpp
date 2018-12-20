
#include "calculate2.h"

namespace geo{


static Point rightdown_pt2d(const Point & pt1, const Point & pt2)
{
	Point t;
	if (more_than(pt1.x, pt2.x)){
		return pt1;
	}else if(equ(pt1.x, pt2.x)){
		if (less_than(pt1.y, pt2.y)){
			return pt1;
		}else{
			return pt2;
		}
	}else{
		return pt2;
	}
}

int rightdown_pt2d(const std::vector<Point> & pts)
{
	Point pt = pts[0];
	int index;
	for (int i = 1; i < pts.size(); i++){
		if (pts[i] == rightdown_pt2d(pts[i], pt)){
			index = i;
		}
		
	}
	return index;	
// 	Point pt1, pt2;
// 	std::vector<Point> ps;
// 	std::vector<int> inds;
// 	int index;
// 	if (pts.empty()){
// 		return 0;
// 	}
// 	pt1 = pts[0];
// 	for (int i = 0; i < pts.size(); i ++){
// 		if (more_equ(pts[i].x, pt1.x)){
// 			pt1 = pts[i];
// 		}
// 	}
// 	for (i = 0; i < pts.size(); i ++){
// 		if (equ(pts[i].x, pt1.x)){
// 			ps.push_back(pts[i]);
// 			inds.push_back(i);
// 		}
// 	}
// 	if (ps.size() == 1){
// 		return inds[0];
// 	}
// 	pt2 = ps[0];
// 	for (i = 0; i < ps.size(); i ++){
//  		if (less_equ(ps[i].y, pt2.y)){
// 			index = i;
//  		}	
// 	}
// 	return inds[index];
}




}//namespace