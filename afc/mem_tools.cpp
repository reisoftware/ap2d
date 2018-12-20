#include "stdafx.h"
#include "mem_tools.h"
#include <stdlib.h>

namespace afc{
namespace mem{

void zero(void * p, int size)
{
	memset(p, 0, size);
}


}//namespace
}//namespace
