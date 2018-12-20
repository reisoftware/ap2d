#ifndef _AFC_DATE_TIME_H_
#define _AFC_DATE_TIME_H_

#include "export.h"
#include <string>

namespace afc{

class AFCAPI Date_Time
{
public:
  std::string local(bool milli=true)const;
  std::string local_date()const;
  std::string local_time(bool milli=true)const;
};

}//namespace

#endif//FILE
