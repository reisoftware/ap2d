#ifndef _AFC_DIR_H_
#define _AFC_DIR_H_

#include "export.h"
#include <string>
#include <vector>

namespace afc{
namespace dir{

enum TYPE {FOLDER, FILE};
struct Item
{
  TYPE type;
  std::string name;
};

AFCAPI std::string cur_name(LPCTSTR path_name);//// c:\bin\abc => abc
AFCAPI TYPE cur_type(LPCTSTR path_name);
AFCAPI void item_name(std::vector<Item>& fnames, LPCTSTR path);
AFCAPI std::string add_sign(std::string path);
AFCAPI void create_floder(LPCTSTR path);
AFCAPI std::string exe_path();

}//namespace//dir
}//namespace//afc

#endif//FILE


