// DB_Blocks.cpp: implementation of the DB_Blocks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB_Blocks.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Blocks::DB_Blocks()
{

}

DB_Blocks::~DB_Blocks()
{

}
DB_Blocks* DB_Blocks::instance()
{	
	static DB_Blocks g;
	return &g;
}
void DB_Blocks::add()
{
	Block_Info info;
	info.name_ = cur_blk_name_;
	info.file_name_ = cur_blk_name_+".blk";
	db_.push_back(info);

}
void DB_Blocks::edit(std::string name)
{

}
void DB_Blocks::del(std::string name)
{

}


void DB_Blocks::get_blk_names(std::vector<std::string> &names)
{
		std::string blk_dir =exe_path_+"blk\\";


}








