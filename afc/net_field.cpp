#include "net_field.h"
#include "format.h"

namespace afc{
namespace net{

void Field::push_back(int i)
{
	field_.push_back(afc::format(i));
}

void Field::push_back(const char * part)
{
	field_.push_back(part);
}

void Field::pop_back()
{
	field_.pop_back();
}

void Field::clear()
{
	field_.clear();
}

string Field::str() const
{
	int n=field_.size();
	if(n<=0){
		return "";
	}
	afc::string str = field_[0];
	int i=0;
	for(i=1; i<n; ++i){
		if(field_[i].empty()){
			continue;
		}
		str += ":";
		str += field_[i];
	}
	return str;
}



}//namespace
}//namespace
