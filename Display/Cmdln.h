#ifndef _CMDLN_H_
#define _CMDLN_H_

#include <string>
class Point;

namespace dlhml{
bool cmdln(const Point& base, const Point& normal, std::string input, Point & target);

bool absolute_coordinates(const Point& base, std::string input, int pos, Point & target);
bool distance(const Point& base, std::string input, const Point& normal, Point & target);
bool relative_coordinates(const Point& base, std::string input, int pos, Point & target);
bool polar_coordinates(const Point& base, std::string input, int pos, Point & target);
bool distance_normal(const Point& base, std::string input, int pos, Point & target);

bool chk_absolute_coordinates(std::string str);
bool chk_distance(std::string str);
bool chk_relative_coordinates(std::string str);
bool chk_polar_coordinates(std::string str);
bool chk_distance_normal(std::string str);
}


#endif