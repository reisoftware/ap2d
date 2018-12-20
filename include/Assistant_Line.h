#ifndef _ASSISTANT_LINE_H_
#define _ASSISTANT_LINE_H_
#include "pt3d.h"
class AFX_EXT_CLASS Assistant_Line{
	CPt3D start_;
	CPt3D end_;
	public:
		Assistant_Line(CPt3D start,CPt3D end);
		Assistant_Line();
		void draw() const;
		void Serialize(CArchive& ar);
		
		void get_pts(std::vector<CPt3D>& pts) const;
};
#endif