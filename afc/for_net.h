
#ifndef _AFC_FOR_NET_H_
#define _AFC_FOR_NET_H_
#include <string>
#include <vector>
#include "export.h"

using std::string;
using std::vector;

struct Entry_Inf
{
	string ip;
	int port;
	string user;
	string pwd;
};

AFCAPI bool login_test(const Entry_Inf &inf);
// AFCAPI bool quit(const Entry_Inf &inf);

AFCAPI bool get_project_list(const Entry_Inf &inf, vector<string> &pronames);
AFCAPI bool get_project_list(const Entry_Inf &inf, string prjname, vector<string>& files);
AFCAPI bool create_project(const Entry_Inf &inf, string proname);
AFCAPI bool put_model_file_ftp(const Entry_Inf &inf, string proname, string local_path, string file_name);
AFCAPI bool get_model_file_ftp(const Entry_Inf &inf, string proname, string local_path, string file_name);
AFCAPI bool put_model_file(const Entry_Inf &inf, string proname, string local_path, string file_name);
AFCAPI bool get_model_file(const Entry_Inf &inf, string proname, string local_path, string file_name);

AFCAPI bool reset_pwd(const Entry_Inf &inf, string new_pwd);
//zgb
AFCAPI bool regist_user(const Entry_Inf &inf, string usr,string pass,string gid,string mail,string phone);
AFCAPI bool link_server(const Entry_Inf &inf);

#endif