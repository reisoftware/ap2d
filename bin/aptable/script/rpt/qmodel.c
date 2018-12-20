#include "rpt_steel.h"
#include "rpt_steel_def.h"
#include <string.h>
#include <math.h>


static int get_user_input(int * col_count)
{
	const char * col_count_key = "column count : ";
	add_att(col_count_key, "2");
	if(!pop_att_dlg()){
		return 0;
	}
	char col_count_vlue[32];
	att_value(col_count_key, col_count_vlue);
	*col_count = atoi(col_count_vlue);
	return 1;
}

static void push_rsteel(int i)
{
	RSteel o;
	o.obj = RPT_OBJ_MEMBER;
	o.id = -1;
	o.parent = -1;
	strcpy(o.name, "ABC");
	strcpy(o.no, "A-1");
	strcpy(o.part_no, "H-1");
	strcpy(o.mat, "SS400");
	strcpy(o.section, "H400X200X8X13");
	o.node = i+1;
	dat_push(&o);
}

void apmain()
{
	int n = 0;
	if(!get_user_input(&n)){
		return;
	}

	int i = 0;
	for(; i<n; ++i){
		push_rsteel(i);
	}
}
