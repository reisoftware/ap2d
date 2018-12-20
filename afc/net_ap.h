#ifndef _AFC_NET_AP_H_
#define _AFC_NET_AP_H_

#include "export.h"
#include "char.h"
#include "str.h"
#include "net_field.h"
#include "../include/net.h"

namespace afc{
namespace net{

class AFCAPI Ap
{
public:
	// 	string server;
	// 	int port;
	REDIS redis;

	string hkey;
	Field field;

public:
	Ap();
	~Ap();

public:
	void push_back(int i);
	void push_back(cchar * tip);
	void pop_back();
	void clear();

public:
	void del();
};

AFCAPI bool check_redis();
AFCAPI string get_server();


}//namespace
}//namespace

#endif//FILE
