#ifndef _TESSELATOR_H_
#define _TESSELATOR_H_
#include <vector>
class CPt3D;
namespace apcad{
	class Polygon;
}
class Tesselator{
	GLUtesselator* obj_;
	Tesselator();
	operator =(const Tesselator&);
	Tesselator(const Tesselator&);

	void make_outer(const apcad::Polygon& outer,std::vector<CPt3D>& pts);
	void make_inner(const std::vector<apcad::Polygon>& inner,std::vector<std::vector<CPt3D> >& inner_pts);
public:
	~Tesselator();
	operator GLUtesselator*();
	static Tesselator& handle();
	
	void make_polygon(const apcad::Polygon& outer,const std::vector<apcad::Polygon>& inner);
};
#endif