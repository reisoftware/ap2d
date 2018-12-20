// DB_Blocks.h: interface for the DB_Blocks class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_BLOCKS_H__0848F144_3FB7_4E7E_B52C_C8A48EB18004__INCLUDED_)
#define AFX_DB_BLOCKS_H__0848F144_3FB7_4E7E_B52C_C8A48EB18004__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <string>
#include "display_export.h"


class Block_Info  
{
public:
	Block_Info(){;}
	virtual ~Block_Info(){;}

	std::string name_;
	std::string file_name_;


};


class DISPLAY_API DB_Blocks  
{
public:
	DB_Blocks();
	virtual ~DB_Blocks();

	void set_cur_name(std::string name){cur_blk_name_ = name;}
	std::string get_cur_name(){return cur_blk_name_;}

	static DB_Blocks* instance();
	void close();


	void set_exe_path(std::string exe_path){exe_path_ = exe_path;}
	void get_blk_names(std::vector<std::string> &names);

	const std::vector<Block_Info>& get_db(){return db_;}

	void add();
	void edit(std::string name);
	void del(std::string name);

private:
	std::vector<Block_Info> db_;
	std::string cur_blk_name_;
	std::string exe_path_;
};

#endif // !defined(AFX_DB_BLOCKS_H__0848F144_3FB7_4E7E_B52C_C8A48EB18004__INCLUDED_)
