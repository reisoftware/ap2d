#include "net_ap.h"
#include "dir.h"

namespace afc{
namespace net{

static const int _0 = 0;
static const int _1 = 1;
static const int _2 = 2;
static const int _3 = 3;
static const int _4 = 4;
static const int _5 = 5;
static const int _6 = 6;
static const int _7 = 7;
static const int _8 = 8;
static const int _9 = 9;
static const char DOT = '.';

string get_server()
{
//	return "192.168.5.10";
	string path = afc::dir::exe_path().c_str();
	string file = path + "qqft";
	FILE * p = fopen(file, "r");
	if(p){
		fclose(p);
		return "www.qqft.com";
	}
	
	file = path + "5.10";
	p = fopen(file, "r");
	if(p){
		fclose(p);
		return "192.168.5.10";
	}

	file = path + "2.229";
	p = fopen(file, "r");
	if(p){
		fclose(p);
		return "192.168.2.229";
	}

	return "192.168.5.229";
// 	char buf[64];
// 	////////////// 2 1 0 . 8 3 . 2 0 3 . 1 1 4
// 	sprintf(buf, "%d%d%d%c%d%d%c%d%d%d%c%d%d%d", _2,_1,_0, DOT, _8,_3, DOT, _2,_0,_3, DOT, _1,_1,_4);
// 	////////////// 1 9 2 . 1 6 8 . 1 . 1 0
// //	sprintf(buf, "%d%d%d%c%d%d%d%c%d%c%d%d", _1,_9,_2, DOT, _1, _6,_8, DOT, _1, DOT, _1,_0);
// 	////////////// 1 2 7 . 0 . 0 . 1
// // 	sprintf(buf, "%d%d%d%c%d%c%d%c%d", _1,_2,_7, DOT, _0, DOT, _0, DOT, _1);
// 	return buf;
}

static int get_port()
{
	char buf[64];
	sprintf(buf, "%d%d%d%d", _6,_3,_7,_9);
	return atoi(buf);
}


bool check_redis()
{
	Ap ap;	
	if(!ap.redis){
		return false;
	}
	return true;
}


Ap::Ap()
{
	// 	server = get_server();
	// 	port = get_port();
	init_net();
	redis = get_redis(get_server(), 50000);
}

Ap::~Ap()
{
	if(redis) free_redis(redis);
	close_net();
}

void Ap::push_back(int i)
{
	field.push_back(i);
}

void Ap::push_back(cchar * tip)
{
	field.push_back(tip);
}

void Ap::pop_back()
{
	field.pop_back();
}

void Ap::clear()
{
	field.clear();
}

void Ap::del()
{
	redis_del(redis, hkey);
}


}//namespace
}//namespace
