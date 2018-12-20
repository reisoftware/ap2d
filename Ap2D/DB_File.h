// DB_File.h: interface for the DB_File class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_FILE_H__780808CF_0EB5_4DB0_86D3_20B1D39CEB82__INCLUDED_)
#define AFX_DB_FILE_H__780808CF_0EB5_4DB0_86D3_20B1D39CEB82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include "DB_Templete.h"


class ApFile 
{
public:
	ApFile(){}
	virtual ~ApFile(){;}
	bool operator==(const ApFile& rhs)
	{
		if(strcmp(name_.c_str(),rhs.name_.c_str()) == 0 )
			return true;
		return false;
	}	
	void set_from_str(char *in);
	void get_str(char *out);

	std::string name_;
	std::string hash_val_;


};
typedef std::vector<ApFile> ApFiles;


class DB_File  : public DB_Templete<ApFiles,ApFile>  
{
public:
	DB_File();
	virtual ~DB_File();

	void upload(std::string key);
	void download(std::string key);

	void upload_ser();
	void download_ser(std::string detail_name,strings &layer_file_names);
	void delete_ser(std::string detail_name,strings &layer_file_names);

	void download_ftp(std::string detail_name,std::string local_file);
	void upload_ftp(std::string detail_name);
	void delete_ftp(std::string detail_name);


	void download_apdim();
	void upload_apdim();

private:
	void create_item(char *in);

};

#endif // !defined(AFX_DB_FILE_H__780808CF_0EB5_4DB0_86D3_20B1D39CEB82__INCLUDED_)
