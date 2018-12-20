#include "stdafx.h"
#include "rpt_api_state.h"
#include "def_tools.h"

namespace afc{
namespace rpt{

Api_State::Api_State()
{
	init();
}

void Api_State::init()
{
	sheet_pos = NULL;
	table_pos = NULL;
	column_pos = NULL;
	super_dats = NULL;
	table_dats = NULL;
	filter = false;
	cur_dat = NULL;
	group = false;
	dat1 = NULL;
	dat2 = NULL;
	group1 = NULL;
	group2 = NULL;
	curgroup = NULL;
	sdb = NULL;
	newsheet = false;
}

// def_static_inctance(Api_State, api_static)
Api_State& api_state()
{
	static Api_State the;
	return the;
}

// api_state_current_group::api_state_current_group(std::vector<afc::Dat*>* cur_group)
// {
// 	api_state().cur_group = cur_group;
// }
// api_state_current_group::~api_state_current_group()
// {
// 	api_state().cur_group = NULL;
// }

}//namespace
}//namespace
