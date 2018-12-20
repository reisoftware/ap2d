// Scene.h: interface for the Scene class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SCENE_H__7B5A1751_F2B2_421A_B7C1_26B0595D23F8__INCLUDED_
#define AFX_SCENE_H__7B5A1751_F2B2_421A_B7C1_26B0595D23F8__INCLUDED_

#include "display_export.h"
#include "Paper_Space.h"
#include "Cmd_Mgr_d.h"
#include "Scene_Wnd.h"
#include "Paint_Entity.h"
#include "Database.h"
#include "Command_Line.h"
#include "Edit_Entity.h"
#include "Painter.h"
#include "myalgorithm.h"
#include "Visitor.h"

#include "Idle_Command.h"

namespace dlhml{
class DISPLAY_API Scene  
{
public:
	Scene();
	void set_idle(Idle_Command* idle);
	virtual ~Scene();

public:
	void move_scene(const Entity * e, double scale=1);
	void move_scene(const std::vector<Entity*>& es, double scale=1);

public:
  //command list
	Idle_Command * get_idle();
  Create_Entity* current_cmd(); 
  void clear_cmd(){cmd_list_.clear();}
	void undo();
	void redo();
	bool can_undo();
	bool can_redo();
  //okcancle
  void ok();
  void confirm();
  void cancel();
  void del();
  //void again();
	void idle();
	void cmdin();

  //  ²»Ó°Ïìdatabase
  void slope_line();
  void set_focus();
  void insert(Entity * symbol);
  void insert(Entity * symbol, int select_count);
  void insert(const Point& pt, Entity * symbol);
  void insert(Entity * xor_it, const std::vector<Float>& dis, Entity * symbol, int side);
  //void insert(double w, double h);
  //void insert(double w, double h, const Point& pt);
  //  Ó°Ïìdatabase
	void property_cad();
  void make_block();
  void split_block();
	void entity_move();
  void strech_cad();
	void create_copy();
	void array_cad(const Entity_Array& ary);
	void create_mirror();
	void create_rotate();
	void create_scale();
	void create_break();
	void create_delete();
	void create_extend();
	void create_trim();
  void vmove_line();
  void offset_cad();
  void add_group();
//  void copy_joint_cad();

	void add_dim_cad();
	void del_dim_cad();
	void re0_dim_cad();
	void layout_dim_base_cad();
	void layout_dim_line_cad();
	void move_dim_line_cad();

	void attach_command(Create_Entity* cmd);
	void idle_command();
	void create_entity(Create_Entity* ce=NULL);

  //paper space;
	bool ortho() const											{return paper_.ortho();}
	void ortho(bool bortho)									{paper_.ortho(bortho);}
	COLORREF background_color() const				{return paper_.background_color();}
	void background_color(COLORREF col)			{paper_.background_color(col);}
	COLORREF entity_color() const						{return paper_.entity_color();}
	void entity_color(COLORREF col)					{paper_.entity_color(col);}
	LPCTSTR line_style() const							{return paper_.line_style();}
	void line_style(LPCTSTR style)					{paper_.line_style(style);}
	LPCTSTR layer() const										{return paper_.layer();}
	void layer(LPCTSTR lay)									{paper_.layer(lay);}
	void set_move(Float dx,Float dy,Float dz)		{paper_.set_move(dx,dy,dz);}
	void set_scale(Float sx,Float sy,Float sz)	{paper_.set_scale(sx,sy,sz);}
	Matrix screen_to_world() const					{return paper_.screen_to_world();}
	Matrix world_to_screen() const					{return paper_.world_to_screen();}
	Point get_current_center(const Point& screen_center) const;
	Float get_current_scale() const					{return paper_.get_current_scale();}
	Snap* get_snap_flag()		{return paper_.get_snap_flag();}

	bool add_to_dim_list() const						{return paper_.add_to_dim_list();}
	void add_to_dim_list(bool b)						{paper_.add_to_dim_list(b);}
	bool erase_from_dim_list() const				{return paper_.erase_from_dim_list();}
	void erase_from_dim_list(bool b)				{paper_.erase_from_dim_list(b);}
	bool align_dim_base() const							{return paper_.align_dim_base();}
	void align_dim_base(bool b)							{paper_.align_dim_base(b);}
	bool reset0_to_dim_list() const					{return paper_.reset0_to_dim_list();}
	void reset0_to_dim_list(bool b)					{paper_.reset0_to_dim_list(b);}
  void radio_dim_flags(int index)         {paper_.radio_dim_flags(index);}
  void init_dim_flags()                   {paper_.init_dim_flags();}

	bool size_dim_continue() const					{return paper_.size_dim_continue();}
	void size_dim_continue(bool b)					{paper_.size_dim_continue(b);}


	void create_Dim_Lead_Dimension();
	void create_Dim_Text_Dimension();
	void create_Dim_Axis_Dimension();


//	void create_line();
//	void edit_line(Entity& line);
	void create_rectentity();
	void edit_rectentity(Entity& rectentity);
//	void create_circle();
//	void edit_circle(Entity& circle);
//	void create_arc();
//	void edit_arc(Entity& arc);
	void create_text(LPCTSTR cont,int height, int color_id);
	void edit_text(Entity& text);
//	void create_cloud_line();
//	void edit_cloud_line(Entity& cloud);

//	void edit_dim_three_pt(Entity& threept);
//	void edit_dim_three_pt_block(Entity& threeptblock);
//	void edit_dim_angle(Entity& angle);
//	void edit_dim_four_pt(Entity& fourpt);
//	void edit_dim_four_pt_block(Entity& fourptblock);
//	void edit_dim_lead(Entity& lead);
//	void edit_dim_lead_block(Entity& leadblock);
//	void edit_dim_radius(Entity& radius);
//	void edit_dim_text(Entity& text);
	void edit_cut_section(Entity& cut_section);


	void mouse_move(UINT nFlags, const Point& pt);
	void left_button_down(UINT nFlags, const Point& pt);
	void left_button_up(UINT nFlags, const Point& pt);
	void left_button_dblclk(UINT nFlags, const Point& pt);
	void right_button_down(UINT nFlags, const Point& pt);
	void right_button_up(UINT nFlags, const Point& pt);
	void right_button_dblclk(UINT nFlags, const Point& pt);
	void middle_button_down(UINT nFlags, const Point& pt);
	void middle_button_up(UINT nFlags, const Point& pt);
	void middle_button_dblclk(UINT nFlags, const Point& pt);
	void mouse_wheel(UINT nFlags, short zDelta, const Point& pt);
	void key_down(UINT nChar, UINT nRepCnt, UINT nFlags);

//  void paint(); //  draw_scene

	void screen_to_world_point(Point& pt) const;
	void world_to_screen_point(Point& pt) const;

	void screen_to_world_rect(Rect& rect) const;
	void world_to_screen_rect(Rect& rect) const;

	Database* database() const {return database_.get();}
	void draw_scene();

	void attach_window(Scene_Wnd* window);
	Scene_Wnd* get_window() const;
	void invalidate();
	void invalidate_rect(RECT rc);
	Rect client_rect();
	Painter* get_painter() const;

	void attach_edit_entity(Edit_Entity* edit);
	Edit_Entity* get_edit_entity() const					{return edit_entity_.get();}

	void attach_edit_entity_dlg(Edit_Entity* edit);
	Edit_Entity* get_edit_entity_dlg() const					{return edit_entity_dlg_.get();}
  void set_vistor(Visitor* edit_dlg);
  Visitor* get_vistor();

	void attach_command_line(Command_Line* command);
	void info_to_command_line(LPCTSTR info,bool update=false);
	bool get_command_line_point(Point& pt) const;
	bool get_command_line_length(Float& len) const;
	int get_commmand_line_string(LPTSTR str) const;
	void coord_info_to_status(LPCTSTR info);

private:
	Paper_Space paper_;
	Cmd_Mgr cmd_list_;
	auto_ptr_close<Scene_Wnd> window_;			//create or attach before initialize
	auto_ptr_close<Painter> painter_;				//create before initialize
	auto_ptr_close<Paint_Entity> paint_;		//create before initialize
	auto_ptr_close<Database> database_;				//create
	auto_ptr_close<Command_Line> command_line_;	//create or attach before initialize
	auto_ptr_close<Edit_Entity> edit_entity_;		//create or attach before initialize

	auto_ptr_close<Edit_Entity> edit_entity_dlg_;	//attach before initialize
	Visitor *edit_ent_dlg_;	//attach before initialize

public:
	int  screen_cx()const;	
  int  screen_cy()const;
  void screen_rc(int& cx, int& cy)const;
  void screen_rc(RECT& rc)const;

public:
  Paint_Snap paint_snap_;
public:
  void selected_all(bool sel);

public:
	void wheel_speed(Float f){wheel_speed_ = f;}
	Float wheel_speed()const{return wheel_speed_;}
  void continue_line(bool b){continue_line_ = b;}
  Float continue_line()const{return continue_line_;}
  void max_draw_count(int n){max_draw_count_ = n;}
  int max_draw_count()const{return max_draw_count_;}
private:
	Float wheel_speed_;
  bool continue_line_;
  int max_draw_count_;

public:
	void  pre_left(const Point& pt){pre_left_=pt;}
	Point pre_left()const{return pre_left_;}
private:
	Point pre_left_;

public:
	void left_button(UINT nFlags, const Point& pt);	////world
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_SCENE_H__7B5A1751_F2B2_421A_B7C1_26B0595D23F8__INCLUDED_)
