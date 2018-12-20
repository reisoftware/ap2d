#ifndef _PRINT_H_
#define _PRINT_H_
#include <vector>

namespace geo
{
class Point;
class Arc;
class Circle;
class RLine;
class LLine;
class SLine;
class Normal;
}

void print_space();
void print_point(const geo::Point &pt);
void print_nor(const geo::Normal &nor);
void print_points(const std::vector<geo::Point> &pts);
void print_head();

template <class T>
void print_line(T &t)
{
	std::string kind = t.get();
	std::cout <<kind.c_str()<<"\n";
	print_point(t.pt1);
	print_point(t.pt2);	

}

void print_lline(const geo::LLine &lline);
void print_sline(const geo::SLine &sline);
void print_rline(const geo::RLine &rline);
void print_arc(const geo::Arc &arc);
void print_circle(const geo::Circle &circle);

void print_test_start();
bool print_test_end(std::string name);
void print_fun_info(std::string name);



#endif