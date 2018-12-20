#include "stdafx.h"
#include "dat_mgr_c.h"

#include <stdlib.h>
#include <cassert>

namespace afc{

namespace the{

static void destroy(void * p)
{
	Array ** ppary = (Array**)p;
	Array * pary = *ppary;
	if(pary){
		delete pary;
		pary = NULL;
		*ppary = pary;
	}
}

static bool assert_ary(const Array& ary, int index)
{
	if(index < 0){
		return false;
	}
	if(index >= ary.size()){
		return false;
	}
	return true;
}
static bool assert_ary(const Array * pary, int index)
{
	if(!pary){
		return false;
	}
	return assert_ary(*pary, index);
}

}//namespace


Dat_Mgr::Dat_Mgr(int unitsize)
:unitsize_(unitsize)
,dat_(sizeof(Array*))
{
}

Dat_Mgr::~Dat_Mgr()
{
	clear();
}

void Dat_Mgr::init(const Array& src)
{
	clear();
	if(src.size()<=0){
		return;
	}
	Array * pary = new Array(sizeof(Array*));
	int n=src.size();
	int i=0;
	for(i=0; i<n; ++i){
		pary->push_back(src.at(i));
	}
	dat_.push_back(pary);
}

void Dat_Mgr::clear()
{
	dat_.loop(&the::destroy);
	dat_.clear();
}


int Dat_Mgr::group_count()const
{
	return dat_.size();
}

int Dat_Mgr::item_count(int gid)const
{
	assert(the::assert_ary(&dat_, gid));
	Array * pary = (Array*)dat_.at(gid);
	return pary->size();
}

void * Dat_Mgr::get_item(int gid, int iid)const
{
	Array& ary = get_group(gid);
	assert(the::assert_ary(ary, iid));
	void * o = ary.at(iid);
	assert(o);
	return o;
}

void Dat_Mgr::loop(PF_LOOP pf)
{
	int n=dat_.size();
	int i=0;
	for(i=0; i<n; ++i){
		loop_group(i, pf);
	}
}

void Dat_Mgr::loop_group(int gid, PF_LOOP pf)
{
	Array& ary = get_group(gid);
	int n=ary.size();
	int i=0;
	for(i=0; i<n; ++i){
		pf(ary.at(i));
	}
}


//////////////////////////// << private >> /////////////////////////////
// Array& Dat_Mgr::get_group(int gid)
// {
// 	assert(the::assert_ary(dat_, gid));
// 	Array * pary = (Array*)(dat_.at(gid));
// 	assert(pary);
// 	return *pary;
// } 

Array& Dat_Mgr::get_group(int gid)const
{
	assert(the::assert_ary(dat_, gid));
	Array * pary = (Array*)(dat_.at(gid));
	assert(pary);
	return *pary;
}


}//namespace