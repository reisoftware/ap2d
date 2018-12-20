#include "stdafx.h"
#include "date_time.h"


namespace afc{

std::string Date_Time::local(bool milli)const
{
  std::string s = local_date() + " " + local_time(milli);
  return s;
}

std::string Date_Time::local_date()const
{
  SYSTEMTIME t;
  GetLocalTime(&t);
  
  char buf[32];
  sprintf(buf, "%0.4d-%0.2d-%0.2d", t.wYear, t.wMonth, t.wDay);
  
  return buf;
}

std::string Date_Time::local_time(bool milli)const
{
  SYSTEMTIME t;
  GetLocalTime(&t);

  char buf[32];
  if(milli){
    sprintf(buf, "%0.2d:%0.2d:%0.2d.%0.3d", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
  }else{
    sprintf(buf, "%0.2d:%0.2d:%0.2d", t.wHour, t.wMinute, t.wSecond);
  }

  return buf;
}




}//namespace
