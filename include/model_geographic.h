// Model_Geographic.h: interface for the Model_Geographic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_GEOGRAPHIC_H__01BD5A8A_FF33_4D8D_B219_FE2AD07CA3FD__INCLUDED_)
#define AFX_MODEL_GEOGRAPHIC_H__01BD5A8A_FF33_4D8D_B219_FE2AD07CA3FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "pt3d.h"
#include "GeNorm.h"
#include "Assistant_Line.h"
#include <string>

class CMember;
namespace gelib{
  class Gl_Dc_Imp;
  const int xy_axis = 1;
  const int yz_axis = 2;
  const int zx_axis = 4;
  class AFX_EXT_CLASS Model_Geographic  
  {
    int index_;
    BOOL need_save_;
    double x_;
    double y_;
    double z_;

    double beta_x_;
    double beta_y_;
    double beta_z_;

    double scale_;

    CPt3D center_;
    CPlane plane_;
    BOOL show_2D_;
    BOOL clip_;

    int axis_type_;
    std::string name_;
    std::vector<CPt3D> pts_;
    std::vector<Assistant_Line> lines_;
  private:
    void serialize_lines(CArchive& ar);
  public:
    Model_Geographic();
    ~Model_Geographic();

    int get_index() const {return index_;}
    void set_index(int index) { index_ = index;}

    BOOL is_need_save() const { return need_save_;}
    void set_need_save(BOOL bTrue) { need_save_ = bTrue;}
  public:
    void add_pt(CPt3D pt);
    void del_pt(CPt3D pt);
    void draw_pts() const;
    void append(std::vector<CPt3D>& pts) const;

    void clear_assistant();
  public:
    void add_line(CPt3D start,CPt3D end);
    void draw_lines() const;

  public:
    void front();
    void back();
    void left();
    void right();
    void center(double scale,double dx,double dy);
    const char* get_name() const;
    void set_name(const char* name);
  public:
    void init_axis_type_from_plane();
    CPt3D get_center() const { return center_;}
    void clip();
    void input_clip_plane_dis();
    CPt3D get_plane_pt() {return plane_.pt;}
    void set_2D(BOOL show_2D) { show_2D_ = show_2D;}
    BOOL is_show_2D() {return show_2D_;}
    void axis_from_clip(CGeAxis* axis) { plane_.InitGeAxis(axis);}
    void set_clip(BOOL clip) {clip_ = clip;}
    BOOL is_clip() { return clip_;}

    void set_plane(CMember* mem1,CMember* mem2);
    void set_plane(CModel* model,CPt3D pt1,CPt3D pt2,CPt3D pt3);
    CPlane& get_plane() {return plane_;}
    void draw_coord(Gl_Dc_Imp& dc);
    void project(double ratio);

    void move_by_x(double delta) { x_ += delta;}
    void move_by_y(double delta) { y_ += delta; }
    void move_by_z(double delta) { z_ += delta; }
	
    void rotate_by_x(double delta) { beta_x_ += delta; }
    void rotate_by_y(double delta) { beta_y_ += delta; }
    void rotate_by_z(double delta) { beta_z_ += delta; }

    void set_cen(CPt3D cen) { center_ = cen;}
    void scale(double delta) { 
      if(delta > 0)
	scale_ *= delta; 
      else if(delta < 0)
	scale_ /= -delta;
      if(scale_ > 1000.0)
	scale_ = 1000.0;
		
    }
    int get_axis_type() {return axis_type_;}
    BOOL set_axis_type();
    void set_axis_type(int type) { axis_type_ = type;}
    CArchive& operator <<(CArchive& ar);
    CArchive& operator >>(CArchive& ar);
    void Serialize(CArchive& ar);
  };
}
#endif // !defined(AFX_MODEL_GEOGRAPHIC_H__01BD5A8A_FF33_4D8D_B219_FE2AD07CA3FD__INCLUDED_)
