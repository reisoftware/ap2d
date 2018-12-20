
#include <iostream>
#include <vector>

#include "outline.h"
#include "SLine.h"

using namespace std;
using namespace geo;

static void fill_lns(vector<SLine>& lns)
{
  vector<Point> pts;
  pts.push_back(Point(0, 3));
  pts.push_back(Point(3, 3));
  pts.push_back(Point(3, 0));
  pts.push_back(Point(0, 0));

  pts.push_back(Point(1, 2));
  pts.push_back(Point(2, 2));
  pts.push_back(Point(2, 1));
  pts.push_back(Point(1, 1));

  lns.push_back(SLine(pts[0], pts[1]));
  lns.push_back(SLine(pts[1], pts[2]));
  lns.push_back(SLine(pts[2], pts[3]));
  lns.push_back(SLine(pts[3], pts[0]));

  lns.push_back(SLine(pts[4], pts[5]));
  lns.push_back(SLine(pts[5], pts[6]));
  lns.push_back(SLine(pts[6], pts[7]));
  lns.push_back(SLine(pts[7], pts[4]));
  
  lns.push_back(SLine(pts[4], pts[0]));
  lns.push_back(SLine(pts[5], pts[1]));
  lns.push_back(SLine(pts[6], pts[2]));
  lns.push_back(SLine(pts[7], pts[3]));
}

int main(int argc, char * argv[])
{
  vector<SLine> src;
  vector<int> outer;
  vector<int> other;
  fill_lns(src);
  outline(src, outer, other);

  return 0;
}
