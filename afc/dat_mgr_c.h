#ifndef _AFC_DAT_MGR_C_H_
#define _AFC_DAT_MGR_C_H_

#include "export.h"
#include "ary.h"

namespace afc{


class AFCAPI Dat_Mgr
{
	typedef Array Ary2d;
	typedef void(*PF_LOOP)(void*);
public:
	Dat_Mgr(int unitsize);
	~Dat_Mgr();

public:
	void init(const Array& src);
	void filter();
	void group();
	void sort();
	void clear();

public:
	int group_count()const;
	int item_count(int gid)const;
	void * get_item(int gid, int iid)const;

public:
	void loop(PF_LOOP pf);
	void loop_group(int gid, PF_LOOP pf);

private:
	//Array&  get_group(int gid);
	Array&  get_group(int gid)const;

private:
	int unitsize_;
	Ary2d dat_;
};

}//namespace

#endif//FILE
