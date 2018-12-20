#ifndef _REI_SECT_H_
#define _REI_SECT_H_

struct REISECT
{
	int type;
	union{
		double a;
		double d;
		double h;
	};
	union{
		double b;
		double bf;
	};
	double tw;
	union{
		double t;
		double tf;
	};
};
#endif