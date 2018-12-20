#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "rpt_steel.h"
#include "rpt_steel_def.h"

#define RPT_FMIN 0.001

/////////////////////// << tools >> ///////////////////////
int get_count(RSteel * o)
{
	if(!o){
		return 0;
	}
	if(o->count <= 1){
		return 1;
	}
	return o->count;
}


/////////////////////// << newsheet >> ///////////////////////
void newsheet_by_row(int row)
{
	if(get_cur_y()>=row){
		newsheet();
	}else{
		unnewsheet();
	}
}

/////////////////////// << init >> ///////////////////////

void add_part_by_super_no()
{
	RSteel * t = (RSteel*)get_super_dats_item(0);
	if(t){
		add_part(t->no);
	}
}

/////////////////////// << filter >> ///////////////////////
void filter_pass_bolt()
{
	RSteel * t = (RSteel*)get_curitem();
	if(!t){
		pass();
		return;
	}
	if(t->obj == RPT_OBJ_BOLT){
		pass();
	}else{
		unpass();
	}
}

void filter_unpass_bolt()
{
	RSteel * t = (RSteel*)get_curitem();
	if(!t){
		pass();
		return;
	}
	if(t->obj == RPT_OBJ_BOLT){
		unpass();
	}else{
		pass();
	}
}

/////////////////////// << group >> ///////////////////////
static int equ_by_kind()
{
	RSteel * t1 = (RSteel*)get_item1();
	RSteel * t2 = (RSteel*)get_item2();
	if(t1->kind == t2->kind){
		return 1;
	}else{
		return 0;
	}
}

static int equ_by_group()
{
	RSteel * t1 = (RSteel*)get_item1();
	RSteel * t2 = (RSteel*)get_item2();
	if(strcmp(t1->group,t2->group)==0){
		return 1;
	}else{
		return 0;
	}
}

static int equ_by_no()
{
	RSteel * t1 = (RSteel*)get_item1();
	RSteel * t2 = (RSteel*)get_item2();
	if(strcmp(t1->no,t2->no)==0){
		return 1;
	}else{
		return 0;
	}
}

static int equ_by_part_no()
{
	RSteel * t1 = (RSteel*)get_item1();
	RSteel * t2 = (RSteel*)get_item2();
	if(strcmp(t1->part_no,t2->part_no)==0){
		return 1;
	}else{
		return 0;
	}
}

static int equ_by_section()
{
	RSteel * t1 = (RSteel*)get_item1();
	RSteel * t2 = (RSteel*)get_item2();
	if(strcmp(t1->section,t2->section)==0){
		return 1;
	}else{
		return 0;
	}
}

static int equ_by_mat()
{
	RSteel * t1 = (RSteel*)get_item1();
	RSteel * t2 = (RSteel*)get_item2();
	if(strcmp(t1->mat,t2->mat)==0){
		return 1;
	}else{
		return 0;
	}
}

static int equ_by_length()
{
	RSteel * t1 = (RSteel*)get_item1();
	RSteel * t2 = (RSteel*)get_item2();
	if(fequ(t1->length, t2->length, RPT_FMIN)){
		return 1;
	}else{
		return 0;
	}
}

static int equ_by_area()
{
	RSteel * t1 = (RSteel*)get_item1();
	RSteel * t2 = (RSteel*)get_item2();
	if(fequ(t1->area, t2->area, RPT_FMIN)){
		return 1;
	}else{
		return 0;
	}
}

// 1
void group_by_no()
{
	if(equ_by_no()){
		equ();
	}else{
		unequ();
	}
}

void group_by_part_no()
{
	if(equ_by_part_no()){
		equ();
	}else{
		unequ();
	}
}

void group_by_section()
{
	if(equ_by_section()){
		equ();
	}else{
		unequ();
	}
}

void group_by_mat()
{
	if(equ_by_mat()){
		equ();
	}else{
		unequ();
	}
}

void group_by_length()
{
	if(equ_by_length()){
		equ();
	}else{
		unequ();
	}
}

void group_by_area()
{
	if(equ_by_area()){
		equ();
	}else{
		unequ();
	}
}


// 2
void group_by_no_section()
{
	if(equ_by_no() && equ_by_section()){
		equ();
	}else{
		unequ();
	}
}

void group_by_part_no_section()
{
	if(equ_by_part_no() && equ_by_section()){
		equ();
	}else{
		unequ();
	}
}

void group_by_section_length()
{
	if(equ_by_section() && equ_by_length()){
		equ();
	}else{
		unequ();
	}
}


// 3
void group_by_no_section_length()
{
	if(equ_by_no() && equ_by_section() && equ_by_length()){
		equ();
	}else{
		unequ();
	}
}

void group_by_part_no_section_length()
{
	if(equ_by_part_no() && equ_by_section() && equ_by_length()){
		equ();
	}else{
		unequ();
	}
}

// 4
void group_by_kind_group_section_mat()
{
	if(equ_by_kind() && equ_by_kind() && equ_by_section() && equ_by_mat()){
		equ();
	}else{
		unequ();
	}
}

/////////////////////// << sort >> ///////////////////////
int cmp_by_no()
{
	RSteel * t1 = (RSteel*)get_group1_item(0);
	RSteel * t2 = (RSteel*)get_group2_item(0);
	return strcmp(t1->no,t2->no);
}

int cmp_by_part_no()
{
	RSteel * t1 = (RSteel*)get_group1_item(0);
	RSteel * t2 = (RSteel*)get_group2_item(0);
	return strcmp(t1->part_no,t2->part_no);
}

int cmp_by_section()
{
	RSteel * t1 = (RSteel*)get_group1_item(0);
	RSteel * t2 = (RSteel*)get_group2_item(0);
	return strcmp(t1->section,t2->section);
}

int cmp_by_length()
{
	RSteel * t1 = (RSteel*)get_group1_item(0);
	RSteel * t2 = (RSteel*)get_group2_item(0);
	if(fless(t1->length, t2->length, RPT_FMIN)){
		return 1;
	}else if(fmore(t1->length, t2->length, RPT_FMIN)){
		return -1;
	}else{
		return 0;
	}
}


void sort_by_no()
{
	if(cmp_by_no()<0){
		order();
	}else{
		unorder();
	}
}

void sort_by_part_no()
{
	if(cmp_by_part_no()<0){
		order();
	}else{
		unorder();
	}
}

void sort_by_section()
{
	if(cmp_by_section()<0){
		order();
	}else{
		unorder();
	}
}

void sort_by_no_section()
{
	int cmp = cmp_by_no();
	if(cmp<0){
		order();
		return;
	}else if(cmp>0){
		unorder();
		return;
	}
	cmp = cmp_by_section();
	if(cmp <0){
		order();
		return;
	}else{
		unorder();
		return;
	}
}

void sort_by_part_no_section()
{
	int cmp = cmp_by_part_no();
	if(cmp<0){
		order();
		return;
	}else if(cmp>0){
		unorder();
		return;
	}
	cmp = cmp_by_section();
	if(cmp<0){
		order();
		return;
	}else{
		unorder();
		return;
	}
}

//3
void sort_by_no_section_length()
{
	int cmp = cmp_by_no();
	if(cmp<0){
		order();
		return;
	}else if(cmp>0){
		unorder();
		return;
	}
	cmp = cmp_by_section();
	if(cmp<0){
		order();
		return;
	}else if(cmp>0){
		unorder();
		return;
	}
	cmp = cmp_by_length();
	if(cmp<0){
		order();
		return;
	}else{
		unorder();
		return;
	}
}

void sort_by_part_no_section_length()
{
	int cmp = cmp_by_part_no();
	if(cmp<0){
		order();
		return;
	}else if(cmp>0){
		unorder();
		return;
	}
	cmp = cmp_by_section();
	if(cmp <0){
		order();
		return;
	}else if(cmp>0){
		unorder();
		return;
	}
	cmp = cmp_by_length();
	if(cmp<0){
		order();
		return;
	}else{
		unorder();
		return;
	}
}
/////////////////////// << sum >> ///////////////////////

int get_curgroup_count_sum()
{
	int sum = 0;
	int n = get_curgroup_count();
	int i=0;
	for(i=0; i<n; ++i){
		RSteel * o = (RSteel*)get_curgroup_item(i);
		sum += o->count;
	}
	return sum;
}

double get_curgroup_length_sum()
{
	double sum = 0;
	int n = get_curgroup_count();
	int i=0;
	for(i=0; i<n; ++i){
		RSteel * o = (RSteel*)get_curgroup_item(i);
		sum += o->length * get_count(o);
	}
	return sum;
}

double get_curgroup_weight_sum()
{
	double sum = 0;
	int n = get_curgroup_count();
	int i=0;
	for(i=0; i<n; ++i){
		RSteel * o = (RSteel*)get_curgroup_item(i);
		sum += o->weight * get_count(o);
	}
	return sum;
}


/////////////////////// << content >> ///////////////////////
void content_by_kind()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_i(t->kind);
	}
}

void content_by_group()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_s(t->group);
	}
}

void content_by_name()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_s(t->name);
	}
}

void content_by_no()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_s(t->no);
	}
}

void content_by_part_no()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_s(t->part_no);
	}
}

void content_by_section()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_s(t->section);
	}
}
void content_by_mat()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_s(t->mat);
	}
}

void content_by_count()
{
	int n = get_curgroup_count_sum();
	set_content_i(n);
}

void content_by_count_sum()
{
	int n = get_curgroup_count_sum();
	set_content_i(n);
}


void content_by_length()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_f(t->length);
	}
}

void content_by_length_sum()
{
	set_content_f(get_curgroup_length_sum());
}

void content_by_weight()
{
	int n = get_curgroup_count();
	if(n>0){
		RSteel * t = (RSteel*)get_curgroup_item(0);
		set_content_f(t->weight);
	}
}

void content_by_weight_sum()
{
	set_content_f(get_curgroup_weight_sum());
}


// 								assembly-part]],
// 								材型]],
// 								材質]],
// 								数量]],
// 								単長度(mm)]],
// 								総長度(mm)]],
// 								単重量(kg)]],
// 								総重量(kg)]],
