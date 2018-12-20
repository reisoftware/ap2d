
#ifndef _DISPLAY_EXPORT_H_DLHML_
#define _DISPLAY_EXPORT_H_DLHML_

#ifdef DISPLAY_EXPORTS
#define DISPLAY_API __declspec(dllexport)
#else
#define DISPLAY_API __declspec(dllimport)
#endif

//#define USE_GL

//#define USE_IMAGE

#include "counter.h"



#endif //_DISPLAY_EXPORT_H_DLHML_
