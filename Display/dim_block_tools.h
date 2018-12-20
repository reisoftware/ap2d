#ifndef _DIM_BLOCK_TOOLS_H_
#define _DIM_BLOCK_TOOLS_H_



namespace dlhml{

  
// template<class T>
// bool is_interfere(T * t1, T * t2)
// {
//   if(t1 == t2){
//     return false;
//   }
//   
//   Rect box1, box2;
//   box1 = t1->offset_box();
//   box2 = t2->offset_box();
//   
//   if(box1.intersect(box2)){
//     return true;
//   }
//   return false;
// }
// 
// template<class T>
// void recal_cur(std::vector<T*>& ts, int cur)
// {
//   int count = ts.size();
//   int i=0;
//   for(i=0; i<count; ++i){
//     if(i==cur){
//       continue;
//     }
//     ////若干涉，则[cur]干涉位置++
//     if(is_interfere(ts[i], ts[cur])){
//       ts[cur]->offset_pp();//++
//       i = -1;
//     }
//   }
// }
// 
// ////获得楼最高层数（楼层+跃层）
// template<class T>
// int get_floor_count(std::vector<T*>& ts)
// {
//   int count = ts.size();
//   int i=0;
//   int fcount = 0, max_fcount = 0;
//   for(i=0; i<count; ++i){
//     fcount = ts[i]->floor_count();
//     if(max_fcount < fcount){
//       max_fcount = fcount;
//     }
//   }
//   return max_fcount;
// }
// 



}

#endif//FILE
