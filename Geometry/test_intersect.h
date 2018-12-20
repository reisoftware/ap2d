#ifndef _TEST_INTERSECT_H_
#define _TEST_INTERSECT_H_
#include "Point.h"
#include <vector>


typedef std::vector<geo::Point> Points;

const std::string ll_kind = "LLine:";
const std::string sl_kind = "SLine:";
const std::string rl_kind = "RLine:";
const std::string arc_kind = "Arc:";
const std::string circle_kind = "Circle:";

void	test_case(Points &pts_input,Points &crosses,Points &pts);
void test_intersect();

#endif