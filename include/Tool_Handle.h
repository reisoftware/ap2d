#ifndef _TOOL_HANDLE_H_
#define _TOOL_HANDLE_H_
#include "ModelTool.h"
#include "Round_Plate_Tool.h"
#include "Bolt_Plate_Tool.h"
#include "PolyBeam_Tool.h"
#include "Norm_Cut_Tool.h"

#include "Make_Plate.h"

#include "geptr.h"
#include "pt3d.h"
#include "resource.h"
#include "CJoint.h"
#include "../include/MemType.h"
namespace gelib{
  class Slect_State;
  class AFX_EXT_CLASS Tool_Handle
  {
    GEXY::CPtr<Tool_Base> tool_;
    vector<int> indexs_;
		CMemType memType;
  public:
    Tool_Handle();
    void handle();

    void get_data(CString name,CString data);

		void handle_mem_type();
		void handle_add_cut();
		void handle_divided();
		void handle_set_opt();

    void handle_front_view();
    void handle_back_view();
    void handle_left_view();
    void handle_right_view();
    void handle_center_view();

    void handle_unround();
    void handle_bolt_plate();
    void handle_norm_cut();
    void handle_round_plate();

    void handle_none();
    void handle_add_col();
    void handle_set_cen();
    void handle_add_beam();
    void handle_add_brace();
    void handle_del_node();
    void handle_move_tool();
    void handle_move_nd();
    void handle_copy_tool();
    void handle_dis_tool();
    void handle_cut_plane();
    void handle_add_axis();
    void handle_sel_plane();
    void handle_cut_section();

    void handle_beam_axis();
    void handle_input_clip_dis();
    void handle_2D_3D_switch();
    void handle_delete();
    void handle_select_plate();
    void handle_edit_plate();

    void handle_make_plate();
    void handle_set_axis_plane();
    void handle_mirror();
    void handle_add_cutplane_2_modle(const char* name);
    void handle_angle();
    void handle_member_cut();

    void handle_gj_jnt();
    void handle_custom_jnt();
    void handle_jb_jnt();
    void handle_box_jnt();
    void handle_base_jnt();
    void handle_jblib();
    void handle_gjlib();
    void handle_chkweld();
    void handle_select_member();
    void handle_jnt_dsn();
    void handle_assign_jnt();

    void parallel_pt();
    void angle_pt();
    void extent_pt();
    void intersect_pt();
    void perpendicular_pt();
    void divided_pt();
    void handle_near_point();	
    void handle_add_bolts();
    void handle_polybeam();
		void handle_script_test(LPCTSTR filename);

    BOOL handle_input();

    void draging_tool(Select_State* select_state,CPoint point);

    void OnTool(Scene_Tool<NONE>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ADD_COL>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<SET_CEN>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ADD_BEAM>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ADD_BRACE>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<DEL_NODE>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<MOVE_TOOL>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<MOVEND_TOOL>& tool,CPt3D& pt1,CPt3D& pt2);

    void OnTool(Scene_Tool<COPY_TOOL>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<DIS_TOOL>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<CUT_PLANE>& tool,CPt3D& pt1,CPt3D& pt2);

    void OnTool(Scene_Tool<CUT_SECTION>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<MEMBER_CUT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ADD_AXIS>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<EDIT_PLATE>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<MAKE_PLATE>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<POLYBEAM_PLATE>& tool,CPt3D& pt1,CPt3D& pt2);

    void OnTool(Scene_Tool<MIRROR_TOOL>& tool,CPt3D& pt1,CPt3D& pt2);

    void OnTool(Scene_Tool<PARALLEL_PT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ANGLE_PT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<EXTENT_PT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<INTERSECT_PT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<PERPENDICULAR_PT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<DIVIDED_PT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<NEARPOINT_TOOL>&tool,CPt3D& pt1,CPt3D& pt2);

    void OnTool(Scene_Tool<ANGLE_TOOL>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<CHK_WELD>& tool,CPt3D& pt1,CPt3D& pt2);

    void OnTool(Scene_Tool<JBLIB_JNT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<CUSTOM_JNT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ASSIGNJNT_TOOL>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ID_GJLIB>& tool,CPt3D& pt1,CPt3D& pt2);

    void OnTool(Scene_Tool<UNROUND_PLATE>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<BOLT_PLATE>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<NORM_CUT>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ROUND_PLATE>& tool,CPt3D& pt1,CPt3D& pt2);
    void OnTool(Scene_Tool<ADD_BOLTS>& tool,CPt3D& pt1,CPt3D& pt2);
	
  private:
    void cut_plane(CPt3D pt1,CPt3D pt2);
  };
}
#endif
