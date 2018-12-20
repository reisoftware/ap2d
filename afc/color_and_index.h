#ifndef _AFC_COLOR_AND_INDEX_H_
#define _AFC_COLOR_AND_INDEX_H_

#include "export.h"

namespace afc{

AFCAPI int colorref_to_index(COLORREF col);
AFCAPI COLORREF index_to_colorref(int index);


}//namespace

#endif//FILE
