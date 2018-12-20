#include "StdAfx.h"
#include "Flags.h"

namespace dlhml{

Flags::Flags()
:size_(0)
MCT_INIT2("Flags")
{
  init();
}
Flags::Flags(int size)
:size_(size)
MCT_INIT2("Flags")
{
  init();
}

int Flags::size()const
{
  return size_;
}
void Flags::resize(int size)
{
  size_ = size;
  init();
}

bool& Flags::operator[] (int index)
{
  return flags_[index];
}
const bool& Flags::operator[] (int index)const
{
  return flags_[index];
}

const Flags& Flags::operator= (const Flags& rhs)
{
  flags_ = rhs.flags_;
  return *this;
}

void Flags::init()
{
  flags_.resize(size_);
  int i=0;
  for(i=0; i<size_; i++){
    flags_[i] = false;
  }
}

void Flags::reverse(int index)
{
  flags_[index] = !flags_[index];
}
void Flags::setat(int index, bool b)
{
  flags_[index] = b;
}
void Flags::radio(int index)
{
  bool b = flags_[index];
  init();
  flags_[index] = !b;
}


}//namespace



