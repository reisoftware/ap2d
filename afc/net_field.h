#ifndef _AFC_NET_FIELD_H_
#define _AFC_NET_FIELD_H_


#include "export.h"
#include "str.h"
#include <vector>

namespace afc{
namespace net{

class AFCAPI Field
{
public:
	void push_back(int i);
	void push_back(const char * tip);
	void pop_back();
	void clear();

public:
	string str() const;

private:
	std::vector<afc::string> field_;

};



}//namespace
}//namespace



#endif//FILE
