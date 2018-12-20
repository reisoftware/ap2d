#ifndef _PLATES_H_
#define _PLATES_H_
#include <vector>
#include "geconnect.h"
#include "Bolts.h"
namespace gelib{
class Model_Geographic;
}

class AFX_EXT_CLASS Plates{
	std::vector<CGePlate> pls_;
	Bolts bolts_;
	public:
		void add_pl(const CGePlate& pl);
		void draw_3d();

		void pick(int index);
		void pick(const std::vector<int>& arys);
		void Serialize(CArchive& ar);
		void draw_clip(gelib::Model_Geographic& geo,std::vector<CPt3D>& pts);

		void modify(const CPt3D& pt1,const CPt3D& pt2,const CPt3D& pt3);

		void erase_select();

		void norm_cut(const CPt3D& pt1,const CPt3D& pt2,double a,BOOL up);
		void bolt_plate(const CPt3D& pt1,double r);
		void round_plate(const CPt3D& pt1,double r);
		void unround_plate(const CPt3D& pt1);

		void property();
		void copy_tool(const CPt3D& pt1,const CPt3D& pt2);
		void move_to(const CPt3D& pt1,const CPt3D& pt2);
		void move_vertex(const CPt3D& pt1,const CPt3D& pt2);

		int get_select_count() const;
		void add_2_jnt(CJoint* jnt);
		void get_from(CJoint* jnt);

		void add_bolts(const Bolts& bolts);
};
#endif