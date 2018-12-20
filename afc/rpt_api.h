#ifndef _AFC_RPT_API_H_
#define _AFC_RPT_API_H_

#include "export.h"

namespace rpt{

//init
AFCAPI int get_super_dats_size();
AFCAPI int get_table_dats_size();
AFCAPI void * get_super_dats_item(int id);
AFCAPI void * get_table_dats_item(int id);
AFCAPI void add_table_dat(void * ptr, int size, const char * name);
AFCAPI void clear_table_dats();

}//namespace


//trace
void rpt_trace(const char * tip);
void rpt_trace_i(const char * tip, int i);
void rpt_trace_f(const char * tip, double f);
void rpt_trace_s(const char * tip, const char * s);
//pos
int rpt_get_last_x();
int rpt_get_last_y();
void rpt_set_start_x(int x);
void rpt_set_start_y(int y);

// void rpt_set_sheet_x(int x);
// void rpt_set_sheet_y(int y);
// void rpt_set_sheet_w(int w);
// void rpt_set_sheet_h(int h);

// int rpt_get_sheet_x();
// int rpt_get_sheet_y();
// void rpt_set_sheet_x(int x);
// void rpt_set_sheet_y(int y);

int rpt_get_table_x();
int rpt_get_table_y();
void rpt_set_table_x(int x);
void rpt_set_table_y(int y);

void rpt_set_column_x(int x);
void rpt_set_column_y(int y);
void rpt_set_column_w(int w);
void rpt_set_column_h(int h);
//init
int rpt_get_super_dats_size();
int rpt_get_table_dats_size();
void * rpt_get_super_dats_item(int id);
void * rpt_get_table_dats_item(int id);
void rpt_add_table_dat(void * ptr, int size, const char * name);
void rpt_clear_table_dats();
//filter
void rpt_pass();
void rpt_unpass();
void * rpt_get_curitem();
//group
void rpt_equ();
void rpt_unequ();
void * rpt_get_item1();
void * rpt_get_item2();
//sort
void rpt_less();
void rpt_unless();
int rpt_get_group1_size();
int rpt_get_group2_size();
void * rpt_get_group1_item(int iid);
void * rpt_get_group2_item(int iid);
//content
int rpt_get_curgroup_size();
void * rpt_get_curgroup_item(int iid);
void rpt_set_content_i(int i);
void rpt_set_content_f(double f);
void rpt_set_content_s(const char * str);
//newsheet
void rpt_newsheet();
void rpt_unnewsheet();


#endif//FILE


