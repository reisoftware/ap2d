#ifndef _AP_RPT_STEEL_H_
#define _AP_RPT_STEEL_H_


struct Rpt_Steel
{
	int obj;					// 1:member, 2:plate, 3:bolt, 4:joint
	int id;						// 索引
	int parent;				// 父构件索引(-1即主构件)
	int count;		//数量
	int color;		//颜色
	int selected;	//选中
	int node;

	int type;				// 1:大梁
	int kind;				// 1:具体表格
	char group[32];	// 工区
	char name[32];
	char no[32];
	char part_no[16];
	char mat[10];
	char section[30];	//规格	1:截面, 2:厚度, 3:直径, 4:无效
	double length;		//member:length, pl:较长的边(mm)
	double area;			//涂装(mm2)
	double weight;		//(kg)
};

///BETTER-Rpt_Steel
#define RSteel struct Rpt_Steel




#endif//FILE
