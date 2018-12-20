#ifndef _AFC_XLS_BOOK_H_
#define _AFC_XLS_BOOK_H_

#include "export.h"
#include "xls_sheet.h"
#include <vector>

namespace afc{
namespace xls{

class Book
{
public:
	afc::string name;
	std::vector<Sheet> sheets;

};

}//namespace
}//namespace


#endif//FILE
