#include "stdafx.h"
#include "ini.h"
#include "str_tools.h"

#include <assert.h>
#include <windows.h>
#include <iostream.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

namespace ini{

static const char * write_error_ = "error0001: ini file cann't be write.";
std::string write_error()
{
  return ini::write_error_;
}

std::string read(const char * file, const char * sec, const char * key)
{
  const char * NOSTR = "INI_ERROR\1";
  const int BUFSIZE = 256;
  char buf[BUFSIZE];
  DWORD buflen = ::GetPrivateProfileString(sec, key, NOSTR, buf, BUFSIZE, file);
  std::string str = NOSTR;
  buf[buflen] = 0;
  str = buf;
  if(str == NOSTR){
    str = "";
  }
  return str;
}

void write(const char * file, const char * sec, const char * key, const char * val)
{
	std::vector<std::string> vec;
	afc::split_string(vec, file, "/\\");
	assert((vec.size() > 0) && "The file path is NUll.");
	std::string drive = vec.front(); 
	BOOL b = ::PathFileExists(drive.c_str());
	assert((b != 0) && "The drive is not exist.");
	
	std::string sep = "\\";
	std::string path = vec.front() + sep;
	for(int i = 1; i < vec.size() - 1; i++){
		 path = path + vec[i] + sep;
		BOOL bb = ::PathFileExists(path.c_str());
		if (!bb){
			::CreateDirectory(path.c_str(), NULL);
		}
	}
	path = "";
  if(!::WritePrivateProfileString(sec, key, val, file)){
    throw(ini::write_error);
  }
} 

}//namespace


