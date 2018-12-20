// DB_File.cpp: implementation of the DB_File class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "DB_File.h"

#include "Global.h"
#include "ap2d_objs.h"
#include "encode.h"
#include <set>
#include "Mgr_Lua.h"
#include "DB_View.h"

#include <afxinet.h>



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void ApFile::get_str(char *out)
{
	rei_quit();
	rei_add_str(NULL,"name_",name_.c_str());
	rei_add_str(NULL,"hash_val_",hash_val_.c_str());

	rei_get_encode(out);
}

void ApFile::set_from_str(char *in)
{
	rei_init(in);

	name_ = rei_get("name_");
	hash_val_ = rei_get("hash_val_");

	rei_quit();

	
	
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DB_File::DB_File()
{

}

DB_File::~DB_File()
{

}
void DB_File::upload(std::string key)
{
	del_all(const_cast<char*>(key.c_str()),Global::instance()->ap2d());

	for(int i=0;i<items_.size();i++){
		char val[MAX_REDIS]={0};
		items_[i].get_str(val);		
		int id = new_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d());
  	update_key(const_cast<char*>(key.c_str()),const_cast<char*>(key.c_str()),Global::instance()->ap2d(),id,val);
		
	}
}
void DB_File::create_item(char *in)
{
	ApFile item;
	item.set_from_str(in);
	if(strcmp(item.name_.c_str(),"")!=0 )
		items_.push_back(item);

}

void DB_File::download(std::string key)
{
	items_.clear();

	if(redis_hgetall(Global::instance()->ap2d()->redis,const_cast<char*>(key.c_str()))){ 
		char str[MAX_REDIS] = {0}; 
		char *rs = NULL; 
		rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
		std::string val = rs;
		rs = strchr(str,'*'); 
		if(!rs) 
			return ; 	
		int num = atoi(rs + 1); 	
		
		for(int i = 0; i < num / 2 ; ++i){ 
			str[0] = 0;
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			rs =  redis_getline(Global::instance()->ap2d()->redis,str,MAX_REDIS);
			if(!rs) 
				return;
			std::string val = rs;
			create_item(const_cast<char*>(val.c_str()));
		}	
	}

}
void DB_File::upload_ser()
{
	std::string old_file,new_file;
	for(int i=0;i<items_.size();i++){
		old_file = Global::instance()->project_info().dir_path+items_[i].name_;
		new_file = Global::instance()->project_info().dir_path+"server\\"+items_[i].name_;
		CopyFile(old_file.c_str(),new_file.c_str(),TRUE);
	}

}

void DB_File::download_ser(std::string detail_name,strings &layer_file_names)
{
	std::string local_file,name ;
	for(int i=0;i<layer_file_names.size();i++){
		name = layer_file_names[i];
		Global::instance()->get_local_file_name(layer_file_names[i],local_file);
		download_ftp(layer_file_names[i],local_file);
		open_lua(local_file,DB_View::instance()->cur_view()->scene()->database());
	}
	//下载标注层
	//在detail的获得层时，自动加入，此时不用在重复获得
//	download_apdim();

	int size = DB_View::instance()->cur_view()->scene()->database()->entity_size();
}
void DB_File::delete_ser(std::string detail_name,strings &layer_file_names)
{
	std::string local_file,name ;
	for(int i=0;i<layer_file_names.size();i++){
		name = layer_file_names[i];
		Global::instance()->get_local_file_name(layer_file_names[i],local_file);
		delete_ftp(layer_file_names[i]);
	}

	int size = DB_View::instance()->cur_view()->scene()->database()->entity_size();
}
void DB_File::delete_ftp(std::string detail_name)
{
	//删除服务器上文件
	CInternetSession inet("apcad");
	CFtpConnection* ftp = inet.GetFtpConnection("www.qqft.com","reichina","asd123FGH",21,TRUE);
	BOOL bOK = ftp->Remove(detail_name.c_str());

	ftp->Close();
	inet.Close();
}
void DB_File::download_ftp(std::string detail_name,std::string local_file)
{
	CInternetSession inet("apcad");
	CFtpConnection* ftp = inet.GetFtpConnection("www.qqft.com","reichina","asd123FGH",21,TRUE);
	BOOL bOK = ftp->GetFile(detail_name.c_str(),local_file.c_str());

	ftp->Close();
	inet.Close();
}
void DB_File::upload_ftp(std::string detail_name)
{
	CInternetSession inet("apcad");
	CFtpConnection* ftp = inet.GetFtpConnection("www.qqft.com","reichina","asd123FGH",21,TRUE);
	BOOL bOK = ftp->PutFile(detail_name.c_str(),detail_name.c_str());
	ftp->Close();
	inet.Close();

}



void DB_File::download_apdim()
{
	std::string local_file,name ;
	name = "apdim";
	Global::instance()->get_local_file_name(name,local_file);
	download_ftp(name,local_file);
	open_lua(local_file,DB_View::instance()->cur_view()->scene()->database());

}
void DB_File::upload_apdim()
{

}





