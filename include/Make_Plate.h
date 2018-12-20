#ifndef _MAKE_PLATE_H_
#define _MAKE_PLATE_H_
#include "ModelTool.h"
#include "pt3d.h"
namespace gelib{
	class Scene;
	class Tool_Handle;
	class Select_State;
template <> class Scene_Tool<MAKE_PLATE>:public Tool_Base{
		enum{value = MAKE_PLATE};
		Scene* s_;
		std::vector<CPt3D> pts_;
		double thick_;
public:

	void set_pt(std::vector<CPt3D>& pts);
	void OnTool(Tool_Handle* h,CPt3D& pt1,CPt3D& pt2);
	void draging(Select_State* state,CPoint point);
	void clear_selected(Select_State* state);
	void get_data(CString& name,CString& data);
	void set_scene(gelib::Scene* s);
};
}
#endif