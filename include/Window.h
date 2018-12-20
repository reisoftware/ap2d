#ifndef _GELIB_WINDOW_H_
#define _GELIB_WINDOW_H_
class InputData;
class CModel;
#define SELNUM_MSG (WM_USER+10)
#define DIS_STR (WM_USER + 11)
#define GET_INPUT (WM_USER +12)
#define GET_MODEL (WM_USER+13)
#define NEW_VIEW (WM_USER+14)
namespace gelib{
	class Model_Geographic;
	AFX_EXT_API void new_wnd(Model_Geographic& geo);
	AFX_EXT_API bool is_show(Model_Geographic& geo);
	AFX_EXT_API void active(Model_Geographic& geo);
	AFX_EXT_API void update_all_views(HWND hwnd);
	AFX_EXT_API void set_modify_flag(BOOL flag = TRUE);
	AFX_EXT_API void send_dis_str(LPCTSTR str);
	AFX_EXT_API InputData* get_input();
	AFX_EXT_API CModel* get_model();

}
#endif
