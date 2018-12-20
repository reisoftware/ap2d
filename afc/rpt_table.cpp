#include "stdafx.h"
#include "rpt_table.h"
#include "rpt_rule.h"
#include "rpt_api_state.h"
#include "rpt_pos_state.h"
#include "rpt_rule_state.h"
#include "xls_pos.h"
#include "lua_tools.h"
#include "lua_fun.h"
#include "Lua_Tab.h"
#include "std_tools.h"
#include "trace.h"

namespace afc{
namespace rpt{

Table::Table()
:LIST(1)
,PACKAGE(2)
,super_dats_(NULL)
{
	init();
}

Table::Table(const Table& o)
:LIST(1)
,PACKAGE(2)
,super_dats_(NULL)
{
	init();
	*this = o;
}

void Table::init()
{
	breakpoint_ = 0;
}

Table& Table::operator = (const Table& o)
{
	type_ = o.type_;
	border_ = o.border_;
	pos_rule_ = o.pos_rule_;
	init_rule_ = o.init_rule_;
	filter_rule_ = o.filter_rule_;
	group_rule_ = o.group_rule_;
	sort_rule_ = o.sort_rule_;
	newsheet_rule_ = o.newsheet_rule_;

	pos_ = o.pos_;
	breakpoint_ = o.breakpoint_;

	columns_ = o.columns_;
	afc::close<Table>(tables_);
	afc::push_back_deep<Table>(tables_, o.tables_);

// 	pf_ = o.pf_;
	super_dats_ = o.super_dats_;
	table_dats_ = o.table_dats_;
	mgr_ = o.mgr_;

	return *this;
}

Table::~Table()
{
	afc::close<Table>(tables_);
}


Table * Table::create()
{
	return new Table();
}

void Table::close()
{
	delete this;
}

// void Table::set_callback(rpt::PF pf)
// {
// 	pf_ = pf;
// 	afc::for_each<Table, rpt::PF>(tables_, pf, &Table::set_callback);
// 	afc::for_each<Column, rpt::PF>(columns_, pf, &Column::set_callback);
// }

bool Table::output(xls::Sheet& xsheet)
{
	afc::Trace at;
	at.trace("Table::output");

	bool result = true;
	cal_pos();
	mgr_init();
	mgr_filter();
	mgr_group();
	mgr_sort();
	if(!output_mgr(xsheet)){
		result = false;
	}
	cal_border(xsheet);
	return result;
}

bool Table::output_mgr(xls::Sheet& xsheet)
{
	afc::Trace at;
	at.trace("Table::output_mgr");

	int n=mgr_.group_count();
	at.trace("group_count : ", n);
	if(!n){
		at.trace("********** n == 0");
		rpt_api.curgroup = NULL;
		output_column(xsheet);
		output_table(xsheet, NULL);
		return true;
	}
	int i=0;
		at.trace("######### n != 0");
	for(i=breakpoint_; i<n; ++i){
		at.trace("group id : ", i);
		if(!output_group(xsheet, i)){
			breakpoint_ = i;
			if(type_ == LIST){
				breakpoint_ ++;
			}
			return false;
		}
	}
	return true;
}


bool Table::output_group(xls::Sheet& xsheet, int gid)
{
	afc::Trace at;
	at.trace("Table::output_group(), gid == ", gid);
	std::vector<afc::Dat*> * gs = mgr_.group(gid);
	assert(gs);
	rpt_api.curgroup = gs;
	output_column(xsheet);
	output_table(xsheet, gs);
	rpt_rule.newsheet = newsheet_rule_;
	if(rpt::newsheet()){
		return false;
	}
	return true;
}

void Table::output_column(xls::Sheet& xsheet)
{
	int n=columns_.size();
	afc::Trace at;
	at.trace("Table::output_column(), n == ", n);
	int i=0;
	for(i=0; i<n; ++i){
		columns_[i].output(xsheet);
	}
}

void Table::output_table(xls::Sheet& xsheet, std::vector<afc::Dat*>* curgroup)
{
	int n=tables_.size();
	afc::Trace at;
	at.trace("Table::output_table(), n == ", n);
	int i=0;
	for(i=0; i<n; ++i){
		assert(tables_[i]);
		//rpt::api_state().super_dats = rpt_api.curgroup;
		at.trace("Table::output_table(), id == ", i);
		//at.trace("curgroup ptr == ", (int)(rpt_api.curgroup));
		tables_[i]->super_dats_ = curgroup;
		tables_[i]->output(xsheet);
	}
}

void Table::cal_pos()
{
	afc::rpt::api_state().table_pos = &pos_;
	rpt::rule_state().pos = pos_rule_;
	rpt::pos();
}

void Table::mgr_init()
{
	afc::Trace at;
	at.trace("Table::mgr_init");
	table_dats_.clear();
	afc::rpt::api_state().super_dats = super_dats_;
	afc::rpt::api_state().table_dats = &table_dats_;
	rpt::rule_state().init = init_rule_;
	at.trace("rpt::init(), super_dats == ", (int)(rpt_api.super_dats));
	rpt::init();
	at.trace("mgr_.init();");
	mgr_.init(table_dats_);
}

void Table::mgr_filter()
{
	afc::Trace at;
	at.trace("Table::mgr_filter");
	//assert(rpt::rule_state().pf.filter);
	rpt::rule_state().filter = filter_rule_;
	//mgr_.filter(rpt::rule_state().pf.filter);
	mgr_.filter(&rpt::filter);
}
void Table::mgr_group()
{
	afc::Trace at;
	at.trace("Table::mgr_group");
	//assert(rpt::rule_state().pf.group);
	rpt::rule_state().group = group_rule_;
	//mgr_.group(rpt::rule_state().pf.group);
	mgr_.group(&rpt::group);
}
void Table::mgr_sort()
{
	//assert(rpt::rule_state().pf.sort);
	rpt::rule_state().sort = sort_rule_;
	//mgr_.sort(rpt::rule_state().pf.sort);
	mgr_.sort(&rpt::sort);
}

void Table::cal_border(xls::Sheet& xsheet)
{
	if(type_ == PACKAGE || !border_){
		return;
	}
	xls::Pos border = xls::uniset(pos_, rpt_api.last_pos);
	xsheet.borders.push_back(border);
}


// void Table::cell_pos_global()
// {
// 	rpt::table_pos(pos_);
// 	rpt::current_xpos(pos_);
// //	rpt::current_h(h_);
// }

// void Table::cell_pos_row_add()
// {
// 	rpt::XPos pos = rpt::current_xpos();
// 	pos.x = pos_.x;
// 	pos.y += h_;
// 	rpt::current_xpos(pos);
// }


void Table::open_lua(lua_State * l, LPCTSTR key)
{
	Lua_Tab lt(l, key);
	get_value(number, l, type_, "type");
	get_value(number, l, border_, "border");
	get_value(string, l, pos_rule_, "pos_rule");
	get_value(string, l, init_rule_, "init_rule");
	get_value(string, l, filter_rule_, "filter_rule");
	get_value(string, l, group_rule_, "group_rule");
	get_value(string, l, sort_rule_, "sort_rule");
	get_value(string, l, newsheet_rule_, "newsheet_rule");
	switch(type_){
		case 1:
			afc::open_lua_ts(l, columns_, "columns");
			break;
		case 2:
			afc::open_lua_tps<Table>(l, tables_, "tables");
			break;
		default:
			return;
			break;
	}
}


}//namespace
}//namespace
