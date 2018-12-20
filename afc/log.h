#ifndef _DEGBUG_OUT_H_
#define _DEGBUG_OUT_H_
#include <string>

namespace afc
{	
AFCAPI void log_start_first();
	
class AFCAPI Log
{
public:
	Log(const std::string &s);
	~Log();
private:
	std::string val_;

};


}//namespace


#endif 
