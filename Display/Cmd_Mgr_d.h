
#ifndef _TIAN_DISPLAY_CMD_MGR_H_
#define _TIAN_DISPLAY_CMD_MGR_H_

#include "display_export.h"
#include <vector>

namespace dlhml{

class Create_Entity;
class Idle_Command;

class DISPLAY_API Cmd_Mgr  
{
public:
	Cmd_Mgr();
  void set_idle(Idle_Command* idle);
  Idle_Command* get_idle() const;

  ~Cmd_Mgr();
	void clear();

  void add_cmd(Create_Entity* c);
	void undo();
	void redo();
	bool can_undo();
	bool can_redo();

	Create_Entity* current();


private:
	std::vector<Create_Entity*> cmds_;
	std::vector<Create_Entity*> redo_cmds_;
	std::vector<Create_Entity*> recycler_;

  Create_Entity* cur_;
  Idle_Command * idle_;

  void close(std::vector<Create_Entity*>& cmds);
  void close_cur();
	
private:
	MCT_DEF
};
}//namespace
#endif//FILE
