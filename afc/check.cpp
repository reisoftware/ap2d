
#include "check.h"
#include "str_tools.h"
#include <vector>
#include <string>
#include <assert.h>
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

namespace afc{

bool check_path(const std::string path)
{
	if (path.empty()){
		return false;
	}
	std::vector<std::string> vec;
	afc::split_string(vec, path, "/\\");
	if (vec.size() <= 0){
		return false;
	}
	std::string drive = vec.front(); 
	BOOL b = ::PathFileExists(drive.c_str());
	if (!b){
		return false; 
	}
	std::string sep;
	if (path.find("\\") != -1){
		sep = "\\";
	}else{
		sep = "/";
	}
	std::string spath = vec.front() + sep;
	for(int i = 1; i < vec.size(); i++){
		spath = spath + vec[i] + sep;
		BOOL bb = ::PathFileExists(spath.c_str());
		if (!bb){
			return false;
		}
	}
	spath = "";	
	return true;
}

}//namespace
