// Snap.cpp: implementation of the Snap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Snap.h"
#include <bitset>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4800)

namespace dlhml{
#define ENDPOINT				(1 << Endpoint)			//line or arc end point
#define CENTERPT				(1 << Center)		//circle or arc center pt
#define MIDDLE					(1 << Middle)	//middle
#define PERPENDICULAR		(1 << Perpendicular)		//perpendicular
#define INTERSECT				(1 << Intersect)			//ents intersect pt,not include LText
#define NEAREST					(1 << Nearest)		//pt in line 
#define ANYPOINT				(1 << Anypoint)		//pt at any place
Snap::Snap()
:flag_(0)
MCT_INIT2("Snap")
{
	trace();
}

Snap::~Snap()
{

}
void Snap::add_flag(Flag f)
{
	flag_ |= (1<<f);
	trace();
}
void Snap::remove_flag(Flag f)
{
	if(flag_ & (1<<f))
		flag_ ^= (1<<f);
	trace();
}

void Snap::zero()
{
	flag_ = 0;
	trace();
}
void Snap::all()
{
	flag_ |= ENDPOINT;
	flag_ |= CENTERPT;
	flag_ |= MIDDLE;
	flag_ |= PERPENDICULAR;
	flag_ |= INTERSECT;
	flag_ |= NEAREST;
	flag_ |= ANYPOINT;
	trace();
}

void Snap::endpoint(bool b)
{
	if(b)
		add_flag(Endpoint);
	else
		remove_flag(Endpoint);
}
bool Snap::endpoint() const
{
	return flag_ & ENDPOINT;
}
void Snap::center(bool b)
{
	if(b)
		add_flag(Center);
	else
		remove_flag(Center);
}
bool Snap::center() const 
{ 
 	return flag_ & CENTERPT;
} 
void Snap::middle(bool b)
{
	if(b)
		add_flag(Middle);
	else
		remove_flag(Middle);
}
bool Snap::middle() const
{
	return flag_ & MIDDLE;
}
void Snap::perpendicular(bool b)
{
	if(b)
		add_flag(Perpendicular);
	else
		remove_flag(Perpendicular);
}
bool Snap::perpendicular() const
{
	return flag_ & PERPENDICULAR;
}
void Snap::intersect(bool b)
{
	if(b)
		add_flag(Intersect);
	else
		remove_flag(Intersect);
}
bool Snap::intersect() const
{
	return flag_ & INTERSECT;
}
void Snap::nearest(bool b)
{
	if(b)
		add_flag(Nearest);
	else
		remove_flag(Nearest);
}
bool Snap::nearest() const
{
	return flag_ & NEAREST;
}
void Snap::anypoint(bool b)
{
	if(b)
		add_flag(Anypoint);
	else
		remove_flag(Anypoint);
}
bool Snap::anypoint() const
{
	return flag_ & ANYPOINT;
}
void Snap::trace() const
{
#ifdef _DEBUG
//	std::bitset<8> bit(flag_);
//	::OutputDebugString(bit.to_string().c_str());
//	::OutputDebugString("\n");
#endif
}
}
