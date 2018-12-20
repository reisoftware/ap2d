#include "StdAfx.h"
#include "format.h"

#include <algorithm>
#include <cassert>
#include <math.h>
#include <string>

#include <stdio.h>

namespace afc{

static const int BIT_SIZE = 128;

static int round_off_positive(double d)
{
  assert(d >= 0);
  d += 0.5;
  int n = (int)d;
  return n;
}

int round_off(double d)
{
  if(d<0){
    return -round_off_positive(-d);
  }
  return round_off_positive(d);
}

double round(double d, double precision)
{
  if(precision==0){
    return d;
  }
  d /= precision;
  d  = round_off(d);
  d *= precision;
  return d;
}

static std::string format_type(int bit)
{
  char buf[BIT_SIZE];
	std::string type = "%";
  sprintf(buf, ".%df", bit);
  type += buf;
  return type;
}

static void invalid_bit(std::string& decimal, bool addends)
{
  if(addends){
    return;
  }
  std::string::size_type pos = decimal.find(".");
	//std::string::size_type pos = std::find(decimal.begin(), decimal.end(), ".");
  if(pos == std::string::npos){
    return;
  }
  pos = decimal.find_last_not_of('0');
  if(pos == std::string::npos){
    return;
  }
  decimal = decimal.substr(0, pos+1);
  if(decimal[decimal.size()-1] == '.'){
    decimal.erase(decimal.size()-1);
  }
}

string format(double d, double precision, int bit, bool addends)
{
  d = round(d, precision);
  std::string str = format(d, bit, addends);
  return str.c_str();
}

string format(double d, int bit, bool addends)
{
  char buf[BIT_SIZE];
  std::string type = format_type(bit);
  sprintf(buf, type.c_str(), d);
  std::string str = buf;
  invalid_bit(str, addends);
  return str.c_str();
}

string format(int i)
{
  char buf[BIT_SIZE];
  sprintf(buf, "%d", i);
  std::string result = buf;
  return result.c_str();
}


}//namespace

