#ifndef _AFC_CASE_SENSITIVE_H_
#define _AFC_CASE_SENSITIVE_H_

#include "export.h"
#include <string>

namespace afc{

AFCAPI std::string upper(std::string source);
AFCAPI std::string lower(std::string source);

}

#endif