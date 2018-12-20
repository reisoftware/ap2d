#include "stdafx.h"
#include "xls.h"
#include "xls_excel.h"
#include "../afc/trace.h"

namespace aex{
namespace xls{

bool output(afc::xls::Book& xbook, LPCTSTR file)
{
	afc::Trace at;
	try{
		aex::Excel xls;
		if(!xls.is_start()){
			return false;
		}
		if(file){
			xls.add(xbook);
			xls.save_as(file);
		}else{
			xls.save_as(xbook);
		}
	}catch(...){
		at.trace("error: output xls");
		return false;
	}
	return true;
}

}//namespace
}//namespace
