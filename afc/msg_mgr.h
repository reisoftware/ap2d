#ifndef _AFC_MSG_MGR_H_
#define _AFC_MSG_MGR_H_

namespace afc{

inline void msg_answer()
{
  MSG msg;
  if(GetMessage(&msg, NULL, 0, 0)){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

}//namespace

#endif//FILE
