
#include "StdAfx.h"
#include "Get_Data.h"

#include "Line.h"

namespace dlhml
{

Get_Data::Get_Data(std::vector<Point>& dats)
:dats_(dats)
{
}

//std::vector<Point>& Get_Data::dats()
//{
//  return dats_;
//} 


bool Get_Data::visit_line(Line& line)
{
  dats_.push_back(line.start());
  dats_.push_back(line.end  ());

  return true;
}

}//namespace

