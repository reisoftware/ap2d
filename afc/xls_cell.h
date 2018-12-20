#ifndef _AFC_XLS_CELL_H_
#define _AFC_XLS_CELL_H_

#include "export.h"
#include "xls_pos.h"
#include "xls_cell_style.h"
#include "str.h"

namespace afc{
namespace xls{

class AFCAPI Cell
{
public:
	xls::Pos pos;
	afc::string content;
	CS style;
};

}//namespace
}//namespace

#endif//FILE
