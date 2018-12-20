#ifndef _cmd_mgr_h_
#define _cmd_mgr_h_
#include <list>
#include "geptr.h"
#include "Cmd.h"
namespace gelib{
class AFX_EXT_CLASS Cmd_Mgr{
	
	std::list<GEXY::CPtr<Cmd> > cmds_;
	std::list<GEXY::CPtr<Cmd> > redo_cmds_;
protected:
	~Cmd_Mgr() {}
public:
	
	void add_cmd(GEXY::CPtr<Cmd> c) {
		cmds_.push_back(c);
		redo_cmds_.clear();
	}
	void undo() { 
		cmds_.back()->unexecute(); 
		redo_cmds_.push_back(cmds_.back());
		cmds_.pop_back();}
	void redo() {
		redo_cmds_.back()->execute();
		cmds_.push_back(redo_cmds_.back());
		redo_cmds_.pop_back();
		}
	void clear() {
		cmds_.clear();
		redo_cmds_.clear();
		}
	bool can_undo() { return !cmds_.empty(); }
	bool can_redo() { return !redo_cmds_.empty(); }
};
}
#endif