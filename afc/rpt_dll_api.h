#ifndef _AFC_RPT_DLL_API_H_
#define _AFC_RPT_DLL_API_H_

#include "export.h"

namespace rpt{

//
// //trace
// AFCAPI void trace(const char * tip);
// AFCAPI void trace_i(const char * tip, int i);
// AFCAPI void trace_f(const char * tip, double f);
// AFCAPI void trace_s(const char * tip, const char * s);
// //pos
// AFCAPI int get_last_x();
// AFCAPI int get_last_y();
// AFCAPI void set_start_x(int x);
// AFCAPI void set_start_y(int y);
// 
// AFCAPI int get_table_x();
// AFCAPI int get_table_y();
// AFCAPI void set_table_x(int x);
// AFCAPI void set_table_y(int y);
// 
// AFCAPI void set_column_x(int x);
// AFCAPI void set_column_y(int y);
// AFCAPI void set_column_w(int w);
// AFCAPI void set_column_h(int h);
//init
AFCAPI int get_super_dats_size();
AFCAPI int get_table_dats_size();
AFCAPI void * get_super_dats_item(int id);
AFCAPI void * get_table_dats_item(int id);
AFCAPI void add_table_dat(void * ptr, int size, const char * name);
AFCAPI void clear_table_dats();
// 
// //filter
// AFCAPI void pass();
// AFCAPI void unpass();
// AFCAPI void * get_curitem();
// //group
// AFCAPI void equ();
// AFCAPI void unequ();
// AFCAPI void * get_item1();
// AFCAPI void * get_item2();
// //sort
// AFCAPI void less();
// AFCAPI void unless();
// AFCAPI int get_group1_size();
// AFCAPI int get_group2_size();
// AFCAPI void * get_group1_item(int iid);
// AFCAPI void * get_group2_item(int iid);
// //content
// AFCAPI int get_curgroup_size();
// AFCAPI void * get_curgroup_item(int iid);
// AFCAPI void set_content_i(int i);
// AFCAPI void set_content_f(double f);
// AFCAPI void set_content_s(const char * str);
// //newsheet
// AFCAPI void newsheet();
// AFCAPI void unnewsheet();

}//namespace

#endif//FILE


