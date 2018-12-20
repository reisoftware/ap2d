#ifndef _AFC_FSEC_H_
#define _AFC_FSEC_H_

#include "export.h"
#include <vector>
#include <string>
#include "hk_key.h"

namespace hk{

class AFCAPI Sec
{
public:
  std::string name_;
  std::vector<Key> keys_;
  
private:
  std::string find(char hit);
  Key * find(LPCSTR cmd);

private:
  void enable(bool b);
  void enable(LPCSTR cmd, bool b);
  
private:
  friend class Fhit;
};


}//namespace

#endif//FILE
