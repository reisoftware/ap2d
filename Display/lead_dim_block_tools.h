#ifndef _DISPLAY_LEAD_DIM_BLOCK_TOOLS_H_
#define _DISPLAY_LEAD_DIM_BLOCK_TOOLS_H_

#include "display_export.h"

#include <vector>

namespace dlhml{

class Lead_Dimension_Block;

DISPLAY_API int recal_lead_block(std::vector<Lead_Dimension_Block*>& bks, double off_degree);


}//namespace


#endif//FILE

