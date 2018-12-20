#ifndef _OBJECT_LINE_DIM_H_
#define _OBJECT_LINE_DIM_H_

#include "export.h"
#include "complex.h"

#include <vector>

namespace dlhml{


class OBJECT_API Line_Dim : public Complex
{


private:
  class Item
  {
    Point s_;                 //  尺寸引出线，起点
  //Float h_;                 //  尺寸引出线，引出点高度
    Float e_;                 //  尺寸引出线，终点高度
  };
private:
  std::vector<Item> item_;  //  尺寸线起始点
  Float dim_degree_;        //  标注线方向
  Float datum_h_;           //  引出点高度基准（重新计算时以此为基准高度）
  int   org_id_;            //  0点尺寸线id
  bool  org_fixed_;         //  0点尺寸线是否使用固定值（h_,e_不参与重新计算）
};
//  注：高度以dim_degree_逆时针旋转90度(+90)方向为正方向

}//namespace

#endif//FILE

