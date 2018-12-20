#ifndef _MFCEX_XLS_H_
#define _MFCEX_XLS_H_

#include "export.h"
#include "xls_excel.h"
#include "../afc/xls_book.h"


namespace aex{
namespace xls{


AEXAPI bool output(afc::xls::Book& xbook, LPCTSTR file);


}//namespace
}//namespace


#endif//FILE
