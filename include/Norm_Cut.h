#ifndef _NORM_CUT_H_
#define _NORM_CUT_H_
class CGePlate;
class CGeNorm;
namespace apcad{
	class Polygon;
}
class AFX_EXT_CLASS Norm_Cut{
	int start_;
	int end_;
	double a_;
	BOOL up_;
	public:
		Norm_Cut();

		void Serialize(CArchive& ar);

		int start() const { return start_;}
		int end() const { return end_;}

		void set(int start,int end,double a,BOOL up);
		double get_len(const CGePlate* plate) const;
		bool get_normal(CGeNorm& normal,const CGePlate* plate) const;
		BOOL is_up() const { return up_;}
		void set_up(BOOL up) { up_ = up;}

		apcad::Polygon get_polygon(const CGePlate* plate) const;

		bool is_same(const Norm_Cut& rhs) const;
		bool is_reverse(const Norm_Cut& rhs) const;
};
#endif