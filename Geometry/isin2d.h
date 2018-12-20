#ifndef _GEOMETRY_ISIN_H_
#define _GEOMETRY_ISIN_H_


namespace geo{

class Point;
class LLine;
class RLine;
class SLine;

bool isin2d(const Point& pt, const LLine& ln);
bool isin2d(const Point& pt, const RLine& ln);
bool isin2d(const Point& pt, const SLine& ln);

}//namespace


#endif//FILE
