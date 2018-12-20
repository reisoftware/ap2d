#ifndef _AFC_RPT_TABLE_H_
#define _AFC_RPT_TABLE_H_

#include "export.h"
#include "str.h"
#include "dat.h"
#include "dat_mgr.h"
#include "rpt_fptr.h"
#include "rpt_column.h"
#include "xls_sheet.h"
#include <vector>
#include "../include/lua.hpp"

namespace afc{
namespace rpt{

class Cell_Mgr;

class AFCAPI Table
{
public:
	Table();
	Table(const Table& o);
	Table& operator = (const Table& o);
	~Table();

public:
	static Table * create();
	void close();

public:
// 	void set_callback(rpt::PF pf);
	bool output(xls::Sheet& xsheet);

public:
	void open_lua(lua_State * l, LPCTSTR key);	

private:
	void cal_pos();
	void init();
	void mgr_init();
	void mgr_filter();
	void mgr_group();
	void mgr_sort();
	void cal_border(xls::Sheet& xsheet);

private:
	bool output_mgr(xls::Sheet& xsheet);
	bool output_group(xls::Sheet& xsheet, int gid);
	void output_column(xls::Sheet& xsheet);
	void output_table(xls::Sheet& xsheet, std::vector<afc::Dat*>* curgroup);

private:
	const int LIST;
	const int PACKAGE;
	int type_;//1:LIST, 2:PACKAGE
	BOOL border_;

public:
	afc::string pos_rule_;
	afc::string init_rule_;
	afc::string filter_rule_;
	afc::string group_rule_;
	afc::string sort_rule_;
	afc::string newsheet_rule_;

private:
	xls::Pos pos_;

private:
	int breakpoint_;

private:
	std::vector<Column> columns_;
	std::vector<Table*> tables_;
	
private:
	//PF pf_;
	std::vector<afc::Dat*>* super_dats_;	//上级表传下来的数据，帮助init
	std::vector<afc::Dat> table_dats_;	//本表所需处理的数据，需要init
	afc::dat::Mgr<afc::Dat> mgr_;
};

}//namespace
}//namespace

#endif//FILE
