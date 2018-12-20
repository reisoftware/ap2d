#ifndef _AFC_RPT_H_
#define _AFC_RPT_H_

#include "export.h"
#include "rpt_fptr.h"
#include "rpt_book.h"
#include "xls_book.h"

namespace afc{

class AFCAPI Report
{
public:
	Report();
	//Report(LPCTSTR book_file);

public:
	void output(xls::Book& xbook, LPCTSTR file, afc::PF_ADD_SYMBOL pf);

private:
	void set_book(LPCTSTR file);
	void set_callback(afc::PF_ADD_SYMBOL pf);
	void output(xls::Book& xbook);

//	rpt::Cell_Mgr cm_;
	
private:
	rpt::Book book_;
};

}//namespace

#endif//FILE
