#ifndef _PT_4D_H_
#define _PT_4D_H_
#include "pt3D.h"
class AFX_EXT_CLASS Pt4D:public CPt3D{
	BOOL	is_arc_;
	public:
		Pt4D();
		explicit Pt4D(const CPt3D& pt);
		Pt4D(CPt3D pt,BOOL is_arc);
		BOOL is_arc() const;
		void Serialize(CArchive& ar);

		void set_arc(BOOL is_arc) { is_arc_ = is_arc;}
		
		Pt4D& operator = (const CPt3D& pt);
};
#endif