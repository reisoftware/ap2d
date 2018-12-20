#ifndef _CMD_TOOL_H_
#define _CMD_TOOL_H_
#include "Cmd.h"
#include "geptr.h"
#include <vector>
class CModel;
namespace gelib{
	template<class T>
		class Item_Add:public Cmd{
		T* t_;
		CModel& model_;
	public:
		Item_Add(T* t,CModel& model):t_(t),model_(model) {}
		bool execute()
		{
			model_.undel(t_);
			return true;
		}
		bool unexecute()
		{
			model_.del(t_);
			return true;
		}
		};
	template<class T>
		class Item_Del:public Cmd{
		 T* t_;
		 CModel& model_;
public:
		Item_Del(T* t,CModel& model):t_(t),model_(model) {}
		bool execute()
		{
			model_.del(t_);
			return true;
		}
		bool unexecute()
		{
			model_.undel(t_);
			return true;
		}
		};
	template<class T>
		class Item_Edit:public Cmd{
		T t_;
		T t_new_;
		CModel& model_;
	public:
		Item_Edit(T* t,CModel& model):t_(*t),model_(model) {}
		void set_new(T* t) { t_new_ = *t;}
		bool execute()
		{
			model_.edit(t_new_);
			return true;
		}
		bool unexecute()
		{
			model_.edit(t_);
			return true;
		}
		};
	class Cmd_Tool:public Cmd{
		typedef std::vector<GEXY::CPtr<Cmd> > CMDS;
		std::vector<GEXY::CPtr<Cmd> > cmds_;
		public:
			void add_cmd(GEXY::CPtr<Cmd>& c) {
				cmds_.push_back(c);
				}
			bool execute() {
				CMDS::iterator it;
				for(it = cmds_.begin(); it != cmds_.end(); ++it)
					(*it)->execute();
				return true;
			}
			bool unexecute() {
				CMDS::reverse_iterator  it;
				for(it = cmds_.rbegin(); it != cmds_.rend(); ++it)
					(*it)->unexecute();
				return true;
			}
		};
}

#endif