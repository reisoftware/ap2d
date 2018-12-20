#include "StdAfx.h"
#include "ln_dim_block_tools.h"

#include <vector>

#include "dim_block_tools.h"
#include "Ln_Dim_Block.h"

namespace dlhml{


// void re0_block(std::vector<Lead_Dimension_Block*>& bks, double offdeg)
// {
//   if(bks.empty()){
//     return;
//   }
//   double waydeg = offdeg-90;
//   dlhml::std_degree(waydeg);
//   Normal waynor;
//   dlhml::degree_2_normal2d(waydeg, waynor);
//   Point wayst = bks[0]->end();
//   Point wayed = wayst.polarTo(1, waynor);
//   Line ln(wayst, wayed);
//   
//   int count = bks.size();
//   int i=0;
//   for(i=1; i<count; ++i){
//     Point pt = bks[i]->end();
//     pt = ln.perpendicular(pt);
//     bks[i]->end(pt);
//   }
// }

  

// int recal_line_block(Ln_Dim_Block& blk)
// {
//   std::vector<Ln_Dim*>& dims = blk.list_;
// //   re0_block(bks, offdeg);
//   int count = dims.size();
//   int i=0;
//   for(i=1; i<count; ++i){
//     recal_cur<Ln_Dim>(dims, i);
//   }
//   int root = get_floor_count<Ln_Dim>(dims);
//   return root;
//   return 1;
// }
// 

}//namespace
