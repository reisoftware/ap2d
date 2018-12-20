
#ifndef _TIAN_DISPLAY_IDLE_COMMAND_H_
#define _TIAN_DISPLAY_IDLE_COMMAND_H_

#include "Create_Entity.h"
#include "Line.h"

namespace dlhml{


enum SEL_FLAG {SNULL, SCTRL, SSHIFT};
enum CMD_TYPE {IDLE, EDIT, MOVE, INSERT_BYENTITY};

class Entity;
class Cad_Command;
class DISPLAY_API Idle_Command : public Create_Entity
{
  friend class Create_Command;
public:
	Idle_Command(Scene& scene);
  virtual void closeme(){delete this;}

	void set_step(){step_ = SEL_S;}
protected:
	virtual ~Idle_Command();

protected:
  virtual Create_Entity* create_command(Entity* t);
  virtual void exit(){}
  virtual void edit_attribute(){}
  virtual void block_mgr(){}
	virtual void set_cad_xor();
protected:
	virtual void add_cur_scene(){}

public:
	virtual void pop_property(Entity * hit = NULL);
	virtual void clipper(){}
	virtual void paste();
	virtual void idle_p();
	virtual void cmd_scene_p(){}

  virtual void on_break_cad(int num, double dis);

protected:
	virtual void mouse_move_p(UINT nFlags, const Point& pt);
  virtual void left_button_down_p(UINT nFlags, const Point& pt);
  virtual void left_button_dblclk_p(UINT nFlags, const Point& pt);
private:
	void set_key_flag(UINT nFlags, const Point& pt);

protected:
  virtual void set(const Point& pt){;}

protected:
	virtual void xor_shirr_rect(bool xor=true);
	virtual void xor_shirr_line(bool xor=true);
	virtual void xor_shirr_temp(bool xor=true);

private:
  virtual void on_draw();
  virtual void on_ok();
  virtual void on_confirm();
  virtual void on_cancel();

private:
	virtual void on_del();
  virtual void on_copy_cad();
	virtual void on_array_cad(const Entity_Array& ary);
  virtual void on_move_cad();
  virtual void on_mirror_cad();
  virtual void on_rotate_cad();
  virtual void on_scale_cad();
private:
  virtual void on_extend_cad();
  virtual void on_trim_cad();
  virtual void on_break_cad();
  virtual void on_offset_cad();
  virtual void on_vmove_line();
  virtual void on_strech_cad();
private:
  virtual void on_make_block();
  virtual void on_split_block();
  virtual void on_add_group();
	//  virtual void on_copy_joint_cad();

private:
  virtual void on_insert(Entity * symbol);
  virtual void on_insert(Entity * symbol, int select_count);
  virtual void on_insert(const Point& pt, Entity * symbol);
  virtual void insert_p (const Entity * e);
  virtual void on_insert(Entity * xor_it, const std::vector<Float>& dis, Entity * symbol, int side);
public:
  void insert(std::vector<Entity*>& symbol, const Point& focus);
  void insert(const Point& pt, std::vector<Entity*>& symbol, const Point& focus);

private:
	virtual void on_property_cad();

private:
  virtual void on_add_dim_cad();
  virtual void on_del_dim_cad();
  virtual void on_re0_dim_cad();
  virtual void on_layout_dim_base_cad();
  virtual void on_layout_dim_line_cad();
  virtual void on_move_dim_line_cad();

protected:
	virtual void selected_p(){}		////选择结束后通知子类

private:
  void start_select();
private:
  CMD_TYPE cmd_type_;
  Entity * insert_;   //insert
	std::vector<Entity*> inserts_;
	Point insert_focus_;
  int select_count_;

public:
	void get_xor(std::vector<Entity*>& xor)const;
	void set_xor(const std::vector<Entity*>& xor);

public:
	void remember_xor();
	void comeback_xor();
private:
	std::vector<Entity*> prexor_;		////记忆上一次选中的实体集

private:
  void draw_red_rect(bool xor);
  void draw_red_rect(Entity * entity, bool xor);
public:
	void clear_selected();
	void clearxor();
  void push_xor(Entity * e);
  void erasexor(Entity * e);
	void push_xor(const std::vector<Entity*>& es);
	void erasexor(const std::vector<Entity*>& es);

protected:
	virtual void clearxor_p();


public:
	void select_pt(Entity * e);
	void draw_pt(Entity * enitiy, bool xor);

	void get_same_group(std::vector<Entity*>& resu, const Entity * e);

private:

//  选择
private:
	Entity* select_entity();
	void xor_entity(Entity* ent);
	bool is_selected(Entity* ent);
	bool if_lock(Entity* ent);
	bool if_cross_ent(Entity* ent);

private:
  void create_to_old();
  void cad_command();
  void execute_new();


private:
  void destory_cad();
  void destory_cc();
  void attach_cc();

private:
  bool alt_flag_;
  SEL_FLAG sel_flag_;       //多选时组合键标志
  Rect  sel_rc_;            //  选择实体的矩形
  bool  is_rcsel_;          //  f:点选，t:圈选

//  拖动
private:
  bool is_there_superposition(const Point& pt, Entity * ent, int pt_index);
  bool find_redrc(Point& pt);
  bool find_redrc(const Point& pt);
	Line get_calc_ln();
private:
  bool sel_red_;           //  选中红框
  int  red_ent_;           //  选中的实体序号
  int  red_pt_;            //  选中的点序号

private:
  Create_Entity * cc_;

protected:
  int  cmd_flag_;

private:
	bool adjust_blue_flag(Entity * e)const;
  bool trace_xor()const;
	
private:
	MCT_DEF
};


}
#endif//FILE
