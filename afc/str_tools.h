
#ifndef _AFC_STR_TOOLS_H_
#define _AFC_STR_TOOLS_H_



#include <string>
#include <vector>
#include "export.h"

namespace afc{


AFCAPI void split_string(std::vector<std::string>& destination, 
                          std::string source,
                          char separator);
AFCAPI void split_string(std::vector<std::string>& destination, 
                          std::string source, 
                          std::string separators);
//****************************************************************
//char * s = "aa+b-ccc*ddddd/123";
//vector<string> d;
//char * sep = "+-*/";
//split_string(d, s, sep);
//==> aa b ccc ddddd 123
//****************************************************************


AFCAPI std::string filter_string(std::string s, std::string del);
AFCAPI std::string append_string(std::string s, int n, char c = ' ');
  

}//namespace

#endif//FILE

