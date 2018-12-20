#ifndef _AFC_RPT_FPTR_H_
#define _AFC_RPT_FPTR_H_

#include "dat.h"
#include "call_tcc.h"
#include <vector>

namespace afc{
namespace rpt{

typedef void(*PF_INIT)();
typedef bool(*PF_FILTER)(afc::Dat*);
typedef bool(*PF_GROUP)(afc::Dat*, afc::Dat*);
typedef bool(*PF_SORT)(std::vector<afc::Dat*>*, std::vector<afc::Dat*>*);
typedef void(*PF_CELL_CONTENT)();

class PF
{
public:
// 	PF_INIT init;
// 	PF_FILTER filter;
// 	PF_GROUP group;
// 	PF_SORT sort;
// 	PF_CELL_CONTENT cell_content;

public:
	PF_ADD_SYMBOL add_api;

public:
	PF();
};

// PF& pf();

}//namespace
}//namespace

#endif//FILE
