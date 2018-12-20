#include "stdafx.h"
#include "Log.h"
#include <string>
#include <fstream>
#include "dir.h"
#include "../afc/date_time.h"
namespace afc
{

static std::ofstream g_o;
#define START  "  ST!\n"
#define END  "  Ed!\n"
#define seg_start  "**********"
#define seg_space  " "
#define seg_end  "*****************************************\n"
int g_tab=0;
static void log_start()
{
	std::string log_name = dir::exe_path()+"\\log.txt";
	g_o.open(log_name.c_str(),std::ios::app|std::ios::in|std::ios::out);
	if(!g_o.is_open()){
		return;
	}	

}
static void log_close()
{
	g_o.close();

}

void log_start_first()
{
  afc::Date_Time dt;
	log_start();
	g_o <<seg_start<< dt.local_date() <<seg_space<< dt.local_time(false)<<seg_end;
	log_close();
}


static void write_tat(std::ofstream &g_o,int tab_num)
{
	while (0 < tab_num--)
		g_o << "\t";
	
}
Log::Log(const std::string &s):val_(s)
{
	log_start();
	write_tat(g_o,g_tab++);	
	g_o << val_ << START;
	log_close();
}
Log::~Log()
{
	log_start();
	write_tat(g_o,--g_tab);
	g_o << val_ << END;
	log_close();

}




}