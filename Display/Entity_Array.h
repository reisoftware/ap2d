#ifndef _DISPLAY_ENTITY_ARRAY_H_
#define _DISPLAY_ENTITY_ARRAY_H_

#include "counter.h"

namespace dlhml
{
	
	struct Entity_Array
	{
		int row_num;
		int col_num;
		double row_dis;
		double col_dis;
		double degree;
		Entity_Array():row_num(0),col_num(0),row_dis(0),col_dis(0),degree(0)MCT_INIT2("Entity_Array"){}
		
	private:
		MCT_DEF
	};

}//namespace

#endif//FILE
