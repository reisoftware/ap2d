
#include "StdAfx.h"
#include "counter.h"

#include <map>
#include <string>
#include <fstream>
#include <cassert>




#ifdef AFC_MCounter

class MyMap
{
public:
	~MyMap();
public:
	std::map<std::string, int> dat_;
};

//static std::map<std::string, int> mobj_;
static  MyMap dat_;

//#define mobj_ dat_.dat_
static std::map<std::string, int>& mobj_ = dat_.dat_;
 

static void add(std::string name)
{
//#ifdef LEAP_OBJ_LIST
	std::map<std::string,int>::iterator it = NULL;
	it = mobj_.find(name);
	if(it == mobj_.end()){
		mobj_[name] = 1;
	}else{
		mobj_[name]++;
	}
//#endif//LEAP_OBJ_LIST
}

static void print()
{
//#ifdef LEAP_OBJ_LIST
	std::ofstream ofs("mleap.txt");
	if(!ofs.is_open()){
		return;
	}
	ofs<<"Leap Object List\n------------------------\n";
	bool leap = false;
	char buf[512];
	std::map<std::string,int>::iterator it = mobj_.begin();
	for(; it != mobj_.end(); ++it){
		assert(it->second >= 0 && "MCounter::print(), obj'num cann't < 0");
		if(it->second == 0){
			continue;
		}
		sprintf(buf, "%s : %d\n", it->first.c_str(), it->second);
		ofs<<buf;
		leap = true;
	}
	if(!leap){
		ofs<<"None.\n";
	}
	ofs<<"\n\n****************************************\nUsed Object Type List\n------------------------\n";
	it = mobj_.begin();
	for(; it != mobj_.end(); ++it){
		ofs<<it->first;
		ofs<<"\n";
	}
	ofs.close();
//#endif//LEAP_OBJ_LIST
}



MyMap::~MyMap()
{
	print();
	//ICounter::print();
}

MCounter::MCounter(LPCTSTR name)
{
	name_ = name;
	add(name_);
}

MCounter::MCounter(const MCounter& rhs)
{
	name_ = rhs.name_;
	add(name_);
}


MCounter::~MCounter()
{
	std::map<std::string,int>::iterator it = NULL;
	it = mobj_.find(name_);
	assert(it != mobj_.end() && "MCounter::~MCounter(), There be must.");
	mobj_[name_]--;
}

#endif//LEAP_OBJ_LIST
