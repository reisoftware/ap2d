
#ifndef _THREE_PT_DIM_BLOCK_TOOLS_H_
#define _THREE_PT_DIM_BLOCK_TOOLS_H_

#include "counter.h"

class Scene;
class Three_Pt_Dimension;
class Three_Pt_Dimension_Block;

namespace better{
class Three_Pt_Dim_Block_Tools
{
public:
  Three_Pt_Dim_Block_Tools(const Scene& scene);
//  Three_Pt_Dim_Block_Tools(const Scene& scene, Three_Pt_Dimension * dim);
  Three_Pt_Dim_Block_Tools(const Scene& scene, Three_Pt_Dimension_Block * dim_block);
  ~Three_Pt_Dim_Block_Tools();

public:
//  void set_dim_ptr(Three_Pt_Dimension * dim);
  void set_dim_block_ptr(Three_Pt_Dimension_Block * dim_block);

public:
//  void insert_to_db();
//  void remove_from_db();

private:
  const Scene& scene_;

//  Three_Pt_Dimension * dim_;
  Three_Pt_Dimension_Block * dim_block_;
  
	
private:
	MCT_DEF
};

//namespace
}

#endif