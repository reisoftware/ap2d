#ifndef _AFC_DEF_TOOLS_H_
#define _AFC_DEF_TOOLS_H_

#include "mem_tools.h"

// #define afcdef(T, t) T t; afc::mem::zero(&t, sizeof(T))
// #define afcdefs(T, t) afcdef(struct T, t)

#define def_static_inctance(type_name, func_name)	\
type_name& func_name()	\
{	\
	static type_name the;	\
	return the;	\
}



#endif//FILE
