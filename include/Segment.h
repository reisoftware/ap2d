#ifndef _SEGMENT_H_
#define _SEGMENT_H_
class Line;
class CArc;
class Visitor_Segment{
	public:
	virtual ~Visitor_Segment() {};
	virtual int do_it(Line& line) = 0;
	virtual int do_it(CArc& arc) = 0;
};
class Segment{

	public:
	virtual ~Segment() {};
	virtual int do_it(Visitor_Segment& v) = 0;
	virtual void release() = 0;
};
namespace GEXY{
	inline void Release(Segment* pT)
	{
		pT->release();
	}
}
#endif