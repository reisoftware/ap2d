#include "StdAfx.h"
#include "geo_obj.h"
#include "../geometry/Normal.h"


namespace dlhml{

GPoint convert(const OPoint& pt)
{
	GPoint gpt;
	gpt.x = pt.x;
	gpt.y = pt.y;
	gpt.z = pt.z;
	return gpt;
}

OPoint convert(const GPoint& pt)
{
	OPoint opt;
	opt.x = pt.x;
	opt.y = pt.y;
	opt.z = pt.z;
	return opt;
}
	
// GArc convert(const OArc& arc)
// {
// 	OPoint opt1, opt2, opt3;
// 	opt1 = arc.start();
// 	opt2 = arc.path();
// 	opt3 = arc.end();
// 	GPoint gpt1, gpt2, gpt3;
// 	gpt1 = convert(opt1);
// 	gpt2 = convert(opt2);
// 	gpt3 = convert(opt3);
// 	GArc garc(gpt1, gpt2, gpt3);
// 	return garc;
// }
// 
// OArc convert(const GArc& arc)
// {
// 	OPoint opt1, opt2, opt3;
// 	opt1 = convert(arc.start);
// 	opt2 = convert(arc.path);
// 	opt3 = convert(arc.end);
// 	OArc oarc;
// 	oarc.set(opt1, opt2, opt3);
// 	return oarc;
// }

GCircle convert(const OCircle& cir)
{
	GPoint gcenter;
	gcenter = convert(cir.center());
	GCircle gcir;
	geo::Normal nor(0, 0, 1);
	gcir.set(gcenter, cir.radius(), nor);
	return gcir;
}

OCircle convert(const GCircle& cir)
{
	OPoint ocenter;
	ocenter = convert(cir.center);
	OCircle ocir;
	ocir.setdata(ocenter, cir.radius);
	return ocir;
}

void convert(const OLine & oln, GSLine& gln)
{
	OPoint os, oe;
	os = oln.start();
	oe = oln.end();
	GPoint gs, ge;
	gs = convert(os);
	ge = convert(oe);
	gln.set(gs, ge);
}

void convert(const GSLine& gln, OLine&  oln)
{	
	OPoint os, oe;
	os = convert(gln.pt1);
	oe = convert(gln.pt2);
	oln.setdata(os, oe);
}


void convert(const OLine & oln, GLLine& gln)
{
	OPoint os, oe;
	os = oln.start();
	oe = oln.end();
	GPoint gs, ge;
	gs = convert(os);
	ge = convert(oe);
	gln.set(gs, ge);
}

void convert(const GLLine& gln, OLine &  oln)
{
	OPoint os, oe;
	os = convert(gln.pt1);
	oe = convert(gln.pt2);
	oln.setdata(os, oe);
}

void convert(const OLine & oln, GRLine& gln)
{
	OPoint os, oe;
	os = oln.start();
	oe = oln.end();
	GPoint gs, ge;
	gs = convert(os);
	ge = convert(oe);
	gln.set(gs, ge);
}

void convert(const GRLine& gln, OLine &  oln)
{
	OPoint os, oe;
	os = convert(gln.pt1);
	oe = convert(gln.pt2);
	oln.setdata(os, oe);
}









}//namespace


