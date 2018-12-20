
#ifndef TIAN_GA_EXT_H_GEOMETRYARITHMETIC_EXPORTS_BETTER_TIAN_GA_BETTER_2008_03_08_15_30_08
#define TIAN_GA_EXT_H_GEOMETRYARITHMETIC_EXPORTS_BETTER_TIAN_GA_BETTER_2008_03_08_15_30_08

#include "math.h"

namespace TIAN_GA_BETTER{

const double PI_R=3.14159265;
const double FLOAT_PRECISION = 0.001;
const double FLOAT_ZERO = FLOAT_PRECISION;

//==
inline BOOL WINAPI TEquFloat(const double& a, const double& b)
{
	return fabs(a - b) < FLOAT_PRECISION;
}
//>
inline BOOL WINAPI TMoreThen(const double& a, const double& b)
{
	return (a - b) > FLOAT_PRECISION;
}
//<
inline BOOL WINAPI TLessThen(const double& a, const double& b)
{
	return (a - b) < -FLOAT_PRECISION;
}
//>=
inline BOOL WINAPI TMoreEqu(const double& a, const double& b)
{
	return (a - b) > -FLOAT_PRECISION;
}
//<=
inline BOOL WINAPI TLessEqu(const double& a, const double& b)
{
	return (a - b) < FLOAT_PRECISION;
}

//ge
inline bool  EquFloat(const double& a, const double& b)
{
	return fabs(a - b) < FLOAT_PRECISION;
}
inline bool  LessEquFloat(const double& a, const double& b)
{
	return  (b - a) >= -(FLOAT_PRECISION);
}


}

#endif