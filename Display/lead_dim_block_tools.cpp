#include "StdAfx.h"
#include "lead_dim_block_tools.h"

#include "../object/Lead_Dimension_Block.h"
#include "../object/Normal.h"
#include "../object/Line.h"
#include "../object/Point.h"

#include "dim_block_tools.h"

namespace dlhml{

static bool is_interfere(Lead_Dimension_Block * bk1, Lead_Dimension_Block * bk2)
{
  if(bk1 == bk2){
    return false;
  }

  Rect box1, box2;
  box1 = bk1->offset_box();
  box2 = bk2->offset_box();

  if(box1.intersect(box2)){
    return true;
  }
  return false;
}
  
static void recal_cur(std::vector<Lead_Dimension_Block*>& bks, int cur)
{
  int count = bks.size();
  int i=0;
  for(i=0; i<count; ++i){
    if(i==cur){
      continue;
    }
    ////若干涉，则[cur]干涉位置++
    if(is_interfere(bks[i], bks[cur])){
      bks[cur]->offset_pp();//++
      i = -1;
    }
  }
}

////获得楼最高层数（楼层+跃层）
static int get_floor_count(std::vector<Lead_Dimension_Block*>& bks)
{
  int count = bks.size();
  int i=0;
  int fcount = 0, max_fcount = 0;
  for(i=0; i<count; ++i){
    fcount = bks[i]->floor_count();
    if(max_fcount < fcount){
      max_fcount = fcount;
    }
  }
  return max_fcount;
}

void re0_block(std::vector<Lead_Dimension_Block*>& bks, double offdeg)
{
  if(bks.empty()){
    return;
  }
  double waydeg = offdeg-90;
  dlhml::std_degree(waydeg);
  Normal waynor;
  dlhml::degree_2_normal2d(waydeg, waynor);
  Point wayst = bks[0]->end();
  Point wayed = wayst.polarTo(1, waynor);
  Line ln(wayst, wayed);

  int count = bks.size();
  int i=0;
  for(i=1; i<count; ++i){
    Point pt = bks[i]->end();
    pt = ln.perpendicular(pt);
    bks[i]->end(pt);
  }
}

int recal_lead_block(std::vector<Lead_Dimension_Block*>& bks, double offdeg)
{
  if(bks.empty()){
    return 0;
  }
  //double offdeg = bks.front()->offset_degree();
  re0_block(bks, offdeg);
  bks[0]->offset_degree(offdeg);
  int count = bks.size();
  int i=0;
  for(i=1; i<count; ++i){
    bks[i]->offset_degree(offdeg);
    recal_cur(bks, i);
  }
  int root = get_floor_count(bks);
  return root;
//   return 1;
}
  
  
  
}//namespace

