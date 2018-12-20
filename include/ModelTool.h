#ifndef _MODEL_TOOL_H
#define _MODEL_TOOL_H
#include "pt3d.h"
namespace gelib{
  class Tool_Handle;
  class Select_State;

  const int NONE = 0;
  const int ADD_BEAM = 1;
  const int ADD_COL = 2;
  const int ADD_BRACE = 3;
  const int SET_CEN = 4;
  const int DEL_NODE = 5;
  const int MOVE_TOOL =6;
  const int COPY_TOOL = 7;

  const int DIS_TOOL = 9;
  const int CUT_PLANE = 10;
  const int EDIT_PLATE = 11;
  const int MAKE_PLATE = 12;
  const int ADD_AXIS = 13;
  const int MIRROR_TOOL = 14;
  const int PARALLEL_PT = 15;
  const int ANGLE_PT = 16;
  const int EXTENT_PT = 17;
  const int INTERSECT_PT = 18;
  const int PERPENDICULAR_PT = 19;
  const int DIVIDED_PT = 20;
  const int ANGLE_TOOL = 21;
  const int CUT_SECTION = 22;
  const int MEMBER_CUT = 23;
  const int MOVEND_TOOL = 24;
  const int CHK_WELD = 25;
  const int JBLIB_JNT = 26;
  const int BOLT_PLATE = 27;
  const int NORM_CUT = 28;
  const int ROUND_PLATE = 29;
  const int UNROUND_PLATE = 30;
  const int CUSTOM_JNT = 31;
  const int ADD_BOLTS = 32;
  const int POLYBEAM_PLATE = 33;
  const int ASSIGNJNT_TOOL = 34;
  const int NEARPOINT_TOOL = 35;
  class Tool_Base{
  public:
    virtual ~Tool_Base() {}
    virtual void OnTool(Tool_Handle* h,CPt3D& pt1,CPt3D& pt2) =0;
    virtual void draging(Select_State* state,CPoint point) = 0;
    virtual void clear_selected(Select_State* state) = 0;
    virtual void get_data(CString& name,CString& data) =0;
  };
  template<int index> class Scene_Tool: public Tool_Base
  {
    enum{value = index};
  public:
    void OnTool(Tool_Handle* h,CPt3D& pt1,CPt3D& pt2) {
      h->OnTool(*this,pt1,pt2);
    }
    void draging(Select_State* state,CPoint point) {
      state->draging(*this,point);
    }
    void clear_selected(Select_State* state){
      state->clear_selected(*this);
    }
    void get_data(CString& name,CString& data) {}
  };
}
#endif
