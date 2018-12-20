// Cmd_Mgr.cpp: implementation of the Cmd_Mgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cmd_Mgr_d.h"
#include "Create_Entity.h"
#include "Idle_Command.h"



#include <cassert>

#include "../include/getrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//zhong
namespace dlhml{
Cmd_Mgr::Cmd_Mgr()
:cur_(NULL)
,idle_(NULL)
MCT_INIT2("Cmd_Mgr")
{
//  noneed_undo_cmd_=0;
}

Cmd_Mgr::~Cmd_Mgr()
{
	clear();
  idle_->close();
}

void Cmd_Mgr::clear()
{
  close(cmds_);
  close(redo_cmds_);
	close(recycler_);
  close_cur();
}

void Cmd_Mgr::add_cmd(Create_Entity* c)
{
  if(cur_){
    if(cur_->needundo()){
      cmds_.push_back(cur_);
			assert(get_idle() && "Cmd_Mgr::add_cmd(Create_Entity* c)");
			if(cur_->type() != Create_Entity::PROP){
				////发送消息给Select_Steel类，要求制作model级命令链表
				get_idle()->cmd_scene_p();
			}
      close(redo_cmds_);
    }
    else{
      close_cur();
    }
  }
  if(c){
    cur_ = c;
  }
  else{
    cur_ = idle_;
  }
}

//  新idle必须存在。
//  原idle如果已经存在，清除掉，再接受新idle。
void Cmd_Mgr::set_idle(Idle_Command* idle)
{
	//TRACE_OUT("Cmd_Mgr::set_idle(Idle_Command* idle)");
  if(!idle){
    return;
  }
  close_cur();
  if(idle_){
    idle_->close();
    idle_=NULL;
  }
  idle_ = idle;
  cur_  = idle;
}

Idle_Command* Cmd_Mgr::get_idle() const
{
  return idle_;
}

void Cmd_Mgr::close(std::vector<Create_Entity*>& cmds)
{
  int i=0;
  for(i=0; i<cmds.size(); i++){
    cmds[i]->close();
  }
  cmds.clear();
}
 
void Cmd_Mgr::undo()
{
  if(!can_undo()){
    return;
  }
  Create_Entity* eee = cmds_.back();
  cmds_.back()->unexecute(); 
  redo_cmds_.push_back(cmds_.back());
  cmds_.pop_back();
}
void Cmd_Mgr::redo()
{ 
  if(!can_redo()){
    return;
  }
  redo_cmds_.back()->execute();
  cmds_.push_back(redo_cmds_.back());
  redo_cmds_.pop_back();
} 

 
bool Cmd_Mgr::can_undo()
{
  if(cur_!=idle_){
    return false;
  }
	return !cmds_.empty();
}
bool Cmd_Mgr::can_redo()
{
  if(cur_!=idle_){
    return false;
  }
	return !redo_cmds_.empty(); 
}
Create_Entity* Cmd_Mgr::current()
{
	assert(cur_ && "Cmd_Mgr::current()");
  return cur_;
}

void Cmd_Mgr::close_cur()
{
  if(cur_ && cur_ != idle_){
		recycler_.push_back(cur_);
    //cur_->close();
    cur_= idle_;
  }
}

//namespace
}
