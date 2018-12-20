#ifndef _AFC_RPT_RULE_H_
#define _AFC_RPT_RULE_H_

#include <vector>
#include "dat.h"

namespace afc{
namespace rpt{

void pos();
void init();
bool filter(afc::Dat * t);
bool group(afc::Dat * t1, afc::Dat * t2);
bool sort(std::vector<afc::Dat*> * t1, std::vector<afc::Dat*> * t2);
void cell_content();

bool newsheet();

}//namespace
}//namespace

#endif//FILE
