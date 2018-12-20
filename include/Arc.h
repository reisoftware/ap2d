#ifndef _ARC_H_
#define _ARC_H_
#include "pt3d.h"
#include "segment.h"
class AFX_EXT_CLASS CArc:public Segment{
	CPt3D start_;
	CPt3D mid_;
	CPt3D end_;
public:
	CArc();
	CArc(CPt3D start,CPt3D mid,CPt3D end);
	
	int do_it(Visitor_Segment& v);
	void release();
	
	double get_r() const;
	CPt3D center() const;
	double get_angle() const; 
	CPt3D get_mid() const {
		return mid_;
	}
	CPt3D get_start() const{
		return start_;
	}
	CPt3D get_end() const{
		return end_;
	}
	
	void set_mid(CPt3D pt);
	void set_center(CPt3D pt);
	
	void GetPts(std::vector<CPt3D>& pts) const;
	void Serialize(CArchive& ar);

	void round_angle(const CPt3D& start,const CPt3D& mid,const CPt3D& end,double r);
	void bolt_angle(const CPt3D& start,const CPt3D& mid,const CPt3D& end,double r);
};
#endif