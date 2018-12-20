// DB_File_Date.cpp: implementation of the DB_File_Date class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "DB_File_Date.h"

#include <fstream>
#include "Mgr_File.h"
#include "Global.h"
#include "Mgr_Convert.h"
#include "str_tools.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_File_Date::DB_File_Date()
{

}

DB_File_Date::~DB_File_Date()
{

}
void DB_File_Date::save()
{
	std::string data_file = Global::instance()->project_info().dir_path+"file_time.txt";
	std::ofstream ofs(data_file.c_str());
	if(!ofs.is_open()){
		return;
	}

	for(int i=0;i<items_.size();i++){
		ofs << items_[i].name_.c_str() <<"			"<<items_[i].date_<<"\n";
	}
	ofs.close();
	
}
void DB_File_Date::read()
{
	std::string f = Global::instance()->project_info().dir_path+"file_time.txt";
	std::fstream file(f.c_str());
	if(!file.is_open())
		return ;
	items_.clear();
	char name[1000] = "0";
	char date[1000] = "0";
	ApFile_Date item;
	while(strcmp(name, "") != 0 ){
		file >> name >> date;
		item.name_ = name;
		item.date_ = date;
		items_.push_back(item);
	}
	file.close();
	int size = items_.size();

}
void DB_File_Date::save_std()
{
	CString s,t1,t2;	
	std::string f = Global::instance()->project_info().dir_path+"file_time.txt";
  CStdioFile file_txt;
  if(file_txt.Open(f.c_str(), CFile::modeCreate | CFile::modeWrite)){
    for(int i=0; i<items_.size(); i++){
			t1 = items_[i].name_.c_str();
			t2 = items_[i].date_.c_str();
			s = t1+"&"+t2;
      file_txt.WriteString(s + "\n");
    }
    file_txt.Close();
  }
	
}
void DB_File_Date::read_std()
{
	items_.clear();
	CString s;	
	std::string f = Global::instance()->project_info().dir_path+"file_time.txt";
	CStdioFile file_txt(f.c_str(),CFile::modeRead);
  std::vector<std::string> vals;
	ApFile_Date item;
	while(file_txt.ReadString(s)){
		vals.clear();
		afc::split_string(vals,s.GetBuffer(0),"&");
		if(vals.size() !=2)
			continue;
		item.name_ = vals[0];
		item.date_ = vals[1];
		items_.push_back(item);
	}
	file_txt.Close();	
	
}


int DB_File_Date::find_name(std::string name)
{
	for(int i=0;i<items_.size();i++){
		if(strcmp(items_[i].name_.c_str(),name.c_str()) == 0)
			return i;		
	}
	return -1;
}
void DB_File_Date::edit(std::string file)
{
	std::string path_name = Global::instance()->project_info().dir_path+file;
	int pos = find_name(path_name);
	if(pos == -1)
		return ;
	std::string new_date = get_file_change_time(path_name);
	items_[pos].date_ = new_date;
}

bool DB_File_Date::change(std::string file)
{
	std::string path_name = Global::instance()->project_info().dir_path+file;
	std::string new_date = get_file_change_time(path_name);
	int size = items_.size();

	int pos = find_name(path_name);
	if(pos != -1){
		if(strcmp(items_[pos].date_.c_str(),new_date.c_str()) == 0)
			return false;
		else
			return true;
	}

	return true;
/*

	ApFile_Dates::iterator iter = find(path_name);
	if(iter != items_.end()){
		if(strcmp(iter->date_.c_str(),new_date.c_str()) == 0)
			return false;
		else
			return true;
	}

	return true;
*/
}
void DB_File_Date::push(const strings &files)
{
	items_.clear();
	ApFile_Date item;
	std::string path_name;
	for(int i=0;i<files.size();i++) {
		path_name = Global::instance()->project_info().dir_path+files[i];
		item.date_ = get_file_change_time(path_name);
		item.name_ = path_name;
		items_.push_back(item);
	}
}

void DB_File_Date::del()
{
	std::string f = Global::instance()->project_info().dir_path+"file_time.txt";
	items_.clear();
	DeleteFile(f.c_str());

}