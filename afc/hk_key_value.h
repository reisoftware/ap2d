#ifndef _AFC_KEY_VALUE_H_
#define _AFC_KEY_VALUE_H_

#include "export.h"
#include <string>

namespace hk{

enum COMBO_KEY {KEY_NULL, KEY_CTRL, KEY_SHIFT, KEY_CTRLSHIFT}; 
	
AFCAPI LPCSTR k_ctrl();
AFCAPI LPCSTR k_shift();
AFCAPI LPCSTR k_ctrl_shift();
AFCAPI LPCSTR tilde();
  
AFCAPI void set_value(std::string value, bool& ctrl, bool& shift, char& hit);
AFCAPI void set_value(std::string value, COMBO_KEY & combo, char& hit);
AFCAPI std::string get_value(bool ctrl, bool shift, char hit);
AFCAPI std::string get_value(COMBO_KEY combo, char hit);


}

#endif//FILE
