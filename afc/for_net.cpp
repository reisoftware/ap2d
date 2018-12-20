#include "StdAfx.h"
#include "for_net.h"
#include "net_client.h"
#include "str_tools.h"
#include "dir.h"
#include "msg_mgr.h"
#include "../include/getrace.h"

static const int cmd_buf_size = 1024;


static void trace_inf(const Entry_Inf& inf)
{
  TRACE_OUT("Inf(ip=%s, port=%d, uid=%s, pwd=%s).\n", 
    inf.ip.c_str(), 
    inf.port, 
    inf.user.c_str(), 
    inf.pwd.c_str());
}

/////////////////////////// << for get cmd >> ///////////////////////////////
static int fill_buf(SOCKET s,char* buf,int* cur,int* size)
{
  int max_num = cmd_buf_size - *cur - *size;
  if(max_num == 0){
    memcpy(buf,buf + *cur,*size);
    *cur = 0;
    max_num = cmd_buf_size - *size;
  }
  int nBytesRecv = recv(s, buf + *cur + *size, max_num, 0);
  if (SOCKET_ERROR == nBytesRecv) {
    printf("\nError occurred while reading from socket %ld.\n", WSAGetLastError());
    return 0; //error
  }
  *size += nBytesRecv;
  return 1;
}

static char* get_s(SOCKET s,char* buf)
{
  static char s_buf[cmd_buf_size];
  static int cur_ = 0;
  static int size_ = 0;
  int i ;
  
  while(1){
    int next_ = cur_;
    for(i = 0 ; i < size_; ++i,++next_){
      if(s_buf[next_] == '\n'){
        int size = i + 1;
        memcpy(buf,&s_buf[cur_],size);
        buf[size] = '\0';
        cur_ = next_ + 1;
        size_ -= size;
        return buf;
      }
    }
    if(!fill_buf(s,s_buf,&cur_,&size_))
      return NULL;
  }
  return NULL;
}

/////////////////////////// << for get cmd 2>> ///////////////////////////////
static int get_imp(SOCKET s,char* buf,int max)
{
  int count = recv(s,buf,max,0); 
  if(SOCKET_ERROR == count)
    return -1;
  return count; 
}

static int get_char(SOCKET s)
{
  static char buf[cmd_buf_size];
  static int cur_ = -1;
  static int size_ = 0;
  int c ;
  if(size_ == 0 && (size_ = get_imp(s,buf,cmd_buf_size)) == -1 )
    return EOF;
  cur_ = cur_ + 1 == cmd_buf_size? 0 : cur_ +1;
  c = buf[cur_];
  size_--;
  return c;
}

static char* get_line(SOCKET s,char* buf,int lim)
{
  int c;
  char* org = buf;
  while(lim-- && (c=get_char(s)) != EOF)
    if((*buf++ = c) == '\n')
      break;
    *buf = '\0';
    return (c == EOF && org == buf)?NULL:org;
}

/////////////////////////// << cmd str >> ///////////////////////////////
// string get_cmd(const Entry_Inf &inf, string cmd)
// {
// 	if ("ls" == cmd)
// 		cmd += "\n";
// 	else if ("login" == cmd) {
// 		cmd += " ";
// 		cmd += inf.user;
// 		cmd += " ";
// 		cmd += inf.pwd;
// 		cmd += "\n";
// 	}
// 	return cmd;
// }

static string get_ls_cmd()
{
  string cmd = "ls";
  cmd += "\n";
  return cmd;
}

static string get_ls_cmd(string prjname)
{
  string cmd = "ls";
  cmd += " ";
  cmd += prjname;
  cmd += "\n";
  return cmd;
}

static string get_login_cmd(const Entry_Inf &inf)
{
  string cmd = "login";
	cmd += " ";
  cmd += inf.user;
  cmd += " ";
  cmd += inf.pwd;
  cmd += "\n";
  return cmd;
}

static string get_passwd_cmd(string new_pwd)
{
  string cmd = "passwd";
  cmd += " ";
  cmd += new_pwd;
  cmd += "\n";
  return cmd;
}

static string get_crtprj_cmd(string prjname)
{
  string cmd = "crtprj";
  cmd += " ";
  cmd += prjname;
  cmd += "\n";
  return cmd;
}

static string get_put_cmd(LPCTSTR ftpfile, LPCTSTR prjfile, LPCTSTR prjname)
{
  string cmd = "put";
  cmd += " ";
  cmd += ftpfile;
  cmd += " ";
  cmd += prjfile;
  cmd += " ";
  cmd += prjname;
  cmd += "\n";
  return cmd;
}

static string get_get_cmd(LPCTSTR ftpfile, LPCTSTR prjfile, LPCTSTR prjname)
{
  string cmd = "get";
  cmd += " ";
  cmd += prjfile;
  cmd += " ";
  cmd += ftpfile;
  cmd += " ";
  cmd += prjname;
  cmd += "\n";
  return cmd;
}

static string get_put_cmd(LPCTSTR prjfile, LPCTSTR prjname)
{
  string cmd = "put";
  cmd += " ";
  cmd += prjfile;
  cmd += " ";
  cmd += prjname;
  cmd += "\n";
  return cmd;
}

static string get_get_cmd(LPCTSTR prjfile, LPCTSTR prjname)
{
  string cmd = "get";
  cmd += " ";
  cmd += prjfile;
  cmd += " ";
  cmd += prjname;
  cmd += "\n";
  return cmd;
}

/////////////////////////// << single cmd >> ///////////////////////////////
static void quit(SOCKET& s)
{
  send_data(s, "quit\n");
  close(&s);
}

static bool login(SOCKET& soct, const Entry_Inf &inf)
{
  TRACE_OUT("login()\n");
  trace_inf(inf);
  if(!connect_server(&soct, inf.ip.c_str(), inf.port))
    return false;
  char buf[cmd_buf_size] = "";
  string cmd = get_login_cmd(inf);
  if(!proc_cmd(buf, &soct, cmd.c_str()))
    return false;
  return 0 == strcmp("login ok\n$\n", buf);
}

static bool passwd(SOCKET& soct, string new_pwd)
{
  string cmd = get_passwd_cmd(new_pwd);
  char buf[cmd_buf_size] = "";
  if(!proc_cmd(buf, &soct, cmd.c_str())){
    return false;
  }
  return 0 == strcmp("$\n", buf);
}

static bool crtprj(SOCKET& soct, string prjname)
{
  string cmd = get_crtprj_cmd(prjname);
  char buf[cmd_buf_size] = "";
  if(!proc_cmd(buf, &soct, cmd.c_str())){
    return false;
  }
  return 0 == strcmp("$\n", buf);
}

static bool ls(SOCKET& soct, string& prjnames)
{
  string cmd = get_ls_cmd();
  char buf[cmd_buf_size] = "";
  if(!proc_cmd(buf, &soct, cmd.c_str())){
    return false;
  }
  prjnames = buf;
  return true;
}

static bool ls(SOCKET& soct, string prjname, string& fnames)
{
  string cmd = get_ls_cmd(prjname);
  char buf[cmd_buf_size] = "";
  if(!proc_cmd(buf, &soct, cmd.c_str())){
    return false;
  }
  fnames = buf;
  return true;
}

static bool put(SOCKET& soct, LPCTSTR ftpfile, LPCTSTR prjfile, LPCTSTR prjname)
{
  string cmd = get_put_cmd(ftpfile, prjfile, prjname);
  char buf[cmd_buf_size] = "";
  if(!proc_cmd(buf, &soct, cmd.c_str())){
    return false;
  }
  return 0 == strcmp("$\n", buf);
}

static bool get(SOCKET& soct, LPCTSTR ftpfile, LPCTSTR prjfile, LPCTSTR prjname)
{
  string cmd = get_get_cmd(ftpfile, prjfile, prjname);
  char buf[cmd_buf_size] = "";
  if(!proc_cmd(buf, &soct, cmd.c_str())){
    return false;
  }
  return 0 == strcmp("$\n", buf);
}

static bool put(SOCKET& soct, LPCTSTR prjfile, LPCTSTR prjname)
{
  string cmd = get_put_cmd(prjfile, prjname);
  char buf[cmd_buf_size] = "";
  if(!proc_cmd(buf, &soct, cmd.c_str())){
    return false;
  }
  return 0 == strcmp("$\n", buf);
}

static bool get(SOCKET& soct, LPCTSTR prjfile, LPCTSTR prjname)
{
  string cmd = get_get_cmd(prjfile, prjname);
  char buf[cmd_buf_size] = "";
  if(!proc_cmd(buf, &soct, cmd.c_str())){
    return false;
  }
  return 0 == strcmp("$\n", buf);
}

/////////////////////////// << complex cmd >> ///////////////////////////////
bool login_test(const Entry_Inf &inf)
{
  TRACE_OUT("login_test()\n");
  trace_inf(inf);
  SOCKET soct;
  if(login(soct, inf)){
	  quit(soct);
    return true;
  }
  return false;
}

bool get_project_list(const Entry_Inf &inf, vector<string> &pronames)
{
	SOCKET soct;
  if(!login(soct, inf)){
    return false;
  }
  string names;
  bool result = ls(soct, names);
  afc::split_string(pronames, names, "$\r\n");
	quit(soct);
	return result;
}

bool get_project_list(const Entry_Inf &inf, string prjname, vector<string>& files)
{
  SOCKET soct;
  if(!login(soct, inf)){
    return false;
  }
  string fnames;
  bool result = ls(soct, prjname, fnames);
  afc::split_string(files, fnames, "$\r\n");
  quit(soct);
  return result;
}

// bool get_project_list(const Entry_Inf &inf, vector<string> &pronames)
// {
// 	SOCKET soct;
// 	if(!connect_server(&soct, inf.ip.c_str(), inf.port))
// 		return false;
// 	char buf[1024] = {0};
// 	string cmd = get_cmd(inf, "login");
// 	if(!proc_cmd(buf, &soct, cmd.c_str()))
// 		return false;
// 	if (0 != strcmp("login ok\n$\n", buf)) {
// 		//AfxMessageBox("login failed");
// 		return false;
// 	}
// 	cmd = get_cmd(inf, "ls");
// 	if (!proc_cmd(buf, &soct, cmd.c_str()))
// 		return false;
//   afc::split_string(pronames, buf, "$\r\n");
// 	quit(soct);
// 
// 	return true;
// 	//return 0 == strcmp("login ok\n$\n", buf);
// }

bool create_project(const Entry_Inf &inf, string proname)
{
  SOCKET soct;
  if(!login(soct, inf)){
    return false;
  }
  bool result = crtprj(soct, proname);
  quit(soct);
	return result;
}

bool put_model_file_ftp(const Entry_Inf &inf, string proname, string local_path, string file_name)
{
  SOCKET soct;
  if(!login(soct, inf)){
    return false;
  }
  //string ftp_file_name = "a";
  local_path = afc::dir::add_sign(local_path);
  string local_file = local_path+file_name;
  if(!ftp_up(soct, inf.ip.c_str(), local_file.c_str(), file_name.c_str())){
    quit(soct);
    return false;
  }
  if(!put(soct, file_name.c_str(), file_name.c_str(), proname.c_str())){
    quit(soct);
    return false;
  }
	return true;
}

bool get_model_file_ftp(const Entry_Inf &inf, string proname, string local_path, string file_name)
{
  SOCKET soct;
  if(!login(soct, inf)){
    return false;
  }
  //string ftp_file_name = "a";
  local_path = afc::dir::add_sign(local_path);
  string local_file = local_path+file_name;
  if(!get(soct, file_name.c_str(), file_name.c_str(), proname.c_str())){
    quit(soct);
    return false;
  }
  if(!ftp_down(soct, inf.ip.c_str(), local_file.c_str(), file_name.c_str())){
    quit(soct);
    return false;
  }
  return true;
}

bool put_model_file(const Entry_Inf &inf, string proname, string local_path, string file_name)
{
  SOCKET soct;
  if(!login(soct, inf)){
    return false;
  }
  local_path = afc::dir::add_sign(local_path);
  string local_file = local_path+file_name;

  FILE* fp = fopen(local_file.c_str(), "r");
  if(!fp){
    quit(soct);
    return false;
  }

  string cmd = get_put_cmd(file_name.c_str(), proname.c_str());
  send_data(soct, cmd.c_str());

  char buf[cmd_buf_size];
  while(fgets(buf, cmd_buf_size, fp)){
    send_data(soct, buf);
  }
  send_data(soct, "$\n");
  if(!rcv_data(soct, buf, cmd_buf_size)) return 0;
  bool result = (0 != strstr(buf, "ok"));
  fclose(fp);
  quit(soct);

  return result;
}

// class Rcv_Buf
// {
// public:
//   string dat_;
//   bool get_line(string& ln){
//     if(dat_.find("\n") == string::npos){
//       
//     }
//   }
// };

bool get_model_file(const Entry_Inf &inf, string proname, string local_path, string file_name)
{
  SOCKET soct;
  if(!login(soct, inf)){
    return false;
  }
  local_path = afc::dir::add_sign(local_path);
  string local_file = local_path+file_name;


  FILE* fp = fopen(local_file.c_str(),"w");
  if(!fp){
    quit(soct);
  }

  string rcmd = get_get_cmd(file_name.c_str(), proname.c_str());
  if(send_data(soct,rcmd.c_str()) == 0) return 0;
  char buf[cmd_buf_size] = {0};
  while(get_s(soct,buf)){
//     afc::msg_answer();
    if(strstr(buf,"$\n") == buf)
      break;
    fprintf(fp,"%s",buf);
  }
//   string cmd = get_get_cmd(file_name.c_str(), proname.c_str());
//   send_data(soct, cmd.c_str());
//   int rcv_size = -1;
//   char buf[cmd_buf_size];
//   while(rcv_size == -1){
//     rcv_size = rcv_line(soct, buf, cmd_buf_size);
//     if(rcv_size == 0){
//       fclose(fp);
//       quit(soct);
//       return false;
//     }
//     fwrite(buf, sizeof(char), strlen(buf), fp);
//   }
  fclose(fp);
  quit(soct);
  return true;
}


bool reset_pwd(const Entry_Inf &inf, string new_pwd)
{
  TRACE_OUT("net::reset_pwd(ip=%s, port=%d, uid=%s, pwd=%s, newpwd=%s).\n", inf.ip.c_str(), inf.port, inf.user.c_str(), inf.pwd.c_str(), new_pwd.c_str());
  SOCKET soct;
  if(!login(soct, inf)){
    TRACE_OUT("login defail.\n");
    return false;
  }
  TRACE_OUT("login ok.\n");
  bool result = passwd(soct, new_pwd);
  TRACE_OUT("reset = %d.\n", result);
  quit(soct);
	return result;
}
//zgb
bool regist_user(const Entry_Inf &inf, string usr,string pass,string gid,string mail,string phone)
{
	SOCKET soct;
//	if(!login(soct, inf)){
//		TRACE_OUT("login defail.\n");
//		return false;
//	}
	TRACE_OUT("login ok.\n");
//	char cmd[8000] = {0};
	//sprintf(cmd,"reg %s %s %s %s %s\n",usr,pass,gid,mail,phone);
	string s = "reg " + usr + " " +pass + " " +gid + " " +mail + " " +phone;
	if(!send_data(soct,s.c_str())) 
		return false;	
	quit(soct);
	return true;
}


bool link_server(const Entry_Inf &inf)
{
	SOCKET soct;
	if(!connect_server(&soct, inf.ip.c_str(), inf.port)){
		return false;
	}
	quit(soct);
	return true;

}
