#ifndef _AFC_PASS_H_
#define _AFC_PASS_H_


#include "export.h"

namespace afc{

namespace pwd{
AFCAPI char* encrypt(const char* s,char* d);
AFCAPI char* decrypt(const char* s,char* d);

}//namespace pwd

} //namespace afc


#endif //FILE