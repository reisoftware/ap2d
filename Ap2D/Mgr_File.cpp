// Mgr_File.cpp: implementation of the Mgr_File class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_File.h"

#include "Mgr_Dxfs.h"
#include "Global.h"
#include "ap2d_objs.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_File::Mgr_File()
{

}

Mgr_File::~Mgr_File()
{

}

void get_files_in_path(CString path,CString extend_name,CStringArray& files)
{
	CString strTemplatePath = path+"*"+extend_name;
	CString str;
  HANDLE hFind;
	WIN32_FIND_DATA fd ;
	hFind=::FindFirstFile((LPCTSTR)strTemplatePath,&fd);
	if(hFind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
			{
				str=(LPCTSTR)&fd.cFileName;
				if(str == ".")
					continue;
				else if(str == "..")
					continue;
				else
					files.Add(str);
			}
		}
		while(::FindNextFile(hFind,&fd));
	}
	FindClose(hFind);

}
BOOL judge_if_have_file(CString path,CString file_name)
{
	CString str,strDimPathFile;
    HANDLE hFind;
	WIN32_FIND_DATA fd ;
	strDimPathFile = path + "*.*";
	hFind=::FindFirstFile((LPCTSTR)strDimPathFile,&fd);
	if(hFind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
			{
				str=(LPCTSTR)&fd.cFileName;
				if(str == file_name)
					return TRUE;
			}
		}
		while(::FindNextFile(hFind,&fd));
	}
	FindClose(hFind);
	return FALSE;
}


bool find_files(std::string path,std::string keyword)
{
	CString str = path.c_str(),strDimPathFile;
  HANDLE hFind;
	WIN32_FIND_DATA fd ;
	strDimPathFile =str + "\\"+"*.*";
	hFind=::FindFirstFile((LPCTSTR)strDimPathFile,&fd);
	if(hFind!=INVALID_HANDLE_VALUE){
		do{
			if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
				continue;			
			CString name =(LPCTSTR)&fd.cFileName;
			if(name.Find(keyword.c_str()) !=-1)
				return true;			
		}
		while(::FindNextFile(hFind,&fd));
	}
	FindClose(hFind);
	return false;

}
bool find_files(std::string path,std::string keyword,std::vector<std::string> &dircets)
{
	CString str = path.c_str(),strDimPathFile;
  HANDLE hFind;
	WIN32_FIND_DATA fd ;
	strDimPathFile =str + "*.*";
	hFind=::FindFirstFile((LPCTSTR)strDimPathFile,&fd);
	if(hFind!=INVALID_HANDLE_VALUE){
		do{
			if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
				continue;			
			str=(LPCTSTR)&fd.cFileName;
			if(strcmp(str,keyword.c_str()) !=-1){
				dircets.push_back(str.GetBuffer(0));
				break;			
			}
		}
		while(::FindNextFile(hFind,&fd));
	}
	FindClose(hFind);
	return false;
	
}
void get_directs(std::string path,std::vector<std::string> &dircets)
{
	CString str = path.c_str(),strDimPathFile;
  HANDLE hFind;
	WIN32_FIND_DATA fd ;
	strDimPathFile =str + "*.*";
	hFind=::FindFirstFile((LPCTSTR)strDimPathFile,&fd);
	if(hFind!=INVALID_HANDLE_VALUE){
		do{
			str=(LPCTSTR)&fd.cFileName;
			if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )){
				dircets.push_back(str.GetBuffer(0));
			}
		}
		while(::FindNextFile(hFind,&fd));
	}
	FindClose(hFind);
	
}
void get_files(std::string path,std::string extension_name,std::vector<std::string> &files)
{
	CString str = path.c_str(),strDimPathFile;
  HANDLE hFind;
	WIN32_FIND_DATA fd ;
	strDimPathFile =str + "*.";
	strDimPathFile +=extension_name.c_str();
	hFind=::FindFirstFile((LPCTSTR)strDimPathFile,&fd);
	if(hFind!=INVALID_HANDLE_VALUE){
		do{
			if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
				continue;
			str=(LPCTSTR)&fd.cFileName;
			if(str == ".")
				continue;
			else if(str == "..")
				continue;
			else
				files.push_back(str.GetBuffer(0));
		}
		while(::FindNextFile(hFind,&fd));
	}
	FindClose(hFind);
	
}
bool find_dir(std::string path)
{
	CString dir,name,temp = path.c_str();
	CString path_len = temp.GetAt(temp.GetLength()-1);
	
	if(path_len == "\\")
		temp = temp.Left(temp.GetLength()-1);	

	int pos = temp.ReverseFind('\\');
	if(pos>0){
		dir = temp.Left(pos+1);
		temp.Delete(0,pos+1);
	}
	else
		return true;
	return find_dir(dir.GetBuffer(0),temp.GetBuffer(0));
}
bool find_dir(std::string path,std::string dir_name)
{
	CString str = path.c_str(),strDimPathFile;
  HANDLE hFind;
	WIN32_FIND_DATA fd ;
	strDimPathFile =str + "*.*";
	hFind=::FindFirstFile((LPCTSTR)strDimPathFile,&fd);
	if(hFind!=INVALID_HANDLE_VALUE){
		do{
			str=(LPCTSTR)&fd.cFileName;
			if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )){
				if(str.GetBuffer(0) == dir_name)
					return true;
			}
		}
		while(::FindNextFile(hFind,&fd));
	}
	FindClose(hFind);
	return false;
}
bool open_dir(std::string &path_name,std::string &file_name,std::string extend_name,std::string init_path)
{
	CString file,temp,extend,path,all_path;
	extend = extend_name.c_str();
	temp = extend +  " file format(*." +extend+  ") |*."  +extend+ "|All Files (*.*)|*.*||";
	static char szFilter[200] ;
	strncpy(szFilter,(LPCTSTR)temp,sizeof(szFilter));

	CFileDialog dlg( FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL );
	temp = "Save "+extend+" File";
	dlg.m_ofn.lpstrTitle = temp;
	dlg.m_ofn.lpstrInitialDir = init_path.c_str();   
	if(dlg.DoModal()== IDOK){
		all_path = dlg.GetPathName();
		file = dlg.GetFileName();
		CString judge = "."+extend;
		if(file.Find(judge)==-1){
			file += judge;
		}
		file_name = file.GetBuffer(0);

		CString path;
		change_dir(all_path,path);
		path_name = path;
//		int pos = all_path.ReverseFind('\\');
//		path_name = all_path.Left(pos);
//		path_name += "\\";
		return true;
	}
	return false;
}
/*
	if(File_Deal::judge_if_have_file(path.c_str(),name.c_str())){
		if(AfxMessageBox("project is exist.overwrite it?",MB_YESNO)!=IDYES){
			return;
		}
	}
*/
bool check_dir(CString path)
{
	if(path.Find(":\\") == -1)
		return false;
	return check_name(path);

}
bool check_name(CString name)
{
	if(name == "")
		return false;
	if(name == " ")
		return false;
	if(name.Find("::") != -1)
		return false;
	if(name.Find("/") != -1)
		return false;
	if(name.Find("'") != -1)
		return false;
	if(name.Find('"') != -1)
		return false;
	if(name.Find('|') != -1)
		return false;
	return true;

}
bool change_dir(CString path_name,CString &path)
{
	int pos = path_name.ReverseFind('\\');
	if(pos <0)
		return false;
	path = path_name.Left(pos);
	path += "\\";
	return true;	
}

std::string select_dir()
{
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	bi.pszDisplayName = name;
	
	bi.lpszTitle = "Select folder, please.";
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
		return "";
	CString strDirectoryPath;
	SHGetPathFromIDList(idl, strDirectoryPath.GetBuffer(MAX_PATH));
	strDirectoryPath.ReleaseBuffer();
	if(strDirectoryPath.IsEmpty())
		return "";
	if(strDirectoryPath.Right(1)!="\\")
		strDirectoryPath+="\\";
	
	return strDirectoryPath.GetBuffer(0);
}



static std::string add_sign(std::string path)
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

std::string exe_path()
{
	char buf[1000];
	GetModuleFileName(NULL, buf, 512);
	PathRemoveFileSpec(buf);
	return add_sign(buf);
}


bool get_file_hash(std::string file_name,std::string &hash_val)
{
	FILE * file = NULL; 
	double size=0;  
	char * buffer = NULL;  
	size_t result;  
	file = fopen(file_name.c_str(), "rb");  
	if(!file)
		return false;
	fseek (file,0 ,SEEK_END);  
	size = ftell(file);  
	rewind (file);  
	buffer = (char*)malloc(sizeof(char)*size+1);  
	if (!buffer)
		return false;  
	result = fread (buffer,1,size,file);  
	if (result != size)
		return false;  
	
	strcat(buffer,"\0");

	hash_val = get_hash_value(buffer);
	fclose (file);  
	free (buffer);  
	return true;
}

void upload_files(std::string ser_path,std::string files_dir)
{
	CString str = exe_path().c_str();
	CString aptable;

#ifdef _DEBUG
	aptable = str+"Upload_d.exe "+ser_path.c_str()+" "+files_dir.c_str();
#else 
	aptable = str+"Upload.exe "+ser_path.c_str()+" "+files_dir.c_str();
#endif
	::WinExec(aptable,SW_SHOW); 
}



std::string get_current_time()
{
	CString strTime,strYear,strMonth,strDay,strHour,strMinute,strSecond;
	int iYear,iMonth,iDay,iHour,iMinute,iSecond;
	CTime time(CTime::GetCurrentTime());
	iYear = time.GetYear();
	strYear.Format("%i",iYear);
	iMonth = time.GetMonth();
	strMonth.Format("%i",iMonth);
	iDay = time.GetDay();
	strDay.Format("%i",iDay);
	iHour = time.GetHour();
	strHour.Format("%i",iHour);
	iMinute = time.GetMinute();
	strMinute.Format("%i",iMinute);
	iSecond = time.GetSecond(); 
	strSecond.Format("%i",iSecond);
	
//	time.Format("%yY%bM%iD-%h:%m:%s");
//	CString s= time.GetTime();
	
	strTime = strYear+"Y"+strMonth+"M"+strDay+"D-"+strHour+":"+strMinute+":"+strSecond;
	return strTime.GetBuffer(0);
}

static std::string get_local_ver()
{
	std::string f = exe_path()+"version.ini";
	std::fstream file(f.c_str());
	if(!file.is_open())
		return "";
	char buff[100] = "0";
	while(strcmp(buff, "") != 0 ){
		file >> buff;
		break;
	}

	return buff;
}
static std::string get_server_ver()
{
	std::string val;
	read_str_server("ap2d_version",val);
	return val;
}

bool check_update(std::string ver)
{
	std::string server = get_server_ver();
	float server_ver = atof(server.c_str()); 
	float cur_ver = atof(ver.c_str()); 
	if(server_ver < cur_ver){
		write_str_server("ap2d_version",ver);
		return true;
	}else{
		return false;
	}
}
bool check_update()
{
	std::string local = get_local_ver();
	std::string server = get_server_ver();
	if(strcmp(local.c_str(),server.c_str()) == 0)
		return false;
	else
		return true;
}

void write_str_server(std::string key,std::string val)
{
	del_all(const_cast<char*>(key.c_str()),Global::instance()->ap2d());
	int id = new_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d());
  update_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d(),id,const_cast<char*>(val.c_str()));

}
void read_str_server(std::string key,std::string &val)
{
	char out[1024]={0};
	int index = 1;
	get_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d(),index,out);
	val = out;
}
std::string get_file_change_time(std::string file)
{
/*
	CFile f;
	if(!f.Open(file.c_str(),CFile::modeRead))
		return "";
	SYSTEMTIME      stLocal,time;
	FILETIME create,access,change;
	GetFileTime((HANDLE)f.m_hFile,&create,&access,&change);
	FileTimeToSystemTime(&change, &stLocal);   
	CTime t,t1;
*/
	
	std::string date="";
  struct stat buf;
  char tt[200];
  int result;
  //获得文件状态信息
  result =stat(file.c_str(), &buf );
  //显示文件状态信息
 if( result != 0 )
     perror( "error" );//并提示出错的原因，如No such file or directory（无此文件或索引）
  else
  {
//        cout<<"文件大小:"<<buf.st_size<<"字节"<<endl;
//        cout<<"所在磁盘盘符 :";
//        cout<<char(buf.st_dev + 'A')<<endl;
//        cout<<"文件创建时间:"<<ctime(&buf.st_ctime);
//        cout<<"访问日期:"<<ctime(&buf.st_atime);//注意这里访问时间为00:00:00为正常
//        cout<<"最后修改日期:"<<ctime(&buf.st_mtime);
      date = ctime(&buf.st_mtime);
			strcpy(tt,date.c_str());
			strcat(tt,"\0");
			CString s = tt;
			s.Replace(" ", "-");
			//因为有多余一空格，会删一个
			//UGLY
			s = s.Left(s.GetLength()-1);
			
      date = s.GetBuffer(0);

			
   }

		return date;
}

bool get_file_change_time(std::string file,time_t &time)
{
  struct stat buf;
  int result=-1;
  result =stat(file.c_str(), &buf);
	if( result != 0 ){
		 return false;
  }else {
      time = buf.st_mtime;
			return true;
   }
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
  if(!::WritePrivateProfileString(sec, key, val, file)){
  }
}

std::string get_file_data(std::string file)
{
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(file.c_str(),&ffd); 
	SYSTEMTIME sysCTime;
	FileTimeToSystemTime(&ffd.ftLastWriteTime,&sysCTime);	
	CString data;
	data.Format("%d-%d-%d",sysCTime.wYear,sysCTime.wMonth,sysCTime.wDay);
	return data.GetBuffer(0);
}

//BrowseCurrenPathtAllTypeFile 函数中files 中每一个都是全路径 需要自己手动转换。
void BrowseCurrenPathtAllTypeFile(std::string path,std::string extension_name,std::vector<std::string> &files,std::string static_path)
{
	CFileFind fileFinder;
	CString temp_path_str = path.c_str();
	CString temp_path_file_expand_name = extension_name.c_str();
	//CString path_all_names = temp_path_str + "*." + temp_path_file_expand_name;
	CString path_all_names = temp_path_str + "*.*";
	BOOL bFinished = fileFinder.FindFile(path_all_names);
	while(bFinished){
		bFinished = fileFinder.FindNextFile();
		if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //若是目录则递归调用此方法
		{
		//	files.push_back(fileFinder.GetFileName().GetBuffer(0));
			BrowseCurrenPathtAllTypeFile( LPCSTR(fileFinder.GetFilePath()+"\\"),extension_name,files,static_path);
		}
		else
		{
			CString fileName = fileFinder.GetFileName();
			if(fileName == ".")
				continue;
			else if(fileName == "..")
				continue;
			else
			{
				if (fileName.Right(4).Compare(".dxf") == 0)
				{
					CString temp_str;
					temp_str = fileFinder.GetFilePath();
				//	AfxMessageBox(temp_str);
					CString temp_static_str = static_path.c_str();
				//		AfxMessageBox(temp_static_str);
						temp_str.Replace(temp_static_str,NULL);

					files.push_back((temp_str).GetBuffer(0));
				//	files.push_back(fileName.GetBuffer(0));
				}
			}
		}
	}

 fileFinder.Close();
}

