#ifndef _AFC_LUA_MGR_H_
#define _AFC_LUA_MGR_H_

#include "export.h"
#include <iostream>

namespace afc{

class AFCAPI Lua_Mgr
{
  enum VAL_TYPE {VAL_STRING, VAL_DIGIT};
public:
  Lua_Mgr(std::ofstream& ofs, int tab, LPCTSTR key, LPCTSTR val, VAL_TYPE type);

private:
  int tab_;
  std::string key_;
  std::string val_;
};

}//namespace

#endif//FILE
