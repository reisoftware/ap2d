
#ifndef _AFC_TCC_H_
#define _AFC_TCC_H_

#include "export.h"

#include <string>

struct TCCState;

namespace afc{z
  struct Tcc
  {
    TCCState * s_;
    void * m_;
  };
}

namespace tcc{

AFCAPI std::string last_error();
AFCAPI void exit(std::string msg = "");

AFCAPI void create(afc::Tcc& t, const std::string& cur_path);
AFCAPI void add_symbol(afc::Tcc& t, const std::string& fname, void * fptr);
AFCAPI void add_file(afc::Tcc& t, std::string file);
AFCAPI void add_code(afc::Tcc& t, std::string code);
AFCAPI void relocate(afc::Tcc& t);
AFCAPI void * get_symbol(afc::Tcc& t, std::string fname, bool thrownull=true);
AFCAPI void destory(afc::Tcc& t);

}//namespace

#endif//FILE

