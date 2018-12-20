#ifndef _DISPLAT_DXF_O_H_
#define _DISPLAT_DXF_O_H_

#include "display_export.h"

#include <string>

namespace dlhml{



class Database;

DISPLAY_API bool output_dxf(std::string file, dlhml::Database& db);

}//namespace
#endif//FILE
