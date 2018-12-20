#ifndef _APBUDGET_DXF_SAVE_H_
#define _APBUDGET_DXF_SAVE_H_



#include <string>

namespace dlhml{

const std::string g_lock_layer_name = "LOCK_LAYER";

#define layer_white_hidden "white_hidden"
#define layer_white_center "white_center"
#define layer_white_solid "white_solid"
#define layer_yellow_solid "yellow_solid"
#define layer_shuise_solid "shuise_solid"
#define layer_green_solid "green_solid"
#define layer_red_solid "red_solid"


class Database;

bool save_dxf(std::string file, dlhml::Database& db);

}//namespace
#endif//FILE
