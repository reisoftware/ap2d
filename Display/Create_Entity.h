
#ifndef _DISPLAY_CREATE_ENTITY_H_
#define _DISPLAY_CREATE_ENTITY_H_

#include <map>

#include "display_export.h"

#include "../object/Point.h"
#include "Paint_Snap.h"
#include "Virtual_Key.h"
#include "Group_Ents.h"
#include "Array_Command.h"


namespace dlhml
{
enum MODE {TEMP, SINGLE, AGAIN, CONTINUE};
enum CADCMDFLAG {CAD_NULL, CAD_ROTATE};
enum WORK_STATE {WORK_IDLE, WORK_SELECT, WORK_SELECT_MAIN, WORK_COMMAND};
enum RECT_SIZE{DRAG_RC, STRECH_RC};


//const int CMD_IDLE = 46;

//////////////////////////////////////////////////////
const int DRAG_SEL_COUNT = 10;

const int STEP_SNAP = 300;
const int STEP_ANYP = 200;
const int STEP_ORTH = 100;
const int STEP_ZERO =   0;
//                                                  //
//                  db   ortho   anypt   snap       //
//1   ~   099 :     +      +       +      +         //
//100 ~   199 :     -      +       +      +         //
//200 ~   299 :     -      -       +      +         //
//300 ~   399 :     -      -       -      +         //
//-1  ~   -99 :     -      -       -      -         //
//        0   :     -      -       +      +         //
const int SEL_S = -101;                               
const int SEL_E = -102;                               
const int DRAGS =  50;                             
const int EDITE =  51;                               
const int DRAGT =  52;                               
const int DRAGE =  55;                               
//const int COPY_JOINT_S = -3;                             
//const int COPY_JOINT_E =  3;                             
const int INSERT_JOINT_BY_COUNT =  -1001;                             
const int VMOVE_S = -103;
const int SLOPE_LINES = 100;
const int SLOPE_LINEE = 101;
const int INSER_BLOCK = 200;
const int INSER_MULTI_BLOCK = 201;
const int ADD_DIM     = 210;
const int DEL_DIM     = 211;
const int RE0_DIM     = 212;
const int FORMAT_DIM_BASE     = 213;
const int LAYOUT_DIM_LINE     = 214;
const int MOVE_DIM_LINE     = 215;
const int BLOCK_FOCUS = 300;
const int ADD_GROUP_S = 301;
//////////////////////////////////////////////////////

class Rect;
class Scene;
class Block;
class Draw_Entity;
class Cad_Command;

class DISPLAY_API Create_Entity  
{
protected:
  friend class Idle_Command;
protected:
  Create_Entity(Scene& scene);

protected:
	void copy(const Create_Entity& s, Create_Entity& d)const;

public:
  virtual ~Create_Entity();

public:
  void close();
protected:
  virtual void closeme(){delete this;}

public:
  WORK_STATE work_state(){return work_state_;}
  //bool repeat_or_ok(){return repeat_or_ok_;}
protected:
  WORK_STATE work_state_;
  //bool repeat_or_ok_;
public:
  //void select_end(){on_select_end();}
protected:
  //virtual void on_select_end(){}

public:
	void move_scene(const Entity * e, double scale=1);
	void move_scene(const std::vector<Entity*>& es, double scale=1);
public:
	void move_scene(const Rect& rect);

public:
  void refresh();
  void ok(){on_ok();}
  void confirm(){on_confirm();}
  void cancel(){on_cancel();}
  void del(){on_del();}
//	void clear_xor();
	void cmdin();
protected:
  virtual void on_draw();
  virtual void on_ok(){}
  virtual void on_confirm(){}
  virtual void on_cancel(){}
	virtual void on_enter(){}
	virtual void on_del(){}

public:
	virtual void idle_p(){}

public:
  void slope_line(){on_slope_line();}
  void set_focus (){on_set_focus();}
  void insert(Entity * xor_it, const std::vector<Float>& dis, Entity * symbol, int side){on_insert(xor_it,dis,symbol,side);}
  void insert(const Point& pt, Entity * symbol){on_insert(pt,symbol);}
  void insert(Entity * symbol){on_insert(symbol);}
  void insert(Entity * symbol, int select_count){on_insert(symbol,select_count);}
	void property_cad(){on_property_cad();}
  void make_block(){on_make_block();}
  void split_block(){on_split_block();}
  void move_cad(){on_move_cad();}
  void strech_cad(){on_strech_cad();}
  void copy_cad(){on_copy_cad();}
  void array_cad(const Entity_Array& ary){on_array_cad(ary);}
  void scale_cad(){on_scale_cad();}
  void rotate_cad(){on_rotate_cad();}
  void mirror_cad(){on_mirror_cad();}
  void vmove_line(){on_vmove_line();}
  void offset_cad(){on_offset_cad();}
  void extend_cad(){on_extend_cad();}
  void break_cad(){on_break_cad();}
  void trim_cad(){on_trim_cad();}
  void add_group(){on_add_group();}
//  void copy_joint_cad(){on_copy_joint_cad();}
  void add_dim_cad(){on_add_dim_cad();}
  void del_dim_cad(){on_del_dim_cad();}
  void re0_dim_cad(){on_re0_dim_cad();}
  void layout_dim_base_cad(){on_layout_dim_base_cad();}
  void layout_dim_line_cad(){on_layout_dim_line_cad();}
  void move_dim_line_cad(){on_move_dim_line_cad();}
protected:
  virtual void on_slope_line(){}
  virtual void on_set_focus (){}
  virtual void on_insert(Entity * xor_it, const std::vector<Float>& dis, Entity * entity, int side){}
  virtual void on_insert(const Point& pt, Entity * block){}
  virtual void on_insert(Entity * symbol, int select_count){}
  virtual void on_insert(Entity * block){}
	virtual void on_property_cad(){}
  virtual void on_make_block(){}
  virtual void on_split_block(){}
  virtual void on_move_cad(){}
  virtual void on_strech_cad(){}
  virtual void on_copy_cad(){}
  virtual void on_array_cad(const Entity_Array& ary){}
  virtual void on_scale_cad(){}
  virtual void on_rotate_cad(){}
  virtual void on_mirror_cad(){}
  virtual void on_vmove_line(){}
  virtual void on_offset_cad(){}
  virtual void on_extend_cad(){}
  virtual void on_break_cad(){}
  virtual void on_trim_cad(){}
  virtual void on_add_group(){}
//  virtual void on_copy_joint_cad(){}
  virtual void on_add_dim_cad(){}
  virtual void on_del_dim_cad(){}
  virtual void on_re0_dim_cad(){}
  virtual void on_layout_dim_base_cad(){}
  virtual void on_layout_dim_line_cad(){}
  virtual void on_move_dim_line_cad(){}

public:
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
protected:
  virtual void mouse_move_p(UINT nFlags, const Point& pt){}
  virtual void left_button_down_p(UINT nFlags, const Point& pt){}
  virtual void left_button_up_p(UINT nFlags, const Point& pt){}
  virtual void left_button_dblclk_p(UINT nFlags, const Point& pt){}
  virtual void right_button_down_p(UINT nFlags, const Point& pt){}
  virtual void right_button_up_p(UINT nFlags, const Point& pt){}
  virtual void right_button_dblclk_p(UINT nFlags, const Point& pt){}
  virtual void middle_button_down_p(UINT nFlags, const Point& pt){}
  virtual void middle_button_up_p(UINT nFlags, const Point& pt){}
  virtual void middle_button_dblclk_p(UINT nFlags, const Point& pt){}
  virtual void mouse_wheel_p(UINT nFlags, short zDelta, const Point& pt){}
  virtual void key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags){}
  
  virtual void xor_draw_p(Draw_Entity& paint){}
 
public:
  Entity * org(){return org_p();}
protected:
  virtual Entity * org_p()const{return NULL;}

public:
  void xor(const std::vector<Entity*>& xor);
  const std::vector<Entity*>& xor()const ;

public:
  void set_first_draw();
  int  pick_rect_edge_length(RECT_SIZE rcsz=DRAG_RC) const;
  void xor_draw();
  
protected:
  Paint_Entity get_paint();
	double get_len_screen(RECT_SIZE rcsz=DRAG_RC);
  void   get_rect(const Point& pt,	Rect& myrc, RECT_SIZE rcsz=DRAG_RC);
  bool   get_command_line_point(Point&  pt) const;
  bool   get_command_line_length(Float& val) const;
  int    get_commmand_line_string(LPTSTR str) const;

protected:
  Scene& scene_;
	//Scene* scn_;
  Point screen2world(const Point& cpt);
  void  get_ortho_point(const Point& base,Point& pt);
  void  rect_from_center_pt(Rect& rc,const Point& center,Float halfEdgeLen);
  bool  get_snap_point(Point& pt, bool xor=true);
  
  Point move_point_;  //  按下中键移动图纸的起点
  Point begin_;			  //	辅助橡皮线起点
	Point temp_;				//	辅助橡皮线临时点（用于旋转命令）
  Point end_;			    //	辅助橡皮线终点
  int step_;				  //	操作步骤
  Virtual_Key vk_;	  //	键盘输入键
  Group_Ents* group_ents_;		//	实体属于某个组
private:
  bool first_;
//protected:
//  Paint_Snap paint_snap_;

//protected:
//  void adjust(bool b);
//  bool adjust()const ;
//private:
//  bool adjust_;

public:
	void blue_frame(bool b){blue_frame_ = b;}
	bool blue_frame()const{return blue_frame_;}
private:
	bool blue_frame_;	////兰框开关（T:不校验），画/选兰框时打开，其他时关闭。


protected:
  bool is_there(const std::vector<Entity*>& es, MY_CLASS mc);
 
  //bet
protected:
  virtual void command_line_output(LPCTSTR txt,bool up=true);
  virtual void command_line_output(double d,bool up=true);
  virtual void command_line_output(const Point& pt,bool up=true);
  virtual void select_blue_frame  (const Point& pt);
  virtual void select_blue_frame  (const Entity& ent);
  virtual void select_blue_frame  (const Entity_ID& id);
  virtual bool is_in_blue_frame   (const Point& pt);
  
  virtual bool adjust_point(Point& pt, bool cmd = true);
  virtual bool adjust_blue_frame(const Point& pt, bool cmd = true);
  
  virtual bool key_input_pt(Point& pt);
  virtual bool key_input_length(Point& pt, Point prept);
  
  Entity* id_2_entity(const Entity_ID& id)const;

  
protected:
  static LPCTSTR OUTSIDE_BLUE_FRAME_;
  
 
  //zb
protected:
  bool if_lock(Entity* ent);

protected:
  bool ortho_;

protected:
  void xor_draw(const std::vector<Entity*> e, bool xor=true);
  void draw(const std::vector<Entity*> e);

public:
	Point mouse_snap(){return mouse_snap_;}

protected:
  Point mouse_snap_;          //  鼠标(mouse_move)当前点,捕捉之后。
  Point mouse_move_;          //  鼠标(mouse_move)当前点
  Point mouse_screen_;        //  鼠标(mouse_move)当前点
  std::vector<Entity*> bk_;		////每次命令，记录数据库中对象的备份，创建bk时，通知子类
  std::vector<Entity*> db_;		////数据库中对象指针
  std::vector<Entity*> xor_;  //  橡皮线

//   int cad_iter_;              //  复制时复制源的序号
//   Entity* get_move_src();
//   Entity* get_copy_src();
// 	bool undoed_;

  CADCMDFLAG  cadcmdflag_;        //  当前的命令状态(旋转、...)
  Cad_Command * cad_;


public:
	void left_button(UINT nFlags, const Point& pt);
	void move_button(UINT nFlags, const Point& pt);

protected:
  virtual void insert_to_db_p(Entity* entity){}
  virtual void remove_from_db_p(Entity* entity){}
	virtual void swap_db_con_p(Entity * db, Entity * bk){}
	virtual void copy_bk_p(const Entity* db, std::vector<Entity*>& bk){}
	virtual void copy_bk_p(std::vector<Entity*>& db, std::vector<Entity*>& bk){}
protected:
  void insert_to_db(Entity* entity);
  void remove_from_db(Entity* entity);
private:
 	void insert_to_db();
 	void remove_from_db();
	void swap_db_ptr();
	void swap_db_con();
public:
	void copy_bk(std::vector<Entity*>& db, std::vector<Entity*>& bk);
	void copy_bk(const Entity * db, std::vector<Entity*>& bk);
protected:
	void insert_to_db(const std::vector<Entity*>& es);
	void remove_from_db(const std::vector<Entity*>& es);
public:
  void execute();
  void unexecute();
public:
  bool needundo()const{return needundo_;}
protected:
  virtual void needundo(bool need){needundo_ = need;}
private:
  bool needundo_;

private:
	bool  get_rotate_pt(Point& temp, Point& end, std::string cmdtxt)const;
	bool  get_rotate_pt(Point& end, std::string cmdtxt)const;
	Point get_rotate_temp_end(Float val);
	Point get_rotate_end(Float val);
	Point get_scale_end(Float val);

public:
  void set_steel(int s){steel_ = s;}
  int  get_steel(){return steel_  ;}
protected:
  int steel_;
protected:
  bool create_text_;

public:
	void step(int t){step_ = t;}
	int  step()const{return step_;}
	void begin(const Point& pt){begin_ = pt;}
	Point begin()const{return begin_;}


public:
	enum TYPE {ADD,DEL,EDIT,COPY, MULTICOPY,PROP,ADD_DEL};
	void type(TYPE t){type_ = t;type_temp_=t;}
	TYPE type()const{return type_;};
	void copy_flag(bool b);
public:
	TYPE type_;
	TYPE type_temp_;
  bool iscopy_;
	int	 copynum_;
	//NOOK??

protected:
	void trace_seled_pt(const std::vector<Entity*>& es)const;

	//	记录strech选中点的状态必须成对使用
	void set_strech_pt(const std::vector<Entity*>& es);
	//	get之前需先set
	void get_strech_pt(std::vector<Entity*>& es)const;
private:
	std::vector<std::pair<int,std::vector<bool> > > strech_pt_;

protected:
	std::string myclass_;
	
private:
	MCT_DEF
};

inline void destory(Create_Entity*& cc);

inline void destory(Create_Entity*& cc)
{
  if(cc){
    cc->close();
    cc=NULL;
  }
}

const LPTSTR layer_manual_dim = "l_manual_dim";//手动加的标注

}
#endif//FILE
