
#include "stdafx.h"
#include "Idle_Command.h"

#include <cassert>
#include <vector>


#include "../include/getrace.h"
#include "../afc/date_time.h"
#include "../object/Global.h"
#include "../object/intersect.h"


#include "Scene_d.h"
#include "Rect.h"
#include "Paint_Entity.h"
#include "Painter.h"
#include "myalgorithm.h"
#include "Line.h"
#include "Database.h"
#include "Edit_Entity_Property.h"
#include "Layer.h"
#include "Block.h"
#include "Cloud_Line.h"
#include "Point.h "

#include "Paint_Entity_Tools.h"
#include "Ln_Dim_Block.h"
#include "Ln_Dim.h"

#include "Create_Command.h"

#include "Edit_Command.h"
#include "Move_Command.h"
#include "Scale_Command.h"
#include "Block_Command.h"
#include "Rotate_Command.h"
#include "Mirror_Command.h"
#include "Insert_Command.h"
#include "Vmove_Line_Command.h"
#include "Offset_Command.h"
#include "Strech_Command.h"
#include "Extend_Command.h"
#include "Break_Command.h"
#include "Trim_Command.h"
#include "Split_Block_Command.h"
#include "Unite_Group_Command.h"
#include "Multi_Insert_Command.h"
#include "Add_Dim_Command.h"
#include "Del_Dim_Command.h"
#include "Re0_Dim_Command.h"
#include "Layout_Dim_Base_Command.h"
#include "Layout_Dim_Line_Command.h"
#include "Move_Dim_Line_Command.h"

#include "Offset_Drag_Pt.h"

namespace dlhml{ 


LPCTSTR c_str_base_pt = "Specify the base point.";


Idle_Command::Idle_Command(Scene& scene) 
:Create_Entity(scene)
,sel_flag_(SNULL)
//,iscopy_(false)
,is_rcsel_(false)
,alt_flag_(false)
,sel_red_ (false)
,red_ent_ (0)
,red_pt_  (0)
,cc_(NULL)
//,cad_(NULL)
,cmd_flag_(0)
,cmd_type_(IDLE)
,select_count_(0)
MCT_INIT2("Idle_Command")
{
  //   TRACE_OUT("\n####Idle_Command::Idle_Command()\n");
  //   TRACE_OUT("####scene_ptr:%d\n",&scene_);
  //   TRACE_OUT("####scn_ptr:%d\n",scn_);
  //   TRACE_OUT("####scn_ptr&:%d\n",&scn_);
  myclass_ = "Idle_Command";
  work_state_=WORK_IDLE;
  //  adjust(true);
  needundo(false);
  step_ = SEL_S;
} 

Idle_Command::~Idle_Command()
{
	//TRACE_OUT("\nIdle_Command::~Idle_Command()\n");
  destory_cad();
	destory_cc();////加入cmd list的，有cmd_mgr负责释放
	//TRACE_OUT("bk_.size == %d\n", bk_.size());
}

void Idle_Command::mouse_move_p(UINT nFlags, const Point& pt)
{
  //   afc::Date_Time dt;
  //   TRACE_OUT("move-- %s\n", dt.local_time().c_str());
  switch(step_)
  {
  case SEL_E:
    xor_shirr_rect();
    end_ = pt;
    xor_shirr_rect();
    break;
  case EDITE:
  case DRAGE:
  case DRAGT:
  //  case COPY_JOINT_E:
  case SLOPE_LINEE:
    xor_shirr_line();
    end_ = pt;
    xor_shirr_line();
    break;
//   ////插入块时画临时橡皮块，暂时用。
//   case INSER_BLOCK:
//     if(insert_){
//       insert_->focus(pt);
//     }
//     if(!db_.empty()){
//       Entity* e = db_.front();
//       if(e){
//         e->focus(pt);
//       }
//     }
//     break;
  }
}

void Idle_Command::on_draw()
{
  //   afc::Date_Time dt;
  //   TRACE_OUT("draw-- %s\n", dt.local_time().c_str());
  //Create_Entity::on_draw();
  draw_red_rect(true);
  if(work_state_==WORK_IDLE || work_state_==WORK_SELECT){
  }
  switch(step_)
  {
  case SEL_E:
    xor_shirr_rect(true);
    break;
  case EDITE:
  case DRAGE:
  case DRAGT:
//  case COPY_JOINT_E:
  case SLOPE_LINEE:
    xor_shirr_line(true);
		xor_shirr_temp(true);
    break;
  }
}

void Idle_Command::idle_p()
{
  destory_cad();
  destory(bk_);
	insert_ = NULL;
	inserts_.clear();
	insert_focus_.setdata(0,0);

  begin_ = end_;
  step_=SEL_S;
  //steel_=CMD_IDLE;
  iscopy_ = false;
	is_rcsel_ = true;
  work_state_=WORK_IDLE;
  scene_.invalidate();
}

void Idle_Command::on_ok()
{
	assert(db_.empty());
	idle_p();
	remember_xor();
	clearxor_p();
// 	select(xor_,false);
// 	xor_.clear();
//   scene_.invalidate();
}

void Idle_Command::start_select()
{
  step_  = SEL_S;
  work_state_=WORK_SELECT;
  command_line_output("Specify the memberes.");
}

void Idle_Command::on_confirm()
{
  if(xor_.empty()){
    start_select();
    return;
  }
  switch(cmd_type_)
  {
  case INSERT_BYENTITY:
    break;
  }
}

void Idle_Command::on_cancel()
{
  on_ok();
}


Create_Entity* Idle_Command::create_command(Entity* t)
{
  return new Create_Command(scene_, t);
}


void Idle_Command::create_to_old()
{
  Entity* entity =NULL;
  if(!xor_.empty()){
    entity = xor_.front();
  }
	//NOOK
  //cc_ = create_command(entity);
	destory_cc();
  cc_ = create_command(NULL);
  if(!cc_){
    return;
  }
  cc_->set_steel(get_steel());
  cc_->group_ents_ = group_ents_;
  cc_->iscopy_ = iscopy_;
	cc_->type_ = type_;
  //dlhml::push_back<Entity>(xor_, cc_->xor_);
  if(!iscopy_ && type_!=ADD){
		dlhml::push_back<Entity>(xor_, cc_->db_);
  }
}
void Idle_Command::set_cad_xor()
{
  cad_->set_xor(&(xor_));
}

Line Idle_Command::get_calc_ln()
{
	if(cad_ && cad_->is_there_temp()){
		Normal tnor, enor;
		tnor.set_data(begin_, temp_);
		enor.set_data(begin_, end_ );
		Float tdeg, edeg;
		dlhml::normal2d_2_degree(tnor, tdeg);
		dlhml::normal2d_2_degree(enor, edeg);
		Float ndeg = edeg - tdeg;
		Normal nnor;
		dlhml::degree_2_normal2d(ndeg, nnor);
		Float len = begin_.distanceto2d(end_);
		Point npt = begin_.polarTo(len, nnor);
		Line ln(begin_, npt);
		temp_ = end_;

		return ln;
	}

	Line ln(begin_,end_);
	return ln;
}

void Idle_Command::cad_command()
{
  create_to_old();
  if(!cad_ || !cc_){
    return;
  }
	set_cad_xor();
  //cad_->set_xor(&(xor_));
  cad_->set_new(&(cc_->bk_));
	Line ln = get_calc_ln();
  if(cad_->cad_cammand(ln)){
		if(iscopy_ ){
			copy_bk(xor_, cc_->bk_);////通知子类备份
		}
    execute_new();
  }else{
		destory_cc();
    select(xor_, true);
    command_line_output("Default.");
  }
}

void Idle_Command::execute_new()
{
//	TRACE_OUT("\n####\nIdle_Cmd::execute_new()\n");
	//select(xor_, false);
	//xor_.clear();

  if(!cc_){
    return;
  }
  cc_->execute();
	//push_xor(cc_->db_);
//	TRACE_OUT("iscopy_ : %d\n", iscopy_);
	////insert 不高亮
	trace_seled_pt(xor_);
	set_strech_pt(xor_);
  select(cc_->db_, false);
	if(!iscopy_ && type_ == ADD){
		clearxor_p();
	}else{
		clearxor_p();
		push_xor(cc_->db_);
	}
	if(!xor_.empty()){
		get_strech_pt(xor_);
	}

// 	if(iscopy_){
// 		clearxor_p();
// 		push_xor(cc_->db_);
// 	}
// 	////insert 不高亮
// 	else if(type_ == ADD){
// 		clearxor_p();
// 	}
	attach_cc();
  scene_.idle_command();
}

//void Idle_Command::on_select_end()
//{
//}


//#define _TEST_SPEET_

// #ifdef _TEST_SPEET_
// //TEST LINE
// void Idle_Command::on_move_cad()
// {
//   Line* ent = Line::create_me();
//   int i=0, j=0;
//   for(i=0; i<100; i++){
//     for(j=0; j<100; j++){
//       ent = Line::create_me();
//       ent->line_style("dot");
//       ent->setdata(Point(i*100,j*100),Point(i*100,j*100+70));
//       insert_to_db(ent);
//     }
//   }
//   
//   Point pt = screen2world(Point(0,0,0));
//   for(i=0;i<65;++i){
//     mouse_wheel(NULL,-120, pt);
//   }
// }
// //TEST TEXT
// void Idle_Command::on_copy_cad()
// {
//   Text* ent = Text::create_me();
//   int i=0, j=0;
//   for(i=0; i<100; i++){
//     for(j=0; j<100; j++){
//       ent = Text::create_me();
//       ent->setdata(Point(i*100,j*100),"TEXT");
//       ent->rotation(1.57);
//       insert_to_db(ent);
//     }
//   }
//   Point pt = screen2world(Point(0,0,0));
//   for(i=0;i<5;++i){
//     mouse_wheel(NULL,-120, pt);
//   }
// }
// //TEST DIM
// void Idle_Command::on_strech_cad()
// {
//   int i=0, j=0;
//   for(j=0; j<1; j++){
//     Ln_Dim_Block * block = Ln_Dim_Block::create_me();
//     Ln_Dim* ent = Ln_Dim::create_me();
//     std::vector<Point> pts;
//     pts.push_back(Point(000,00+100*j));
//     pts.push_back(Point(100,00+100*j));
//     pts.push_back(Point(100,50+100*j));
//     ent->set(pts);
//     block->push_back(ent);
//     for(i=1; i<100; i++){
//       Ln_Dim * dim = (Ln_Dim*)ent->clone();
//       dim->ept(Point(((i+1)*100),0+100*j));
//       block->push_back(dim);
//     }
//     Paint_Entity_Tools::recal_dim_block(*block);
//     insert_to_db(block);
//   }
//   
//   Point pt = screen2world(Point(0,0,0));
//   for(i=0;i<65;++i){
//     mouse_wheel(NULL,-120, pt);
//   }
// }
// void Idle_Command::on_offset_cad()
// {
//   //TEST TEXT
//   Text* txt = Text::create_me();
//   int i=0, j=0;
//   for(i=0; i<100; i++){
//     for(j=0; j<100; j++){
//       txt = Text::create_me();
//       txt->setdata(Point(i*100,j*100),"TEXT");
//       insert_to_db(txt);
//     }
//   }
//   
//   //TEST LINE
//   Line* ln = Line::create_me();
//   //int i=0, j=0;
//   for(i=0; i<100; i++){
//     for(j=0; j<100; j++){
//       ln = Line::create_me();
//       ln->line_style("dot");
//       ln->setdata(Point(i*100,j*100),Point(i*100,j*100+70));
//       insert_to_db(ln);
//     }
//   }
//   
//   //TEST DIM
// //  Ln_Dim_Block * block = Ln_Dim_Block::create_me();
// //  Ln_Dim* dim = Ln_Dim::create_me();
// //  std::vector<Point> pts;
// //  pts.push_back(Point(0,0));
// //  pts.push_back(Point(100,0));
// //  pts.push_back(Point(100,50));
// //  dim->set(pts);
// //  block->push_back(dim);
// //  //int i=0, j=0;
// //  for(i=1; i<100; i++){
// //    dim = (Ln_Dim*)dim->clone();
// //    dim->ept(Point(((i+1)*100),0));
// //    block->push_back(dim);
// //  }
// //  Paint_Entity_Tools::recal_dim_block(*block);
// //  insert_to_db(block);
// //  
// //  Point pt = screen2world(Point(0,0,0));
// //  for(i=0;i<65;++i){
// //    mouse_wheel(NULL,-120, pt);
// //  }
//   on_strech_cad();
// }
// #else
////MOVE COMMAND
///STRECH COMMAND
////OFFSET COMMAND
//#endif

// void Idle_Command::on_copy_joint_cad()
// {
//     if(xor_.empty()){
//       step_ = SEL_S;
//       work_state_=WORK_SELECT;
//       return;
//     }
// 
//     if(work_state_ == WORK_SELECT_MAIN){
//       dlhml::push_back<Entity>(xor_, bk_);
//       cmd_flag_ = COPY_JOINT_E;
//       exit();
//       ok();
//     }
//     else{
//       destory_cad();
//       cad_ = new Move_Command;
//       step_ = COPY_JOINT_S;
//       iscopy_ = true;
//       command_line_output(c_str_base_pt);
//       work_state_=WORK_COMMAND;
//     }
// }

//void Idle_Command::on_copy_array(const Entity_Array& ary)
//{
//  if(xor_.empty()){
//    return;
//  }
//  Array_Command* ac = new Array_Command;
//  ac->set_array(ary);
//  destory_cad();
//  cad_ = ac;
//  iscopy_ = true;
//  cad_command();
//}

//bool Idle_Command::get_other_pt(int r_ent, int r_pt, Point& pt)
//{
//  if(r_ent < 0 || r_ent >= xor_.size()){
//    return false;
//  }
//  std::vector<Point> pts;
//  xor_[r_ent]->getdrag(pts);
//  if(pts.size() < 2){
//    return false;
//  }
//  if(r_pt < 0 || r_pt >= pts.size()){
//    return false;
//  }
//  int c_pt = 0;
//  if(r_pt==0){
//    c_pt = 1;
//  }else{
//    c_pt = r_pt-1;
//  }
//  pt = pts[c_pt];
//  return true;
//}

void Idle_Command::set_key_flag(UINT nFlags, const Point& ptc)
{
  Point pt=ptc;
  SHORT ret_alt = ::GetKeyState(VK_MENU);
  if(ret_alt<0){
    alt_flag_ = true;
  }
  else{
    alt_flag_ = false;
  }
  
	if(nFlags&MK_SHIFT){
		sel_flag_ = SSHIFT;
		copy_flag(false);
	}
	else if(nFlags&MK_CONTROL){
		sel_flag_ = SCTRL;
		copy_flag(true);
	}
	else{
		sel_flag_ = SNULL;
		copy_flag(false);
	}
}

void Idle_Command::left_button_down_p(UINT nFlags, const Point& ptc) 
{ 
	Point pt = ptc;
  Rect dim_rc;

	set_key_flag(nFlags, pt);

  switch(step_)
  {
  case SEL_S:
    if(xor_.size()<=DRAG_SEL_COUNT && find_redrc(pt)){
      Edit_Command * cmd = new Edit_Command;
      cmd->set_edit(red_ent_,red_pt_);
      destory_cad();
      cad_ = cmd;
      step_ = EDITE;
			type(EDIT);
			iscopy_ = false;
      select_blue_frame(*xor_[0]);
    }
    else{
      get_rect(pt, sel_rc_);
      is_rcsel_ = false;
      if(!select_entity()){
        step_ = SEL_E;
      }
    }
    begin_ = end_ = pt;
    copy_flag(false);
    break;
  case SEL_E:
    end_ = pt;
    is_rcsel_ = true;
    sel_rc_.setdata(begin_,end_);
    xor_shirr_rect();
    select_entity();
    begin_ = pt;
    step_ = SEL_S;
    break;
  case DRAGS:
    begin_ = end_ = pt;
//		//TRACE_OUT("case DRAGS:\n, begin:\t%f\t,%f",begin_.x, begin_.y);
    step_ = cad_&&cad_->is_there_temp() ? DRAGT : DRAGE;
    if(cad_){
      command_line_output(cad_->endpt_cmd_out());
    }
		if(cad_&&type()==COPY){
			clipper();
		}
    break;
  case EDITE:
    end_ = pt;
    cad_command();
    begin_ = end_ = pt;  
    scene_.invalidate();
    step_ = cad_ ? EDITE : SEL_S ;
    //iscopy_ = false;
    exit();
    break;
  case DRAGT:
		temp_ = pt;
    step_ = DRAGE ;
		xor_shirr_temp(true);
    break;
  case DRAGE:
  case BLOCK_FOCUS:
    end_ = pt;
    cad_command();
    end_ = pt;  
		if(!cad_ || !cad_->is_keep_begin()){
			begin_ = end_;
		}
    scene_.invalidate();
    step_ = cad_ ? DRAGE : SEL_S ;
		if(!cad_){
			step_ = SEL_S;
		}else if(cad_->is_reset_begin()){
			step_ = DRAGS;
		}else{
			step_ = DRAGE;
		}
    //iscopy_ = false;
    //block_mgr();
		exit();
    break;
  case INSER_BLOCK:
    on_insert(pt, insert_);
    break;
  case INSER_MULTI_BLOCK:
    insert(pt, inserts_, insert_focus_);
    break;
  case ADD_DIM:
    end_ = pt;
    cad_command();
    begin_ = end_ = pt;  
    scene_.invalidate();
    //on_add_dim_cad();
    break;
  case DEL_DIM:
    end_ = pt;
    get_rect(pt,dim_rc);
    if(cad_){
      ((Del_Dim_Command*)cad_)->set_rect(dim_rc);
    }
    cad_command();
    begin_ = end_ = pt;  
    scene_.invalidate();
    //on_del_dim_cad();
    break;
  case RE0_DIM:
    end_ = pt;
    get_rect(pt,dim_rc);
    if(cad_){
      ((Re0_Dim_Command*)cad_)->set_rect(dim_rc);
    }
    cad_command();
    begin_ = end_ = pt;  
    scene_.invalidate();
    //on_re0_dim_cad();
    break;
  case FORMAT_DIM_BASE:
  case LAYOUT_DIM_LINE:
  case MOVE_DIM_LINE:
    end_ = pt;
    cad_command();
    begin_ = end_ = pt;  
    scene_.invalidate();
    break;
  case VMOVE_S:
    get_rect(pt, sel_rc_);
    is_rcsel_ = false;
    if(!select_entity()){
      step_ = VMOVE_S;
    }else{
      on_vmove_line();
    }
    break;
  }
  set(pt);
}



//void Idle_Command::on_insert(Entity * xor_it, const std::vector<Float>& dis, Entity * symbol, int side)
//{
//  if(xor_.empty()){
//    start_select();
//    return;    
//  }
//  iscopy_ = true;
//  db_.push_back(symbol);
//  begin_=end_=Point(0,0);
//  destory_cad();
//  Mulit_Insert_Command * ic = new Mulit_Insert_Command;
//  ic->set_symbol(symbol);
//  ic->set_dis(&dis);
//  ic->set_side(side);
//  ic->set_xor_it(xor_it);
//  cad_ = ic;
//  cad_command();
//
//}

static Point middle(Entity* e1, Entity* e2)
{
	Point st1, ed1, st2, ed2;
	dlhml::get(e1, st1, ed1);
	dlhml::get(e2, st2, ed2);
	Float it_dis = st1.distanceto2d(st2);
	Float min_dis = it_dis;
	Point myresult = (st1+st2) / 2;
//	if(MoreThen(min_dis, it_dis)){
//		min_dis = it_dis;
//		myresult = (st1+ed1) / 2;
//	}
	it_dis = st1.distanceto2d(ed2);
	if(MoreThen(min_dis, it_dis)){
		min_dis = it_dis;
		myresult = (st1+ed2) / 2;
	}
	it_dis = ed1.distanceto2d(st2);
	if(MoreThen(min_dis, it_dis)){
		min_dis = it_dis;
		myresult = (ed1+st2) / 2;
	}
	it_dis = ed1.distanceto2d(ed2);
	if(MoreThen(min_dis, it_dis)){
		min_dis = it_dis;
		myresult = (ed1+ed2) / 2;
	}
	return myresult;
}

static bool intersect(const std::vector<Entity*>& es, Point& cross)
{
	if(es.size() < 2){
		return false;	
	}
  bool is_intersect=false;
  std::vector<Point> pts;
  int i=0;    
  for(i=0; i<es.size(); i++){
    es[i]->intersect(*(es[(i+1)%es.size()]), pts);
    if(!pts.empty()){
			cross = pts[0];
      is_intersect=true;
      break;
    }
  }
	return is_intersect;
}

//void Idle_Command::on_insert(Entity * symbol, int select_count)
//{
//  insert_= symbol;
//  db_.push_back(insert_);
//  if(xor_.empty()){
//    step_  = SEL_S;
//    work_state_=WORK_SELECT;
//    command_line_output("Specify the memberes.");
//    //cmd_flag_ = INSERT_JOINT_BY_COUNT;
//    //select_count_=select_count;
//    return;    
//  }
//  //cmd_flag_ = 0;
//  if(xor_.size() == 1){
//    step_  = INSER_BLOCK;
//    command_line_output("Specify a point.");
//    //cross_cursor_=true;
//    work_state_=WORK_COMMAND;
//    return;
//  }
//  bool is_intersect=false;
//  std::vector<Point> pts;
//  int i=0;
//  for(i=0; i<xor_.size(); i++){
//    if(xor_[i]->intersect(*(xor_[(i+1)%xor_.size()]), pts)){
//      on_insert(pts[0], symbol);
//      is_intersect=true;
//      break;
//    }
//  }
//  if(!is_intersect){
//    step_  = INSER_BLOCK;
//    command_line_output("Specify a point.");
//    //cross_cursor_=true;
//    work_state_=WORK_COMMAND;
//    return;
//  }
//  xor_draw(xor_,true);
//  draw_red_rect(true);
//  select(xor_,false);
//  xor_draw(xor_,true);
//  xor_.clear();
//}

//void Idle_Command::add_group_p(const Point& pt)
//{
//  Entity * main_e = xor_.front();
//  std::string group_name = main_e->group();
//  if(group_name.empty()){
//    const int pt_format_buf_size = 128;
//	  char buf[pt_format_buf_size];
//	  int len = sprintf(buf, "%d\0", main_e->entity_id().entity_id());
//    group_name = buf;
//  }
//  int i=0;
//  for(i=0; i<xor_.size(); i++){
//    xor_[i]->group(group_name.c_str());
//  }
//  erasexor(main_e);
//  push_xor(main_e);
//  //command_line_output("main member.");
//  cmd_flag_ = ADD_GROUP_S;
//  exit();
//  on_cancel();
//}
//void Idle_Command::add_group_p(const Point& pt)
//{
//  get_rect(pt, sel_rc_);
//  is_rcsel_ = false;
//  sel_flag_ = SSHIFT;
//  Entity* main_e = select_entity();
//  if(!main_e){
//    return;
//  }
//  std::string group_name = main_e->group();
//  if(group_name.empty()){
//    const int pt_format_buf_size = 128;
//	  char buf[pt_format_buf_size];
//	  int len = sprintf(buf, "%d\0", main_e->entity_id().entity_id());
//    group_name = buf;
//  }
//  int i=0;
//  for(i=0; i<xor_.size(); i++){
//    xor_[i]->group(group_name.c_str());
//  }
//  erasexor(main_e);
//  push_xor(main_e);
//  //command_line_output("main member.");
//  cmd_flag_ = ADD_GROUP_S;
//  exit();
//  on_cancel();
//}


bool Idle_Command::find_redrc(Point& pt)
{
  Rect rc;
  std::vector<Point> pts;
  int e=0, i=0; //e:实体迭代器, i:点迭代器
  for(e=0; e<xor_.size(); e++){
    pts.clear();
    xor_[e]->getdrag(pts);
    for(i=0; i<pts.size(); i++){
      get_rect(pts[i], rc);
      if(pt.envelop(rc)){
        red_ent_ = e;
        red_pt_  = i;
        pt = pts[i];
        return true;
      }
    }
  }
  return false;
}
bool Idle_Command::find_redrc(const Point& pt)
{
  Point ptd = pt;
  return find_redrc(ptd);
}
void Idle_Command::push_xor(const std::vector<Entity*>& es)
{
	int i=0;
	for(i=0; i<es.size(); ++i){
		if(!es[i]){
			continue;
		}
		push_xor(es[i]);
	}
}
void Idle_Command::erasexor(const std::vector<Entity*>& es)
{
	int i=0;
	for(i=0; i<es.size(); ++i){
		if(!es[i]){
			continue;
		}
		erasexor(es[i]);
	}
}

void Idle_Command::select_pt(Entity * e)
{
	if(!e){
		return;
	}
	if(!e->selected()){
		return;
	}
  std::vector<Point> pts;
  e->getstrech(pts);
  int i=0;
  for(i=0;i<pts.size();i++){
    if(pts[i].envelop(sel_rc_)){
      pts[i].selected(true);
    }
    else{
			////原来被选中的点，不取消
      //pts[i].selected(false);
    }
  }
  e->setstrech(pts);
}

void Idle_Command::clearxor_p()
{
	//TRACE_OUT("\nIdle_Command::clearxor_p()\n");
	clearxor();
}

void Idle_Command::clear_selected()
{
	dlhml::select(xor_, false);
	xor_.clear();
}
void Idle_Command::clearxor()
{
	//TRACE_OUT("\nIdle_Command::clearxor()\n");
  ////本就没有选中的，无需任何操作
  if(xor_.empty()){
    return;
  }
	remember_xor();
	dlhml::select(xor_, false);
	xor_.clear();
	scene_.invalidate();
}

void Idle_Command::push_xor(Entity * e)
{
  if(!e){
    return;
  }
  if(e->selected()){
    return;
  }
//   std::vector<Entity*>::iterator it=NULL;
//   it = find(e, xor_);
//   if(it){
// 		return;
//   }
	e->xor_draw(get_paint());
	e->selected(true);
	xor_.push_back(e);
	e->xor_draw(get_paint());
	////选中点
	if(xor_.size() <= DRAG_SEL_COUNT){
//		select_entity使用xor_entity选择实体，在其中已经选点了。
// 		if(is_rcsel_){
// 			select_pt(e);
// 		}
		draw_red_rect(e, true);
	}


	//   std::vector<Point> pts;
//   e->getstrech(pts);
//   int i=0;
//   for(i=0;i<pts.size();i++){
//     if(pts[i].envelop(sel_rc_)){
//       pts[i].selected(true);
//     }
//     else{
//       //pts[i].selected(false);
//     }
//   }
//   e->setstrech(pts);

//  if(xor_.size()==1){
//    draw_red_rect(e, false);
//  }
//  else if(xor_.size()==2){
//    draw_red_rect(xor_[0], true);
//  }
}
void Idle_Command::erasexor(Entity * e)
{
  if(!e->selected()){
    return;
  }
  std::vector<Entity*>::iterator it=NULL;
  it = find(e, xor_);
  if(!it){
    return;
  }
	if(xor_.size() <= DRAG_SEL_COUNT){
		draw_red_rect(e, true);
	}

	e->xor_draw(get_paint());
  e->selected(false);
  xor_.erase(it);
  e->xor_draw(get_paint());
  //   ////选中点
  //   std::vector<Point> pts;
  //   e->getstrech(pts);
  //   int i=0;
  //   for(i=0;i<pts.size();i++){
  //     pts[i].selected(false);
  //   }
  //   e->setstrech(pts);
	
}
//void Idle_Command::xor_entity(Entity* ent)
//{
//	std::vector<Entity*>::iterator pos = find(ent,xor_);
//	if(pos == NULL){
//    push_xor(ent);
//    // 		ent->selected(true);
//    // 		xor_.push_back(ent);
//    // 		ent->draw(get_paint());
//    // 		draw_red_rect(ent,true);
//	}
//	else if(sel_flag_ == SSHIFT){
//    //erasexor(ent);
//    push_xor(ent);
//    //no action
//	}
//	else if(sel_flag_ == SCTRL){
//    erasexor(ent);
//    // 		ent->xor_draw(get_paint());
//    // 		ent->selected(false);
//    // 		xor_.erase(pos);
//    // 		ent->draw(get_paint());
//    // 		draw_red_rect(ent, true);
//	}
//  ////执行到此，不会出现SNULL
//	else if(sel_flag_ == SNULL){
//		//no action
//	}
//}

void Idle_Command::xor_entity(Entity* ent)
{
	std::vector<Entity*>::iterator pos = find(ent,xor_);
	if(pos == NULL){
		ent->selected(true);
		xor_.push_back(ent);
		select_pt(ent);
    //push_xor(ent);
//		TRACE_OUT("\n#### strech-cad\n");
		trace_seled_pt(xor_);
	}
	else if(sel_flag_ == SSHIFT){
    //erasexor(ent);
    //push_xor(ent);
		//select_pt(ent);
		//draw_pt(ent, true);
    //no action
	}
	else if(sel_flag_ == SCTRL){
		
		//std::vector<Entity*>::iterator it=NULL;
		//it = find(ent, xor_);
		//if(!it){
		//	return;
		//}
		ent->selected(false);
		select_pt(ent);
		xor_.erase(pos);
		//erasexor(ent);
	}
  ////执行到此，不会出现SNULL
	else if(sel_flag_ == SNULL){
		//no action
	}
}

void Idle_Command::get_same_group(std::vector<Entity*>& groups, const Entity * ent)
{
	std::string group_name = ent->group();
	if(group_name.empty()){
		groups.push_back(const_cast<Entity*>(ent));
		return;
	}
	entity_iterator group_it = scene_.database()->entity_begin();
	for(; group_it!=scene_.database()->entity_end();++group_it){
		Entity * group_ent = *group_it;
		if(!group_ent){
			continue;
		}
		if(strcmp(group_name.c_str(),group_ent->group().c_str())==0){
			groups.push_back(group_ent);
		}
	}
}

//alt_flag_ && 
Entity* Idle_Command::select_entity()
{
	remember_xor();
  if(sel_flag_ == SNULL){
		clearxor_p();
//     xor_draw(xor_);
// 		draw_red_rect(true);
//     select(xor_, false);
//     draw(xor_);
//     xor_.clear();
  }
  Entity* seled = NULL;
	entity_iterator iter = scene_.database()->entity_end();
  bool isloop = scene_.database()->entity_end()!=scene_.database()->entity_begin();
	while(isloop){
    iter--;
		Entity * ent = *iter;
    if(is_selected(ent)){
      if(alt_flag_){
				bool ent_sel = ent->selected();
				std::vector<Entity*> gp_es;
				get_same_group(gp_es, ent);
				//push_xor(gp_es);

				(!ent_sel) ?	push_xor(gp_es) : erasexor(gp_es);

      }else{
        xor_entity(ent);
      }
      seled = *iter;
      if(!is_rcsel_){
        break;
      }
    }
    if(iter==scene_.database()->entity_begin()){
      break;
    }
	}
//  if(select_count_ >1){
//    if(cmd_flag_==INSERT_JOINT_BY_COUNT){
//      if(xor_.size() >= select_count_){
//        Entity* symble = insert_->clone();
//        on_insert(symble,select_count_);
//      }
//    }
//  }
  begin_=end_;
  scene_.invalidate();
	selected_p();		////通知子类，选择结束
  assert(trace_xor());
  return seled;
}

//old//alt_flag_ && 
//Entity* Idle_Command::select_entity()
//{
//  if(sel_flag_ == SNULL){
//    xor_draw(xor_);
//		draw_red_rect(true);
//    select(xor_, false);
//    draw(xor_);
//    xor_.clear();
//  }
//  Entity* seled = NULL;
//	entity_iterator iter = scene_.database()->entity_begin();
//	for(; iter!=scene_.database()->entity_end();++iter){
//		Entity * ent = *iter;
//    if(is_selected(ent)){
//      std::string group_name = ent->group();
//      if(alt_flag_ && !group_name.empty()){
//        bool ent_sel = ent->selected();
//	      entity_iterator group_it = scene_.database()->entity_begin();
//	      for(; group_it!=scene_.database()->entity_end();++group_it){
//		      Entity * group_ent = *group_it;
//          if(strcmp(group_name.c_str(),group_ent->group())==0){
//            if(ent_sel){
//              push_xor(group_ent);
//            }
//            else{
//              erasexor(group_ent);
//            }
//            xor_entity(group_ent);
//          }
//        }
//      }else{
//        xor_entity(ent);
//      }
//      seled = *iter;
//      if(!is_rcsel_){
//        break;
//      }
//    }
//	}
////  if(select_count_ >1){
////    if(cmd_flag_==INSERT_JOINT_BY_COUNT){
////      if(xor_.size() >= select_count_){
////        Entity* symble = insert_->clone();
////        on_insert(symble,select_count_);
////      }
////    }
////  }
//  begin_=end_;
//  scene_.invalidate();
//  return seled;
//}

bool Idle_Command::adjust_blue_flag(Entity * e)const
{
	bool isblue = e->isa(MY_RUNTIME_CLASS(Group_Ents)) ? true : false;
	return (isblue == blue_frame_);
}

static void trace_ent(const Entity * e)
{
  TRACE_OUT("idle::xor ptr: %d\n", e);
  TRACE_OUT("idle::xor id : %d\n", e->entity_id().entity_id());
}

bool Idle_Command::trace_xor()const
{
  int n=xor_.size();
  int i=0;
  for(i=0; i<n; ++i){
    trace_ent(xor_[i]);
  }
  return true;
}


bool Idle_Command::is_selected(Entity* ent)
{
  if(!ent->visibility()){
		return false;
  }
  if(if_lock(ent)){
		return false;
  }

  if(if_cross_ent(ent) && adjust_blue_flag(ent)){
		return true;
  }
	return false;
}

bool Idle_Command::if_lock(Entity* ent)
{
//  if(strcmp(ent->layer_name(), "layer_input_entities") == 0){
//    return true;
//  }
//  return false;

	Layer* layer = NULL;
	bool if_have = scene_.database()->get_layer(layer,ent->layer_name());
	if(if_have && layer != NULL){
		if(layer->lock()){
			return true;
    }
	}
	return false;	
}

bool Idle_Command::if_cross_ent(Entity* ent)
{
  if(!ent){
    return false;
  }
  Rect box = ent->box2d();
  box.update();
  sel_rc_.update();
  if(is_disjoint(sel_rc_, box)){
    return false;
  }
//   if(!sel_rc_.intersect(box)){
//     return false;
//   }

  Point& set_pt_ = begin_;
  Point& up_pt_  = end_  ;
	if(LessThen(set_pt_.x, up_pt_.x)){
		if(ent->envelop(sel_rc_)){
			return true;
		}
	}
  else{
		if(ent->envelop(sel_rc_) ||  ent->intersect(sel_rc_) ){
			return true;
		}
	}
	return false;
}

void Idle_Command::xor_shirr_temp(bool xor)
{
  Paint_Entity paint = get_paint();
	if(cad_ && cad_->cadtype()==ROTACMD && step_ == DRAGE){
		Line ln(begin_,temp_);
		ln.color_index(2);
		paint.draw_line(ln,xor);
	}

}

void Idle_Command::xor_shirr_line(bool xor)
{
  Paint_Entity paint = get_paint();
  Line ln(begin_,end_);
  ln.color(RGB(200,255,100));
  //ln.line_style("dot");
  //ln.color_index(3);
  paint.draw_line(ln,xor);
  //ln.xor_draw(paint);
}

void Idle_Command::xor_shirr_rect(bool xor)
{
  if(begin_ == end_){
    return;
  }

  //   afc::Date_Time dt;
  //   TRACE_OUT("idle1-- %s\n", dt.local_time().c_str());

	Painter* painter = scene_.get_painter();
	Paint_Entity paint(scene_,*painter);
  Point& set_pt_ = begin_;
  Point& up_pt_  = end_  ;


	Line line;
  if(set_pt_.x > up_pt_.x){
    line.line_style("dot");
    //line.color_index(1);
    //xor=false;
  }
	line.setdata(Point(set_pt_.x,set_pt_.y),Point(up_pt_.x,set_pt_.y));
	paint.draw_line(line, xor);
  //line.xor_draw(paint);
	line.setdata(Point(up_pt_.x,set_pt_.y),Point(up_pt_.x,up_pt_.y));
	paint.draw_line(line, xor);
  //line.xor_draw(paint);
	line.setdata(Point(up_pt_.x,up_pt_.y),Point(set_pt_.x,up_pt_.y));
	paint.draw_line(line, xor);
  //line.xor_draw(paint);
	line.setdata(Point(set_pt_.x,up_pt_.y),Point(set_pt_.x,set_pt_.y));
	paint.draw_line(line, xor);
  //line.xor_draw(paint);
  //   TRACE_OUT("idle2-- %s\n\n", dt.local_time().c_str());
}

//  在xor_中查看是否与ent(xor_中的元素)的pt相同位置的点
//  ent必须是xor_中元素
//  如果有相同的点，重复画红框
bool Idle_Command::is_there_superposition(const Point& pt, Entity * ent, int pt_index)
{
  if(!ent){
    return false;
  }
  Rect rc;
  std::vector<Point> pts;
  std::vector<Entity*>::iterator it=xor_.begin();
  int i=0; //e:实体迭代器, i:点迭代器
  for(; (*it)!=ent&&it!=xor_.end(); it++){
    pts.clear();
    (*it)->getdrag(pts);
    for(i=0; i<pts.size(); i++){
      if(pt == pts[i]){
        return true;
      }
    }
  }
  pts.clear();
  ent->getdrag(pts);
  for(i=0; i<pt_index&&i<pts.size(); i++){
    if(pt == pts[i]){
      return true;
    }
  }
  return false;
}

void Idle_Command::draw_pt(Entity * enitiy, bool xor)
{
// 	TRACE_OUT("Idle_Command::draw_pt(Entity*)\n");
  if(!enitiy){
    return;
  }
	
  std::vector<Point> pts;
  enitiy->getstrech(pts);
  Rect rc; 
  Paint_Entity paint = get_paint();
  int i=0;
  for(i=0; i<pts.size(); i++){
    if(is_there_superposition(pts[i], enitiy, i)){
      continue;
    }
		if(!pts[i].selected()){
			continue;
		}
    get_rect(pts[i], rc, STRECH_RC);
    rc.color_index(3);
    rc.selected(true);
    paint.draw_rect(rc,xor);
  }
	
}



void Idle_Command::draw_red_rect(Entity * enitiy, bool xor)
{
  if(!enitiy){
    return;
  }

  std::vector<Point> pts;
  enitiy->getdrag(pts);
  Rect rc; 
  Paint_Entity paint = get_paint();
  int i=0;
  for(i=0; i<pts.size(); i++){
    if(is_there_superposition(pts[i], enitiy, i)){
      continue;
    }
    get_rect(pts[i], rc);
    rc.color_index(3);
    rc.selected(false);
		if(xor_.size() <= DRAG_SEL_COUNT){
			paint.draw_rect(rc,xor);
		}
  }

	draw_pt(enitiy, xor);
}
// void Idle_Command::draw_red_rect(Entity * enitiy, bool xor)
// {
//   if(!enitiy){
//     return;
//   }
// 
//   std::vector<Point> pts;
//   enitiy->getdrag(pts);
//   Rect rc; 
//   //   if(pts.size()==1){
//   //     rc.selected(true);
//   //   }else{
//   //     rc.selected(false);
//   //   }
//   Paint_Entity paint = get_paint();
//   int i=0;
//   for(i=0; i<pts.size(); i++){
//     if(is_there_superposition(pts[i], enitiy, i)){
//       continue;
//     }
//     get_rect(pts[i], rc);
//     rc.color_index(3);
//     rc.selected(false);
//     paint.draw_rect(rc,xor);
//     if(pts[i].selected()){
//       get_rect(pts[i], rc, STRECH_RC);
//       rc.color_index(3);
//       rc.selected(true);
//       paint.draw_rect(rc,xor);
//     }
//   }
// }

void Idle_Command::draw_red_rect(bool xor)
{
  ////选中实体过多时，不画选择框
  if(xor_.empty()){
    return;
  }
  if(xor_.size() <=DRAG_SEL_COUNT){
    int i=0;
    for(i=0; i<xor_.size(); i++){
		  draw_red_rect(xor_[i],xor);
	  }
    //draw_red_rect(xor_[0],xor);
    return;
  }
//  int i=0;
//  for(i=0; i<xor_.size(); i++){
//		draw_red_rect(xor_[i],xor);
//	}
}

//****prop****
void Idle_Command::on_property_cad()
{
  if(xor_.empty()){
    step_ = SEL_S;
    //work_state_=WORK_SELECT;
    return;
  }
  begin_=end_=Point(0,0);
	type(PROP);
	iscopy_ = false;
  select_blue_frame(*xor_[0]);

	create_to_old();
	dlhml::copy(xor_, cc_->bk_);
	copy_bk(xor_, cc_->bk_);
	attach_cc();
  scene_.idle_command();
}

void Idle_Command::pop_property(Entity * hit)
{
//	TRACE_OUT("\nIdle_Command::pop_property(Entity * hit)\n");
	Visitor * v = scene_.get_vistor();
	assert(v && "Idle_Command::pop_property(Entity * hit)");
  if(hit){
    hit->visit(*v);
  }else if(!xor_.empty()){
		xor_.front()->visit(*v);
  }else{
//		TRACE_OUT("Can't pop it(No hit, no xor).");
	}
  step_ = SEL_S;
//edit_attribute();
}

void Idle_Command::left_button_dblclk_p(UINT nFlags, const Point& pt)
{
	if(blue_frame_){
		return;
	}

	////如果不是选择（如击中拖拽框）
  if(step_!= SEL_S && step_!=SEL_E){
		step_ = SEL_S;
		destory_cad();
    //return;
  }
  if(cad_){
    return;
  }

  get_rect(pt, sel_rc_);
  is_rcsel_ = true;
  Entity* db_seled = select_entity();
  step_ = SEL_S;

	pop_property(db_seled);

//   if(xor_.empty()){
//     return;
//   }
// 
//   if(db_seled){
//     db_seled->visit(*scene_.get_vistor());
//   }else{
// 		xor_.front()->visit(*scene_.get_vistor());
//     //edit_attribute();
//   }
//    
//   step_ = SEL_S;
}

//void Idle_Command::left_button_dblclk_p(UINT nFlags, const Point& pt)
//{
//  if(step_ != SEL_S){
//    return;
//  }
//
//  get_rect(pt, sel_rc_);
//  is_rcsel_ = true;
//  Entity* db_seled = select_entity();
//  step_ = SEL_S;
//
//  if(db_seled){
//  }
//  else if(!xor_.empty()){
//    db_seled = xor_.front();
//  }else{
//    return;
//  }
//
//
//  create_to_old();
//  if(!cc_){
//    return;
//  }
//  copy(xor_, cc_->bk_);
//
//  db_seled->visit(*scene_.get_vistor());
//    
//  execute_new();
//}

void Idle_Command::destory_cad()
{
  if(cad_){
    delete cad_;
    cad_ = NULL;
  }
}
void Idle_Command::destory_cc()
{
  if(cc_){
    delete cc_;
    cc_ = NULL;
  }
}
void Idle_Command::attach_cc()
{
	scene_.attach_command(cc_);
	cc_ = NULL;
}

//**CAD-COMMAND*********************************************
void Idle_Command::on_del()
{
  int aaa = xor_.size();
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
	type(DEL);
	iscopy_ = false;
	create_to_old();
	//...
	//destory(cc_->bk_);
	//cc_->bk_.clear();
	execute_new();
  on_ok();
}

void Idle_Command::on_copy_cad()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify objects.");
    return;
  }
  command_line_output(c_str_base_pt);
	command_line_output("Inupt the number of copy(default:1):");
  destory_cad();
  cad_ = new Move_Command;
  step_ = DRAGS;
	type(COPY);
  iscopy_ = true;
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

void Idle_Command::paste()
{
}

void Idle_Command::on_array_cad(const Entity_Array& ary)
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify objects.");
    return;
  }
  begin_=end_=Point(0,0);
	type(COPY);
  iscopy_ = true;
	copynum_= ary.row_num * ary.col_num -1;
  destory_cad();
	if(copynum_ == 0){
		////复制0个，等于不复制
		return;
	}
  Array_Command * ac = new Array_Command;
	ac->set_array(ary);
  cad_ = ac;
  select_blue_frame(*xor_[0]);
  cad_command();
	
}

void Idle_Command::on_move_cad()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  destory_cad();
  cad_ = new Move_Command;
  step_ = DRAGS;
	type(EDIT);
	iscopy_ = false;
  command_line_output(c_str_base_pt);
  work_state_=WORK_COMMAND;
  //repeat_or_ok_=false;
  select_blue_frame(*xor_[0]);
}

void Idle_Command::on_mirror_cad()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  destory_cad();
  cad_ = new Mirror_Command;
  step_ = DRAGS;
	type(EDIT);
	iscopy_ = false;
  command_line_output(c_str_base_pt);
  //cross_cursor_=true;
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

void Idle_Command::on_rotate_cad()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  destory_cad();
  cad_ = new Rotate_Command;
  step_ = DRAGS;
	type(EDIT);
	iscopy_ = false;
  command_line_output(c_str_base_pt);
  //cross_cursor_=true;
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

void Idle_Command::on_scale_cad()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  destory_cad();
  cad_ = new Scale_Command;
  step_ = DRAGS;
	type(EDIT);
	iscopy_ = false;
  command_line_output(c_str_base_pt);
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

//****Line-Command****
void Idle_Command::on_extend_cad()
{
	if(xor_.empty()){
		step_ = SEL_S;
		work_state_=WORK_SELECT;
		return;
	}
	destory_cad();
	cad_ = new Extend_Command;
	step_ = DRAGS;
	type(EDIT);
	iscopy_ = false;
	command_line_output(c_str_base_pt);
	work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

void Idle_Command::on_trim_cad()
{
	if(xor_.empty()){
		step_ = SEL_S;
		work_state_=WORK_SELECT;
		return;
	}
	destory_cad();
	cad_ = new Trim_Command;
	step_ = DRAGS;
	type(EDIT);
	iscopy_ = false;
	command_line_output(c_str_base_pt);
	work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

void Idle_Command::on_break_cad(int num, double dis)
{
	if(xor_.empty()){
		step_ = SEL_S;
		work_state_=WORK_SELECT;
		return;
	}
	destory_cad();
	Break_Command * bcmd = new Break_Command;
	bcmd->setcur(this);
	bcmd->num(num);
	bcmd->dis(dis);
	cad_ = bcmd;
	//step_ = DRAGS;
	//*******
	type(ADD_DEL);
	iscopy_ = false;
	//********
	command_line_output(c_str_base_pt);
	work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);

	cad_command();
// 	scene_.invalidate();
// 	exit();
}

void Idle_Command::on_break_cad()
{
	if(xor_.empty()){
		step_ = SEL_S;
		work_state_=WORK_SELECT;
		return;
	}
	destory_cad();
	Break_Command * bcmd = new Break_Command;
	bcmd->setcur(this);
	cad_ = bcmd;
	step_ = DRAGS;
	//*******
	type(ADD_DEL);
	iscopy_ = false;
	//********
	command_line_output(c_str_base_pt);
	work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

void Idle_Command::on_offset_cad()
{
  if(xor_.size()!=1){
    command_line_output("Specify a object.");
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  
  Offset_Drag_Pt odve;
  if(!xor_.front()->visit(odve)){
    command_line_output("This object can't offseted, specify a object again.");
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  
  destory_cad();
  cad_ = new Offset_Command;
  cad_->set_xor(&(xor_));
  begin_=end_=odve.get_drag_pt();
  step_ = DRAGE;
	type(COPY);
  iscopy_ = true;
  command_line_output("Specify the point or distance.");
  work_state_=WORK_COMMAND;
  
  select_blue_frame(*xor_[0]);
}
void Idle_Command::on_vmove_line()
{
	//NOOK on_vmove_line offset ?
  if(xor_.size()!=1){
    command_line_output("Specify a line.");
    step_ = VMOVE_S;
    work_state_=WORK_SELECT;
    return;
  }
  std::vector<Point> pts;
  xor_.back()->getdrag(pts);
  if(pts.size()<2){
    return;
  }
  Line ln(pts.front(),pts.back());
  
  destory_cad();
  cad_ = new Vmove_Line_Command;
  cad_->set_xor(&(xor_));
  begin_=end_=ln.middle();
  step_ = DRAGE;
	type(COPY);
  iscopy_ = true;
  command_line_output("Specify the point or distance.");
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

void Idle_Command::on_strech_cad()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  destory_cad();
  cad_ = new Strech_Command;
  step_ = DRAGS;
	type(EDIT);
	iscopy_ = false;
  command_line_output(c_str_base_pt);
  work_state_=WORK_COMMAND;
  //repeat_or_ok_=false;
  
  select_blue_frame(*xor_[0]);
}

//****Multi-entities****
void Idle_Command::on_make_block()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  destory_cad();
  cad_ = new Block_Command;
	type(ADD_DEL);
	iscopy_ = false;
  step_ = BLOCK_FOCUS;
  cmd_flag_ = BLOCK_FOCUS;
  command_line_output("Specify the focus.");
  work_state_=WORK_COMMAND;
  //repeat_or_ok_=false;
}

void Idle_Command::on_split_block()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    return;
  }
  destory_cad();
  cad_ = new Split_Block_Command;
	type(ADD_DEL);
	iscopy_ = false;
  cad_command();
  command_line_output("Split block have done.");
  work_state_=WORK_IDLE;
}

void Idle_Command::on_add_group()
{
  if(xor_.empty()){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify the main member and sub-memberes.");
    return;
  }
  if(xor_.size() == 1){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify sub-memberes.");
    return;
  }
  
  destory_cad();
  cad_ = new Unite_Group_Command;
	type(EDIT);
	iscopy_ = false;

  cad_command();
  //bk_.clear();
  //dlhml::push_back<Entity>(cc_->bk_, bk_);
	////命令结束，通知子类
  cmd_flag_ = ADD_GROUP_S;
  exit();
  command_line_output("Unite group have done.");
  on_cancel();
}

//****Insert****
void Idle_Command::on_insert(Entity * symbol, int select_count)
{
	////计算点，转调on_insert(pt,symbol);
  if(xor_.empty()){
    start_select();
		bk_.push_back(symbol);////只是为了析构时释放内存
    return;    
  }
  insert_= symbol;
  if(xor_.size() == 1){
    step_  = INSER_BLOCK;
    command_line_output("Specify a point.");
    //cross_cursor_=true;
    work_state_=WORK_COMMAND;
    return;
  }
	
	////求交点
	Point cross;
	bool is_intersect = dlhml::intersect(xor_, cross);
	////如果没有交点，则取前两个实体的端点，取最近两点的中间
	if(!is_intersect){
		assert(xor_.size() >= 2);
		cross = dlhml::middle(xor_[0], xor_[1]);
		is_intersect = true;
	}
	////
	on_insert(cross, symbol);
	////
  if(!is_intersect){
    step_  = INSER_BLOCK;
    command_line_output("Specify a point.");
    //cross_cursor_=true;
    work_state_=WORK_COMMAND;
    return;
  }
	clearxor_p();
//   xor_draw(xor_,true);
//   draw_red_rect(true);
//   select(xor_,false);
//   xor_draw(xor_,true);
//   xor_.clear();
}

void Idle_Command::on_insert(Entity* symbol)
{
	////用户指定点，转调on_insert(pt,symbol);
  insert_= symbol;
  //bk_.push_back(insert_);////只是为了析构时释放内存
  step_  = INSER_BLOCK;
  command_line_output("Specify a point.");
  //cross_cursor_=true;
  work_state_=WORK_COMMAND;
}

void Idle_Command::on_insert(const Point& pt, Entity * symbol)
{
//	TRACE_OUT("\nIdle_Command::on_insert(pt,symblo)\n");
	assert(symbol && "on_insert(const Point& pt, Entity * symbol)");
  iscopy_ = false;
	type(ADD);
	symbol->selected(false);
//	TRACE_OUT("Before push_back, bk_.size == %d\n", bk_.size());
	dlhml::push_back<Entity>(symbol, bk_);////只是为了析构时释放内存
//	TRACE_OUT("After push_back, bk_.size == %d\n", bk_.size());
  //bk_.push_back(symbol);
  begin_ = symbol->focus(); 
	end_=pt;
	select_blue_frame(pt);
  insert_p(symbol);
}
void Idle_Command::insert_p(const Entity * e)
{
  destory_cad();
  Insert_Command * ic = new Insert_Command;
  ic->set_insert(e);
  cad_ = ic;
  cad_command();
}

void Idle_Command::on_insert(Entity * xor_it, const std::vector<Float>& dis, Entity * symbol, int side)
{
	////不转调on_insert(pt,symbol);
  if(xor_.empty()){
    start_select();
		bk_.push_back(symbol);////只是为了析构时释放内存
    return;    
  }
	assert(symbol && "on_insert(const Point& pt, Entity * symbol)");
  iscopy_ = false;		////
	type(ADD);				////不转调on_insert(pt,symbol);
	symbol->selected(false);
	dlhml::push_back<Entity>(symbol, bk_);
  begin_=end_=Point(0,0);////Multi_Insert
  destory_cad();
  Mulit_Insert_Command * ic = new Mulit_Insert_Command;
  ic->set_symbol(symbol);
  ic->set_dis(&dis);
  ic->set_side(side);
  ic->set_xor_it(xor_it);
  cad_ = ic;
	select_blue_frame(*xor_[0]);
  cad_command();
	
}

void Idle_Command::insert(std::vector<Entity*>& symbol, const Point& focus)
{
	////转调insert(pt,<>symbol);
	inserts_ = symbol;
	insert_focus_ = focus;
  step_  = INSER_MULTI_BLOCK;
  command_line_output("Specify a point.");
  //cross_cursor_=true;
  work_state_=WORK_COMMAND;

}

void Idle_Command::insert(const Point& pt, 
													std::vector<Entity*>& symbol,
													const Point& focus)
{
	////不转调on_insert(pt,symbol);
	if(symbol.empty()){
		return;
	}
	
	iscopy_ = false;
	type(ADD);////不转调on_insert(pt,symbol);
	dlhml::select(symbol, false);
	//inserts_ = symbol;
	//insert_focus_ = focus;
	dlhml::push_back<Entity>(symbol, bk_);
	begin_= focus; 
	end_=pt;
	select_blue_frame(pt);
  destory_cad();
  Insert_Command * ic = new Insert_Command;
  ic->set_insert(symbol);
	ic->setcur(this);
  //ic->set_insert(e);
  cad_ = ic;
  cad_command();
}



//****Dim****
//  增加/打断直线标注
//  选择之后只需指定一个点
void Idle_Command::on_add_dim_cad()
{
  if(xor_.size() != 1 || xor_[0]->myclass()!=LINE_DIM_BLOCK){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify a line dimesion.");
    return;
  }
  begin_=end_=Point(0,0);
  destory_cad();
  cad_ = new Add_Dim_Command;
  step_ = ADD_DIM;                        //  直接指定终点
	type(EDIT);
	iscopy_ = false;
  command_line_output("Specify a point of dimesion.");
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

////删除/合并直线标注
////选择之后只需指定一个点
void Idle_Command::on_del_dim_cad()
{
  if(xor_.size() != 1 || xor_[0]->myclass()!=LINE_DIM_BLOCK){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify a line dimesion.");
    return;
  }
  begin_=end_=Point(0,0);
  destory_cad();
  cad_ = new Del_Dim_Command;
  step_ = DEL_DIM;                        //  直接指定终点(删除延长线)
	type(EDIT);
	iscopy_ = false;
  command_line_output("Specify a extend line of dimesion.");
  work_state_=WORK_COMMAND;
}

//  重设直线标注0点
//  选择之后只需指定一个点
void Idle_Command::on_re0_dim_cad()
{
  if(xor_.size() != 1 || xor_[0]->myclass()!=LINE_DIM_BLOCK){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify a line dimesion.");
    return;
  }
  begin_=end_=Point(0,0);
  destory_cad();
  cad_ = new Re0_Dim_Command;
  step_ = RE0_DIM;                        //  直接指定终点
	type(EDIT);
	iscopy_ = false;
  command_line_output("Specify new 0 point of dimesion.");
  work_state_=WORK_COMMAND;
}

////删除/合并直线标注
////选择之后只需指定一个点
void Idle_Command::on_layout_dim_base_cad()
{
  if(xor_.size() != 1 || xor_[0]->myclass()!=LINE_DIM_BLOCK){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify a line dimesion.");
    return;
  }
  begin_=end_=Point(0,0);
  destory_cad();
  cad_ = new Layout_Dim_Base_Command;
  step_ = FORMAT_DIM_BASE;                        //  直接指定终点(删除延长线)
	type(EDIT);
	iscopy_ = false;
  command_line_output("Specify a point of dimesion.");
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

////删除/合并直线标注
////选择之后只需指定一个点
void Idle_Command::on_layout_dim_line_cad()
{
  if(xor_.size() != 1 || xor_[0]->myclass()!=LINE_DIM_BLOCK){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify a line dimesion.");
    return;
  }
  begin_=end_=Point(0,0);
  destory_cad();
  cad_ = new Layout_Dim_Line_Command;
  step_ = LAYOUT_DIM_LINE;                        //  直接指定终点(删除延长线)
	type(EDIT);
	iscopy_ = false;
  command_line_output("Specify a point of dimesion.");
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

////删除/合并直线标注
////选择之后只需指定一个点
void Idle_Command::on_move_dim_line_cad()
{
  if(xor_.size() != 1 || xor_[0]->myclass()!=LINE_DIM_BLOCK){
    step_ = SEL_S;
    work_state_=WORK_SELECT;
    command_line_output("Specify a line dimesion.");
    return;
  }
  begin_=end_=Point(0,0);
  destory_cad();
  cad_ = new Move_Dim_Line_Command;
  step_ = DRAGS;                        //  直接指定终点(删除延长线)
	type(EDIT);
	iscopy_ = false;
  command_line_output("Specify a point of dimesion.");
  work_state_=WORK_COMMAND;
	
  select_blue_frame(*xor_[0]);
}

////记忆当前选中的实体集
void Idle_Command::remember_xor()
{
	//TRACE_OUT("\nIdle_Command::remember_xor()\n");
	if(xor_.empty()){
		return;
	}
	//TRACE_OUT("xor_.size() == %d\n", xor_.size());
	//TRACE_OUT("prexor_.size() == %d\n", prexor_.size());
	prexor_ = xor_;
	//TRACE_OUT("--\n", xor_.size());
	//TRACE_OUT("xor_.size() == %d\n", xor_.size());
	//TRACE_OUT("prexor_.size() == %d\n", prexor_.size());
}

////恢复选择上一次（记忆体内）的实体集
void Idle_Command::comeback_xor()
{
// 	TRACE_OUT("\nIdle_Command::comeback_xor()\n");
// 	TRACE_OUT("xor_.size() == %d\n", xor_.size());
// 	TRACE_OUT("prexor_.size() == %d\n", prexor_.size());
	if(prexor_.empty()){
		return;
	}
	//std::swap(xor_, prexor_);
	dlhml::select(xor_, false);
	xor_ = prexor_;
	dlhml::select(xor_, true);
	scene_.invalidate();
// 	TRACE_OUT("--\n", xor_.size());
// 	TRACE_OUT("xor_.size() == %d\n", xor_.size());
// 	TRACE_OUT("prexor_.size() == %d\n", prexor_.size());
}

// void Idle_Command::push_bk(Entity * e)
// {
// 	if(!e){
// 		return;
// 	}
// 	std::vector<Entity*>::iterator it=NULL;
// 	it = find(e, bk_);
// 	if(!it){
// 		return;
// 	}
// 	bk_.push_back(e);
// }
// 
// void Idle_Command::push_bk(const std::vector<Entity*>& es)
// {
// 	int i=0;
// 	for(i=0; i<es.size(); ++i){
// 		push_bk()
// 	}
// }

void Idle_Command::get_xor(std::vector<Entity*>& xor)const
{
	xor = xor_;
}
void Idle_Command::set_xor(const std::vector<Entity*>& xor)
{
	clearxor_p();
	xor_ = xor;
	dlhml::select(xor_, true);
	scene_.invalidate();
}


}//namespace
