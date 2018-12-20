#ifndef _NORM_CUT_TOOL_H_
#define _NORM_CUT_TOOL_H_
#include "ModelTool.h"
#include "pt3d.h"
#include "genorm.h"

namespace gelib{
	class Scene;
	class Tool_Handle;
	class Select_State;
template <> class Scene_Tool<NORM_CUT>:public Tool_Base{
		enum{value = NORM_CUT};
		Scene* s_;
		CPt3D pt1_;
		CPt3D pt2_;
		double angle_;
		BOOL up_;

public:
	void set(Scene* s,const CPt3D& pt1,const CPt3D& pt2);
	void OnTool(Tool_Handle* h,CPt3D& pt1,CPt3D& pt2);
	void draging(Select_State* state,CPoint point);
	void clear_selected(Select_State* state);
	void get_data(CString& name,CString& data);
};
}
#endif