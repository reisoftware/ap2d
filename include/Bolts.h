#ifndef _BOLTS_H_
#define _BOLTS_H_
#include "pt3d.h"
class CGePlate;
class CGeAxis;
class AFX_EXT_CLASS Bolts{
private:
	int xnum_;
	int ynum_;
	double xdis_;
	double ydis_;
	double d_;
	double hole_d_;
	double len_;
	CString type_;
	CPt3D s_;
	CPt3D e_;
	CPt3D norm_;
private:
	void draw_bolt(const CPt3D& pt,CGeAxis* axis) const;
public:
	Bolts();
	void set_xnum(int num) { xnum_ = num;}
	void set_ynum(int num) { ynum_ = num;}
	void set_xdis(double dis) { xdis_ = dis;}
	void set_ydis(double dis) { ydis_ = dis;}
	void set_d(double d) { d_ = d;}
	void set_len(double len) { len_ = len;}
	void set_type(CString type) { type_ = type;}
 	void set_pt(const CPt3D& s,const CPt3D& e) { s_ = s; e_ = e;}
	void set_holed(double d) { hole_d_ = d;}
	void set_normal(const CGeNorm& norm);
	void draw_3d() const;

	void Serialize(CArchive& ar);

	friend class CMBoltDlg;
};
#endif
