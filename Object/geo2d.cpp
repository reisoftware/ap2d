
#include "StdAfx.h"
#include "geo2d.h"

#include "Point.h"

using namespace std;
using namespace dlhml;

namespace geo2d{

int min_dis(const std::vector<dlhml::Point>& pts, const dlhml::Point& pt)
{
	if(pts.empty()){
		return -1;
	}

	int min_dis_id = 0;

  Float min_dis = pt.distanceto2d(pts[0]);
  Float dis=0;
  int i=0;
  for(i=1; i<pts.size(); ++i){
    dis = pt.distanceto2d(pts[i]);
    if(LessThen(dis,min_dis)){
      min_dis = dis;
      min_dis_id = i;
    }
  }
	
	return min_dis_id;
}


}//namespace




