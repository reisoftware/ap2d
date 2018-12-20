#include "stdafx.h"
#include "test.h"

namespace aex{

void Test::test()
{
  LPTSTR msg;
#ifdef _DEBUG
  msg = "_D: test";
#else
  msg = "_R: test";
#endif

  AfxMessageBox(msg);

}

}//namespace
