#include "StdAfx.h"
#include "Create_Command.h"
#include "../object/Global.h"

#include "Cloud_Line.h"
#include "Line_Arrow.h"
#include "Normal.h"
#include "RArc.h"

#include "Scene_d.h"
#include "Entity_Calculate.h"
#include "Paint_Entity_Tools.h"
#include "Blue_Frame_Tools.h"

#include "../include/getrace.h"

namespace dlhml
{

//template<class T>
Create_Command::Create_Command(Scene& scene, Entity* org)
:Create_Entity(scene)
,mode_(AGAIN)
//,index_(0)
,org_(NULL)
,drag_(NULL)
MCT_INIT2("Create_Command")
{
//	TRACE_OUT("Create_Command::Create_Command(Scene& scene, Entity* org)\n");
	Create_Entity::type(Create_Entity::ADD);
  myclass_ = "Create_Command";
  work_state_=WORK_COMMAND;
  //adjust(true);
  if(org){
//		TRACE_OUT("clone org_\n");
    org_  = org->clone();
    ortho_= org->is_ortho();
    db_color = org->color_index();
    org_->selected(true);
    if(org_->isa(MY_RUNTIME_CLASS(Ln_Dim))){
      org_->selected(false);
    }
//		TRACE_OUT("clone drag_\n");
    drag_  = org_->clone();
  }
}

Create_Command::~Create_Command()
{
//	TRACE_OUT("Create_Command::~Create_Command()\n");
//	TRACE_OUT("destory org_\n");
	dlhml::destory(org_);	
//	TRACE_OUT("destory drag_\n");
	dlhml::destory(drag_);
}


//template<class T>
void Create_Command::mouse_move_p(UINT nFlags, const Point& pt)
{
  drag(pt);
}
//template<class T>
void Create_Command::drag(const Point& ptc)
{
  if(step_ == 0 || drag_ == NULL){
    return;
  }
  Point pt = ptc;
  drag_->xor_draw(get_paint());
  if(drag_->myclass() == LINE_DIM){
    Ln_Dim* lndim = (Ln_Dim*)drag_;
    Paint_Entity_Tools::dim_text_recal(*lndim);
  }
  set_cur_pt(drag_, pt);
  drag_->xor_draw(get_paint());
}

//template<class T>
void Create_Command::left_button_down_p(UINT nFlags, const Point& pt)
{
  set(pt);
}

void Create_Command::input_text(LPCTSTR txt)
{
  if(xor_.empty()){
    return;
  }
  //xor_.back()->txt_.text(txt);
  on_ok();
  scene_.create_entity(cloneme());
}
//template<class T>
void Create_Command::set(const Point& pt)
{
//	TRACE_OUT("Create_Command::set(const Point& ptc)\n");
  if(org_ == NULL){
    return;
  }
  if(step_ >= org_->pt_count()){
    return;
  }
//  Point pt = ptc;
  if(step_ < org_->pt_count()-1){
    begin_=end_=pt;
		set_cur_pt(org_,pt);
    if(org_->myclass() == LINE_DIM){
      Ln_Dim* lndim = (Ln_Dim*)org_;
      Paint_Entity_Tools::dim_text_recal(*lndim);
    }
	  step_++;
		//set_all_pt(drag_, pt);
		//TRACE_OUT("destory(drag_)\n");
    destory(drag_);
		//TRACE_OUT("drag_ = org_->clone()\n");
    drag_ = org_->clone();
  }
  else{
    //get_ortho_point(begin_, pt);
		set_cur_pt(org_,pt);
    if(org_->myclass() == LINE_DIM){
      Ln_Dim* lndim = (Ln_Dim*)org_;
      Paint_Entity_Tools::dim_text_recal(*lndim);
    }
		push_create_xor();
    set_all_pt(org_,pt);
	  if(mode_ == TEMP || mode_ == SINGLE){
      end_=pt;
		  step_ = 0;
      on_ok();
      if(org_->myclass() == LINE_DIM){
        if(bk_.empty()){
          return;
        }
        scene_.get_idle()->xor_.clear();
        scene_.get_idle()->xor_.push_back(bk_[0]);
        bk_[0]->selected(true);
        bk_[0]->draw(get_paint());
        scene_.add_dim_cad();
      }
      else{
        scene_.create_entity(cloneme());
        //  continue line
			  if(org_->isa(MY_RUNTIME_CLASS(Line)) || org_->isa(MY_RUNTIME_CLASS(Line_Arrow))){
          if(scene_.continue_line()){
				    scene_.left_button(NULL,pt);
          }
        }
      }
	  }	  
    else if(mode_ == AGAIN){
      end_=pt;
		  step_ = 0;
	  }
	  else{
      begin_=pt;
		  //step_ ++--;
	  }
  }
}

//template<class T>
void Create_Command::on_draw()
{
	//Create_Entity::on_draw();
	if(drag_){
	  drag_->xor_draw(get_paint());
	}
}



void Create_Command::output_temp()
{
  Entity* temp = xor_.back();
  double len2d= temp->length();
  Rect   temrc= temp->box2d();
  double x_dis= temrc.xmax()-temrc.xmin();
  double y_dis= temrc.ymax()-temrc.ymin();
	if(temp->isa(MY_RUNTIME_CLASS(Line))){
		Line * temln = static_cast<Line*>(temp);
		x_dis = fabs(temln->start().x - temln->end().x);
		y_dis = fabs(temln->start().y - temln->end().y);
	}

  const int pt_format_buf_size = 128;
	char buf[pt_format_buf_size];
	int len = sprintf(buf, "X:%.2f,  Y:%.2f,  L:%.2f\0", x_dis, y_dis, len2d);
  std::string str=buf;
  scene_.info_to_command_line(str.c_str(), true);
	xor_.back()->xor_draw(get_paint());// 
	dlhml::destory(xor_);
	needundo(false);
}

void Create_Command::dim_into_block()
{
  Ln_Dim* dim = (Ln_Dim*)(xor_[0]);
  Ln_Dim_Block * block = Ln_Dim_Block::create_me();
  block->push_back(dim);
  block->dim_line_radian(dim->dim_line_radian());
  bk_.push_back(block);
}

//template<class T>
void Create_Command::push_create_xor()
{
	//TRACE_OUT("Create_Command::push_create_xor()\n");
  if(org_ == NULL){
    return;
  }
	//TRACE_OUT("clone => xor\n");
  Entity* myent = org_->clone();
  xor_.push_back(myent);
}

////云线处理, 由于此时云线还未完成，所以未进入xor_，需额外加入
void Create_Command::cloud_line()
{
  if(org_->pt_count() == MAX_PT_COUNT){
		if(org_->isa(MY_RUNTIME_CLASS(Cloud_Line))){
			Cloud_Line * cl = static_cast<Cloud_Line*>(org_);
			std::vector<Point> pts;
			cl->getdata(pts);
			if(pts.size()<3){
				return;
			}
		}
		push_create_xor();
  }
}

//template<class T>
void Create_Command::on_ok()
{
	////云线处理
	cloud_line();
  ////误操作检验
	if(xor_.empty()){
		needundo(false);
    scene_.idle_command();
		return;
	}
  //  种子归0
  step_=0;
  set_all_pt(org_,Point(0,0,0));

	if(mode_ == TEMP){
		output_temp();
    return;
	}

  color(xor_,db_color);
	if(mode_ == SINGLE && xor_[0]->isa(MY_RUNTIME_CLASS(Ln_Dim))){
		dim_into_block();
	}else{
		dlhml::push_back<Entity>(xor_, bk_);
	}
// 	if(mode_ == SINGLE && xor_[0]->isa(MY_RUNTIME_CLASS(Ln_Dim))){
//     if(xor_[0]->myclass() == LINE_DIM){
// 			dim_into_block();
//     }else{
// 		  dlhml::push_back<Entity>(xor_, bk_);
//     }
// 	}
// 	else if(mode_ == AGAIN){
// 		dlhml::push_back<Entity>(xor_, bk_);
// 	}
// 	else if(mode_ == CONTINUE){
// 		dlhml::push_back<Entity>(xor_, bk_);
// 	}

  select(xor_,false);
	xor_.clear();
	//TRACE_OUT("on_ok()--destory(drag_)\n");
  destory(drag_);
  execute();
	scene_.invalidate();
  scene_.idle_command();
}


void Create_Command::on_cancel()
{
  needundo(false);
	destory(xor_);
  //on_ok();
  step_=0;
  set_all_pt(org_,Point(0,0,0));
  destory(drag_);
	scene_.invalidate();
	scene_.idle_command();
}

void Create_Command::idle_p()
{
	on_cancel();
}

//template<class T>
void Create_Command::set_cur_pt(Entity* ent, const Point& pt)
{
  std::vector<Point> pts;
  ent->getctrl(pts);
  int i=0;
  for(i=step_; i<pts.size(); i++){
    pts[i] = pt;
  }
  if(ent->pt_count() == MAX_PT_COUNT && step_ >= pts.size()){
    pts.push_back(pt);
  }
  ent->setctrl(pts);
  ent->set_step(step_);
}

void Create_Command::set_all_pt(Entity* ent, const Point& pt)
{
  std::vector<Point> pts;
  ent->getctrl(pts);
  int i=0;
  for(i=0; i<pts.size(); i++){
    pts[i] = pt;
  }
  ent->setctrl(pts);
}
                                        

void Create_Command::closeme()
{
  delete this;
}

Create_Entity* Create_Command::cloneme()
{
  Create_Command* cc = NULL;
  return cc;
}

}//namespace
