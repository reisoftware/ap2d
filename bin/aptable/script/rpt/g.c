#include "g.h"
#include "rpt_steel.h"
#include <string.h>

void g_filter()
{
	RSteel * t = (RSteel*)get_curitem();
	if(!t){
		pass();
		return;
	}
	//trace(t->no);
	if(t->type != RPT_TYPE_G){
		pass();
		return;
	}
	unpass();
}

void g_filter_by_part_no()
{
	RSteel * t = (RSteel*)get_curitem();
	if(!t){
		pass();
		return;
	}
	if(get_super_dats_count()<=0){
		pass();
		return;
	}
	RSteel * s = (RSteel*)get_super_dats_item(0);
	if(!s){
		pass();
		return;
	}
	//trace(t->no);
	if(strcmp(t->no, s->no) != 0){
		pass();
	}else{
		unpass();
	}
}

void g_filter_by_super_kind_group_section_mat()
{
	RSteel * t = (RSteel*)get_curitem();
	if(!t){
		pass();
		return;
	}
	if(t->type != RPT_TYPE_G){
		pass();
		return;
	}
	if(get_super_dats_count()<=0){
		pass();
		return;
	}
	RSteel * s = (RSteel*)get_super_dats_item(0);
	if(!s){
		pass();
		return;
	}
	if(t->kind != s->kind){
		pass();
		return;
	}	
	if(strcmp(t->group, s->group) != 0){
		pass();
		return;
	}	
	if(strcmp(t->section, s->section) != 0){
		pass();
		return;
	}	
	if(strcmp(t->mat, s->mat) != 0){
		pass();
		return;
	}	
	unpass();
}
