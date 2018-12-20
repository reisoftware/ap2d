#ifndef _AFC_FHIT_H_
#define _AFC_FHIT_H_

#include "export.h"

#include <vector>
#include <string>

#include "hk_sec.h"

namespace hk{


class AFCAPI Fhit
{
public:
	std::string file_;
  std::vector<Sec> hotkey_;
public:
  void push_sec(LPCSTR sec);
  void push_key(LPCSTR key, char hit=NOHIT, bool ctrl=false, bool shift=false);

public:
  Fhit():cur_(NULL){}

public:
  std::string find(char hit);
  hk::Sec * find(LPCSTR sec_name);

public:
  void ini_file(LPCSTR file){file_ = file;}
  void load();

public:
  void save();
  void set(LPCSTR sec, LPCSTR cmd, LPCSTR kval);
	bool is_conflict(LPCSTR kval);

public:
  void enable(bool b);
  void enable(LPCSTR sec, bool b);
  void enable(LPCSTR sec, LPCSTR cmd, bool b);

private:
  Sec * cur_;

};

AFCAPI void push_key(LPCSTR key, char hit=NOHIT, bool ctrl=false, bool shift=false);
//AFCAPI std::string find_cmd(char hit);
AFCAPI Fhit& default_fhit();
AFCAPI Fhit& fhit_instance();

}//namespace

#endif//FILE
