// Mgr_File.h: interface for the Mgr_File class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_FILE_H__D6ED0525_790D_4359_A678_650E2B6E1111__INCLUDED_)
#define AFX_MGR_FILE_H__D6ED0525_790D_4359_A678_650E2B6E1111__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#pragma warning (disable:4786)

#include <string>
#include <vector>


class Mgr_File  
{
public:
	Mgr_File();
	virtual ~Mgr_File();

};

void get_files_in_path(CString path,CString extend_name,CStringArray& files);
BOOL judge_if_have_file(CString path,CString file_name);

bool find_files(std::string path,std::string keyword);
bool find_files(std::string path,std::string keyword,std::vector<std::string> &dircets);
void get_directs(std::string path,std::vector<std::string> &dircets);
void get_files(std::string path,std::string extension_name,std::vector<std::string> &files);
bool find_dir(std::string path,std::string dir_name);
bool find_dir(std::string path);


bool open_dir(std::string &path_name,std::string &file_name,std::string extend_name,std::string init_path="");
bool check_dir(CString path);
bool check_name(CString name);
bool change_dir(CString path_name,CString &path);

std::string select_dir();


std::string exe_path();

std::string get_current_time();

//
bool get_file_hash(std::string file_name,std::string &hash_val);

void upload_files(std::string ser_path,std::string files_dir);


bool check_update(std::string ver);
bool check_update();

void write_str_server(std::string key,std::string val);
void read_str_server(std::string key,std::string &val);

std::string get_file_change_time(std::string file);
bool get_file_change_time(std::string file,time_t &time);


std::string read(const char * file, const char * sec, const char * key);
void write(const char * file, const char * sec, const char * key, const char * val);

std::string get_file_data(std::string file);

void BrowseCurrenPathtAllTypeFile(std::string path,std::string extension_name,std::vector<std::string> &files,std::string static_path);

#endif // !defined(AFX_MGR_FILE_H__D6ED0525_790D_4359_A678_650E2B6E1111__INCLUDED_)
