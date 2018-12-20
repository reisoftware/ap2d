#ifndef _AFC_LOG_MGR_H_
#define _AFC_LOG_MGR_H_

#include "export.h"
#include <string>

namespace afc{


class AFCAPI Log_Mgr
{
public:
  void clear();
  void push_back(LPCTSTR log);

public:
  const std::string& logs()const;

public:
//   void show()const;
  void show(LPCTSTR file)const;
  void save(LPCTSTR file)const;
  
private:
  std::string logs_;
};

}//namespace


#endif//FILE
