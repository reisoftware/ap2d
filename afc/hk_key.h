#ifndef _AFC_FKEY_H_
#define _AFC_FKEY_H_

#include "export.h"
#include <string>

namespace hk{

const char NOHIT = '~';

class AFCAPI Key
{
public:
  std::string cmd_;
private:
  char hit_;
  bool ctrl_;
  bool shift_;

private:
  void enable(bool b){able_ = b;}
  bool able_; //  T:enable,F:disable.

public:
  std::string key_value()const;
  
private:
  bool is_hit(char hit);
  
private:
  Key():hit_(NOHIT),ctrl_(false),shift_(false),able_(false){}
  
private:
  friend class Sec;
  friend class Fhit;
};

AFCAPI bool can_hit(char c);
AFCAPI bool can_use(char c);

}//namespace

#endif//FILE
