#ifndef _READ_H_
#define _READ_H_
namespace geo
{
class Point;
class Arc;
class Circle;
class RLine;
class LLine;
class SLine;
}

void read_pt(geo::Point & pt);
void read_point(geo::Point &pt);
template <class T>
void read_line(T &t);
void read_lline(geo::LLine &lline);
void read_sline(geo::SLine &sline);
void read_rline(geo::RLine &rline);
void read_arc(geo::Arc &arc);
void read_circle(geo::Circle &circle);


#endif
