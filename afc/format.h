#ifndef _AFC_FORMAT_H_
#define _AFC_FORMAT_H_

#include "export.h"
#include "str.h"

namespace afc{


// 四舍五入
AFCAPI int round_off(double d);
// 任意精度舍入
AFCAPI double round(double d, double precision);
// 格式化浮点数
// precision  :精度（舍入模数）
// bit        :显示小数位数
// addends    :显示小数点后结尾的0
AFCAPI string format(double d, double precision, int bit, bool addends);
AFCAPI string format(double d, int bit = 6, bool addends = true);
AFCAPI string format(int i);



}//namespace

#endif//FILE
