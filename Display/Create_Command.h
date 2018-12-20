
#ifndef _CREATE_COMMAND_H_
#define _CREATE_COMMAND_H_

#include "Create_Entity.h"

namespace dlhml
{

////template<class T> 
class DISPLAY_API Create_Command : public Create_Entity
{
public:
  Create_Command(Scene& scene, Entity* org);
  void mode(MODE m){mode_=m;}

protected:
  virtual ~Create_Command();
  virtual void closeme();
  virtual Create_Entity* cloneme();

protected:
  virtual Entity * org_p()const{return org_;}

	virtual void idle_p();

private:
//  virtual void right_button_down_p(UINT nFlags, const Point& pt);
  virtual void left_button_down_p(UINT nFlags, const Point& pt);
  virtual void mouse_move_p(UINT nFlags, const Point& pt);
  virtual void drag(const Point& pt);
  virtual void set (const Point& pt);
  //virtual bool execute_p();
  //virtual bool unexecute_p();
  virtual void input_text(LPCTSTR txt);

private:
  virtual void on_draw();

private:
  virtual void on_ok();
  virtual void on_cancel();

private:

private:
  void set_cur_pt(Entity* ent, const Point& pt);
  void set_all_pt(Entity* ent, const Point& pt);
  //void push_clone_new(Entity * ent);
  void push_create_xor();
	void cloud_line();

private:
	void output_temp();
	void dim_into_block();

protected:
  MODE mode_;                 //  模式：重画、连续
  //int  iter_;               //  迭代：当前正在操作的xor
  Entity * org_;
  Entity * drag_;
  int      db_color;
public:
//  int index_;
	
private:
	MCT_DEF
};

/*
//template<class T>
Create_Command::Create_Command(Scene& scene, Entity* org)
:Create_Entity(scene)
,mode_(EXIT)
,org_(org)
,index_(0)
{
  push_create_xor();
}

//template<class T>
void Create_Command::mouse_move_p(UINT nFlags, const Point& pt)
{
  drag(pt);
}
//template<class T>
void Create_Command::drag(const Point& pt)
{
  xor_.back()->xor_draw(get_paint());
  set_cur_pt(xor_.back(), pt);
  xor_.back()->xor_draw(get_paint());
}

//template<class T>
void Create_Command::left_button_down_p(UINT nFlags, const Point& pt)
{
  setctrl(pt);
}
//template<class T>
void Create_Command::setctrl(const Point& pt)
{
  set_cur_pt(xor_.back(), pt);
  //
  step_++;
  if(step_ < xor_.back()->pt_count()){
    return;
  }
  step_=0;
  push_create_xor();
  //push_clone_new(xor_.back());
}

//template<class T>
void Create_Command::on_draw()
{
  int i=0;
  for(i=0; i<xor_.size(); i++){
    xor_[i]->draw(get_paint());
  }
}

//template<class T>
void Create_Command::on_ok()
{
//  int i=0;
//  for(i=0; i<xor_.size(); i++){
//    insert_to_db(*(xor_[i]));
//    new_.push_back(xor_[i]);
//  }
  push(xor_, new_);
  xor_.clear();
  execute_p();
  scene_.idle_command();
}

//template<class T>
bool Create_Command::execute_p()
{
  int i=0;
  for(i=0; i<old_.size(); i++){
    remove_from_db(*(old_[i]));
  }
  for(i=0; i<new_.size(); i++){
    insert_to_db(*(new_[i]));
  }
  scene_.invalidate();
  return true;
}

//template<class T>
bool Create_Command::unexecute_p()
{
  int i=0;
  for(i=0; i<new_.size(); i++){
    remove_from_db(*(new_[i]));
  }
  for(i=0; i<old_.size(); i++){
    insert_to_db(*(old_[i]));
  }
  scene_.invalidate();
  return true;
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
  ent->set(pts);
}

//template<class T>
void Create_Command::push_create_xor()
{
  //Entity* myent = T::create_me();
  Entity* myent = org_->clone();
  xor_.push_back(myent);
}
//template<class T>
void Create_Command::push_clone_new(Entity* ent)
{
  Entity* myent = ent->clone();
  new_.push_back(myent);
}
*/
}//namespace
#endif//FILE
