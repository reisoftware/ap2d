#include "stdafx.h"
#include "xls_sheet.h"
#include "format.h"
#include <cassert>

namespace afc{
namespace xls{

Sheet::Sheet()
:id(0)
{
}

afc::string Sheet::name()const
{
	afc::string str = prefix;
	str += afc::format(id);
	return str;
}

void Sheet::clear()
{
	id = 0;
	cells.clear();
	borders.clear();
	ws.clear();
	hs.clear();
}

void set_size(std::vector<double>& s, int xid, double size)
{
	assert(xid>=1);
	if(size <= 0.1){
		return;
	}
	int n=s.size();
	int id = xid-1;
	if(id < n){
		s[id] = size;
		return;
	}
	int i=0;
	for(i=n; i<id+1; i++){
		s.push_back(size);
	} 

// 	int n=s.size();
// 	int i=0;
// 	for(i=0; i<n; ++i){
// 		if(s[i].first == first){
// 			return;
// 		}
// 	}
// 	pair p;
// 	p.first = first;
// 	p.second = second;
// 	s.push_back(p);
}

double get_size(const std::vector<double>& s, int xid)
{
	assert(xid >= 0);
	if(xid == 0){
		return 0;
	}
	int n=s.size();
	if(n<=0){
		return 0;
	}
	int id = xid - 1;
	if(id<n){
		return s[id];
	}
	return s.back();
}

double get_size_sum(const std::vector<double>& s, int xid)
{
	double sum = 0;
	int n=xid;
	int i=0;
	for(i=0; i<=n; ++i){
		sum += get_size(s, i);
	}
	return sum;
}


}//namespace
}//namespace
