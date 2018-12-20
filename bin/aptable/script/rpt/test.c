#include "rpt_steel.h"
#include "rpt_steel_def.h"
#include <string.h>
#include <math.h>

static int get_user_section(char * old_section, char * new_section)
{
	const char * old_section_key = "old section : ";
	const char * new_section_key = "new section : ";
	add_att(old_section_key, "H400X200X8X13");
	add_att(new_section_key, "C60X30X10X2.3");
	if(!pop_att_dlg()){
		return 0;
	}
	att_value(old_section_key, old_section);
	att_value(new_section_key, new_section);
	return 1;
}



static void replace_section(const char * old_section, const char * new_section)
{
	int n = dat_count();
	int i = 0;
	for(; i<n; ++i){
		RSteel * o = (RSteel*)dat_item(i);
		if(	o && 
				o->obj == RPT_OBJ_MEMBER && 
				strcmp(o->section, old_section) == 0){
			strcpy(o->section, new_section);
			o->selected = 1;
		}
	}
}




void apmain()
{
	char old_section[32];
	char new_section[32];
	if(!get_user_section(old_section, new_section)){
		return;
	}
	replace_section(old_section, new_section);
}
