// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <Wininet.h>
#include <assert.h>

#include "getrace.h"

#define MAX_IP   16
#define MAX_USER 32
#define MAX_PWD  16

int init_net();
int connect_server(SOCKET *s, char* server, int portno);
int proc_cmd(char *buf, const SOCKET *s, char* cmd);
void close(const SOCKET *s);

int connect_server(SOCKET* s, const char* server, int portno)
{
  assert(NULL != s && NULL != server);
  TRACE_OUT("connect_server()\n");
  TRACE_OUT("server = %s, port = %d\n", server, portno);
  if(!init_net()){
    TRACE_OUT("!init_net()\n");
		return 0;
  }
	struct sockaddr_in ServerAddress;
	struct hostent *Server;
		
	//Create a socket
	*s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
	if (INVALID_SOCKET == *s) 
	{
		TRACE_OUT("Error occurred while opening socket: %d.\n", WSAGetLastError());
		return 0; //error
	}
		
	//Get the server details
	Server = gethostbyname(server);
		
	if (Server == NULL) 
	{
		closesocket(*s);
		TRACE_OUT("Error occurred no such host.\n");
		return false; //error
	}
		
	//Cleanup and Init with 0 the ServerAddress
	ZeroMemory((char *) &ServerAddress, sizeof(ServerAddress));
		
	ServerAddress.sin_family = AF_INET;
		
	//Assign the information received from gethostbyname()
	CopyMemory((char *)&ServerAddress.sin_addr.s_addr, 
		(char *)Server->h_addr,
		Server->h_length);
		
	ServerAddress.sin_port = htons(portno);
		
	//Establish connection with the server
	if (SOCKET_ERROR == ::connect(*s, (const struct sockaddr *)(&ServerAddress),sizeof(ServerAddress))) 
	{
		closesocket(*s);
		TRACE_OUT("Error occurred while connecting.\n");
		return 0; //error
	}
	TRACE_OUT("connect_server(), success \n");
	return 1;
}

int init_net()
{
		WSADATA wsaData;
		
		int nResult;
		nResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (NO_ERROR != nResult){
			printf("error:init net\n");
			return 0;
		}
		return 1;
}
int send_data(SOCKET s, const char* buf)
{
		int sent_bytes = send(s, buf, strlen(buf), 0);
		if (SOCKET_ERROR == sent_bytes) 
		{
			printf("\nError occurred while writing to socket %ld.\n", WSAGetLastError());
			return 0; //error
		}
		return sent_bytes;
}
int rcv_data(SOCKET s,char* buf,DWORD bytes)
{
		int nBytesRecv = recv(s, buf, bytes, 0);
		
		if (SOCKET_ERROR == nBytesRecv) 
		{
			printf("\nError occurred while reading from socket %ld.\n", WSAGetLastError());
			buf[0] = 0;
			return 0; //error
		}
		*(buf + nBytesRecv) = 0;
		if(strstr(buf,"$\n") == 0){
			nBytesRecv += rcv_data(s,buf+nBytesRecv,bytes);
		}
		return nBytesRecv;
}

int rcv_line(SOCKET s, char * buf, DWORD bytes)
{
  int nBytesRecv = recv(s, buf, bytes, 0);
  if(SOCKET_ERROR == nBytesRecv){
    buf[0] = 0;
    return 0;
  }
  return 0;
}

////0:失败，-1：待续，其他：结束
// int rcv_line(SOCKET s, char* buf, DWORD bytes)
// {
//   int nBytesRecv = recv(s, buf, bytes, 0);
//   if(SOCKET_ERROR == nBytesRecv){
//     buf[0] = 0;
//     return 0;
//   }
//   char * dollar = strstr(buf,"$\n");
//   if(dollar != 0){
//     dollar[0] = '\n';
//     dollar[1] = '\0';
//     return nBytesRecv;
//   }
//   return -1;
// }

void close_net()
{
	WSACleanup();
}

int login(SOCKET s,char* name,char* pass)
{
	char cmd[255] = {0};
	sprintf(cmd,"login %20s %20s\n",name,pass);
	if(!send_data(s,cmd)) return 0;
	char buf[1024];
	if(!rcv_data(s,buf,1024)) return 0;
	if(strstr(buf,"login ok") != buf) return 0;
	return 1;
}

int getftp(SOCKET s,char* ftpname,char* ftppass)
{
	char cmd[] = "getftp\n";
	if(!send_data(s,cmd)) return 0;
	char buf[1024];
	if(!rcv_data(s,buf,1024)) return 0;
	sscanf(buf,"%32s %32s",ftpname,ftppass);
	return 1;
}

HINTERNET get_ftp(char* ftpname,char* ftppass, LPCTSTR ip)
{
	HINTERNET session = InternetOpen("rei",INTERNET_OPEN_TYPE_DIRECT,0,0,0);
	if(!session) {printf("error:open internet\n");return 0;}
	HINTERNET ftp = InternetConnect(session,
		//"192.168.1.10",
    ip,
		INTERNET_DEFAULT_FTP_PORT,
		ftpname,
		ftppass,
		INTERNET_SERVICE_FTP,
		INTERNET_FLAG_PASSIVE,
		0);
	if(!ftp) printf("error:open ftp\n");
	//InternetCloseHandle(session);
	return ftp;
}

int testftp(SOCKET s,char* local,char* remote,char* newlocal)
{
	char name[32];
	char pass[32];
	if(!getftp(s,name,pass)) return 1;
//	printf("ftp:name=%s pass = %s\n",name,pass);
	HINTERNET ftp = get_ftp(name,pass, "192.168.1.10");
	if(!ftp) return 1;
	if(!FtpPutFile(ftp,local,remote,FTP_TRANSFER_TYPE_BINARY|INTERNET_FLAG_NEED_FILE,0)){
		InternetCloseHandle(ftp);
		printf("error:put file\n"); return 1;
	}
	if(!FtpGetFile(ftp,remote,newlocal,FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY,0))
		printf("error:get file\n");
	InternetCloseHandle(ftp);
	printf("ftp put & get ok\n$\n");
	return 1;
}

int process_cmd(SOCKET s,char* cmd)
{
	if(strstr(cmd,"testftp")==cmd){
		char temp[255];
		char local[255];
		char remote[255];
		char newlocal[255];
		if(sscanf(cmd,"%s %s %s %s",temp,local,remote,newlocal) == 4)
			return testftp(s,local,remote,newlocal);
		printf("usage:testftp local remote newlocal\n$\n");
		return 1;
	}
	if(!send_data(s,cmd)) return 0;
	char buf[1024];
	if(!rcv_data(s,buf,1024)) return 0;
	//printf("%s",buf);
	if(strstr(cmd,"quit") == cmd)
		return 0;
	return 1;
}

//////////////////////////////////////////////////////////////////////////
int proc_cmd(char *buf, const SOCKET *s, const char* cmd)
{
	assert(NULL != buf && NULL != s && NULL != cmd);
	if(!send_data(*s, cmd)) return 0;
	if(!rcv_data(*s, buf, 1024)) return 0;
	//printf("%s", buf);
	//if(strstr(cmd, "quit") == cmd)
	//	return 0;
	return 1;
}

bool ftp_up(SOCKET s, LPCTSTR ip, LPCTSTR local, LPCTSTR remote)
{
  char name[32];
  char pass[32];
  if(!getftp(s,name,pass)) 
    return false;
  HINTERNET ftp = get_ftp(name,pass,ip);
  if(!ftp) 
    return false;
  if(!FtpPutFile(ftp,local,remote,FTP_TRANSFER_TYPE_BINARY|INTERNET_FLAG_NEED_FILE,0)){
    InternetCloseHandle(ftp);
    return false;
  }
  InternetCloseHandle(ftp);
  return true;
}

bool ftp_down(SOCKET s, LPCTSTR ip, LPCTSTR local, LPCTSTR remote)
{
  char name[32];
  char pass[32];
  if(!getftp(s,name,pass)) 
    return false;
  HINTERNET ftp = get_ftp(name,pass,ip);
  if(!ftp) 
    return false;
  if(!FtpGetFile(ftp,remote,local,FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY,0)){
    InternetCloseHandle(ftp);
    return false;
  }
  InternetCloseHandle(ftp);
  return true;
}

void close(const SOCKET *s)
{
	assert(NULL != s);
	closesocket(*s);
	close_net();
}

//int main(int argc, char* argv[])
//{	
//	SOCKET s;
//	if(connect_server(&s, "192.168.1.10", 50000) == 0)
//		return 0;
//
//	char cmd[255] = {0};
////	fgets(cmd, 255, stdin);
//	char buf[1024] = {0};
////	if(!proc_cmd(buf, &s, cmd)) 
////		return 0;
//	proc_cmd(buf, &s, "login tbj 123456\n");
//	printf("cmd = %s", cmd);
//	printf("%s\n", buf);
//	//fgets(cmd, 255, stdin);
//	//strcpy(cmd, "ls\n\r");
//	proc_cmd(buf, &s, "ls\n");
//	printf("%s\n", buf);
//	proc_cmd(buf, &s, "quit\n");
//	printf("%s\n", buf);
//
//	close(&s);
//	return 0;
//}

//int main(int argc, char* argv[])
//{
//		if(!init_net())
//			return 0;
//		
//		SOCKET s;
//		if(connect_server(&s,"192.168.1.10",50000) == 0)
//			return 0;
//
//		char cmd[255] = {0};
//		while(fgets(cmd,255,stdin)){
//		//	char* rt = strpbrk(cmd,"\r\n");
//		//	if(rt) *rt = 0;
//			if(!process_cmd(s,cmd)) 
//				break;
//			char buf[255] = {0};
//			printf("%s\n", buf);
//		}
//
//
//		closesocket(s);
//		close_net();
//		return 0;
//}
