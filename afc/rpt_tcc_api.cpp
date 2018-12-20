#include "stdafx.h"
#include "rpt_tcc_api.h"
#include "rpt_api_state.h"
#include "rpt_def.h"
#include "tcc.h"
#include "format.h"
#include <cassert>
#include "../include/getrace.h"



/////////////////////// << def >> ///////////////////////


/////////////////////// << the >> ///////////////////////
namespace the{
	typedef std::vector<afc::Dat> Dats;
	typedef std::vector<afc::Dat*> Groups;

	static void * dat_2_steel(afc::Dat * t)
	{
		assert(t);
		void * p = t->ptr();
		assert(p);
		void * o = static_cast<void*>(p);
		assert(o);
		return o;
	}

	static afc::Dat * group_2_dat(Groups& group, int iid)
	{
		assert(iid >= 0);
		assert(iid < group.size());
		afc::Dat * t = group[iid];
		return t;
	}

	static afc::Dat& dats_2_dat(Dats& dats, int iid)
	{
		assert(iid >= 0);
		assert(iid < dats.size());
		afc::Dat& ts = dats[iid];
		return ts;
	}

	static void * group_2_steel(Groups& group, int iid)
	{
		afc::Dat* t = group_2_dat(group, iid);
		void * o = dat_2_steel(t);
		return o;
	}

	static void * dats_2_steel(Dats& dats, int iid)
	{
		afc::Dat& t = dats_2_dat(dats, iid);
		void * o = dat_2_steel(&t);
		return o;
	}

	/////////////////////// << get_group >> ///////////////////////
	static Groups& get_group(Groups* group)
	{
		assert(group);
		assert(!group->empty());
		return *group;
	}

	static Dats& get_dats(Dats* dats)
	{
		assert(dats);
		assert(!dats->empty());
		return *dats;
	}

	static void * get_steel(Groups* group, int iid)
	{
		Groups& g = get_group(group);
		void * o = group_2_steel(g, iid);
		assert(o);
		return o;
	}

	static void * get_steel(Dats* dats, int iid)
	{
		Dats& ts = get_dats(dats);
		void * o = dats_2_steel(ts, iid);
		assert(o);
		return o;
	}

}//namespace the

// #define def_get_group(which)	\
// 	assert(afc::rpt::api_state().which##_group);	\
// 	assert(!afc::rpt::api_state().which##_group->empty());	\
// 	std::vector<afc::Dat*>& which##_group = *afc::rpt::api_state().which##_group;
// 
// #define  def_get_steel(which, iid)	\
// 	def_get_group(which);	\
// 	void * which##_steel = the::group_2_steel(which##_group, iid);
// //enddef





/////////////////////// << trace >> ///////////////////////
void rpt_trace(const char * tip)
{
	TRACE_OUT("##TCC#  %s\n", tip);
}

void rpt_trace_i(const char * tip, int i)
{
	TRACE_OUT("##TCC#  %s%i\n", tip, i);
}

void rpt_trace_f(const char * tip, double f)
{
	TRACE_OUT("##TCC#  %s%f\n", tip, f);
}

void rpt_trace_s(const char * tip, const char * s)
{
	TRACE_OUT("##TCC#  %s%s\n", tip, s);
}

/////////////////////// << init >> ///////////////////////
//last
int rpt_get_last_x()
{
	int x = rpt_api.last_pos.x+rpt_api.last_pos.w-1;
	return x;
}
int rpt_get_last_y()
{
	int y = rpt_api.last_pos.y+rpt_api.last_pos.h-1;
	return y;
}

void rpt_set_start_x(int x)
{
	rpt_api.last_pos.x = x;
}
void rpt_set_start_y(int y)
{
	rpt_api.last_pos.y = y;
}

//sheet
// void rpt_set_sheet_x(int x)
// {
// 	rpt_tcc_ptr(rpt_api.sheet_pos, "set_sheet_x()");
// 	rpt_api.sheet_pos->x = x;
// 	rpt_api.last_pos.x = x;
// }
// 
// void rpt_set_sheet_y(int y)
// {
// 	rpt_tcc_ptr(rpt_api.sheet_pos, "set_sheet_y()");
// 	rpt_api.sheet_pos->y = y;
// 	rpt_api.last_pos.y = y;
// }

void rpt_set_sheet_w(int w)
{
	rpt_tcc_ptr(rpt_api.sheet_pos, "set_sheet_w()");
	rpt_api.sheet_pos->w = w;
}

void rpt_set_sheet_h(int h)
{
	rpt_tcc_ptr(rpt_api.sheet_pos, "set_sheet_h()");
	rpt_api.sheet_pos->h = h;
}



//sheet
// int rpt_get_sheet_x()
// {
// 	rpt_tcc_ptr(rpt_api.sheet_pos, "get_sheet_x()");
// 	return rpt_api.sheet_pos->x;
// }
// int rpt_get_sheet_y()
// {
// 	rpt_tcc_ptr(rpt_api.sheet_pos, "get_sheet_y()");
// 	return rpt_api.sheet_pos->y;
// }
// 
// void rpt_set_sheet_x(int x)
// {
// 	rpt_tcc_ptr(rpt_api.sheet_pos, "set_sheet_x()");
// 	rpt_api.sheet_pos->x = x;
// }
// void rpt_set_sheet_y(int y)
// {
// 	rpt_tcc_ptr(rpt_api.sheet_pos, "set_sheet_y()");
// 	rpt_api.sheet_pos->y = y;
// }


//table
int rpt_get_table_x()
{
	rpt_tcc_ptr(rpt_api.table_pos, "get_table_x()");
	return rpt_api.table_pos->x;
}
int rpt_get_table_y()
{
	rpt_tcc_ptr(rpt_api.table_pos, "get_table_y()");
	return rpt_api.table_pos->y;
}

void rpt_set_table_x(int x)
{
	rpt_tcc_ptr(rpt_api.table_pos, "set_table_x()");
	rpt_api.table_pos->x = x;
}
void rpt_set_table_y(int y)
{
	rpt_tcc_ptr(rpt_api.table_pos, "set_table_y()");
	rpt_api.table_pos->y = y;
}

//set column
void rpt_set_column_x(int x)
{
	rpt_tcc_ptr(rpt_api.column_pos, "set_column_x()");
	rpt_api.column_pos->x = x;
}

void rpt_set_column_y(int y)
{
	rpt_tcc_ptr(rpt_api.column_pos, "set_column_y()");
	rpt_api.column_pos->y = y;
}

void rpt_set_column_w(int w)
{
	rpt_tcc_ptr(rpt_api.column_pos, "set_column_w()");
	rpt_api.column_pos->w = w;
}

void rpt_set_column_h(int h)
{
	rpt_tcc_ptr(rpt_api.column_pos, "set_column_h()");
	rpt_api.column_pos->h = h;
}


/////////////////////// << init >> ///////////////////////
int rpt_get_super_dats_size()
{
	if(!rpt_api.super_dats){
		return 0;
	}
	return rpt_api.super_dats->size();
}

int rpt_get_table_dats_size()
{
	if(!rpt_api.table_dats){
		return 0;
	}
	return rpt_api.table_dats->size();
}

void * rpt_get_super_dats_item(int id)
{
	std::vector<afc::Dat*>* super_dats = rpt_api.super_dats;
	int aaa = rpt_api.super_dats->size();
	rpt_tcc_aryptr(rpt_api.super_dats, "get_super_dats_item()");
	return the::get_steel(rpt_api.super_dats, id);
}

void * rpt_get_table_dats_item(int id)
{
	rpt_tcc_aryptr(rpt_api.table_dats, "get_table_dats_item()");
	return the::get_steel(rpt_api.table_dats, id);
}

void rpt_add_table_dat(void * ptr, int size, const char * name)
{
	rpt_tcc_ptr(rpt_api.table_dats, "add_table_dat()");
	afc::Dat t;
	t.set(ptr, size, name);
	rpt_api.table_dats->push_back(t);
}

void rpt_clear_table_dats()
{
	rpt_tcc_ptr(rpt_api.table_dats, "clear_table_dats()");
	rpt_api.table_dats->clear();
}


/////////////////////// << filter >> ///////////////////////

void rpt_pass()
{
	afc::rpt::api_state().filter = true;
}

void rpt_unpass()
{
	afc::rpt::api_state().filter = false;
}

void * rpt_get_curitem()
{
	rpt_tcc_ptr(afc::rpt::api_state().cur_dat, "get_curitem()");
	void * o = the::dat_2_steel(afc::rpt::api_state().cur_dat);
	return o;
}

/////////////////////// << group >> ///////////////////////
void rpt_equ()
{
	afc::rpt::api_state().group = true;
}

void rpt_unequ()
{
	afc::rpt::api_state().group = false;
}

void * rpt_get_item1()
{
	rpt_tcc_ptr(afc::rpt::api_state().dat1, "get_item()");
	void * o = the::dat_2_steel(afc::rpt::api_state().dat1);
	return o;
}

void * rpt_get_item2()
{
	rpt_tcc_ptr(afc::rpt::api_state().dat2, "get_item2()");
	void * o = the::dat_2_steel(afc::rpt::api_state().dat2);
	return o;
}

/////////////////////// << sort >> ///////////////////////

void rpt_less()
{
	afc::rpt::api_state().sort = true;
}

void rpt_unless()
{
	afc::rpt::api_state().sort = false;
}

int rpt_get_group1_size()
{
	rpt_tcc_aryptr(rpt_api.group1, "get_group1_size()");
	return the::get_group(rpt_api.group1).size();
}

int rpt_get_group2_size()
{
	rpt_tcc_aryptr(rpt_api.group2, "get_group2_size()");
	return the::get_group(rpt_api.group2).size();
}

void * rpt_get_group1_item(int iid)
{
	rpt_tcc_aryptr(rpt_api.group1, "get_group1_item()");
	return the::get_steel(rpt_api.group1, iid);
}
void * rpt_get_group2_item(int iid)
{
	rpt_tcc_aryptr(rpt_api.group2, "get_group2_item()");
	return the::get_steel(rpt_api.group2, iid);
}



/////////////////////// << content >> ///////////////////////
namespace the{

	static void set_cur_cell_content(LPCTSTR str)
	{
		afc::rpt::api_state().cur_cell_content = str;
	}

}//namespace the

int rpt_get_curgroup_size()
{
	rpt_tcc_aryptr(rpt_api.curgroup, "get_crugroup()");
	return the::get_group(rpt_api.curgroup).size();
}

void * rpt_get_curgroup_item(int iid)
{
	rpt_tcc_aryptr(rpt_api.curgroup, "get_crugroup()");
	return the::get_steel(rpt_api.curgroup, iid);
}

void rpt_set_content_i(int i)
{
	the::set_cur_cell_content(afc::format(i));
}

void rpt_set_content_f(double f)
{
	the::set_cur_cell_content(afc::format(f));
}

void rpt_set_content_s(const char * s)
{
	the::set_cur_cell_content(s);
}



// void rpt_cur_group_size()
// {
// 	def_get_group(cur);
// 	int n = cur_group.size();
// 	the::set_cur_cell_content(afc::format(n));
// }
// 
// void rpt_cur_group_section()
// {
// 	def_get_steel(cur, 0);
// 	afc::string str = cur_steel->section;
// 	the::set_cur_cell_content(str);
// }
// 
// void rpt_cur_group_length()
// {
// 	def_get_steel(cur, 0);
// 	double f = cur_steel->length;
// 	the::set_cur_cell_content(afc::format(f));
// }
// 
// void rpt_cur_group_length_sum()
// {
// 	def_get_sum(cur, length);
// 	the::set_cur_cell_content(afc::format(sum));
// }

//newsheet
void rpt_newsheet()
{
	rpt_api.newsheet = true;
}

void rpt_unnewsheet()
{
	rpt_api.newsheet = false;
}