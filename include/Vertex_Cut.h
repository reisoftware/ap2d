#ifndef _VERTEX_CUT_H_
#define _VERTEX_CUT_H_
#include "pt4d.h"
class Vertex_Cut{
public:
	enum Type{ROUND,BOLT};
//private:
	Type type_;
	double r_;
	int index_;
public:
	Vertex_Cut();
	void Serialize(CArchive& ar);
	int get_index() const { return index_;}
	void bolt(int index,double r);
	void round(int index,double r);
	void get_pts(const vector<Pt4D>& pts,
							vector<Pt4D>& result) const;
};
#endif