#ifndef _AFC_RPT_API_STATE_H_
#define _AFC_RPT_API_STATE_H_


#include "export.h"
#include "dat.h"
#include "xls_pos.h"
#include "rpt_style_db.h"
#include <vector>


namespace afc{
namespace rpt{

class Api_State
{
public:
	xls::Pos last_pos;
	xls::Pos * sheet_pos;
	xls::Pos * table_pos;
	xls::Pos * column_pos;

public:
	//init
	std::vector<afc::Dat*>* super_dats;
	std::vector<afc::Dat>* table_dats;

public:
	bool filter;
	afc::Dat * cur_dat;

public:
	bool group;
	afc::Dat * dat1;
	afc::Dat * dat2;

public:
	bool sort;
	std::vector<afc::Dat*>* group1;
	std::vector<afc::Dat*>* group2;

public:
	std::vector<afc::Dat*>* curgroup;
	afc::string cur_cell_content;

public:
  bool newsheet;

public:
	//ÑùÊ½¿â
	rpt::SDB * sdb;

public:
	Api_State();
	void init();
};

AFCAPI Api_State& api_state();
#define rpt_api afc::rpt::api_state()

// class api_state_current_group
// {
// public:
// 	api_state_current_group(std::vector<afc::Dat*>* cur_group);
// 	~api_state_current_group();
// };

}//namespace
}//namespace


#endif//FILE
