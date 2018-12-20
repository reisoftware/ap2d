#ifndef _HOLE_H_
#define _HOLE_H_

#define MATRIX_HOLE  0X00000001
#define LONG_HOLE    0X00000002
#define MOUSE_HOLE   0X00000004
#define UP_FLANG     0X00000004
#define DOWN_FLANG   0X00000008
#define WPL_HOLE     0X00000010
#define MIX_HOLE     0X00000020

typedef struct _HOLE_{
	unsigned int type;
	int jnt_index;
	double r;
	union{
		double x;
		double l;
	};
	double y;
	union{
	double disx;
	double dis;
	};
	double disy;
	int xn;
	int yn;
}HOLE;

#endif