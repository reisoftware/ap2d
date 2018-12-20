
#ifndef _CLIENT_H
#define _CLIENT_H

//#ifdef CLIENT_EXPORTS
//#define CLIENT_EXT __declspec(dllexport)
//#else 
//#define CLIENT_EXT __declspec(dllimport)
//#endif 

#include <winsock2.h>

int  connect_server(SOCKET *s, const char* server, int portno);
int  proc_cmd(char *buf,const SOCKET *s, const char* cmd);
void close(const SOCKET *s);

bool ftp_up(SOCKET s, LPCTSTR ip, LPCTSTR local, LPCTSTR remote);
bool ftp_down(SOCKET s, LPCTSTR ip, LPCTSTR local, LPCTSTR remote);

int send_data(SOCKET s, const char* buf);
int rcv_data(SOCKET s,char* buf,DWORD bytes);
int rcv_line(SOCKET s, char* buf, DWORD bytes);

#endif