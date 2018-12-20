#include "rpt_steel.h"
#include "rpt_steel_def.h"
#include <string.h>
#include <math.h>


static int get_user_find(char * section, double * length, int * andor)
{
	const char * section_key = "section : ";
	const char * length_key = "length : ";
	const char * andor_key = "&&(1) ||(0) : ";
	add_att(section_key, "H400X200X8X13");
	add_att(length_key, "4000");
	add_att(andor_key, "1");
	if(!pop_att_dlg()){
		return 0;
	}
	char length_value[32];
	char andor_value[32];
	att_value(section_key, section);
	att_value(length_key, length_value);
	att_value(andor_key, andor_value);
	*length = atoi(length_value);
	trace_s("length_value : ", length_value);
	trace_f("length : ", *length);
	*andor = atoi(andor_value);
	return 1;
}

static int is_and(RSteel * o, const char * section, double length)
{
	if(strcmp(o->section, section) == 0	&& fequ(o->length, length, 0.01)){
		return 1;
	}
	return 0;
}

static int is_or(RSteel * o, const char * section, double length)
{
	if(strcmp(o->section, section) == 0	|| fequ(o->length, length, 0.01)){
		return 1;
	}
	return 0;
}

static int is(RSteel * o, const char * section, double length, int andor)
{
	if(!o || o->obj != RPT_OBJ_MEMBER){
		return 0;
	}
	if(andor){
		return is_and(o, section, length);
	}else{
		return is_or(o, section, length);
	}
}


static void find(const char * section, double length, int andor)
{
	int n = dat_count();
	int i = 0;
	for(; i<n; ++i){
		RSteel * o = (RSteel*)dat_item(i);
		if(is(o, section, length, andor)){
			o->selected = 1;
		}
	}
}


void apmain()
{
	char section[32];
	double length = 0.0;
	int andor = 0;
	if(!get_user_find(section, &length, &andor)){
		return;
	}
	find(section, length, andor);
}
