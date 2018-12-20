#ifndef _REI_GLOBAL_H
#define	_REI_GLOBAL_H

#pragma warning( disable: 4786 4788)

#include <gl\gl.h>
#include <gl\glu.h>
#include <GL\glaux.h>
#include <math.h>

#define PI 3.14159265

namespace GEXY{
const double FLOAT_PRECISION = 0.001;
inline BOOL WINAPI EquFloat(const double& a, const double& b)
{
	BOOL result = (a - b) < FLOAT_PRECISION && (b - a) < FLOAT_PRECISION;
	return result;
}
}

#endif