// ApNet_Check.cpp: implementation of the ApNet_Check class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "ApNet_Check.h"

#include "Afxsock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ApNet_Check::ApNet_Check()
{

}

ApNet_Check::~ApNet_Check()
{

}
BOOL ApNet_Check::check(CString user,CString password)
{

	CSocket aSocket;
	CString port="8000";
	CString ip="115.159.81.210";
	//CString ip="www.apcad.com";
	CString strText;

	if(!aSocket.Create())
	{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", aSocket.GetLastError());
		AfxMessageBox(szMsg);
		return FALSE;
	}
	//转换需要连接的端口内容类型
	int nPort = atoi(port);
	//连接指定的地址和端口
	if(aSocket.Connect(ip, nPort))
	{
		CString key = "login\r\n"+user+"\r\n"+password+"\r\n";
		CString len;
		len.Format("%i",key.GetLength());
		strText = len+"\r\n"+key;
		char szRecValue[1024] = {0};
		//发送内容给服务器
		aSocket.Send(strText, strText.GetLength());
		//接收服务器发送回来的内容(该方法会阻塞, 在此等待有内容接收到才继续向下执行)
		aSocket.Receive((void *)szRecValue, 1024);
		CString res_val = szRecValue;
		int pos = res_val.Find("32");
		if(pos != -1){
			aSocket.Close();
			return TRUE;
		}else{
			aSocket.Close();
			return FALSE;

		}
	}else{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", aSocket.GetLastError());
		AfxMessageBox(szMsg);
		//关闭
		aSocket.Close();
		return FALSE;

	}

	return FALSE;

}
BOOL ApNet_Check::check_data(CString user,CString password)
{

	CSocket aSocket;
	CString port="8000";
	CString ip="115.159.81.210";
	CString strText;

	if(!aSocket.Create())
	{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", aSocket.GetLastError());
		AfxMessageBox(szMsg);
		return FALSE;
	}
	//转换需要连接的端口内容类型
	int nPort = atoi(port);
	//连接指定的地址和端口
	if(aSocket.Connect(ip, nPort))
	{
		CString key = "login\r\n"+user+"\r\n"+password+"\r\n";
		CString len;
		len.Format("%i",key.GetLength());
		strText = len+"\r\n"+key;
		char szRecValue[1024] = {0};
		//发送内容给服务器
		aSocket.Send(strText, strText.GetLength());
		//接收服务器发送回来的内容(该方法会阻塞, 在此等待有内容接收到才继续向下执行)
		aSocket.Receive((void *)szRecValue, 1024);
		CString res_val = szRecValue;
		int pos = res_val.Find("32");
		if(pos != -1){
			aSocket.Close();
			return TRUE;
		}else{
			aSocket.Close();
			return FALSE;

		}
	}else{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", aSocket.GetLastError());
		AfxMessageBox(szMsg);
		//关闭
		aSocket.Close();
		return FALSE;

	}

	return FALSE;

}
void ApNet_Check::save(CString user,CString password)
{
	CString file_name = ".//login";
	CStdioFile file;
	if(!file.Open(file_name,CFile::modeCreate|CFile::modeWrite) )
		return;


	file.WriteString(user +"\n");
	file.WriteString(password +"\n");

	file.Close();
}
void ApNet_Check::open(CString &user,CString &password)
{
	int cur_num = 0;
	CString file_name = ".//login";
	CStdioFile file;
	if(!file.Open(file_name,CFile::modeRead))
		return;
	CString line;
	file.ReadString(line);
	user = line;
	file.ReadString(line);
	password = line;	
	file.Close();
}