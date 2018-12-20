#ifndef _MFCEX_XLS_TOOLS_H_
#define _MFCEX_XLS_TOOLS_H_

#include "../afc/str.h"
#include "../afc/xls_pos.h"
//#include <string>

namespace aex{

namespace xls{

	bool is_regular_pos(LPCTSTR pos);
	afc::string get_regular_pos(long x, long y, long w = 1, long h = 1);
	afc::string get_regular_pos(const afc::xls::Pos& pos);

}//namespace

}//namespace

#endif//FILE
