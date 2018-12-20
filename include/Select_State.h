#ifndef _SELECT_STATE_H_
#define _SELECT_STATE_H_
#include <vector>
#include "pt3d.h"
#include "ModelTool.h"
#define SELNUM_MSG (WM_USER+10)
class CGePlate;
namespace gelib{
	class AFX_EXT_CLASS Select_State{
			DWORD type_;
			int needed_;
			BOOL drag_drawed_;
			std::vector<int> select_ary_;
			std::vector<CPt3D> pts_;
			
	public:
		  Select_State();
		 
			int get_ary_size() {return select_ary_.size();}
      int get_ary_item(int index) { return select_ary_[index];}
			std::vector<int>& get_ary() { return select_ary_;}

			CPt3D get_pt(int index) { return pts_[index];}

			int get_node(CPt3D& nd1,CPt3D& nd2);

			BOOL is_select_joint();
			BOOL is_select_member();
			BOOL is_select_joint_or_member();
			BOOL is_select_node();
			BOOL is_draw_select();
			BOOL is_select_2node();
			BOOL is_select_1node();
			BOOL is_select_plate();
			BOOL is_need_clear_line() { return drag_drawed_;}
			BOOL is_single_select_nodes() const; 
			BOOL is_multi_select_nodes() const;

			BOOL is_select_nodes();
			
			void multi_select_nodes(int max_num = -1);
			void single_select_nodes(int max_num=0);
			void select_plate();
			void select_joint();
			void select_member();
			void select_one_node();
			void select_two_node();
			void draw_select(BOOL bTrue);

			void clear_selected() ;
	

			void clear_select_ary() ;
			void update_model_select();
		
			void push_node(CPt3D pt);
			int get_pts_num() const;
			void draging(CPoint pt);

			void select_main(int num);
			void clear_or_reserve_select_ary();
			void select_sub(int num,UINT sub);

			void enable_drag_drawed(BOOL bTrue) {drag_drawed_ = bTrue;}
			BOOL manual_input_pt(CPt3D& pt1,CPt3D& pt2,int& num);

			void clear_selected(Tool_Base& tool);
			void clear_selected(Scene_Tool<DIS_TOOL>& tool);
			void draging(Tool_Base& tool,CPoint point);
			void draging_polygon(CPoint point);
			void draging(Scene_Tool<INTERSECT_PT>& tool,CPoint point);
			void draging(Scene_Tool<ANGLE_TOOL>& tool,CPoint point);
			void draging(Scene_Tool<PERPENDICULAR_PT>& tool,CPoint point);
			void draging(Scene_Tool<MAKE_PLATE>& tool,CPoint point);
			void draging(Scene_Tool<POLYBEAM_PLATE>& tool,CPoint point);
			void draging(Scene_Tool<EDIT_PLATE>&tool,CPoint point);
		};
}
#endif