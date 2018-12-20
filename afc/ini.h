#ifndef _AFC_INI_H_
#define _AFC_INI_H_

#include <string>
#include "export.h"

namespace ini{

AFCAPI std::string write_error();
AFCAPI std::string read(const char * file, const char * sec, const char * key);
AFCAPI void write(const char * file, const char * sec, const char * key, const char * val);

}//namespace

#endif//FILE
