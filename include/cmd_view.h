#ifndef _CMD_VIEW_H_
#define _CMD_VIEW_H_
#include "cmd.h"
#include "Model_Geographic.h"
namespace gelib{
	class Cmd_View :public Cmd
		{
	Model_Geographic model_geo_;
	Model_Geographic* model_origin_;
	public:
		void front_view() {model_geo_ = *model_origin_;model_geo_.front();}
		void back_view() {model_geo_ = *model_origin_;model_geo_.back();}
		void left_view() {model_geo_ = *model_origin_;model_geo_.left();}
		void right_view() {model_geo_ = *model_origin_;model_geo_.right();}
		void center_view(double scale,double dx ,double dy)
		{
			model_geo_ = *model_origin_;
			model_geo_.center(scale,dx,dy);
		}
	public:
		Cmd_View(Model_Geographic* model_origin):model_origin_(model_origin) {}
		bool execute();
		bool unexecute(); 
		};
}
#endif