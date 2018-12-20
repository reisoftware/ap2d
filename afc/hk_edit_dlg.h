#ifndef _AFC_HOTKEY_EDIT_DLG_H_
#define _AFC_HOTKEY_EDIT_DLG_H_

#include <string>

namespace edit{

void show_dlg();
BOOL isok();

std::string& kcmd();
std::string& kval();

HWND& hparent();


}//namespace

#endif//FILE

