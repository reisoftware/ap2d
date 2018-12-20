// Snap.h: interface for the Snap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SNAP_H__649CAA5D_6BA5_4660_A343_87DE9972420C__INCLUDED_
#define AFX_SNAP_H__649CAA5D_6BA5_4660_A343_87DE9972420C__INCLUDED_

#include "export.h"
#include "../afc/counter.h"

namespace dlhml{
class OBJECT_API Snap  
{
public:
	enum Flag{
		Endpoint = 0  ,
		Center        ,
		Middle        ,
		Perpendicular ,
		Intersect     ,
		Nearest       ,
		Anypoint
	};

	Snap();
	~Snap();

	void add_flag(Flag f);
	void remove_flag(Flag f);

	void zero();
	void all();

	void endpoint(bool b);
	bool endpoint() const;
  void center(bool b);
  bool center() const;
	void middle(bool b);
	bool middle() const;
	void perpendicular(bool b);
	bool perpendicular() const;
	void intersect(bool b);
	bool intersect() const;
	void nearest(bool b);
	bool nearest() const;
	void anypoint(bool b);
	bool anypoint() const;

private:
	BYTE flag_;

	void trace() const;
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_SNAP_H__649CAA5D_6BA5_4660_A343_87DE9972420C__INCLUDED_)
