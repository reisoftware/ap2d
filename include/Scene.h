// Scene.h: interface for the Scene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__9DB8DDFE_78B4_4503_9A23_1F3F95D9D9C4__INCLUDED_)
#define AFX_SCENE_H__9DB8DDFE_78B4_4503_9A23_1F3F95D9D9C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <gl/gl.h>
#include <gl/glu.h>
#include "Gl_Dc_Imp.h"
#include "model_geographic.h"

#include "cmd_mgr.h"
#include "mouse_handle.h"
#include "Key_Handle.h"
#include "selector.h"
#include "select_state.h"
#include "Tool_Handle.h"
#include "geptr.h"


class CModel;
namespace gelib{
  class AFX_EXT_CLASS Scene :public Mouse_Handle,public Key_Handle,
	       public Cmd_Mgr,public Selector,public Select_State,
	       public Tool_Handle
  {
  public:

    Scene(CModel& model,HWND hWnd);
    ~Scene();
  public:
    void offset(double x,double y);
    void OnPaint();
    void OnSize(UINT nType, int cx, int cy);

    void render();
    void line_frame();
    void reinitialize_geo();
    void reset_plane();
    void set_geo(Model_Geographic geo);
		void set_prj();

    void set_active();
    CModel& get_model() { return model_;}
    CWnd* get_cwnd() {return CWnd::FromHandle(hwnd_);}
  private:
    CModel& model_;
    HWND hwnd_;
    Gl_Dc_Imp gl_dc_imp_;
    std::vector<CPt3D> section_pts_;
	
  private:	
    Model_Geographic model_geo_;
    DWORD dwSelType;

  private:
    CPt3D get_cursor_pt();	
    void reinitialize_center();
    double ratio();
    void gl_project();
    void draw_scene(GLenum mode = GL_RENDER);
    void draw_model(GLenum mode);
    void draw_pls();

    CPoint world_2_client(CPt3D& pt);
    BOOL client_2_world(CPoint &pt, CPt3D &pt_3d);
	
    void set_cen(CPt3D cen) {model_geo_.set_cen(cen);}
    void move_by_x(double delta) {model_geo_.move_by_x(delta);}
    void move_by_y(double delta) {model_geo_.move_by_y(delta);}
    void scale(double delta) {model_geo_.scale(delta);}
	

    void draw_mems(GLenum mode);
    void draw_jnts(GLenum mode);
    void draw_nodes();
    void draw_assistant_pts();
    void draw_assistant_lines();
    void draw_jnts_plates();

    int get_node_num(CPt3D pt);

    void get_nds_in_plane(std::vector<CPt3D>& ids);
    void add_assistant_pt(CPt3D pt);
    void del_assistant_pt(CPt3D pt);
	
    void add_assistant_line(CPt3D start,CPt3D end);
  public:
    class Gl_Dc{
      Scene* scene_;
    public:
      explicit Gl_Dc(Scene* s):scene_(s) { scene_->gl_dc_imp_.attach(scene_->hwnd_);}
      ~Gl_Dc() { scene_->gl_dc_imp_.detach(scene_->hwnd_);}
    };

    friend class Gl_Dc;
    friend class Mouse_Handle;
    friend class Key_Handle;
    friend class Selector;
    friend class Select_State;
    friend class Tool_Handle;
    //
  };

  template<class T>
  inline
  Scene* get_scene(T* t)
  {
    return static_cast<Scene*>(t);
  }
}	
#endif // !defined(AFX_SCENE_H__9DB8DDFE_78B4_4503_9A23_1F3F95D9D9C4__INCLUDED_)
