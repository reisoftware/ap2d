 
#include "stdafx.h"
#include "str_tools.h"

namespace afc{

  void split_string(std::vector<std::string>& destination, 
                    std::string source, 
                    std::string separators) 
  {
    std::string item;
    int source_length = source.length();
    for(int i=0; i<source_length; i++) {
      if(separators.find(source[i]) == std::string::npos) {
        item += source[i];
      }else{
        if (!item.empty()) {
          destination.push_back(item);
          item = "";
        }
      }
    }
    if(!item.empty()) {
      destination.push_back(item);
      item = "";
    }
  }


  void split_string(std::vector<std::string>& destination, 
                    std::string source, 
                    char separator) 
  {
    std::string separators;
    separators.insert(separators.end(), separator);
    afc::split_string(destination, source, separators);
  }

  std::string filter_string(std::string s, std::string del)
  {
    std::string d;
    int c=s.size();
    int i=0;
    for(i=0; i<c; ++i){
      if(del.find(s[i]) == std::string::npos){
        d.insert(d.end(), s[i]);
      }
    }
    return d;
  }

  std::string append_string(std::string s, int n, char c)
  {
    std::string d = s;
    int i=d.size();
    for(; i<n; ++i){
      d.insert(d.end(), c);
    }
    return d;
  }

}//namespace




