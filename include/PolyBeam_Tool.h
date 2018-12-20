#ifndef _POLY_BEAM_H_
#define _POLY_BEAM_H_
#include "ModelTool.h"
#include "pt3d.h"
#include "genorm.h"
#include <vector>
class CPlane;
namespace gelib{
	class Scene;
	class Tool_Handle;
	class Select_State;
template <> class Scene_Tool<POLYBEAM_PLATE>:public Tool_Base{
		enum{value = POLYBEAM_PLATE};
		Scene* s_;
		std::vector<CPt3D> pts_;
		double thick_;
		double len_;
		CPlane* plane_;
public:
	void set_plane(CPlane* plane);
	void set_pt(std::vector<CPt3D>& pts);
	void OnTool(Tool_Handle* h,CPt3D& pt1,CPt3D& pt2);
	void draging(Select_State* state,CPoint point);
	void clear_selected(Select_State* state);
	void get_data(CString& name,CString& data);
	void set_scene(gelib::Scene* s);
};
}
#endif