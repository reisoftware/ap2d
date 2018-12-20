#ifndef _AFC_TCC_DEF_H_
#define _AFC_TCC_DEF_H_

#include <stdlib.h>

#define apzero(t) memset(&t, 0, sizeof(t))
#define apdef(T, t) T t; apzero(t)
#define apdefs(T, t) apdef(struct T, t)


#endif//FILE
