#include "stdafx.h"
#include "rpt_column.h"
#include "rpt_api_state.h"
#include "rpt_pos_state.h"
#include "rpt_rule_state.h"
#include "rpt_rule.h"
#include "trace.h"
#include "lua_tools.h"
#include "lua_fun.h"
#include "Lua_Tab.h"

#include <cassert>

namespace afc{
namespace rpt{

Column::Column()
{
// 	memset(&pf_, 0, sizeof(PF));
}

// void Column::set_callback(rpt::PF pf)
// {
// 	pf_ = pf;
// }

void Column::output(xls::Sheet& xsheet)
{
// 	if(!rpt_api.curgroup && !content_rule_.empty()){
// 		return;	
// 	}

	xls::Cell cell;
	cal_pos(cell);
	cal_centent(cell);
	cal_style(cell);
	cal_size(xsheet);
	xsheet.cells.push_back(cell);
//	current_column_add(w_);

	afc::Trace at;
	at.trace("Column::output");
	at.trace(cell.content);
	at.trace("cell.pos.x == ", cell.pos.x);
	at.trace("cell.pos.y == ", cell.pos.y);
	at.trace("cell.pos.w == ", cell.pos.w);
	at.trace("cell.pos.h == ", cell.pos.h);
}

// void Column::cal_pos(Cell& cell)
// {
// 	cell.pos = rpt::current_xpos();
// 	cell.pos.h = rpt::current_h();
// //	cell.pos.w = w_;
// }

void Column::cal_pos(xls::Cell& cell)
{
	rpt::api_state().column_pos = &pos_;
	rpt::rule_state().pos = pos_rule_;
	rpt::pos();
	cell.pos = pos_;
	rpt::api_state().last_pos = pos_;
}

void Column::cal_centent(xls::Cell& cell)
{
	cell.content = content_;
	if(content_rule_.empty()){
		return;	
	}
// 	if(!rpt_api.curgroup){
// 		return;
// 	}
	// 	assert(rpt::rule_state().pf.cell_content && "output after set_init_callback.");
	rpt::rule_state().cell_content = content_rule_;
	//rpt::rule_state().pf.cell_content();
	rpt::cell_content();
	cell.content = rpt::api_state().cur_cell_content;
}

void Column::cal_style(xls::Cell& cell)
{
	assert(api_state().sdb);
	api_state().sdb->fill(style_, cell.style);
}


// 	if(w_ >= 0){
// 		int n=pos_.w;
// 		int i=0;
// 		for(i=0; i<n; ++i){
// 			xsheet.ws[pos_.x+i] = w_;
// 		}
// 	}
static void rpt_column_cal_size(std::vector<double>& whs, 
																double wh, int posxy, int poswh)
{
	int n=poswh;	
	int i=0;	
	for(i=0; i<n; ++i){	
		xls::set_size(whs, posxy+i, wh);
	}	
}
// 
void Column::cal_size(xls::Sheet& xsheet)
{
	rpt_column_cal_size(xsheet.ws, w_, pos_.x, pos_.w);
	rpt_column_cal_size(xsheet.hs, h_, pos_.y, pos_.h);
}

void Column::open_lua(lua_State * l, LPCTSTR key)
{
	Lua_Tab(l, key);
	get_value(string, l, content_, "content");
	get_value(string, l, content_rule_, "content_rule");
	get_value(string, l, style_, "style");
	get_value(string, l, pos_rule_, "pos_rule");
	get_value(number, l, w_, "w");
	get_value(number, l, h_, "h");

// 	w_ = (w_<=0) ? 8.38 : w_;
// 	h_ = (h_<=0) ? 14.25 : h_;
}


}//namespace
}//namespace

