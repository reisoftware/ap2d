#include "StdAfx.h"

#include <shellapi.h>
#include <fstream>
#include "getrace.h"

#include "log_mgr.h"

namespace afc{

void Log_Mgr::push_back(LPCTSTR log)
{
  if(logs_.find(log) != std::string::npos){
    return;
  }
  logs_ += log;
  logs_ += "\n";
}

void Log_Mgr::clear()
{
  logs_ = "";
}

const std::string& Log_Mgr::logs()const
{
  return logs_;
}


// void Log_Mgr::show()const
// {
//   ::ShellExecute(NULL, "open", "abbcc", "", "", SW_SHOW);
//   ::WinExec("notepad.exe", SW_SHOW);
//   //NOOK
// }

void Log_Mgr::show(LPCTSTR file)const
{
  save(file);
  if(logs_.empty()){
    return;
  }
  ::ShellExecute(NULL, "open", file, "", "", SW_SHOW);
}


void Log_Mgr::save(LPCTSTR file)const
{
//   TRACE_OUT("Log_Mgr::save(file, %d)\n", append);
//   LPCTSTR t = append ? "w" : "w";
//   LPCTSTR t = append ? "a+" : "w";
//   LPCTSTR t = NULL;
//   if(append){
//     t = "a+";
//   }else{
//     t = "w";
//   }
//   TRACE_OUT("t == %s\n)", t);
  LPCTSTR t = "w";
  FILE * f = fopen(file, t);
  if(!f){
    TRACE_OUT("fail: Log_Mgr::save(file), fopen(%s).\n", file);
    return;
  }
  fwrite(logs_.c_str(), sizeof(char), logs_.size(), f);
  fclose(f);
}


}//namespace

