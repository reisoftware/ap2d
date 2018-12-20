#ifndef _MFCEX_RPT_ADD_API_H_
#define _MFCEX_RPT_ADD_API_H_

#include "export.h"
#include "../bin/script/rpt/rpt_steel.h"
#include "../afc/tcc.h"

/////////////////////// << TCC >> ///////////////////////
AEXAPI void rpt_add_symbol(afc::Tcc &t);

/////////////////////// << api >> ///////////////////////
void rpt_get_project_name(char * buf, int bufsize);
void rpt_add_all();
void rpt_add_assembly();
void rpt_add_part(const char * no);



#endif//FILE


