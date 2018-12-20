#include "StdAfx.h"
#include "xls_tools.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "../afc/format.h"

namespace aex{
	
namespace xls{


enum RANGE_ATOMIC {OTHER = 0, ALPHA, NUMBER, COLON};
static init_pos_rule(std::vector<std::vector<int> >& rules)
{
	int rule1[] = {ALPHA, NUMBER, COLON, ALPHA, NUMBER};
	int rule2[] = {ALPHA, COLON, ALPHA};
	int rule3[] = {NUMBER, COLON, NUMBER};
	int rule4[] = {ALPHA, NUMBER};

	rules.clear();
	std::vector<int> vrule1(rule1, rule1+5);
	rules.push_back(vrule1);
	std::vector<int> vrule2(rule2, rule2+3);
	rules.push_back(vrule2);
	std::vector<int> vrule3(rule3, rule3+3);
	rules.push_back(vrule3);
	std::vector<int> vrule4(rule4, rule4+2);
	rules.push_back(vrule4);
}

bool is_regular_pos(LPCTSTR pos1)
{
	std::string pos = pos1;

	std::vector<std::vector<int> > range_rule;
	init_pos_rule(range_rule);
	std::vector<int> range_exp;
	std::string::const_iterator it(pos.begin());
	std::string::const_iterator end(pos.end());
	int state_in = OTHER;
	while (it != end) {
		if (isalpha(*it) && state_in != ALPHA){
			range_exp.push_back(ALPHA);
			state_in = ALPHA;
		}
		else if (isdigit(*it) && state_in != NUMBER){
			range_exp.push_back(NUMBER);
			state_in = NUMBER;
		}
		else if (':' == *it){
			range_exp.push_back(COLON);
			state_in = COLON;
		}
		else if (!isdigit(*it) && !isalpha(*it) && state_in != OTHER){
			range_exp.push_back(OTHER);
			state_in = OTHER;
		}
		it++;
	}
	std::copy(range_exp.begin(), range_exp.end(), std::ostream_iterator<int>(std::cout, " "));
	
	for (int i = 0; i < range_rule.size(); i++) {
		if (range_exp == range_rule[i])
			return true;
	}
	return false;
}


//1-->A,1-->B,27-->AA ...
static afc::string get_regular_x(long x)
{
	assert(x >= 0);
	std::string str;
	const long sys = 26;
	long cur_digit = 0;
	while(x > 0){
		cur_digit = x % sys;
		str += cur_digit - 1 + 'A';
		x = x / sys;
	}
	std::reverse(str.begin(), str.end());
	return str.c_str();
}

static afc::string get_regular_y(long y)
{
	if(y<=0){
		return "";
	}
  char buf[128];
  sprintf(buf, "%d", y);
  afc::string result = buf;
  return result;
}

afc::string get_regular_pos(long x, long y, long w, long h)
{
	assert(x >= 0);
	assert(y >= 0);
	assert(w >= 0);
	assert(h >= 0);
	afc::string str;
	str += get_regular_x(x);
	str += get_regular_y(y);
	str += ":";
	str += get_regular_x(x+w-1);
	str += get_regular_y(y+h-1);
	return str;
}

afc::string get_regular_pos(const afc::xls::Pos& pos)
{
	return get_regular_pos(pos.x, pos.y, pos.w, pos.h);
}


}//namespace

}//namespace
