#include "stdafx.h"
#include "dir.h"
#include "str_tools.h"
#include <vector>
#include <string>
#include <cassert>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")


namespace afc{
namespace dir{

//// c:\bin\abc => abc
std::string cur_name(LPCTSTR path_name)
{
  assert(path_name);
  std::vector<std::string> pns;
  afc::split_string(pns, path_name, "/\\");
  if(pns.empty()){
    return "";
  }
  return pns.back();
}

TYPE cur_type(LPCTSTR path_name)
{
  //NOOK
  return FOLDER;
}

void item_name(std::vector<Item>& fnames, LPCTSTR path)
{
  std::string mypath = add_sign(path);
  mypath += "*";
  HANDLE hf;
  WIN32_FIND_DATA fd;
  hf = ::FindFirstFile(mypath.c_str(), &fd);
  if(hf == INVALID_HANDLE_VALUE){
    ::FindClose(hf);
    return;
  }
  do{
    if(strcmp(fd.cFileName, ".") == 0){
      continue;
    }
    if(strcmp(fd.cFileName, "..") == 0){
      continue;
    }
    Item it;
    if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
      it.type = FOLDER;
    }else{
      it.type = FILE;
    }
    it.name = fd.cFileName;
    fnames.push_back(it);
  }while(::FindNextFile(hf, &fd));
  ::FindClose(hf);
}

std::string add_sign(std::string path)
{
  if(path.empty()){
    return "\\";
  }
  if(path[path.size()-1] == '/' || path[path.size()-1] == '\\'){
    return path;
  }
  path += "\\";
  return path;
}

static void create_a_floder(LPCTSTR path)
{
  assert(path);
  std::vector<std::string> dirs;
  afc::split_string(dirs, path, "/\\");
  if(dirs.empty()){
    return;
  }
  std::string cur_dir = dirs.back();

  if(strstr(cur_dir.c_str(), ":") != NULL){
    return;
  }

  if(!::PathFileExists(path)){
    ::CreateDirectory(path, NULL);
  }
}

void create_floder(LPCTSTR path)
{
  assert(path);
  std::vector<std::string> dirs;
  afc::split_string(dirs, path, "/\\");

  std::string cur_path;
  std::string sep = "\\";
  int count = dirs.size();
  int i=0;
  for(i=0; i<count; ++i){
    cur_path += dirs[i];
    cur_path += sep;
    create_a_floder(cur_path.c_str());
  }
}


std::string exe_path()
{
	char buf[1000];
	GetModuleFileName(NULL, buf, 512);
	PathRemoveFileSpec(buf);
	return add_sign(buf);
}

}//namespace//dir
}//namespace//afc
