
#ifndef _GET_DATA_H_
#define _GET_DATA_H_

#include <vector>
#include "Point.h"
#include "Visitor.h"

namespace dlhml
{
  
class Get_Data : public Visitor
{
public:
  Get_Data(std::vector<Point>& dats);
	virtual bool visit_line(Line& line);
  
//public:
//  std::vector<Point>& dats(); 

private:
  std::vector<Point>& dats_;
};

}//namespace

#endif//FILE
