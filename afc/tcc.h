
#ifndef _AFC_TCC_H_
#define _AFC_TCC_H_

#include "export.h"
#include "str.h"

struct TCCState;

namespace afc{


class AFCAPI Tcc
{
	struct Error
	{
		afc::string msg_;
	};

public:
	Tcc();
	~Tcc();

private:
	Tcc(const Tcc& t){}
	operator = (const Tcc& t){}

private:
	void init();

public:
	void create(LPCTSTR path);
	void add_symbol(LPCTSTR fname, void * fptr);
	void add_file(LPCTSTR file);
	void add_code(LPCTSTR code);
	void relocate();
	void * get_symbol(LPCTSTR fname, bool thrownull=true);
	void destroy();

private:
	void exit();

public:
	static void exit(LPCTSTR msg);

private:
  TCCState * s_;
  void * m_;

private:
	afc::string script_;
	Error error_;
};

}//namespace



/////////////////////// << tcc exit >> ///////////////////////
#define rpt_tcc_exit(expression, tip)	\
	if(expression){	\
		afc::Tcc::exit(tip);	\
	}

#define rpt_tcc_ptr(ptr, tip)	\
	if(!ptr){	\
		afc::Tcc::exit(tip);	\
	}

#define rpt_tcc_ary(ary, tip)	\
	if(ary.empty()){	\
		afc::Tcc::exit(tip);	\
	}

#define rpt_tcc_aryptr(aryptr, tip)	\
	if(!aryptr){	\
		afc::Tcc::exit(tip);	\
	}	\
	if(aryptr->empty()){	\
		afc::Tcc::exit(tip);	\
	}

#endif//FILE

