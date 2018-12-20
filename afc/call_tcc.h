#ifndef _AFC_CALL_TCC_H_
#define _AFC_CALL_TCC_H_

#include "export.h"
#include "tcc.h"

namespace afc{

typedef void (*PF_ADD_SYMBOL)(afc::Tcc& t);

AFCAPI void call_code(PF_ADD_SYMBOL pf_symbol, LPCTSTR func_code, LPCTSTR func_name);
AFCAPI void call_code(PF_ADD_SYMBOL pf_symbol, LPCTSTR func_code, LPCTSTR func_name, void * param1);
AFCAPI void call_code(PF_ADD_SYMBOL pf_symbol, LPCTSTR func_code, LPCTSTR func_name, void * param1, void * param2);


AFCAPI void call_script(PF_ADD_SYMBOL pf_symbol, LPCTSTR file, LPCTSTR func_name);
AFCAPI void call_script(PF_ADD_SYMBOL pf_symbol, LPCTSTR file, LPCTSTR func_name, void * param1);
AFCAPI void call_script(PF_ADD_SYMBOL pf_symbol, LPCTSTR file, LPCTSTR func_name, void * param1, void * param2);

}//namespace

#endif//FILE
