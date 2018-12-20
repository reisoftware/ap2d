#ifndef _JOINT_H_
#define _JOINT_H_

#define MAX_BUFFER 255
#define MAX_MEMS 25
#define HSHAPE 1
#define ANGLESHAPE 2
#define TUBESHAPE 3
#define CHANNELSHAPE 4
#define CSHAPE 5
#define ROUNDSHAPE 6
#define PIPESHAPE 7
#define CTSHAPE 8

struct Pt{
	double x;
	double y;
	double z;
};
struct SECT
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

struct JOINT{
	char script_name[MAX_BUFFER];
	char joint_name[MAX_BUFFER];
	int mem_num;
	int mems[MAX_MEMS];
	int basept;
	int params_num;
};
struct JOINT_IO{
	struct JOINT* (*create_jnt)(struct JOINT* jnt);
	int (*edit)(struct JOINT* jnt);//user input 
	struct Pt (*get_offset)(struct JOINT* jnt,int mem_index);
	int (*serialize)(struct JOINT* jnt,void* ar);
	int (*dsn)(void* joint,struct JOINT* jnt,void* cnt);
	int (*unmodify_member)(void* joint,struct JOINT* jnt);
	int (*free_jnt)(struct JOINT* jnt);
};

#endif